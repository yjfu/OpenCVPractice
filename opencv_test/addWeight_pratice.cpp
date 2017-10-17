#include"practice.h"

bool inRange(int radius, int xCentral, int yCentral, int x, int y){
    return radius*radius>(y-yCentral)*(y-yCentral)+(x-xCentral)*(x-xCentral);
}
Mat getRadialMask(int radius, Size size){
    Mat mask(size, CV_8UC1);
    int xCentral = size.width/2;
    int yCentral = size.height/2;
    for(int i = 0;i<size.height;i++){
        //各通道交错排列,data的长度为n*width,n为通道数
        uchar* data = mask.ptr<uchar>(i);
        for(int j = 0;j<size.width;j++){
            if(inRange(radius, xCentral, yCentral, j, i))
                data[j] = 1;
            else
                data[j] = 0;
        }
    }
    return mask;
}
void wave(){
    Mat cat = imread("cat_small.jpg");
    Mat wave = imread("wave.jpg", 0);
    resize(wave, wave, cat.size());

    int maxRadium = max(cat.size().height, cat.size().width);
    maxRadium /= 2;
    for(int i = 0;i<maxRadium;i++) {
        Mat mask = getRadialMask(i, wave.size());
        Mat maskedWave;
        wave.copyTo(maskedWave, mask);
        //imshow("wave-gray", maskedWave);
        cvtColor(maskedWave, maskedWave, COLOR_GRAY2BGR);
        Mat mix;
        addWeighted(cat, 0.8, maskedWave, 0.2, 0, mix);
        imshow("mixed", mix);
        waitKey(30);
    }
    waitKey(0);
}