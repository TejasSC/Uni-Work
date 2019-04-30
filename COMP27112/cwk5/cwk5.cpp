#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int sizeKernel = 127, maxAlpha = 10, alpha = 1;
Mat src, blurPic, histData, histOutput, change;

Mat drawHist(Mat hist, int scale) {
  double mx = 0;
  minMaxLoc(hist, 0, &mx, 0, 0);
  Mat result = Mat::zeros(256*scale, 256*scale, CV_8UC1);
  for(int i = 0; i < 255; i++) {
    //get histogram values
    float histValue = hist.at<float>(i, 0);
    float nextValue = hist.at<float>(i+1, 0);
    //create 4 points for polygon
    Point p1 = Point(i*scale, 256*scale);
    Point p2 = Point((i+1)*scale, 256*scale);
    Point p3 = Point((i+1)*scale, (256-nextValue*256/mx)*scale);
    Point p4 = Point(i*scale, (256-nextValue*256/mx)*scale);

    //drawPolygon(ending in pl)
    int numPoints = 5;
    Point points[] = {p1, p2, p3, p4, p1};
    fillConvexPoly(result, points, numPoints, Scalar::all(256),0,0);
  }//for
  return result;
}//drawHist

//function called everytime slider changes value
void trackbar(int, void*){
  sizeKernel = 1 + 2*alpha;//kernel size must be a positive odd number
  //Using GaussianBlur function to perform image smoothing
  //bigger image -> more smoothing
  GaussianBlur(src, blurPic, Size(sizeKernel, sizeKernel), 0);
  imshow("Original picture", blurPic);
  //offset added to ensure greyscale values go between brightnesses of 0 and 255
  change = 128 + (src - blurPic);
  imshow("Showing difference", change);
  int channels[] = {0};
  int sizeHgrams[] = {256};
  float range[] = {0,256};
  const float* rangeHgram[] = {range};
  calcHist(&change, 1, channels, Mat(), histData, 1, sizeHgrams, rangeHgram);
  histOutput = drawHist(histData, 1);
  namedWindow("histogram output", 256);
  imshow("histogram output", histOutput);
}//tracker

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Please provide a valid file path\n");
    return -1;
  }
  src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  if (src.channels()==3) {
    cvtColor(src, src, CV_RGB2GRAY);//convert src to greyscale image
  }
  namedWindow("Original picture", CV_WINDOW_AUTOSIZE);
  imshow("Original picture", src);
  //creates and adds slider to the window
  //slider alters the value alpha as it moves
  createTrackbar("Blur Slider","Original picture",&alpha, maxAlpha, trackbar);
  waitKey(0);
  return 0;
}
