#include "myheader.h"

void setball(struct Ball a[], int num){
    for(int i=0;i<num;i++){
        a[i].ball= al_load_bitmap( "ball.bmp");
        a[i].ball_x= rand()%(SCREEN_W - BALL_SIZE-1);
        a[i].ball_y= rand()%(SCREEN_H/2 - BALL_SIZE-1);
        a[i].direction = rand() % 4; /* and then make a random initial direction */
        setbullet(a[i].ball_x, a[i].ball_y,a[i].bul);
    }
}

void moveBall(struct Ball a[],int i) /* moves the ball */
{
   switch ( a[i].direction ) {
      case DOWN_RIGHT:
         a[i].ball_x+=MONSTERSPEED; /* move the ball to the right */
         a[i].ball_y+=MONSTERSPEED; /* move the ball down */
         break;
      case UP_RIGHT:
         a[i].ball_x+=MONSTERSPEED; /* move the ball to the right */
         a[i].ball_y-=MONSTERSPEED; /* move the ball up */
         break;
      case DOWN_LEFT:
         a[i].ball_x-=MONSTERSPEED; /* move the ball to the left */
         a[i].ball_y+=MONSTERSPEED; /* move the ball down */
         break;
      case UP_LEFT:
         a[i].ball_x-=MONSTERSPEED; /* move the ball to the left */
         a[i].ball_y-=MONSTERSPEED; /* move the ball up */
         break;
   } /* end switch */

   if ( a[i].ball_y <= 0 || a[i].ball_y >= (SCREEN_H/2 - BALL_SIZE) )
      MonsterreverseVerticalDirection(a,i); /* make it go the other way */
   /* if the ball is going off the left or right... */
   if ( a[i].ball_x <= 0 || a[i].ball_x >= (SCREEN_W - BALL_SIZE) )
      MonsterreverseHorizontalDirection(a,i); /* make it go the other way */
}

void MonsterreverseVerticalDirection(struct Ball a[],int i) /* reverse the balls up-down direction */
{
   if ( a[i].direction == DOWN_RIGHT ) a[i].direction = UP_RIGHT;
    else if ( a[i].direction == DOWN_LEFT ) a[i].direction = UP_LEFT;
        else if ( a[i].direction == UP_RIGHT ) a[i].direction = DOWN_RIGHT;
            else if ( a[i].direction == UP_LEFT ) a[i].direction = DOWN_LEFT;
} /* end function reverseVerticalDirection */

void MonsterreverseHorizontalDirection(struct Ball a[],int i) /* reverses the horizontal direction */
{

   switch (  a[i].direction ){
      case DOWN_RIGHT:
           a[i].direction = DOWN_LEFT;
         break;
      case UP_RIGHT:
          a[i].direction = UP_LEFT;
         break;
      case DOWN_LEFT:
          a[i].direction = DOWN_RIGHT;
         break;
      case UP_LEFT:
          a[i].direction = UP_RIGHT;
         break;
   } /* end switch */
} /* end function reverseHorizontalDirection */

void MonsterCollision(Match* matchPtr,struct Ball ballPtr[], ALLEGRO_KEYBOARD_STATE* KBstatePtr){
Player* playerPtr=&matchPtr->player;
for (int k=0;k<MONSTER_NUM;k++){

        if((abs((ballPtr[k].ball_x)-(playerPtr->x))<=BALL_SIZE)&&playerPtr->y==(ballPtr[k].ball_y+BALL_SIZE))
            {
                MonsterreverseVerticalDirection(ballPtr,k); /* make it go the other way */
                playerPtr->collisioncd=0;
                playerPtr->collisionstate=1;
                playerPtr->blood--;
            }
        if((abs((ballPtr[k].ball_x)-(playerPtr->x))<=BALL_SIZE)&&playerPtr->y==(ballPtr[k].ball_y-BALL_SIZE))
            {
                MonsterreverseVerticalDirection(ballPtr,k);  /* make it go the other way */
                playerPtr->collisioncd=0;
                playerPtr->collisionstate=2;
                playerPtr->blood--;

            }
        if((abs((ballPtr[k].ball_y)-(playerPtr->y))<=BALL_SIZE)&&playerPtr->x==(ballPtr[k].ball_x+BALL_SIZE))
            {
                MonsterreverseHorizontalDirection(ballPtr,k);  /* make it go the other way */
                playerPtr->collisioncd=0;
                playerPtr->collisionstate=3;
                playerPtr->blood--;

            }
        if((abs((ballPtr[k].ball_y)-(playerPtr->y))<=BALL_SIZE)&&playerPtr->x==(ballPtr[k].ball_x-BALL_SIZE))
            {
                MonsterreverseHorizontalDirection(ballPtr,k); /* make it go the other way */
                playerPtr->collisioncd=0;
                playerPtr->collisionstate=4;
                playerPtr->blood--;

            }

            playerPtr->collisioncd+=1;

    }
}
