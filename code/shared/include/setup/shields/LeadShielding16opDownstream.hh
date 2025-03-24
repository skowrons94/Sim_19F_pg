#ifndef LeadShielding16opDownstream_h
#define LeadShielding16opDownstream_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class LeadShielding16opDownstream
{
public:

  LeadShielding16opDownstream();
  ~LeadShielding16opDownstream();

public:

  G4double GetLength();
  G4double GetWidth();
  G4LogicalVolume* Construct();
  
private:
  Materials* materials;

  G4double lengthBox4;
};

#endif
