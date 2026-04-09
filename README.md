PART 1 - 
Objective - Design a precise LED blinking system using a hardware timer. The LED must toggle every 2 seconds, strictly based on timer events.

What a timer is in a microcontroller :-

      > A timer is counter which counts the ticks of the clock depending on the speed of the clock (16MHz, 8Mhz etc).
      > After a certain amount of ticks, an update happens which causes an interrupt to occur and perform a function (like 
        turn on an LED or turn off an LED).

Why hardware timers are preferred over software delays :-

      > Software delays are generally less effiecient than hardware timers, because they depend upon the compiler and they 
        also keep the CPU in use for the delay, whereas timers can function independently and can allow the CPU to handle 
        other tasks (multitasking). 
      > We can get accurate delays of our preference using timers than software delays.

Basic working concept :- 

      > The timer counts the number of times the clock ticks, but initially the clock ticks at a very high speed, for eg - 16Mhz i.e 16000000 times in one second, therefore it is hard for the timer to keep track and hence we use a pre-scaler which slows down the tick rate to a smaller value which is easier for the timer to count. For example if we set the PSC (pre-scaler) to 15999,it counts from 0 to 15999 i.e 16000 times, it slows down the clock ticking rate to 1Khz (16MHz/(15999 + 1)).
      > The ARR (auto reload register) stores a certain value, when the timer starts counting from 0, it goes till the highest value in ARR after which the timer overflows and resets to 0 (overflow indicates an update - LED turn on).
      > We can verify the values of ARR and PSC set using the timer formula which is - 
                          Interrupt time(in seconds) = ((PSC + 1)(ARR + 1))/Clock frequency


Register Configuration for 2-Second Delay :-

      >In this program, general purpose timer - TIM2 was used which is connected APB1 bus.
      >PSC value was set to 15999 as the clock is 16MHz and the preferred tick rate was 1KHz (timer take 1ms per tick).
      >For a delay of 2s - ARR was set to 1999; for 2000ms we need 2000 ticks of the timer (verified using above formula).
      >The control register of the timer was set 1 to enable the timer (TIM2_CR1).
      >The status register of the timer was used as a flag (TIM2_SR).
      >The status register (update flag) becomes 1 when the timer finishes counting, after this the flag is reset to start the event again.
                                          




PART 2 - 
Objective - Understand and implement serial communication between the microcontroller and a computer using UART.

UART Protocol :-

      >UART is Universal Asynchronus Receiver/Transmitter. It is used for serial communication between the microcontroller and other devices.
      >It is a protocol which allows serial communication to happen wihtout the use of clock signal (hence Asynchronus).
      >Two wires are present which are the Tx and Rx (transmitter and receiver) from transmitting and recepting data respectively.
      >It can be used for low speed applications. In comparision with parallel communication which is better for high speed, UART is better in terms of less complexity.
      >Baud rate is the rate at which bits are transmitted per second. When two devices are communicating, the Baud rate for both should be same.
      >Data sent follows a frame format which includes - start bit, data bits, parity bit (optional) and stop bit
                              >start bit - when the start bit is logic 0, it allows the receiver to know that data will be sent.
                              >data bit - these bits are the actual information to be passed.
                              >stop bit - when the stop bit (logic 1) is passed, it indicated that the data transfer has finished.
                              >parity bit - this is a bit which is used to identify if the data passed is correct or not. It can either be even parity or odd parity. In even parity, the parity bit is set so that the total number of 1's is even. In odd parity, the parity bit is set so that the total number of 1's is odd.


      >Asynchronus communication is all about Baud rate and start and stop bits (without the use of clock).
                                          
2) Implementation Details :-

        >RCC_AHB1ENR (used for GPIOA), RCC_APB1ENR (used for USART2), GPIOA_MODER, GPIOA_AFRL (to use PA2 as TX and PA3 as RX), USART2_BRR (to set baud rate - no of clock cycles per bit), USART2_CR1 (to enable USART2), USART2_SR (to check if data can be sent or not using flags), USART2_SR (to store the data to be transmitted).

        >Baud rate - 9600 bits/sec, BRR register stores the number of cylces of clock after which data is to be sent, so in one bit is transmitted in 1/9600s - during which 16000000/9600 = 1667(approx) clock cycles are completed. Therefore USART2_BRR is set to 1667.


         >Steps involved in transmitting data :-
               1) Enable USART
               2) Before sending each character, check the TXE flag (in Transmit register) is empty.
               3) SET TXE and send the data into USART data register.
               











