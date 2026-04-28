#include <stm32f446xx.h>
#include <stdio.h>

int main(void)
{
	//clock supply to all
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    GPIOA->MODER |= (3 << 0); //PA0 - 11 for analog mode

    GPIOA->MODER |= (2 << (2*2)); //PA2 - 10 for alternate function
    GPIOA->AFR[0] |= (7 << (2*4)); //AF7 for usart2

    USART2->BRR = 1667; // baud rate = 9600
    USART2->CR1 |= USART_CR1_UE; //enable usart2
    USART2->CR1 |= USART_CR1_TE; //enable transmitter

    ADC1->SQR3 |= 0; //channel 0
    ADC1->CR2 |= ADC_CR2_ADON; //enable adc

    while(1)
    {
    	ADC1->CR2 |= ADC_CR2_SWSTART; //starting conversion

    	while(!(ADC1->SR & ADC_SR_EOC));

        uint32_t analog_val = ADC1->DR;

        int digital_val = (analog_val * 3300) / 4096; //CONVERSION FROM ANALOG TO DIGITAL

        char msg[50];

        sprintf(msg, "Analog value = %d, Digital voltage = %d.%3dV \r\n",analog_val,digital_val/1000, digital_val%1000);

        for(int i = 0; msg[i] != '\0'; i++)
        {
        	while(!(USART2->SR & USART_SR_TXE));
        	USART2->DR = msg[i];

        }
    }

}










