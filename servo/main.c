#include "msp430_version.h" 
#include "osc.h"
#include "adc.h"


int compuerta_ctl=0; 
int c=0;
int a,b,d;
int tacr_nuevo, tacr_viejo;
int cuerpo;
int tiempo_alcanzado=1;
int ya_iniciado = 0;
//int contador_distancia_gato = 0;
float res;
int cat_detected;
long unsigned int contador=0;
/*
void compuerta_servo(int control){
  
  if(control==1){    
    TACCR1= 32;
    }
    else if(control==0){
    TACCR1=65;
    }
}
*/
void main(void){
    
    osc_init_xt2();
    WDTCTL = WDTPW + WDTHOLD;
    P5DIR |= 0x1C;
    P4DIR |= 0xFF;
    P2DIR |= 0x0F;
    P1SEL |= BIT6;
    P1DIR |= BIT6;

 
    TACCTL0 = CCIE;
    TBCCTL0 = CCIE;
    
    TACCR0 = 625-1;
    TACTL = TASSEL_1 + MC_1;    // reloj ACLK, modo up to CCR0
    TACCTL1 = OUTMOD_7;         //PWM para servo motor de compuerta

    
    TBCTL = TBSSEL_1 + MC_1; //Timer_B ACLK y en modo Up to TBCCR0 
    TBCCR0 = 55-1;  //50hz
     
    //compuerta_servo(compuerta_ctl);
     _BIS_SR(LPM0_bits + GIE);
    
}

#define CONV(x)      x			// convertir x en voltaje

// Timer A0 rutina de servicio de interrupción
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
 // if(modo_sensor == 1) { 
   //   if ((tiempo_alcanzado == 1) && (ya_iniciado ==1)){
    //    adc_single_channel_single_conv_it(0);
     //   res = _resultado();
    //  }
  cat_detected = detectado();
     if ((tiempo_alcanzado == 1) && (cat_detected == 0)){
        P5OUT &= 0xEF;
        adc_init_single_channel_single_conv_it();
        adc_single_channel_single_conv_it(0);
     //   res = _resultado();
      }
      else {
        P5OUT |= 0x10;
        adc_single_channel_single_conv_it(0);
      }
  }
          

#pragma vector = TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
  cat_detected = detectado();
  if (cat_detected == 1) {
    control_steper();
    contador += 1;
    if (contador == 5000) {
      contador=0;
      ADC12IE |= 0x01;
    }
  }
}


