/*
 * ADC.c
 *
 * Created: 03/11/2024 04:49:35 p.m.
 * Author : LSL
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
	//Selección de la referencia de voltaje
	ADMUX &=~ (1 << REFS1);
	ADMUX |= (1 << REFS0);
	
	ADMUX &=~ (1 << ADLAR); //Ajuste de bits ADCL
	
	//Selección del pin de ADC (el 4 es  un bit reservado)
	ADMUX &=~ (1 << MUX3);
	ADMUX &=~ (1 << MUX2);
	ADMUX &=~ (1 << MUX1);
	ADMUX &=~ (1 << MUX0);

	
    ADCSRA |= (1 << ADEN); //Se habilita el ADC
	ADCSRA |= (1 << ADSC); //Comienza la conversión de ADC
	
	ADCSRA |= (1 << ADATE); //Auto trigger habilitado
	
	//Clock division (entre 2)
	ADCSRA |= (1 << ADPS2);
	ADCSRA &=~ (1 << ADPS1);
	ADCSRA &=~ (1 << ADPS0);
	
	DDRB |= (1<<0); //Pin del led como salida
	
	int adc = 0;
	
    while (1) 
    {
		ADCSRA |= (1 << ADEN); //Se habilita el ADC
		ADCSRA |= (1 << ADSC); //Comienza la conversión de ADC
		
		ADCSRA |= (1 << ADIF); //Se habilita cuando la conversión ADC termina
		
		adc = (ADC*5)/1024; 
		
		if(adc >= 3){
			PORTB |= (1 << 0);
		}else{
			PORTB &=~ (1 << 0);
		}
    }
}

