/*
 * rpi.h
 *
 *  Created on: 12 Jan 2014
 *      Author: jamie
 */

#ifndef RPI_H_
#define RPI_H_


#define BCM2708_PERI_BASE        0x3F000000 
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)	// GPIO controller
#define GPIO_TIMER 				(BCM2708_PERI_BASE + 0x003000)  // Timer
#define GPIO_CLOCK				(BCM2708_PERI_BASE + 0x00101000)
#define TIMER_OFFSET 			(4)
#define BLOCK_SIZE 				(4*1024)
#define BCM_PASSWORD			0x5A000000
#define GPIO_CLOCK_SOURCE       1
#define TIMER_CONTROL			(0x408 >> 2)
#define TIMER_IRQ_RAW			(0x410 >> 2)
#define TIMER_PRE_DIV			(0x41C >> 2)

static unsigned char gpioToGPFSEL [] =
{
  0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1,
  2,2,2,2,2,2,2,2,2,2,
  3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,
} ;


// gpioToShift
//        Define the shift up for the 3 bits per pin in each GPFSEL port

static unsigned char gpioToShift [] =
{
  0,3,6,9,12,15,18,21,24,27,
  0,3,6,9,12,15,18,21,24,27,
  0,3,6,9,12,15,18,21,24,27,
  0,3,6,9,12,15,18,21,24,27,
  0,3,6,9,12,15,18,21,24,27,
} ;

// IO Access
struct bcm2835_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};

//struct bcm2835_peripheral gpio = {GPIO_BASE};
//struct bcm2835_peripheral timer = {ST_BASE};

extern struct bcm2835_peripheral gpio;  // They have to be found somewhere, but can't be in the header
extern struct bcm2835_peripheral gpio_timer;  // They have to be found somewhere, but can't be in the header
extern struct bcm2835_peripheral gpio_clock;  // They have to be found somewhere, but can't be in the header


#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1 ignores bits which are 0

#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))

#endif /* RPI_H_ */
