#include "BGO14NpTarget.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "BGO14NpTargetMessenger.hh"



BGO14NpTarget::BGO14NpTarget(){
  bgo14NpTargetMessenger = new BGO14NpTargetMessenger(this);
}


BGO14NpTarget::~BGO14NpTarget(){
  delete bgo14NpTargetMessenger;
}

BGO14NpTarget* BGO14NpTarget::instance = 0;

BGO14NpTarget* BGO14NpTarget::GetInstance()
{
  if (instance == 0)
    {
      instance = new BGO14NpTarget;

    }
  return instance;
}

G4LogicalVolume* BGO14NpTarget::Construct()
{
  materials = Materials::GetInstance();

  G4cout << "BGO14NpTarget.cc: got Materials object instance" << G4endl;
     
  //Target layers solid volumes
  if (&bgo14NpTargetSize == NULL || bgo14NpTargetSize.empty()) {
    G4cout << "BGO14NpTarget.cc: target size vector was null or empty. Setting to default (3.0 mm r, 0.1 um z)" << G4endl;
    bgo14NpTargetSize = { 3.0, 0.0001 };
  }
  G4cout << "BGO14NpTarget.cc: target size = " << bgo14NpTargetSize[0] << " mm radius, " << bgo14NpTargetSize[1] << " mm thickness" << G4endl;
  G4Tubs *TargetSol  = new G4Tubs("TargetSolid", 0., bgo14NpTargetSize[0]*mm, 0.5*bgo14NpTargetSize[1]*mm, 0.*deg,360.*deg);
  
  G4cout << "BGO14NpTarget.cc: created target solid" << G4endl;

  // Target layers logical volumes
  TargetLog = new G4LogicalVolume(TargetSol, materials->GetMaterial("TargetMat"), "TargetLogical",0,0,0);
  
  G4cout << "BGO14NpTarget.cc: created target logical volume" << G4endl;

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,0.,6.0));
  TargetLog->SetVisAttributes(color);

  G4cout << "BGO14NpTarget.cc: set target visual attributes" << G4endl;

  return TargetLog;

}

/*G4LogicalVolume* BGO14NpTarget::GetTargetLog(G4int fTargetSlice)
  {
  TargetSlice = fTargetSlice;
  return TargetLayerLog[TargetSlice];
  }*/

G4LogicalVolume* BGO14NpTarget::GetTargetLog()
{
  return TargetLog;
}

G4double BGO14NpTarget::GetTargetThickness()
{
  G4double bgo14NpTargetThickness = bgo14NpTargetSize[1];
  G4cout << "Target thickness = " << bgo14NpTargetThickness << G4endl;
  return bgo14NpTargetThickness;
}
