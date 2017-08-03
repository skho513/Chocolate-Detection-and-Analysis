#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

Mat src; Mat src_HSV;
Mat src2; Mat src2_gray;
RNG rng(12345);

void drawCircles(Mat red_hue_image, Mat green_hue_image, Mat white_hue_image, Mat yellow_hue_image, Mat blue_hue_image, Mat orig_image);
void thresh_callback(int, void*);

int main( int argc, char** argv )
{
  /// Load source image	
  src = imread( argv[1], 1 );
  src2 = imread( argv[2], 1); 

  cvtColor(src2, src2_gray, CV_BGR2GRAY);
  blur(src2_gray, src2, Size(3,3));
  thresh_callback(0, 0);

  Mat copy_image = src.clone();

  medianBlur(src, src, 3);
	
  /// Convert image to HSV and blur it
  cvtColor( src, src_HSV, CV_BGR2HSV );

  /// Threshold the HSV image, keep only red pixels
  Mat red_hue_image;
  inRange(src_HSV, Scalar(1,100,100), Scalar(8,255,255), red_hue_image);

  // Threshold the HSV image, keep only green pixels
  Mat green_hue_image;
  inRange(src_HSV, Scalar(50,100,100), Scalar(70,255,255), green_hue_image);

  // Threshold the HSV image, keep only white pixels
  Mat white_hue_image;
  inRange(src_HSV, Scalar(0,0,200), Scalar(179,100,255), white_hue_image);

  // Threshold the HSV image, keep only yellow pixels
  Mat yellow_hue_image;
  inRange(src_HSV, Scalar(20,100,100), Scalar(30,255,255), yellow_hue_image);

  // Threshold the HSV image, keep only blue pixels
  Mat blue_hue_image;
  inRange(src_HSV, Scalar(90,50,50), Scalar(100,255,255), blue_hue_image);

  GaussianBlur(red_hue_image, red_hue_image, Size(9, 9), 2, 2);
  GaussianBlur(green_hue_image, green_hue_image, Size(9, 9), 2, 2); 
  GaussianBlur(white_hue_image, white_hue_image, Size(9, 9), 2, 2);
  GaussianBlur(yellow_hue_image, yellow_hue_image, Size(9, 9), 2, 2);
  GaussianBlur(blue_hue_image, blue_hue_image, Size(9, 9), 2, 2);

  drawCircles(red_hue_image, green_hue_image, white_hue_image, yellow_hue_image, blue_hue_image, copy_image); 

  waitKey(0);
  return(0);
}

void drawCircles(Mat red_hue_image, Mat green_hue_image, Mat white_hue_image, Mat yellow_hue_image, Mat blue_hue_image, Mat orig_image)
{

  ofstream outputFile;
  outputFile.open ("QuestionTwo_Output.txt");
// Use the Hough transform to detect circles in the combined threshold image
	vector<Vec3f> circles;

	// Red
	HoughCircles(red_hue_image, circles, CV_HOUGH_GRADIENT, 1, red_hue_image.rows/20, 10, 20, 30, 60);

// Loop over all detected circles and outline them on the original image

	for(size_t i = 0; i < circles.size(); ++i) {
		Point center(round(circles[i][0]), round(circles[i][1]));
		int radius = round(circles[i][2]);

  		// Circle outline
	           circle(orig_image, center, radius, Scalar(0, 0, 255), 5);
	}
	cout << "There are " << circles.size() << " red chocolate eggs" << endl;


  outputFile << "There are "  << circles.size() << " red chocolate eggs. \n" <<
 endl;	

	// Green
	HoughCircles(green_hue_image, circles, CV_HOUGH_GRADIENT, 1, green_hue_image.rows/11, 10, 20, 0, 100);

	for(size_t i = 0; i < circles.size(); ++i) {
		Point center(round(circles[i][0]), round(circles[i][1]));
		int radius = round(circles[i][2]);

	           circle(orig_image, center, radius, Scalar(0, 255, 0), 5);
	}

	cout << "There are " << circles.size() << " green chocolate eggs" << endl;

	outputFile << "\nThere are "  << circles.size() << " green chocolate eggs. \n" << endl;
	

	// White
	HoughCircles(white_hue_image, circles, CV_HOUGH_GRADIENT, 1, white_hue_image.rows/15, 10, 20, 0, 100);

	for(size_t i = 0; i < circles.size(); ++i) {
		Point center(round(circles[i][0]), round(circles[i][1]));
		int radius = round(circles[i][2]);

	           circle(orig_image, center, radius, Scalar(255, 255, 255), 5);
	}
	cout << "There are " << circles.size() << " white chocolate eggs" << endl;

	outputFile << "There are "  << circles.size() << " white chocolate eggs. \n" << endl;
	
	// Yellow
	HoughCircles(yellow_hue_image, circles, CV_HOUGH_GRADIENT, 1, yellow_hue_image.rows/11, 10, 20, 0, 100);

	for(size_t i = 0; i < circles.size(); ++i) {
		Point center(round(circles[i][0]), round(circles[i][1]));
		int radius = round(circles[i][2]);

	           circle(orig_image, center, radius, Scalar(0, 255, 255), 5);
	}
	cout << "There are " << circles.size() << " yellow chocolate eggs" << endl;

	outputFile << "There are "  << circles.size() << " yellow chocolate eggs. \n" << endl;

	// Blue
	HoughCircles(blue_hue_image, circles, CV_HOUGH_GRADIENT, 1, blue_hue_image.rows/11, 10, 20, 0, 100);

	for(size_t i = 0; i < circles.size(); ++i) {
		Point center(round(circles[i][0]), round(circles[i][1]));
		int radius = round(circles[i][2]);

	           circle(orig_image, center, radius, Scalar(255, 0, 0), 5);
	}
	cout << "There are " << circles.size() << " blue chocolate eggs" << endl;

	outputFile << "There are "  << circles.size() << " blue chocolate eggs. \n" << endl;	

	outputFile.close();

	namedWindow("chocolate_eggs_marked", WINDOW_AUTOSIZE);
	imshow("chocolate_eggs_marked", orig_image);

  /// Save as JPG image file in the current directory
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    compression_params.push_back(95);

  imwrite("chocolate_eggs_marked.jpg", orig_image, compression_params );
}

void thresh_callback(int, void* )
{
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using Threshold
  threshold( src2, threshold_output, 100, 255, THRESH_BINARY );
  /// Find contours
  findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Find the rotated rectangles and ellipses for each contour
  vector<RotatedRect> minRect( contours.size() );
  vector<RotatedRect> minEllipse( contours.size() );
 

  for( int i = 0; i < contours.size(); i++ )
     { minRect[i] = minAreaRect( Mat(contours[i]) );
     //  cout << minRect[i].points() "\n"<< endl;
       if( contours[i].size() > 5 )
         { minEllipse[i] = fitEllipse( Mat(contours[i]) ); }
     }

  /// Draw contours + rotated rects + ellipses
  Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
	int width;
	int hundred_pixels=(45000/450);
	int good_eggs = 0;
	int bad_eggs = 0;
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       // contour
       drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       // ellipse
       ellipse( drawing, minEllipse[i], color, 2, 8 );
       // rotated rectangle
       Point2f rect_points[4];
       minRect[i].points( rect_points );
       for( int j = 0; j < 4; j++ )
	{
          line( drawing, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
//		cout << rect_points[j].x << "," << rect_points[j].y << endl;
	
		width = sqrt(pow(rect_points[(j+1)%4].x - rect_points[j].x, 2) + pow(rect_points[(j+1)%4].y - rect_points[j].y, 2));
	//	cout << width << endl;
//		height =  sqrt(pow(rect_points[(j+2)%4].x - rect_points[(j+1)%4].x, 2) + pow(rect_points[(j+2)%4].y - rect_points[(j+1)%4].y, 2));
			
		if (width < hundred_pixels)			
		{
			bad_eggs++;
		}
		else
			 {
				good_eggs++;
			 }
	}
     } 

		cout << "There are "<< good_eggs <<" good eggs and " << bad_eggs << " bad_eggs" << endl; 

  char const* source_window = "Sorting objects by size";
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  imshow( source_window, drawing);
}
