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
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter){
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    while(!(UART->EVENTS_TXDRDY)){
    }
    UART->TASKS_STOPTX = 1;
    UART->EVENTS_TXDRDY = 0;
}

char uart_read(){
    UART->TASKS_STARTRX = 1;
    char letter = 0;
    if(UART->EVENTS_RXDRDY){
        letter=UART->RXD;
    }
    UART->EVENTS_RXDRDY = 0;
    return letter;
}