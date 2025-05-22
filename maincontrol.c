#include "myheader.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "myheader.h"

void game(){




    int finish = 0;
    Match match;
    int num=MONSTER_NUM;//SET NUMBER OF MONSTER
    struct Ball a[num];
    int CountBulletTime1 = 0;
    int CountBulletTime2 = BulletTime/2;
    int Bullet2=0;

    Player* playerPtr = &match.player;
    PlayerShot* playershot=match.playershot;

    ALLEGRO_BITMAP* ball_img = NULL;        /* pointer to the ball's image bitmap */
    ALLEGRO_BITMAP* player_img = NULL;        /* pointer to the ball's image bitmap */
    ALLEGRO_BITMAP* playershot_img = NULL;        /* pointer to the ball's image bitmap */
    ALLEGRO_DISPLAY* display = NULL;    /* pointer to display */
    //ALLEGRO_DISPLAY* display1 = NULL;
    ALLEGRO_SAMPLE* boing = NULL;       /* pointer to sound file */
    ALLEGRO_SAMPLE* background = NULL;  /* pointer to sound file */
    ALLEGRO_FONT* pongFont = NULL;      /* pointer to Font file */
    ALLEGRO_KEYBOARD_STATE KBstate;
    ALLEGRO_SAMPLE_ID backgroundId;

    srand( time( NULL ) ); /* seed the random function */
    al_init(); /* initialize Allegro */
    al_install_keyboard(); /* install the keyboard for Allegro to use */
    al_init_image_addon();
    al_install_audio();  // install sound driver
    al_init_acodec_addon();      //AUDIO
    al_reserve_samples(9);
    al_init_font_addon();    // install font addons
    al_init_ttf_addon();

    display = al_create_display(SCREEN_W, SCREEN_H);

    playershot_img=al_load_bitmap("bar.bmp");
    player_img=al_load_bitmap("ball.bmp");
    ball_img = al_load_bitmap("ball.bmp");      /* load the ball bitmap */
    boing = al_load_sample("boing.wav");    /* load the sound file */

    initPlayer(playerPtr,player_img,boing);     /* initial the players */
    initPlayerShot(&match,playershot_img,boing);
    setball(a,num);

    pongFont = al_load_ttf_font("ARCHRISTY.ttf", 40, 0); /* load the FONT file */
    background = al_load_sample("taipei.wav"); /* load the background sound file */
    al_play_sample(background, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundId);
    //al_play_sample(boing, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundId1);

    while(finish == 0)
    {
        al_get_keyboard_state(&KBstate);
        if(al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
        {
            finish = 1;
        }
        while(PASS_TIME-al_get_time()>0&&finish == 0&&playerPtr->blood>0){
                //printf("%d\n",playershot[0].shoty[0]);
            al_get_keyboard_state(&KBstate);
            if(al_key_down(&KBstate, ALLEGRO_KEY_ESCAPE))
                {
                    finish = 1;
                }
            if(playerPtr->collisioncd>=COLLISION_CD+COLD_CD){
                playerPtr->collisionstate=0;
                movePlayer(&match,a,&KBstate);}
            else if(playerPtr->collisioncd<COLLISION_CD){

                if(playerPtr->collisionstate==1){
                    playerreverseVerticalDirectionUP(&match);
                    }
                if(playerPtr->collisionstate==2){

                    playerreverseVerticalDirectionDOWN(&match);
                    }
                if(playerPtr->collisionstate==3){
                    playerreverseHorizontalDirectionUP(&match);
                    }
                if(playerPtr->collisionstate==4){
                    playerreverseHorizontalDirectionDOWN(&match);
                    }
            }

            MonsterCollision(&match,a,&KBstate);
            playerPtr->shottime+=1;
            al_draw_bitmap(playerPtr->img, playerPtr->x, playerPtr->y, 0);

            if(al_key_down(&KBstate, ALLEGRO_KEY_SPACE)){
                if(getScore(&match,&KBstate)==1){
                    initPlayerShot(&match,playershot_img,boing);
                }
            }
            for(int j=0;j<20-playerPtr->shot;j++){
                for(int i=0;i<2;i++){
                    al_draw_bitmap(playershot[i].shotimg, playershot[i].shotx[j], playershot[i].shoty[j], 0);}////////
                }
            PlayerShotMove(&match,playershot_img,boing);
            CountBulletTime1++;
            CountBulletTime2++;
            for(int i=0;i<num;i++){
                moveBall(a,i); /* move the ball */
                al_draw_bitmap( a[i].ball, a[i].ball_x, a[i].ball_y, 0);/* draw the bitmap */
                movebullet(a[i].bul);
                if(CountBulletTime1>=BulletTime){
                    setbullet(a[i].ball_x, a[i].ball_y,a[i].bul);
                }
                if(CountBulletTime2>=BulletTime){
                    setbullet(a[i].ball_x, a[i].ball_y,a[i].bul2);
                    Bullet2=1;
                }
                if(Bullet2){
                   movebullet(a[i].bul2);
                }
            }

            if(CountBulletTime1>=BulletTime){
                CountBulletTime1=0;
            }
            if(CountBulletTime2>=BulletTime){
                CountBulletTime2=0;
            }
            al_draw_textf(pongFont, al_map_rgb(255, 255, 255), 200, 0, -1,
                              "Player Blood: %d", playerPtr->blood);
            al_draw_textf(pongFont, al_map_rgb(255, 255, 255), 600, 0, -1,
                              "Player Shot: %d", playerPtr->shot);
            al_draw_textf(pongFont, al_map_rgb(255, 255, 255),1000, 0, -1,
                              "Time Remaining: %.1lf",PASS_TIME-al_get_time());
            al_rest(0.003);

            al_flip_display(); /* Wait for the beginning of a vertical retrace. */
            al_clear_to_color(al_map_rgb(10,50,100));
        }
    }
    for(int k=0;k<num;k++){
        al_destroy_bitmap( a[k].ball); /* destroy the ball bitmap */
        for(int l=0;l<bulnum;l++){
            al_destroy_bitmap( a[k].bul[l].bullet);
        }
    }
    al_stop_sample(&backgroundId);   /* stop bgm */
    al_destroy_sample(background);  /* destroy the background sound file */
    al_destroy_bitmap(ball_img);        /* destroy the ball bitmap */
    al_destroy_display(display);    /* destroy the display */
    al_destroy_bitmap(player_img);
    al_destroy_bitmap(playershot_img);       /* destroy the bar bitmap */
    al_destroy_sample(boing);       /* destroy the boing sound file */
    al_destroy_font(pongFont);      /* destroy the font */

} /* end function main */


void initPlayer(Player* playerPtr, ALLEGRO_BITMAP* player_img,ALLEGRO_SAMPLE* boing)
{
    playerPtr->x=SCREEN_W / 2;
    playerPtr->y=SCREEN_H / 2;
    playerPtr->shot=SHOT_SIZE;
    playerPtr->boing=boing;
    playerPtr->img=player_img;
    playerPtr->blood=PLAYER_BLOOD;
    playerPtr->shottime=0;
    playerPtr->collisioncd=COLLISION_CD;
    playerPtr->collisionstate=0;
}


//void initPaddle(Paddle* paddlePtr, ALLEGRO_BITMAP* img)
//{
//    /* give left paddle its initial y-coordinat e */
//    paddlePtr->yLeft = SCREEN_H / 2;
//    /* give right paddle its initial y-coordinate */
//    paddlePtr->yRight = SCREEN_H / 2;
//    paddlePtr->img = img;
//}

void movePlayer(Match* matchPtr,struct Ball ballPtr[], ALLEGRO_KEYBOARD_STATE* KBstatePtr)

{

//    Ball ballPtr[MONSTER_NUM];
//    for(int i=0;i<MONSTER_NUM;i++){
//    ballPtr[i]= matchPtr->ball[i];}


    Player* playerPtr=&matchPtr->player;
    if(al_key_down(KBstatePtr, ALLEGRO_KEY_LEFT))
        //paddlePtr->yLeft -= PADDLE_MOVE;
        playerPtr->x-=PLAYER_MOVE;
        //printf("%d\n",paddlePtr->yLeft);

    if(al_key_down(KBstatePtr, ALLEGRO_KEY_RIGHT))
        //paddlePtr->yLeft += PADDLE_MOVE;
         playerPtr->x+=PLAYER_MOVE;

    if(al_key_down(KBstatePtr, ALLEGRO_KEY_UP))
        playerPtr->y-=PLAYER_MOVE;


    if(al_key_down(KBstatePtr, ALLEGRO_KEY_DOWN))
        playerPtr->y+=PLAYER_MOVE;

    /* make sure the paddles don go off screen */


    if(playerPtr->y < 0)
        playerPtr->y = 0;
    if(playerPtr->y > SCREEN_H-BALL_SIZE)
        playerPtr->y = SCREEN_H-BALL_SIZE;
    if(playerPtr->x < 0)
        playerPtr->x = 0;
    if(playerPtr->x > SCREEN_W-BALL_SIZE)
        playerPtr->x = SCREEN_W-BALL_SIZE;





}
void playerreverseVerticalDirectionUP(Match* matchPtr){

    Player* playerPtr=&matchPtr->player;
    playerPtr->y+=PLAYER_MOVE;


}
void playerreverseVerticalDirectionDOWN(Match* matchPtr){

    Player* playerPtr=&matchPtr->player;
    playerPtr->y-=PLAYER_MOVE;


}
void playerreverseHorizontalDirectionUP(Match* matchPtr){

    Player* playerPtr=&matchPtr->player;
    playerPtr->x+=PLAYER_MOVE;


}
void playerreverseHorizontalDirectionDOWN(Match* matchPtr){

    Player* playerPtr=&matchPtr->player;
    playerPtr->x-=PLAYER_MOVE;


}

