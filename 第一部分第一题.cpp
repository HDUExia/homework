#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main(){
    Mat srcimage = imread("senbai.jpg");                //imread picture
    int width = srcimage.cols;
    int height = srcimage.rows;
    int channels = srcimage.channels();
    uchar *p_rows = 0;                              //uchar a pointer,this pointer will point every pixel of picture
    imshow("orginal image",srcimage);
    for(int i = 0;i<height;i++){
        p_rows = srcimage.ptr<uchar>(i);                //the pointer points the first address of every rows
        for(int j = 0;j<width;j++){         
            if(channels == 1){                          //if channels is 1,do nothing
                p_rows[j] = p_rows[j];
            }
            if(channels == 3){                          //if channals is 3,sum up rgb channels and divide 3
                int sum = p_rows[j*3]+p_rows[j*3+1]+p_rows[j*3+2];
                p_rows[j*3] = p_rows[j*3+1] = p_rows[j*3+2] = sum/3;
            }
        }
    }
    imshow("the output of part 1 1st question",srcimage);
    waitKey(0);
    return 0;

}