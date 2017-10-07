#include"practice.h"

int lineType = 8;
Scalar color (255, 0, 0);

void drawEllipse(Mat img, Point center, Size axes, double angle,
        double startAngle, double endAngle, int thickness, Scalar color){

    ellipse(img, center, axes, angle, startAngle,
            endAngle, color,thickness, lineType);
}

void drawCircle(Mat img, Point center, int radium, int thickness, Scalar color){
    circle(img, center, radium, color, thickness, lineType);
}

Point span(Point center, Point src, double theta){
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);
    Point dst = src-center;
    double newX = dst.x*cosTheta-dst.y*sinTheta;
    double newY = dst.y*cosTheta+dst.x*sinTheta;

    dst.x = (int)newX+src.x;
    dst.y = (int)newY+src.y;

    return dst;
}
void drawHexagram(Mat img, Point center, int radium, int thickness, Scalar color){
    Point points[2][3];
    points[0][0] = Point(center.x, center.y+radium);
    points[1][0] = Point(center.x, center.y-radium);
    for(int i = 0;i<2;i++){
        points[i][1] = span(center, points[i][0], 120);
        points[i][1] = span(center, points[i][0], 240);
    }

    
}