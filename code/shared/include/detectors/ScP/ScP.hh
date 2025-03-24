#ifndef ScP_h
#define ScP_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;

class ScP
{
public:

  ScP();
  ~ScP();

  static ScP* GetInstance();

public:

  G4LogicalVolume* Construct();
  
private:
  Materials* materials;
  static ScP* instance;
};

#endif
