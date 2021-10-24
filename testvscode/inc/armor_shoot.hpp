#include<iostream>

using namespace std;
class armor_shoot
{
private:
    int volume_outpost = 1500;
    int bullet_number = 0;
    int all_money = 0;
public:
    bool shooting();                       //射击函数 随机命中
    int  exchange_bullet(int frequency);   //兑换子弹 计算已经花费的钱 传入兑换次数
    void run();                            //运行函数

};

