#include <stdint.h>
#include "gpio.h"
#include "uart.h"

void uart_init(){
    GPIO->PIN_CNF[6] = 1; //Type XD
    GPIO->PIN_CNF[8] = 0; //Read XD

    UART->PSELTXD = 6;
    UART->PSELRXD= 8;

    UART->BAUDRATE = 0x00275000;

    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = 4;
    UART->TASK_STARTRX = 1; //Sjekk om det stemmer
}

void uart_send(char letter){
    UART->TXD = letter;
    while(!(UART->EVENTS_TXDRDY)){
        UART->EVENTS_TXDRDY = 0;
    }
    UART->TASK_STOPTX = 1;
}

char uart_read(){
    while(!(UART->EVENTS_TXDRDY)){
        UART->EVENTS_TXDRDY = 0;
    }
    if(UART->RXD == ""){
        return "\0";
    }
    return UART->RXD;
}