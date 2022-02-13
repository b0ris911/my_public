#include "my_func.h"
//---------------------------------------------------------
//---------------------------------------------------------
//---------------------------------------------------------
u08 InverseByte(u08 byte) {
    u08 ret = 0;
    for(s08 i=0;i<8;i++) {
        ret |= ((byte & (1 << i)) ? 1 : 0)<<(7 - i);
    }
    return ret;
}
//---------------------------------------------------------
void IB(GPIO_TypeDef *GPIOx, u16 GPIO_Pin){
  u32 odr;
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  /* get current Ouput Data Register value */
  odr = GPIOx->ODR;
  /* Set selected pins that were at low level, and reset ones that were high */
  GPIOx->BSRR = ((odr & GPIO_Pin) << 16) | (~odr & GPIO_Pin);
}
//---------------------------------------------------------
u08 ReadPin(GPIO_TypeDef *GPIOx, u16 GPIO_Pin) {
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  if ((GPIOx->IDR & GPIO_Pin) != 0) {
    return 1;
  }
  else {
    return 0;
  }
}
//---------------------------------------------------------
u16 sqrt_new (u32 L) {
    if (L < 2)
        return (u16) L;

    u32 rslt, div;

    rslt = L;
    div = L / 2;

    while (1) {
        div = (L / div + div ) / 2;

        if (rslt > div)
            rslt = div;
        else
            return (u16) rslt;
    }
}
