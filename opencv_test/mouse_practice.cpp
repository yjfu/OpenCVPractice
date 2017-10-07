/**
 * void mouseHandle(int event, int x, int y, int flags, void* para)
 * event参数:
 * #define EVENT_MOUSEMOVE 0             滑动
 * #define EVENT_LBUTTONDOWN 1           左键点击
 * #define EVENT_RBUTTONDOWN 2           右键点击
 * #define EVENT_MBUTTONDOWN 3           中间点击
 * #define EVENT_LBUTTONUP 4             左键释放
 * #define EVENT_RBUTTONUP 5             右键释放
 * #define EVENT_MBUTTONUP 6             中间释放
 * #define EVENT_LBUTTONDBLCLK 7         左键双击
 * #define EVENT_RBUTTONDBLCLK 8         右键双击
 * #define EVENT_MBUTTONDBLCLK 9         中间释放
 * flag参数:
 * #define EVENT_FLAG_LBUTTON 1           左键移动
 * #define EVENT_FLAG_RBUTTON 2           右键移动
 * #define EVENT_FLAG_MBUTTON 4           中间移动
 * #define EVENT_FLAG_CTRLKEY 8           按Ctrl不放事件
 * #define EVENT_FLAG_SHIFTKEY 16         按Shift不放事件
 * #define EVENT_FLAG_ALTKEY 32           按Alt不放事件
 */
#include "practice.h"

struct UserData{
    Mat *src, *to_show;
    String winName;
    int radium;
    UserData(Mat *src, Mat *to_show, String winName, int radium){
        this->src = src;
        this->to_show = to_show;
        this->winName = winName;
        this->radium = radium;
    }
};

void drawOnAPixel(Vec3b& pix){
    for(int i =0;i<3;i++)pix[i] = 0;
}

void dim(Vec3b& pix, Vec3b dst, int stepNum){
    int step[3];
    for(int i = 0;i<3;i++)step[i] = saturate_cast<uchar>(dst[i]/stepNum);
    bool dimEnd = false;
    for(int i = 0;i<3;i++){
        if(pix[i]+step[i]>=dst[i])dimEnd = true;
        pix[i] += step[i];
    }
    if(dimEnd)
        for(int i = 0;i<3;i++)pix[i] = dst[i];
}

void mouseHandle(int event, int x, int y, int flags, void* para){
    static bool down =false;
    UserData* ud = (UserData*)para;
    if(event == EVENT_MOUSEMOVE&&down){
        //printf("pos: (%d, %d)\n", x, y);
        for(int i = -ud->radium;i<ud->radium+1;i++){
            for(int j = -ud->radium;j<ud->radium+1;j++){
                Vec3b& pix = ud->to_show->at<Vec3b>(y+j, x+i);
                drawOnAPixel(pix);
            }
        }
    }
    if(event == EVENT_LBUTTONDOWN)down = true;
    if(event == EVENT_LBUTTONUP)down = false;
}

void mouseTest(string imgName, string winName, int radium){
    namedWindow(winName);
    Mat img = imread(imgName);
    Mat toShow;
    img.copyTo(toShow);

    UserData ud(&img, &toShow, winName, radium);
    setMouseCallback(winName, mouseHandle, &ud);

    while(1){
        imshow(winName, *ud.to_show);
        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                dim(ud.to_show->at<Vec3b>(i, j), ud.src->at<Vec3b>(i, j), 10);
            }
        }
        if(waitKey(5)==27)break;
    }
}
