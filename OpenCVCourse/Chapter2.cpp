#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Images  //////////////////////

void main() {

    string path = "Resources/test.png";
    Mat img = imread(path);
    Mat imgGray;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur
    imshow("Image", img);
    imshow("Image Gray", imgGray);

    waitKey(0);

}




