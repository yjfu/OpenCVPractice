#include"practice.h"

int lineType = 8;
const double PI = acos(-1);

void drawEllipse(Mat img, Point center, Size axes, double angle,
        double startAngle, double endAngle, int thickness, Scalar color){

    ellipse(img, center, axes, angle, startAngle,
            endAngle, color,thickness, lineType);
}

void drawCircle(Mat img, Point center, int radium, int thickness, Scalar color){
    circle(img, center, radium, color, thickness, lineType);
}

/**
 * 顺时针旋转弧度值
 */
Point span(Point center, Point src, double theta){
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    Point dst = src-center;
    double newX = dst.x*cosTheta+dst.y*sinTheta;
    double newY = dst.y*cosTheta-dst.x*sinTheta;

    dst.x = (int)newX+center.x;
    dst.y = (int)newY+center.y;

    return dst;
}
void drawFilledHexagram(Mat img, Point center, int radium, Scalar color){
    Point points[2][3];
    points[0][0] = Point(center.x, center.y+radium);
    points[1][0] = Point(center.x, center.y-radium);
    for(int i = 0;i<2;i++){
        points[i][1] = span(center, points[i][0], PI*2/3);
        points[i][2] = span(center, points[i][0], PI*4/3);
    }

    /**
     * 这个函数是先划定区域再着色
     * 对于points[0]和points[1]两个多边形,着色时取抑或
     * 若想取并,则应该对两个多边形分别两次调用这个函数
     */
//    const Point *pToPoints[2] = {points[0], points[1]};
//    int pointNum[] = {3, 3};
//    fillPoly(img, pToPoints, pointNum, 2, color, 8);

    /**
     * 取并的代码
     */
    const Point *pToPoints1[1] = {points[1]};
    const Point *pToPoints2[1] = {points[0]};
    int pointNum2[] = {3};
    fillPoly(img, pToPoints1, pointNum2, 1, color, 8);
    fillPoly(img, pToPoints2, pointNum2, 1, color, 8);
}

void drawNAngleStart(Mat img, Point center, int radium, Scalar color, int angleNum){
    Point *pointsOuter = new Point[angleNum];
    Point *pointsInner = new Point[angleNum];
    double innerRadium = radium/10;
    pointsOuter[0] = Point(0, -radium)+center;
    pointsInner[0] = Point(0, -innerRadium)+center;
    for(int i = 1;i<angleNum;i++){
        pointsOuter[i] = span(center, pointsOuter[0], 2*i*PI/angleNum);
        pointsInner[i] = span(center, pointsInner[0], 2*i*PI/angleNum);
    }
    for(int i = 0;i<angleNum;i++){
        pointsInner[i] = span(center, pointsInner[i], PI/angleNum);
    }

    for(int i = 0;i<angleNum;i++){
        line(img, pointsInner[i], pointsOuter[i], color, 1, 8);
        line(img, pointsInner[i], pointsOuter[(i+1)%angleNum], color, 1, 8);
    }
    delete []pointsInner;
    delete []pointsOuter;
}

void paintEye(){
    Mat img (Size(300, 300), CV_8UC3, Scalar(255, 255, 255));

    drawNAngleStart(img, Point(150, 150), 150, Scalar(0, 0, 0), 12);
    drawEllipse(img, Point(150, 150), Size(50, 100), 90, 0, 360, -1, Scalar(0, 0, 0));
    drawEllipse(img, Point(150, 150), Size(75, 150), 90, 120, 240, 3, Scalar(0, 0, 0));
    drawCircle(img, Point(150, 150), 50, -1, Scalar(255, 255, 255));
    drawCircle(img, Point(150, 150), 25, -1, Scalar(0, 0, 0));
    drawFilledHexagram(img, Point(150, 150), 25, Scalar(0, 0, 255));
    namedWindow("eye", WINDOW_NORMAL);
    imshow("eye", img);
    waitKey(0);
}
