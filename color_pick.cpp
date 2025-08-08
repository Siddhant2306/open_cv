#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<iostream>

cv::Mat frame_hsv, mask , imgcolor;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

cv::VideoCapture cap(0);
cv::Mat frame;

int main()
{
    cv::namedWindow("Adjust", (640, 200));
    cv::createTrackbar("Hue min", "Adjust", &hmin, 179);
    cv::createTrackbar("Hue max", "Adjust", &hmax, 179);
    cv::createTrackbar("Sat min", "Adjust", &smin, 255);
    cv::createTrackbar("Sat max", "Adjust", &smax, 255);
    cv::createTrackbar("val min", "Adjust", &vmin, 255);
    cv::createTrackbar("val max", "Adjust", &vmax, 255);

    while (true) {
        cap >> frame; 

        cv::cvtColor(frame, frame_hsv, cv::COLOR_BGR2HSV);

        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(frame_hsv, lower ,upper, mask);

        cv::flip(frame, frame, 1);

        cv::imshow("Webcam", frame);
        cv::imshow("Mask", mask);

        if (cv::waitKey(1) == 27) break;
    }
}

