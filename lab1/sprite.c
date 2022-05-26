#include "sprite.h"
#include "Images.h"
#include "Nokia5110/SPI.h"
#include "include.h"
#include "Task_def.h"
static int a = 0;
static int b = 0;
static int c = 0;
unsigned int count=0,road_flag=0;
void Player_Init(){
    //Player.x = 32;
    Player.y = 47;
    Player.life = 1;
    Player.point = 0;
    Player.image = PlayerShip0;
    Player.explode[0] = BigExplosion0;
    a = 0;
    b = 0;
    c = 0;
    Player1.image = player_car;
    Player1.x = 10;
    Player1.life = 1;
}
void Player_Draw(){
    if(Player.life == 1){
        Nokia5110_PrintBMP(Player.x, Player.y, Player.image, 0);
    }else if(Player.life == 0){
        Nokia5110_PrintBMP(Player.x, Player.y, Player.explode[0], 0);
    }
}
void Bunker_Init(){
    uint8_t i = 0;
    for(i=0;i<3;i++){
        Bunker[i].x = 32*i;
        Bunker[i].y = 39;
        Bunker[i].life = 3;
    }
}
void Bunker_Draw(){
    uint8_t i = 0;
    for(i=0;i<3;i++){
        if(Bunker[i].life==3){
            Nokia5110_PrintBMP(Bunker[i].x, Bunker[i].y, Bunker0, 0);
        }else if(Bunker[i].life==2){
            Nokia5110_PrintBMP(Bunker[i].x, Bunker[i].y, Bunker1, 0);
        }else if(Bunker[i].life==1){
            Nokia5110_PrintBMP(Bunker[i].x, Bunker[i].y, Bunker2, 0);
        }
    }
}
void Enemy_Init(){
    uint8_t i = 0;
    uint8_t j = 0;
    for(j=0;j<3;j++){
        for(i=0;i<5;i++){
            Enemy[i+5*j].x = 1 + 16*i;
            Enemy[i+5*j].y = 9*(j+1);
            Enemy[i+5*j].life = 1;
            Enemy[i+5*j].image = SmallEnemy10PointA;
            Enemy[i+5*j].explode[0] = SmallExplosion0;
        }
    }
}
void Enemy_Move(){
    uint8_t i = 0;
    if(a%11==0){
        for(i=0;i<15;i++){
            if(b%2==0){
                Enemy[i].x += 3;
            }else{
                Enemy[i].x -= 3;
            }
            if(a%99==0){
                Enemy[i].y += 1;
            }
        }
        b++;
    }
    a++;
}
void Enemy_Draw(){
    uint8_t i;
    static int d[15];
    static int e[15];
    for(i=0;i<15;i++){
        if(Enemy[i].life==1){
            d[i] = 0;
            e[i] = 0;
            Nokia5110_PrintBMP(Enemy[i].x, Enemy[i].y, Enemy[i].image, 0);
        }else if(d[i]==0){
            Nokia5110_PrintBMP(Enemy[i].x, Enemy[i].y, Enemy[i].explode[0], 0);
            e[i]++;
            if(e[i]%17==0){
                d[i]++;
            }
        }
    }
}
void Player_Missile_Init(){
    Player_Missile.x = Player.x + 8;
    Player_Missile.y = Player.y - 0;
    Player_Missile.life = 0;
    Player_Missile.image = Missile0;
}
void Player_Missile_Draw(){
    if(Player_Missile.life>0){
        Nokia5110_PrintBMP(Player_Missile.x, Player_Missile.y, Player_Missile.image, 0);
    }
}
void Player_Missile_Move(){
    if(Player_Missile.life>0){
        if(Player_Missile.y==0){
            Player_Missile.y = Player.y - 7;
            Player_Missile.life = 0;
        }else{
            Player_Missile.y -= 1;
        }
    }
}
void Missile_Init(){
    uint8_t i;
    for(i=0;i<15;i++){
        Missile[i].x = Enemy[i].x + 7;
        Missile[i].y = Enemy[i].y + 8;
        Missile[i].life = 0;
        Missile[i].image = Missile0;
    }
}
void Missile_Draw(){
    uint8_t i;
    for(i=0;i<15;i++){
        if(Missile[i].life>0){
            Nokia5110_PrintBMP(Missile[i].x, Missile[i].y, Missile[i].image, 0);
        }
    }
}
void Missile_Move(){
    uint8_t i;
    static int speed = 0;
    speed++;
    if(speed%11==1){
        for(i=0;i<15;i++){
            if(Missile[i].life==1){
                if(Missile[i].y>=47){
                    Missile[i].life = 0;
                    Missile[i].y = Enemy[i].y + 8;
                }
                //                else{
                Missile[i].y += 1 ;
                //                }
            }
        }
    }
}
void Player_Point(){
    uint8_t i;
    uint8_t j;
    for(i=0;i<3;i++){
        if((Bunker[i].life==3)&&(Player_Missile.x>=Bunker[i].x)&&(Player_Missile.x<=(Bunker[i].x+17))
                &&((Player_Missile.y-4)<=Bunker[i].y)&&((Player_Missile.y-4)>=(Bunker[i].y-25))&&(Player_Missile.life == 1)){
            Player_Missile.life = 0;
            Bunker[i].life = 2;
            Player_Missile.x = Player.x + 8;
            Player_Missile.y = Player.y - 7;
        }else if((Bunker[i].life==2)&&(Player_Missile.x>=Bunker[i].x)&&(Player_Missile.x<=(Bunker[i].x+17))
                &&((Player_Missile.y-4)<=Bunker[i].y)&&((Player_Missile.y-4)>=(Bunker[i].y-25))&&(Player_Missile.life == 1)){
            Player_Missile.life = 0;
            Bunker[i].life = 1;
            Player_Missile.x = Player.x + 8;
            Player_Missile.y = Player.y - 7;
        }else if((Bunker[i].life==1)&&(Player_Missile.x>=Bunker[i].x)&&(Player_Missile.x<=(Bunker[i].x+17))
                &&((Player_Missile.y-4)<=Bunker[i].y)&&((Player_Missile.y-4)>=(Bunker[i].y-25))&&(Player_Missile.life == 1)){
            Player_Missile.life = 0;
            Bunker[i].life = 0;
            Player_Missile.x = Player.x + 8;
            Player_Missile.y = Player.y - 7;
        }
        for(j=0;j<15;j++){
            if((Enemy[j].life==1)&&(Player_Missile.x>=Enemy[j].x)&&(Player_Missile.x<=(Enemy[j].x+14))
                    &&((Player_Missile.y-4)<=Enemy[j].y)&&((Player_Missile.y-4)>=(Enemy[j].y-10))
                    &&(Player_Missile.life == 1)){
                Player_Missile.life = 0;
                Enemy[j].life = 0;
                Player.point += 1;
            }
        }
    }
}
void GameOver(){
    int i;
    int j;
    for(i=0;i<15;i++){
        if(Enemy[i].y>=46){
            Player.life = 0;
        }
        if((Missile[i].life)&&(((Missile[i].x+2)>=(Player.x+2))&&((Missile[i].x+2)<=(Player.x+17))
                &&(Missile[i].y>=(Player.y-3))&&(Missile[i].y<=Player.y))){
            Player.life = 0;
        }
        if((((Enemy[i].x>=Player.x)&&(Enemy[i].x<=(Player.x+17)))
                ||(((Enemy[i].x+15)>=Player.x)&&((Enemy[i].x+15)<=(Player.x+17))))
                &&((Enemy[i].y>=(Player.y-3))&&(Enemy[i].y<=Player.y))){
            Player.life = 0;
        }
        for(j=0;j<3;j++){
            if(((Missile[i].x+2)>=Bunker[j].x)&&((Missile[i].x+2)<=(Bunker[j].x+18))
                    &&(Missile[i].y>=(Bunker[j].y-5))&&(Missile[i].y<=Bunker[j].y)
                    &&(Bunker[j].life!=0)&&(Missile[i].life==1)){
                Bunker[j].life -= 1;
                Missile[i].life = 0;
            }
            if((((Enemy[i].x>=Bunker[j].x)&&(Enemy[i].x<=(Bunker[j].x+17)))
                    ||(((Enemy[i].x+15)>=Bunker[j].x)&&((Enemy[i].x+15)<=(Bunker[j].x+17))))
                    &&((Enemy[i].y>=(Bunker[j].y-4))&&(Enemy[i].y<=Bunker[j].y))){
                Bunker[j].life = 0 ;
            }
        }
        if((Missile[i].life)&&(Player_Missile.life)){
            if((((Missile[i].x>=Player_Missile.x)&&(Missile[i].x<=(Player_Missile.x+4)))
                    ||(((Missile[i].x+4)>=Player_Missile.x)&&((Missile[i].x+4)<=(Player_Missile.x+4))))
                    &&((Missile[i].y>=(Player_Missile.y-9))&&((Missile[i].y-4)<=Player_Missile.y))){
                Player_Missile.life = 0;
                Player_Missile.x = Player.x + 8;
                Player_Missile.y = Player.y - 7;
                Missile[i].life = 0;
                Missile[i].x = Enemy[i].x + 7;
                Missile[i].y = Enemy[i].y + 8;
            }
        }
    }
}
void AutoFire(){
    int r = rand()%14;
    static uint8_t delay = 0;
    delay++;
    if((Enemy[r].life==1)&&(delay%17==1)){
        if(Missile[r].life==0){
            Missile[r].y = Enemy[r].y;
            Missile[r].life = 1;
        }
    }
}
void RoadMove(){
    Nokia5110_ClearBuffer();
    road_flag++;
    if(road_flag > 0 && road_flag <6)
    {
        Nokia5110_PrintBMP(1, 10, road1, 0);
        Nokia5110_PrintBMP(1, 46, road1_D, 0);
        for(count=0;count<4;count++)
        {
            Nokia5110_PrintBMP(17+count*16, 10, road1, 0);
            Nokia5110_PrintBMP(17+count*16, 46, road1_D, 0);
        }

    }
    else if(road_flag > 5 && road_flag <11)
    {
        Nokia5110_PrintBMP(1, 10, road2, 0);
        Nokia5110_PrintBMP(1, 46, road2_D, 0);
        for(count=0;count<4;count++)
        {
            Nokia5110_PrintBMP(17+count*16, 10, road2, 0);
            Nokia5110_PrintBMP(17+count*16, 46, road2_D, 0);
        }
    }
    else if(road_flag > 10 && road_flag <16)
    {
        Nokia5110_PrintBMP(1, 10, road3, 0);
        Nokia5110_PrintBMP(1, 46, road3_D, 0);
        for(count=0;count<4;count++)
        {
            Nokia5110_PrintBMP(17+count*16, 10, road3, 0);
            Nokia5110_PrintBMP(17+count*16, 46, road3_D, 0);
        }
    }
    else if(road_flag > 15 && road_flag <21)
    {
        Nokia5110_PrintBMP(1, 10, road4, 0);
        Nokia5110_PrintBMP(1, 46, road4_D, 0);
        for(count=0;count<4;count++)
        {
            Nokia5110_PrintBMP(17+count*16, 10, road4, 0);
            Nokia5110_PrintBMP(17+count*16, 46, road4_D, 0);
        }
    }
    else
    {
        road_flag = 0;
    }
    for(count=0;count<2;count++)
    {
        if(Enemy1[count].life == 1)
        {
            Nokia5110_PrintBMP(Enemy1[count].x, Enemy1[count].y, Enemy1[count].image, 0);
        }
    }
    if(Player1.life == 1){
        Nokia5110_PrintBMP(Player1.x, Player1.y, Player1.image, 0);
    }else if(Player1.life == 0){
        Nokia5110_PrintBMP(Player1.x, Player1.y, Player.explode[0], 0);
    }
    Nokia5110_DisplayBuffer();
}
void Draw(){
    Nokia5110_ClearBuffer();
    Player_Draw();
    Bunker_Draw();
    Enemy_Draw();
    Player_Missile_Draw();
    Missile_Draw();
    Nokia5110_DisplayBuffer();
}
void Car_Init(){
    int i;
    for(i=0;i<2;i++){
        Enemy1[i].x = 68;
        Enemy1[i].image = Enemy_car;
        Enemy1[i].life = 0;
    }
}
void Car_Create(){
    c++;
    if((Enemy1[1].life == 0) && (c%3==2)){
        Enemy1[1].y = 15+rand()%26;
        Enemy1[1].life = 1;
        c = 0;
        UARTprintf("1\n");
    }
    if(Enemy1[0].life == 0){
        Enemy1[0].y = 15+rand()%26;
        Enemy1[0].life = 1;
        UARTprintf("0\n");
    }

}
void GameOver1(){
    int i;
    for(i=0;i<2;i++){
        if(Enemy1[i].life == 1){
            if(((Enemy1[i].x<=(Player1.x+15))&&((Enemy1[i].x+15)>=(Player1.x+15))
                    &&((Player1.y-9)<=Enemy1[i].y)&&((Player1.y-9)>=(Enemy1[i].y-9)))
            ||((Enemy1[i].x<=(Player1.x+15))&&((Enemy1[i].x+15)>=(Player1.x+15))
                    &&((Player1.y)<=Enemy1[i].y)&&((Player1.y)>=(Enemy1[i].y-9)))){
                Player1.life = 0;
            }
            if(Enemy1[i].x<2){
                Enemy1[i].x = 68;
                Enemy1[i].life = 0;
            }
            Enemy1[i].x -= 1;
        }
        if(Enemy1[0].x == 20){
            xSemaphoreGive(xMutex);
        }
        if(Enemy1[0].x < 2){
            xSemaphoreGive(xMutex);
        }
        if(Enemy1[1].x < 2){
            xSemaphoreGive(xMutex);
        }
    }
}






