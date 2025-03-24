#ifndef Foil23napaMessenger_h
#define Foil23napaMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "Foil23napa.hh"

class Foil23napa;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;


class Foil23napaMessenger: public G4UImessenger
{
public:
  Foil23napaMessenger(Foil23napa*);
  ~Foil23napaMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
 
  
private:
  Foil23napa* foil23napa;
  G4UIdirectory* Foil23napaDir;

  G4UIcommand* FoilTCmd;
  G4UIcommand* FoilAlTCmd;
};

#endif




