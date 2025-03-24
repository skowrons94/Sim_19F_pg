#ifndef TargetHolderOuterFront10bMessenger_h
#define TargetHolderOuterFront10bMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithABool.hh"

class TargetHolderOuterFront10b;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;

class TargetHolderOuterFront10bMessenger: public G4UImessenger
{
public:
  TargetHolderOuterFront10bMessenger(TargetHolderOuterFront10b* );
  ~TargetHolderOuterFront10bMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
 
  
private:
  TargetHolderOuterFront10b* targetholderouterfront10b;
  G4UIdirectory* TargetHolderOuterFront10bDir;

  G4UIcmdWithAString* FileNameCmd;
};

#endif
