#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Basic Functions  //////////////////////

void main() {

    string path = "Resources/test.png";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY); // imgGray = cv.cvtColor(img,cv.COLOR_BGR2GRAY) in python
    GaussianBlur(img, imgBlur,Size(3,3),5,0);
    //Canny(imgBlur, imgCanny, 50, 150);
    Canny(img, imgCanny, 25, 75); // decrease the value for canny make more edges

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); // no Numpy in cpp :( and the kernel size is always odd
    dilate(imgCanny, imgDil, kernel);
    erode(imgDil, imgErode, kernel);

    imshow("Image", img);
    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDil); // make  canny thicker
    imshow("Image Erode", imgErode);   // make dil narraower


    waitKey(0);

}




