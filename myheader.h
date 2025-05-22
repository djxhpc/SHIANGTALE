#ifndef _MYHEADER_H_
#define _MYHEADER_H_
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>



#define DOWN_RIGHT 0
#define UP_RIGHT 1
#define DOWN_LEFT 2
#define UP_LEFT 3
#define DOWN 1



#define SCREEN_W  1600
#define SCREEN_H  800
#define PASS_TIME 140
#define BALL_SIZE 40



#define SHOT_SIZE 20
#define SHOT_CD 45
#define SHOT_SPEED 5


#define COLD_CD 500


#define PLAYER_MOVE 2
#define PLAYER_BLOOD 15

#define MONSTERSPEED 1
#define MONSTER_NUM 5
#define UP_LEFT 3
#define bulnum 3
#define BulletTime 1000
#define COLLISION_CD 300


typedef struct Player
{
    int x; 		/* the ball's x-coordinate */
    int y; 		/* the ball's y-coordinate */
    int blood;
    int shottime;
    int shot;
    ALLEGRO_BITMAP* img; 	/* pointer to the ball's image bitmap */
    ALLEGRO_SAMPLE* boing; 	/* pointer to sound file */
    int collisioncd;
    int collisionstate;

} Player;



typedef struct PlayerShot
{
    int shotx[SHOT_SIZE];
    int shoty[SHOT_SIZE];
    ALLEGRO_BITMAP* shotimg;
    ALLEGRO_SAMPLE* boing;

} PlayerShot;



typedef struct bullet
{
    ALLEGRO_BITMAP *bullet ; /* load the ball bitmap */
    int bullet_x;  /* give the ball its initial x-coordinate */
    int bullet_y; /* give the ball its initial y-coordinate */
    int bullet_direction;

}bullet;

typedef struct Ball
{
    ALLEGRO_BITMAP *ball ; /* load the ball bitmap */
    int ball_x;  /* give the ball its initial x-coordinate */
    int ball_y; /* give the ball its initial y-coordinate */
    int direction;
    bullet bul[bulnum];
    bullet bul2[bulnum];
    ALLEGRO_SAMPLE* boing; 	/* pointer to sound file */
}Ball;


typedef struct Match
{
    //Ball ball[MONSTER_NUM];
    Player player;  /* score of the two player */
    PlayerShot playershot[2];

} Match;



void initPlayer(Player* playerPtr, ALLEGRO_BITMAP* player_img,ALLEGRO_SAMPLE* boing);
void movePlayer(Match* matchPtr,struct Ball ballPtr[], ALLEGRO_KEYBOARD_STATE* KBstatePtr);
int getScore(Match* matchPtr,ALLEGRO_KEYBOARD_STATE* KBstatePtr);
void initPlayerShot(Match* matchPtr,ALLEGRO_BITMAP* shot_img,ALLEGRO_SAMPLE* boing);
void PlayerShotMove(Match* matchPtr,ALLEGRO_BITMAP* shot_img,ALLEGRO_SAMPLE* boing);
void moveBall( struct Ball a[],int i );
void MonsterreverseVerticalDirection( struct Ball a[],int i );
void MonsterreverseHorizontalDirection( struct Ball a[],int i );
void setball(struct Ball a[], int num);
void setbullet(int x, int y, struct bullet bul[]);
void movebullet(struct bullet bul[]);
void playerreverseVerticalDirectionUP(Match* matchPtr);
void playerreverseVerticalDirectionDOWN(Match* matchPtr);
void playerreverseHorizontalDirectionUP(Match* matchPtr);
void playerreverseHorizontalDirectionDOWN(Match* matchPtr);
void MonsterCollision(Match* matchPtr,struct Ball ballPtr[], ALLEGRO_KEYBOARD_STATE* KBstatePtr);
void game();
#endif // _MYHEADER_H_
