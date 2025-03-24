#include "Target.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

Target::Target(){;}


Target::~Target(){;}

G4LogicalVolume *Target::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,0.,1.0));

  targetL = 0.1*um;

  //G4Box *TargetSol = new G4Box("TargetSolid", 1*cm, 1*cm, 0.980392157E-6*cm);
  //G4Box *TargetSol = new G4Box("TargetSolid", 0.5*cm, 0.5*cm, 5E-6*cm); // 10 ug/cm2
  G4VSolid *TargetSol = new G4Tubs("TargetSolid", 0.0*cm, 15*mm, targetL/2, 0*deg, 360*deg);

  G4LogicalVolume *TargetLog = new G4LogicalVolume(TargetSol, materials->GetMaterial("Ta2O165"), "TargetLogical");
  //G4LogicalVolume *TargetLog = new G4LogicalVolume(TargetSol, materials->GetMaterial("N14gas"), "TargetLogical");
  //G4LogicalVolume *TargetLog = new G4LogicalVolume(TargetSol, materials->GetMaterial("G4_Si"), "TargetLogical");
  //G4LogicalVolume *TargetLog = new G4LogicalVolume(TargetSol, materials->GetMaterial("G4_C"), "TargetLogical");
  
  TargetLog->SetVisAttributes(color);
  
  return TargetLog;
}
G4double Target::GetTargetThickness()
{
  return targetL;
}
