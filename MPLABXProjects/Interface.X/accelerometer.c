/* 
 * File:   accelerometer.c
 * Author: Vinay
 *
 * Created on April 24, 2012, 9:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "p33ep64mc202.h"
#include <libpic30.h>

/*
 * 
 */
void start_timer_1(void)
  {
  T1CON = 0;
  T1CONbits.TCKPS = 2;  /* Prescaler 1:64 */
  IPC0bits.T1IP = 5;    /* High Priority */
  IEC0bits.T1IE = 1;
  IFS0bits.T1IF = 0;
  PR1 = 576;            /* ~1mS */
  TMR1 = 0;
  T1CONbits.TON = 1;
  }

//====================================================================| SETUP USART
void setupUSART(){

    /*TXSTA1 =   0b00100000; //Enable transmit and low baud rate
    RCSTA1 =   0b10010000; //Enable serial port and continous receive
    BAUDCON1 = 0b00001000; //Enable 16 bit baud generator
    SPBRGH = 0;                // Set Baud Rate
    SPBRG = 25;                // Set Baud Rate High*/




}

volatile unsigned int sysclock = 0;

/*--- Timer 1 Interrupt ~1mS system timer ---*/

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
  {
  sysclock++;
  IFS0bits.T1IF = 0;
  }

/*--- Millisecond delay ---*/

void delay_1mS(unsigned int milliseconds)
  {
  unsigned int timer;

  timer = sysclock;

  while((sysclock - timer) < milliseconds){
    ;
    }
    //long int i;
    //for(i=0;i<65000;i++){}
}

int main(int argc, char** argv)
{

    TRISA = 0b1111111111111110;
    TRISB = 0b1111111111111111;
    ANSELA = 0b0000000000000000;
    ANSELB = 0b0000000000000000;
    start_timer_1();
    while(1)
    {
        LATAbits.LATA0 = 0;
        
        if(PORTB & 0x0001)
        LATAbits.LATA0 = 1;

        delay_1mS(100);
    }
    return 1;
}

