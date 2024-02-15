#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define F_OUT PB1

/*

| OCR1A  |   0   |   1   |    2    |   3   |    4    |
| Focr1a | 4 MHz | 2 MHz | 1.3 MHz | 1 MHz | 800 kHz |

| OCR1A  |    5    |    6    |    7    |    8    |    9    |
| Focr1a | 666 kHz | 571 kHz | 500 kHz | 444 kHz | 400 kHz |

*/

void Timer1_Init(void)
{
	/*******************************************
		Clear Timer on Compare Match (CTC) Mode
	********************************************/
	// Toggle OC1A/OC1B on Compare Match
	TCCR1A = (1 << COM1A0);
	// No prescaling; CTC mode
	TCCR1B = (1 << CS10)|(1 << WGM12);
	// For 1 MHz output
	OCR1A = 3;
}

int main(void)
{
	// Output
	DDRB = (1 << F_OUT)|(1 << LED);

	Timer1_Init();

	while (1)
	{
		PORTB ^= (1 << LED);
		_delay_ms(500);
	}

	return 0;
}