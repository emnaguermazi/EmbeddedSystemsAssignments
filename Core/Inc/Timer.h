#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_conf.h"


class Timer {
	public:

		Timer(uint32_t pin);
		~Timer();
		void init();
		void Start();
		uint32_t GetCounter();
		void EnableInterrupt(uint32_t preemptPrio, uint32_t subPrio);
		void ClearFlag();

	private:
		uint32_t tim;
		TIM_HandleTypeDef TIM_Handle;
};

#endif
