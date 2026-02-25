# open-cv (OpenCV C++ practice)

A small C++ project for practicing **OpenCV** with a live webcam feed.

Current demo: **color detection + contour bounding**, tracking the detected object’s center and drawing on the frame.

## What it does

- Opens the default webcam (`cv::VideoCapture cap(0)`).
- Converts frames to HSV.
- Applies an HSV threshold mask for a configured color range (currently Blue).
- Finds contours and bounding rectangles.
- Tracks detected centers in `newPoints` and draws on the output.

## Project layout

- `main.cpp` — main OpenCV demo.
- `color_pick.cpp` — additional experiments.
- `CMakeLists.txt` — builds `OpenCVTest`.

## Build (Windows)

This project expects an OpenCV build at a hardcoded path in `CMakeLists.txt`:

```cmake
set(OpenCV_PATH "C:/Users/Siddhant/Downloads/opencv/build")
```

### Configure + build

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

If CMake can’t find OpenCV libs/headers, update `OpenCV_PATH` to your OpenCV build directory.

## Run

Run the produced executable; a window will open showing the mirrored webcam feed.

- Press `Esc` to exit.
