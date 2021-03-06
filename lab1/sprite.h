/*
 * sprite.h
 *
 *  Created on: May 19, 2022
 *      Author: nghia
 */

#ifndef SPRITE_H_
#define SPRITE_H_
#include "stdint.h"
typedef struct {
    volatile uint8_t x;
    uint8_t y;
    uint8_t life;
    uint8_t point;
    const unsigned char *explode[2];
    const unsigned char *image;
    const unsigned char *block;
}sprite;
sprite Player;
sprite Enemy[15];
sprite Bunker[2];
sprite Player_Missile;
sprite Missile[15];
extern void Player_Init();
extern void Player_Move();
extern void Player_Draw();
extern void Bunker_Init();
extern void Bunker_Draw();
extern void Enemy_Init();
extern void Enemy_Move();
extern void Enemy_Draw();
extern void Missile_Init();
extern void Missile_Draw();
extern void Missile_Move();
extern void Player_Point();
extern void GameOver();
extern void Player_Missile_Init();
extern void Player_Missile_Draw();
extern void Player_Missile_Move();
extern void AutoFire();
extern void Draw();
////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct{
    volatile unsigned int x;
    unsigned int y;
    unsigned const char *image;
    unsigned int life;
}car_on_road;
car_on_road Player1;
car_on_road Enemy1[2];
extern unsigned int count,road_flag;
extern void RoadMove();
extern void Car_Init();
extern void Car_Create();
extern void GameOver1();
#endif /* SPRITE_H_ */
