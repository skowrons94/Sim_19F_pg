#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class Materials;
class DetectorConstructionMessenger;
class BGO14NpSD;
class LeadShielding16op;
class BGO14Np;
class BGO14NpTarget;
class BGO14NpTargetHolder;
class ColdFinger16op;
class TargetChamber16op;
class SourceNo62;
class SourceHolder20210510A;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  
  DetectorConstruction();
  virtual ~DetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  G4LogicalVolume* GetSensitiveDetector(G4VPhysicalVolume* aVolume,G4int depth=0);

  void SetSourcePos(G4ThreeVector fSourcePos) {SourcePos = fSourcePos;};
  void SetBGO14NpPos(G4ThreeVector fBGO14NpPos) {BGO14NpPos = fBGO14NpPos;};
  void SetBGO14NpTargetHolderPos(G4ThreeVector fBGO14NpTargetHolderPos) {BGO14NpTargetHolderPos = fBGO14NpTargetHolderPos;};
  void SetPhysics(G4String fPhysics) {Physics = fPhysics;};
  void SetMaxStep(G4double fMaxStep) {MaxStep = fMaxStep;};
  void SetSourceHolder(G4String fSourceHolder) {SourceHolder = fSourceHolder;};

  G4ThreeVector GetSourcePos();
  G4String GetPhysics();
  G4String GetSourceHolder();

private:
  void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);

  Materials* materials;
  DetectorConstructionMessenger* detectorConstructionMessenger;

  G4LogicalVolume* SensitiveLogicalVolume;

  G4ThreeVector SourcePos;
  G4ThreeVector BGO14NpPos;
  G4ThreeVector BGO14NpTargetHolderPos;
  G4String Physics;
  G4String SourceHolder;
  LeadShielding16op* ALeadShielding;
  BGO14Np* ABGO;
  BGO14NpTarget* ATarget;
  BGO14NpTargetHolder* ATargetHolder;
  TargetChamber16op* ATargetChamber;
  G4double MaxStep;
  ColdFinger16op* AColdFinger;


};

#endif
