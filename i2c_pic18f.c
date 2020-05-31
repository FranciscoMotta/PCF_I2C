
#include <xc.h>
#include <stdint.h>
#include "i2c_pic18f.h"

void i2c_configuracion(void) {
    TRIS_CLOCK = 1;
    TRIS_DATOS = 1;
    /*
     * The user must configure these pins as inputs by setting
     *the associated TRIS bits.
     */
    SSPSTATbits.SMP = 1; /*Elegimos la velocidad de transmisi�n estandar en 0 es la modalidad de high speed*/
    SSPSTATbits.CKE = 0; /*Desabilitamos las entradas espec�ficas del SMB*/
    

    SSPCON1bits.SSPEN = 1; /*Activamos los pines de SCL y SDA para el I2C*/
    SSPCON1bits.SSPM = 0b1000; /*Elegimos la velocidad de transmision segun la siguiente formula  clock = FOSC/(4 * (SSPADD + 1))*/
    

    SSPCON2 = 0x00; /*Regsitro propio cuando se est� en el proceso de transmision de datos por I2C*/

    SSPADD = 49; /*Divisor para la se�al de reloj SCL*/
}

void i2c_empezar_transmicion(void) {
    SSPCON2bits.SEN = 1; /*Iniciamos la condicion de START para la transmisi�n de datos*/
while (SSPCON2bits.SEN == 1); /*Preguntamos si el bit est� en 0 lo cual indica que ya inici� la comunicaci�n*/
}

void i2c_terminar_transmicion(void) {
    SSPCON2bits.PEN = 1; /*Terminamos el proceso de transmici�n de datos por i2c*/
while (SSPCON2bits.PEN == 1); /*Preguntamos si est� en 0 lo cual indica que ya termin� el proceso de transmici�n de datos*/
}

void i2c_reiniciar_transmicion(void) {
    SSPCON2bits.RSEN = 1; /*Reiniciamos el proceso de envio*/
while (SSPCON2bits.RSEN == 1);/*Preguntamos si ya termin� el proceso de reinicio de la transmisi�n por I2C*/
}

void i2c_reconocimiento(void) {
    PIR1bits.SSPIF = 0; /*Limpiamos la bandera del transmisi�n/recepci�n y la ponemos en modo de espera*/
    SSPCON2bits.ACKDT = 0; /*Ponemos el bit en 0 que es relativo al proceso de reconocimiento dado por el SLAVE*/
    SSPCON2bits.ACKEN = 1; /*Damos inicio a la secuencia de reconocimiento por los pines de SDA y SCL y env�a el dato de ACKDT*/
while (PIR1bits.SSPIF == 0); /*Esperamos a que se active la bandera de transmisi�n/recepci�n*/
}

void i2c_no_reconocimiento(void) {
    PIR1bits.SSPIF = 0; /*Limpiamos la bandera del transmisi�n/recepci�n y la ponemos en modo de espera*/
    SSPCON2bits.ACKDT = 1; /*Ponemos el bit en 1 que es relativo al proceso dado reconocimiento dado por el SLAVE*/
    SSPCON2bits.ACKEN = 1; /*Damos inicio a la secuencia de reconocimiento por los pines de SDA y SCL y env�a el dato de ACKDT*/
while (PIR1bits.SSPIF == 0);  /*Esperamos a que se active la bandera de transmisi�n/recepci�n*/
}

char i2c_enviar_dato(char i2c_dato) {
    PIR1bits.SSPIF = 0;
    SSPBUF = i2c_dato; //Envia data por I2C
    while (PIR1bits.SSPIF == 0); //Wait for interrupt flag to go high indicating transmission is complete
}