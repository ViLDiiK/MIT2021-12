#include "stm8s.h"
#include "milis.h"

#include <stdio.h>      //abych mohl použít sprintf
#include "stm8_hd44780.h"

/*#include "delay.h"*/
/*#include <stdio.h>*/
/*#include "../lib/uart.c"*/

#define _ISOC99_SOURCE
#define _GNU_SOURCE

#define LED_PORT GPIOC
#define LED_PIN  GPIO_PIN_5
#define LED_HIGH   GPIO_WriteHigh(LED_PORT, LED_PIN)
#define LED_LOW  GPIO_WriteLow(LED_PORT, LED_PIN)
#define LED_TOGG GPIO_WriteReverse(LED_PORT, LED_PIN)

#define BTN_PORT GPIOE
#define BTN_PIN  GPIO_PIN_4
#define BTN_PUSH (GPIO_ReadInputPin(BTN_PORT, BTN_PIN)==RESET) 


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    init_milis();
}


int main(void)
{
    uint32_t time = 0;
    
    char text[16];
    uint8_t cislo = 35;

    setup();
    /*init_uart();*/

    lcd_init();
    lcd_gotoxy(0, 0);
    lcd_puts("Funguje to!");

    sprintf(text, "Zdravim");
    lcd_gotoxy(0, 1);
    lcd_puts(text);


    while (1) {

        if (milis() - time > 333 && BTN_PUSH) {
            LED_TOGG; 
            time = milis();
        }

        /*LED_FLIP; */
        /*_delay_ms(333);*/
        /*printf("Funguje to!!!\n");*/
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
