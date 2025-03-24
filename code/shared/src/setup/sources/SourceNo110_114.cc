#include "SourceNo110_114.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

SourceNo110_114::SourceNo110_114(){;}


SourceNo110_114::~SourceNo110_114(){;}

G4LogicalVolume *SourceNo110_114::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(0.,0.,1.0));

  G4double srcInDiam = 0*mm;
  srcOutDiam = 10*mm;
  srcL = 3.0*mm;

  G4VSolid* srcSol = new G4Tubs("srcTube",srcInDiam/2,srcOutDiam/2,srcL/2,0.0,360.0*deg);

  G4LogicalVolume* srcLog = new G4LogicalVolume(srcSol,materials->GetMaterial("G4_POLYETHYLENE"),"srcLog",0,0,0);

  srcLog->SetVisAttributes(color);
  
  return srcLog;
}

G4double SourceNo110_114::GetDiameter()
{
  return srcOutDiam/2;
}

G4double SourceNo110_114::GetThickness()
{
  return srcL/2;
}
