/*Created by Guna shekar G 
	as part of Task RECIEVED by NUNAM technologies*/
// This is application file 

#include<stdio.h>
#include "nrf.h"         // library file for nrf family
#include "Task_Driver.h" //Including the header file
#include "Task_Driver.c" //Including the developed driver
int i=0;
//main program
void main(){
	//for every 529us timestamp needs to be printed
	//529us = 18903 Hz
	while(1){
		start_timer(529, fptr);		//starting a timer to count, for every 529us, timestamp needs to be print
		if(timestampStatus){
			//Caoture has occured for 529us
			i++;
			printf("The current time stamp is %d.%d", i,timestamp);
			//or we can use the UART peripheral to print on the serial window
		}
	}	
	
	return 0;
}