#ifndef Collimator20nep_h
#define Collimator20nep_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"

class Materials;

class Collimator20nep
{
public:

  Collimator20nep();
  ~Collimator20nep();

public:

  //G4LogicalVolume * Construct();
  G4AssemblyVolume * Construct();

  G4double GetLength();
  G4double GetLength2();
  G4LogicalVolume* GetTargetLog(G4int);
  
private:
  Materials* materials;

  G4double ringL;
  G4double slabL;
  G4double sheetL;
  G4double screwCutL;
  G4double screwL;

  G4int GasSlice;
  G4LogicalVolume* gasLog[5];

};

#endif
