#ifndef Chamber20nep_h
#define Chamber20nep_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4AssemblyVolume.hh"

class Materials;

class Chamber20nep
{
public:

  Chamber20nep();
  ~Chamber20nep();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();
  G4double GetLength2();
  G4double GetInnerLength();
  G4double GetHeight();
  G4LogicalVolume* GetTargetLog(G4int);
  G4LogicalVolume* GetInnerVolumeLog();

private:
  Materials* materials;

  G4double outerY;
  G4double outerL;
  G4double innerL;

  G4double innerLorig; // temporary fix for 21Ne setup until calorimeter is coded

  G4int GasSlice;
  G4LogicalVolume* gasLog[7];
  G4LogicalVolume* vacuumLog;
};

#endif
