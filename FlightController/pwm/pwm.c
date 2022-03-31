/*
 * pwm.c
 *
 *  Created on: Mar 29, 2022
 *      Author: Akeman
 */

#include <stdbool.h>
#include <stdint.h>

#include <ti/sysbios/BIOS.h>

#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_gpio.h>

#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/sysctl.h>
#include <driverlib/timer.h>

#include "pwm/pwm.h"

static uint32_t clock;
static const uint32_t pwmFrequencyInHertz = 100;

void setPWM(const uint32_t percent)
{
    if (percent != 0.0f)
    {
        const unsigned int timerLoad = clock / pwmFrequencyInHertz;
        const uint32_t prescaler = timerLoad >> 16;

        TimerPrescaleSet(TIMER3_BASE, TIMER_B, prescaler);

        GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_3);

        TimerLoadSet(TIMER3_BASE, TIMER_B, timerLoad);

        const uint32_t period = TimerLoadGet(TIMER3_BASE, TIMER_B) + (TimerPrescaleGet(TIMER3_BASE, TIMER_B) * (prescaler << 16));
        const uint32_t dutyCycle = period * ((100.0f - percent) / 100.0f);

        TimerPrescaleMatchSet(TIMER3_BASE, TIMER_B, dutyCycle / (prescaler << 16));
        TimerMatchSet(TIMER3_BASE, TIMER_B, dutyCycle % (prescaler << 16));

        TimerEnable(TIMER3_BASE, TIMER_B);
    }
    else
    {
        TimerDisable(TIMER3_BASE, TIMER_B);
        GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_3, 0);
    }

}

void initPWM(void)
{
    xdc_runtime_Types_FreqHz freq;
    BIOS_getCpuFreq((xdc_runtime_Types_FreqHz*)&freq);

    clock = freq.lo;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);

    GPIOPinConfigure(GPIO_PM3_T3CCP1);
    GPIOPinTypeTimer(GPIO_PORTM_BASE, GPIO_PIN_3);

    TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
    TimerClockSourceSet(TIMER3_BASE, TIMER_CLOCK_SYSTEM);

//    TimerPrescaleSet(TIMER3_BASE, TIMER_B, prescaler);
}
