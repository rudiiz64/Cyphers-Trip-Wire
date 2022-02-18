/*
 * hcsr04.h
 *
 *  Created on: Feb 17, 2022
 *      Author: Rudi
 */

#ifndef INC_HCSR04_H_
#define INC_HCSR04_H_

#include <stm32h745xx.h>
#include "main.h"

#define CM 100
#define cm_conversion 58
#define MICRO_CONV 100000

typedef struct hcsr04 {
	float duration;
	float distance;
}hcsr04_data;


/* Purpose: Initialization function of the HCSR04
 * @param: None
 * @retval: None
*/
void sensorInit();

/* @purpose: Period Elapsed Callback function of the HCSR04
 * @param: A pointer to a timer struct
 * @retval: None
*/
void sensorPEC(TIM_TypeDef *htim);

/* @purpose: Data analysis function of the HCSR04
 * @param: None
 * @retval: None, values are instead stored in a struct
*/
void sensorData(hcsr04_data *data);

#endif /* INC_HCSR04_H_ */
