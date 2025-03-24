#ifndef SourceHolder20210510B_h
#define SourceHolder20210510B_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class SourceHolder20210510B
{
public:

  SourceHolder20210510B();
  ~SourceHolder20210510B();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();
  G4double GetThickness();
  
private:
  Materials* materials;

  G4double hold1Z;
  G4double hold4Y;
  G4double hold1Y;
};

#endif
