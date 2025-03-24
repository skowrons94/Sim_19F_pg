#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class PrimaryGeneratorMessenger: public G4UImessenger
{
public:
  PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
  ~PrimaryGeneratorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  PrimaryGeneratorAction* primaryGeneratorAction;
  G4UIdirectory* PGADir;

};

#endif
