#ifndef LeadShielding16op_h
#define LeadShielding16op_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class LeadShielding16op
{
public:

  LeadShielding16op();
  ~LeadShielding16op();

public:

  G4double GetLength();
  G4double GetWidth();
  G4LogicalVolume* Construct();
  
private:
  Materials* materials;

  G4double lengthBox3;
  G4double lengthBox4;
};

#endif
