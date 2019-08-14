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

static void init_adc_fds (void)
{
    const char *AIN0_NODE, *AIN1_NODE;
    struct utsname uname_buf;

    /* ADC node setup */
    uname(&uname_buf);

    AIN0_NODE = "/sys/devices/platform/ff100000.saradc/iio:device0/in_voltage2_raw";
    AIN1_NODE = "/sys/devices/platform/ff100000.saradc/iio:device0/in_voltage3_raw";
 
    adcFds[0] = open(AIN0_NODE, O_RDONLY);
    adcFds[1] = open(AIN1_NODE, O_RDONLY);
}

static void setClkState (int pin, int state)
{
    uint32_t target = 0;
    uint8_t bank = pin / 32;
    uint8_t shift = bank < 2 ? bank + 2 : bank + 1;

    target |= (1 << (shift + 16));

    switch (state) {
    case EDGE_CLK_ENABLE:
        if (bank < 2) {
            target |= *(cru[0] + (EDGE_PMUCRU_GPIO_CLK_OFFSET >> 2));
            target &= ~(1 << shift);
            *(cru[0] + (EDGE_PMUCRU_GPIO_CLK_OFFSET >> 2)) = target;
        } else {
            target |= *(cru[1] + (EDGE_CRU_GPIO_CLK_OFFSET >> 2));
            target &= ~(1 << shift);
            *(cru[1] + (EDGE_CRU_GPIO_CLK_OFFSET >> 2)) = target;
        }
        break;
    case EDGE_CLK_DISABLE:
        if (bank < 2) {
            target |= *(cru[0] + (EDGE_PMUCRU_GPIO_CLK_OFFSET >> 2));
            target |=  (1 << shift);
            *(cru[0] + (EDGE_PMUCRU_GPIO_CLK_OFFSET >> 2)) = target;
        } else {
            target |= *(cru[1] + (EDGE_CRU_GPIO_CLK_OFFSET >> 2));
            target |=  (1 << shift);
            *(cru[1] + (EDGE_CRU_GPIO_CLK_OFFSET >> 2)) = target;
        }
        break;
    default:
        break;
    }
}

static void setIomuxMode (int pin, int mode)
{
    uint32_t offset, target;
    uint8_t bank, group;

    bank    = pin / 32;
    group   = (pin - bank * 32) / 8;
    offset  = 0x10 * (bank > 1 ? bank - 2 : bank) + 0x4 * group;
    target  = 0;

    target |= (1 << (gpioToShiftGReg(pin) * 2 + 17));
    target |= (1 << (gpioToShiftGReg(pin) * 2 + 16));

    switch (mode) {
    case EDGE_FUNC_GPIO:
        // Common IOMUX Funtion 1 : GPIO (0b00)
        if (bank < 2) {
            offset += EDGE_PMUGRF_IOMUX_OFFSET;

            target |= *(grf[0] + (offset >> 2));
            target &= ~(1 << (gpioToShiftGReg(pin) * 2 + 1));
            target &= ~(1 << (gpioToShiftGReg(pin) * 2));

            *(grf[0] + (offset >> 2)) = target;
        } else {
            offset += EDGE_GRF_IOMUX_OFFSET;

            target |= *(grf[1] + (offset >> 2));
            target &= ~(1 << (gpioToShiftGReg(pin) * 2 + 1));
            target &= ~(1 << (gpioToShiftGReg(pin) * 2));

            *(grf[1] + (offset >> 2)) = target;
		}
        break; 
	default:
        break;
    }
}


int gpioToShiftGReg (int pin)
{
     return pin % 8;
}

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
	}else if(piModel == PI_MODEL_KHADAS_EDGE){
		return pin % 32;
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
	void *mapped_cru[2], *mapped_grf[2], *mapped_gpio[5];

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
	}else if(piModel == PI_MODEL_KHADAS_EDGE){
		mapped_cru[0] = mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_PMUCRU_BASE);
		mapped_cru[1] = mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_CRU_BASE);
		mapped_grf[0] = mmap(0, EDGE_GRF_BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_PMUGRF_BASE);
		mapped_grf[1] = mmap(0, EDGE_GRF_BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_GRF_BASE);
		mapped_gpio[1] = mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_GPIO_1_BASE);
		mapped_gpio[2] = mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_GPIO_2_BASE);
		mapped_gpio[4] = mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_GPIO_4_BASE);
		mapped_gpio[0] = mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_GPIO_0_BASE);
		mapped_gpio[3] = mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, EDGE_GPIO_3_BASE);
		if ((mapped_cru[0] == MAP_FAILED) || (mapped_cru[1] == MAP_FAILED)) {
			wiringPiFailure(WPI_ALMOST,
			               "wpSetupKhadas: mmap (CRU) failed: %s\n",
			                strerror (errno));
		}else{
			cru[0] = (uint32_t *) mapped_cru[0];
			cru[1] = (uint32_t *) mapped_cru[1];
		}

		if ((mapped_grf[0] == MAP_FAILED) || (mapped_grf[1] == MAP_FAILED)) {
			wiringPiFailure(WPI_ALMOST,
			               "wpSetupKhadas: mmap (GRF) failed: %s\n",
			                strerror (errno));
		}else{
			grf[0] = (uint32_t *) mapped_grf[0];
			grf[1] = (uint32_t *) mapped_grf[1];
		}

		if ((mapped_gpio[0] == MAP_FAILED) ||
		    (mapped_gpio[1] == MAP_FAILED) ||
		    (mapped_gpio[2] == MAP_FAILED) ||
		    (mapped_gpio[3] == MAP_FAILED) ||
		    (mapped_gpio[4] == MAP_FAILED)) {
				wiringPiFailure(WPI_ALMOST,
			                        "wpSetupKhadas: mmap (GPIO) failed: %s\n",
		                            strerror (errno));
		}else{
			edge_gpio[0] = (uint32_t *) mapped_gpio[0];
			edge_gpio[1] = (uint32_t *) mapped_gpio[1];
			edge_gpio[2] = (uint32_t *) mapped_gpio[2];
			edge_gpio[3] = (uint32_t *) mapped_gpio[3];
			edge_gpio[4] = (uint32_t *) mapped_gpio[4];
		}
	}
	return 0;
}

void wiringPiCleanupKhadas(void)
{
	int i=0;
	if(piModel == PI_MODEL_KHADAS_EDGE){
		for(i=0;i<5;i++){
			munmap((void *)edge_gpio[i], BLOCK_SIZE);
			if(i<2){
				munmap((void *)grf[i], BLOCK_SIZE);
				munmap((void *)cru[i], BLOCK_SIZE);
			}
		}
	}else{
		munmap((void *)gpio, BLOCK_SIZE);
		munmap((void *)gpio1, BLOCK_SIZE);
	}
}


void pinModeKhadas(int pin, int mode)
{
	int shift,fsel;
	int origPin, bank;
	unsigned long flags;

	fsel  = gpioToGPFSELReg(pin);
	shift = gpioToShiftReg (pin);
	if(piModel == PI_MODEL_KHADAS_EDGE){
		origPin = pin;
		bank = pin / 32;

		setClkState (pin, EDGE_CLK_ENABLE);
		setIomuxMode(pin, EDGE_FUNC_GPIO);

		switch (mode) {
		    case INPUT:
		        *(edge_gpio[bank] + (EDGE_GPIO_CON_OFFSET >> 2)) &= ~(1 << gpioToShiftReg(pin));
		        break;
		    case OUTPUT:
		        *(edge_gpio[bank] + (EDGE_GPIO_CON_OFFSET >> 2)) |=  (1 << gpioToShiftReg(pin));
		        break;
	    }
		setClkState (pin, EDGE_CLK_DISABLE);
	}else if(piModel == PI_MODEL_KHADAS_VIM1){
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
	uint32_t offset, target;
	uint8_t bank, group;
	if(piModel == PI_MODEL_KHADAS_EDGE){
		bank    = pin / 32;
	    group   = (pin - bank * 32) / 8;
	    offset  = 0x10 * (bank > 1 ? bank - 2 : bank) + 0x4 * group;
	    target  = 0;
	
	    target |= (1 << (gpioToShiftGReg(pin) * 2 + 17));
	    target |= (1 << (gpioToShiftGReg(pin) * 2 + 16));
	
	    setClkState(pin, EDGE_CLK_ENABLE);

		switch(pud){
			case PUD_UP:
		        if (bank < 2) {
		            offset += EDGE_PMUGRF_PUPD_OFFSET;
		
		            target |= *(grf[0] + (offset >> 2));
		            target &= ~(1 << (gpioToShiftGReg(pin) * 2 + 1));
		            target |=  (1 << (gpioToShiftGReg(pin) * 2));
		 
		            *(grf[0] + (offset >> 2)) = target;
		        } else {
		            offset += EDGE_GRF_PUPD_OFFSET;
		
		            target |= *(grf[1] + (offset >> 2));
		            if (bank == 2 && group >= 2) {
		                target |=  (1 << (gpioToShiftGReg(pin) * 2 + 1));
		                target |=  (1 << (gpioToShiftGReg(pin) * 2));
		            } else {
		                target &= ~(1 << (gpioToShiftGReg(pin) * 2 + 1));
		                target |=  (1 << (gpioToShiftGReg(pin) * 2));
		           }
	
		            *(grf[1] + (offset >> 2)) = target;
		        }
		        break;
			case PUD_DOWN:
		        if (bank < 2) {
		            offset += EDGE_PMUGRF_PUPD_OFFSET;
			
		            target |= *(grf[0] + (offset >> 2));
		            target |=  (1 << (gpioToShiftGReg(pin) * 2 + 1));
		            target &= ~(1 << (gpioToShiftGReg(pin) * 2));
		
		            *(grf[0] + (offset >> 2)) = target;
		        } else {
		            offset += EDGE_GRF_PUPD_OFFSET;
		
		            target |= *(grf[1] + (offset >> 2));
		            if (bank == 2 && group >= 2) {
		                target &= ~(1 << (gpioToShiftGReg(pin) * 2 + 1));
		                target |=  (1 << (gpioToShiftGReg(pin) * 2));
		            } else {
		                target |=  (1 << (gpioToShiftGReg(pin) * 2 + 1));
		                target &= ~(1 << (gpioToShiftGReg(pin) * 2));
		            }
		
		            *(grf[1] + (offset >> 2)) = target;
		        }
		        break;
			case PUD_OFF:
		        if (bank < 2) {
		            offset += EDGE_PMUGRF_PUPD_OFFSET;
			
		            target |= *(grf[0] + (offset >> 2));
		            target &= ~(1 << (gpioToShiftGReg(pin) * 2 + 1));
		            target &= ~(1 << (gpioToShiftGReg(pin) * 2));
			
		            *(grf[0] + (offset >> 2)) = target;
		        } else {
		            offset += EDGE_GRF_PUPD_OFFSET;
		
		            target |= *(grf[1] + (offset >> 2));
		            target &= ~(1 << (gpioToShiftGReg(pin) * 2 + 1));
		            target &= ~(1 << (gpioToShiftGReg(pin) * 2));
			
		             *(grf[1] + (offset >> 2)) = target;
		        }
		        break;
			default:
				break;
		}
		setClkState(pin, EDGE_CLK_DISABLE);
	}else{
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
}

int digitalReadKhadas(int pin)
{
	int bank, ret;
	if(piModel == PI_MODEL_KHADAS_EDGE){
		bank = pin / 32;
		setClkState(pin, EDGE_CLK_ENABLE);
		ret = *(edge_gpio[bank] + (EDGE_GPIO_GET_OFFSET >> 2)) & (1 << gpioToShiftReg(pin)) ? HIGH : LOW;
		setClkState(pin, EDGE_CLK_DISABLE);
		return ret;
	}else{
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
	}
	return -1;
}

void digitalWriteKhadas(int pin,int value)
{
	int bank;
	if(piModel == PI_MODEL_KHADAS_EDGE){
		bank = pin / 32;
		setClkState(pin, EDGE_CLK_ENABLE);
		switch (value){ 
			case  LOW:
		        *(edge_gpio[bank] + (EDGE_GPIO_SET_OFFSET >> 2)) &= ~(1 << gpioToShiftReg(pin));
		        break;
		    case HIGH:
		        *(edge_gpio[bank] + (EDGE_GPIO_SET_OFFSET >> 2)) |=  (1 << gpioToShiftReg(pin));
		        break;
		    default:
		        break;
		}
	    setClkState(pin, EDGE_CLK_DISABLE);

	}else if((pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)||
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
	char value[5] = {0,};
	if(piModel == PI_MODEL_KHADAS_EDGE){
		switch (pin) {
			case    0:  case    25:
				pin = 0;
				break;
			case    1:  case    29:
				pin = 1;
				break;
			default:
				return 0;
		}
		if (adcFds [pin] == -1)
			return 0;
		lseek(adcFds [pin], 0L, SEEK_SET);
		if (read(adcFds [pin], &value[0], 4) < 0) {
			wiringPiFailure(WPI_FATAL, "%s: Error occurs when it reads from ADC file descriptor. \n", __func__);
			return -1;
		}
	}else
		wiringPiFailure(WPI_FATAL, "analogReadKhadas: No DAC on Khadas\n");
	return atoi(value);

}

void analogWriteKhadas(int pin, int value)
{
	wiringPiFailure(WPI_FATAL, "analogWriteKhadas: No DAC Write on Khadas\n");
}

int pinGetModeKhadas(int pin)
{
	int shift;
	int rwbit, regval, retval=0;
	int origPin, bank;
	if(piModel == PI_MODEL_KHADAS_EDGE){
		origPin = pin;
		bank = pin / 32;
		setClkState (pin, EDGE_CLK_ENABLE);
		setIomuxMode(pin, EDGE_FUNC_GPIO);
		regval = *(edge_gpio[bank] + (EDGE_GPIO_CON_OFFSET >> 2));
		setClkState (pin, EDGE_CLK_DISABLE);
	}else{
		if((pin >= VIM3_GPIOAO_PIN_START && pin <= VIM3_GPIOAO_PIN_END)||
			(pin >= VIM2_GPIOAO_PIN_START && pin <= VIM2_GPIOAO_PIN_END)||
			(pin >= VIM1_GPIOAO_PIN_START && pin <= VIM1_GPIOAO_PIN_END)){
			regval = (*(gpio1 + gpioToGPFSELReg(pin)));
		}else
			regval = (*(gpio + gpioToGPFSELReg(pin)));
	}
	rwbit = regval & (1 << gpioToShiftReg(pin));
	retval = ((rwbit!=0) ? 0 : 1);

	return retval;
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
	}else if(strcmp(hardware, "Edge-V") == 0){
		piModel = PI_MODEL_KHADAS_EDGE;
		info->type = "Khadas EDGE-V";
		info->p1_revision = 3;
		info->ram = "2048M/4096M";
		info->manufacturer = "wesion";
		info->processor = "RK3399";
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
	}else if(piModel == PI_MODEL_KHADAS_EDGE){
		pin_to_gpio = (const int(*)[41]) & phyToGpio_rev_edge;
		bcm_to_khadasgpio = &bcmToOGpioKhadas_edge;
	}
}

