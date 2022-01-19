#include "ds18b20.h"

extern OWIflags OWIStatus;
extern unsigned char *OWIDataBuffer;
extern s16 data_di;

s32 temperature;
s16 temp_data;

void ProcessDS18B20() {
	//if((work_mode==WORK)||(work_mode==ALARM)){}

/*! \brief  The state machine that controls communication on the 1-Wire bus
 *  
 *  This function is called from main every time the 1-Wire driver is not
 *  busy. The state machine will read the temperature from a DS1820 temperature
 *  sensor, crc check it, and put it in the global variable temperature if 
 *  everything is OK.
 */

    static u08 state = OWI_STATE_IDLE;
    static u08 buf[9];
    u08 i;
    u08 crc;	
    // If an error has occurred since last time, clear all flags and
    // return to idle state.
    if (OWIStatus.error) {
        state = OWI_STATE_IDLE;
        OWIStatus.allFlags = FALSE;
    }
    
    switch (state) {
        case OWI_STATE_IDLE: {
            // Send reset signal and update state.
            OWI_DetectPresence();
            state = OWI_STATE_DETECT_PRESENCE1;
            break;
        }

        case OWI_STATE_DETECT_PRESENCE1: {
            // If no presence was detected, go back to idle state.
            if(OWIStatus.presenceDetected == FALSE) {
                state = OWI_STATE_IDLE;
            }
            // If presence was detected, send Skip ROM and Start conversion
            // signals. 
            else {
                buf[0] = OWI_ROM_SKIP;
                buf[1] = DS1820_START_CONVERSION;
                OWI_TransmitData(buf, 16);
                state = OWI_STATE_WAIT_FOR_CONVERSION1;
            }
            break;
        }
		case OWI_STATE_WAIT_FOR_CONVERSION1: 
			StartGTimer(timer_delay_ds18b20,800);
			if(ExpGTimer(timer_delay_ds18b20)) {
				state = OWI_STATE_WAIT_FOR_CONVERSION2;
			}
		break;
		
		case OWI_STATE_WAIT_FOR_CONVERSION2:
               OWI_DetectPresence();
               state = OWI_STATE_DETECT_PRESENCE2;
		break;

        case OWI_STATE_DETECT_PRESENCE2: {
            // If no presence was detected, go back to idle state.
            if(OWIStatus.presenceDetected == FALSE) {
                state = OWI_STATE_IDLE;
            }
            // If presence was detected, send Skip ROM and Read scratchpad
            // signals. 
            else {
                buf[0] = OWI_ROM_SKIP;
                buf[1] = DS1820_READ_SCRATCHPAD;
                OWI_TransmitData(buf, 16);
                state = OWI_STATE_READ_SCRATCHPAD;   
            }
            break;
        }
    
        case OWI_STATE_READ_SCRATCHPAD: {
            // Read the 9 bytes of scratchpad data.
            OWI_ReceiveData(buf, 9 * 8);
            state = OWI_STATE_CHECK_CRC;
            break;
        }
    
        case OWI_STATE_CHECK_CRC: {
            // Compare the computed crc with the crc read from the 
            // scratchpad. 
            crc = 0;
            for(i = 0; i < 8; i++) {
                crc =  OWI_ComputeCRC8(buf[i], crc);
            }
            // If they match, update the temperature variable.
            if (crc == buf[8]) {
                temperature = buf[0] | (buf[1] << 8);                
                state = OWI_STATE_IDLE;

				temp_data=(temperature*10)/16;
				data_di=temp_data;
/*				LcdClear();
				LcdGoto(100);
				LcdString("T = ");		
				STrimConvert(tmp/10,3);
				LCD(3);
				LcdWriteData('.');
				TrimConvert(tmp%10,1);
				LCD(1);
*/	          }
            // If they don't match, go back to the second Reset to 
            // read the scratchpad again.
            else {
                OWI_DetectPresence();
                state = OWI_STATE_DETECT_PRESENCE2;
            }
            break;
        }
    }
}





