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
#define PI_MODEL_KHADAS_EDGE		9

#define WPI_FATAL	(1==1)
#define WPI_ALMOST	(1==2)

#define MODE_PINS            0
#define MODE_GPIO            1
#define MODE_GPIO_SYS        2
#define MODE_PHYS            3
#define MODE_PIFACE          4
#define MODE_UNINITIALISED  -1

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

#define VIM1_GPIO_PIN_BASE			400

#define VIM1_GPIODV_PIN_START		(VIM1_GPIO_PIN_BASE + 49)		//400+49=149
#define VIM1_GPIODV_PIN_END			(VIM1_GPIO_PIN_BASE + 78)		
#define VIM1_GPIOH_PIN_START		(VIM1_GPIO_PIN_BASE + 16)		//400+16=116
#define VIM1_GPIOH_PIN_END			(VIM1_GPIO_PIN_BASE + 25)
#define VIM1_GPIOAO_PIN_START		(VIM1_GPIO_PIN_BASE + 30)		//400+30=130
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

// Common offset for GPIO registers from each GPIO bank's base address
#define EDGE_GPIO_CON_OFFSET        0x04        // GPIO_SWPORTA_DDR
#define EDGE_GPIO_SET_OFFSET        0x00        // GPIO_SWPORTA_DR
#define EDGE_GPIO_GET_OFFSET        0x50        // GPIO_EXT_PORTA

#define EDGE_FUNC_GPIO          0b00        // Bit for IOMUX GPIO mode

// Common mmap block size for KHADAS-EDGE GRF register
#define EDGE_GRF_BLOCK_SIZE     0xF000

// GPIO{0, 1}
#define EDGE_PMUGRF_BASE            0xFF320000
#define EDGE_PMUGRF_IOMUX_OFFSET        0x0000      // GRF_GPIO0A_IOMUX
#define EDGE_PMUGRF_PUPD_OFFSET     0x0040      // PMUGRF_GPIO0A_P
		    
// GPIO{2, 3, 4}
#define EDGE_GRF_BASE           0xFF770000
#define EDGE_GRF_IOMUX_OFFSET       0xE000      // GRF_GPIO2A_IOMUX
#define EDGE_GRF_PUPD_OFFSET        0xE040      // GRF_GPIO2A_P
	 
// Offset to control GPIO clock
// Make 31:16 bit HIGH to enable the writing corresponding bit
#define EDGE_PMUCRU_BASE            0xFF750000
#define EDGE_PMUCRU_GPIO_CLK_OFFSET 0x0104      // PMUCRU_CLKGATE_COEDGE
					 
#define EDGE_CRU_BASE           0xFF760000
#define EDGE_CRU_GPIO_CLK_OFFSET        0x037C      // CRU_CLKGATE_CON31
			
#define EDGE_CLK_ENABLE         0b0
#define EDGE_CLK_DISABLE            0b1
						    
// Only for Linux kernel for now. Edit to 0 for Android
#ifndef __ANDROID__
#define EDGE_GPIO_PIN_BASE      1000
#else
#define EDGE_GPIO_PIN_BASE      0
#endif
								  
// GPIO1_A. 0,1,2,3,4,7
// GPIO1_B.     0,1,2,3,4,5
// GPIO1_C. 2,4,5,6
// GPIO1_D. 0
#define EDGE_GPIO_1_BASE            0xFF730000
							
// GPIO2_C. 0_B,1_B
#define EDGE_GPIO_2_BASE            0xFF780000
						
// GPIO4_C. 5,6
// GPIO4_D. 0,4,5,6
#define EDGE_GPIO_4_BASE            0xFF790000
						 
// Reserved
// GPIO{0, 3}
#define EDGE_GPIO_0_BASE            0xFF720000
#define EDGE_GPIO_3_BASE            0xFF788000


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

/*----------------------------------------------------------------------------------*/
/*define to edge*/
/* ADC file descriptor */
static int adcFds[2];

/* GPIO mmap control. Actual GPIO bank number. */
static volatile uint32_t *edge_gpio[5];
 
/* GRF(General Register Files) base addresses to control GPIO modes */
static volatile uint32_t *grf[2];
/* CRU(Clock & Reset Unit) base addresses to control CLK mode */
static volatile uint32_t *cru[2];
/*----------------------------------------------------------------------------------*/

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
	 -1,475,     //  0 |  1 :                     | GPIODV_26
	 -1, -1,     //  2 |  3 :
	422,423,     //  4 |  5 :
	425, -1,     //  6 |  7 :
	 -1, -1,     //  8 |  9 :
	424,436,     // 10 | 11 :
	 -1, -1,     // 12 | 13 :
	 -1,474,     // 14 | 15 :
	476, -1,     // 16 | 17 :           GPIODV_27 |
	 -1, -1,     // 18 | 19 :
	 -1,435,     // 20 | 21 :
	434, -1,     // 22 | 23 :
	421,432,     // 24 | 25 :            GPIOAO_1 | GPIOAO_2
	 -1, -1,     // 26 | 27 :
	 -1,473,     // 28 | 29 :
	 -1,421,     // 30 | 31 :
	 // Padding:
	  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //32to47
	  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //48to63
};

static const int phyToGpio_rev_vim1[64] = {
	//physical header pin number to native gpio number
	 -1,
	 -1, -1,     //  1 | 21 :
	 -1,474,     //  2 | 22 :
	 -1,473,     //  3 | 23 :
	 -1, -1,     //  4 | 24 :
	 -1,476,     //  5 | 25 :                    GND | I2C_SCK_B(GPIODV_27)
	 -1,475,     //  6 | 26 :                     5V | I2C_SDA_B(GPIODV_26)
	 -1, -1,     //  7 | 27 :                HUB_DM2 | 3.3V
	 -1, -1,     //  8 | 28 :                HUB_DP2 | GND
	 -1,423,     //  9 | 29 :                    GND | GPIOH_7
	 -1,422,     // 10 | 30 :                ADC_CH0 | GPIOH_6
	 -1,425,     // 11 | 31 :                    GND | GPIOH_9
	 -1,424,     // 12 | 32 :                ADC_CH2 | GPIOH_8
	 -1,436,     // 13 | 33 :                  SPDIF | GPIOAO_6
	 -1, -1,     // 14 | 34 :                    GND | GND
	435, -1,     // 15 | 35 : (GPIOAO_5)UART_RX_AO_B | PWM_AO_A(GPIOAO_3)
	434, -1,     // 16 | 36 : (GPIOAO_4)UART_TX_AO_B | RTC_CLK
	 -1,421,     // 17 | 37 :                    GND | GPIOH_5
	431, -1,     // 18 | 38 :     (GPIOAO_1)Linux_RX | PWR_EN
	432, -1,     // 19 | 39 :     (GPIOAO_2)Linux_Tx | PWM_F
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

static const int pinToGpio_rev_edge[64] = {
	// wiringPi number to native gpio number
  	120,  121,  //  0 |  1 :            GPIO3_D0 | GPIO3_D1
	122,  123,  //  2 |  3 :            GPIO3_D2 | GPIO3_D3
    124,  125,  //  4 |  5 :            GPIO3_D4 | GPIO3_D5
	126,  127,  //  6 |  7 :            GPIO3_D6 | GPIO3_D7
    64,  65,    //  8 |  9 : (GPIO2_A0) I2C2_SDA | I2C2_SCL (GPIO2_A1)
    50, 128,    // 10 | 11 :  (GPIO1_C2) SPI3_CS | I2S_CLK (GPIO4_A0)
    47,  48,    // 12 | 13 : (GPIO1_B7) SPI3_TXD | SPI3_RXD (GPIO1_C0)
    49,  -1,    // 14 | 15 : (GPIO1_C1) SPI3_CLK | UART_TX
    -1, 112,    // 16 | 17 :             UART_RX | SPDIF_TX (GPIO3_C0)
    -1,  -1,    // 18 | 19 :
    -1,  -1,    // 20 | 21 :  
    -1,  -1,    // 22 | 23 : 
    -1,  -1,    // 24 | 25 :                     | ADC_IN2
    -1,  -1,    // 26 | 27 : 
    -1,  -1,    // 28 | 29 :                     | ADC_IN3
    -1,  -1,    // 30 | 31 : 
	
	// Padding:
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 32...47
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 48...63
};

static const int phyToGpio_rev_edge[64] = {
	// physical header pin number to native gpio number
     -1,        //  0
     -1, -1,            //   1 | 21 :                        5V | GND
	 -1, 48,            //   2 | 22 :                        5V | SPI3_RXD (GPIO1_C0)
	 -1, 47,            //   3 | 23 :                  HOST1_DM | SPI3_TXD (GPIO1_B7)
     -1, -1,            //   4 | 24 :                  HOST1_DP | GND
     -1, 65,            //   5 | 25 :                       GND | I2C2_SCL (GPIO2_A1)
     -1, 64,            //   6 | 26 :                      3.3V | I2C2_SDA (GPIO2_A0)
     -1, -1,            //   7 | 27 :                  MCU_NRST | 3.3V
     -1, -1,            //   8 | 28 :                  MCU_SWIM | GND
     -1,120,            //   9 | 29 :                       GND | I2S0_SCLK (GPIO3_D0)
     -1,128,            //  10 | 30 :                   ADC_IN2 | I2S_CLK (GPIO4_A0)
     -1,127,            //  11 | 31 :                      1.8V | I2S0_SDO0 (GPIO3_D7)
     -1,122,            //  12 | 32 :                   ADC_IN3 | I2S0_LRCK_TX (GPIO3_D2)
    112,123,            //  13 | 33 :       (GPIO3_C0) SPDIF_TX | I2S0_SDI0 (GPIO3_D3)
     -1, -1,            //  14 | 34 :                       GND | GND
     50,126,            //  15 | 35 :        (GPIO1_C2) SPI3_CS | I2S0_SDI3SDO1 (GPIO3_D6)
     49,125,            //  16 | 36 :       (GPIO1_C1) SPI3_CLK | I2S0_SDI2SDO2 (GPIO3_D5)
     -1,124,            //  17 | 37 :                       GND | I2S0_SDI1SDO3 (GPIO3_D4)
     -1,121,            //  18 | 38 :                   UART_RX | I2S0_LRCK_RX (GPIO3_D1)
     -1, -1,            //  19 | 39 :                   UART_TX | MCU_PA1
     -1, -1,            //  20 | 40 :                      3.3V | GND
	
	
    // Not used
    -1, -1, -1, -1, -1, -1, -1, -1, // 41...48
	-1, -1, -1, -1, -1, -1, -1, -1, // 49...56
    -1, -1, -1, -1, -1, -1, -1  // 57...63
};


int khadas_found;
int piModel;

const int bcmToOGpioKhadas_vim1[64]={
	 -1, -1, -1, -1, -1, -1,434,436,
	424, -1, -1, -1, -1, -1, -1,476,
	 -1, -1,475,421, -1, -1, -1, -1,
	423,425, -1, -1, -1, -1, -1, -1,
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

const int bcmToOGpioKhadas_edge[64]={
	 -1, -1, -1, -1, -1, -1, 49,123,
	122, -1,124, -1,125, -1, -1, 65,
	121, -1, 64, -1, -1, -1, -1, -1,
	120,127, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
};

const int bcmToOGpioRPi_phy_xxx[64]={
	 -1, -1,  2,  3,  4,  5, 16, 33,
	 32,  2, 37, 12, 36, 17, 24, 25,
	 38,  6, 26, 18, -1, -1,  8, 28,
	 29, 31, -1,  7, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
	 -1, -1, -1, -1, -1, -1, -1, -1,
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
extern const int bcmToOGpioKhadas_edge[64];
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
