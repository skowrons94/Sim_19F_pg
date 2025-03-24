#include "SourceHolder20210510B.hh"

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

SourceHolder20210510B::SourceHolder20210510B(){;}


SourceHolder20210510B::~SourceHolder20210510B(){;}

G4LogicalVolume *SourceHolder20210510B::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,0.,1.0));

  G4double rodX = 10*mm;
  G4double rodY = 10*mm;
  G4double rodL = 600*mm;

  G4double hold1X = 40*mm;
  hold1Y = 6.0*mm;
  hold1Z = 54.2*mm;

  G4double hold2X = 36*mm;
  G4double hold2Y = 6.1*mm;
  G4double hold2Z = 25*mm;

  G4double hold3X = 8*mm;
  G4double hold3Y = 6.1*mm;
  G4double hold3Z = 17.7*mm;

  G4double hold4X = 36*mm;
  hold4Y = 4*mm;
  G4double hold4Z = 25.3*mm;

  G4double hold5Diam = 10*mm;
  G4double hold5L = 1.6*mm;
  auto rot = new G4RotationMatrix();
  rot->rotateX(90*deg);

  G4VSolid* rodSol = new G4Box("rodBox",rodX/2,rodY/2,rodL/2);
  G4VSolid* hold1Sol = new G4Box("hold1Box",hold1X/2,hold1Y/2,hold1Z/2);
  G4VSolid* hold2Sol = new G4Box("hold2Box",hold2X/2,hold2Y/2,hold2Z/2);
  G4VSolid* hold3Sol = new G4Box("hold3Box",hold3X/2,hold3Y/2,hold3Z/2);
  G4VSolid* hold4Sol = new G4Box("hold4Box",hold4X/2,hold4Y/2,hold4Z/2);
  G4VSolid* hold5Sol = new G4Tubs("hold5Tube",0,hold5Diam/2,hold5L/2,0.0,360.0*deg);

  G4SubtractionSolid* holdsub1Sol = new G4SubtractionSolid("holdsub1", hold1Sol, hold2Sol, 0, G4ThreeVector(0,0,-hold1Z/2+hold2Z/2+2*mm));
  G4SubtractionSolid* holdsub2Sol = new G4SubtractionSolid("holdsub2", holdsub1Sol, hold3Sol, 0, G4ThreeVector(0,0,hold1Z/2-hold3Z/2-9.5*mm));
  G4SubtractionSolid* holdsub3Sol = new G4SubtractionSolid("holdsub3", holdsub2Sol, hold4Sol, 0, G4ThreeVector(0,hold1Y/2-hold4Y/2,hold1Z/2-hold4Z/2-2*mm));
  G4SubtractionSolid* holdsub4Sol = new G4SubtractionSolid("holdsub4", holdsub3Sol, hold5Sol, rot, G4ThreeVector(0,-hold1Y/2+hold5L/2+0.5*mm,hold1Z/2-14.5*mm));
  G4UnionSolid* holdSol = new G4UnionSolid("hold", holdsub4Sol, rodSol, 0, G4ThreeVector(0,0,-hold1Z/2-rodL/2));

  G4LogicalVolume* holdLog = new G4LogicalVolume(holdSol,materials->GetMaterial("G4_POLYETHYLENE"),"holdLog",0,0,0);

  holdLog->SetVisAttributes(color);
  
  return holdLog;
}

G4double SourceHolder20210510B::GetLength()
{
  return hold1Z/2-9.5*mm;
}

G4double SourceHolder20210510B::GetThickness()
{
  return hold4Y-hold1Y/2+1.5*mm;
}
