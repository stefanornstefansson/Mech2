/*
 * DCmotor.h
 *
 *  Created on: Apr 6, 2021
 *      Author: Notandi
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

void motor(){
	char c = 0;
	DDRB = 0x01;
		while(c<3){
			delay_ms(300);
			PORTB = 0x01;
			delay_ms(100);
			PORTB = 0x00;
			c++;
		}

}

#endif /* DCMOTOR_H_ */
