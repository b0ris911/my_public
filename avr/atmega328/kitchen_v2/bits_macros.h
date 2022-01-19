#ifndef BITS_MACROS_
#define BITS_MACROS_
/***********************************************************
//BITS MACROS
//PASHGAN 2009
//CHIPENABLE.RU
//
//reg : имя переменной, регистра
//bit : позиция бита
//val : 0 или 1
************************************************************/
#define Bit(bit)  (1<<(bit))

#define CB(reg, bit)       reg &= (~(1<<(bit)))
//пример: CB(PORTB, 1); //сбросить 1-й бит PORTB

#define SB(reg, bit)          reg |= (1<<(bit))
//пример: SB(PORTB, 3); //установить 3-й бит PORTB

#define SetBitVal(reg, bit, val) do{if ((val&1)==0) reg &= (~(1<<(bit)));\
                                  else reg |= (1<<(bit));}while(0)
//пример: SetBitVal(PORTB, 3, 1); //установить 3-й бит PORTB
//	  SetBitVal(PORTB, 2, 0); //сбросить 2-й бит PORTB

#define BIC(reg, bit)    ((reg & (1<<(bit))) == 0)
//пример: if (BIC(PORTB,1)) {...} //если бит очищен

#define BIS(reg, bit)       ((reg & (1<<(bit))) != 0)
//пример: if(BIS(PORTB,2)) {...} //если бит установлен

#define IB(reg, bit)	  reg ^= (1<<(bit))
//пример: IB(PORTB, 1); //инвертировать 1-й бит PORTB

#endif//BITS_MACROS_







