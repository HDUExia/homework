#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
   Mat srcimage = imread("senbai.jpg"); //载入图片
   if(!srcimage.data){
       std::cout<<"can not imread picture"<<std::endl;
   }//判断是否载入成功
   pyrDown(srcimage,srcimage);
   std::vector<Mat> channels;//定义容器，装载三个通道
   split(srcimage,channels);//调用split函数，分离通道
   Mat bluechannel = channels.at(0);
   Mat greenchannel = channels.at(1);
   Mat redchannel = channels.at(2);//定义三个Mat类装载分离后的通道
   imshow("srcimage",srcimage);
   imshow("bluechannels",bluechannel);
   imshow("greenchannels",greenchannel);
   imshow("redchannels",redchannel);
   waitKey(0);
}
