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

void sensorData (hcsr04_data *data){
	// Sensor pin control
	HAL_GPIO_WritePin(sensorTrig_GPIO_Port, sensorTrig_Pin, 1);
	HAL_GPIO_WritePin(sensorTrig_GPIO_Port, sensorTrig_Pin, 0);
	HAL_GPIO_WritePin(sensorEcho_GPIO_Port, sensorEcho_Pin, 1);

	// Computation of distance and time
	duration = HAL_GPIO_ReadPin(sensorTrig_GPIO_Port, sensorTrig_Pin);
	data->duration = duration * MICRO_CONV;
	data->distance = (duration/cm_conversion) * CM;
}
