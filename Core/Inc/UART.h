#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal_iwdg.h"

class UART {
	public:

		UART(uint32_t pin);
		~UART();
		void init();
		HAL_StatusTypeDef Transmit(uint8_t *ptr);
		HAL_StatusTypeDef Receive(uint8_t *ptr);
		void EnableInterrupt(uint32_t preemptPrio, uint32_t subPrio);
		void UART2_IRQHandler();

	private:
		uint32_t pin;
		UART_HandleTypeDef  UART_Handle;

};

#endif
