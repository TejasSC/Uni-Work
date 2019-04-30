#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, dst;
//g++ wk5.cpp -o wk5 `pkg-config --libs --cflags opencv`

void Threshold_Demo( int, void* )
{
  /* 0: Binary
  1: Binary Inverted
  2: Threshold Truncated
  3: Threshold to Zero
  4: Threshold to Zero Inverted
  */
  threshold( src, dst, threshold_value, max_BINARY_value,threshold_type );
  imshow( "Threshold Demo", dst );
}//Threshold_Demo

int main( int argc, char** argv )
{
  //Load an image
  if (argc != 2) {
    printf("Please provide a valid file path\n");
    return -1;
  }
  src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  if (src.channels()==3) {
    cvtColor(src, src, CV_RGB2GRAY);//convert src to greyscale image
  }

  //Create a window to display results
  namedWindow( "Threshold Demo", CV_WINDOW_AUTOSIZE );

  //Create Trackbar to choose type of Threshold
  createTrackbar( "Slide to get different threshold values", "Threshold Demo",
  &threshold_type, max_type, Threshold_Demo );

  createTrackbar( "Value", "Threshold Demo", &threshold_value, max_value,
    Threshold_Demo );

  //Call the function to initialize
  Threshold_Demo( 0, 0 );
  waitKey(0);
  if (strcmp(argv[1], "1.bmp")==0) {
    imwrite("Threshold 1.jpg", dst);
  } else if (strcmp(argv[1], "2.jpg")==0) {
    imwrite("Threshold 2.jpg", dst);
  } else if (strcmp(argv[1], "3.jpg")==0) {
    imwrite("Threshold 3.jpg", dst);
  }

  return 0;
}//main
