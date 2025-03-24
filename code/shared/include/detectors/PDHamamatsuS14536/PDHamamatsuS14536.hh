#ifndef PDHamamatsuS14536_h
#define PDHamamatsuS14536_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class PDHamamatsuS14536
{
public:

  G4double GetX();
  G4double GetY();
  PDHamamatsuS14536();
  ~PDHamamatsuS14536();

public:

  G4LogicalVolume* Construct(G4int);
  
private:
  Materials* materials;

  G4double ContX;
  G4double ContY;

};

#endif
