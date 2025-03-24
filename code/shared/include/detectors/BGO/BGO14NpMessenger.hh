#ifndef BGO14NpMessenger_h
#define BGO14NpMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class BGO14Np;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class BGO14NpMessenger: public G4UImessenger
{
public:
  BGO14NpMessenger(BGO14Np*);
  ~BGO14NpMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  BGO14Np* bgo14Np;
  G4UIdirectory* BGO14NPDir;

  G4UIcommand* BGO14NpCmd;

};

#endif
