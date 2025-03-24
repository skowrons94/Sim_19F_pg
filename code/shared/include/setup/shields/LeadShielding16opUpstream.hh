#ifndef LeadShielding16opUpstream_h
#define LeadShielding16opUpstream_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class LeadShielding16opUpstream
{
public:

  LeadShielding16opUpstream();
  ~LeadShielding16opUpstream();

public:

  G4double GetLength();
  G4double GetWidth();
  G4LogicalVolume* Construct();
  
private:
  Materials* materials;

  G4double lengthBox3;
};

#endif
