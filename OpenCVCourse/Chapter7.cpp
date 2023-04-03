#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


/////////////////  shapes and contours Detecting   //////////////////////

Mat imgGray, imgBlur, imgCanny, imgDil;


void getContours(Mat imgDil,Mat img) {


    //ex: {{Point(20,20),Point(50,60)}, {Point(20,20),Point(50,60)}, {Point(20,20),Point(50,60)}}
    vector<vector<Point>> contours;
    // a vector with 4 integer value in it 
    vector<Vec4i> hierarchy; 
   
    

    findContours(imgDil,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    //drawContours(img, contours, -1, Scalar(255,0,255),10);
    // -1 means all, increase the last value to make it the thicker
    
    //filtering small one shape

    for (int i = 0; i < contours.size(); i++) 
    {
        int area = contourArea(contours[i]);
        cout << area << endl;

        vector<vector<Point>> conPoly(contours.size()); // you have to define it out of loop but I get errors |-> corner polygon
        vector<Rect> boundRect(contours.size());
        string objectType;

        if (area > 1000)
        {
            float peri = arcLength(contours[i], true); //true means it is a closed object
            approxPolyDP(contours[i], conPoly[i], 0.02*peri, true); //could use 3 instead of 0.02 * peri
            /*drawContours(img, contours, i, Scalar(255, 0, 255), 2);*/
            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]);
            //rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

            int objCor = (int)conPoly[i].size(); 

            if (objCor == 3) { objectType = "Tri"; }
            if (objCor == 4) {
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                cout << aspRatio << endl;
                if (aspRatio < 0.95 && aspRatio < 1.05) { objectType = "Square"; }
                else { objectType = "Rect"; }
            } //use elseif instead
            if (objCor > 4) { objectType = "Circle"; }


            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
            /*putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 5);*/  //to big font
            putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN,1, Scalar(0, 69, 255),0.5);


        }
    }

}

void main() {

    string path = "Resources/shapes.png";
    Mat img = imread(path);
    
    // Preprocessing the image -> make a smooth line for Canny
    cvtColor(img, imgGray, COLOR_BGR2GRAY); 
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 5, 0);
    Canny(img, imgCanny, 25, 75); 
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); 
    dilate(imgCanny, imgDil, kernel);

    getContours(imgDil,img);

    imshow("Image", img);
    //imshow("Image Gray", imgGray);
    //imshow("Image Blur", imgBlur);
    //imshow("Image Canny", imgCanny);
    //imshow("Image Dilation", imgDil); // make  canny thicker
    waitKey(0);

}
