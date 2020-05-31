/*
 * File:   principal.c
 * Author: HP
 *
 * Created on 6 de abril de 2020, 11:28 PM
 */


#include <xc.h>
#include "configu.h"
#include "i2c_pic18f.h"
/*
 * Macros
 */

/*
 * Varaibles
 */

/*
 * Funciones
 */

#define _XTAL_FREQ 20000000UL

#define BOTON PORTCbits.RC0
#define TRIS_BOTON TRISCbits.TRISC0

void main(void) {
    TRIS_BOTON = 1;
    i2c_configuracion(); /*Configuramos los registros correspondientes al I2C*/
    i2c_empezar_transmicion(); /*Enviamos la condicion de start para empezar la transmision de datos*/
    i2c_enviar_dato(0b01000000);
    i2c_enviar_dato(0xAA);
    i2c_terminar_transmicion();
    while (1) {

    }
    return;
}
