{\rtf1\ansi\ansicpg1252\cocoartf1671\cocoasubrtf400
{\fonttbl\f0\fnil\fcharset0 AmericanTypewriter;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww19760\viewh19600\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 //Polynomial regression function\
cv::vector<double> fitPoly(cv::vector<cv::Point> points, int n)\
\{\
  //Number of points\
  int nPoints = points.size();\
\
  //Vectors for all the points' xs and ys\
  cv::vector<float> xValues = cv::vector<float>();\
  cv::vector<float> yValues = cv::vector<float>();\
\
  //Split the points into two vectors for x and y values\
  for (int i = 0;  i < nPoints;  i++)\
  \{\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\sl264\slmult1\pardirnatural\partightenfactor0
\cf0     xValues.push_back(points[i].x);\
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0
\cf0     yValues.push_back(points[i].y);\
  \}\
\
  //Augmented matrix\
  double matrixSystem[n+1][n+2];\
  for (int row = 0; row < n+1; row++)\
  \{\
    for (int col = 0; col < n+1; col++)\
    \{\
      matrixSystem[row][col] = 0;\
      for (int i = 0; i < nPoints; i++)\
        matrixSystem[row][col] += pow(xValues[i], row + col);\
    \}\
\
    matrixSystem[row][n+1] = 0;\
    for (int i = 0; i < nPoints; i++)\
      matrixSystem[row][n+1] += pow(xValues[i], row) * yValues[i];\
\
  \}\
\
  //Array that holds all the coefficients\
  double coeffVec[n+2];\
\
  //Gauss reduction\
  for (int i = 0; i <= n-1; i++)\
    for (int k=i+1; k <= n; k++)\
    \{\
      double t=matrixSystem[k][i]/matrixSystem[i][i];\
\
      for (int j=0;j<=n+1;j++)\
        matrixSystem[k][j]=matrixSystem[k][j]-t*matrixSystem[i][j];\
\
    \}\
\
  //Back-substitution\
  for (int i=n;i>=0;i--)\
  \{\
    coeffVec[i] = matrixSystem[i][n+1];\
    for (int j=0;j<=n+1;j++)\
      if (j!=i)\
        coeffVec[i] = coeffVec[i]-matrixSystem[i][j]*coeffVec[j];\
 \
    coeffVec[i] = coeffVec[i]/matrixSystem[i][i];\
  \}\
\
  //Construct the cv vector and return it\
  cv::vector<double> result = cv::vector<double>();\
  for (int i = 0; i < n+1; i++)\
    result.push_back(coeffVec[i]);\
  return result;\
\}\
\
//Returns the point for the equation determined\
//by a vector of coefficents, at a certain x location\
cv::Point pointAtX(cv::vector<double> coeff, double x)\
\{\
  double y = 0;\
  for (int i = 0; i < coeff.size(); i++)\
  y += pow(x, i) * coeff[i];\
  return cv::Point(x, y);\
\}\
}