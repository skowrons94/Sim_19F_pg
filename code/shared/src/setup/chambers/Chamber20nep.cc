#include "Chamber20nep.hh"

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

Chamber20nep::Chamber20nep(){;}


Chamber20nep::~Chamber20nep(){;}

G4LogicalVolume *Chamber20nep::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color1 = new G4VisAttributes(G4Colour(1.,1.,1.0));
  G4VisAttributes *color2 = new G4VisAttributes(G4Colour(1.,0.,0.0));
  G4VisAttributes *colorgas0 = new G4VisAttributes(G4Colour(0.9,1.,1.0));
  G4VisAttributes *colorgas1 = new G4VisAttributes(G4Colour(0.75,1.,1.0));
  G4VisAttributes *colorgas2 = new G4VisAttributes(G4Colour(0.6,1.,1.0));
  G4VisAttributes *colorgas3 = new G4VisAttributes(G4Colour(0.45,1.,1.0));
  G4VisAttributes *colorgas4 = new G4VisAttributes(G4Colour(0.3,1.,1.0));
  G4VisAttributes *colorgas5 = new G4VisAttributes(G4Colour(0.15,1.,1.0));
  G4VisAttributes *colorgas6 = new G4VisAttributes(G4Colour(0.0,1.,1.0));

  G4double outerX = 128*mm;
  outerY = 112*mm;
  outerL = 568*mm;

  G4double cutOutX = 114*mm;
  G4double cutOutY = 2.1*mm;
  G4double cutOutL = 160*mm;

  G4double innerX = 120*mm;
  G4double innerY = 104*mm;
  innerLorig = 557*mm;

  innerL = 384*mm; // temporary fix for 21Ne setup until calorimeter is coded

  G4double holeDiam = 56*mm;
  G4double holeL = 11.0*mm;

  G4double gas1L = 32*mm;
  G4double gas2L = 60*mm;
  G4double gas3L = 70*mm;
  G4double gas4L = 70*mm;
  G4double gas5L = 60*mm;
  // 43 mm because of the collimator
  G4double gas6L = innerL-43*mm-gas1L-gas2L-gas3L-gas4L-gas5L;

  G4VSolid* outerSol = new G4Box("outerBox",outerX/2,outerY/2,outerL/2);
  G4VSolid* cutOutSol = new G4Box("cutOutBox",cutOutX/2,cutOutY/2,cutOutL/2);
  G4VSolid* holeSol = new G4Tubs("holeTube",0,holeDiam/2,holeL/2,0.0,360.0*deg);
  G4VSolid* vacuumSol = new G4Box("vacuumBox",innerX/2,innerY/2,innerL/2);

  // gas is divided in 6 slices inside the chamber (1-6) + at the entrance of the chamber (0)
  G4VSolid* gas0Sol = new G4Tubs("gas0Tube",0,holeDiam/2,holeL/2,0.0,360.0*deg);
  G4VSolid* gas1Sol = new G4Box("gas1Box",innerX/2,innerY/2,gas1L/2);
  G4VSolid* gas2Sol = new G4Box("gas2Box",innerX/2,innerY/2,gas2L/2);
  G4VSolid* gas3Sol = new G4Box("gas3Box",innerX/2,innerY/2,gas3L/2);
  G4VSolid* gas4Sol = new G4Box("gas4Box",innerX/2,innerY/2,gas4L/2);
  G4VSolid* gas5Sol = new G4Box("gas5Box",innerX/2,innerY/2,gas5L/2);
  G4VSolid* gas6Sol = new G4Box("gas6Box",innerX/2,innerY/2,gas6L/2);

  gasLog[0] = new G4LogicalVolume(gas0Sol,materials->GetMaterial("gas_ch0"),"gas0Log",0,0,0);
  gasLog[1] = new G4LogicalVolume(gas1Sol,materials->GetMaterial("gas_ch1"),"gas1Log",0,0,0);
  gasLog[2] = new G4LogicalVolume(gas2Sol,materials->GetMaterial("gas_ch2"),"gas2Log",0,0,0);
  gasLog[3] = new G4LogicalVolume(gas3Sol,materials->GetMaterial("gas_ch3"),"gas3Log",0,0,0);
  gasLog[4] = new G4LogicalVolume(gas4Sol,materials->GetMaterial("gas_ch4"),"gas4Log",0,0,0);
  gasLog[5] = new G4LogicalVolume(gas5Sol,materials->GetMaterial("gas_ch5"),"gas5Log",0,0,0);
  gasLog[6] = new G4LogicalVolume(gas6Sol,materials->GetMaterial("gas_ch6"),"gas6Log",0,0,0);

  G4AssemblyVolume *gas = new G4AssemblyVolume();
  G4ThreeVector tr(0,0,0);
  gas->AddPlacedVolume(gasLog[1],tr,0);
  tr.setZ(gas1L/2+gas2L/2);
  gas->AddPlacedVolume(gasLog[2],tr,0);
  tr.setZ(gas1L/2+gas2L+gas3L/2);
  gas->AddPlacedVolume(gasLog[3],tr,0);
  tr.setZ(gas1L/2+gas2L+gas3L+gas4L/2);
  gas->AddPlacedVolume(gasLog[4],tr,0);
  tr.setZ(gas1L/2+gas2L+gas3L+gas4L+gas5L/2);
  gas->AddPlacedVolume(gasLog[5],tr,0);
  tr.setZ(gas1L/2+gas2L+gas3L+gas4L+gas5L+gas6L/2);
  gas->AddPlacedVolume(gasLog[6],tr,0);

  G4SubtractionSolid* chamber1Sol = new G4SubtractionSolid("chamber1", outerSol, cutOutSol, 0, G4ThreeVector(0,outerY/2-cutOutY/2,-outerL/2+120*mm));
  G4SubtractionSolid* chamberSol = new G4SubtractionSolid("chamber", chamber1Sol, cutOutSol, 0, G4ThreeVector(0,-outerY/2+cutOutY/2,-outerL/2+195*mm));
  //G4SubtractionSolid* chamber2Sol = new G4SubtractionSolid("chamber2", chamber1Sol, cutOutSol, 0, G4ThreeVector(0,-outerY/2+cutOutY/2,-outerL/2+195*mm));
  //G4SubtractionSolid* chamberSol = new G4SubtractionSolid("chamber", chamber2Sol, holeSol, 0, G4ThreeVector(0,0,-outerL/2+holeL/2));
  
  G4LogicalVolume* chamberLog = new G4LogicalVolume(chamberSol,materials->GetMaterial("G4_STAINLESS-STEEL"),"chamberLog",0,0,0);
  vacuumLog = new G4LogicalVolume(vacuumSol,materials->GetMaterial("G4_Galactic"),"vacuumLog",0,0,0);

  auto *vacuumPhys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,-outerL/2+holeL+innerL/2),vacuumLog,"vacuumPhys",chamberLog,0,0);

  auto *gas0Phys = new G4PVPlacement(0,G4ThreeVector(0*mm,0.0*mm,-outerL/2+holeL/2),gasLog[0],"gas0Phys",chamberLog,0,0);

  auto rotGas = new G4RotationMatrix();
  rotGas->rotateX(0*deg);
  G4ThreeVector trGas(0,0,-innerL/2+43*mm+gas1L/2);
  gas->MakeImprint(vacuumLog,trGas,rotGas);
  
  chamberLog->SetVisAttributes(color1);
  vacuumLog->SetVisAttributes(color2);
  gasLog[0]->SetVisAttributes(colorgas0);
  gasLog[1]->SetVisAttributes(colorgas1);
  gasLog[2]->SetVisAttributes(colorgas2);
  gasLog[3]->SetVisAttributes(colorgas3);
  gasLog[4]->SetVisAttributes(colorgas4);
  gasLog[5]->SetVisAttributes(colorgas5);
  gasLog[6]->SetVisAttributes(colorgas6);

  return chamberLog;
}

G4double Chamber20nep::GetLength()
{
  //return innerL-outerL/2;
  return innerLorig-outerL/2; // temporary fix for 21Ne setup until calorimeter is coded
}

G4double Chamber20nep::GetLength2()
{
  return outerL;
}

G4double Chamber20nep::GetInnerLength()
{
  return innerL;
}

G4double Chamber20nep::GetHeight()
{
  return outerY;
}

G4LogicalVolume* Chamber20nep::GetTargetLog(G4int fGasSlice)
{
  GasSlice = fGasSlice;
  return gasLog[GasSlice];
}

G4LogicalVolume* Chamber20nep::GetInnerVolumeLog()
{
  return vacuumLog;
}
