#ifndef InnerLeadShielding16op_h
#define InnerLeadShielding16op_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class InnerLeadShielding16op
{
public:

  InnerLeadShielding16op();
  ~InnerLeadShielding16op();

public:

  G4double GetLength();
  G4LogicalVolume* Construct();
  
private:
  Materials* materials;

  G4double ShieldL;
};

#endif
