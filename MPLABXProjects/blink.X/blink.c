#include "p33ep64mc202.h"

_FICD(ICS_PGD1 & JTAGEN_OFF);

int main()
{
	TRISA = 0b1111111111111110;
        TRISB = 0b1111111111111111;
        ANSELA = 0b0000000000000000;
        ANSELB = 0b0000000000000000;
        long int i,j;
	while(1)
        {
            for( j = 0 ; j < 100000 ; j++)
            {}
		LATA = 0b0000000000000001;

            for( j = 0 ; j < 100000 ; j++)
            {}
                if(PORTB & 0x0001)
		LATA = 0b0000000000000000;
	}
	return 0;
}
