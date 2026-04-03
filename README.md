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
      >PSC value was set to 7999 as the clock is 8MHz and the preferred tick rate was 1KHz (timer take 1ms per tick).
      >For a delay of 2s - ARR was set to 1999; for 2000ms we need 2000 ticks of the timer (verified using above formula).
      >The control register of the timer was set 1 to enable the timer (TIM2_CR1).
      >The status register of the timer was used as a flag (TIM2_SR).
      >The status register (update flag) becomes 1 when the timer finishes counting, after this the flag is reset to start the event again.
                                          

                                          
