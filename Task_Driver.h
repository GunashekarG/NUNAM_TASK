/*Created by Guna shekar G 
	as part of Task RECIEVED by NUNAM technologies*/

/* this is a driver.h file
	This contains the definitions and declarations regarding the custom Timer 
	driver that implemented in the Task_Driver.c file*/

#ifndef __TASK_DRIVER_H
#define __TASK_DRIVER_H

#define TIMER_MODE_REG 0x504            //Register to select mode of the Timer

#define TIMER_PRESCALAR 0x510           //Prescalar register
#define TIMER_BITMODE 0x508             //configure  number of bits used by the timer
#define TIMER_SHORTCUT_REG 0x200        //Shortcut register
#define TIMER_INTERRUPT ENABLE  0x304   //Interrupt enable register
#define TIMER_INTERRUPT DISABLE  0x308   //Interrupt disable register
#define TIMER_CC_0 0X540                 // Timer capture compare reg 0
#define TIMER_CC_1 0X544                 // Timer capture compare reg 1
#define TIMER_CC_2 0X548                 // Timer capture compare reg 2
#define TIMER_CC_3 0X54C                 // Timer capture compare reg 3
#define TIMER_CC_4 0X550                 // Timer capture compare reg 4
#define TIMER_CC_5 0X554                 // Timer capture compare reg 5

#define SYSCLK_FREQ 16000000			//System clock frequency 16MHz

// Timer mode definitions

#define TIMER_MODE_Timer   0      // 0 for timer mode(low power)
#define TIMER_MODE_Counter 2       // 2 for counter mode(low power)

#define TASKS_HFCLKSTART 0x00     //Start HFCLK crystal oscillator 
#define TASKS_HFCLKSTOP  0x04	  //Stop HFCLK crystal oscillator
#define TASKS_LFCLKSTART 0x08	  //Start LFCLK source
#define TASKS_LFCLKSTOP  0x0C	  //Stop LFCLK source
#define HFCLKRUN 0x408				//Status indicating that HFCLKSTART task has been triggered
#define HFCLKSTAT 0x40C			//LFCLK status
#define LFCLKRUN 0x414			//Status indicating that LFCLKFCLKSTART task has been triggered
#define LFCLKSTAT 0x4198			//LFCLK status

#define TIMER_PRESCALAR 1    	//Defining the timer pre scalar value


typedef struct{
	uint32_t Prescalar,
	uint32_t CounterMode,
	uint32_t TimePeriod,
	uint32_t BitMode
} TimerBasedInstance;

void start_timer(int time, &start_function(void));		//Function to start the timer task

// Timer bitmode definitions

#define TIMER_BITMODE_16Bit 0
#define TIMER_BITMODE_08Bit 1
#define TIMER_BITMODE_24Bit 2
#define TIMER_BITMODE_32Bit 3


#endif