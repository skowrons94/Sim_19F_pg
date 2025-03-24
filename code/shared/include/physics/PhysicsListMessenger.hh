#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PhysicsList;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class PhysicsListMessenger: public G4UImessenger
{
public:
  PhysicsListMessenger(PhysicsList* p = 0);
  virtual ~PhysicsListMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  PhysicsList* physicsList;
  G4UIdirectory* PhysDir;

  G4UIcmdWithAString* EmPhysCmd;
  G4UIcmdWithABool* HadrPhysCmd;

};

#endif
