#ifndef BGO14NpTargetHolderMessenger_h
#define BGO14NpTargetHolderMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class BGO14NpTargetHolder;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;

class BGO14NpTargetHolderMessenger: public G4UImessenger
{
public:
  BGO14NpTargetHolderMessenger(BGO14NpTargetHolder*);
  ~BGO14NpTargetHolderMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  BGO14NpTargetHolder* bgo14NpTargetHolder;
  G4UIdirectory* BGO14NPTARGETHOLDERDir;

  G4UIcommand* BGO14NpTargetHolderCmd;

};

#endif
