#include "GeBO.hh"
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

#include "GeBOMessenger.hh"

GeBO::GeBO(){
  geBOMessenger = new GeBOMessenger(this);

}


GeBO::~GeBO(){
  delete geBOMessenger;
}

GeBO* GeBO::instance = 0;

GeBO* GeBO::GetInstance()
{
  if (instance == 0)
    {
      instance = new GeBO;

    }
  return instance;
}

G4LogicalVolume *GeBO::Construct()
{
  materials = Materials::GetInstance();

  G4double outerCasingDiameter = 95*mm;
  OuterCasingLength = 180*mm;

  G4double outerCasingRadialThickness = 1*mm;
  G4double outerCasingFrontThickness  = 1*mm;

  G4double innerCasingDiameter = 90*mm;
  G4double innerCasingLength = 130*mm;
  G4double mylarThickness = 0.03*mm;
  G4double innerCasingFrontThickness = 0.03*mm;
  G4double innerCasingRadialThickness = 0.76*mm;
  G4double innerCasingBackThickness = 3.2*mm;
  G4double innerCasingHoleDiameter = 10.0*mm;
  G4double innercasingRadialLength = innerCasingLength-innerCasingFrontThickness-innerCasingBackThickness;

  // Outer case
  G4VSolid* outerCaseSol        = new G4Tubs("gecaseTube",0.0*mm,outerCasingDiameter/2,OuterCasingLength/2,0.0,360.0*deg);
  
  G4LogicalVolume* outerCaseLog = new G4LogicalVolume(outerCaseSol,materials->GetMaterial("G4_Al"),"outercaseLog");

  // Ge vacuum
  G4VSolid* gevacSol        = new G4Tubs("gevacTube",0.0*mm,outerCasingDiameter/2 - outerCasingRadialThickness ,OuterCasingLength/2 - outerCasingFrontThickness,0.0,360.0*deg);
  
  G4LogicalVolume* gevacLog = new G4LogicalVolume(gevacSol,materials->GetMaterial("G4_Galactic"),"gevacLog");

  // Inner casing
  // Mylar  
  G4VSolid* geIncaseMylarSol        = new G4Tubs("geIncaseMylarTube",0.0*mm,innerCasingDiameter/2,mylarThickness,0.0,360.0*deg);

  G4LogicalVolume* geIncaseMylarLog = new G4LogicalVolume(geIncaseMylarSol,materials->GetMaterial("G4_MYLAR"),"geincaseMylarLog");

  // Aluminum
  G4VSolid* geIncaseFrontAlSol   = new G4Tubs("geIncaseFrontAlTube",0.0*mm,innerCasingDiameter/2,innerCasingFrontThickness/2,0.0,360.0*deg);
  G4VSolid* geIncaseLateralAlSol = new G4Tubs("geIncaseLateralAlTube",innerCasingDiameter/2-innerCasingRadialThickness,innerCasingDiameter/2,innercasingRadialLength/2,0.0,360.0*deg);
  G4VSolid* geIncaseBackAlSol    = new G4Tubs("geIncaseBackAl",innerCasingHoleDiameter/2,innerCasingDiameter/2,innerCasingBackThickness/2,0.0,360.0*deg);
  G4UnionSolid* geIncaseUn1Sol   = new G4UnionSolid("geIncaseun1", geIncaseLateralAlSol, geIncaseFrontAlSol, 0, G4ThreeVector(0,0,innercasingRadialLength/2+innerCasingFrontThickness/2));
  G4UnionSolid* geIncaseUn2Sol   = new G4UnionSolid("geIncaseun2", geIncaseUn1Sol, geIncaseBackAlSol, 0, G4ThreeVector(0,0,-innercasingRadialLength/2-innerCasingBackThickness/2));
  
  G4LogicalVolume* geIncaseAlLog = new G4LogicalVolume(geIncaseUn2Sol,materials->GetMaterial("G4_Al"),"geincaseAlLog");

  // Detector

  G4double detectorLength       = 84.6*mm;
  G4double detectorDiameter     = 87.8*mm;
  G4double detectorHoleLength   = 76.9*mm;
  G4double detectorHoleDiameter = 9.7*mm;
  G4double detectorLiveLength   = detectorLength - DeadFront - DeadBack;
  G4double detectorLiveDiameter = detectorDiameter - 2*DeadSide;

  // Dead Ge

  G4VSolid* gedeadSol        = new G4Tubs("gedeadTube",0.0*mm,detectorDiameter/2,detectorLength/2,0.0,360.0*deg);
  G4VSolid* gedeadHoleSol    = new G4Tubs("gedeadHoleTube",0.0*mm,detectorHoleDiameter/2,detectorHoleLength/2,0.0,360.0*deg);
  G4VSolid* gedeadSubSol     = new G4SubtractionSolid("gedeadSub", gedeadSol, gedeadHoleSol,0, G4ThreeVector(0,0,-(detectorLength/2-detectorHoleLength/2)));
  
  G4LogicalVolume* gedeadLog = new G4LogicalVolume(gedeadSubSol,materials->GetMaterial("G4_Ge"),"gedeadLog");

  // Ge
  G4VSolid* geSol        = new G4Tubs("geTube",0.0*mm,detectorLiveDiameter/2,detectorLiveLength/2,0.0,360.0*deg);
  G4VSolid* geHoleSol    = new G4Tubs("geHoleTube",0.0*mm,detectorHoleDiameter/2+DeadHole,detectorHoleLength/2+DeadHole,0.0,360.0*deg);
  G4VSolid* geSubSol     = new G4SubtractionSolid("geSubTube", geSol, geHoleSol,0, G4ThreeVector(0,0,-detectorLiveLength/2+detectorHoleLength/2-DeadBack));
  
  G4LogicalVolume* geLog = new G4LogicalVolume(geSubSol,materials->GetMaterial("G4_Ge"),"geLog");

  G4double innerDetectorPosition    = 4*mm;
  G4double Disp                     = (OuterCasingLength - innerCasingLength)/2 - outerCasingFrontThickness - innerDetectorPosition;
  G4double detectorWrappingDistance = 0.7*mm;

  auto *gevacPhys         = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,0.0*mm),gevacLog,"gevacphys",outerCaseLog,0,2);  
  auto *geIncaseMylarPhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,Disp + innerCasingLength/2 + mylarThickness/2),geIncaseMylarLog,"geIncaseMylarPhys",gevacLog,0,2);  
  auto *geIncaseAlPhys    = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,Disp),geIncaseAlLog,"geIncaseAlPhys",gevacLog,0,2);  
  auto *gedeadPhys        = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,Disp+(innercasingRadialLength/2-detectorLength/2)-detectorWrappingDistance),gedeadLog,"gedeadPhys",gevacLog,0,2);
  auto *gePhys            = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,DeadBack-(detectorLength/2-detectorLiveLength/2)),geLog,"gePhys",gedeadLog,0,2);


  G4VisAttributes *colorGeContainer = new G4VisAttributes(G4Colour(0.5,0.5,0.5)); // gray
  G4VisAttributes *colorGeAl = new G4VisAttributes(G4Colour(0.9,0.9,0.9)); // light gray
  G4VisAttributes *colorGeDead      = new G4VisAttributes(G4Colour(0,1.,0.0)); // green
  G4VisAttributes *colorGeVac      = new G4VisAttributes(G4Colour(0,1.,1.0)); // cyan
  G4VisAttributes *colorGeCrystal   = new G4VisAttributes(G4Colour(1.,0.0,0.0)); // red
  G4VisAttributes *colorGeMylar   = new G4VisAttributes(G4Colour(1.,0.6,0.2)); // brown
 
  outerCaseLog->SetVisAttributes(colorGeContainer);
  gevacLog->SetVisAttributes(colorGeVac);
  geIncaseMylarLog->SetVisAttributes(colorGeMylar);
  geIncaseAlLog->SetVisAttributes(colorGeAl);
  gedeadLog   ->SetVisAttributes(colorGeDead);  
  geLog       ->SetVisAttributes(colorGeCrystal);
  //colorGeVac->SetVisibility(false);

  return outerCaseLog;

}

G4double GeBO::GetLength(){
  return OuterCasingLength;
}

