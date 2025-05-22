#include "myheader.h"
void initPlayerShot(Match* matchPtr,ALLEGRO_BITMAP* shot_img,ALLEGRO_SAMPLE* boing){
    PlayerShot *playershot=&matchPtr->playershot;
    Player *playerPtr=&matchPtr->player;
    for(int i=0;i<2;i++){
        playershot[i].shotx[20-playerPtr->shot-1]=playerPtr->x+10;
        playershot[i].shoty[20-playerPtr->shot-1]=playerPtr->y-i*100+20;
        playershot[i].shotimg=shot_img;
    }
}

void PlayerShotMove(Match* matchPtr,ALLEGRO_BITMAP* shot_img,ALLEGRO_SAMPLE* boing){

    PlayerShot *playershot=&matchPtr->playershot;
    Player *playerPtr=&matchPtr->player;
    for(int j=0;j<20-playerPtr->shot;j++){
        for(int i=0;i<2;i++){
            if(i==0){
                playershot[i].shoty[j]+=SHOT_SPEED;}
            if(i==1){
                playershot[i].shoty[j]-=SHOT_SPEED;}

        }
    }
}
