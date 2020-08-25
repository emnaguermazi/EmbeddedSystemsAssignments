#include "UART.h"

UART::UART(uint32_t pin) : pin(pin) {}

UART::~UART() {}



void UART::init() {

	/* Enable GPIO module */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* Configure the GPIO pins */
	GPIO_InitTypeDef GPIO_Init;
	GPIO_Init.Pin = pin;
	GPIO_Init.Mode = GPIO_MODE_AF_PP;
	GPIO_Init.Pull = GPIO_PULLUP;
	GPIO_Init.Speed = GPIO_SPEED_HIGH;
	GPIO_Init.Alternate = GPIO_AF7_USART2;

	/* Initialize the GPIO pins */
	HAL_GPIO_Init(GPIOA, &GPIO_Init);

	/* Enable UART 2 */
	__HAL_RCC_USART2_CLK_ENABLE();

	/* Configure the UART pins */
	UART_InitTypeDef  UART_Init;
	UART_Init.BaudRate = 9600;
	UART_Init.WordLength = UART_WORDLENGTH_8B;
	UART_Init.StopBits = UART_STOPBITS_1;
	UART_Init.Parity = UART_PARITY_NONE;
	UART_Init.Mode = UART_MODE_TX_RX;
	UART_Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_Init.OverSampling = UART_OVERSAMPLING_16;

	UART_Handle.Instance = USART2;
	UART_Handle.Init = UART_Init;


	/* Initialize the GPIO pins */
	HAL_UART_Init(&UART_Handle);

}

HAL_StatusTypeDef UART::Transmit(uint8_t *ptr) {
    return HAL_UART_Transmit(&UART_Handle, ptr, sizeof(ptr), HAL_MAX_DELAY);
}

HAL_StatusTypeDef UART::Receive(uint8_t *ptr) {
    return HAL_UART_Receive(&UART_Handle, ptr, sizeof(ptr), HAL_MAX_DELAY);
}


void UART::EnableInterrupt(uint32_t preemptPrio, uint32_t subPrio) {
	/* Enable UART interrupt */
	__HAL_UART_ENABLE_IT(&UART_Handle, UART_IT_TC);

	/* Enable interrupt on interrupt controller */
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	/* Adjust interrupt priority */
	HAL_NVIC_SetPriority(USART2_IRQn, preemptPrio, subPrio);
}

void UART::UART2_IRQHandler() {
	HAL_UART_IRQHandler(&UART_Handle);
}

