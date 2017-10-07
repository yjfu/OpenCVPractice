#include "practice.h"

int main(){
    //trackBarTest("cat_small.jpg", "track bar test");
    //mouseTest("cat_small.jpg", "mouse test", 10);
    Mat img (Size(300, 300), CV_8UC3, Scalar(255, 255, 255));

    drawEllipse(img, Point(150, 150), Size(50, 100), 90, 0, 360, -1, Scalar(0, 0, 0));
    drawCircle(img, Point(150, 150), 50, -1, Scalar(255, 255, 255));
    drawCircle(img, Point(150, 150), 25, -1, Scalar(0, 0, 0));
    namedWindow("ellipse", WINDOW_NORMAL);
    imshow("ellipse", img);
    waitKey(0);
}