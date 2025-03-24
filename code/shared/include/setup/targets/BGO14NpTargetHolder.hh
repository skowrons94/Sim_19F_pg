#ifndef BGO14NpTargetHolder_h
#define BGO14NpTargetHolder_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;
class BGO14NpTargetHolderMessenger;

class BGO14NpTargetHolder
{
public:

  BGO14NpTargetHolder();
  ~BGO14NpTargetHolder();

  static BGO14NpTargetHolder* GetInstance();

public:
  void SetBGO14NpTargetBackingThickness(std::vector<G4double> fbgo14NpTargetBackingThickness) {bgo14NpTargetBackingThickness = fbgo14NpTargetBackingThickness;};
  G4double GetTargetPosition();
  G4LogicalVolume* Construct();
  
private:
  Materials* materials;
  BGO14NpTargetHolderMessenger* bgo14NpTargetHolderMessenger;

  static BGO14NpTargetHolder* instance;

  std::vector<G4double> bgo14NpTargetBackingThickness;

  G4double lengthHolderLower;
  G4double lengthHolderMid;
  G4double lengthHolderUpper;
};

#endif
