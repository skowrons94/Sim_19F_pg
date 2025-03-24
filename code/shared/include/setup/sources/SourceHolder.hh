#ifndef SourceHolder_h
#define SourceHolder_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class SourceHolder
{
public:

  SourceHolder();
  ~SourceHolder();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();
  G4double GetThickness();
  
private:
  Materials* materials;

  G4double hold2Z;
  G4double hold4Y;
  G4double hold1Y;
};

#endif
