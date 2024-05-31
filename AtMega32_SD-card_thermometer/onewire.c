#include "onewire.h"
int OWTouchReset(void)
{
	int result;
	_delay_us(0);
	OW_low; // Drives DQ low
	_delay_us(480);
	OW_high; // Releases the bus
	_delay_us(70);
	result = OW_check; // Sample for presence pulse from slave
	_delay_us(410); // Complete the reset sequence recovery
	return result; // Return sample presence pulse result
}
//-----------------------------------------------------------------------------
// Send a 1-Wire write bit. Provide 10us recovery time.
//
void OWWriteBit(int bit)
{
	if (bit)
	{
		// Write '1' bit
		OW_low; // Drives DQ low
		_delay_us(6);
		OW_high; // Releases the bus
		_delay_us(64); // Complete the time slot and 10us recovery
	}
	else
	{
		// Write '0' bit
		OW_low; // Drives DQ low
		_delay_us(60);
		OW_high; // Releases the bus
		_delay_us(10);
	}
}
//-----------------------------------------------------------------------------
// Read a bit from the 1-Wire bus and return it. Provide 10us recovery time.
//
int OWReadBit(void)
{
	int result;
	OW_low; // Drives DQ low
	_delay_us(6);
	OW_high; // Releases the bus
	_delay_us(9);
	result = OW_check; // Sample the bit value from the slave
	_delay_us(55); // Complete the time slot and 10us recovery
	return result;
}
void OWWriteByte(int data)
{
	int loop;
	// Loop to write each bit in the byte, LS-bit first
	for (loop = 0; loop < 8; loop++)
	{
		OWWriteBit(data & 0x01);
		// shift the data byte for the next bit
		data >>= 1;
	}
}
//-----------------------------------------------------------------------------
// Read 1-Wire data byte and return it
//
int OWReadByte(void)
{
	int loop, result=0;
	for (loop = 0; loop < 8; loop++)
	{
		// shift the result to get it ready for the next bit
		result >>= 1;
		// if result is one, then set MS bit
		if (OWReadBit())
			result |= 0x80;
	}
	return result;
}
