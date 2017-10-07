#ifndef PRACTICE_H
#define PRACTICE_H

#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void trackBarTest(string imgName, string winName);
void mouseTest(string imgName, string winName, int radium);
void drawEllipse(Mat img, Point center, Size axes, double angle, double startAngle, double endAngle, int thickness, Scalar color);
void drawCircle(Mat img, Point center, int radium, int thickness, Scalar color);
#endif