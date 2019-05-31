/*
 * basicADCSWC.c
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */
#include "stm32f1xx_hal.h"

#include "basicADCSWC.h"

#include "hardwareCfg.h"

#include "basicErrorHandlerSWC.h"


struct ADCErrorStruct {

	uint8_t ErrorADCStatusIPROPx;

	uint8_t ErrorADCStatusUserMotorSpd;

	uint32_t ErrorADCLastEntryIPROPx;

	uint32_t ErrorADCLastEntryUserMotorSpd;

} ADCErrorStruct_Tag;

struct ADCErrorStruct ADCErrorStruct_;

void basicReadADCRawValues()
{

}

void basicReadADCRawIPROP(void){

 uint16_t adc1=0, adc2=0, adc3 =0;
 uint32_t tickstart = 0U;

 /* Get tick count */
 tickstart = HAL_GetTick();

 ADC_ChannelConfTypeDef adcChannelx;

 adcChannelx.Channel = IPROP1CHNL;

 adcChannelx.Rank = 1;

 adcChannelx.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;


if (HAL_ADC_ConfigChannel(&hadc1, &adcChannelx) != HAL_OK)
   	{

	ADCErrorStruct_.ErrorADCStatusIPROPx++;

	ADCErrorStruct_.ErrorADCLastEntryIPROPx = HAL_GetTick();
	return;
   	}

HAL_ADC_Start(&hadc1);

   while(1) {

     if(__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_EOC))
     {

		adc1 = HAL_ADC_GetValue(&hadc1);


	    break;

	 }

     if((HAL_GetTick() - tickstart ) > ADC_TIMEOUT )

     {

    	 ADCErrorStruct_.ErrorADCStatusIPROPx++;

    	 ADCErrorStruct_.ErrorADCLastEntryIPROPx = HAL_GetTick();

    	 return;

     }

   }

HAL_ADC_Stop(&hadc1);



 adcChannelx.Channel = IPROP2CHNL;
 adcChannelx.Rank = 1;
 adcChannelx.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;

if (HAL_ADC_ConfigChannel(&hadc1, &adcChannelx) != HAL_OK)
	{
		ADCErrorStruct_.ErrorADCStatusIPROPx++;

		ADCErrorStruct_.ErrorADCLastEntryIPROPx = HAL_GetTick();

		return;
	}

HAL_ADC_Start(&hadc1);

while(1){

    	if(__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_EOC))
    	{

    		adc2 = HAL_ADC_GetValue(&hadc1);


			break;

	 	 }

    	if((HAL_GetTick() - tickstart ) > ADC_TIMEOUT )

    	{

   	 ADCErrorStruct_.ErrorADCStatusIPROPx++;

   	 ADCErrorStruct_.ErrorADCLastEntryIPROPx = HAL_GetTick();

   	 return;

    	}


	}

	HAL_ADC_Stop(&hadc1);

}

uint8_t basicGetErrorADCStatusIPROPx(void) {

	return ADCErrorStruct_.ErrorADCStatusIPROPx;

}

uint32_t basicGetErrorADCLastEntryIPROPx(void) {

	return ADCErrorStruct_.ErrorADCLastEntryIPROPx;

}

void basicReadADCRawUserMtrSpeed(void) {
	 uint16_t adc1=0, adc2=0, adc3 =0;
	 uint32_t tickstart = 0U;

	 /* Get tick count */
	 tickstart = HAL_GetTick();

	 ADC_ChannelConfTypeDef adcChannelx;

	 adcChannelx.Channel = POTUSRMTRSPEED;

	 adcChannelx.Rank = 1;

	 adcChannelx.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;


	if (HAL_ADC_ConfigChannel(&hadc1, &adcChannelx) != HAL_OK)
	   	{

		ADCErrorStruct_.ErrorADCStatusUserMotorSpd++;

		ADCErrorStruct_.ErrorADCLastEntryUserMotorSpd = HAL_GetTick();
		return;
	   	}

	HAL_ADC_Start(&hadc1);

	   while(1) {

	     if(__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_EOC))
	     {

			adc1 = HAL_ADC_GetValue(&hadc1);


		    break;

		 }

	     if((HAL_GetTick() - tickstart ) > ADC_TIMEOUT )

	     {

	    	 ADCErrorStruct_.ErrorADCStatusUserMotorSpd++;

	    	 ADCErrorStruct_.ErrorADCLastEntryUserMotorSpd = HAL_GetTick();

	    	 return;

	     }

	   }

	HAL_ADC_Stop(&hadc1);
}

uint8_t basicGetErrorADCStatusUserMotorSpd(void) {


	return ADCErrorStruct_.ErrorADCStatusUserMotorSpd;

}


void basicADCErrorHandler(void){

	if((HAL_GetTick()-ADCErrorStruct_.ErrorADCLastEntryIPROPx) > INTERNAL_ADCErrorEraseTime ) {

		ADCErrorStruct_.ErrorADCStatusIPROPx = 0;

	}

	else if((HAL_GetTick()-ADCErrorStruct_.ErrorADCLastEntryUserMotorSpd) > INTERNAL_ADCErrorEraseTime ) {

		ADCErrorStruct_.ErrorADCStatusUserMotorSpd = 0;

	}

	else if( ADCErrorStruct_.ErrorADCStatusIPROPx > 3 ) {

		/*
		 * TODO enter global error variable
		 */
		basicGlobalErrorState |= (1 << (MaskGlobalErrorADCStatusIPROPx));
	}

	else if(ADCErrorStruct_.ErrorADCStatusUserMotorSpd > 3) {

	   /*
		* TODO enter global error variable
		*/
		basicGlobalErrorState |= (1 << (MaskGlobalErrorADCStatusUserMotorSpd));
	}
}
