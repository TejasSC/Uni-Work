#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//DON'T BE IN FISH: g++ ex4.cpp -o ex4 `pkg-config --libs --cflags opencv`

using namespace cv; Mat src, dst, color_dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
int lowHLPthresh = 20;
int max_HLPthresh = 100;
vector<Vec4i> lines;
vector<Point> allPoints;
vector<Point> pointsPlot;
vector<double> coeffs;

//Computing a polynomial line's coefficients and points on polynomial line
//n is the degree of polynomial
vector<double> fitPoly(vector<Point> points, int n){
  int nPoints = points.size();//number of points

  //vectors for all the points' xs and ys
  vector<float> xValues = vector<float>();
  vector<float> yValues = vector<float>();
  int i;
  for (i = 0; i < nPoints; i++) {
    xValues.push_back(points[i].x);
    yValues.push_back(points[i].y);
  }//for

  //Augmented matrix
  double matrixSystem[n+1][n+2];
  for (int row = 0; row < n+1; row++)
  {
    for (int col = 0; col < n+1; col++)
    {
      matrixSystem[row][col] = 0;
      for (int i = 0; i < nPoints; i++)
        matrixSystem[row][col] += pow(xValues[i], row + col);
    }

    matrixSystem[row][n+1] = 0;
    for (int i = 0; i < nPoints; i++)
      matrixSystem[row][n+1] += pow(xValues[i], row) * yValues[i];

  }

  //Array that holds all the coefficients
  double coeffVec[n+2];

  //Gauss reduction
  for (int i = 0; i <= n-1; i++)
    for (int k=i+1; k <= n; k++)
    {
      double t=matrixSystem[k][i]/matrixSystem[i][i];

      for (int j=0;j<=n+1;j++)
        matrixSystem[k][j]=matrixSystem[k][j]-t*matrixSystem[i][j];

    }

  //Back-substitution
  for (int i=n;i>=0;i--)
  {
    coeffVec[i] = matrixSystem[i][n+1];
    for (int j=0;j<=n+1;j++)
      if (j!=i)
        coeffVec[i] = coeffVec[i]-matrixSystem[i][j]*coeffVec[j];

    coeffVec[i] = coeffVec[i]/matrixSystem[i][i];
  }

  //Construct the cv vector and return it
  vector<double> result = vector<double>();
  for (int i = 0; i < n+1; i++)
    result.push_back(coeffVec[i]);
  return result;
}//fitPoly
//Returns the point for the equation determined
//by a vector of coefficents, at a certain x location
Point pointAtX(vector<double> coeff, double x){
  double y = 0;
  for (int i = 0; i < coeff.size(); i++)
    y += pow(x, i) * coeff[i];
  return Point(x, y);
}//pointAtX
/**
* @function on_callback
* @brief Trackbar callback - Canny thresholds input with a ratio 1:3
*/
void on_callback(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);
  src.copyTo( dst, detected_edges);
  HoughLinesP(dst, lines, 1, CV_PI/180, lowHLPthresh, 80, 10);
  /*Step 3: Apply probabilistic Hough transformation*/
  cvtColor(dst, color_dst, CV_GRAY2BGR );
  // HoughLinesP(dst, lines, 1, CV_PI/180, 70, 80, 10);
  for (size_t i = 0; i < lines.size(); i++) {
    //Don't want vertical lines, i.e. where two points(x,y) have equal x's
    if (lines[0]!=lines[2]) {
      //apply the gradient threshold
      if ((lines[i][3]-lines[i][1])/(lines[i][2]-lines[i][0]) <= 0.5
      && (lines[i][3]-lines[i][1])/(lines[i][2]-lines[i][0]) >= -0.5) {
        line( color_dst, Point(lines[i][0], lines[i][1]),
        Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
      }//if
    }//if
  }//for
  /*Step 4: polynomial regression*/
  int i, j, k;
  for (k = 0; k < lines.size(); k++) {
    allPoints.push_back(Point(lines[k][0], lines[k][1]));
    allPoints.push_back(Point(lines[k][2], lines[k][3]));
  }//for
  //create coefficient vector from all the points, with degree 2
  coeffs = fitPoly(allPoints, 2);
  for (int i = 0; i < allPoints.size(); i++) {
    pointsPlot.push_back(pointAtX(coeffs, allPoints[i].x));
    circle(color_dst, pointsPlot[i], 1, Scalar( 0, 255, 255 ));
  }//for
  /// Show the image
  imshow( "Horizon detected", color_dst );
}//on_callback

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Please provide a valid file path\n");
    return -1;
  }
  src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
  namedWindow("Original picture", CV_WINDOW_AUTOSIZE);
  imshow("Original picture", src);
  //pre step: blur the image before doing anything
  /*Step 1: convert src to greyscale image, apply gaussian blur*/
  if (src.channels()==3) {
    cvtColor(src, src, CV_RGB2GRAY);
  }//if
  GaussianBlur(src, src, Size(3,3), 0);
  // namedWindow("blurred picture", CV_WINDOW_AUTOSIZE);
  // imshow("blurred picture", src);

  namedWindow("Horizon detected", CV_WINDOW_AUTOSIZE);
  /*Step 1.5: apply binary threshold with black and white colours*/
  //src, dst, threshold_type, max binary value, threshold_type
  //threshold( src, src, 0, 255,3 );
  /*Step 2: Apply Canny filter on frame, leaving us with image of edges*/
  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Canny Threshold:", "Horizon detected", &lowThreshold,
    max_lowThreshold, on_callback );
  //src, dst, lower threshold, upper threshold, kernel size
  //Canny(src, dst, 10, 70, 3);
  //filter out vertical lines by calculating inverse tangent of each line
  createTrackbar( "HLP Threshold:", "Horizon detected", &lowHLPthresh,
    max_HLPthresh, on_callback );

  on_callback(0, 0);
  waitKey(0);
  if (strcmp(argv[1], "horizon1.jpg")==0) {
    imwrite("Canny 1.jpg", dst);
  } else if (strcmp(argv[1], "horizon2.png")==0) {
    imwrite("Canny 2.jpg", dst);
  } else if (strcmp(argv[1], "horizon3.jpg")==0) {
    imwrite("Canny 3.jpg", dst);
  } else if (strcmp(argv[1], "horizon0.jpg")==0) {
    imwrite("Canny 0.jpg", dst);
  }
  return 0;
}//main
