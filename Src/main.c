
#include <stdint.h>


// RCC
#define RCC_BASE 0x40023800
#define RCC_AHB1ENR RCC_BASE + 0x30
#define RCC_APB1ENR RCC_BASE + 0x40

//GPIOA
#define GPIOA_MODER 0x40020000
#define GPIOA_ODR GPIOA_MODER + 0x14

//Timer2
#define TIM2_CR1 0x40000000
#define TIM2_PSC TIM2_CR1 + 0x28
#define TIM2_ARR TIM2_CR1 + 0x2C
#define TIM2_SR TIM2_CR1 + 0x10

int main(void)
{

	*((uint32_t*)(RCC_AHB1ENR)) |= (1 << 0); // GPIOA enable (bit0 = 1)
	*((uint32_t*)(RCC_APB1ENR)) |= (1 << 0); // TIM2 enable (bit0 = 1)

	*((uint32_t*)(GPIOA_MODER)) &= ~(1 << 11); //PA5 --> 01, bit11 = 0
	*((uint32_t*)(GPIOA_MODER)) |= (1 << 10); // bit10 = 1

	*((uint32_t*)(TIM2_PSC)) = 7999; //prescaler slows down clock to from 8MHz to 1kHz, timer ticks every 1ms
	*((uint32_t*)(TIM2_ARR)) = 1999; // ARR counts the number of ticks, we need 2000ms so ARR = 1999
	*((uint32_t*)(TIM2_CR1)) |= (1 << 0); //bit0 = 1 to enable counter

	while(1)
	{
		while(!(*((uint32_t*)(TIM2_SR)) & 1)); //while status register is 0 dont do anything

		*((uint32_t*)(TIM2_SR)) &= ~(1 << 0); //when status register becomes 1, turn it to 0 then blink the LED

		*((uint32_t*)(GPIOA_ODR)) ^= (1 << 5); //when LED is off --> turn on and vice versa
	}
}
