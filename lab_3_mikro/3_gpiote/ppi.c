#include "ppi.h"
#include "gpiote.h"

void ppi_init(){
    for (int i = 1; i<=4; i++){
        PPI->PPI_CH[i].EEP = (uint32_t)&(GPIOTE->EVENTS_IN[0]);
        PPI->PPI_CH[i].TEP = (uint32_t)&(GPIOTE->TASKS_OUT[1+i]);
        PPI->CHENSET = (1 << i);
    }
}