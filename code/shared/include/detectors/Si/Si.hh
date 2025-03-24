#ifndef Si_h
#define Si_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class Si
{
public:

  Si();
  ~Si();

public:

  G4LogicalVolume* Construct();
  
private:
  Materials* materials;
};

#endif
