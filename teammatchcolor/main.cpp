//#include<opencv2/opencv.hpp>
//#include<iostream>
//#include<opencv2/imgproc/imgproc.hpp>
//#include<opencv2/highgui/highgui.hpp>
//using namespace std;
//using namespace cv;


//int main(){
//    vector<vector<Point>> contours;
//    vector<Vec4i> hireachy;
//    Mat srcImage,grayImage,mask,dstImage1,dstImage2,dstImage3;
//    Rect roi1,roi2;
//    VideoCapture capture;
//    capture.open(2);
//    float height,width;
//    while(capture.read(srcImage)){
//        cvtColor(srcImage,grayImage,COLOR_BGR2GRAY);
//        mask=Mat::zeros(srcImage.size(),srcImage.type());
//        threshold(grayImage,dstImage1,130,255,THRESH_BINARY);
//        findContours(dstImage1,contours,hireachy,RETR_CCOMP,CHAIN_APPROX_SIMPLE);
//        for(auto i = 0;i < contours.size();i++){
//            roi1 = boundingRect(contours[i]);
//            width = MIN(roi1.height,roi1.width);
//            height = MAX(roi1.height,roi1.width);
//            if(width/height > 0.9 && roi1.area() > 50){
//                rectangle(srcImage,roi1,Scalar(0,0,255),2);
//                for(auto i=0; i < srcImage.cols;i++){
//                    for(auto j = 0;j < srcImage.rows;j++){
//                        if(i > roi1.x && i < roi1.br().x &&j > roi1.y && j < roi1.br().y){
//                                                mask.at<Vec3b>(i,j)[0] = srcImage.at<Vec3b>(i,j)[0];
//                                                mask.at<Vec3b>(i,j)[1] = srcImage.at<Vec3b>(i,j)[1];
//                                                mask.at<Vec3b>(i,j)[2] = srcImage.at<Vec3b>(i,j)[2];
//                                              }
//                    }
//                }
//            }
//        }
//        imshow("!",srcImage);
//        imshow("2",mask);
//        waitKey(1);
//    }
//    waitKey();
//    return 0;
//}
#include<opencv2/opencv.hpp>
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<iostream>
#include <time.h>

using namespace cv;
using namespace std;

// 声明函数
void move_lamp(int lamp_m_h, int lamp_m_w, int bg_m_h, int bg_m_w, Mat& mask, Mat& lamp);
void move(int& lamp_m_h, int& lamp_m_w, int& lamp_m_h_unit, int& lamp_m_w_unit, int& bg_m_h, int& bg_m_w, int& bg_m_h_unit, int& bg_m_w_unit);
Mat make_mask(Mat lamp);
int randNum(int min_val, int max_val);
void run();

// ---------- 自行修改 --------------------------------
//int bg_h = 1440, bg_w = 900;        //bg图片大小
//int lamp_h = 950, lamp_w = 450;     //lamp图片大小（调整
int bg_h = 720, bg_w = 450;        //bg图片大小
int lamp_h = 475, lamp_w = 225;     //lamp图片大小（调整）
// ---------- 我发现这部分代码↑的存在意义不大 ---------

//  载入图片 "路径"  ------ 自行修改 --------------
String BG = "/home/ma/teammatchcolor/dist/BG.png";
String GREEN_filename = "/home/ma/teammatchcolor/dist/GREEN_cut.png";
String GREEN_yellow_on_filename = "/home/ma/teammatchcolor/dist/GREEN(yellow-on)_cut.png";
String RED_filename = "/home/ma/teammatchcolor/dist/RED_cut.png";
String RED_yellow_on_filename = "/home/ma/teammatchcolor/dist/RED(yellow-on)_cut.png";

// BG图片全局
Mat BG_image;

int main()
{
    cv::namedWindow("output", 0);
//    cv::setWindowProperty("output", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
    run();
}

void run()
{

    // -------------------- 先把图片全部加载完 ----------------------------
    BG_image = imread(BG);
    if(BG_image.empty())
    {
        cout <<"1" <<endl;
        return ;
    }
    resize(BG_image, BG_image, Size(BG_image.cols / 3, BG_image.rows / 3));

    Mat lamp_G = imread(GREEN_filename);
    resize(lamp_G, lamp_G, Size(lamp_G.cols / 2.5, lamp_G.rows / 2.5));
    Mat mask_G = make_mask(lamp_G);

    Mat lamp_G_y = imread(GREEN_yellow_on_filename);
    resize(lamp_G_y, lamp_G_y, Size(lamp_G_y.cols / 2.5, lamp_G_y.rows / 2.5));
    Mat mask_G_y = make_mask(lamp_G_y);

    Mat lamp_R = imread(RED_filename);
    resize(lamp_R, lamp_R, Size(lamp_R.cols / 2.5, lamp_R.rows / 2.5));
    Mat mask_R = make_mask(lamp_R);

    Mat lamp_R_y = imread(RED_yellow_on_filename);
    resize(lamp_R_y, lamp_R_y, Size(lamp_R_y.cols / 2.5, lamp_R_y.rows / 2.5));
    Mat mask_R_y = make_mask(lamp_R_y);
    // -------------------- 防止反复 imread 卡顿 ---------------------------


    // -----------------------后续修改建议使用结构体--------------------------
    int lamp_m_h = 100, lamp_m_w = 100;         //lamp_ROI移动起始点
    int lamp_m_h_unit = 2, lamp_m_w_unit = 2;   //lamp移动单位

    int bg_m_h = 65, bg_m_w = 65;                 //BG_ROI移动起始点
    int bg_m_h_unit = -3, bg_m_w_unit = -3;       //BG移动单位
    // -----------------------后续修改建议使用结构体--------------------------

    //待机画面
    move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_R, lamp_R);
    //waitKey(0);
    for (int i = 0; i < 100; i++)
    {
        move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_R, lamp_R);
        move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);
    }
    for (int j = 0; j < 2; j++)
    {
        int l = 0;
        while (l < 5)
        {
            move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_R_y, lamp_R_y);
            move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);
            l++;
        }
        while (l < 10)
        {
            move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_R, lamp_R);
            move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);
            l++;
        }
    }


    for (;;)   //capture.read(frame)
    {
        int latency_time;
        int flag = 0;
        //发送切换红绿灯信号
        //test_send("G");
        latency_time = randNum(46, 115);              //获得范围内的随机数
        for (int i = 0; i < latency_time; i++)        //60帧下, 循环60次大概需要 1.31秒         =>         换算下来即为 45.8015次 循环的时间 花费1秒
        {
            move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_G, lamp_G);
            move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);

            //达到某个时间后，读取传入的判断信息
            if (i > 45 && flag == 0)
            {
                //test_read();
                //flag++;
            }
        }
        flag = 0;       //重置flag

        for (int j = 0; j < 2; j++)
        {
            int l = 0;
            while (l < 5)
            {
                move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_G_y, lamp_G_y);
                move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);
                l++;
            }
            while (l < 10)
            {
                move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_G, lamp_G);
                move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);
                l++;
            }
        }

        //发送切换红绿灯信号
        //test_send("R");
        latency_time = randNum(46, 115);            //获得范围内的随机数
        for (int i = 0; i < latency_time; i++)
        {
            move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_R, lamp_R);
            move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);

            //达到某个时间后，读取传入的判断信息
            if (i > 35 && flag == 0)
            {
                //test_read();
                //flag++;
            }
        }
        for (int j = 0; j < 2; j++)
        {
            int l = 0;
            while (l < 5)
            {
                move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_R_y, lamp_R_y);
                move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);
                l++;
            }
            while (l < 10)
            {
                move_lamp(lamp_m_h, lamp_m_w, bg_m_h, bg_m_w, mask_R, lamp_R);
                move(lamp_m_h, lamp_m_w, lamp_m_h_unit, lamp_m_w_unit, bg_m_h, bg_m_w, bg_m_h_unit, bg_m_w_unit);
                l++;
            }
        }
    }
}

// imread 处理太慢了,会导致帧数低 (以处理)
// @brief: 显示BG 和 lamp 的动图效果
void move_lamp(int lamp_m_h, int lamp_m_w, int bg_m_h, int bg_m_w, Mat& mask, Mat& lamp)
{
    int64 time0 = getTickCount();
    //(不能用)浅拷贝, 当图像之间进行赋值时，图像数据并未发生复制，两个对象指向同一块内存, 改变图像2会影响图像 1
    //Mat image_2 = image;

    //深拷贝, 当图像之间进行赋值时，图像数据发生复制，两个对象指向不同的内存, 改变图像2不会影响图像 1
    //img.copyTo(image);
    Mat BG_ROI = BG_image(Rect(bg_m_h, bg_m_w, 2880 / 3 - 80 - 47, 1800 / 3 - 80));
    static Mat BG_image_2(cv::Size(BG_ROI.size()), CV_8UC3);//= BG_ROI.clone();
    BG_ROI.copyTo(BG_image_2);

    static Mat imROI;
    imROI = BG_image_2(Rect(lamp_m_h, lamp_m_w, lamp.cols, lamp.rows));
    //image.copyTo(imageROI，mask), 作用是把mask和image重叠以后把mask中像素值为0（black）的点对应的image中的点变为透明，而保留其他点。
    lamp.copyTo(imROI, mask);
    imshow("output", BG_image_2);

    waitKey(1);
    //帧数相关
    for (int flag = 0; flag == 0; )
    {
        if (getTickFrequency() / (getTickCount() - time0) <= 60)
        {
            flag = 1;
        }
    }
    cout << "当前帧率：" << getTickFrequency() / (getTickCount() - time0) << endl;
}

// -------------------- 限制移动范围，自行修改 -------------------------------
// @brief: ROI 的 h,w 数值更新, 使得BG图和lamp图能产生动图效果
void move(int& lamp_m_h, int& lamp_m_w, int& lamp_m_h_unit, int& lamp_m_w_unit, int& bg_m_h, int& bg_m_w, int& bg_m_h_unit, int& bg_m_w_unit)
{
    //lamp_ROI点 移动区域
    lamp_m_h += lamp_m_h_unit;
    lamp_m_w += lamp_m_w_unit;

    //高度达到上下限则反弹
    if (lamp_m_h >= bg_h - lamp_h - 120 || lamp_m_h <= 30)
    {
        lamp_m_h_unit = -lamp_m_h_unit;
        lamp_m_h += 2 * lamp_m_h_unit;
    }
    //宽度达到上下限反弹
    if (lamp_m_w >= bg_w - lamp_w - 50 || lamp_m_w <= 30)
    {
        lamp_m_w_unit = -lamp_m_w_unit;
        lamp_m_w += 2 * lamp_m_w_unit;
    }


    //BG_ROI 移动区域
    bg_m_h += bg_m_h_unit;
    bg_m_w += bg_m_w_unit;

    if (bg_m_h >= 75 || bg_m_h <= 2)
    {
        bg_m_h_unit = -bg_m_h_unit;
        bg_m_h += 2 * bg_m_h_unit;
    }
    if (bg_m_w >= 75 || bg_m_w <= 2)
    {
        bg_m_w_unit = -bg_m_w_unit;
        bg_m_w += 2 * bg_m_w_unit;
    }
}


//@brief:制作传入 lamp 图片的掩膜
//@param:传入的 lamp 图片
//@return:lamp 图掩膜
Mat make_mask(Mat lamp)
{
    Mat grayPng;
    cvtColor(lamp, grayPng, COLOR_BGR2GRAY);
    threshold(grayPng, grayPng, 10, 255, THRESH_BINARY);
    //掩模反色
    //Mat mask = 255 - grayPng;
    Mat mask = grayPng;
    //imshow("mask", mask);

    return mask;
}


//@brief:产生[min_val,max_val]范围内的随机数
//@param:min_val:最小值
//@param:max_val:最大值
//@return:生成的随机数
int randNum(int min_val, int max_val)
{
    //判断前检查 min_val 和 max_val的值大小对比
    if (min_val > max_val)
    {
        cout << "不符合要求，min_val必须小等于max_val的值。" << endl;
        return 0;
    }
    //
    int num_val = rand() % (max_val - min_val + 1) + min_val;
    return num_val;
}


