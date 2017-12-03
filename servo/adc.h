#ifndef ADC__H
#define ADC__H
/*  Include section
*
***************************************************/
#include "msp430_version.h"

/*  Defines section
*
***************************************************/

/*  Function Prototype Section
*
***************************************************/
int adc_single_channel_single_conv(int);
void adc_init_single_channel_single_conv();
void adc_init_single_channel_single_conv_it();
void adc_single_channel_single_conv_it(int ch);

void adc_seq_channel_single_conv(int *, int *);
void adc_init_seq_channel_single_conv();

int detectado();
void control_steper();

#endif
