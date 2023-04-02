#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Draw Shapes and Text   //////////////////////

void main() {

    // Blank Image
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); //an image with 8bit unsigned(0-255) and 3 Channel BGR- WE don't have numpy so you have to use Scalar

    //circle(img, Point(256, 256), 155, Scalar(0, 69, 255),10);
    circle(img, Point(256, 256), 155, Scalar(0, 69, 255),FILLED);
    
    /*rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255),10);*/
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
    line(img, Point(130, 296),Point(382,450),Scalar(255,255,255),2);

    //putText(img, "hello world", Point(137, 262), FONT_HERSHEY_DUPLEX,2,Scalar(0, 69, 255),2); //the font is too big
    //putText(img, "hello world", Point(137, 262), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 2); //the font is better
    putText(img, "hello world", Point(137, 262), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 5); 


    imshow("Image", img);

    waitKey(0);

}




