/* 
 * File:   pwm_implem.c
 * Author: Vinay
 *
 * Created on March 13, 2012, 3:28 PM
 */

#include "p33ep64mc202.h"
#include <libpic30.h>

_FOSCSEL(PWMLOCK_OFF);
int pwm_50()
{
    PTCON = 0x0000;
    PTPER = 1000; //1000

    PHASE1 = 0;

    PDC1 = 500;

    DTR1 = 0;
    ALTDTR1 = 0;

    PWMKEY = 0xABCD;

    PWMKEY = 0x4321;

    IOCON1 = 0xCC00;

    PWMCON1 = 0x0000;

    PWMKEY = 0xABCD;

    PWMKEY = 0x4321;

    FCLCON1 = 0x0003;

    PTCON2 = 0x0003; //clock prescaler

    PTCON = 0x8000;

	/*while(1)
	{
            
	}*/

return 0;
}

int pwm_80()
{
    PTCON = 0x0000;
    PTPER = 1000; //1000

    PHASE1 = 0;

    PDC1 = 800;

    DTR1 = 0;
    ALTDTR1 = 0;

    PWMKEY = 0xABCD;

    PWMKEY = 0x4321;

    IOCON1 = 0xCC00;

    PWMCON1 = 0x0000;

    PWMKEY = 0xABCD;

    PWMKEY = 0x4321;

    FCLCON1 = 0x0003;

    PTCON2 = 0x0003; //clock prescaler

    PTCON = 0x8000;

	/*while(1)
	{

	}*/

return 0;
}

int pwm_100()
{
    PTCON = 0x0000;
    PTPER = 1000; //1000

    PHASE1 = 0;

    PDC1 = 1000;

    DTR1 = 0;
    ALTDTR1 = 0;

    PWMKEY = 0xABCD;

    PWMKEY = 0x4321;

    IOCON1 = 0xCC00;

    PWMCON1 = 0x0000;

    PWMKEY = 0xABCD;

    PWMKEY = 0x4321;

    FCLCON1 = 0x0003;

    PTCON2 = 0x0003; //clock prescaler

    PTCON = 0x8000;

	/*while(1)
	{

	}*/

return 0;
}

int pwm_20()
{
    PTCON = 0x0000;
    PTPER = 1000; //1000

    PHASE1 = 0;

    PDC1 = 200;

    DTR1 = 0;
    ALTDTR1 = 0;

    PWMKEY = 0xABCD;

    PWMKEY = 0x4321;

    IOCON1 = 0xCC00;

    PWMCON1 = 0x0000;

    PWMKEY = 0xABCD;

    PWMKEY = 0x4321;

    FCLCON1 = 0x0003;

    PTCON2 = 0x0003; //clock prescaler

    PTCON = 0x8000;

	/*while(1)
	{

	}*/

return 0;
}

/*--- Global sytem clock ---*/

volatile unsigned int sysclock = 0;

/*--- Initialise Timer 1 (Used as system 1mS clock) ---*/

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

int main()
{
    //start_timer_1();
    TRISA = 0b1111111111111110;
    while(1)
    {
        //pwm_20();
            LATA = 0b0000000000000001;
            delay_1mS(1000);
        //pwm_100();
        LATA = 0b0000000000000000;
            delay_1mS(1000);
        
        //pwm_50();
       
            //delay_1mS(1000);
        
        //pwm_80();
        
            //delay_1mS(1000);
        
        //pwm_20();
        
            //delay_1mS(1000);
        
    }

    return 0;
}


