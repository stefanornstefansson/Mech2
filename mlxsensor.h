/*
 * mlxsensor.h
 *
 *  Created on: Mar 18, 2021
 *      Author: Notandi
 */

#ifndef MLXSENSOR_H_
#define MLXSENSOR_H_

uint8_t TWI_ERROR = 0;
uint8_t TWI_SUCCESS = 1;

void TWI_Init(void)
{
// s e t SCL t o 400kHz
	TWSR = 0x00; //no need f o r pre−s c a l i n g
	TWBR = 0xC8; // t h i s i s a l l we need f o r SCL 400kHz
	TWCR = (1<<TWEN); // e n a bl e TWI, i t t a k e s over t h e I /O p i n s
}

void TWIStart(void){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while((TWCR & (1<<TWINT))==0){

	}




}

uint8_t TWIGetStatus (void) // read s t a t u s
{
	uint8_t status;
//mask s t a t u s
	status = (TWSR & 0xF8);
	return status;
}

void TWIWrite (uint8_t u8data) // w r i t e d a t a t o TWI
{

	TWDR = u8data;

	TWCR = (1<<TWINT)|(1<<TWEN); // Clear TWINT t o s t a r t t r a n sm i s s i o n o f a d d r e s s
	while ((TWCR & (1<<TWINT)) == 0){ // w a i t f o r Ack / Nack
	}
	}


uint8_t TWIReadNACK(void) // read b y t e w i t h NACK
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
	return TWDR;
}


uint8_t TWIReadACK(void) // read b y t e w i t h ACK
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while ((TWCR & (1<<TWINT)) == 0 );
	return TWDR;
}

void TWIStop (void) // send s t o p s i g n a l
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while (!(TWCR & (1<<TWSTO))); // Wait t i l l s t o p c o n d i t i o n i s t r a n sm i t t e d
}

uint8_t TWI_ReadRegByte(uint8_t slave, uint8_t reg, uint8_t* cReturn)
{


	uint8_t c;
	TWIStart();

	if((c=TWIGetStatus()) != 0x08){ // i s s t a r t no t s e n t

		return TWI_ERROR;
	}


	TWIWrite(slave); // nex t w r i t e a b y t e t o s l a v e
	if(TWIGetStatus() != 0x18){ // i f ACK no t r e c e i v e d

		return TWI_ERROR;
	}

	TWIWrite(reg); // w r i t e t h i s b y t e

	if(TWIGetStatus() != 0x28){

		return TWI_ERROR;
	}

	TWIStop();

//delay_ms(2); //a s h o r t d el a y i s needed

	TWIStart();
	if(TWIGetStatus() != 0x08){

		return TWI_ERROR;
	}

	TWIWrite ((slave) | 0x01); // nex t read a b y t e
	if(TWIGetStatus() != 0x40){

			return TWI_ERROR;
	}

	c=TWIReadNACK(); //must use NAC t o i n d i c a t e end

	if(TWIGetStatus() != 0x58){

			return TWI_ERROR;
	}

	TWIStop();

	*cReturn=c;
	return TWI_SUCCESS;
		delay_ms(1000);
}
uint8_t TWI_ReadReg2Bytes(uint8_t slave, uint8_t reg, uint16_t* iReturn)
{


	uint16_t i;
	uint8_t c1, c2, c3;
	TWIStart();

	if((i=TWIGetStatus()) != 0x08){ // i s s t a r t no t s e n t
		ToTerm('a');
		return TWI_ERROR;
	}


	TWIWrite(slave); // nex t w r i t e a b y t e t o s l a v e
	if(TWIGetStatus() != 0x18){ // i f ACK no t r e c e i v e d
		ToTerm('b');
		return TWI_ERROR;
	}

	TWIWrite(reg); // w r i t e t h i s b y t e

	if(TWIGetStatus() != 0x28){
		ToTerm('c');
		return TWI_ERROR;
	}

	//TWIStop();
//delay_ms(1); //a s h o r t d el a y i s needed
	TWIStart();
	if(TWIGetStatus() != 0x10){
		ToTerm('d');
		return TWI_ERROR;
	}

	TWIWrite ((slave) | 0x01); // nex t read a b y t e
	if(TWIGetStatus() != 0x40){
		ToTerm('e');
			return TWI_ERROR;
	}

	c1=TWIReadACK();
	if(TWIGetStatus() != 0x50){
			ToTerm('f');
				return TWI_ERROR;
		}
	c2=TWIReadACK(); //must use NAC t o i n d i c a t e end
	if(TWIGetStatus() != 0x50){
			ToTerm('g');
				return TWI_ERROR;
		}
	c3=TWIReadACK();


	if(TWIGetStatus() != 0x50){
		ToTerm('h');
			return TWI_ERROR;
	}

	TWIStop();
	i=((c2<<8)|c1);
	*iReturn=i;
	return TWI_SUCCESS;
		delay_ms(1);
}




uint8_t TWI_WriteRegByte(uint8_t slave, uint8_t reg, uint8_t cValue)
{
	char c;
	TWIStart();
	if((c=TWIGetStatus()) != 0x08){ // i s s t a r t no t s e n t
		ToTerm('a');
			return TWI_ERROR;
	}

	TWIWrite(slave); // nex t w r i t e a b y t e t o s l a v e
	if(TWIGetStatus() != 0x18){
		ToTerm('b');
		return TWI_ERROR;
	}
	TWIWrite(reg); // w r i t e t h i s b y t e
	if(TWIGetStatus() != 0x28){
		ToTerm('c');

		return TWI_ERROR;
	}

	TWIWrite(cValue);
	if(TWIGetStatus() != 0x28)
		return TWI_ERROR;


	TWIStop();

		return TWI_SUCCESS;

}



#endif /* MLXSENSOR_H_ */
