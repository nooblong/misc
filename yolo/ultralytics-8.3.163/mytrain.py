from ultralytics import YOLO

if __name__ == "__main__":
    model = YOLO(r"yolo11s.pt")

    model.train(
        data=r"C:\Users\lyl\Documents\GitHub\misc\yolo\ultralytics-8.3.163\datasets\apex2\data.yaml",
        epochs=100,
        batch=16,
        imgsz=416,
        workers=8,
        cache="disk",

        degrees=0,
        mixup=0.0,
    )