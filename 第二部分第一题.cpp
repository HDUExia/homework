#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int hmax = 180;
int hmin_Max = 360;
int hmin = 0;
int hmax_Max = 180;

int smax = 255;
int smax_Max = 255;
int smin = 0;
int smin_Max = 255;

int vmax = 255;
int vmax_Max = 255;
int vmin = 0;
int vmin_Max = 255;//建立三通道的最大最小值

Mat srcimage;//原图像
Mat hsvimage;//hsv图像
Mat dstimage;//效果图

std::string dstname  = "dstimage";
//窗口名
void CallBack(int ,void*){//建立回调函数来建立滑动条
        dstimage = Mat::zeros(srcimage.size(),srcimage.type());
        Mat mask;//掩膜
        inRange(srcimage,Scalar(hmin,smin,vmin),Scalar(hmax,smax,vmax),mask);
        //将mask变为srcimage的hsv通道图像
	imshow("mask",mask);
        for(int i =0;i<srcimage.rows;i++){
            for(int j =0;j<srcimage.cols;j++){
                if(mask.at<uchar>(i,j) == 255){
                    dstimage.at<Vec3b>(i,j) = srcimage.at<Vec3b>(i,j);
                }
            }
        }//用mask对效果图遮盖
    imshow(dstname,dstimage);
}
int main(){ 
    srcimage = imread("clip.jpg");
    if(srcimage.empty()){
    	std::cout<<"can not imread picture";//判断图像读入情况
    }
    imshow("srcimage",srcimage);
    hsvimage = srcimage.clone()；
    cvtColor(srcimage,hsvimage,COLOR_BGR2HSV);//将srcimage转为hsv通道
    imshow("hsvimage",hsvimage);
    namedWindow(dstname);
    dstimage;
    createTrackbar("hmin",dstname,&hmin,hmin_Max,CallBack);
    createTrackbar("smin",dstname,&smin,smin_Max,CallBack);
    createTrackbar("vmin",dstname,&vmin,vmin_Max,CallBack);
    createTrackbar("hmax",dstname,&hmax,hmin_Max,CallBack);
    createTrackbar("smax",dstname,&smax,smin_Max,CallBack);
    createTrackbar("vmax",dstname,&vmax,vmin_Max,CallBack);//建立滑动条

    waitKey(0);
    return 0;
}
