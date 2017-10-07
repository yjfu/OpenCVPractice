#include "practice.h"

struct UserData{
    string winName;
    Mat* src;
    Mat* toShow;
    int channel;
    UserData(string winName, Mat* src, Mat* toShow, int channel){
        this->src = src;
        this->toShow = toShow;
        this->winName = winName;
        this->channel = channel;
    }
};
void changeChannel(int pos, void* usrData){
    UserData* ud = (UserData*)usrData;
    for(int i = 0;i<ud->src->rows;i++){
        for(int j = 0;j<ud->src->cols;j++){
            Vec3b src = ud->src->at<Vec3b>(i, j);
            Vec3b& dst = ud->toShow->at<Vec3b>(i, j);
            dst[ud->channel] = saturate_cast<uchar>(pos*1.0/255*src[ud->channel]);
        }
    }
    imshow(ud->winName, *(ud->toShow));
}
void trackBarTest(string imgName, string winName){
    Mat img = imread(imgName);
    Mat toShow;
    img.copyTo(toShow);
    namedWindow(winName);
    UserData* ud_blue = new UserData(winName, &img, &toShow, 0);
    UserData* ud_green = new UserData(winName, &img, &toShow, 1);
    UserData* ud_red = new UserData(winName, &img, &toShow, 2);
    int startPos = 255;
    int maxPos = 2*255;
    createTrackbar("red", winName, &startPos, maxPos, changeChannel, ud_red);
    createTrackbar("green", winName, &startPos, maxPos, changeChannel, ud_green);
    createTrackbar("blue", winName, &startPos, maxPos, changeChannel, ud_blue);
    imshow(winName, toShow);
    waitKey(0);
}