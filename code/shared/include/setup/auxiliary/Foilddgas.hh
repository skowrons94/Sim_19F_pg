#ifndef Foilddgas_h
#define Foilddgas_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class Foilddgas
{
public:
  Foilddgas();
  ~Foilddgas();

public:

  G4LogicalVolume * Construct(G4double);
  
private:
  Materials* materials;

};

#endif
