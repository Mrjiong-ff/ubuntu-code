
#ifndef COLOR_H
#define COLOR_H

#include<time.h>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

class colorknow
{
private:
public:
    Mat srcImage,grayImage,mask,dstImage1,dstImage2,dstImage3;
//    float height,width;
    vector<vector<Point>> contours;
    vector<Mat> _split;
    Rect roi1,roi2;
    int red_number=0,green_number=0,yellow_number=0;
    int judge;
     int color();
     void deal(Mat srcImage);
     int Judgment(Mat mask);

};
#endif // COLOR_H
