#include "TargetHolder16op.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4UnionSolid.hh"
#include "G4Polycone.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

TargetHolder16op::TargetHolder16op(){;}


TargetHolder16op::~TargetHolder16op(){;}

G4LogicalVolume *TargetHolder16op::Construct()
{
  materials = Materials::GetInstance();
  
  lengthHolderLower = 10.0 * mm;
  G4double rInnerHolderLower = 54/2 * mm;
  G4double rOuterHolderLower = 58/2 * mm;
  
  lengthHolderMid = 1.7 * mm;
  G4double rInnerHolderMid = 0 * mm;
  G4double rOuterHolderMid = 58/2 * mm;
  
  lengthHolderUpper = 11.0 * mm;
  G4double rInnerHolderUpper = 0 * mm;
  G4double rOuterHolderUpper = 40.5/2 * mm;
  
  G4double lengthTargetBacking = 0.25 * mm;
  G4double rInnerTargetBacking = 0/2 * mm;
  G4double rOuterTargetBacking = 30/2 * mm;
  
  G4double lengthWater = 9.2*mm-lengthTargetBacking;
  G4double rInnerWater = 0 * mm;
  G4double rOuterWater = 23.2/2 * mm;
  
  G4double phiStart = 0*deg;
  G4double phiTotal = 360*deg;
  
  auto solidLower
    = new G4Tubs("Lower",
		 rInnerHolderLower, rOuterHolderLower,
		 0.5*lengthHolderLower,
		 phiStart,phiTotal);
  
  auto solidMid
    = new G4Tubs("Mid",
		 rInnerHolderMid, rOuterHolderMid,
		 0.5*lengthHolderMid,
		 phiStart,phiTotal);
  
  auto solidUpper
    = new G4Tubs("Upper",
		 rInnerHolderUpper, rOuterHolderUpper,
		 0.5*lengthHolderUpper,
		 phiStart,phiTotal);
  
  auto solidTargetBacking
    = new G4Tubs("TargetBacking",
		 rInnerTargetBacking, rOuterTargetBacking,
		 0.5*lengthTargetBacking,
		 phiStart,phiTotal);
  
  auto solidWater
    = new G4Tubs("Water",
		 rInnerWater, rOuterWater,
		 0.5*lengthWater,
		 phiStart,phiTotal);
  
  
  auto solidUni0 = new G4UnionSolid("Uni0",solidLower,solidMid,0,G4ThreeVector(0,0,lengthHolderLower/2+lengthHolderMid/2));
  auto solidHolder = new G4UnionSolid("Uni1",solidUni0,solidUpper,0,G4ThreeVector(0,0,lengthHolderLower/2+lengthHolderMid+lengthHolderUpper/2));
  

  G4LogicalVolume* logicHolder = new G4LogicalVolume(solidHolder, materials->GetMaterial("G4_Al"), "logicHolder");
  G4LogicalVolume* logicTargetBacking = new G4LogicalVolume(solidTargetBacking, materials->GetMaterial("G4_Ta"), "logicTargetBacking");                          
  G4LogicalVolume* logicWater = new G4LogicalVolume(solidWater, materials->GetMaterial("G4_WATER"), "logicWater");                          

  G4VPhysicalVolume *physWater = new G4PVPlacement(0, G4ThreeVector(0.,0.,lengthHolderLower/2+lengthWater/2+lengthTargetBacking), logicWater, "physWater", logicHolder, false, 0, true);
  G4VPhysicalVolume *physTargetBacking = new G4PVPlacement(0, G4ThreeVector(0.,0.,lengthHolderLower/2+lengthTargetBacking/2), logicTargetBacking, "physTargetBacking", logicHolder, false, 0, true);
  
  
  
  
  
  logicHolder->SetVisAttributes(G4VisAttributes(G4Colour::Red()));
  logicTargetBacking->SetVisAttributes(G4VisAttributes(G4Colour::Grey()));
  logicWater->SetVisAttributes(G4VisAttributes(G4Colour::Blue()));
  
  return logicHolder;
}
G4double TargetHolder16op::GetTargetPosition()
{
  return lengthHolderLower/2;
}
