#ifndef TargetChamber16op_h
#define TargetChamber16op_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;
class TargetChamber16opMessenger;

class TargetChamber16op
{
public:

  TargetChamber16op();
  ~TargetChamber16op();
  static TargetChamber16op* GetInstance();
  

public:

  G4double GetLength();
  G4LogicalVolume* Construct();
  void SetTargetCh16opMat(G4String fTargetCh16opType) {TargetCh16opType = fTargetCh16opType;};
  
private:
  Materials* materials;
  TargetChamber16opMessenger* targetchamber16opMessenger;

  G4double lengthCounterFlange;
  G4double lengthTube;
  G4double lengthCF40;
  G4double lengthCF100;
  G4String TargetCh16opType;
  
  static TargetChamber16op* instance;
};

#endif
