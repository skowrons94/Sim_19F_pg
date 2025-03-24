#ifndef SourceNo110_114_h
#define SourceNo110_114_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class SourceNo110_114
{
public:

  SourceNo110_114();
  ~SourceNo110_114();

public:

  G4LogicalVolume * Construct();

  G4double GetDiameter();
  G4double GetThickness();
  
private:
  Materials* materials;

  G4double srcOutDiam;
  G4double srcL;

};

#endif
