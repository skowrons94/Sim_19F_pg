#ifndef Collimatorddgas_h
#define Collimatorddgas_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class Collimatorddgas
{
public:

  Collimatorddgas();
  ~Collimatorddgas();

public:

  G4LogicalVolume * Construct();

  G4double GetLength();

private:
  Materials* materials;

  G4double outerL;

};

#endif
