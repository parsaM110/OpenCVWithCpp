#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


///////////////  Color image  //////////////////////

void main() {
    // standard practice int main(){return 0;} -> but void just works fine

    string path = "Resources/lambo.png";
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);

}


