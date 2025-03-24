#ifndef CuShieldForGeDD20nep_h
#define CuShieldForGeDD20nep_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"

class Materials;

class CuShieldForGeDD20nep
{
public:

  CuShieldForGeDD20nep();
  ~CuShieldForGeDD20nep();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();
  G4double GetHeight();
  
private:
  Materials* materials;

  G4double slabL;
  G4double slabY;

};

#endif
