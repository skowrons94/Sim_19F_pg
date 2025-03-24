#include "CuShieldForGePD20nep.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

CuShieldForGePD20nep::CuShieldForGePD20nep(){;}


CuShieldForGePD20nep::~CuShieldForGePD20nep(){;}

G4LogicalVolume *CuShieldForGePD20nep::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,0.,1.0));

  G4double shieldInnerDiam = 118*mm;
  shieldOuterDiam = 198*mm;
  shieldL = 250*mm;

  G4double shieldCutDiam = 120*mm;
  G4double shieldCutL = 100*mm;

  G4RotationMatrix *rotCut = new G4RotationMatrix();
  rotCut->rotateX(26.22*deg);

  G4VSolid* shield1Sol = new G4Tubs("shield1Tube",shieldInnerDiam/2,shieldOuterDiam/2,shieldL/2,0.0,360.0*deg);
  G4VSolid* shieldCutSol = new G4Tubs("shieldCutTube",0,shieldCutDiam/2,shieldCutL/2,0.0,360.0*deg);
  G4SubtractionSolid* shieldSol = new G4SubtractionSolid("shield", shield1Sol, shieldCutSol, rotCut, G4ThreeVector(0,shieldInnerDiam/2-40.35*mm,shieldL/2));
  
  G4LogicalVolume* shieldLog = new G4LogicalVolume(shieldSol,materials->GetMaterial("G4_Cu"),"shieldLog",0,0,0);

  shieldLog->SetVisAttributes(color);
  
  return shieldLog;
}

G4double CuShieldForGePD20nep::GetLength()
{
  return shieldL;
}

G4double CuShieldForGePD20nep::GetDiameter()
{
  return shieldOuterDiam;
}
