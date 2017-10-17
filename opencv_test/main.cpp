#include "practice.h"

void takePhotos(){
    VideoCapture vc(0);
    waitKey(2000);
    Mat wss;

    vc>>wss;
    Mat small_wss;
    resize(wss, small_wss, Size(wss.cols/2, wss.rows/2));
    imwrite("wss.jpg",  small_wss);

    Mat img = imread("wss.jpg");
    imshow("a", img);
    waitKey(0);
}
int main(){
    //trackBarTest("cat_small.jpg", "track bar test");
    //mouseTest("cat_small.jpg", "mouse test", 10);
    //paintEye();

    wave();
}