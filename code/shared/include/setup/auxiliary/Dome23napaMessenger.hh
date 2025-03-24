#ifndef Dome23napaMessenger_h
#define Dome23napaMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithABool.hh"

class Dome23napa;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;

class Dome23napaMessenger: public G4UImessenger
{
public:
  Dome23napaMessenger(Dome23napa* );
  ~Dome23napaMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
 
  
private:
  Dome23napa* dome23napa;
  G4UIdirectory* Dome23napaDir;

  G4UIcmdWithAString* FileNameCmd;
};

#endif
