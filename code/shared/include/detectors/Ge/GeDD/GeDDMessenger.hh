#ifndef GeDDMessenger_h
#define GeDDMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class GeDD;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class GeDDMessenger: public G4UImessenger
{
public:
  GeDDMessenger(GeDD*);
  ~GeDDMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  GeDD* geDD;
  G4UIdirectory* GEDDDir;

  G4UIcommand* DeadSideCmd;
  G4UIcommand* DeadFrontCmd;
  G4UIcommand* DeadBackCmd;
  G4UIcommand* DispCmd;
};

#endif
