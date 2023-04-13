//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/objdetect.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;


/////////////////  Project 3  //////////////////////



//// code for real time face detection too slow on cpu

//void main() {
//
//    VideoCapture cap(0);
//    Mat img;
//
//
//    CascadeClassifier faceCascade;
//    faceCascade.load("Resources/haarcascade_frontalface_default.xml");
//
//    vector<Rect> faces;
//
//    while (true) {
//
//        cap.read(img);
//
//        faceCascade.detectMultiScale(img, faces, 1.1, 10);
//
//        for (int i = 0; i < faces.size(); i++)
//        {
//            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
//        }
//
//        if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }
//        imshow("Image", img);
//        waitKey(1);
//
//       
//
//    }
//
//    
//
//}


// detecting license by webcam

//void main() {
//
//    VideoCapture cap(0);
//    Mat img;
//
//
//    CascadeClassifier plateCascade;
//    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");
//
//    vector<Rect> plates;
//
//    while (true) {

//
//        cap.read(img);
//
//        plateCascade.detectMultiScale(img, plates, 1.1, 10);
//
//        for (int i = 0; i < plates.size(); i++)
//        {
//            rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
//        }
//
//        if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }
//        imshow("Image", img);
//        waitKey(1);
//
//
//
//    }
//
//
//
//}


//find the plates in the images by shareScreen


#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <Windows.h>
#include <iostream>

using namespace std;
using namespace cv;

Mat hwnd2mat(HWND hwnd)
{
    HDC hwindowDC, hwindowCompatibleDC;

    int height, width, srcheight, srcwidth;
    HBITMAP hbwindow;
    Mat src;
    BITMAPINFOHEADER  bi;

    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    RECT windowsize;    // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = windowsize.bottom / 1;  //change this to whatever size you want to resize to
    width = windowsize.right / 1;

    src.create(height, width, CV_8UC4);

    // create a bitmap
    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth = width;
    bi.biHeight = -height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    // copy from the window device context to the bitmap device context
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return src;
}

int main(int argc, char** argv)
{
    HWND hwndDesktop = GetDesktopWindow();
    namedWindow("output", WINDOW_NORMAL);
    int key = 0;

      CascadeClassifier plateCascade;
      plateCascade.load("Resources/haarcascade_russian_plate_number.xml");
  
      vector<Rect> plates;

    while (key != 27)
    {
        Mat src = hwnd2mat(hwndDesktop);
        // you can do some image processing here

        plateCascade.detectMultiScale(src, plates, 1.1, 10);
        
                for (int i = 0; i < plates.size(); i++)
                {
                    Mat imgCrop = src(plates[i]);
                    //imshow(to_string(i), imgCrop);
                    imwrite("Resources/Plates/" + to_string(i) + ".png",imgCrop);
                    rectangle(src, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);
                }
        
                if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }


        imshow("output", src);
        key = waitKey(60); // you can change wait time
    }

}