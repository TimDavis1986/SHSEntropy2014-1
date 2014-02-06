#ifndef __ACQUISITION_ARMS__
#define __ACQUISITION_ARMS__

#include "WPILib.h"
#include "EntropySubsystemTemplate.h"
#include "EntropyJoystick.h"

class AcquisitionArms : public EntropySubsystemTemplate
{
private:
	static const int compressorRelayChannel = 1;
	static const int pressureSwitchChannel = 8;
	Compressor * airCompressor;
	
	static const int upperSolenoidChannel = 2;
	static const int lowerSolenoidChannel = 1;
	Solenoid * upperSolenoid;
	Solenoid * lowerSolenoid;
public:
	AcquisitionArms();
	
	bool Initialize ();
	
	void TeleopInitialize();
		
	void Cleanup();
		
	char * GetFeedback();
	
	void UpperVerticalPos(EntropyJoystick * GameStick);
	
	void LowerVerticalPos(EntropyJoystick * GameStick);
};

#endif
