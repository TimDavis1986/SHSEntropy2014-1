#include "AcquisitionArms.h"
#include "EntropyJoystick.h"
#include "EntropyInfraredSensor.h"
#include "IODefinitions.h"

AcquisitionArms::AcquisitionArms() {

}

bool AcquisitionArms::Initialize() 
{
	airCompressor = new Compressor (1, pressureSwitchChannel, 1, compressorRelayChannel);
	upperSolenoid = new Solenoid (upperSolenoidChannel);
	lowerSolenoid = new Solenoid (lowerSolenoidChannel);
	InfraredSensor.Initialize();
	MotorBelt = new CANJaguar(IODefinitions::MOTOR_ACQUISITION_BELT);
	MotorExtender = new CANJaguar(IODefinitions::MOTOR_ACQUISITION_EXTENDER);

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
	MotorExtender->Set(0.0);
	MotorBelt->Set(0.0);
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
	} else {
		lowerSolenoid->Set(false);
	}
}
void AcquisitionArms::Extend(EntropyJoystick * GameStick)
{
	if (GameStick->GetRawButton(1)) {
		MotorExtender->Set(0.2);
	} else if (GameStick->GetRawButton(2)) {
		MotorExtender->Set(-0.2);
	} else {
		MotorExtender->Set(0.0);
	}
}
void AcquisitionArms::BeltEnable(EntropyJoystick * GameStick)
{
	if (GameStick->GetRawButton(6)) {
		MotorBelt->Set(0.2);
	} else if (GameStick->GetRawButton(7)){
		MotorBelt->Set(-0.2);
	} else {
		MotorBelt->Set(0.0);
	}
}

char * AcquisitionArms::GetFeedback(){ return NULL;}
