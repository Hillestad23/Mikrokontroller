#include "gpiote.h"

void gpiote_init(){
    GPIOTE->CONFIG[0] = ((1 << 0)) //Mode event 
    | (13 << 8) //Pin select 13
    | (2 << 16); //Polarity HiToLow

    for (int i = 1; i <=4; i++){
        GPIOTE->CONFIG[i] = ((3 << 0)) //Mode task 
        | ((16+i) << 8) //Pin select 17-20
        | (3 << 16) //Polarity Toggle
        | (1 << 20); //Initial high
    }
}

