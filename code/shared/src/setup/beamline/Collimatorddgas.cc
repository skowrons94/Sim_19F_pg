#include "Collimatorddgas.hh"

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

Collimatorddgas::Collimatorddgas(){;}


Collimatorddgas::~Collimatorddgas(){;}

G4LogicalVolume *Collimatorddgas::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,1.,1.0));

  G4double outerX = 25*mm;
  G4double outerY = 25*mm;
  outerL = 130*mm;

  G4double cutOut1X = 23*mm;
  G4double cutOut1Y = 23*mm;
  G4double cutOut1L = 98*mm;

  G4double cutOut4X = 23*mm;
  G4double cutOut4Y = 23*mm;
  G4double cutOut4L = 29*mm;

  G4double cutOut2Diam = 6*mm;
  G4double cutOut2L = 1.1*mm;

  G4double cutOut3Diam = 8*mm;
  G4double cutOut3L = 1.1*mm;

  G4VSolid* outerSol = new G4Box("outerBox",outerX/2,outerY/2,outerL/2);
  G4VSolid* cutOut1Sol = new G4Box("cutOut1Box",cutOut1X/2,cutOut1Y/2,cutOut1L/2);
  G4VSolid* cutOut4Sol = new G4Box("cutOut4Box",cutOut4X/2,cutOut4Y/2,cutOut4L/2);
  G4VSolid* cutOut2Sol = new G4Tubs("cutOut2Tube",0,cutOut2Diam/2,cutOut2L/2,0.0,360.0*deg);
  G4VSolid* cutOut3Sol = new G4Tubs("cutOut3Tube",0,cutOut3Diam/2,cutOut3L/2,0.0,360.0*deg);

  G4SubtractionSolid* collimator1Sol = new G4SubtractionSolid("collimator1", outerSol, cutOut1Sol, 0, G4ThreeVector(0,0,-outerL/2+cutOut1L/2+1*mm));
  G4SubtractionSolid* collimator2Sol = new G4SubtractionSolid("collimator2", collimator1Sol, cutOut4Sol, 0, G4ThreeVector(0,0,+outerL/2-cutOut4L/2-1*mm));
  G4SubtractionSolid* collimator3Sol = new G4SubtractionSolid("collimator3", collimator2Sol, cutOut2Sol, 0, G4ThreeVector(0,0,-outerL/2+0.5*mm));
  G4SubtractionSolid* collimatorSol = new G4SubtractionSolid("collimator", collimator3Sol, cutOut3Sol, 0, G4ThreeVector(0,0,+outerL/2-cutOut4L-1.5*mm));

  G4LogicalVolume* collimatorLog = new G4LogicalVolume(collimatorSol,materials->GetMaterial("G4_Al"),"collimatorLog",0,0,0);

  collimatorLog->SetVisAttributes(color);
  
  return collimatorLog;
}

G4double Collimatorddgas::GetLength()
{
  return outerL;
}
