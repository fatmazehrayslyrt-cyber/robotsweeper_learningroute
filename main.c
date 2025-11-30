#include "stm32f10x.h"

/* PROJECT: Digital GPIO Test (Register-Level)
 *
 * Pin assignments:
 *  - Left motor direction:  PB0, PB1
 *  - Right motor direction: PB10, PB11
 *  - Status LED:            PB5
 *  - User button:           PC13 (pull-up)
 */

static void delay(volatile uint32_t t)
{
    while (t--) { __NOP(); }
}

/* ------------------- GPIO INITIALIZATION ------------------- */

void gpio_init(void)
{
    /* Enable GPIOA, GPIOB, GPIOC and AFIO clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN
                 |  RCC_APB2ENR_IOPBEN
                 |  RCC_APB2ENR_IOPCEN
                 |  RCC_APB2ENR_AFIOEN;

    /* Motor direction pins: PB0, PB1, PB10, PB11
       Mode: Output, Push-Pull, 2 MHz (MODE = 0b10, CNF = 0b00) */

    // PB0, PB1 → CRL
    GPIOB->CRL &= ~((0xF << (4 * 0)) | (0xF << (4 * 1)));
    GPIOB->CRL |=  ((0x2 << (4 * 0)) | (0x2 << (4 * 1)));

    // PB10, PB11 → CRH (index = pin - 8)
    GPIOB->CRH &= ~((0xF << (4 * (10 - 8))) | (0xF << (4 * (11 - 8))));
    GPIOB->CRH |=  ((0x2 << (4 * (10 - 8))) | (0x2 << (4 * (11 - 8))));

    /* Status LED: PB5 (output push-pull, 2 MHz) */
    GPIOB->CRL &= ~(0xF << (4 * 5));
    GPIOB->CRL |=  (0x2 << (4 * 5));

    /* User button: PC13 (input pull-up)
       MODE = 0b00, CNF = 0b10 → 0x8 */
    GPIOC->CRH &= ~(0xF << (4 * (13 - 8)));
    GPIOC->CRH |=  (0x8 << (4 * (13 - 8)));

    GPIOC->ODR |= (1 << 13);  // Enable pull-up
}

/* ------------------- HELPER FUNCTIONS ------------------- */

static inline void led_on(void)
{
    GPIOB->BSRR = (1 << 5);
}

static inline void led_off(void)
{
    GPIOB->BRR = (1 << 5);
}

static inline uint8_t button_pressed(void)
{
    return ((GPIOC->IDR & (1 << 13)) == 0U);
}

static inline void motor_left(int dir)
{
    switch (dir) {
        case 1:  GPIOB->BSRR = (1 << 0); GPIOB->BRR = (1 << 1); break;
        case -1: GPIOB->BRR = (1 << 0); GPIOB->BSRR = (1 << 1); break;
        default: GPIOB->BRR = (1 << 0) | (1 << 1); break;
    }
}

static inline void motor_right(int dir)
{
    switch (dir) {
        case 1:  GPIOB->BSRR = (1 << 10); GPIOB->BRR = (1 << 11); break;
        case -1: GPIOB->BRR = (1 << 10); GPIOB->BSRR = (1 << 11); break;
        default: GPIOB->BRR = (1 << 10) | (1 << 11); break;
    }
}

/* ------------------- MAIN LOOP ------------------- */

int main(void)
{
    gpio_init();

    uint8_t run = 0;  // 0 = stop, 1 = forward

    motor_left(0);
    motor_right(0);
    led_off();

    while (1)
    {
        if (button_pressed()) {
            delay(200000);                // debounce
            if (button_pressed()) {
                run ^= 1;                 // toggle state

                if (run) {
                    led_on();
                    motor_left(1);
                    motor_right(1);
                } else {
                    led_off();
                    motor_left(0);
                    motor_right(0);
                }

                while (button_pressed()) {
                    // wait until button is released
                }
            }
        }
    }
}
