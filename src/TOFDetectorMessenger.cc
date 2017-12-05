#include "TOFDetectorMessenger.hh"
#include "TOFDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

TOFDetectorMessenger::TOFDetectorMessenger(TOFDetectorConstruction* detectorAction):Detector(detectorAction)
{
	DetectorDir = new G4UIdirectory("/TOF/Detector/");
	DetectorDir->SetGuidance("UI commands of DetectorAction construction Action");
	DetectorDir->SetGuidance("Set the parameter of the S1 and S2 detectors");

	FlightAngleCmd = new G4UIcmdWithADoubleAndUnit("/TOF/Detector/FlightAngle", this);
	FlightAngleCmd -> SetGuidance("Set the flight angle");
	FlightAngleCmd -> SetParameterName("FlightAngle", false);
	FlightAngleCmd -> SetRange("FlightAngle>=0.");
	FlightAngleCmd -> SetUnitCategory("Angle");
	FlightAngleCmd -> AvailableForStates(G4State_PreInit,G4State_Idle);
    
    NumberOfS1Cmd = new G4UIcmdWithAnInteger("/TOF/Detector/NumberOfS1", this);
    NumberOfS1Cmd -> SetGuidance("Set the number of s1");
	NumberOfS1Cmd -> SetParameterName("NumberOfS1", false);
	NumberOfS1Cmd -> SetRange("NumberOfS1>0");
	NumberOfS1Cmd -> AvailableForStates(G4State_PreInit,G4State_Idle); 
    
    NumberOfS2Cmd = new G4UIcmdWithAnInteger("/TOF/Detector/NumberOfS2", this);
    NumberOfS2Cmd -> SetGuidance("Set the number of s2");
	NumberOfS2Cmd -> SetParameterName("NumberOfS2", false);
	NumberOfS2Cmd -> SetRange("NumberOfS2>0");
	NumberOfS2Cmd -> AvailableForStates(G4State_PreInit,G4State_Idle); 
    
    UpdateCmd =  new G4UIcmdWithoutParameter("/TOF/Detector/update",this);
    UpdateCmd -> SetGuidance("Update Scintilator geometry.");
    UpdateCmd -> SetGuidance("This command MUST be applied before \"beamOn\" ");
    UpdateCmd -> SetGuidance("if you changed geometrical value(s).");
    UpdateCmd -> AvailableForStates(G4State_Idle);    
}

TOFDetectorMessenger::~TOFDetectorMessenger()
{

    delete FlightAngleCmd;
    delete UpdateCmd;
	delete DetectorDir;
}

void TOFDetectorMessenger::SetNewValue(G4UIcommand* command, G4String value)
{
	if( command == FlightAngleCmd)
	{ Detector -> SetFlightAngle(FlightAngleCmd -> GetNewDoubleValue(value));}
    
    if( command == NumberOfS1Cmd)
	{ Detector -> SetNumberOfS1(NumberOfS1Cmd -> GetNewIntValue(value));}
    
    if( command == NumberOfS2Cmd)
	{ Detector -> SetNumberOfS2(NumberOfS2Cmd -> GetNewIntValue(value));}
    
    if( command == UpdateCmd )
    { Detector->UpdateGeometry(); }

}
