
// Burak G�N 
// 7/20/2017 
// DS18B20 �s� sens�r� k�t�phanesi
// Atollic



#ifndef _BG_ONE_WIRE_H 
#define _BG_ONE_WIRE_H

#include "stdio.h"


#define  READ_ROM		         0x33                                                          
#define  SKIP_ROM		         0xCC
#define  READ_SCRATCHPAD	     0xBE
#define  CONVERT_TEMP	   	     0x44
#define  SEARCH_ROM              0xF0
#define  MATCH_ROM               0x55
#define  WRITE_SCRATCHPAD        0x4E
#define  UNUSED                  0x00

#define  SET_RESOLUTION_9_BIT    0x1F
#define  SET_RESOLUTION_10_BIT   0x3F
#define  SET_RESOLUTION_11_BIT   0x5F
#define  SET_RESOLUTION_12_BIT   0x7F
 
// temp calculation time in ms according to resolution 
#define DELAY_RESOLUTION_10_BIT  94
#define DELAY_RESOLUTION_11_BIT  188
#define DELAY_RESOLUTION_12_BIT  376
#define DELAY_RESOLUTION_13_BIT  751

#ifndef delayResolution
#define delayResolution DELAY_RESOLUTION_10_BIT
#endif

/* stm32f429zi kart�nda G portunun 2. pini kullan�lm��t�r.
Bunun de�i�tirilmesi durumunda clock_enable ve pin ayarlar� d�zeltilmelidir */




#define enableClock         RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN ;    //saat �reteci aktif

#define defPinAsOutput      GPIOG-> MODER |= GPIO_MODER_MODE2_0;      //0_��k�s
#define defPinAsInput       GPIOG->IDR // MODER |=GPIO_MODER_MODE2_1;

#define getPinValue         (((GPIOG)->IDR & (GPIO_IDR_ID2)) == 0 ? 0 : 1)

#define defPinOutputType    GPIOG->OTYPER &= ~(GPIO_OTYPER_OT_2);
#define defPinInputType     GPIOG->PUPDR |= GPIO_PUPDR_PUPD2_1;

#define setPinHigh	        GPIOG ->BSRR  |= GPIO_BSRR_BS_2;
#define setPinLow           GPIOG ->BSRR  |= GPIO_BSRR_BS_2<<16;





 void     ResetPulse(void);
 void     SendByte(uint8_t  val);
 void     WriteBitReset(void);
 void     WriteBitSet(void);
 uint8_t  ReadByte(void);
 void     ReadScratchpad(void);
 void     ReadROM(void);
 void     StartConversion(void);
 void     ReadTemperature(void);





#endif  // _BG_ONE_WIRE_H







