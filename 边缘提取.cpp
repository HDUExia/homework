#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
  VideoCapture capture(0); 		//调用摄像头
  if(!capture.isOpened()){	//判断是否成功调用
      return 1;
  }
  while(1){
      Mat frame;
      capture>>frame;
      if(frame.empty()){
          break;		
      }
      Mat gray,blurimage,cannyimage;
      cvtColor(frame,gray,COLOR_RGB2GRAY);//将每一帧转为灰度图
      blur(gray,blurimage,Size(3,3));		//对灰度图进行滤波
      Canny(blurimage,cannyimage,1,3);	//检测边缘
      imshow("canny",cannyimage);
      waitKey(30);
  }

  waitKey(0);
}
