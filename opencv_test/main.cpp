#include "practice.h"

int main(){
    //trackBarTest("cat_small.jpg", "track bar test");
    //mouseTest("cat_small.jpg", "mouse test", 10);
    Mat img = imread("cat_small.jpg");
    Mat dst;
    imshow("src", img);
    cvtColor(img, dst, COLOR_RGB2BGR);
    imshow("dst", dst);
    waitKey(0);
}