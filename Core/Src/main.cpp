#include "main.h"
#include "LED.h"
#include "Button.h"
#include "UART.h"
#include "Timer.h"
#include <cstdio>

void SystemClock_Config(void);

Button::Properties userButtonProps {
	GPIOA, GPIO_PIN_0, EXTI0_IRQn
};

Button infoButton(userButtonProps);

LED greenLed(GPIO_PIN_12);
LED orangeLed(GPIO_PIN_13);
LED redLed(GPIO_PIN_14);
LED blueLed(GPIO_PIN_15);

PulseLED bluePulseLed(blueLed, 1000);

UART TX(GPIO_PIN_2);
UART RX(GPIO_PIN_3);

Timer firstTimer(2);
Timer secondTimer(3);
Timer thirdTimer(4);
Timer fourthTimer(5);

void handleInfoButtonInterrupt(void*) {
	bluePulseLed.pulse();
}

extern void sysTickHookMain() {
	static int counter = 0;

	if (counter >= 25) {
		orangeLed.off();
	} else {
		orangeLed.on();
	}

	counter++;

	if (counter >= 50) {
		counter = 0;
	}
}

/* Assignment 1 : Exercise 7 */
void LedsCycle(LED leds[4]) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			if (i != j) {
				leds[j].off();
			}
		}
		leds[i].on();
		HAL_Delay(500);
	}
}

/* Assignment 1 : Exercise 8 */
enum Mode {CLOCK,COUNTERCLOCK, TOGETHER};
Mode mode = CLOCK;
void switchMode(void) {
	if (mode == CLOCK) {
		mode = COUNTERCLOCK;
	} else if (mode == COUNTERCLOCK) {
		mode = TOGETHER;
	} else if (mode == TOGETHER) {
		mode = CLOCK;
	}
}
void pressedListener (void*) {
	redLed.on();
	switchMode();
}

void LedsModes(void) {
	if (mode == CLOCK) {
		LED leds[] = {greenLed, orangeLed, redLed, blueLed};
		LedsCycle(leds);
	} else if (mode == COUNTERCLOCK) {
		LED leds[] = {greenLed, blueLed, redLed, orangeLed};
		LedsCycle(leds);
	} else if (mode == TOGETHER) {
		LED leds[] = {greenLed, blueLed, redLed, orangeLed};
		for (size_t i = 0; i < 4; i++) {
			leds[i].on();
		}
		HAL_Delay(500);
		for (size_t i = 0; i < 4; i++) {
			leds[i].off();
		}
		HAL_Delay(500);
	}
}

/* Assignment 1 : Exercise 10 */

/* Assignment 1 : Exercise 11 */

/* Assignment 2 : Exercise 1 */

/* Assignment 2 : Exercise 2 */

/* Assignment 2 : Exercise 3 */

/* Assignment 2 : Exercise 4 */


int main(void) {
  HAL_Init();

  SystemClock_Config();

  greenLed.init();
  orangeLed.init();
  redLed.init();
  blueLed.init();

  infoButton.init();
  infoButton.setPriority(2, 0);

  infoButton.setPressedListener(pressedListener, nullptr);

  TX.init();
  RX.init();

  while (1) {
	  /* Assignment 1 : Exercise 7 */
	  /*LED leds[] = {greenLed, orangeLed, redLed, blueLed};
	  LedsCycle(leds);*/

	  /* Assignment 1 : Exercise 8 */
	  //LedsModes();

	  /* Assignment 1 : Exercise 10 */

	  /* Assignment 1 : Exercise 11 */

	  /* Assignment 2 : Exercise 1 */

	  /* Assignment 2 : Exercise 2 */

	  /* Assignment 2 : Exercise 3 */

	  /* Assignment 2 : Exercise 4 */



  }

}

void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	//Configure the main internal regulator output voltage
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	//Initializes the CPU, AHB and APB busses clocks
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	//Initializes the CPU, AHB and APB busses clocks
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

void Error_Handler(void) {
	while(1) {}
}

#ifdef  USE_FULL_ASSERT

	void assert_failed(uint8_t *file, uint32_t line) {}

#endif
