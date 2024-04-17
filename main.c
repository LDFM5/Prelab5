/*
 * Lab5.c
 *
 * Created: 16/04/2024 18:32:29
 * Author : luisd
 */ 
#define F_CPU 16000000
//#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include "PWM0/PMW0.h"
#include "PWM1/PWM1.c"
#include "ADC/ADC.c"
volatile uint8_t valorADC=0;
volatile uint8_t PuertoADC=4;
volatile uint16_t destino=0;

void init_pines(void){
		// Configurar los pines PC4, PC5 y A6 como entradas y habilitar resistencias de pull-up
		DDRC &= ~(1 << DDC4) & ~(1 << DDC5) & ~(1 << DDC6);
		PORTC |= (1 << PORTC4) | (1 << PORTC5)| (1 << PORTC6);

}

uint16_t reescalar(uint8_t valor, uint8_t max_origen, uint16_t max_destino) {
	// Convertir el valor al rango 0 - max_origen
	float valor_normalizado = (float)valor / max_origen;

	// Escalar el valor al rango 0 - max_destino
	uint16_t valor_reescalado = valor_normalizado * max_destino;

	return valor_reescalado;
}

int main() {
	init_pines();
	//frecuencia del adc -> 16M/128 = 125kHz
	init_ADC(0,0,128);
	
	destino=100;
	int preescaler=1024;
	
	init_PWM1A(0,6,preescaler, 50);
	//init_PWM1B(0);
	uint8_t valor = 0;


	while (1) {
		valor = readADC(4);
		uint16_t valor_reescalado = reescalar(valor, 255, destino);
		duty_cycle1A(valor_reescalado);
	}

	return 0;
}
