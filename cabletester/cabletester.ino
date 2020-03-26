// Read pins
#define INPUT_START		14  // Inputs start from INPUT_START, should be zero indexed, so the zero'th input
#define INPUT_STOP		53  // Inputs stop at INPUT_STOP
#define INPUT_NO		40  // Inputs stop at INPUT_STOP

// MUX select pins
#define MUXSEL_START	5   // Mux selection pin start at pin 5
#define MUXSEL_STOP		9   // Mux selection pin stop at pin 9

// MUX control signals
#define MUX_A			2   // Mux lowest bit
#define MUX_B			3   // Mux middle bit
#define MUX_C			4   // Mux highest bit

uint8_t noPairs = 12;
char lkConfig[] = {'+', '-', 'G'};
char lkPinout[] = 
{	
	'E', 'F', 'A', 
	'B', 'C', 'G', 
	'H', 'J', 'D',
	'S', 'T', 'K', 
	'L', 'M', 'U', 
	'V', 'W', 'N',
	'P', 'R', 'X', 
	'a', 'b', 'g', 
	'c', 'd', 'j', 
	'e', 'f', 'm', 
	'n', 'p', 'h', 
	'r', 's', 'k', 
};


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

///
/// Converts from a binary number to digital pins between startPin and endPin
///
void WriteMuxC(const uint8_t& data, const uint8_t& startPin, const uint8_t& noPins)
{
	for (uint8_t i = 0; i <= noPins; i++)
	{
		digitalWrite(i, (data >> i) & 0x1);
	}
}

///
/// Reads the pins between startPin and endPin, returns a uint64_t with where the trigger happened.
/// The LSB is the last input to be scanned, so if you scan pin 1 and 2, the read would be 0b(pin1)(pin2)
///
uint64_t ReadInputs(const uint8_t& startPin, const uint8_t& noPins)
{
	uint64_t inputPins = 0x0;
	for (uint8_t p = 0; p < noPins; p++)
	{
		inputPins = (inputPins + digitalRead(startPin + p)) << 1;
	}
	return inputPins;
}

/// 
/// Returns true if the zero indexed curPin is high, and only that pin
///
boolean CheckIfNormal(const uint64_t& data, const uint8_t curPin)
{
	if ((0x1 << curPin) == data)
		return true;
}

///
/// Returns the number of set bits
///
uint8_t CountSetBits(uint64_t data) 
{ 
    uint8_t count = 0; 
    while (data) { 
        count += data & 1; 
        data >>= 1; 
    } 
    return count; 
} 

int * FindErrors(uint64_t data, const uint8_t& noPin, const uint8_t& curPin)
{
	data = (data & ~(0x1 << curPin)); 	// Removes the currently searched pin
	char errors[CountSetBits(data)]; 	// Creates a list to store errors
	uint8_t errIndex = 0;

	for (uint8_t p = 0; p < noPin; p++)
	{
		
		if ((data & 0x1) && p != curPin)
		{
			errors[errIndex++] = p;
		}
		data = data >> 1;
	}
}

void loop()
{
	
}
