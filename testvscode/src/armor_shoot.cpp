#include "armor_shoot.hpp"

bool armor_shoot::shooting(){
    srand((unsigned)time(NULL));
    int number_b = rand()%20;
    if (number_b <= 10)
    {
       return true; 
    }else{
       return false;
    }
    
}
int armor_shoot::exchange_bullet(int frequency){
    all_money = frequency * 75;
    bullet_number += 5;
    return all_money;
}
void armor_shoot::run(){
    int frequency = 1;
    int flag = 0;
    while(volume_outpost > 0){
    if(bullet_number == 0){
    exchange_bullet(frequency);
    frequency++;
    }
    else if(shooting()){
            volume_outpost -= 200;
            bullet_number-- ;
                    flag++;
            if(volume_outpost <= 0){
                break;
            }
        }else{
            bullet_number--;
                    flag++;
        }
    }
    cout << "使用子弹颗数" << flag << endl;
    cout << "总消耗金币数" << all_money << endl;

}