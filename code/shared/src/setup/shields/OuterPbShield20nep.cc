#include "OuterPbShield20nep.hh"

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

OuterPbShield20nep::OuterPbShield20nep(){;}


OuterPbShield20nep::~OuterPbShield20nep(){;}

G4LogicalVolume *OuterPbShield20nep::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(0.2,0.2,0.0));

  G4double outerX = 600*mm;
  G4double outerY = 612*mm;
  outerL = 568*mm;

  G4double cutOutChX = 128*mm+12*mm; // left: 10 mm gap, right: 2 mm gap
  G4double cutOutChY = 112*mm+30*mm+5*mm+6*mm; // Cu for GeDD: 30 mm, bottom: 5 mm, top: 6 mm 
  G4double cutOutChL = 569*mm;

  G4double holeDDDiam = 104.4*mm;
  //G4double holeDDDiam = 95*mm;
  G4double holeDDL = 221*mm;

  G4double holePDDiam = 198*mm;
  G4double holePDL = 251*mm;

  G4VSolid* outerSol = new G4Box("outerBox",outerX/2,outerY/2,outerL/2);
  G4VSolid* cutOutChSol = new G4Box("cutOutChBox",cutOutChX/2,cutOutChY/2,cutOutChL/2);
  G4VSolid* holeDDSol = new G4Tubs("holeDDTube",0,holeDDDiam/2,holeDDL/2,0.0,360.0*deg);
  G4VSolid* holePDSol = new G4Tubs("holePDTube",0,holePDDiam/2,holePDL/2,0.0,360.0*deg);

  G4RotationMatrix* rotHole = new G4RotationMatrix();
  rotHole->rotateX(90*deg);

  G4SubtractionSolid* outerPbShield1Sol = new G4SubtractionSolid("outerPbShield1", outerSol, cutOutChSol, 0, G4ThreeVector(4*mm,15*mm+0.5*mm,0)); // X: half of difference between left and right gap, Y: Cu + half of difference between top and bottom gap
  //G4SubtractionSolid* outerPbShield2Sol = new G4SubtractionSolid("outerPbShield2", outerPbShield1Sol, holeDDSol, rotHole, G4ThreeVector(0,outerY/2-holeDDL/2+1*mm,-outerL/2+120*mm));
  G4SubtractionSolid* outerPbShield2Sol = new G4SubtractionSolid("outerPbShield2", outerPbShield1Sol, holeDDSol, rotHole, G4ThreeVector(0,outerY/2-holeDDL/2+1*mm,-outerL/2+111*mm));
  G4SubtractionSolid* outerPbShieldSol = new G4SubtractionSolid("outerPbShield", outerPbShield2Sol, holePDSol, rotHole, G4ThreeVector(0,-outerY/2+holePDL/2-0.99*mm,-outerL/2+184*mm));


  G4LogicalVolume* outerPbShieldLog = new G4LogicalVolume(outerPbShieldSol,materials->GetMaterial("G4_Pb"),"outerPbShieldLog",0,0,0);

  outerPbShieldLog->SetVisAttributes(color);
  
  return outerPbShieldLog;
}

G4double OuterPbShield20nep::GetLength()
{
  return outerL;
}
