#ifndef Chamberddgas_h
#define Chamberddgas_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class Chamberddgas
{
public:

  Chamberddgas();
  ~Chamberddgas();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();

private:
  Materials* materials;

  G4double chamberOuterDiam;

};

#endif
