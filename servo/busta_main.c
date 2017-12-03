#include "msp430_version.h"
#include <stdio.h>
#include "display.h"
#include "osc.h"
#include "adc.h"

/*char new_char1[] = {BIT0-BIT0,BIT0-BIT0,BIT2,BIT1+BIT2+BIT3,BIT0+BIT1+BIT2+BIT3+BIT4,BIT1+BIT2+BIT3,BIT2,BIT0-BIT0};
char new_char2[] = {BIT0-BIT0,BIT3,BIT2+BIT3,BIT1+BIT2+BIT3+BIT4,BIT0+BIT1+BIT2+BIT3+BIT4,BIT1+BIT2+BIT3+BIT4,BIT2+BIT3,BIT3};
char new_char3[] = {BIT0-BIT0,BIT1,BIT2+BIT1,BIT1+BIT2+BIT3+BIT0,BIT0+BIT1+BIT2+BIT3+BIT4,BIT1+BIT2+BIT3+BIT0,BIT2+BIT1,BIT1};
char new_char4[] = {BIT0-BIT0,BIT0-BIT0,BIT0-BIT0,BIT0+BIT1+BIT2+BIT3+BIT4,BIT0+BIT1+BIT2+BIT3+BIT4,BIT0+BIT1+BIT2+BIT3+BIT4,BIT0-BIT0,BIT0-BIT0};
char *p1;
char *p2;
char *p3;
char *p4; */
int c=0;
int a,b,d;
int tacr_nuevo, tacr_viejo;
int contador=0;
int cuerpo;
int tiempo_alcanzado=1;
int ya_iniciado = 0;
//int contador_distancia_gato = 0;
float res;

void main(void)
{
    osc_init_xt2();
    WDTCTL = WDTPW + WDTHOLD;
    
   /* display_init();
    display_set_pos(0x00);
    display_send_cmd(0x0C);
    p1 = new_char1;
    p2 = new_char2;
    p3 = new_char3;
    p4 = new_char4;
    display_new_character(0x01, p1);
    display_new_character(0x02, p2);
    display_new_character(0x03, p3);
    display_new_character(0x04, p4); */
    
    //printf("%c",0x01);

  /*  CCTL0 = CCIE;             	// CCR0 habilita interrupción del timer
    CCR0 = 625-1;               // frecuencia 50 HZ, señal PWM */
    
   /* P1DIR &= 0xFD;
    P1SEL &= 0xFD;
    P1DIR |= 0x04;
    P1SEL |= 0x04; */
    P5DIR |= 0x1C;
    
    TACCTL0 = CCIE;
    TACCR0 = 625-1;
    TACTL = TASSEL_1 + MC_1;    // reloj ACLK, modo up to CCR0
   // TACCTL1 = OUTMOD_7;         // reset-set
   // TACCR1= 80;
    
   /* TBCCTL0 = CCIE;
    TBCCR0 = 16384-1;
    TBCTL = TBSSEL_1 + MC_1;
    
    
    adc_init_single_channel_single_conv_it(); // inicia conversion y habilita interrupciones del ADC12
    adc_single_channel_single_conv_it(0); */
    
    _BIS_SR(LPM0_bits + GIE);
   
   /* x = (dc/4095);
    
    
    if ((P1IN & 0x01) == 0x01) {
      TACCR1 = x*624;
}
    else                        {
      TACCR1 = (1-x)*624;
} */
    

}


#define CONV(x)      x			// convertir x en voltaje

// Timer A0 rutina de servicio de interrupción
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  if ((tiempo_alcanzado == 1) && (ya_iniciado ==1)){
    adc_single_channel_single_conv_it(0);
 //   res = _resultado();
  }
  else if ((tiempo_alcanzado == 1) && (ya_iniciado ==0)){
    P5OUT &= 0xEF;
    adc_init_single_channel_single_conv_it();
    adc_single_channel_single_conv_it(0);
 //   res = _resultado();
  }
  else {
    P5OUT |= 0x10;
  }
  
/*  contador_distancia_gato = ((res <= 0.12) && (contador_distancia_gato != 150))?contador_distancia_gato+1:0;
  if (contador_distancia_gato == 150) {
    P5OUT &= 0xFB;
    P5OUT |= 0x08;
  }
  else {
    P5OUT &= 0xF7;
    P5OUT |= 0x04;
  } */
  
        
}
/*
#pragma vector = TIMERB0_VECTOR 
__interrupt void Timer_B (void)
{
        tacr_nuevo = TACCR1;
        contador += 1;
        cuerpo = ((TACCR1-32)*15)/32;
        int i;
        
        c = ((abs(tacr_viejo - tacr_nuevo) <= 1) & contador >= 4)?1:0;
        a = ((tacr_viejo < tacr_nuevo) & c == 0)?1:0;
        b = ((tacr_viejo > tacr_nuevo) & c == 0)?1:0;
  
        if (c==1) {
          int pos = display_get_pos();
          display_clear();
          for(i=0;i<cuerpo;i++) {
            printf("%c",0x04);
          }
          printf("%c",0x01);
          display_set_pos(pos);
}          
        else if (a==1) {
          int pos = display_get_pos();
          display_clear();
          for(i=0;i<cuerpo;i++) {
            printf("%c",0x04);
          }
          printf("%c",0x02);
          display_set_pos(pos);
          contador=0;
        } 
        
        else if (b==1) {
          int pos = display_get_pos();
          display_clear();
          for(i=0;i<cuerpo;i++) {
            printf("%c",0x04);
          }
          printf("%c",0x03);
          display_set_pos(pos);
          contador=0;
        }   */
        
       /* float grado = ((tacr_nuevo*180)/32.0) - 180;
        int pos = display_get_pos();
        int linea = display_lcd_addr(2);
        display_set_pos(linea);
        printf("Grado = %d",grado);
        display_set_pos(pos); 
        tacr_viejo = TACCR1;
        c=0; 
          
}*/