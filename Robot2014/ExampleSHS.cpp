#include "ExampleSHS.h"
#include "IODefinitions.h"

ExampleSHS::ExampleSHS() {
	
	
}

bool ExampleSHS::Initialize()
{
	MotorShootAz = new CANJaguar(IODefinitions::MOTOR_ACQUISITION_BELT);
	MotorShootEl = new CANJaguar(IODefinitions::MOTOR_ACQUISITION_EXTENDER);
	return true;
}

void ExampleSHS::Cleanup()
{ 
	MotorShootAz->Disable();
	MotorShootEl->Disable();
}

void ExampleSHS::StopAz()
{
	MotorShootAz->Set(0.0);
}

void ExampleSHS::MoveAz( bool move_left, bool move_right )
{
	if ( move_left && move_right )
	{
		StopAz(); 
	} 
	else if ( move_left )
	{
		MotorShootAz->Set( SPEED );
	} 
	else if ( move_right ){
		MotorShootAz->Set( -SPEED );
	}
	else {
		StopAz();
	}
}
char * ExampleSHS::GetFeedback(){ return NULL;}


