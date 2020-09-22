// This is a driver.c file
/*Created by Guna shekar G 
	as part of Task RECIEVED by NUNAM technologies*/
	
/*This is the implementation file for the Custom Driver
that counts for a specific amount of time*/


#include <stdio.h>
#include<matlib.h>
#include "Task_Driver.h"

//Global variable to store the timestamp
	extern int timeStamp = 0;		//global variable to store the captured value
	int delayHz = 0;				//global variable to calculate delay in hz (1/529us)
	int pscVal = 0;					//global variable to calculate the value that needs to loaded tp prescalar register to obtain delay of 529us
	extern bool timestampStatus = false; //global boolean to indicate whether the capture event occured on 529us or not

static void timerInit(int time){
	TimerBasedInstance TI1;
	TI1.Prescalar = TIMER_PRESCALAR;
	TI1.CounterMode = TIMER_MODE_Counter;		// Timer is set to Counter mode to count
	TI1.TimePeriod = time;
	TI1.BitMode = TIMER_BITMODE_16Bit;			//Set counter to 16 bit resolution
}

//Callback function that will just starts the timer after all the initialization
static void start_function(){
	NRF_TIMER2->TASKS_START = 1;               // Start TIMER2
}

extern void *fptr = &start_function(void);

extern void start_timer(int time, fptr);
{	
	/* timer in nrf52810 is connected to APB bus and since we know APB is peripheral clock, 
	we should make sure LFCLCK enabled since for the counter mode of the timer external clock source is required*/
	
	if(LFCLKSTAT && HFCLKSTAT){
		//Both LFCLCK and HFCLCK is enabled
		timerInit(time);		
		
		NRF_TIMER2->CC[0] = 10000;                               //Set value for TIMER2 compare register 0   (should calculate for 529 us)
		NRF_TIMER2->CC[1] = 5;                                   //Set value for TIMER2 compare register 1
	}
}

//A function that stops the timer on calling it
extern stop_timer(){
	NRF_TIMER2->TASKS_STOP = 1;  //stops the timer
}







//STM32 Timer code
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//Since I am a fresher and not knowing much about nordic based controller, I have done the timer part in STM32 controller as I am slightly aware of that config
	//I have tried to initialize nrf52810 in .h file
	
	//stm32 driver developed for stm32 nucleo board(virtual not tested)
	//The below program waits for the captured value to be set and then stores the captured value in global variable timeStamp
	//PA5 input, Timer2 generates count and toggles LED for every 1Hz, PA6 input Timer3 output, captures the set value and stores 
	
	//Global variable to store the timestamp
	int timeStamp = 0;		//global variable to store the captured value
	static int timeInterval=0; //static variable that holds the real time timestamp of the capture
	delayHz = 1/time;		//calculating delay in Hz 1/529u = 18903 Hz
	pscVal = SYSCLK_FREQ/delayHz; //calculating the value that needs to be loaded on to the prescalar register to get the 529us delay 16M/18903 = 846
	
	//configuring TIM2 for counter 
	RCC->AHB1ENR |= 1;     // Enable AHB bus 
	GPIOA-> MODER | 0x800; //set GPIO to alternate mode
	GPIOA->AFR[0] |= 0x00010000;  //setting alternate function to TIM2
	RCC->APB1 |=0x01; //since Timer is connected to apb, enabling apb bus
	
	TIM2->PSC = 847-1;	//Loading 1600 to pre scalar reg 16M divided bt 1600
	TIM2->ARR = 1;  //Loading ARR to totally give 18903 HZ delay which is 529 us 
	TIM2-> CCMR |= 0x30; //set output to toggle on match
	TIM2-> CCR1 = 0;//set match mode
	TIM2->CNT = 1; //enable ch1
	TIM2->CR1 = 1; //Enable TIM2
	
	//configuring TIM3 CH1 as input capture for match and capture to count / indicate on match of obtaining delay
	RCC->APB1ENR |=1;			// since timer 3 is an alternative function of GPIOA which is further connected to APB bus
	GPIOA->MODER |= 0x200;		//set PA6 to alternate function
	GPIOA->AFR[0] |= 0x02000000; //select the alternate function of PA6 to timer 3 ch1 
	TIM3->PSC = 1600;			//Value to be loaded in order to divide the sysclk(16MHz) 
	TIM3->ARR = 10000;			//value to load Autoreload register in order to obtain 1Hz of delay
	TIM3->CCMR = 0x41;			//0100 0001 that is setting CH1 of the TIM3 to capture at every edge
	TIM3->CCER = 1;				//Enable ch1 of TIM3
	TIM3->CR1 = 1;				//Enable TIM3
	while(1){
		while(! TIM3->SR &2){}     //wait untill the input edge is captured
		timeInterval = TIM3->CCR1;
		timestamp = timeInterval; //this sttement is provided in order to get the real time timestamp that needs to be printed via application code, since static variable can not be externed
		timestampStatus = true;		//Indicates that capture event is triggered
	}
	
	//End of counter for 1Hz using STM32 microcontroller
	
	//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------