#include <stdint.h>
#include "gpio.h"
#include "uart.h"

void uart_init(){
    GPIO->PIN_CNF[6] = (1 << 0); //Type XD
    GPIO->PIN_CNF[8] = (0 << 0); //Read XD

    UART->PSELTXD = 0x00000006;
    UART->PSELRXD= 0x00000008;

    UART->BAUDRATE = 0x00275000;

    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = (1 << 2);
    UART->TASKS_STARTRX = 1;
    UART->TASKS_STARTTX = 1;
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
    char letter = '\0';
    if(UART->EVENTS_RXDRDY){
        UART->EVENTS_RXDRDY = 0;
        letter=UART->RXD;
    }
    return letter;
}