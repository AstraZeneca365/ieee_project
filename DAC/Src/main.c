#include <stm32f446xx.h>
#include <stdint.h>
#include<stdio.h>
#include<math.h>

void delay(void)
{
    for (volatile int i = 0; i < 10000; i++);
}


int main(void)
{

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;

	GPIOA->MODER |= (3 << (5*2));

	DAC->CR |= DAC_CR_EN2;

	/*
	//single voltage
	DAC->DHR12R2 = 2048; //voltage ~ 3.3/2 = 1.65V
	*/

	/*
	//ramp voltage

	while(1)
	{
		for(int i = 0; i < 4096; i++)
		    {
		        DAC->DHR12R2 = i;
		        delay();
		    }
	}
	*/

	/*
	//sine voltage

	while(1)
	{
		for(int i = 0; i < 4096; i++)
		{
			float angle = (2*3.14159*i)/4096;
			DAC->DHR12R2 = (uint32_t)((sin(angle) + 1)*2048);
			delay();
		}
	}
	*/




}
