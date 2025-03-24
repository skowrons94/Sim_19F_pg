#ifndef OuterPbShield20nep_h
#define OuterPbShield20nep_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class OuterPbShield20nep
{
public:

  OuterPbShield20nep();
  ~OuterPbShield20nep();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();
  G4LogicalVolume* GetTargetLog();

private:
  Materials* materials;

  G4double outerL;

};

#endif
