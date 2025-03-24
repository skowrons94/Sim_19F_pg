#ifndef GePDMessenger_h
#define GePDMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class GePD;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class GePDMessenger: public G4UImessenger
{
public:
  GePDMessenger(GePD*);
  ~GePDMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  GePD* gePD;
  G4UIdirectory* GEPDDir;

  G4UIcommand* DeadSideCmd;
  G4UIcommand* DeadFrontCmd;
  G4UIcommand* DeadBackCmd;
  G4UIcommand* DispCmd;
};

#endif
