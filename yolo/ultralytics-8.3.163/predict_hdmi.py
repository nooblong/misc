import cv2
from ultralytics import YOLO

# ===== 1. 打开采集卡（一般就是一个“摄像头设备”）=====
# Windows 推荐用 CAP_DSHOW，减少卡顿
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

# 设置 1080p 30fps
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
cap.set(cv2.CAP_PROP_FPS, 30)

# 尝试设置为 MJPEG（很多采集卡支持，带宽更低更稳）
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'MJPG'))

# ===== 2. 加载 YOLO =====
model = YOLO("apex2.pt")  # 或你的 best.pt

# ===== 3. 循环读取并推理 =====
frame_id = 0
while True:
    ret, frame = cap.read()
    if not ret:
        print("读取失败")
        break

    if frame_id % 1 == 0:
        h, w = frame.shape[:2]
        crop = frame[h // 2 - 160:h // 2 + 160, w // 2 - 160:w // 2 + 160]
        results = model.predict(crop, imgsz=320)
    frame_id += 1

    # 画框（可选）
    annotated = results[0].plot()

    cv2.imshow("capture + yolo", annotated)

    # 按 q 退出
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()