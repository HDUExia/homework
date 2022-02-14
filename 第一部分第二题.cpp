#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
    Mat srcimage = imread("senbai.jpg");//读入图像
    uchar *prow;
    for(int i = 0;i<srcimage.rows;i++){
        prow = srcimage.ptr<uchar>(i);//设置指针指向每一行的首地址
        for(int j = 0;j<srcimage.cols;j++){
            if(srcimage.channels() == 1)//如果只有一个通道的图像，不做操作
                std::cout<<"plz imread a 3 channnels picture"<<std::endl;
            else if(srcimage.channels() == 3){
                int average = prow[j*3]+prow[j*3+1]+prow[j*3+2];
                average /=3;		//给average赋值
                uchar threshold = 100;
                if(average > threshold){//如果average>threshold则avg变为255，否则变为0
                    average = 255;
                }
                else average = 0;

                prow[j*3] = prow[j*3+1] = prow[j*3+2] = average;//给三个通道赋上avg的值

            }


        }
    }
    imshow("part1 #2",srcimage);
    waitKey(0);
}
