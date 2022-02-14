#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
    Mat srcimage = imread("senbai.jpg");//载入图片
    pyrDown(srcimage,srcimage); //缩小图片尺寸
    Mat deepMat = srcimage.clone();//深拷贝
    Mat shallowMat = srcimage;    //浅拷贝
    uchar *prow = 0;		//定义像素指针
    for(int i = 0;i<srcimage.rows;i++){	//如T2的操作
        prow = srcimage.ptr<uchar>(i);
        for(int j = 0;j<srcimage.cols;j++){
            int avg = prow[j*3]+prow[j*3+1]+prow[j*3+2];
            avg /=3;
            int threshold = 100;
            if(avg>threshold)
                avg = 255;
            else avg = 0;
            prow[j*3] = prow[j*3+1] = prow[j*3+2] = avg;
        }
    }
    imshow("deepMat",deepMat);
    imshow("shallowMat",shallowMat);
    imshow("srcimage",srcimage);
    waitKey(0);
}
