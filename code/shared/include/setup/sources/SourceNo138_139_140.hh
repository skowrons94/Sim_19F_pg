#ifndef SourceNo138_139_140_h
#define SourceNo138_139_140_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class SourceNo138_139_140
{
public:

  SourceNo138_139_140();
  ~SourceNo138_139_140();

public:

  G4LogicalVolume * Construct();

  G4double GetDiameter();
  G4double GetThickness();
  
private:
  Materials* materials;

  G4double sourceHolderInDiam;
  G4double sourceHolderOutDiam;
  G4double sourceHolderThickness;

  G4double sourceInDiam;
  G4double sourceOutDiam;
  G4double sourceThickness;

  //G4double src1aOutDiam;
  //G4double src1aL;

};

#endif
