/*
 * errorHandler.c
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */
#include "stm32f1xx_hal.h"

#include "basicErrorHandlerSWC.h"

#include "basicLEDDriverSWC.h"

#include "interfaces.h"

#include "basicADCSWC.h"

#include "core_cm3.h"

uint8_t basicGlobalErrorState=0;
uint8_t redLedBlinking=0;

void basicCheckGlobalErrors(void){

	if(basicGlobalErrorState & (1<<MaskGlobalErrorADCStatusIPROPx)) {

		/*TODO error led function and shut down*/
		redLedBlinking |= (1 << MaskRedLedFastBlinking);
		NVIC_SystemReset();

		return;
	}

	else if(!(basicGlobalErrorState & (1<<MaskGlobalErrorADCStatusIPROPx))) {

		/*reset the led blinking request*/
		redLedBlinking &= ~(1 << MaskRedLedFastBlinking);

	}

	if (basicGlobalErrorState & (1<<MaskGlobalErrorADCStatusUserMotorSpd)) {

		/*TODO error user motor speed, set speed to 80% of 327
		 */
		basicSetADCRawValueUserMotorSpd((uint16_t)228);
	}

	if((HBridgeFailureCode_sig==1)) {

		/* HBridge error is reported from the Hardware. (nFault pin)*/
		redLedBlinking |= (1 << MaskRedLedFastBlinking);
	}

	else if((HBridgeFailureCode_sig==0)) {

		/* Clear HBridge error, is reported from the Hardware. (nFault pin)*/
		redLedBlinking &= ~(1 << MaskRedLedFastBlinking);
	}

	if(ApplicationInternalError_sig==1) {

		/* Application Software error is reported*/
		redLedBlinking |= (1 << MaskRedLedSlowBlinking);
	}
	else if(ApplicationInternalError_sig==0) {

		/* Clear  Application Software error*/
		redLedBlinking &= ~(1 << MaskRedLedSlowBlinking);
	}


}
