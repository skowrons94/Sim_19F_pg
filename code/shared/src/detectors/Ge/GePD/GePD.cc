#include "GePD.hh"
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

#include "GePDMessenger.hh"

GePD::GePD(){
  gePDMessenger = new GePDMessenger(this);
}


GePD::~GePD(){
  delete gePDMessenger;
}

GePD* GePD::instance = 0;

GePD* GePD::GetInstance()
{
  if (instance == 0)
    {
      instance = new GePD;

    }
  return instance;
}

G4LogicalVolume *GePD::Construct()
{
  materials = Materials::GetInstance();

  G4double gecaseDiam = 108*mm;
  G4double gecaseL = 239.5*mm;
  
  G4double gevacDiam = 105*mm;
  G4double gevacL = 238.5*mm;
  
  G4double geIncase1InDiam = 0*mm;
  G4double geIncase1OutDiam = 99.5*mm;
  G4double geIncase1L = 200*mm;

  G4double geIncase2InDiam = 95.1*mm;
  G4double geIncase2OutDiam = 100*mm;
  G4double geIncase2L = 16.7*mm;

  G4double geIncase3InDiam = 95.1*mm;
  G4double geIncase3OutDiam = 100*mm;
  G4double geIncase3L = 30*mm;

  G4double geIncase4InDiam = 95.1*mm;
  G4double geIncase4OutDiam = 100*mm;
  G4double geIncase4L = 139*mm;

  G4double geInvacInDiam = 0*mm;
  G4double geInvacOutDiam = 91*mm;
  G4double geInvacL = 200*mm;

  G4double gedeadDiam = 91*mm;
  G4double gedeadL = 90.7*mm;
  
  G4double geDiam = ((gedeadDiam/mm)-2*(DeadSide/mm))*mm;
  G4double geL = ((gedeadL/mm)-(DeadFront/mm)-(DeadBack/mm))*mm;
  
  G4double geholeDiam = 14*mm;
  G4double geholeL = 77*mm;

  G4double gehole1InDiam = 21*mm;
  G4double gehole1OutDiam = 32*mm;
  G4double gehole1L = 2*mm;

  // Ge case
  G4VSolid* gecaseSol = new G4Tubs("gecaseTube",0.0*mm,gecaseDiam/2,gecaseL/2,0.0,360.0*deg);
  G4LogicalVolume* gecaseLog = new G4LogicalVolume(gecaseSol,materials->GetMaterial("G4_Cu"),"gecaseLog");

  // Ge vacuum
  G4VSolid* gevacSol = new G4Tubs("gevacTube",0.0*mm,gevacDiam/2,gevacL/2,0.0,360.0*deg);
  G4LogicalVolume* gevacLog = new G4LogicalVolume(gevacSol,materials->GetMaterial("G4_Galactic"),"gevacLog");

  // Ge Incase
  G4VSolid* geIncase1Sol = new G4Tubs("geIncase1Tube",geIncase1InDiam/2,geIncase1OutDiam/2,geIncase1L/2,0.0,360.0*deg);
  G4VSolid* geIncase2Sol = new G4Tubs("geIncase2Tube",geIncase2InDiam/2,geIncase2OutDiam/2,geIncase2L/2,0.0,360.0*deg);
  G4VSolid* geIncase3Sol = new G4Tubs("geIncase3Tube",geIncase3InDiam/2,geIncase3OutDiam/2,geIncase3L/2,0.0,360.0*deg);
  G4VSolid* geIncase4Sol = new G4Tubs("geIncase4Tube",geIncase4InDiam/2,geIncase4OutDiam/2,geIncase4L/2,0.0,360.0*deg);

  G4SubtractionSolid* geIncasesub1Sol = new G4SubtractionSolid("geIncasesub1", geIncase1Sol, geIncase2Sol, 0, G4ThreeVector(0,0,geIncase1L/2-geIncase2L/2-1.3*mm));
  G4SubtractionSolid* geIncasesub2Sol = new G4SubtractionSolid("geIncasesub2", geIncasesub1Sol, geIncase3Sol, 0, G4ThreeVector(0,0,geIncase1L/2-geIncase3L/2-25*mm));
  G4SubtractionSolid* geIncaseSol = new G4SubtractionSolid("geIncase", geIncasesub2Sol, geIncase4Sol, 0, G4ThreeVector(0,0,geIncase1L/2-geIncase4L/2-62*mm));

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

  // Ge hole 1
  G4VSolid* gehole1Sol = new G4Tubs("gehole1Tube",gehole1InDiam/2,gehole1OutDiam/2,gehole1L/2,0.0,360.0*deg);
  G4LogicalVolume* gehole1Log = new G4LogicalVolume(gehole1Sol,materials->GetMaterial("G4_Galactic"),"gehole1Log");

  auto *gevacPhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,-0.5*mm),gevacLog,"gevacPhys",gecaseLog,0,0);
  auto *geIncasePhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,gevacL/2-geIncase1L/2-Disp),geIncaseLog,"geIncasePhys",gevacLog,0,0);
  auto *geInvacPhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,0.0*mm),geInvacLog,"geInvacPhys",geIncaseLog,0,0);
  auto *gedeadPhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,geInvacL/2-gedeadL/2),gedeadLog,"gedeadPhys",geInvacLog,0,0);
  auto *gePhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,gedeadL/2-geL/2-DeadFront),geLog,"gePhys",gedeadLog,0,0);
  auto *geholePhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,-(geL-geholeL)/2),geholeLog,"geholePhys",geLog,0,0);
  auto *gehole1Phys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,-(geL-gehole1L)/2),gehole1Log,"gehole1Phys",geLog,0,0);

  G4VisAttributes *colorGeCrystal = new G4VisAttributes(G4Colour(1.,0.0,0.0));
  G4VisAttributes *colorGeDead = new G4VisAttributes(G4Colour(0,1.,0.0));
  G4VisAttributes *colorGeContainer = new G4VisAttributes(G4Colour(0.5,0.5,0.0));

  geLog->SetVisAttributes(colorGeCrystal);
  gedeadLog->SetVisAttributes(colorGeDead);
  gecaseLog->SetVisAttributes(colorGeContainer);

  return gecaseLog;

}
