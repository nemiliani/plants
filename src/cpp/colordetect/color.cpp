#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat imgOriginal, imgHSV, imgThresholded;

int iLowH = 0;
int iHighH = 179;

int iLowS = 0; 
int iHighS = 255;

int iLowV = 0;
int iHighV = 255;


void threshold(int, void*){

    //Threshold the image
    inRange(imgHSV, 
            Scalar(iLowH, iLowS, iLowV), 
            Scalar(iHighH, iHighS, iHighV), 
            imgThresholded); 
      
    //morphological opening (remove small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

    //morphological closing (fill small holes in the foreground)
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    imshow("Thresholded Image", imgThresholded); //show the thresholded image

}

int main( int argc, char** argv ){

    /// Load an image
    imgOriginal = imread( argv[1], 1 );
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

    

    //Create trackbars in "Control" window

    //Hue (0 - 179)
    createTrackbar("LowH", "Control", &iLowH, 179, threshold);
    createTrackbar("HighH", "Control", &iHighH, 179, threshold);

    //Saturation (0 - 255)
    createTrackbar("LowS", "Control", &iLowS, 255, threshold);
    createTrackbar("HighS", "Control", &iHighS, 255, threshold);

    //Value (0 - 255)
    createTrackbar("LowV", "Control", &iLowV, 255, threshold); 
    createTrackbar("HighV", "Control", &iHighV, 255, threshold);

    //Convert the captured frame from BGR to HSV
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 
    imshow("Original", imgOriginal); //show the original image

    /// Wait until user finishes program
    for(;;){
        int c;
        c = waitKey( 20 );
        if( (char)c == 27 ){ break; }
    }
    return 0;

}
