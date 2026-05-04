import cv2
from ultralytics import YOLO

model = YOLO("apex2.pt")

cap = cv2.VideoCapture(r"C:\Users\lyl\Videos\6.23.mp4")

fps = cap.get(cv2.CAP_PROP_FPS)
w = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
h = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

out = cv2.VideoWriter(
    "output.mp4",
    cv2.VideoWriter_fourcc(*"mp4v"),
    fps,
    (w, h)
)

CROP_SIZE = 320
frame_id = 0
while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # ===== 计算中心裁剪区域 =====
    cx, cy = w // 2, h // 2
    x1 = cx - CROP_SIZE // 2
    y1 = cy - CROP_SIZE // 2
    x2 = cx + CROP_SIZE // 2
    y2 = cy + CROP_SIZE // 2

    crop = frame[y1:y2, x1:x2]

    # ===== 只对 crop 预测 =====

    if frame_id % 2 == 0:  # 每2帧推理一次（60 → 30FPS推理）
        results = model(crop)
        last_boxes = results[0].boxes
    else:
        # 复用上一帧结果
        pass
    frame_id += 1


    # ===== 把检测框映射回原图 =====
    if results[0].boxes is not None:
        for box in results[0].boxes:
            bx1, by1, bx2, by2 = box.xyxy[0].tolist()

            # 映射回原图坐标
            bx1 += x1
            bx2 += x1
            by1 += y1
            by2 += y1

            # 画框
            cv2.rectangle(
                frame,
                (int(bx1), int(by1)),
                (int(bx2), int(by2)),
                (0, 255, 0),
                2
            )

    # 可视化裁剪区域（方便调试）
    cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 0, 0), 1)

    out.write(frame)

cap.release()
out.release()
cv2.destroyAllWindows()