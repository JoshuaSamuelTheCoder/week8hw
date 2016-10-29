#include <opencv2/opencv.hpp> // how we import opencv2
#include <iostream> // strings
#include <string>

using namespace cv;


int main(int argc, char *argv[])
{

  std::string fileLocation = "320px-Flag_of_Japansvg.png";

  //std: string fileLocation = argv[1];

  Mat img = imread(fileLocation);

  cv::Mat img_HSV;
  cv::cvtColor(img,img_HSV,CV_BGR2HSV); //converting from rgb to hsv


  std::vector<cv::Mat> channels;
  vector<vector <cv::Point> > contours;

  cv::Mat hueOrig = channels.at(0).clone();
  cv::Mat threshLower,threshHigher,result;

  cv::threshold(hueOrig,threshLower,20,255, CV_THRESH_BINARY);
  cv::threshold(hueOrig,threshHigher,80,255,CV_THRESH_BINARY_INV);
  result = threshLower & threshHigher;
  //std::vector<cv::Mat> channels;
  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
  {
    return -1;
  }

   Mat edges;
   namedWindow("edges",1);
   for(int i = 0; i< contours.size(); i++)
   {
       Mat frame;
       cap >> frame; // get a new frame from camera
       cvtColor(frame, edges, COLOR_BGR2GRAY);
       GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
       Canny(edges, edges, 0, 30, 3);
       imshow("edges", edges);
       imshow("Thesholded",result);
       if(waitKey(30) >= 0)
       {
          break;
       }

   }
   // the camera will be deinitialized automatically in VideoCapture destructor
   return 0;

//cv:: imshow("Thresholded",result);
//cv::imshow("Hue",channels.at(0));
//cv::imshow("Saturation",channels.at(1));
//cv::imshow("Value",channels.at(2));
//imshow("Here is an amazing picture", img);
}
