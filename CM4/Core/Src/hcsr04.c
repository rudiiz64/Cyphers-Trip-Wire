/*
 * hcsr04.c
 *
 *  Created on: Feb 17, 2022
 *      Author: Rudi
 */

#include "hcsr04.h"

float duration = 0;
float distance = 0;

void sensorInit(){
	HAL_GPIO_WritePin(sensorEcho_GPIO_Port, sensorEcho_Pin, 0);
	HAL_GPIO_WritePin(sensorTrig_GPIO_Port, sensorTrig_Pin, 0);
}

void sensorPEC(TIM_TypeDef *htim){
	/* If the timer is equal to another defined timer or a defined value, reset the pin state and the counter */
}

void sensorData (struct hcsr04){
	// Sensor pin control
	HAL_GPIO_WritePin(sensorTrig_GPIO_Port, sensorTrig_Pin, 1);
	delay(10);
	HAL_GPIO_WritePin(sensorTrig_GPIO_Port, sensorTrig_Pin, 0);
	HAL_GPIO_WritePin(sensorEcho_GPIO_Port, sensorEcho_Pin, 1);

	// Computation of distance and time
	duration = HAL_GPIO_ReadPin(sensorTrig_GPIO_Port, sensorTrig_Pin);
	hcsr04_data->duration = duration * MICRO_CONV;
	hcsr04_data->distance = (duration/cm_conversion) * CM;
}