#include "cabletester.h"

// Read pins
#define INPUT_START		14  // Inputs start from INPUT_START, should be zero indexed, so the zero'th input
#define INPUT_STOP		53  // Inputs stop at INPUT_STOP
#define INPUT_NO		40  // Inputs stop at INPUT_STOP

// MUX select pins
#define MUXSEL_START	5   // Mux selection pin start at pin 5
#define MUXSEL_STOP		9   // Mux selection pin stop at pin 9
#define MUXSEL_NO		5 	// Number of MUXes

// MUX control signals
#define MUX_A			2   // Mux lowest bit
#define MUX_B			3   // Mux middle bit
#define MUX_C			4   // Mux highest bit
#define MUX_STATES		8	// States of mux, 2^noBits


void setup()
{
	Serial.begin(9600);

	// Set up OUTPUTs
	for (uint8_t i = MUX_A; i <= MUXSEL_STOP; i++)
	{
		pinMode(i, OUTPUT);
	}

	// Set up INPUTs
	for (uint8_t i = 0; i < INPUT_NO; i++)
	{
		pinMode(INPUT_START + i, INPUT);
	}
}


void loop()
{

}
