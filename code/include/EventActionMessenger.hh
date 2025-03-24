#ifndef EventActionMessenger_h
#define EventActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class EventAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class EventActionMessenger: public G4UImessenger
{
public:
  EventActionMessenger(EventAction*);
  ~EventActionMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  EventAction* eventAction;
  G4UIdirectory* EADir;

  G4UIcmdWithADouble* NoiseBGO14NpCmd;
};

#endif
