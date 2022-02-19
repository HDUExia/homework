#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat srcimage;		//原图像
Mat dstimage;		//效果图
int _yuzhi_;		//阈值
int min_max = 255;	//滑动条变动幅度
double Max = 255;	//阈值最大值
void callback(int,void*){
    threshold(  //用threshold函数可以将图片二值化，但不能改变通道
		srcimage,//输入函数
		dstimage,//输出函数
		_yuzhi_,//变动的阈值
		Max,//最大值
		1);
	//0: THRESH_BINARY  当前点值大于阈值时，取Maxval,也就是第四个参数，下面再不说明，否则设置为0

	//1: THRESH_BINARY_INV 当前点值大于阈值时，设置为0，否则设置为Maxval

	//2: THRESH_TRUNC 当前点值大于阈值时，设置为阈值，否则不改变

	//3: THRESH_TOZERO 当前点值大于阈值时，不改变，否则设置为0

	//4: THRESH_TOZERO_INV  当前点值大于阈值时，设置为0，否则不改变
    Mat element = getStructuringElement(MORPH_ELLIPSE,Size(3,3));
    //创建内核
    morphologyEx(dstimage,dstimage,MORPH_DILATE,element);
    //将第三个参数改为MORPH_OPEN,MORPH_COLSE,MORPH_ERODE<MORPH_OTUS可分别实现开运算，闭预算，腐蚀和大津法，此处为膨胀
    Mat labels,centroids,stats;
    int nncomp = connectedComponentsWithStats(//此函数可划分图像联通域
		    dstimage,//输入图像
		    labels,//联通域的序号，0为最大的联通域，背景
		    stats,//联通域的数据
		    centroids//联通域的中心点
		    );
   
    std::vector<Vec3b> colors(nncomp);//建立容器存放颜色
    colors[0] = Vec3b(0,0,0);//背景为黑色
    for(int i = 1;i<nncomp;i++){
        colors[i] = Vec3b(rand()%256,rand()%256,rand()%256);
        if(stats.at<int>(i,CC_STAT_AREA)<=100){
		//过滤噪声：如果面积小于100，则设置为背景色
            colors[i] = Vec3b(0,0,0);
        }
    }
    Mat newimage = Mat::zeros(dstimage.size(),CV_8UC3);
    //建立一个三通道的图片
    for(int i = 0;i<dstimage.rows;i++){
        for(int j = 0 ; j<dstimage.cols;j++){
            int label =labels.at<int>(i,j);
	    //labels.at操作访问每一个像素点所属的联通域序号
            newimage.at<Vec3b>(i,j) = colors[label];//用颜色图画联通域

        }
    }
    for(int i = 1;i<nncomp;i++){
        int x = centroids.at<double>(i,0);
        int y = centroids.at<double>(i,1);//读取联通域的横纵坐标
        int width = stats.at<int>(i,2);
        int height = stats.at<int>(i,3);//联通域的最大宽度和高度
	rectangle(//画矩形
			newimage,
			Point(x-width/2,y-height/2),
			Point(x+width/2,y+height/2),
			Scalar(114,51,4),2); 
    }


    imshow("dstimage",newimage);
    std::cout<<":the number is" <<nncomp-1<<":";//输出clip个数，这个不太会处理，导致会一直在终端输出
}
int main(){ 
    srcimage = imread("clip.jpg",0);//读入图片
    if(srcimage.empty()){
        std::cout<<"can not imread picture";
        return 0;
    }
    namedWindow("dstimage");
    imshow("srcimage",srcimage);
    cvtColor(srcimage,srcimage,COLOR_BGR2GRAY);//转为单通道的会度图
    createTrackbar("threshold","dstimage",&_yuzhi_,min_max,callback);
    //创建调整阈值的滑动条
    waitKey(0);
    return 0;
}
