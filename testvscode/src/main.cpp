// #include<iostream>
// #include<thread>
// using namespace std;

// #include <opencv2/opencv.hpp>
// using namespace cv;

// void Receiver(void)
// {
// 	VideoCapture cap("udpsrc port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG,framerate=30/1 ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink", 
//             CAP_GSTREAMER);
//     while (true) {
//         Mat frame;
//         cap.read(frame);
//         imshow("receiver", frame);
//         if (waitKey(1) == 27) {
//             break;
//         }
//     }
// }

// void Sender(void)
// {
//     VideoCapture cap(0);
// 	VideoWriter writer(
// 		"appsrc ! videoconvert ! video/x-raw,format=YUY2,width=1280,height=720,framerate=30/1 ! jpegenc ! rtpjpegpay ! udpsink host=127.0.0.1 port=5000", 
//         0,		// fourcc 
// 		30,		// fps
// 		Size(1280, 720), 
// 		true);	// isColor
// 	// VideoWriter writer(
// 	// 	"appsrc ! videoconvert ! video/x-raw,format=YUY2,width=1280,height=720,framerate=30/1 ! jpegenc ! rtpjpegpay ! udpsink host=127.0.0.1 port=5000", 
//     //     0,		// fourcc 
// 	// 	30,		// fps
// 	// 	Size(1280, 720), 
// 	// 	true);	// isColor
//     while (true) {
//         Mat frame;
//         cap.read(frame);
//         writer.write(frame);
//     }
// }

// int main()
// {
//     // thread th2(Sender);
//     // thread th3(Receiver);
//     // th2.join();
//     // th3.join();
//     Receiver();
//     return 0;
// }
// #include<stdio.h>
// using namespace std;
// int main(){
//     float x,y;
//     scanf("%f",&x);
//     if(x < 1){
//         y = x;
//     }else if(1 <= x && x < 10){
//     y = x * 2 - 1;
//     }else{
//         y = 3 * x - 11;
//     }
//     printf("%5.2f", y);
//     return 0;
// }
// #include "armor_shoot.hpp"

// int main(){
//     armor_shoot armor_shoot_;
//     armor_shoot_.run();
// }
#include<iostream>
using namespace std;
#define Y 5//矩阵宽高-1
#define X 5

class Point; 
class Image                                                      //图片类
{

public:
    void ROI(Point& upper_right, Point& lower_left);

    void ROI(Point& Center, int height, int width);
    

	
private:
    int A[Y+1][X+1] = {
        {1, 11, 20, 27, 31, 35},
        {12, 2, 10, 19, 26, 32},
        {21, 13, 3,  9, 18, 25},
        {28, 22, 14, 4,  8, 17},
        {33, 29, 23, 15, 5,  7},
        {36, 34, 30, 24, 16, 6}
    };
};

class Point                                                       //点类
{
public:
    friend void Image::ROI(Point& Center, int height, int width);
    friend void Image::ROI(Point& upper_right, Point& lower_left);
    Point(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
private:
    int m_x;
    int m_y;
};
void Image::ROI(Point& upper_right, Point& lower_left)             //两点函数
{
    if (upper_right.m_x < 0) upper_right.m_x = 0;
    if (upper_right.m_y < 0) upper_right.m_y = 0;
    if (upper_right.m_x > X) upper_right.m_x = X;
    if (upper_right.m_y > Y) upper_right.m_y = Y;
    if (lower_left.m_x < 0) lower_left.m_x = 0;
    if (lower_left.m_y < 0) lower_left.m_y = 0;
    if (lower_left.m_x > X) lower_left.m_x = X;
    if (lower_left.m_y > Y) lower_left.m_y = Y;
    
    for (int i =upper_right.m_y ; i <=lower_left.m_y ; i++)
    {
        
        for (int o =upper_right.m_x; o <= lower_left.m_x; o++)
        {
            
            cout << "  " <<A[i][o];
        }
        // cout << endl;
    }
}
void Image::ROI(Point& Center, int width,int height )               //中心点到边函数
{
    int x, y, a, b;
    x = Center.m_y - height;
    a = Center.m_y + height;
    y = Center.m_x - width;
    b = Center.m_x + width;
    if (x < 0) x = 0;
    if (a > X) a = X;
    if (y < 0) y = 0;
    if (b > Y )b = Y;
    for (int i = x; i <=a; i++)
    {
        
        for (int o =y; o <= b; o++)
        {
            if (o < 0) o = 0;
            else if (o > X) o = X;
            cout << "  " << A[i][o];
        }
        cout << endl;
    }
}

//函数一
void test01()
{
    int x,y;
    cout << "请输入右上角的坐标:";
    cin >> x;
    cin >> y;
    Point upper_right(x, y);
    cout << "请输入左下角的坐标：";
    cin >> x;
    cin >> y;
    Point lower_left(x, y);
    Image p1;
    p1.ROI(upper_right, lower_left);
    
}

//函数二
void test02()
{
    int x, y;
    cout << "请输入中心点的坐标:";
    cin >> x;
    cin >> y;
    Point Center(x, y);
    cout << "请输入中心点距离宽高边的距离：(先宽后高）";
    cin >> x;
    cin >> y;
    Image p1;
    p1.ROI(Center,x,y);
}

int main(void)
{
    test01();
    // test02();

    return 0;
}
