#include "myheader.h"

void setbullet(int x, int y, struct bullet bul[])
{
    bul[0].bullet_direction =0;
    bul[1].bullet_direction =1;
    bul[2].bullet_direction =2;
    for(int j=0;j<bulnum;j++){
        bul[j].bullet=al_load_bitmap("bar.bmp");
        bul[j].bullet_x=x+BALL_SIZE/2;
        bul[j].bullet_y=y+BALL_SIZE/2;
    }

}

void movebullet(struct bullet bul[])
{
    for(int i=0;i<bulnum;i++){
        if(bul[i].bullet_y>SCREEN_H){
            return;
        }
        bul[i].bullet_y=bul[i].bullet_y+1;
        al_draw_bitmap( bul[i].bullet, bul[i].bullet_x, bul[i].bullet_y, 0);

        switch ( bul[i].bullet_direction ) {
          case DOWN_RIGHT:
            bul[i].bullet_x=bul[i].bullet_x+1; /* move the ball to the right */
            bul[i].bullet_y=bul[i].bullet_y+1; /* move the ball down */
            break;
          case DOWN:
            bul[i].bullet_y=bul[i].bullet_y+1;
            al_draw_bitmap( bul[i].bullet, bul[i].bullet_x, bul[i].bullet_y, 0);
            break;
          case DOWN_LEFT:
            bul[i].bullet_x=bul[i].bullet_x-1; /* move the ball to the left */
            bul[i].bullet_y=bul[i].bullet_y+1; /* move the ball down */
            break;
       }
    }

}
