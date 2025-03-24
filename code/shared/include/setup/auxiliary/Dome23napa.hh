#ifndef Dome23napa_h
#define Dome23napa_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;
class Dome23napaMessenger;

class Dome23napa
{
public:
  Dome23napa();
  ~Dome23napa();
  void SetFileName(G4String filename) {fileName = filename;};
  static Dome23napa* GetInstance();

public:

  G4LogicalVolume * Construct();
  
private:
  G4String fileName;
  Materials* materials;
  Dome23napaMessenger* dome23napaMessenger;

  static Dome23napa* instance;
};

#endif
