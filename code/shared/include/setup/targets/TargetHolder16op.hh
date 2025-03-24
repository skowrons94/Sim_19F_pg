#ifndef TargetHolder16op_h
#define TargetHolder16op_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class TargetHolder16op
{
public:

  TargetHolder16op();
  ~TargetHolder16op();

public:
  G4double GetTargetPosition();
  G4LogicalVolume* Construct();
  
private:
  Materials* materials;

  G4double lengthHolderLower;
  G4double lengthHolderMid;
  G4double lengthHolderUpper;
};

#endif
