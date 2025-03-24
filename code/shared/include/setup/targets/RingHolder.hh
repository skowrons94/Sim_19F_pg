#ifndef RingHolder_h
#define RingHolder_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class RingHolder
{
public:

  RingHolder();
  ~RingHolder();

public:
  G4double GetLength();
  G4LogicalVolume* Construct();

private:
  Materials* materials;
  G4double lengthRingHolder;
};

#endif

