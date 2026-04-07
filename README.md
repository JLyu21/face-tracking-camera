# Face Tracking Camera

A computer vision project that uses OpenCV for face detection and Arduino-controlled servos to track faces in real-time.

## Overview

This project creates a camera system that automatically tracks faces using:
- **OpenCV** with a pre-trained Caffe model for face detection
- **Python** for processing video stream and calculating face positions
- **Arduino** with servo motors to physically move the camera
- **Serial communication** between Python and Arduino

## Hardware Requirements

- ESP32-CAM or IP camera (streaming at `http://172.20.10.11:81/stream`)
- Arduino board (Uno, Nano, etc.)
- 2x Servo motors (pan and tilt)
- USB cable for Arduino

## Wiring

| Servo | Arduino Pin |
|-------|-------------|
| X (Pan)  | Pin 9 |
| Y (Tilt) | Pin 10 |

## Project Structure

```
face-tracking-camera/
├── opencv_faceTracking.ipynb    # Main Python script (Jupyter Notebook)
├── pyserial.ino                 # Arduino sketch for servo control
└── .vscode/
    └── tasks.json               # VS Code build tasks
```

## How It Works

1. **Face Detection**: OpenCV captures video from the IP camera and uses a DNN-based face detector
2. **Position Calculation**: Python calculates the center of detected faces
3. **Serial Communication**: Face coordinates are sent to Arduino via USB serial
4. **Servo Control**: Arduino moves servos to keep the face centered in the frame

## Setup Instructions

### 1. Install Python Dependencies

```bash
pip install opencv-python pyserial numpy
```

### 2. Download Model Files

The script automatically downloads these on first run:
- `deploy.prototxt` - Model architecture
- `res10_300x300_ssd_iter_140000_fp16.caffemodel` - Pre-trained weights

### 3. Upload Arduino Code

1. Open `pyserial.ino` in Arduino IDE
2. Select your board and port
3. Upload the sketch

### 4. Configure Camera Stream

Update the camera URL in `opencv_faceTracking.ipynb`:
```python
s = "http://YOUR_CAMERA_IP:81/stream"
```

### 5. Run the Tracker

Open `opencv_faceTracking.ipynb` in Jupyter Notebook and run all cells.

## Usage

1. Power on your ESP32-CAM and ensure it's streaming
2. Connect Arduino to your computer via USB
3. Run the Python script
4. The camera will automatically track detected faces!

Press `ESC` to exit.

## Tuning Parameters

In `pyserial.ino`:
- `deadZone` (default: 20) - Dead zone where no movement occurs (pixels)
- `gain` (default: 0.02) - Movement sensitivity multiplier

In `opencv_faceTracking.ipynb`:
- `conf_threshold` (default: 0.7) - Minimum confidence for face detection
- `send_interval` (default: 0.1) - Serial update rate (seconds)

## Troubleshooting

**"No module named 'cv2'"**
→ Install OpenCV: `pip install opencv-python`

**Serial port not found**
→ Check COM port in Device Manager and update `serialInst.port` in Python

**Camera not connecting**
→ Verify camera IP address and ensure it's on the same network

**Servos not moving**
→ Check wiring and ensure Arduino sketch is uploaded correctly

## Future Improvements

- [ ] Add support for multiple face tracking
- [ ] Implement smoother servo movement with easing
- [ ] Add GUI for real-time parameter adjustment
- [ ] Support for different camera sources (USB, Raspberry Pi Camera)
- [ ] Add face recognition to track specific people

## License

MIT License - Feel free to use and modify!

## Author

Jiaheng Lyu
