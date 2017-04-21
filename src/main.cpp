#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <zbar.h>
#include <iostream>
 using namespace cv;
 using namespace std;
 using namespace zbar;
 int main()
 {
   VideoCapture cap(0); 
   if (!cap.isOpened()) 
   {
     cout << "Cannot open the video cam" << endl;
     return -1;
   }
   ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
   double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); 
   double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); 
   cout << "Frame size : " << dWidth << " x " << dHeight << endl;
   namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); 
   while (1)
   {
     Mat frame;
     bool bSuccess = cap.read(frame); 
      if (!bSuccess) 
     {
        cout << "Cannot read a frame from video stream" << endl;
        break;
     }
     Mat grey;
     cvtColor(frame,grey,CV_BGR2GRAY);
     int width = frame.cols;
     int height = frame.rows;
     uchar *raw = (uchar *)grey.data;
 
     Image image(width, height, "Y800", raw, width * height);
 
     int n = scanner.scan(image);
   
     for(Image::SymbolIterator symbol = image.symbol_begin();
     symbol != image.symbol_end();
     ++symbol) {
         vector<Point> vp;
    
     cout << "decoded " << symbol->get_type_name() << " symbol \"" << symbol->get_data() << '"' <<" "<< endl;
       int n = symbol->get_location_size();
       for(int i=0;i<n;i++){
         vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
       }
       RotatedRect r = minAreaRect(vp);
       Point2f pts[4];
       r.points(pts);
       for(int i=0;i<4;i++){
         line(frame,pts[i],pts[(i+1)%4],Scalar(255,0,0),3);
       }
       cout<<"upper left point x, y, width, height: "<<pts[0] << ","<<pts[1]<<","<<pts[2] << ","<<pts[3]<< endl;
       cout<<"Angle: "<<r.angle<<endl;
     }
     imshow("MyVideo", frame); 
     if (waitKey(30) == 27) 
     {
       cout << "esc key is pressed by user" << endl;
       break;
     }
   }
   return 0;
 }


