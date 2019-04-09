#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
int main(int argc, char *argv[]) {
  printf("OpenCV version: %d.%d\n", CV_MAJOR_VERSION, CV_MINOR_VERSION);
  Mat src; int window;
  src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  window = cvNamedWindow("Some window name", CV_WINDOW_AUTOSIZE);
  imshow("Here's a horseboi", src);
  waitKey(0);
  return 0;
}
