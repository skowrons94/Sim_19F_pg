#ifndef GePD_h
#define GePD_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;
class GePDMessenger;

class GePD
{
public:

  GePD();
  ~GePD();

  static GePD* GetInstance();

public:

  G4LogicalVolume* Construct();

  void SetDeadSide(G4double fDeadSide) {DeadSide = fDeadSide;};
  void SetDeadFront(G4double fDeadFront) {DeadFront = fDeadFront;};
  void SetDeadBack(G4double fDeadBack) {DeadBack = fDeadBack;};
  void SetDisp(G4double fDisp) {Disp = fDisp;};
  
private:
  Materials* materials;
  GePDMessenger* gePDMessenger;

  G4double DeadSide;
  G4double DeadFront;
  G4double DeadBack;
  G4double Disp;

  static GePD* instance;
};

#endif
