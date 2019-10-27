#include <string.h>
#include "stm32f1xx_hal.h"
#include "eeprom_calib.h"
#include "eeprom_em.h"
#include "crcModule.h"
// Create variable in Flash with initial values
const struct CAL_PARAM_tag InitCAL = {{0x00},{0.15,0x02,0x03,0x04,0x05,0x06,VIRTUALL_ADDRESS_OF_STRUCT,0x07,0x08,0x09,0x10,0x11}} ;
// Create pointer for the calibration parameters
void  *pInitCAL = &InitCAL;
struct CAL_PARAM_tag CALinRAM;

void initCAL(void) {

	for(int i=0; i<2; i++) {

	EE_WriteBlock(pInitCAL,sizeof(struct CAL_PARAM_tag));

	}

    uint16_t retVal = EE_ReadBlockInEEm(&CALinRAM,sizeof(CAL_PARAM),VIRTUALL_ADDRESS_OF_STRUCT);

    if(retVal==0) {
    	/*Address found*/

    	/* calculate the CRC */

    	uint32_t crcValue = calculateCRCfromStruct(&CALinRAM.data);

    	 if(CALinRAM.data_crc == crcValue) {

    		 /**/
    		 memset(&CALinRAM, (char)1, sizeof(struct CAL_PARAM_tag));
    	    }

    	 else {

    		//not ok
    		 memset(&CALinRAM, (char)0, sizeof(struct CAL_PARAM_tag));

    	    }
    }
    else if(retVal==1){
    	/* Address no found */
    	EE_WriteBlock(pInitCAL,sizeof(struct CAL_PARAM_tag));
    }
    else if(retVal==NO_VALID_PAGE) {

    }


}




