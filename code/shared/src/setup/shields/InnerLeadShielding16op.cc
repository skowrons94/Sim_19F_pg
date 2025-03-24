#include "InnerLeadShielding16op.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4Polycone.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4ExtrudedSolid.hh"

InnerLeadShielding16op::InnerLeadShielding16op(){;}


InnerLeadShielding16op::~InnerLeadShielding16op(){;}

G4LogicalVolume *InnerLeadShielding16op::Construct()
{
  materials = Materials::GetInstance();
  
  G4double GeHoleDiam = 130*mm;
  G4double GeHoleL = 300*mm;

  G4double ShieldInnerDiam = 200*mm;
  G4double ShieldOuterDiam = 290*mm;
  ShieldL = 471.5*mm;

  G4double ShieldCutX = 10*mm;
  G4double ShieldCutY = 291*mm;
  G4double ShieldCutZ = 160.5*mm;

  auto solidGeHole
    = new G4Tubs("GeHole",
		 0, GeHoleDiam/2,
		 GeHoleL/2,
		 0*deg,360*deg);

  auto solidShield0
    = new G4Tubs("Shield0",
		 ShieldInnerDiam/2, ShieldOuterDiam/2,
		 ShieldL/2,
		 0*deg,360*deg);

  auto solidShieldCut
    = new G4Box("ShieldCut",
		 ShieldCutX/2, ShieldCutY/2,
		 ShieldCutZ/2);


  G4VSolid *solidSub0 = new G4SubtractionSolid("Sub0", solidShield0, solidShieldCut, 0, G4ThreeVector(0,0,-ShieldL/2+ShieldCutZ/2-1*mm));

  G4RotationMatrix* rotGeHole = new G4RotationMatrix();
  rotGeHole->rotateY(55*deg);

  G4VSolid *solidShield = new G4SubtractionSolid("Shield", solidSub0, solidGeHole, rotGeHole, G4ThreeVector(-ShieldOuterDiam/2,0,-ShieldL/2+258*mm+8.55*mm));
  
  G4LogicalVolume *logicInnerShield = new G4LogicalVolume(solidShield, materials->GetMaterial("G4_Pb"), "logicInnerShield");
  
  logicInnerShield->SetVisAttributes(G4VisAttributes(G4Colour::Black()));
  
  return logicInnerShield;
}

G4double InnerLeadShielding16op::GetLength()
{
  return ShieldL;
}
