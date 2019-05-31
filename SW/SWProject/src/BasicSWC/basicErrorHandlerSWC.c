/*
 * errorHandler.c
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */
#include "stm32f1xx_hal.h"

#include "basicErrorHandlerSWC.h"

#include "basicLEDDriverSWC.h"

uint8_t basicGlobalErrorState=0;

void basicCheckGlobalErrors(void){

	if(basicGlobalErrorState & MaskGlobalErrorADCStatusIPROPx) {

		/*TODO error led function and shut down*/
		redLedBlinking |= (1 << MaskRedLedFastBlinking);

	}

	else if(!(basicGlobalErrorState & MaskGlobalErrorADCStatusIPROPx)) {

		/*reset the led blinking request*/
		redLedBlinking &= ~(1 << MaskRedLedFastBlinking);

	}

	else if (basicGlobalErrorState & MaskGlobalErrorADCStatusUserMotorSpd) {

		/*TODO error user motor speed, set speed to 80%
		 */
	}



}
