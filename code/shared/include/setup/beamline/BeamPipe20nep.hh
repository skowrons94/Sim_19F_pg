#ifndef BeamPipe20nep_h
#define BeamPipe20nep_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4AssemblyVolume.hh"

class Materials;

class BeamPipe20nep
{
public:

  BeamPipe20nep();
  ~BeamPipe20nep();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();
  G4LogicalVolume* GetTargetLog(G4int);

private:
  Materials* materials;

  G4double pipeL;

  G4int GasSlice;
  G4LogicalVolume* gasLog[5];
};

#endif
