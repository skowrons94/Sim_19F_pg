#ifndef CuShieldForGePD20nep_h
#define CuShieldForGePD20nep_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"

class Materials;

class CuShieldForGePD20nep
{
public:

  CuShieldForGePD20nep();
  ~CuShieldForGePD20nep();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();
  G4double GetDiameter();
  
private:
  Materials* materials;

  G4double shieldL;
  G4double shieldOuterDiam;

};

#endif
