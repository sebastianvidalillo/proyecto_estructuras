/***************************************************
* Nombre del modulo: osc.c
*
* Modulo creado para la asignatura Elo312
* Laboratorio de Estructura de Computadores
* del departamento de Electr�nica de la Universidad
* T�cnica Federico Santa Mar�a. El uso o copia
* est� permitido y se agracede mantener el nombre 
* de los creadores.
*
* Escrito inicialmente el 01/01/2004 Por Michael Kusch
* Modificado el 19/09/2014           Por Mauricio Sol�s.
*
* Descripci�n del m�dulo:
* Modulo Inicializador de Osciladores y Clocks

***************************************************/

/*  Include section
*
***************************************************/
#include "msp430_version.h"

/*  Defines section
*
***************************************************/


/*  Local Function Prototype Section
*
***************************************************/

/*  Global Variables Section
*
***************************************************/


/**************************************************
* Nombre    		: void osc_init_xt2(void)
* returns		: void
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Inicializa los osciladores y Cloks
**************************************************/
void osc_init_xt2(void)
{
	// Al enceder la MSP, �sta queda operando a aprox 800kHz para MCLK y SMCLK,
	// y a XT1 en modo LF para ACLK

	BCSCTL1 &= ~XT2OFF;                            // XT2 encendido (8MHz)
	do                                             // wait in loop until crystal is stable
		IFG1 &= ~OFIFG;
	while (IFG1 & OFIFG);
	IE1 &= ~WDTIE;                                 // disable WDT int.
	IFG1 &= ~WDTIFG;                               // clear WDT int. flag

	BCSCTL2 = SELM_2 | DIVM_0 | SELS | DIVS_0 ;    // MCLK <- XT2 | MCLK = 1:1 | SMCLK <- XT2 | SMCLK = 1:1 ;

	WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | WDTIS1 ; // use WDT as timer, flag each 512 pulses from SMCLK
	while (!(IFG1 & WDTIFG));                       // count 1024 pulses from XT2
	// (until XT2's amplitude is OK)
	IFG1 &= ~OFIFG;                                 // clear osc. fault int. flag
}

