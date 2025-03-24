#include "CuShieldForGeDD20nep.hh"

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

CuShieldForGeDD20nep::CuShieldForGeDD20nep(){;}


CuShieldForGeDD20nep::~CuShieldForGeDD20nep(){;}

G4LogicalVolume *CuShieldForGeDD20nep::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,0.,1.0));

  G4double slabX = 128*mm;
  slabY = 30*mm;
  slabL = 568*mm;

  G4double slabHoleDiam = 104.4*mm;
  //G4double slabHoleDiam = 95*mm;
  G4double slabHoleL = 31*mm;

  G4VSolid* slab1Sol = new G4Box("slab1Box",slabX/2,slabY/2,slabL/2);
  G4VSolid* slabHoleSol = new G4Tubs("slabHoleTube",0,slabHoleDiam/2,slabHoleL/2,0.0,360.0*deg);
  G4RotationMatrix* rotHole = new G4RotationMatrix();
  rotHole->rotateX(90*deg);
  //G4SubtractionSolid* slabSol = new G4SubtractionSolid("slab", slab1Sol, slabHoleSol, rotHole, G4ThreeVector(0,0,-slabL/2+120*mm));
  G4SubtractionSolid* slabSol = new G4SubtractionSolid("slab", slab1Sol, slabHoleSol, rotHole, G4ThreeVector(0,0,-slabL/2+111*mm));
  
  G4LogicalVolume* slabLog = new G4LogicalVolume(slabSol,materials->GetMaterial("G4_Cu"),"slabLog",0,0,0);

  slabLog->SetVisAttributes(color);
  
  return slabLog;
}

G4double CuShieldForGeDD20nep::GetLength()
{
  return slabL;
}
G4double CuShieldForGeDD20nep::GetHeight()
{
  return slabY;
}
