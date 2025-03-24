#ifndef GeBO_h
#define GeBO_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;
class GeBOMessenger;

class GeBO
{
public:

  GeBO();
  ~GeBO();

  static GeBO* GetInstance();

public:

  G4LogicalVolume* Construct();

  G4double GetLength();

  void SetDeadSide(G4double fDeadSide) {DeadSide = fDeadSide;};
  void SetDeadFront(G4double fDeadFront) {DeadFront = fDeadFront;};
  void SetDeadBack(G4double fDeadBack) {DeadBack = fDeadBack;};
  void SetDeadHole(G4double fDeadHole) {DeadHole = fDeadHole;};
  
private:
  Materials* materials;
  GeBOMessenger* geBOMessenger;

  G4double DeadSide;
  G4double DeadFront;
  G4double DeadBack;
  G4double DeadHole;
  G4double OuterCasingLength;

  static GeBO* instance;
};

#endif
