#include "eep_328.h"

u08 what_write;
u08 address;
u16 *pdata_x16;
s32 *pdata_x32;
s08  *parray_x8;
s16 *parray_x16;
s32 *parray_x32;
u08 num_elements;
//--------------------------------------
ISR (EE_READY_vect) {
volatile static uint8_t step=0,bit0=0,bit1=0,bit2=0,bit3=0;
switch (what_write) {
	case BYTE_X8:
		EECR |= (1<<EEMPE);
		EECR |= (1<<EEPE);			
		EECR &= ~(1<<EERIE);		
	break;
	case BYTE_X16:
		switch (step) {
			case 0:
				bit1=(*pdata_x16)>>8;
				bit0=*pdata_x16;
				EEARL=address++;												
				EEDR=bit1;				
				EECR |= (1<<EEMPE);
				EECR |= (1<<EEPE);
				step=1;			
			break;		
			case 1:
				EEARL=address;								
				EEDR=bit0;				
				EECR |= (1<<EEMPE);
				EECR |= (1<<EEPE);
				EECR &= ~(1<<EERIE);		
				step=0;			
			break;	
		}		
	break;
	
//------------------------------
	}//sw	
}//ISR			
//---------------------------------------
void WriteArrayEeprom_x8 (uint8_t kol_vo_elements,u08 adress,int8_t *parray2write) {
	while(EECR & (1<<EEPE));
	what_write=ARRAY_X8;
	num_elements=kol_vo_elements;
	address=adress;
	parray_x8=parray2write;
	EECR |= (1<<EERIE);
}
//---------------------------------------
void ReadArrayEeprom_x8 (uint8_t kol_vo_elements,u08 adress,int8_t *parrayfromeep) {
	for (uint8_t i=kol_vo_elements;i!=0;i--) {
		EEARL=adress++;
		EECR |= (1<<EERE);
		*parrayfromeep++=EEDR;				
	}		
}
//---------------------------------------
void ReadEeprom_x8 (u08 adress,uint8_t *pdatafromeep) {
	EEARL=adress;
	EECR |= (1<<EERE);
	*pdatafromeep=EEDR;	
}
//---------------------------------------
void WriteEeprom_x8 (u08 adress,uint8_t *pdata2write) {
	while(EECR & (1<<EEPE));
	what_write=BYTE_X8;
	EEARL=adress;
	EEDR=*pdata2write;
	EECR |= (1<<EERIE);
}
