#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;



/////////////////  Project 1 (Virtual Painter)  //////////////////////

// no hard code for colors we use vector for 4 colors
//<hmin,smin,vmin,hmax,smax,vmax>
vector<vector<int>> myColors{ {95,100,248,121,255,255}, //blue
      {149,120,165,179,255,255} }; //red
Mat img;
vector<vector<int>> newPoints;
//{{x,y,0 --> blue},{x,y,1 --> red}}
vector<Scalar> myColorValues{ {255,0,0}, //blue
                            {0,0,255} }; //red

Point getContours(Mat imgDil) {


    //ex: {{Point(20,20),Point(50,60)}, {Point(20,20),Point(50,60)}, {Point(20,20),Point(50,60)}}
    vector<vector<Point>> contours;
    // a vector with 4 integer value in it 
    vector<Vec4i> hierarchy;



    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(img, contours, -1, Scalar(255,0,255),10);
    // -1 means all, increase the last value to make it the thicker

    //filtering small one shape

    vector<vector<Point>> conPoly(contours.size()); // you have to define it out of loop but I get errors |-> corner polygon
    vector<Rect> boundRect(contours.size());
    Point myPoint(0, 0);

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;

       
        string objectType;

        if (area > 25)
        {
            float peri = arcLength(contours[i], true); //true means it is a closed object
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); //could use 3 instead of 0.02 * peri
            /*drawContours(img, contours, i, Scalar(255, 0, 255), 2);*/
            /*drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);*/
            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width / 2;
            myPoint.y = boundRect[i].y;
           


            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
           
        }
    }
    return myPoint;

}


vector<vector<int>> findColor(Mat img)
{
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    for(int i = 0;i<myColors.size();i++)
    { 
    /*Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);*/
        Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
        Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
        Mat mask;
    inRange(imgHSV, lower, upper, mask);
   /* imshow(to_string(i), mask);*/
         Point myPoint = getContours(mask);
         if (myPoint.x != 0 && myPoint.y != 0) {
        newPoints.push_back({ myPoint.x,myPoint.y,i });
        }
    }
    return newPoints;
}


void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues) {

    for (int i = 0; i < newPoints.size(); i++) {
        circle(img, (Point(newPoints[i][0],newPoints[i][1])), 10, myColorValues[newPoints[i][2]], FILLED);
    }
}

void main() {


    VideoCapture cap(0);
   


    while (true) {

        cap.read(img);
        newPoints = findColor(img);
        drawOnCanvas(newPoints,myColorValues);
        imshow("Image", img);
        //waitKey(1); to fast
        waitKey(1);

    }



}

