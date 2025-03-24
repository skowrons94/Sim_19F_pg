#ifndef BGO14NpTargetMessenger_h
#define BGO14NpTargetMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class BGO14NpTarget;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;

class BGO14NpTargetMessenger: public G4UImessenger
{
public:
  BGO14NpTargetMessenger(BGO14NpTarget*);
  ~BGO14NpTargetMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  BGO14NpTarget* bgo14NpTarget;
  G4UIdirectory* BGO14NPTARGETDir;

  G4UIcommand* BGO14NpTargetCmd;

};

#endif
