#include <stdio.h>
#include "unity_config.h"

#ifdef ARDUINO_AVR_UNO
void init_uart()
{
    // Operation mode Async
    UCSR0C &= ~(1 << UMSEL00);
    UCSR0C &= ~(1 << UMSEL01);

    // Not parity
    UCSR0C &= ~(1 << UPM00);
    UCSR0C &= ~(1 << UPM01);

    // One stop bit
    UCSR0C &= ~(1 << USBS0);

    // Frame 8bits
    UCSR0C |= (1 << UCSZ00);
    UCSR0C |= (1 << UCSZ01);
    UCSR0B &= ~(1 << UCSZ02);

    // Double speed
    UCSR0A |= (1 << U2X0);
    // Baudrate
    UBRR0 = (16000000 / 8 / 115200) - 1;

    // Enable TX Y RX
    UCSR0B |= (1 << TXEN0);
    UCSR0B |= (1 << RXEN0);
}

static int uart_putchar(char c)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}
void unityOutputStart()
{
    init_uart();
}

void unityOutputChar(char c)
{
    uart_putchar(c);
    // printf("%c", c);
    // Serial.println(c);
    // printf("cross compilation-test in atmega328p\n");
}

void unityOutputFlush() {}

void unityOutputComplete() {}
#endif