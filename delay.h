/*
 * delay.h
 *
 *  Created on: Mar 20, 2021
 *      Author: Notandi
 */

#ifndef DELAY_H_
#define DELAY_H_

/*
 * delay.c
 *
 *  Created on: Feb 15, 2021
 *      Author: Notandi
 */

void delay_ms(unsigned int milliSeconds){
while(milliSeconds){
	milliSeconds--;
	delay_us(1000);
}
}

void delay_us(unsigned int microSeconds){
	while(microSeconds){
		microSeconds--;
	}
}




#endif /* DELAY_H_ */
