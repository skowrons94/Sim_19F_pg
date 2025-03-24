#ifndef DetectorConstructionMessenger_h
#define DetectorConstructionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class DetectorConstructionMessenger: public G4UImessenger
{
public:
  DetectorConstructionMessenger(DetectorConstruction*);
  ~DetectorConstructionMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  DetectorConstruction* detectorConstruction;
  G4UIdirectory* DCDir;

  G4UIcommand* SourcePosCmd;
  G4UIcommand* BGO14NpPosCmd;
  G4UIcommand* BGO14NpTargetHolderPosCmd;
  G4UIcommand* MaxStepCmd;
  G4UIcmdWithAString* PhysicsCmd;
  G4UIcmdWithAString* SourceHolderCmd;
};

#endif
