#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"
#include <sys/types.h>

ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
    uart_send(*letter);
    letter++;
    }
    return count;
}

ssize_t _read(int fd, void *buf, size_t count){
    char *str = (char *)(buf);
    char letter;
    do {
        letter = uart_read();
    } while(letter == 0);
    *str = letter;
    return 1;
}

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
	GPIO->PIN_CNF[15] = (3 << 2);
	GPIO->PIN_CNF[16] = (3 << 2);
	GPIO->PIN_CNF[17] = 1;
	GPIO->PIN_CNF[18] = 1;
	GPIO->PIN_CNF[19] = 1;
	GPIO->PIN_CNF[20] = 1;
}

int main(){
	button_init();
	int sleep = 0;
	uart_init();
	int led_check = 0;
	int a,b;
	while(1){
		if(!(1 & (GPIO->IN) >> 13)){
			uart_send('A');
		}
		else if(!(1 & (GPIO->IN) >> 14)){
			uart_send('B');
		}
		else if(!(1 & (GPIO->IN) >> 15)){
			iprintf("The average grade in TTK%d in %d was: %c\n\r", 4235, 2022, 'B');
		}
		else if(!(1 & (GPIO->IN) >> 16)){
            iprintf("Enter one integer:\n\r");
            scanf("%d", &a);
            iprintf("Enter another:\n\r");
            scanf("%d", &b);
            iprintf("%d * %d = %d\n\r", a, b, a*b);
        }
		
		if(uart_read()!=0 && led_check==0){
			GPIO->OUTCLR = (1<<17);
			GPIO->OUTCLR = (1<<18);
			GPIO->OUTCLR = (1<<19);  
			GPIO->OUTCLR = (1<<20);
			led_check=1;
			uart_send('k');

		}
		else if(uart_read()!=0 && led_check==1){			
			GPIO->OUTSET = (1<<17);
			GPIO->OUTSET = (1<<18);
			GPIO->OUTSET = (1<<19);
			GPIO->OUTSET = (1<<20);
			led_check=0;
			uart_send('R');

		}
		sleep = 1000000;
		while(--sleep); 
	}
	return 0;
}

