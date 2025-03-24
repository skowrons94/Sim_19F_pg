#include "Chamberddgas.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

Chamberddgas::Chamberddgas(){;}


Chamberddgas::~Chamberddgas(){;}

G4LogicalVolume *Chamberddgas::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,1.,1.0));

  chamberOuterDiam = 520*mm;
  G4double chamberInnerDiam = 510*mm;
  G4double chamberL = 10*cm;

  G4VSolid* chamberSol = new G4Tubs("chamberTube",chamberInnerDiam/2,chamberOuterDiam/2,chamberL/2,0.0,360.0*deg);

  G4LogicalVolume* chamberLog = new G4LogicalVolume(chamberSol,materials->GetMaterial("G4_Al"),"chamberLog",0,0,0);

  chamberLog->SetVisAttributes(color);
  
  return chamberLog;
}

G4double Chamberddgas::GetLength()
{
  return chamberOuterDiam;
}
