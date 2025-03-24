#ifndef TargetHolderOuterFront10b_h
#define TargetHolderOuterFront10b_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;
class TargetHolderOuterFront10bMessenger;

class TargetHolderOuterFront10b
{
public:
  TargetHolderOuterFront10b();
  ~TargetHolderOuterFront10b();
  void SetFileName(G4String filename) {fileName = filename;};
  static TargetHolderOuterFront10b* GetInstance();

public:

  G4LogicalVolume * Construct();
  
private:
  G4String fileName;
  Materials* materials;
  TargetHolderOuterFront10bMessenger* targetholderouterfront10bMessenger;

  static TargetHolderOuterFront10b* instance;
};

#endif
