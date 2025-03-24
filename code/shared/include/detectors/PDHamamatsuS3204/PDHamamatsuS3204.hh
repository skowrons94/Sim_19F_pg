#ifndef PDHamamatsuS3204_h
#define PDHamamatsuS3204_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class PDHamamatsuS3204
{
public:

  G4double GetX();
  G4double GetY();
  PDHamamatsuS3204();
  ~PDHamamatsuS3204();

public:

  G4LogicalVolume* Construct(G4int);
  
private:
  Materials* materials;

  G4double ContX;
  G4double ContY;

};

#endif
