#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/mman.h>

#include "cpuinfo.h"

#define DEFINE_KHADAS_VARS
#include "khadas.h"

int wiringPiFailure (int fatal, const char *message, ...)
{
	va_list argp ;
	char buffer [1024] ;

	if (!fatal && wiringPiReturnCodes)
		return -1 ;

	va_start (argp, message) ;
	vsnprintf (buffer, 1023, message, argp) ;
	va_end (argp) ;

	fprintf (stderr, "%s", buffer) ;
	exit (EXIT_FAILURE) ;

	return 0 ;
}

static int gpioToGPSETReg(int pin)
{
	if(piModel == PI_MODEL_KHADAS_VIM1){
		if(pin >= VIM1_GPIODV_PIN_START && pin <= VIM1_GPIODV_PIN_END)
			return VIM1_GPIODV_OUTP_REG_OFFSET;
		if(pin >= VIM1_GPIOH_PIN_START && pin <= VIM1_GPIOH_PIN_END)
			return VIM1_GPIOH_OUTP_REG_OFFSET;
		if(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)
			return VIM1_GPIOAO_OUTP_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		if(pin >= VIM2_GPIODV_PIN_START && pin <= VIM2_GPIODV_PIN_END)
			return VIM2_GPIODV_OUTP_REG_OFFSET;
		if(pin >= VIM2_GPIOH_PIN_START && pin <= VIM2_GPIOH_PIN_END)
			return VIM2_GPIOH_OUTP_REG_OFFSET;
		if(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)
			return VIM2_GPIOAO_OUTP_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM3){
		if(pin >= VIM3_GPIOA_PIN_START && pin <= VIM3_GPIOA_PIN_END)
			return VIM3_GPIOA_OUTP_REG_OFFSET;
		if(pin >= VIM3_GPIOH_PIN_START && pin <= VIM3_GPIOH_PIN_END)
			return VIM3_GPIOH_OUTP_REG_OFFSET;
		if(pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)
			return VIM3_GPIOAO_OUTP_REG_OFFSET;
		if(pin >= VIM3_GPIOZ_PIN_START && pin <= VIM3_GPIOZ_PIN_END)
			return VIM3_GPIOZ_OUTP_REG_OFFSET;
	}
	return -1;
}

static int  gpioToGPLEVReg (int pin)
{
	if(piModel == PI_MODEL_KHADAS_VIM3){
		if(pin >= VIM3_GPIOA_PIN_START && pin <= VIM3_GPIOA_PIN_END)
			return VIM3_GPIOA_INP_REG_OFFSET;
		if(pin >= VIM3_GPIOH_PIN_START && pin <= VIM3_GPIOH_PIN_END)
			return VIM3_GPIOH_INP_REG_OFFSET;
		if(pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)
			return VIM3_GPIOAO_INP_REG_OFFSET;
		if(pin >= VIM3_GPIOZ_PIN_START && pin <= VIM3_GPIOZ_PIN_END)
			return VIM3_GPIOZ_INP_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		if(pin >= VIM2_GPIODV_PIN_START && pin <= VIM2_GPIODV_PIN_END)
			return VIM2_GPIODV_INP_REG_OFFSET;
		if(pin >= VIM2_GPIOH_PIN_START && pin <= VIM2_GPIOH_PIN_END)
			return VIM2_GPIOH_INP_REG_OFFSET;
		if(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)
			return VIM2_GPIOAO_INP_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM1){
		if(pin >= VIM1_GPIODV_PIN_START && pin <= VIM1_GPIODV_PIN_END)
			return VIM1_GPIODV_INP_REG_OFFSET;
		if(pin >= VIM1_GPIOH_PIN_START && pin <= VIM1_GPIOH_PIN_END)
			return VIM1_GPIOH_INP_REG_OFFSET;
		if(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)
			return VIM1_GPIOAO_INP_REG_OFFSET;
	}
	return -1;
}

static int  gpioToPUENReg(int pin)
{
	if(piModel == PI_MODEL_KHADAS_VIM1){
		if(pin >= VIM1_GPIODV_PIN_START && pin <= VIM1_GPIODV_PIN_END)
			return VIM1_GPIODV_PUEN_REG_OFFSET;
		if(pin >= VIM1_GPIOH_PIN_START && pin <= VIM1_GPIOH_PIN_END)
			return VIM1_GPIOH_PUEN_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		if(pin >= VIM2_GPIODV_PIN_START && pin <= VIM2_GPIODV_PIN_END)
			return VIM2_GPIODV_PUEN_REG_OFFSET;
		if(pin >= VIM2_GPIOH_PIN_START && pin <= VIM2_GPIOH_PIN_END)
			return VIM2_GPIOH_PUEN_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM3){
		if(pin >= VIM3_GPIOA_PIN_START && pin <= VIM3_GPIOA_PIN_END)
			return VIM3_GPIOA_PUEN_REG_OFFSET;
		if(pin >= VIM3_GPIOH_PIN_START && pin <= VIM3_GPIOH_PIN_END)
			return VIM3_GPIOH_PUEN_REG_OFFSET;
		if(pin >= VIM3_GPIOZ_PIN_START && pin <= VIM3_GPIOZ_PIN_END)
			return VIM3_GPIOZ_PUEN_REG_OFFSET;
		if(pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)
			return VIM3_GPIOAO_PUEN_REG_OFFSET;
	}
	return -1;
}

static int  gpioToPUPDReg (int pin)
{
	if(piModel == PI_MODEL_KHADAS_VIM1){
		if(pin >= VIM1_GPIODV_PIN_START && pin <= VIM1_GPIODV_PIN_END)
			return VIM1_GPIODV_PUPD_REG_OFFSET;
		if(pin >= VIM1_GPIOH_PIN_START && pin <= VIM1_GPIOH_PIN_END)
			return VIM1_GPIOH_PUPD_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		if(pin >= VIM2_GPIODV_PIN_START && pin <= VIM2_GPIODV_PIN_END)
			return VIM2_GPIODV_PUPD_REG_OFFSET;
		if(pin >= VIM2_GPIOH_PIN_START && pin <= VIM2_GPIOH_PIN_END)
			return VIM2_GPIOH_PUPD_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM3){
		if(pin >= VIM3_GPIOA_PIN_START && pin <= VIM3_GPIOA_PIN_END)
			return VIM3_GPIOA_PUPD_REG_OFFSET;
		if(pin >= VIM3_GPIOH_PIN_START && pin <= VIM3_GPIOH_PIN_END)
			return VIM3_GPIOH_PUPD_REG_OFFSET;
		if(pin >= VIM3_GPIOZ_PIN_START && pin <= VIM3_GPIOZ_PIN_END)
			return VIM3_GPIOZ_PUPD_REG_OFFSET;
		if(pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)
			return VIM3_GPIOAO_PUPD_REG_OFFSET;
	}
	return -1;
}

static int  gpioToShiftReg(int pin)
{
	if(piModel == PI_MODEL_KHADAS_VIM1){
		if(pin >= VIM1_GPIODV_PIN_START && pin <= VIM1_GPIODV_PIN_END)
			return pin - VIM1_GPIODV_PIN_START;
		if(pin >= VIM1_GPIOH_PIN_START && pin <= VIM1_GPIOH_PIN_END)
			return pin - VIM1_GPIOH_PIN_START +20;
		if(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)
			return pin - VIM1_GPIOAO_PIN_START;
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		if(pin >= VIM2_GPIODV_PIN_START && pin <= VIM2_GPIODV_PIN_END)
			return pin - VIM2_GPIODV_PIN_START;
		if(pin >= VIM2_GPIOH_PIN_START && pin <= VIM2_GPIOH_PIN_END)
			return pin - VIM2_GPIOH_PIN_START +20;
		if(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)
			return pin - VIM2_GPIOAO_PIN_START;
	}else if(piModel == PI_MODEL_KHADAS_VIM3){
		if(pin >= VIM3_GPIOA_PIN_START && pin <= VIM3_GPIOA_PIN_END)
			return pin - VIM3_GPIOA_PIN_START;
		if(pin >= VIM3_GPIOH_PIN_START && pin <= VIM3_GPIOH_PIN_END)
			return pin - VIM3_GPIOH_PIN_START;
		if(pin >= VIM3_GPIOZ_PIN_START && pin <= VIM3_GPIOZ_PIN_END)
			return pin - VIM3_GPIOZ_PIN_START;
		if(pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)
			return pin - VIM3_GPIOAO_PIN_START;
	}
	return -1;
}

static int  gpioToGPFSELReg (int pin)
{
	if(piModel == PI_MODEL_KHADAS_VIM1){
		if(pin >= VIM1_GPIODV_PIN_START && pin <= VIM1_GPIODV_PIN_END)
			return VIM1_GPIODV_FSEL_REG_OFFSET;
		if(pin >= VIM1_GPIOH_PIN_START && pin <= VIM1_GPIOH_PIN_END)
			return VIM1_GPIOH_FSEL_REG_OFFSET;
		if(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)
			return VIM1_GPIOAO_FSEL_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		if(pin >= VIM2_GPIODV_PIN_START && pin <= VIM2_GPIODV_PIN_END)
			return VIM2_GPIODV_FSEL_REG_OFFSET;
		if(pin >= VIM2_GPIOH_PIN_START && pin <= VIM2_GPIOH_PIN_END)
			return VIM2_GPIOH_FSEL_REG_OFFSET;
		if(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)
			return VIM2_GPIOAO_FSEL_REG_OFFSET;
	}else if(piModel == PI_MODEL_KHADAS_VIM3){
		if(pin >= VIM3_GPIOA_PIN_START && pin <= VIM3_GPIOA_PIN_END)
			return VIM3_GPIOA_FSEL_REG_OFFSET;
		if(pin >= VIM3_GPIOH_PIN_START && pin <= VIM3_GPIOH_PIN_END)
			return VIM3_GPIOH_FSEL_REG_OFFSET;
		if(pin >= VIM3_GPIOZ_PIN_START && pin <= VIM3_GPIOZ_PIN_END)
			return VIM3_GPIOZ_FSEL_REG_OFFSET;
		if(pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)
			return VIM3_GPIOAO_FSEL_REG_OFFSET;
	}
	return -1;
}

int wiringPiSetupKhadas(void)
{
	int fd;
	if(access("/dev/gpiomem",0) == 0){
		if((fd = open("/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC)) < 0)
			return wiringPiFailure(WPI_ALMOST,
				"wpSetupKhadas : Unable to open /dev/gpiomem: %s\n",
				strerror(errno));
	}else{
		if (geteuid() != 0)
			(void)wiringPiFailure(WPI_ALMOST,
				"wpSetupKhadas:Must be root. (Did you forget sudo?\n");
		if ((fd = open("/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC)) < 0)
			return wiringPiFailure(WPI_ALMOST,
				"wpSetupKhadas : Unable to open /dev/mem: %s\n",
				strerror(errno));
	}

	if(piModel == PI_MODEL_KHADAS_VIM1){
		gpio1  = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE,
							MAP_SHARED, fd, VIM1_GPIOAO_BASE);
		gpio  = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE,
							MAP_SHARED, fd, VIM1_GPIO_BASE);
		
		if (((int32_t)gpio == -1) || ((int32_t)gpio1 == -1))
			return wiringPiFailure(WPI_ALMOST,
				"wpSetupKhadas: mmap (GPIO) failed: %s\n",
				strerror (errno));
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		gpio1  = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE,
								MAP_SHARED, fd, VIM2_GPIOAO_BASE);
		gpio  = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE,
								MAP_SHARED, fd, VIM2_GPIO_BASE);

		if (((int32_t)gpio == -1) || ((int32_t)gpio1 == -1))
			return wiringPiFailure(WPI_ALMOST,
				"wpSetupKhadas: mmap (GPIO) failed: %s\n",
				strerror (errno));
	}else if(piModel == PI_MODEL_KHADAS_VIM3){
		gpio1  = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE,
								MAP_SHARED, fd, VIM3_GPIOAO_BASE);
		gpio  = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE,
								MAP_SHARED, fd, VIM3_GPIO_BASE);	
		
		if (((int32_t)gpio == -1) || ((int32_t)gpio1 == -1))
			return wiringPiFailure(WPI_ALMOST,
				"wpSetupKhadas: mmap (GPIO) failed: %s\n",
				strerror (errno));
	}
	return 0;
}

void wiringPiCleanupKhadas(void)
{
	munmap((void *)gpio, BLOCK_SIZE);
	munmap((void *)gpio1, BLOCK_SIZE);
}


void pinModeKhadas(int pin, int mode)
{
	int shift,fsel;

	fsel  = gpioToGPFSELReg(pin);
	shift = gpioToShiftReg (pin);
	
	if(piModel == PI_MODEL_KHADAS_VIM1){
		if(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END){
			if(mode == INPUT){
				*(gpio1 + fsel) = (*(gpio1 + fsel) |  (1 << shift));
			}else if (mode == OUTPUT){
				*(gpio1 + fsel) = (*(gpio1 + fsel) & ~(1 << shift));
			}
		}else{
			if(mode == INPUT){
				*(gpio + fsel) = (*(gpio + fsel) |  (1 << shift));
			}else if (mode == OUTPUT){
				*(gpio + fsel) = (*(gpio + fsel) & ~(1 << shift));
			}
		}
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		if(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END){
			if(mode == INPUT){
				*(gpio1 + fsel) = (*(gpio1 + fsel) |  (1 << shift));
			}else if (mode == OUTPUT){
				*(gpio1 + fsel) = (*(gpio1 + fsel) & ~(1 << shift));
			}
		}else{
			if(mode == INPUT){
				*(gpio + fsel) = (*(gpio + fsel) |  (1 << shift));
			}else if (mode == OUTPUT){
				*(gpio + fsel) = (*(gpio + fsel) & ~(1 << shift));
			}
		}
	}else if(piModel == PI_MODEL_KHADAS_VIM3){
		if(pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END){
			if(mode == INPUT){
				*(gpio1 + fsel) = (*(gpio1 + fsel) |  (1 << shift));
			}else if (mode == OUTPUT){
				*(gpio1 + fsel) = (*(gpio1 + fsel) & ~(1 << shift));
			}
		}else{
			if(mode == INPUT){
				*(gpio + fsel) = (*(gpio + fsel) |  (1 << shift));
			}else if (mode == OUTPUT){
				*(gpio + fsel) = (*(gpio + fsel) & ~(1 << shift));
			}
		}
	}
}

void pullUpDnControlKhadas(int pin, int pud)
{
	int shift = 0;

	shift = gpioToShiftReg(pin);
	
	if((pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)||
		(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)||
		(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)){
		if(pud){
			//Enable Pull/Pull-down resister
			*(gpio1 + gpioToPUENReg(pin)) =
				(*(gpio1 + gpioToPUENReg(pin)) | (1 << shift));
			if (pud == PUD_UP)
				*(gpio1 + gpioToPUPDReg(pin)) =
					(*(gpio1 + gpioToPUPDReg(pin)) | (1 << shift));
			else
				*(gpio1 + gpioToPUPDReg(pin)) =
					(*(gpio1 + gpioToPUPDReg(pin)) & ~(1 << shift));
		}else //Disable Pull/Pull-down resister
			*(gpio1 + gpioToPUENReg(pin)) =
				(*(gpio1 + gpioToPUENReg(pin)) & ~(1 << shift));
	}else{
		if(pud){
			//Enable Pull/Pull-down resister
			*(gpio + gpioToPUENReg(pin)) =
				(*(gpio + gpioToPUENReg(pin)) | (1 << shift));
			if (pud == PUD_UP)
				*(gpio + gpioToPUPDReg(pin)) =
					(*(gpio + gpioToPUPDReg(pin)) | (1 << shift));
			else
				*(gpio + gpioToPUPDReg(pin)) =
					(*(gpio + gpioToPUPDReg(pin)) & ~(1 << shift));
		}else //Disable Pull/Pull-down resister
			*(gpio + gpioToPUENReg(pin)) =
				(*(gpio + gpioToPUENReg(pin)) & ~(1 << shift));
	}
}

int digitalReadKhadas(int pin)
{	
	if((pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)||
		(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)||
		(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)){
		if ((*(gpio1 + gpioToGPLEVReg(pin)) & (1 << gpioToShiftReg(pin))) != 0)
			return HIGH;
		else
			return LOW;
	}else{		
		if ((*(gpio + gpioToGPLEVReg(pin)) & (1 << gpioToShiftReg(pin))) != 0)
			return HIGH;
		else
			return LOW;
	}
	return -1;
}

void digitalWriteKhadas(int pin,int value)
{
	if((pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)||
		(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)){
		if (value == LOW)
			*(gpio1 + gpioToGPSETReg(pin)) &= ~(1 << (gpioToShiftReg(pin) + 16));
		else
			*(gpio1 + gpioToGPSETReg(pin)) |=  (1 << (gpioToShiftReg(pin) + 16));
	}else if (pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END){
		if (value == LOW)
			*(gpio1 + gpioToGPSETReg(pin)) &= ~(1 << gpioToShiftReg(pin));
		else
			*(gpio1 + gpioToGPSETReg(pin)) |=  (1 << gpioToShiftReg(pin));
	}else{
		if (value == LOW)
			*(gpio + gpioToGPSETReg(pin)) &= ~(1 << gpioToShiftReg(pin));
		else
			*(gpio + gpioToGPSETReg(pin)) |=  (1 << gpioToShiftReg(pin));
	}		
}

int analogReadKhadas(int pin)
{
	return 0;
}

void analogWriteKhadas(int pin, int value)
{
	wiringPiFailure(WPI_FATAL, "analogWriteKhadas: No DAC on Khadas\n");
}

int pinGetModeKhadas(int pin)
{
	int shift;
	int rwbit, regval, retval=0;

	if((pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)||
		(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)||
		(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)){
		regval = (*(gpio1 + gpioToGPFSELReg(pin)));
	}else
		regval = (*(gpio + gpioToGPFSELReg(pin)));
}

void setInfoKhadas(char *hardware, void *vinfo)
{
	rpi_info *info = (rpi_info *)vinfo;

	if(strcmp(hardware, "VIM3") == 0){
		piModel = PI_MODEL_KHADAS_VIM3;
		info->type = "Khadas VIM3";
		info->p1_revision = 3;
		info->ram = "2048M/4096M";
		info->manufacturer = "wesion";
		info->processor = "AMLA311D";
	}else if(strcmp(hardware, "VIM2") == 0){
		piModel = PI_MODEL_KHADAS_VIM2;
		info->type = "Khadas VIM2";
		info->p1_revision = 3;
		info->ram = "2048M/4096M";
		info->manufacturer = "wesion";
		info->processor = "AMLS912";
	}else if(strcmp(hardware, "VIM") == 0){
		piModel = PI_MODEL_KHADAS_VIM1;
		info->type = "Khadas VIM";
		info->p1_revision = 3;
		info->ram = "2048M/4096M";
		info->manufacturer = "wesion";
		info->processor = "S905X";
	}
}

void setMappingPtrsKhadas(void)
{
	if(piModel == PI_MODEL_KHADAS_VIM1){
		pin_to_gpio = (const int(*)[41]) & phyToGpio_rev_vim1;
		bcm_to_khadasgpio = &bcmToOGpioKhadas_vim1;
	}else if(piModel == PI_MODEL_KHADAS_VIM2){
		pin_to_gpio = (const int(*)[41]) & phyToGpio_rev_vim2;
		bcm_to_khadasgpio = &bcmToOGpioKhadas_vim2;
	}else if(piModel == PI_MODEL_KHADAS_VIM3){
		pin_to_gpio = (const int(*)[41]) & phyToGpio_rev_vim3;
		bcm_to_khadasgpio = &bcmToOGpioKhadas_vim3;
	}
}

