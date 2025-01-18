#ifndef ADC_H
#define ADC_H

#include "gd32f1x0.h"
#include "systick.h"

void AdcConfig(void);
void DacConfig(void);
void GetInsertedValue(void);
uint16_t GetAdcVbus(void);
uint16_t GetAdcTemp(void);

#endif
