#ifndef ColdFinger16op_h
#define ColdFinger16op_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class ColdFinger16op
{
public:

  ColdFinger16op();
  ~ColdFinger16op();

public:
  G4double GetLength();
  G4LogicalVolume* Construct();
  
private:
  Materials* materials;
  G4double lengthColdTrap;
};

#endif
