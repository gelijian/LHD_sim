
#ifndef TOFDetectorMessenger_h
#define TOFDetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class TOFDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;


class TOFDetectorMessenger: public G4UImessenger
{
public:
	TOFDetectorMessenger(TOFDetectorConstruction*);
	~TOFDetectorMessenger();

	virtual void SetNewValue(G4UIcommand*, G4String);

private:
	TOFDetectorConstruction* Detector;
    G4UIdirectory* DetectorDir;
	G4UIcmdWithADoubleAndUnit* FlightAngleCmd;
    G4UIcmdWithAnInteger* NumberOfS1Cmd;
    G4UIcmdWithAnInteger* NumberOfS2Cmd;
    G4UIcmdWithoutParameter * UpdateCmd;
};

#endif
