#include "myheader.h"

////void initBall(Ball* ballPtr, ALLEGRO_BITMAP* img, ALLEGRO_SAMPLE* boing)
////{
////    ballPtr->x = SCREEN_W / 2-200;  /* give the ball its initial x-coordinate */
////    ballPtr->y = SCREEN_H / 2-300;  /* give the ball its initial y-coordinate */
////    ballPtr->dir = rand() % 4;  /* and then make a random initial direction */
////    ballPtr->img = img;
////    ballPtr->boing = boing;
////}



/* moves the ball */
////void moveBall(Match* matchPtr)
////{
////    Ball* ballPtr = &matchPtr->ball;
////
////    switch(ballPtr->dir)
////    {
////        case DOWN_RIGHT:
////            ++ballPtr->x; /* move the ball to the right */
////            ++ballPtr->y; /* move the ball down */
////
////            break;
////        case UP_RIGHT:
////            ++ballPtr->x; /* move the ball to the right */
////            --ballPtr->y; /* move the ball up */
////            break;
////        case DOWN_LEFT:
////            --ballPtr->x; /* move the ball to the left */
////            ++ballPtr->y; /* move the ball down */
////            break;
////        case UP_LEFT:
////            --ballPtr->x; /* move the ball to the left */
////            --ballPtr->y; /* move the ball up */
////            break;
////    } /* end switch */

    /* make sure the ball doesn go off the screen */

    /* if the ball is going off the top or bottom... */
////    if(ballPtr->y <= 0 || ballPtr->y >= (SCREEN_H - BALL_SIZE))
////    {
////        reverseVerticalDirection(&matchPtr->ball); /* make it go the other way */
////    }
////
////
////    /* if the ball is going off the left or right... */
////    if(ballPtr->x <= 0 || ballPtr->x >= (SCREEN_W - BALL_SIZE))
////    {
////        reverseHorizontalDirection(matchPtr); /* make it go the other way */
////    }



} /* end function moveBall */

/* reverse the ball up-down direction */
void reverseVerticalDirection(Match* matchPtr)
{
    Ball* ballPtr = &matchPtr->ball;
    if(ballPtr->dir == DOWN_RIGHT)
        ballPtr->dir = UP_RIGHT;
    else if(ballPtr->dir == DOWN_LEFT)
        ballPtr->dir = UP_LEFT;
    else if(ballPtr->dir == UP_RIGHT)
        ballPtr->dir = DOWN_RIGHT;
    else if(ballPtr->dir == UP_LEFT)
        ballPtr->dir = DOWN_LEFT;

    al_play_sample(ballPtr->boing, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE,
                   NULL); /* play "boing" sound once */

} /* end function reverseVerticalDirection */

/* reverses the horizontal direction */
void reverseHorizontalDirection(Match* matchPtr)
{
    Ball* ballPtr = &matchPtr->ball;
//   int player;
    switch(ballPtr->dir)
    {
        case DOWN_RIGHT:
            ballPtr->dir = DOWN_LEFT;
            //getScore(matchPtr, PLAYER_R);
            break;
        case UP_RIGHT:
            ballPtr->dir = UP_LEFT;
            //getScore(matchPtr, PLAYER_R);
            break;
        case DOWN_LEFT:
            ballPtr->dir = DOWN_RIGHT;
            //getScore(matchPtr, PLAYER_L);
            break;
        case UP_LEFT:
            ballPtr->dir = UP_RIGHT;
            //getScore(matchPtr, PLAYER_L);
            break;
    } /* end switch */
    al_play_sample(ballPtr->boing, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE,
                   NULL); /* play "boing" sound once */

} /* end function reverseHorizontalDirection */
