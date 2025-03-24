#include "SourceNo138_139_140.hh"

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

SourceNo138_139_140::SourceNo138_139_140(){;}


SourceNo138_139_140::~SourceNo138_139_140(){;}

G4LogicalVolume *SourceNo138_139_140::Construct()
{
  materials = Materials::GetInstance();

  G4bool checkOverlaps = false;

  G4VisAttributes *color1 = new G4VisAttributes(G4Colour(1.0,0.,6.0));

  sourceInDiam = 0.*mm;
  sourceOutDiam = 31.5*mm;
  sourceThickness = 0.5*mm;

  G4VSolid* sourceSol = new G4Tubs("sourceTube",sourceInDiam/2,sourceOutDiam/2,sourceThickness/2,0.0,360.0*deg);
  G4LogicalVolume* sourceLog = new G4LogicalVolume(sourceSol,materials->GetMaterial("G4_POLYETHYLENE"),"sourceLog",0,0,0);

  sourceLog->SetVisAttributes(color1);

  return sourceLog;
  
}

G4double SourceNo138_139_140::GetDiameter()
{
  return sourceHolderOutDiam/2;
}

G4double SourceNo138_139_140::GetThickness()
{
  return sourceThickness/2;
}
