/* 
 * File:   i2c_pic18f.h
 * Author: HP
 *
 * Created on 6 de abril de 2020, 11:33 PM
 */

#ifndef I2C_PIC18F_H
#define	I2C_PIC18F_H

#include <xc.h>

#define _XTAL_FREQ 20000000UL

#define TRIS_DATOS TRISBbits.TRISB0
#define TRIS_CLOCK TRISBbits.TRISB1

void i2c_configuracion(void) ;
void i2c_empezar_transmicion (void);
void i2c_terminar_transmicion (void);
void i2c_reiniciar_transmicion (void);
void  i2c_reconocimiento (void);
void  i2c_no_reconocimiento (void);
char i2c_enviar_dato (char i2c_dato);

#endif	/* I2C_PIC18F_H */

