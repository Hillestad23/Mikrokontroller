#include <stdint.h>
#include "uart.h"
#include "gpio.h"

void button_init(){ 
	/*GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
	GPIO->PIN_CNF[17] = 1;
	GPIO->PIN_CNF[18] = 1;
	GPIO->PIN_CNF[19] = 1;
	GPIO->PIN_CNF[20] = 1;*/
	// Fill inn the configuration for the remaining buttons 
}

int main(){
	// Configure LED Matrix
	// for(int i = 17; i <= 20; i++){
	// 	GPIO->DIRSET = (1 << i);
	// 	GPIO->OUTCLR = (1 << i);
	// }

	// Configure buttons -> see button_init()
	button_init();

	int sleep = 0;
	while(1){
		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}

