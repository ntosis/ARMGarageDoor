#include "stm32f1xx_hal.h"
#include "eeprom_calib.h"
#include "eeprom_em.h"
#include <string.h>
// Create variable in Flash with initial values
const CAL_PARAM InitCAL = {0.15,0x02,0x03,0x04,0x05,0x06,0x8888,0x07,0x08,0x09,0x10} ;
// Create pointer for the calibration parameters
void  *pInitCAL = &InitCAL;

CAL_PARAM CALinRAM;

void initCAL(void) {

    uint16_t retVal = EE_ReadBlockInEEm(&CALinRAM,sizeof(CAL_PARAM),0x8888);

    if(retVal==0) {
    	/*Address found*/
    	 if(CALinRAM.statusOfThisBlock==0x01) {

    		//ok

    	    }
    	    else {

    		//not ok

    	    }
    }
    else if(retVal==1){
    	/* Address no found */
    	//EE_WriteBlock(pInitCAL,sizeof(CAL_PARAM),0x8888);
    }
    else if(retVal==NO_VALID_PAGE) {

    }


}




