
#include <iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace cv;
using namespace std;
void Gammacorrection(Mat &srcimage,Mat &desimage,float fGamma){
    CV_Assert(srcimage.data);//检查图片的输入
    CV_Assert(srcimage.depth() !=sizeof(uchar) );
    int lut[256];//建立数值表
    for(int i=0;i<256;i++){
        lut[i] = saturate_cast<uchar>(pow((float)i/255,fGamma)*255.0f);
    }//给数值表赋值，使其符合指数曲线，saturate_cast<uchar>防止像素溢出
    const int channels = srcimage.channels();
    desimage = srcimage.clone();
    if(channels == 1){	//通道数为1，用迭代器指向des图片来赋值
        MatIterator_<uchar> it,end;
        for(it = desimage.begin<uchar>(),end = desimage.end<uchar>();it<end;it++){
            *it = lut[(*it)];//将dst的图片进行gamma校正
        }
    }

    if(channels == 3){//通道数为3
        MatIterator_<Vec3b> it,end;
        for(it = desimage.begin<Vec3b>(),end = desimage.end<Vec3b>();it!=end;it++){
            for(int j =0;j!=3;j++){
                (*it)[j] = lut[(*it)[j]];
            }
        }
    }
}
