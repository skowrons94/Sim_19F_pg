#ifndef HadronPhysicsListMessenger_h
#define HadronPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class HadronPhysicsList;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class HadronPhysicsListMessenger: public G4UImessenger
{
public:
  HadronPhysicsListMessenger(HadronPhysicsList* p = 0);
  virtual ~HadronPhysicsListMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  HadronPhysicsList* hadronPhysicsList;
  G4UIdirectory* PhysDir;

  G4UIcmdWithABool* HPinelProtCmd;
  G4UIcmdWithABool* HPinelDeutCmd;
  G4UIcmdWithABool* HPinelTritCmd;
  G4UIcmdWithABool* HPinelHe3Cmd;
  G4UIcmdWithABool* HPinelAlphCmd;
  G4UIcmdWithABool* HPinelC12Cmd;
  G4UIcmdWithABool* InelProtCmd;
  G4UIcmdWithABool* InelDeutCmd;
  G4UIcmdWithABool* InelTritCmd;
  G4UIcmdWithABool* InelHe3Cmd;
  G4UIcmdWithABool* InelAlphCmd;
  G4UIcmdWithABool* InelC12Cmd;
  G4UIcmdWithAString* PartCapTypeCmd;
  G4UIcmdWithABool* PartCapCmd;

};

#endif
