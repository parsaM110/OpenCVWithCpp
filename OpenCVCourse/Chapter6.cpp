#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Color Detection  //////////////////////
//
//Mat imgHSV, mask; 
//// create track bar with while loop for finding the values
//int hmin = 0, smin = 110, vmin = 153;
//int hmax = 19, smax = 240, vmax = 255;
//
//void main() {
//    // standard practice int main(){return 0;} -> but void just works fine
//
//    /*string path = "Resources/lambo.png";*/ //use shapes.jpg instead to see all colors
//    string path = "Resources/shapes.png";
//    Mat img = imread(path);
//    cvtColor(img, imgHSV, COLOR_BGR2HSV); //hue saturation value
//    // we will use HSV because its better and real life for Color Detection , images usually don't have only one color like red but a range of similar colors
//
//    namedWindow("Track bars", (640, 200));
//    createTrackbar("Hue min", "Track bars",&hmin,179); // max of hue is 179 and the others are 255
//    createTrackbar("Sat min", "Track bars", &smin, 255);
//    createTrackbar("Val min", "Track bars", &vmin, 255);
//    createTrackbar("Hue max", "Track bars", &hmax, 179);
//    createTrackbar("Sat max", "Track bars", &smax, 255);
//    createTrackbar("Val max", "Track bars", &vmax, 255);
//
//    while (true) {
//
//
//        Scalar lower(hmin, smin, vmin);
//        Scalar upper(hmax, smax, vmax);
//        inRange(imgHSV, lower, upper, mask);
//
//        imshow("Image", img);
//        imshow("Image HSV", imgHSV);
//        imshow("Image Mask", mask);
//        waitKey(1);
//    }
//
//}

///////////////  Color Detection with webcam  //////////////////////

Mat imgHSV, mask;
// create track bar with while loop for finding the values
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

// try to get the values by tuning -> for blue pen
//int hmin = 95, smin = 100, vmin = 248;
//int hmax = 121, smax = 255, vmax = 255;

//  for blue red
//int hmin = 149, smin = 120, vmin = 165;
//int hmax = 179, smax = 255, vmax = 255;

void main() {
    // standard practice int main(){return 0;} -> but void just works fine

    VideoCapture cap(0);
    Mat img;
    
    namedWindow("Track bars", (640, 200));
    createTrackbar("Hue min", "Track bars", &hmin, 179); // max of hue is 179 and the others are 255
    createTrackbar("Sat min", "Track bars", &smin, 255);
    createTrackbar("Val min", "Track bars", &vmin, 255);
    createTrackbar("Hue max", "Track bars", &hmax, 179);
    createTrackbar("Sat max", "Track bars", &smax, 255);
    createTrackbar("Val max", "Track bars", &vmax, 255);


    while (true) {



        cap.read(img);
        cvtColor(img, imgHSV, COLOR_BGR2HSV);

        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        imshow("Image", img);
        imshow("Image HSV", imgHSV);
        imshow("Image Mask", mask);
       
        waitKey(1);

    }

   

}



