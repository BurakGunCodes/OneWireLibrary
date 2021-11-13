
#include "BG_1_Wire.h"

#include "delay.h"                            // DelayUs() kullan�m� i�in
#include "stdio.h"                            // sprintf() kullan�m� i�in

int ResetPulse()
{

    defPinAsOutput;
    defPinOutputType;
    setPinHigh;
    DelayUs(500);

    setPinLow; 
    DelayUs(500);

    setPinHigh;
    defPinInputType;
	defPinAsInput;
    DelayUs(50);

}

static void  SendByte(uint8_t  val)
{
    uint8_t             n;

    for (n=0; n<8; n++)
    {

        setPinLow;

        if (val & 1) 
        { 
            WriteBitSet(); 
        }
        else
        { 
            WriteBitReset(); 
        }

        DelayUs(5);
        val = val >> 1;
    }
}

void WriteBitSet()
{
	
    defPinAsOutput;
    setPinHigh;
	DelayUs(10);

    setPinLow;
	DelayUs(2);

    setPinHigh;
	DelayUs(10);
}

void WriteBitReset()
{

        defPinAsOutput;
        setPinHigh;
		DelayUs(10);

        setPinLow;
		DelayUs(100);

        setPinHigh;
		DelayUs(10);
}

static  uint8_t  ReadByte(void)
{
    uint8_t n;
    int     val = 0;

    for (n=0; n<8; n++)
    {
        val = val >> 1;
        setPinLow;
        defPinAsOutput;
        DelayUs(3);

        setPinHigh;
        defPinAsInput;
        DelayUs(10);

        if (getPinValue) 
        {
             val = val | 0x80;
        }

        DelayUs(50);
    }

    return  val;

}

int*  ReadScratchPad(void)
{
    uint8_t n;
    uint8_t pad[8];

    int     x[10];

    char    str[10];

    ResetPulse();
    DelayUs(100);
    SendByte(SKIP_ROM);
    SendByte(READ_SCRATCHPAD);

    for (n=0; n<8; n++)
    {
        pad[n] = ReadByte();
    }

    return pad;

}

int* ReadROM(void)
{
    uint8_t n;
    int rom[8];

    char    str[15];

    int     x[10] ;

    ResetPulse();
    DelayUs(100);
    SendByte(READ_ROM);

    for (n=0; n<8; n++)
    {
        rom[n] = ReadByte();
    }

    return rom ;

}

static void  StartConversion(void)
{

    ResetPulse();
    DelayUs(100);
    SendByte(SKIP_ROM);
    SendByte(CONVERT_TEMP);

    DelayUs(delayResolution) ;
}

int  ReadTemperature(void)
{

    uint8_t  temp;

    uint8_t  n;
    uint8_t  pad[8];

    int  x[10];
    int  ondalik;

    char str[15];

    ResetPulse();
    DelayUs(100);
    SendByte(SKIP_ROM);
    SendByte(READ_SCRATCHPAD);

    for (n=0; n<9; n++)
    {
        pad[n] = ReadByte();

    }

    temp = ( ( ( (pad[0] & 0xF0)>> 4) + (pad[1] << 4 ) ) ); // pad[1] * 16 ile << 4 ayn� i�lemi yapar 4 bit kayd�r�r
    
    return temp;

}


void SetResolution(uint8_t val){

    ResetPulse();
    DelayUs(100);
    SendByte(SKIP_ROM);
    SendByte(WRITE_SCRATCHPAD); // Yazma komutu g�nderildi
    SendByte(UNUSED);           // TL kullan�lmayacag� i�in 0x00 yolland�
    SendByte(UNUSED);           // TH kullan�lmayacag� i�in 0x00 yolland�
    SendByte(val);              // Cozunurluk bilgisi yolland�.
    ResetPulse();

    DelayUs(100);
    SendByte(COPY_SCRATCHPAD);
    DelayUs(16000);


    switch(val)
    {
        case 0x1F:
        delayResolution = DELAY_RESOLUTION_9_BIT;
        break;

        case 0x3F:
        delayResolution = DELAY_RESOLUTION_10_BIT;
        break;

        case 0x5F:
        delayResolution = DELAY_RESOLUTION_11_BIT;
        break;

        case 0x7F:
        delayResolution = DELAY_RESOLUTION_12_BIT;
        break;


    }








}



