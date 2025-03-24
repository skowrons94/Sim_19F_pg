#ifndef BGO14NpTarget_h
#define BGO14NpTarget_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4AssemblyVolume.hh"

class Materials;
class BGO14NpTargetMessenger;

class BGO14NpTarget
{
public:

  BGO14NpTarget();
  ~BGO14NpTarget();

  static BGO14NpTarget* GetInstance();
  

public:

  G4LogicalVolume* Construct();
  void SetBGO14NpTargetSize(std::vector<G4double> fbgo14NpTargetSize) {bgo14NpTargetSize = fbgo14NpTargetSize;};
  
  //G4LogicalVolume* GetTargetLog(G4int);
  G4LogicalVolume* GetTargetLog();
  G4double GetTargetThickness();
  
  
private:
  Materials* materials;
  BGO14NpTargetMessenger* bgo14NpTargetMessenger;
  
  static BGO14NpTarget* instance;
  
  std::vector<G4double> bgo14NpTargetSize;
  
  
  G4int TargetSlice;
  
  G4LogicalVolume* TargetLog;
  
};

#endif
