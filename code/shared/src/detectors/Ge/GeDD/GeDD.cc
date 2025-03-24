#include "GeDD.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "GeDDMessenger.hh"

GeDD::GeDD(){
  geDDMessenger = new GeDDMessenger(this);
}


GeDD::~GeDD(){
  delete geDDMessenger;
}

GeDD* GeDD::instance = 0;

GeDD* GeDD::GetInstance()
{
  if (instance == 0)
    {
      instance = new GeDD;

    }
  return instance;
}

G4LogicalVolume *GeDD::Construct()
{
  materials = Materials::GetInstance();

  G4double gecaseDiam = 95*mm;
  G4double gecaseL = 200*mm;
  
  G4double gevacDiam = 91.8*mm;
  G4double gevacL = 199.1*mm;
  
  G4double geIncaseInDiam = 0*mm;
  G4double geIncaseOutDiam = 89*mm; // this is not known from drawings, info from Eliana
  G4double geIncaseL = 130*mm;

  G4double geInvacInDiam = 0*mm;
  G4double geInvacOutDiam = 83.4*mm; // geIncaseOutDiam - 1.6
  G4double geInvacL = 130*mm;

  G4double gedeadDiam = 79.9*mm;
  //G4double gedeadDiam = 83.4*mm;
  G4double gedeadL = 77.6*mm;
  
  G4double geDiam = ((gedeadDiam/mm)-2*(DeadSide/mm))*mm;
  G4double geL = ((gedeadL/mm)-(DeadFront/mm)-(DeadBack/mm))*mm;
  
  G4double geholeDiam = 8.9*mm;
  G4double geholeL = 64*mm;

  // Ge case
  G4VSolid* gecaseSol = new G4Tubs("gecaseTube",0.0*mm,gecaseDiam/2,gecaseL/2,0.0,360.0*deg);
  G4LogicalVolume* gecaseLog = new G4LogicalVolume(gecaseSol,materials->GetMaterial("G4_C"),"gecaseLog");

  // Ge vacuum
  G4VSolid* gevacSol = new G4Tubs("gevacTube",0.0*mm,gevacDiam/2,gevacL/2,0.0,360.0*deg);
  G4LogicalVolume* gevacLog = new G4LogicalVolume(gevacSol,materials->GetMaterial("G4_Galactic"),"gevacLog");

  // Ge Incase
  G4VSolid* geIncaseSol = new G4Tubs("geIncaseTube",geIncaseInDiam/2,geIncaseOutDiam/2,geIncaseL/2,0.0,360.0*deg);
  G4LogicalVolume* geIncaseLog = new G4LogicalVolume(geIncaseSol,materials->GetMaterial("G4_Cu"),"geIncaseLog");

  // Ge Invacuum
  G4VSolid* geInvacSol = new G4Tubs("geInvacTube",geInvacInDiam/2,geInvacOutDiam/2,geInvacL/2,0.0,360.0*deg);
  G4LogicalVolume* geInvacLog = new G4LogicalVolume(geInvacSol,materials->GetMaterial("G4_Galactic"),"geInvacLog");

  // GeDead 
  G4VSolid* gedeadSol = new G4Tubs("gedeadTube",0.0*mm,gedeadDiam/2,gedeadL/2,0.0,360.0*deg);
  G4LogicalVolume* gedeadLog = new G4LogicalVolume(gedeadSol,materials->GetMaterial("G4_Ge"),"gedeadLog");

  // Ge
  G4VSolid* geSol = new G4Tubs("geTube",0.0*mm,geDiam/2,geL/2,0.0,360.0*deg);
  G4LogicalVolume* geLog = new G4LogicalVolume(geSol,materials->GetMaterial("G4_Ge"),"geLog");

  // Ge hole
  G4VSolid* geholeSol = new G4Tubs("geholeTube",0.0*mm,geholeDiam/2,geholeL/2,0.0,360.0*deg);
  G4LogicalVolume* geholeLog = new G4LogicalVolume(geholeSol,materials->GetMaterial("G4_Galactic"),"geholeLog");

  auto *gevacPhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,-0.45*mm),gevacLog,"gevacPhys",gecaseLog,0,1);
  auto *geIncasePhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,gevacL/2-geIncaseL/2-Disp),geIncaseLog,"geIncasePhys",gevacLog,0,1);
  auto *geInvacPhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,0.0*mm),geInvacLog,"geInvacPhys",geIncaseLog,0,1);
  auto *gedeadPhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,geInvacL/2-gedeadL/2),gedeadLog,"gedeadPhys",geInvacLog,0,1);
  auto *gePhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,gedeadL/2-geL/2-DeadFront),geLog,"gePhys",gedeadLog,0,1);
  auto *geholePhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,-(geL-geholeL)/2),geholeLog,"geholePhys",geLog,0,1);

  G4VisAttributes *colorGeCrystal = new G4VisAttributes(G4Colour(1.,0.0,0.0));
  G4VisAttributes *colorGeDead = new G4VisAttributes(G4Colour(0,1.,0.0));
  G4VisAttributes *colorGeContainer = new G4VisAttributes(G4Colour(0.5,0.5,0.0));

  geLog->SetVisAttributes(colorGeCrystal);
  gedeadLog->SetVisAttributes(colorGeDead);
  gecaseLog->SetVisAttributes(colorGeContainer);

  return gecaseLog;

}
