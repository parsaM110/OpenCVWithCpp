#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  Warp Images (KING)  //////////////////////

float w = 250, h = 350;
Mat matrix, imgWarp;



void main() {

    string path = "Resources/cards.jpg";
    Mat img = imread(path);


    Point2f src[4] = { {529,142}, {771,190},{405,395},{674,457} };
    Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f},{0.0f,h},{w,h} };

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    //create cirlce around Images


    imshow("Image", img);
    imshow("Warp", imgWarp);
    waitKey(0);

}


 
