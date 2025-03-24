#ifndef GeBOMessenger_h
#define GeBOMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class GeBO;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class GeBOMessenger: public G4UImessenger
{
public:
  GeBOMessenger(GeBO*);
  ~GeBOMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  GeBO* geBO;
  G4UIdirectory* GEBODir;

  G4UIcommand* DeadSideCmd;
  G4UIcommand* DeadFrontCmd;
  G4UIcommand* DeadBackCmd;
  G4UIcommand* DeadHoleCmd;
};

#endif
