
#include "myheader.h"

int getScore(Match* matchPtr,ALLEGRO_KEYBOARD_STATE* KBstatePtr)
{

    Player* playerPtr = &matchPtr->player;
        if(playerPtr->shottime>=SHOT_CD&&playerPtr->shot>0){
            playerPtr->shot-=1;
            playerPtr->shottime=0;
            return 1;
        }
        return 0;
}
