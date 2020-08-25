#include "hooks.h"
#include "main.h"
#include "LED.h"

void SysTick_Handler(void) {
	HAL_IncTick();
	PulseLED::tickInterruptHandler();
	//sysTickHookMain();
}

void EXTI0_IRQHandler(void) {
	infoButton.pressedInterruptHandler();
}

