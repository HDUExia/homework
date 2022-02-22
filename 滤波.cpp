#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;


void salt(Mat &srcimage,int number){		//编写噪声函数
    int width = srcimage.cols;
    int height = srcimage.rows;
    for(int i = 0 ;i<number;i++){
        int x = rand()%height;
        int y = rand()%width;
        srcimage.at<Vec3b>(x,y)[0] = rand()%255;
        srcimage.at<Vec3b>(x,y)[1] = rand()%255;
        srcimage.at<Vec3b>(x,y)[2] = rand()%255;
    }
    return ;
} 

int main(){
    VideoCapture capture(0);	//调用摄像头
    if(!capture.isOpened()){	//判断是否打开
        return 0 ;
    }
    Mat srcimage;	//原图之后转化为噪声图
    Mat dstimage;	//均值滤波的效果图
    Mat mediaimage;   //中值滤波的效果图
    Mat gaussimage;	//高斯滤波效果图
    while(1){
        capture>>srcimage;
        salt(srcimage,5000);//将srcimage增加噪声
        blur(srcimage,dstimage,Size(3,3));//均值
        GaussianBlur(srcimage,gaussimage,Size(3,3),1,1);//高斯
        medianBlur(srcimage,mediaimage,9);//中值
        imshow("srcimage",srcimage);
        imshow("saltimage",srcimage);
        imshow("blur",dstimage);
        imshow("gaussimage",gaussimage);
        imshow("medianBlur",mediaimage);
        waitKey(30);
        

    }
}
