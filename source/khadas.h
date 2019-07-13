#ifndef __KHADAS_H__
#define __KHADAS_H__

/* code from wiringPI/wiringPi.h */
#define PI_MODEL_UNKNOWN  0
#define PI_MODEL_A        1
#define PI_MODEL_B        2
#define PI_MODEL_BP       3
#define PI_MODEL_CM       4
#define PI_MODEL_AP       5
#define PI_MODEL_KHADAS_VIM1	  	6
#define PI_MODEL_KHADAS_VIM2	  	7
#define PI_MODEL_KHADAS_VIM3		8

#define WPI_FATAL	(1==1)
#define WPI_ALMOST	(1==2)

/* end of wiringPI/wiringPi.h */

/*cpoy from wiringPI/wiringPi.c */

#ifndef TRUE
#define TRUE	(1==1)
#define FALSE	(1==2)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

/****copy from wiringPI/vim1****/
#define VIM1_GPIO_MASK				(0xFFFFFF00)
#define VIM1_GPIO_BASE				0xc8834000
#define VIM1_GPIOAO_BASE			0xc8100000

#define VIM1_GPIO_PIN_BASE			100

#define VIM1_GPIODV_PIN_START		(VIM1_GPIO_PIN_BASE + 49)		//100+49=149
#define VIM1_GPIODV_PIN_END			(VIM1_GPIO_PIN_BASE + 78)		
#define VIM1_GPIOH_PIN_START		(VIM1_GPIO_PIN_BASE + 16)		//100+16=116
#define VIM1_GPIOH_PIN_END			(VIM1_GPIO_PIN_BASE + 25)
#define VIM1_GPIOAO_PIN_START		(VIM1_GPIO_PIN_BASE + 30)		//100+30=130
#define VIM1_GPIOAO_PIN_END			(VIM1_GPIO_PIN_BASE + 39)

#define VIM1_GPIODV_FSEL_REG_OFFSET			0x10C		//[29:0]
#define VIM1_GPIODV_OUTP_REG_OFFSET			0x10D		//[29:0]
#define VIM1_GPIODV_INP_REG_OFFSET			0x10E		//[29:0]
#define VIM1_GPIODV_PUPD_REG_OFFSET			0x13a		//[29:0]
#define VIM1_GPIODV_PUEN_REG_OFFSET			0x148		//[29:0]

#define VIM1_GPIOH_FSEL_REG_OFFSET			0x10F		//[29:20]
#define VIM1_GPIOH_OUTP_REG_OFFSET			0x110		//[29:20]
#define VIM1_GPIOH_INP_REG_OFFSET			0x111		//[29:20]
#define VIM1_GPIOH_PUPD_REG_OFFSET			0x13b		//[29:20]
#define VIM1_GPIOH_PUEN_REG_OFFSET			0x149		//[29:20]

#define VIM1_GPIOAO_FSEL_REG_OFFSET			0x009		//[9:0]
#define VIM1_GPIOAO_OUTP_REG_OFFSET			0x009		//[25:16]
#define VIM1_GPIOAO_INP_REG_OFFSET			0x00a		//[9:0]
#define VIM1_GPIOAO_PUPD_REG_OFFSET			
#define VIM1_GPIOAO_PUEN_REG_OFFSET


#define VIM1_MUX_0_REG_OFFSET			0x12C
#define VIM1_MUX_1_REG_OFFSET			0x12D
#define VIM1_MUX_2_REG_OFFSET			0x12E
#define VIM1_MUX_3_REG_OFFSET			0x12F
#define VIM1_MUX_4_REG_OFFSET			0x130
#define VIM1_MUX_5_REG_OFFSET			0x131
#define VIM1_MUX_6_REG_OFFSET			0x132
#define VIM1_MUX_7_REG_OFFSET			0x133
#define VIM1_MUX_8_REG_OFFSET			0x134
#define VIM1_MUX_9_REG_OFFSET			0x135

#define VIM1_AO_MUX_1_REG_OFFSET		0x005
#define VIM1_AO_MUX_2_REG_OFFSET		0x006

/****copy from wiringPI/vim2****/
#define VIM2_GPIO_MASK					(0xFFFFFF00)
#define VIM2_GPIO_BASE					0xc8834000
#define VIM2_GPIOAO_BASE				0xc8100000

#define VIM2_GPIO_PIN_BASE				200

#define VIM2_GPIODV_PIN_START			(VIM2_GPIO_PIN_BASE + 49) 	//200+49=249
#define VIM2_GPIODV_PIN_END				(VIM2_GPIO_PIN_BASE + 78)
#define VIM2_GPIOH_PIN_START			(VIM2_GPIO_PIN_BASE + 16)	//200+16=216
#define VIM2_GPIOH_PIN_END				(VIM2_GPIO_PIN_BASE + 25)
#define VIM2_GPIOAO_PIN_START			(VIM2_GPIO_PIN_BASE + 30)	//200+30=230
#define VIM2_GPIOAO_PIN_END				(VIM2_GPIO_PIN_BASE + 39)

#define VIM2_GPIODV_FSEL_REG_OFFSET		0x10C
#define VIM2_GPIODV_OUTP_REG_OFFSET		0x10D
#define VIM2_GPIODV_INP_REG_OFFSET		0x10E
#define VIM2_GPIODV_PUPD_REG_OFFSET     0x13a
#define VIM2_GPIODV_PUEN_REG_OFFSET     0x148

#define VIM2_GPIOH_FSEL_REG_OFFSET		0x10F		//[29:20]
#define VIM2_GPIOH_OUTP_REG_OFFSET		0x110
#define VIM2_GPIOH_INP_REG_OFFSET       0x111
#define VIM2_GPIOH_PUPD_REG_OFFSET		0x13b
#define VIM2_GPIOH_PUEN_REG_OFFSET      0x149

#define VIM2_GPIOAO_FSEL_REG_OFFSET     0x009
#define VIM2_GPIOAO_OUTP_REG_OFFSET     0x009       //[25:16]
#define VIM2_GPIOAO_INP_REG_OFFSET      0x00a
#define VIM2_GPIOAO_PUPD_REG_OFFSET
#define VIM2_GPIOAO_PUEN_REG_OFFSET	


#define VIM2_MUX_0_REG_OFFSET 			0x12C
#define VIM2_MUX_1_REG_OFFSET           0x12D
#define VIM2_MUX_2_REG_OFFSET           0x12E
#define VIM2_MUX_3_REG_OFFSET           0x12F
#define VIM2_MUX_4_REG_OFFSET           0x130
#define VIM2_MUX_5_REG_OFFSET           0x131
#define VIM2_MUX_6_REG_OFFSET           0x132
#define VIM2_MUX_7_REG_OFFSET           0x133
#define VIM2_MUX_8_REG_OFFSET           0x134
#define VIM2_MUX_9_REG_OFFSET           0x135

#define VIM2_AO_MUX_1_REG_OFFSET        0x005
#define VIM2_AO_MUX_2_REG_OFFSET        0x006

/****cpoy from wiringPI/vim3****/
#define VIM3_GPIO_MASK					(0xFFFFFF00)
#define VIM3_GPIO_BASE					0xff634000
#define VIM3_GPIOAO_BASE				0xff800000

#define VIM3_GPIO_PIN_BASE				300

#define VIM3_GPIOA_PIN_START			(VIM3_GPIO_PIN_BASE ) 	 	//300
#define VIM3_GPIOA_PIN_END				(VIM3_GPIO_PIN_BASE + 15)
#define VIM3_GPIOH_PIN_START			(VIM3_GPIO_PIN_BASE + 20)	//300+20=320
#define VIM3_GPIOH_PIN_END				(VIM3_GPIO_PIN_BASE + 29)
#define VIM3_GPIOZ_PIN_START			(VIM3_GPIO_PIN_BASE + 30)	//300+30=330
#define VIM3_GPIOZ_PIN_END				(VIM3_GPIO_PIN_BASE + 45)
#define VIM3_GPIOAO_PIN_START			(VIM3_GPIO_PIN_BASE + 50)	//300+50=350
#define VIM3_GPIOAO_PIN_END				(VIM3_GPIO_PIN_BASE + 59)

#define VIM3_GPIOA_FSEL_REG_OFFSET		0x120
#define VIM3_GPIOA_OUTP_REG_OFFSET		0x121
#define VIM3_GPIOA_INP_REG_OFFSET		0x122
#define VIM3_GPIOA_PUPD_REG_OFFSET		0x13F
#define VIM3_GPIOA_PUEN_REG_OFFSET    	0x14D
#define VIM3_GPIOA_DS_REG_5A_OFFSET   	0x1D6
#define VIM3_GPIOA_MUX_D_REG_OFFSET   	0x1BD
#define VIM3_GPIOA_MUX_E_REG_OFFSET   	0x1BE


#define VIM3_GPIOH_FSEL_REG_OFFSET		0x119		
#define VIM3_GPIOH_OUTP_REG_OFFSET		0x11A
#define VIM3_GPIOH_INP_REG_OFFSET       0x11B
#define VIM3_GPIOH_PUPD_REG_OFFSET		0x13D
#define VIM3_GPIOH_PUEN_REG_OFFSET      0x14B
#define VIM3_GPIOH_DS_REG_3A_OFFSET   	0x1D4
#define VIM3_GPIOH_MUX_B_REG_OFFSET		0x1BB

#define VIM3_GPIOAO_FSEL_REG_OFFSET     0x009
#define VIM3_GPIOAO_OUTP_REG_OFFSET     0x00d       
#define VIM3_GPIOAO_INP_REG_OFFSET      0x00a		//'0' is set to output ,defalut is input
#define VIM3_GPIOAO_PUPD_REG_OFFSET		0x00b
#define VIM3_GPIOAO_PUEN_REG_OFFSET		0x00c
#define VIM3_GPIOAO_DS_REG_A_OFFSET		0x007
#define VIM3_GPIOAO_MUX_0_REG_OFFSET	0x005
#define VIM3_GPIOAO_MUX_1_REG_OFFSET	0x006


#define VIM3_GPIOZ_FSEL_REG_OFFSET		0x11C		
#define VIM3_GPIOZ_OUTP_REG_OFFSET		0x11D
#define VIM3_GPIOZ_INP_REG_OFFSET       0x11E
#define VIM3_GPIOZ_PUPD_REG_OFFSET		0x14C
#define VIM3_GPIOZ_PUEN_REG_OFFSET      0x13E
#define VIM3_GPIOZ_DS_REG_4_OFFSET   	0x1D5
#define VIM3_GPIOZ_MUX_B_REG_OFFSET		0x1B6

#ifdef DEFINE_KHADAS_VARS

#define INPUT 	1
#define OUTPUT	0
#define ALT0	4

/* from wiringPI/GPIO */
#define PAGE_SIZE	(4*1024)
#define BLOCK_SIZE	(4*1024)

#define HIGH 1
#define LOW  0

#define PUD_OFF  0
#define PUD_DOWN 1
#define PUD_UP   2

/*cpoy from wiringPI/common */
#define MAXPINCOUNT 40
extern const int (*pin_to_gpio)[MAXPINCOUNT+1];

int wiringPiReturnCodes = FALSE;

static volatile uint32_t *gpio, *gpio1;

static int sysFdData [64] = {
     -1, -1, -1, -1, -1, -1, -1, -1, // 0...7
     -1, -1, -1, -1, -1, -1, -1, -1, // 8...15
     -1, -1, -1, -1, -1, -1, -1, -1, // 16...23
     -1, -1, -1, -1, -1, -1, -1, -1, // 24...31
     -1, -1, -1, -1, -1, -1, -1, -1, // 32...39
     -1, -1, -1, -1, -1, -1, -1, -1, // 40...47
     -1, -1, -1, -1, -1, -1, -1, -1, // 48...55
     -1, -1, -1, -1, -1, -1, -1, -1, // 56...63
};

static int sysFdIrqType [64] = {
     -1, -1, -1, -1, -1, -1, -1, -1, // 0...7
     -1, -1, -1, -1, -1, -1, -1, -1, // 8...15
     -1, -1, -1, -1, -1, -1, -1, -1, // 16...23
     -1, -1, -1, -1, -1, -1, -1, -1, // 24...31
     -1, -1, -1, -1, -1, -1, -1, -1, // 32...39
     -1, -1, -1, -1, -1, -1, -1, -1, // 40...47
     -1, -1, -1, -1, -1, -1, -1, -1, // 48...55
     -1, -1, -1, -1, -1, -1, -1, -1, // 56...63
};

static const int pinToGpio_rev_vim1[64] = {
	//wiringPi number to native gpio number
	 -1,175,     //  0 |  1 :                     | GPIODV_26
	 -1, -1,     //  2 |  3 :
	122,123,     //  4 |  5 :
	125, -1,     //  6 |  7 :
	 -1, -1,     //  8 |  9 :
	124,136,     // 10 | 11 :
	 -1, -1,     // 12 | 13 :
	 -1,174,     // 14 | 15 :
	176, -1,     // 16 | 17 :           GPIODV_27 |
	 -1, -1,     // 18 | 19 :
	 -1,135,     // 20 | 21 :
	134, -1,     // 22 | 23 :
	121,132,     // 24 | 25 :            GPIOAO_1 | GPIOAO_2
	 -1, -1,     // 26 | 27 :
	 -1,173,     // 28 | 29 :
	 -1,121,     // 30 | 31 :
	 // Padding:
	  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //32to47
	  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //48to63
};

static const int phyToGpio_rev_vim1[64] = {
	//physical header pin number to native gpio number
	 -1,
	 -1, -1,     //  1 | 21 :
	 -1,174,     //  2 | 22 :
	 -1,173,     //  3 | 23 :
	 -1, -1,     //  4 | 24 :
	 -1,176,     //  5 | 25 :                    GND | I2C_SCK_B(GPIODV_27)
	 -1,175,     //  6 | 26 :                     5V | I2C_SDA_B(GPIODV_26)
	 -1, -1,     //  7 | 27 :                HUB_DM2 | 3.3V
	 -1, -1,     //  8 | 28 :                HUB_DP2 | GND
	 -1,123,     //  9 | 29 :                    GND | GPIOH_7
	 -1,122,     // 10 | 30 :                ADC_CH0 | GPIOH_6
	 -1,125,     // 11 | 31 :                    GND | GPIOH_9
	 -1,124,     // 12 | 32 :                ADC_CH2 | GPIOH_8
	 -1,136,     // 13 | 33 :                  SPDIF | GPIOAO_6
	 -1, -1,     // 14 | 34 :                    GND | GND
	135, -1,     // 15 | 35 : (GPIOAO_5)UART_RX_AO_B | PWM_AO_A(GPIOAO_3)
	134, -1,     // 16 | 36 : (GPIOAO_4)UART_TX_AO_B | RTC_CLK
	 -1,121,     // 17 | 37 :                    GND | GPIOH_5
	121, -1,     // 18 | 38 :     (GPIOAO_1)Linux_RX | PWR_EN
	122, -1,     // 19 | 39 :     (GPIOAO_2)Linux_Tx | PWM_F
	 -1, -1,     // 20 | 40 :                   3.3V | GND
	 //  Not used
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1,                             //41-63
};

static const int pinToGpio_rev_vim2[64] = {
	//wiringPi number to native gpio number
	270,275,        //   0 | 1  :                     GPIODV_21 | GPIODV_26
	271,272,        //   2 | 3  :                     GPIODV_22 | GPIODV_22
	222,223,        //   4 | 5  : 
	225, -1,        //   6 | 7  :                       GPIOH_9 |
	 -1, -1,        //   8 | 9  :                               |
	224,236,        //  10 | 11 :                       GPIOH_8 | GPIOAO_6
	 -1, -1,        //  12 | 13 :                               |
	 -1,274,        //  14 | 15 :                               |
	276, -1,        //  16 | 17 :                     GPIODV_27 |
	 -1, -1,        //  18 | 19 :                               |
	 -1,235,        //  20 | 21 :                               | GPIOAO_5
	234, -1,        //  22 | 23 :                      GPIOAO_4 |
	231,230,        //  24 | 25 :                      GPIOAO_1 | GPIOAO_0
	 -1, -1,        //  26 | 27 :                               |
	262,273,        //  28 | 29 :                     GPIODV_13 |
	278,221,        //  30 | 31 :                               |
	// Padding:
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //32to47
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //48to63
};

static const int phyToGpio_rev_vim2[64] = {
	//physical header pin number to native gpio number
	 -1,
	 -1, -1,            //   1 | 21 :                        5V | GND
	 -1,274,            //   2 | 22 :                        5V | GPIODV_25
	 -1,273,            //   3 | 23 :                    USB_DM | GPIODV_24
	 -1, -1,            //   4 | 24 :                    USB_DP | GND
	 -1,276,            //   5 | 25 :                       GND | GPIODV_27
	270,275,            //   6 | 26 :                 GPIODV_21 | GPIODV_26
	271, -1,            //   7 | 27 :                 GPIODV_22 | 3.3V
	272, -1,            //   8 | 28 :                 GPIODV_23 | GND
	 -1,223,            //   9 | 29 :                       GND | GPIOH7
	 -1,222,            //  10 | 30 :                      ADC0 | GPIOH6
	 -1,225,            //  11 | 31 :                      1.8V | GPIOH9
	 -1,224,            //  12 | 32 :                      ADC1 | GPIOH8
	 -1,236,            //  13 | 33 :                     SPDIF | GPIOAO_6
	 -1, -1,            //  14 | 34 :                       GND | GND
	235,278,            //  15 | 35 :    (GPIOAO_5)UART_RX_AO_B | GPIODV_29
	234, -1,            //  16 | 36 :    (GPIOAO_4)UART_TX_AO_B | RTC_CLK
	 -1,221,            //  17 | 37 :                       GND | GPIOH5
	231, -1,            //  18 | 38 :        (GPIOAO_1)Linux_RX | EXP_INT
	230,262,            //  19 | 39 :        (GPIOAO_0)Linux_TX | GPIODV_13
	 -1, -1,            //  20 | 40 :                      3.3V | GND
	 //Not used
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1,                                        //41-63
};

static const int pinToGpio_rev_vim3[64] = {
	//wiringPi number to native gpio number
	 -1,353,        //   0 | 1  :                               | GPIOAO_3
	 -1, -1,        //   2 | 3  :                               |
	300,301,        //   4 | 5  :                               | GPIOA_1
	303, -1,        //   6 | 7  :                       GPIOA_3 |
	 -1, -1,        //   8 | 9  :                               |
	302,304,        //  10 | 11 :                       GPIOA_2 | GPIOA_4
	 -1, -1,        //  12 | 13 :                               |
	 -1,315,        //  14 | 15 :                               |
	352, -1,        //  16 | 17 :                      GPIOAO_2 |
	 -1, -1,        //  18 | 19 :                               |
	 -1,326,        //  20 | 21 :                               | GPIOH_6
	327, -1,        //  22 | 23 :                       GPIOH_7 |
	351,350,        //  24 | 25 :                      GPIOAO_1 | GPIOAO_0
	 -1, -1,        //  26 | 27 :                               |
	 -1,314,        //  28 | 29 :                               |
	 -1,324,        //  30 | 31 :                               |
	// Padding:
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //32to47
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //48to63
};

static const int phyToGpio_rev_vim3[64] = {
	//physical header pin number to native gpio number
	 -1,
	 -1, -1,            //   1 | 21 :                        5V | GND
	 -1,315,            //   2 | 22 :                        5V | GPIOA_15
	 -1,314,            //   3 | 23 :                    USB_DM | GPIOA_14
	 -1, -1,            //   4 | 24 :                    USB_DP | GND
	 -1,352,            //   5 | 25 :                       GND | GPIOAO_2
	 -1,353,            //   6 | 26 :                    MCU3.3 | GPIOAO_3
	 -1, -1,            //   7 | 27 :                   MCUNrST | 3.3V
	 -1, -1,            //   8 | 28 :                   MCUSWIM | GND
	 -1,301,            //   9 | 29 :                       GND | GPIOA_1
	 -1,300,            //  10 | 30 :                      ADC0 | GPIOA_0
	 -1,303,            //  11 | 31 :                      1.8V | GPIOA_3
	 -1,302,            //  12 | 32 :                      ADC1 | GPIOA_2
	 -1,304,            //  13 | 33 :                     SPDIF | GPIOA_4
	 -1, -1,            //  14 | 34 :                       GND | GND
	326, -1,            //  15 | 35 :     (GPIOH_6)UART_RX_AO_B | PWM-F
	327, -1,            //  16 | 36 :     (GPIOH_7)UART_TX_AO_B | RTC_CLK
	 -1,324,            //  17 | 37 :                       GND | GPIOH_4
	351, -1,            //  18 | 38 :        (GPIOAO_1)Linux_RX | MCUFA_1
	350, -1,            //  19 | 39 :        (GPIOAO_0)Linux_TX | GPIOZ_15
	 -1, -1,            //  20 | 40 :                      3.3V | GND
	 //Not used
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1,                                        //41-63
};

int khadas_found;
int piModel;

const int bcmToOGpioKhadas_vim1[64]={
	 -1, -1, -1, -1, -1, -1,134,136,
	124, -1, -1, -1, -1, -1, -1,176,
	 -1, -1,175,121, -1, -1, -1, -1,
	123,125, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1
};

const int bcmToOGpioKhadas_vim2[64]={
	 -1, -1, -1, -1, -1, -1,234,236,
	224, -1, -1, -1, -1, -1, -1,276,
	 -1,270,275,231, -1, -1,272, -1,
	223,225, -1,271, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1
};

const int bcmToOGpioKhadas_vim3[64]={
	 -1, -1, -1, -1, -1,326,327,304,
	302, -1, -1, -1, -1, -1, -1,352,
	 -1, -1,353,351, -1, -1, -1, -1,
	301,303, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1
};

const int bcmToOGpioRPi[64]={
	 0, 1, 2, 3, 4, 5, 6, 7, 
	 8, 9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35,36,37,38,39,
	40,41,42,43,44,45,46,47,
	48,49,50,51,52,53,54,55,
	56,57,58,59,60,61,62,63
};

const int (*bcm_to_khadasgpio)[64];

#else

extern int khadas_found;
extern int piModel;
extern const int bcmToOGpioKhadas_vim1[64];
extern const int bcmToOGpioKhadas_vim2[64];
extern const int bcmToOGpioKhadas_vim3[64];
extern const int bcmToOGpioRPi[64];
extern const int (*bcm_to_khadasgpio)[64];

int wiringPiSetupKhadas(void);
void wiringPiCleanupKhadas(void);
void pinModeKhadas(int pin, int mode);
void pullUpDnControlKhadas(int pin, int pud);
int digitalReadKhadas(int pin);
void digitalWriteKhadas(int pin, int value);
int analogReadKhadas(int pin);
void analogWriteKhadas(int pin, int value);
int pinGetModeKhadas(int pin);
void setInfoKhadas(char *hardware, void *vinfo);
void setMappingPtrsKhadas(void);

#endif

#endif
