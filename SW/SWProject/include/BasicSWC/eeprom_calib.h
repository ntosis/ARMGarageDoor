/*
 * eeprom_calib.h
 *
 *  Created on: Jul 5, 2016
 *      Author: unix
 */

#ifndef EEPROM_CALIB_H_
#define EEPROM_CALIB_H_

#define _start 0x800C000

// Create structure
typedef struct {
	float K_P_Htng;
    uint16_t K_I_Htng;
    uint16_t K_D_Htng;
    uint16_t K_P_Coolg;
    uint16_t K_I_Coolg;
    uint16_t K_D_Coolg;
    uint16_t virtualAddress;
    uint8_t  oneLevelSystem_C;
    uint8_t smartCnt_C;
    uint8_t debugInfosFlag_C;
    uint8_t statusOfThisBlock;
} CAL_PARAM;

void initCAL(void);
void checkForaValidBlockInEEm(void);
void copyBlockFromEEmtoRam(void);
void copyInitCALtoRam(void);

extern void  *pInitCAL;
extern uint8_t *a_ptr;


/*
#define K_P_Htng (p->K_P_Htng)
#define K_I_Htng (p->K_I_Htng)
#define K_D_Htng (p->K_D_Htng)
#define K_P_Coolg (p->K_P_Coolg)
#define K_I_Coolg (p->K_I_Coolg)
#define K_D_Coolg (p->K_D_Coolg)
#define oneLevelSystem_C (p->oneLevelSystem_C)
#define smartCnt_C (p->smartCnt_C)
#define debugInfosFlag_C p->debugInfosFlag_C)
*/
#endif /* EEPROM_CALIB_H_ */

