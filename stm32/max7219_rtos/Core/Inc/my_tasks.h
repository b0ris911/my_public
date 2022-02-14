#ifndef my_tasks_h
#define my_tasks_h

#include "my_head_files.h"

void vTaskTestLed(void *param);
void vTaskTestUart(void *param);
void vTaskTestI2C(void *param);
void vTaskMemory(void *param);

void vTaskGSCC(void *param);
u32 Get_systick(void);

#endif
