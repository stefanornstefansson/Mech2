/*
 * UART_Transmit.h
 *
 *  Created on: Mar 1, 2021
 *      Author: Notandi
 */

#ifndef UART_TRANSMIT_H_
#define UART_TRANSMIT_H_

void ToTerm(char data){
	while (!(UCSR0A & (1<<UDRE0))){
	// pu t da ta i n t o b u f f e r

	}
	//DDRB=0x20; //make LED p in o u t p u t
	UDR0 = data;
}

pow (int x){

	int y = 1;
	int k = 10;

	if(x == 0){
			return 1;
	}
	else{
	for(char i=1; i<=x; i++){
		y = y*10;
		//ToTerm(y);
	}
	}
	return y;
}
void InitUART(){
    UBRR0H = 0;
	UBRR0L = 207;
// e n a bl e r e c e i v e r and t r a n sm i t t e r
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
// set frame format
	UCSR0C=(1<<USBS0) | (3<<UCSZ00);

}

void UART_Transmit_Byte_Hex (unsigned char data){
UART_Transmit_Nibble_Hex(data >> 4);
UART_Transmit_Nibble_Hex(data & 0x0F);
}

void UART_Transmit_Int_Hex (unsigned int data){
	UART_Transmit_Byte_Hex(data >> 8);
	UART_Transmit_Byte_Hex(data & 0x00FF);

}

void UART_Transmit_Long_Hex (unsigned long data){
	UART_Transmit_Int_Hex(data >> 16);
	UART_Transmit_Int_Hex(data & 0x0000FFFF);
}


void UART_Transmit_Nibble_Hex (unsigned char data){

	unsigned char c;
	c = ' ';
	data = data & 0x0F; // mask o u t l ow e r n i b b l e
	if((data >= 0) && (data < 10))
		c = '0' + data;
	if((data >= 10) && (data <= 15))
		c = 'A'+ (data - 10);
	ToTerm(c);
}

void UART_Transmit_Byte_Dec (char data){
	char a = 0;
	char b = data/10;
	char c, d;

	while(b >= 1){
		//ToTerm(b);
		b = b/10;
		a++;
	}

	for(int j=a; j>=0; j--){
		//ToTerm('b');
		c = data / pow(j);
		c = c % 10;
		d = c+48;
		ToTerm(d);
	}
}



UART_Receive(){
	char cData;
	while (!(UCSR0A & (1<<RXC0))){
	// g e t and r e t u r n da ta

	}
	cData= UDR0;
}

void UART_Transmit_String (char s[])
{
	char cIndex = 0;
	while (s[cIndex] != 0)
	{
		ToTerm(s[cIndex]);
		cIndex++;
	}
}

int strlen (char s[])
{
	int i = 0;
	while (s[i] != 0)
		i++;
	return i;
}


void UART_itoa (int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0 ) // r e c o r d s i g n
		n = -n; // make n p o s i t i v e
	i = 0;

	do { // g e n e r a t e d i g i t s i n r e v e r s e o r d e r
		s[i++] = n%10 + '0'; // g e t n e x t d i g i t
	} while ((n /= 10) > 0); // d e l e t e i t
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	}

// C program for implementation of ftoa()

// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;

	// Extract floating part
	float fpart = n - (float)ipart;

	// convert integer part to string
	int i = intToStr(ipart, res, 0);

	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}






#endif /* UART_TRANSMIT_H_ */
