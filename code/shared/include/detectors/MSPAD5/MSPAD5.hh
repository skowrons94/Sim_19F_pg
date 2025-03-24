#ifndef MSPAD5_h
#define MSPAD5_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class MSPAD5
{
public:

  G4double GetX();
  G4double GetY();
  MSPAD5();
  ~MSPAD5();

public:

  G4LogicalVolume* Construct(G4int);
  
private:
  Materials* materials;

  G4double ContX;
  G4double ContY;

};

#endif
