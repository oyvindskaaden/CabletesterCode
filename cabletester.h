#ifndef cabletester
#define cabletester

#include <array>

using namespace std;

// LK pinout and configuration
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

class Cabletester
{
private:
	array<uint64_t, 36> results;

	const array<uint8_t,36>& inputPins;

	const array<uint8_t,5>& muxSel;

	const array<uint8_t,3>& muxCtrl;

public:
	Cabletester(const array<uint8_t,36>& inputPins, 
				const array<uint8_t,5>& muxSel, 
				const array<uint8_t,3>&  muxCtrl);

	~Cabletester();

	///
	/// Converts from a binary number data to digital pins in array ctrlPins
	///
	void WriteBits(uint8_t data, const const array<uint8_t,3>& ctrlPins);

	///
	/// Reads the pins between startPin and endPin, returns a uint64_t with where the trigger happened.
	/// The LSB is the last input to be scanned, so if you scan pin 1 and 2, the read would be 0b(pin1)(pin2)
	///
	uint64_t ReadInputs(const array<uint8_t,36>& pins);

	/// 
	/// Returns true if the zero indexed curPin is high, and only that pin
	///
	boolean CheckIfNormal(const uint64_t& data, const uint8_t curPin);

	///
	/// Returns the number of set bits
	///
	uint8_t CountSetBits(uint64_t data);


	/// 
	/// Takes in the dataint and finds all the indexes for errors, excludes the current pin
	///
	uint8_t* FindErrors(uint64_t data, const uint8_t noPin, const uint8_t curPin);


	///
	/// Scans all the pins specified by the arguments, specify where the MUXsel pins start and amount, where MUXctrl are and the number of states, input start and number.
	/// Returns a list of length inputNo (up to 64 inputs), containing all the scan data.
	/// Optional is how long it should scan the pins for, default for delay is 0ms (at least one time).
	/// Optional is to specify how many times the scan should be done, default for count is 1. 
	///
	uint64_t* ScanPins(const uint8_t muxSelStart, const uint8_t muxSelNo, const uint8_t muxCtrlStart, const uint8_t muxCtrlNo, const uint8_t muxStates, const uint8_t inputStart, const uint8_t inputNo, const uint16_t delay = 0, const uint8_t count = 1);
};






#endif