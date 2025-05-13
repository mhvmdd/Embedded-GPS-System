
 /*
 * ADC.c
 *
 *  Created on: May 10, 2025
 *      Author: Nadine Amr
 */

#include "ADC.h"
#include "tm4c123gh6pm.h" 
#include "GPIO/GPIO.h"


void ADC_Init(void)
{
  // 1. Enable clocks for GPIOE and ADC0
    SYSCTL_RCGCGPIO_R |= (1U << 4); // Enable clock for Port E
    SYSCTL_RCGCADC_R |= (1U << 0);  // Enable clock for ADC0
    while ((SYSCTL_PRGPIO_R & (1U << 4)) == 0); // Wait for GPIOE to be ready

    // 2. Configure PE2 as ADC input (AIN1)
    GPIO_PORTE_AFSEL_R |= (1U << 2);   // Enable alternate function on PE2
    GPIO_PORTE_DEN_R &= ~(1U << 2);    // Disable digital on PE2
    GPIO_PORTE_AMSEL_R |= (1U << 2);   // Enable analog function on PE2

    // 3. Configure ADC0 Sequencer 3 for channel 1
    ADC0_ACTSS_R &= ~(1U << 3);        // Disable SS3 for config
    ADC0_EMUX_R &= ~(0xF << 12);       // Software trigger
    ADC0_SSMUX3_R = 1;                 // Set channel AIN1 (PE2)
    ADC0_SSCTL3_R = 0x06;              // END0 + IE0
    ADC0_ACTSS_R |= (1U << 3);         // Enable SS3
}

uint32_t ADC_Read(void)
{
		uint32_t result;
    ADC0_PSSI_R = (1U << 3); // Start conversion on SS3
    while ((ADC0_RIS_R & (1U << 3)) == 0); // Wait until done
    result = ADC0_SSFIFO3_R & 0xFFF; // Read 12-bit result
    ADC0_ISC_R = (1U << 3); // Clear interrupt
    return result;
}