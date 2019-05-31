/*
 * basicADCSWC.h
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */

#ifndef INCLUDE_BASICSWC_BASICADCSWC_H_
#define INCLUDE_BASICSWC_BASICADCSWC_H_

#define IPROP1CHNL ADC_CHANNEL_1
#define IPROP2CHNL ADC_CHANNEL_2
#define POTUSRMTRSPEED ADC_CHANNEL_8
#define ADC_TIMEOUT 10 //ms
#define INTERNAL_ADCErrorEraseTime 300 //ms

void basicReadADCRawValues(void);
void basicReadADCRawIPROP(void);
uint8_t basicGetErrorADCStatusIPROPx(void);
uint32_t basicGetErrorADCLastEntryIPROPx(void);
void basicReadADCRawUserMtrSpeed(void);
void basicADCErrorHandler(void);
uint8_t basicGetErrorADCStatusUserMotorSpd(void);

struct ADCErrorStruct ADCErrorStruct_;



#endif /* INCLUDE_BASICSWC_BASICSWC_H_ */
