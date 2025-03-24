#ifndef MaterialsMessenger_h
#define MaterialsMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class Materials;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class MaterialsMessenger: public G4UImessenger
{
public:
  MaterialsMessenger(Materials*);
  ~MaterialsMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  Materials* materials;
  G4UIdirectory* MDir;

  G4UIcmdWithAString* GasTypeCmd;
  G4UIcmdWithAString* Layer0TypeCmd;
  G4UIcmdWithAString* TargetBackingCmd;
  G4UIcommand* GasPrChCmd;
  G4UIcommand* GasTChCmd;
  G4UIcommand* GasPrColCmd;
  G4UIcommand* GasTColCmd;
  G4UIcommand* GasPrPipeCmd;
  G4UIcommand* GasTPipeCmd;
  G4UIcommand* MixNeAbCmd;
  G4UIcommand* MixBAbCmd;
  G4UIcommand* MixWrCmd;
  G4UIcommand* MixRhoCmd;
};

#endif
