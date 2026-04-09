
#include <stdint.h>

//RCC registers

#define RCC_BASE 0x40023800
#define RCC_AHB1ENR *(uint32_t*)(RCC_BASE + 0x30)
#define RCC_APB1ENR *(uint32_t*)(RCC_BASE + 0x40)

//GPIO registers
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER *(uint32_t*)(GPIOA_BASE + 0x00)
#define GPIOA_AFRL *(uint32_t*)(GPIOA_BASE + 0x20)

// USART2 registers
#define USART2_BASE 0x40004400
#define USART2_SR  *(uint32_t*)(USART2_BASE + 0x00)
#define USART2_DR  *(uint32_t*)(USART2_BASE + 0x04)
#define USART2_BRR *(uint32_t*)(USART2_BASE + 0x08)
#define USART2_CR1 *(uint32_t*)(USART2_BASE + 0x0C)


int main(void)

{
	RCC_AHB1ENR |= (1 << 0);   // GPIOA enable
	RCC_APB1ENR |= (1 << 17);  // USART2 enable

	//for alternate function - 10
	GPIOA_MODER &= ~(1 << 4); // for PA2 bit4 = 0
	GPIOA_MODER |= (1 << 5); // for PA2 bit5 = 1
	GPIOA_MODER &= ~(1 << 6); // for PA3 bit6 = 0
	GPIOA_MODER |= (1 << 7); // for PA3 bit7 = 1

	//setting AF7
	GPIOA_AFRL |= (7 << (2 * 4)); // PA2
	GPIOA_AFRL |= (7 << (3 * 4)); // PA3


	//enabling USART and transmitter
	USART2_CR1 |= (1 << 13); // USART enable
	USART2_CR1 |= (1 << 3);  // Transmit enable

	USART2_BRR = 1667; //  16000000/9600


	while(1)
	{
		while(!(USART2_SR & (1 << 7))); //check if TXE is zero
		USART2_DR = 'H';

		while(!(USART2_SR & (1 << 7)));
		USART2_DR = 'i';

		for(int i = 0; i < 10000; i++); //delay
	}
}
