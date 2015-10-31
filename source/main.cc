#include "serial_stream_stm32f3.h"
#include "timer_15.h"
#include "Clock.h"
#include "timedclock.h"
#include "ctimers_stmf3.h"
#include "stm32f30x.h"                  // Device header

void led_init(void);

int main(){
	//System configuration
	led_init();
	timer2_init(500,0);
	timer2_start();
	//User application
	while(1);
}

void led_init(void){
	//Turn on the GPIOB peripherial
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	//Configure PB13  as push pull ouput an set the output to high
	GPIOB->MODER &=~(GPIO_MODER_MODER13);
	GPIOB->MODER |=GPIO_MODER_MODER13_0;//output
	GPIOB->ODR |= GPIO_ODR_13;
}

void led_flip(void){
	static int lastVal = 0;
	if(lastVal == 0){
		lastVal = 1;
		GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_RESET);
	}else{
		lastVal = 0;
		GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_SET);
	}
}

void timer2_callback(void){
	led_flip();
}
