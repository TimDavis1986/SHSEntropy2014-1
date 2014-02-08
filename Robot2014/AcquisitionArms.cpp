#include "AcquisitionArms.h"
#include "EntropyJoystick.h"
#include "EntropyInfraredSensor.h"

AcquisitionArms::AcquisitionArms() {

}

bool AcquisitionArms::Initialize() 
{
	airCompressor = new Compressor (1, pressureSwitchChannel, 1, compressorRelayChannel);
	upperSolenoid = new Solenoid (upperSolenoidChannel);
	lowerSolenoid = new Solenoid (lowerSolenoidChannel);
	InfraredSensor.Initialize();

	return true;
}
void AcquisitionArms::TeleopInitialize()
{
	airCompressor->Start();
}
void AcquisitionArms::Cleanup() 
{
	upperSolenoid->Set(false);
	lowerSolenoid->Set(false);
	airCompressor->Stop();
}
void AcquisitionArms::UpperVerticalPos(EntropyJoystick * GameStick) 
{
	upperSolenoid->Set(GameStick->GetRawButton(3));
}
void AcquisitionArms::LowerVerticalPos(EntropyJoystick * GameStick)
{
	lowerSolenoid->Set(GameStick->GetRawButton(4));
}

void AcquisitionArms::Update()
{
	if (InfraredSensor.GetValue() > 1.4)
	{
		lowerSolenoid->Set(true);
	}
	else
	{
		lowerSolenoid->Set(false);
	}
}

char * AcquisitionArms::GetFeedback(){ return NULL;}
