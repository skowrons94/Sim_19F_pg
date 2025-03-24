#ifndef Target_h
#define Target_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class Target
{
public:

  Target();
  ~Target();

public:

  G4double GetTargetThickness();
  G4LogicalVolume * Construct();
  
private:
  Materials* materials;
  G4double targetL;
};

#endif
