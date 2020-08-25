#include "Timer.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_conf.h"

Timer::Timer(uint32_t tim) : tim(tim) {}

Timer::~Timer() {}

void Timer::init() {

	/* Enable timer clock and initialize the timer */
	TIM_Base_InitTypeDef TIM_Init;
	TIM_Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM_Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	if (tim == 2) {
		__HAL_RCC_TIM2_CLK_ENABLE();
		TIM_Init.Prescaler = (uint16_t) (HAL_RCC_GetPCLK1Freq()/10/25-1);
		TIM_Init.Period = 25;
		TIM_Handle.Instance = TIM2;
	} else if (tim == 3) {
		__HAL_RCC_TIM3_CLK_ENABLE();
		TIM_Init.Prescaler = (uint16_t) (HAL_RCC_GetPCLK1Freq()/20*3/40-1);
		TIM_Init.Period = 40;
		TIM_Handle.Instance = TIM3;
	} else if (tim == 4) {
		__HAL_RCC_TIM4_CLK_ENABLE();
		TIM_Init.Prescaler = (uint16_t) (HAL_RCC_GetPCLK1Freq()/4/64-1);
		TIM_Init.Period = 64;
		TIM_Handle.Instance = TIM4;
	} else if (tim == 5) {
		__HAL_RCC_TIM5_CLK_ENABLE();
		TIM_Init.Prescaler = (uint16_t) (HAL_RCC_GetPCLK1Freq()/5*2/100-1);
		TIM_Init.Period = 100;
		TIM_Handle.Instance = TIM5;
	}
	TIM_Handle.Init = TIM_Init;

	HAL_TIM_Base_Init(&TIM_Handle);

}

void Timer::Start() {
	HAL_TIM_Base_Start(&TIM_Handle);
}

uint32_t Timer::GetCounter() {
	return __HAL_TIM_GET_COUNTER(&TIM_Handle);
}

void Timer::EnableInterrupt(uint32_t preemptPrio, uint32_t subPrio) {
	/* Enable timer update interrupt */
	__HAL_TIM_ENABLE_IT(&TIM_Handle, TIM_IT_UPDATE);

	/* Enable interrupt on interrupt controller and adjust interrupt priority */
	if (tim == 2) {
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
		HAL_NVIC_SetPriority(TIM2_IRQn, preemptPrio, subPrio);
	} else if (tim == 3) {
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
		HAL_NVIC_SetPriority(TIM3_IRQn, preemptPrio, subPrio);
	} else if (tim == 4) {
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
		HAL_NVIC_SetPriority(TIM4_IRQn, preemptPrio, subPrio);
	} else if (tim == 5) {
		HAL_NVIC_EnableIRQ(TIM5_IRQn);
		HAL_NVIC_SetPriority(TIM5_IRQn, preemptPrio, subPrio);
	}
}

void Timer::ClearFlag() {
	__HAL_TIM_CLEAR_FLAG(&TIM_Handle, TIM_IT_UPDATE);
}
