#ifndef DEBUG_H_
#define DEBUG_H_

#define INT_EUSCIA0		(32)
#define EUSCI_A0_MODULE	(0x40001000)
#define DCORSEL_3		(0x00030000)

const eUSCI_UART_Config uartConfig = {
	EUSCI_A_UART_CLOCKSOURCE_SMCLK,					// SMCLK Clock Source
	6,												// BRDIV
	8,												// UCxBRF
	32,												// UCxBRS
	EUSCI_A_UART_NO_PARITY,							// No Parity
	EUSCI_A_UART_LSB_FIRST,							// MSB First
	EUSCI_A_UART_ONE_STOP_BIT,						// One stop bit
	EUSCI_A_UART_MODE,								// UART mode
	EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION	// Oversampling
};

void debug_init() {
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
			GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
	MAP_UART_initModule(EUSCI_A0_MODULE, &uartConfig);
	MAP_UART_enableModule(EUSCI_A0_MODULE);
}

void debug_sendByte(const char c)
{
	MAP_UART_transmitData(EUSCI_A0_MODULE, c);
}

void debug(const char *s) {
	char c;

	while (c = *s++) {
		debug_sendByte(c);
	}

	debug_sendByte('\n'); debug_sendByte('\r');
}

#endif
