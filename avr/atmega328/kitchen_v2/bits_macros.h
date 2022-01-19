#ifndef BITS_MACROS_
#define BITS_MACROS_
/***********************************************************
//BITS MACROS
//PASHGAN 2009
//CHIPENABLE.RU
//
//reg : ��� ����������, ��������
//bit : ������� ����
//val : 0 ��� 1
************************************************************/
#define Bit(bit)  (1<<(bit))

#define CB(reg, bit)       reg &= (~(1<<(bit)))
//������: CB(PORTB, 1); //�������� 1-� ��� PORTB

#define SB(reg, bit)          reg |= (1<<(bit))
//������: SB(PORTB, 3); //���������� 3-� ��� PORTB

#define SetBitVal(reg, bit, val) do{if ((val&1)==0) reg &= (~(1<<(bit)));\
                                  else reg |= (1<<(bit));}while(0)
//������: SetBitVal(PORTB, 3, 1); //���������� 3-� ��� PORTB
//	  SetBitVal(PORTB, 2, 0); //�������� 2-� ��� PORTB

#define BIC(reg, bit)    ((reg & (1<<(bit))) == 0)
//������: if (BIC(PORTB,1)) {...} //���� ��� ������

#define BIS(reg, bit)       ((reg & (1<<(bit))) != 0)
//������: if(BIS(PORTB,2)) {...} //���� ��� ����������

#define IB(reg, bit)	  reg ^= (1<<(bit))
//������: IB(PORTB, 1); //������������� 1-� ��� PORTB

#endif//BITS_MACROS_







