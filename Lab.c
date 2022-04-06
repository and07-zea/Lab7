/*
 * File:   Lab.c
 * Author: Andrea Rodriguez Zea
 *
 * Created on April 4, 2022, 8:40 PM
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT    // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF               // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF              // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF              // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF                 // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF                // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF              // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF               // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF              // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF                // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V           // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF                // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>                         // Compilador usado
#include <stdint.h>                     // Extensión para INT
#include <stdio.h>                      

uint8_t IN;

void setup(void);

#define pb_inc  PORTBbits.RB0           // Define el puerto RB0 para PB+
#define pb_dec  PORTBbits.RB1           // Define el puerto RB0 para PB-

void __interrupt() isr(void)

    {
    if(INTCONbits.RBIF){                // Se localiza interrupción en RB0
        if(!pb_inc)                     
        { IN ++ ;                       // Incremento de valores en el puerto C
            PORTC = IN; 
            if (IN==20)                 // Se define 0 - 20 como rango
                IN=0;
        }         
        else if(!pb_dec)                // Se localiza interrupción en RB0
        { IN --;                        // Incremento de valores en el puerto C
            PORTC = IN;                 
              if(IN==255)               // Se define 21 - 255 como rango
                  IN=21;                
        }            
        INTCONbits.RBIF = 0;            // Limpia la bandera de interrupción]
    }
    return;
}

void main(void){
    setup();
    while(1){   }
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;

    TRISC = ~0x1F;
    PORTC = 0; 
    
    TRISBbits.TRISB0 = 1;               // RB0 es IN
    TRISBbits.TRISB1 = 1;               // RB1 es IN
    OPTION_REGbits.nRBPU = 0;           // Pull-Up PORT B
    WPUBbits.WPUB0 = 1;                 // Pull up-B e RB0
    WPUBbits.WPUB1 = 1;                 // Pull up-B On RB1
    INTCONbits.GIE = 1;                 // Interrupciones globales - HABILITADAS
    INTCONbits.RBIE = 1;                // Interrupciones PORTB
    IOCBbits.IOCB0 = 1;                 // Interrupciones por cambio de estado para el puerto RB0 
    IOCBbits.IOCB1 = 1;                 // Interrupciones por cambio de estado para el puerto RB1
    INTCONbits.RBIF = 0;                // Limpieza de banderas
}