#include "cabletester.h"

///
/// Converts from a binary number to digital pins between startPin and endPin
///
void WriteBits(const uint8_t data, const uint8_t startPin, const uint8_t noPins)
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
uint64_t ReadInputs(const uint8_t startPin, const uint8_t noPins)
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


/// 
/// Takes in the dataint and finds all the indexes for errors, excludes the current pin
///
uint8_t* FindErrors(uint64_t data, const uint8_t noPin, const uint8_t curPin)
{
	data = (data & ~(0x1 << curPin)); 	// Removes the currently searched pin
	uint8_t errors[noPin]; 	// Creates a list to store errors
	uint8_t errIndex = 0;

	for (uint8_t p = 0; p < noPin; p++)
	{
		if ((data & 0x1) && p != curPin)
		{
			errors[errIndex++] = p;
		}
		data = data >> 1;
	}

	return errors;
}


uint64_t* ScanPins(const uint8_t muxSelStart, const uint8_t muxSelNo, const uint8_t muxCtrlStart, const uint8_t muxCtrlNo, const uint8_t muxStates, const uint8_t inputStart, const uint8_t inputNo, const uint16_t delay = 0, const uint8_t count = 1)
{
	uint8_t selected = 0x1;
	uint64_t results[inputNo];
	for (uint8_t i = 0; i < count; i++)
	{
		for (uint8_t s = 0; s < muxSelNo; s++)
		{
            // Writes what mux is selected
			WriteBits(selected, muxSelStart, muxSelNo);		
			for (uint8_t d = 0; d < muxStates; d++)
			{
				WriteBits(d, muxCtrlStart, muxCtrlNo);
				// Her må vi lese pins fo å sjekke errors.
				uint32_t startTime = millis();
				uint32_t endTime = startTime;
				// Run this loop for delay amount of time, at least one time
				do 
				{
					// OR the results from the scan, and put in array
					results[muxStates * s + d] = results[muxStates * s + d] | ReadInputs(inputNo, inputNo);
					
					endTime = millis();
				} 
				while ((endTime - startTime) <= delay);
				
			}
			// Moves the selected bit to the left
			selected = selected << 1;
		}
	}
}