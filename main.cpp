#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat frame;
std::vector<std::vector<int>> newPoints;


cv::Point getcountours(cv::Mat ImgDil)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> Hierarchy;

    findContours(ImgDil, contours, Hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Point center;

    for(int i = 0 ; i < contours.size(); i++)
    {
        int area = cv::contourArea(contours[i]);
        std::cout<< area << std::endl;

        std::vector<std::vector<cv::Point>> conPoly(contours.size());
        std::vector<cv::Rect> boundRect(contours.size());
        std::string objectType;

        if(area > 1000)
        {
            float peri = arcLength(contours[i],true);
            cv::approxPolyDP(contours[i],conPoly[i],0.02*peri,true);

            std::cout << conPoly[i].size() << std::endl;
            boundRect[i] = cv::boundingRect(conPoly[i]);
            center.x = boundRect[i].x + boundRect[i].width / 2;
            center.y = boundRect[i].y;


            cv::drawContours(frame, conPoly,i,cv::Scalar(0,0,255),2);
            cv::rectangle(frame, boundRect[i].tl(), boundRect[i].br(),cv::Scalar(0,255,0),5);
        }
    }
    
    return center;
}

// hmin,smin,vmin,hmax,smax,vmax
std::vector<std::vector<int>> Color{
    {101,78,0,114,255,255} //Blue
};

std::vector<cv::Scalar> ColorValues {
    {0,0,255} // Blue
};


std::vector<std::vector<int>> findcolor(cv::Mat frame)
{
    cv::Mat frame_hsv;

    cv::cvtColor(frame, frame_hsv, cv::COLOR_BGR2HSV);

    for(int i =0 ; i <Color.size(); i++)
    {
        cv::Scalar lower(Color[i][0], Color[i][1], Color[i][2]);
        cv::Scalar upper(Color[i][3], Color[i][4], Color[i][5]);
        cv::Mat mask;
        cv::inRange(frame_hsv, lower ,upper, mask);
        imshow(std::to_string(i),mask);
        cv::Point center = getcountours(mask);

        if(center.x != 0 && center.y != 0)
        {
            newPoints.push_back({center.x , center.y, i });
        }
    }
    return newPoints;
}

void draw(std::vector<std::vector<int>> newPoints , std::vector<cv::Scalar> ColorValues)
{
    for(int i = 0 ; i < newPoints.size(); i++)
    {
        cv::circle(frame, (cv::Point(newPoints[i][0],newPoints[i][0])) , 10, ColorValues[newPoints[i][2]],cv::FILLED);
    }
}

int main() {
    cv::VideoCapture cap(0); 

    while (true) {
        cap >> frame; 

        cv::flip(frame, frame, 1);
        newPoints =  findcolor(frame);
        draw(newPoints, ColorValues);
        cv::imshow("Mirrored Webcam", frame);

        if (cv::waitKey(1) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
