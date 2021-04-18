/*
 * main.c
 *
 *  Created on: Mar 18, 2021
 *      Author: Notandi
 */
#include <avr/io.h>
#include "mlxsensor.h"
#include <steveo/UART_Transmit.h>
#include <steveo/delay.h>
#include <steveo/DCmotor.h>


int main(){
	char res[20];
	float temp2, sum;
	 InitUART();
	 PORTB = 0x02;

	 TWI_Init();

	  uint16_t ret;
	  uint8_t r;
	   //char print;
	   uint16_t temp;
	 /*
	   ret = TWI_ReadRegByte(0x5A, 0x07); // receive DATA
	   ret |= TWI_ReadRegByte(0x5A, 0x07) << 8;
	   */
while(1){
	while(PINB !=0x02){
	}
	sum = 0;
for(int i=0; i<100; i++){

	 r = TWI_ReadReg2Bytes(0xB4, 7, &temp); // read MSB

	 // Uart_int_Dec(i);

	  /* ret |= TWI_ReadRegByte(0x5A, 0x07) << 8;            // receive DATA
	   temp = (float)ret;
	   temp *= .02;
	   temp -= 273.15;
	   */
	  // print = (char)
	   /*ToTerm(ret3);
	   ToTerm(ret);
	   ToTerm(ret<<8);
*/
	  /*
	  ToTerm(c1);
	  ToTerm(c2);
	  */
	  //ToTerm('w');
	  if(r==TWI_ERROR){
		 // ToTerm('s');
		  TWIStop();
	  }

	  	  //temp = (float)temp;
	  	  temp2 = temp*0.02-273.15+5.2;



	      ftoa(temp2, res, 1);
	      UART_Transmit_String(res);
	      UART_Transmit_String(" ");

	      sum += temp2;

	      delay_ms(30);
	      }
			if((sum/100.0)>32.0){
				UART_Transmit_String("aaa");
				ftoa((sum/100.0), res, 1);
				motor();


			}
			ftoa(sum/100, res, 1);
			UART_Transmit_String("bbb");
			UART_Transmit_String(res);
			/*ftoa(sum/100.0, res, 1);
			UART_Transmit_String(res);
			*/



}
}


