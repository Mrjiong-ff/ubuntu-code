#include"color.h"
#include"serial.h"
#include"time.h"
void colorknow::deal(Mat srcImage){
//    cvtColor(srcImage,grayImage,COLOR_BGR2GRAY);
//    equalizeHist(grayImage,grayImage);
    split(srcImage,_split);
    subtract(_split[1],_split[2],dstImage1);
    threshold(dstImage1,dstImage1,140,200,THRESH_BINARY);
    findContours(dstImage1,contours,/*RETR_CCOMP*/CHAIN_APPROX_SIMPLE,CHAIN_APPROX_SIMPLE);
}
int colorknow::Judgment(Mat mask){
    int lightg;
    unsigned char buff='a';
    char buffer[512];
    cvtColor(mask,mask,COLOR_BGR2HSV);
    for(auto i = 0;i < mask.rows;i++){
        Vec3b* q = mask.ptr<Vec3b>(i);
        for(auto j = 0 ;j < mask.cols;j++){
            if(q[j][0] > 35 && q[j][0] < 77 && q[j][1]>46 && q[j][2]>43){
                green_number++;
                cout<<"G--"<<green_number<<endl;
//                sleep(1);
            }
            if(green_number>60){
               write(lightg,&buff,1);
            }else{
                continue;
            }
        }
    }
    green_number = 0;
    return lightg;
}
int colorknow::color()
{
    int result;
    float height,width;
    VideoCapture capture(2);
    while(capture.read(srcImage)){
            double t=(double)getTickCount();
    //        cvtColor(srcImage,hsvImage,COLOR_BGR2HSV);
    //        inRange(hsvimage,Scalar(0,0,201),Scalar(131,255,255),midimage);
    //        findContours(srcImage,contours1,hireachy1,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
            deal(srcImage);
            mask=Mat::zeros(srcImage.size(),srcImage.type());
            for(auto i = 0;i < contours.size();i++){
                roi1 = boundingRect(contours[i]);
                height = MIN(roi1.height,roi1.width);
                width = MAX(roi1.height,roi1.width);
                if(height/width > 0.95&& roi1.area()>55 ){
                    rectangle(srcImage,roi1,Scalar(255,0,0),2);
                    for(auto i=0; i < srcImage.rows;i++){
                        Vec3b* p = srcImage.ptr<Vec3b>(i);
                        Vec3b* q = mask.ptr<Vec3b>(i);
                        for(auto j = 0;j < srcImage.cols;j++){
                            if((j > roi1.tl().x && j < roi1.br().x) && (i > roi1.tl().y && i < roi1.br().y)){
                                                    q[j][0] = p[j][0];
                                                    q[j][1] = p[j][1];
                                                    q[j][2] = p[j][2];
                                                  }
                        }
                    }
            }
                    }
            Judgment(mask);
            t=((double)getTickCount()-t)/getTickFrequency();
                   int fps=int(1.0/t);
//                   cout<<"FPS:"<<fps<<endl;
//                   imshow("2",dstImage1);
                   imshow("1",srcImage);
                   imshow("2",dstImage1);
                   imshow("a",mask);
                   waitKey(50);
        }
}

