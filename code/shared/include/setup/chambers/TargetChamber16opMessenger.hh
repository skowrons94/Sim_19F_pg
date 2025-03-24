#ifndef TargetChamber16opMessenger_h
#define TargetChamber16opMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class TargetChamber16op;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class TargetChamber16opMessenger: public G4UImessenger
{
public:
  TargetChamber16opMessenger(TargetChamber16op*);
  ~TargetChamber16opMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  TargetChamber16op* targetchamber16op;
  G4UIdirectory* TARGETCH16OPDir;

  G4UIcmdWithAString* TargetCh16opCmd;
  

};

#endif
