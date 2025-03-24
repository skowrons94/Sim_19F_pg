#include "BeamPipe20nep.hh"

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

BeamPipe20nep::BeamPipe20nep(){;}


BeamPipe20nep::~BeamPipe20nep(){;}

G4LogicalVolume *BeamPipe20nep::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color1 = new G4VisAttributes(G4Colour(1.,1.,1.0));
  G4VisAttributes *color2 = new G4VisAttributes(G4Colour(1.,0.,0.0));
  G4VisAttributes *colorgas1 = new G4VisAttributes(G4Colour(0.75,1.,1.0));
  G4VisAttributes *colorgas2 = new G4VisAttributes(G4Colour(0.6,1.,1.0));
  G4VisAttributes *colorgas3 = new G4VisAttributes(G4Colour(0.45,1.,1.0));
  G4VisAttributes *colorgas4 = new G4VisAttributes(G4Colour(0.3,1.,1.0));
  G4VisAttributes *colorgas5 = new G4VisAttributes(G4Colour(0.15,1.,1.0));

  pipeL = 390*mm;
  G4double pipeInnerDiam = 56*mm;
  G4double pipeOuterDiam = 60*mm;

  G4double gas1L = 67.5*mm;
  G4double gas2L = 85*mm;
  G4double gas3L = 85*mm;
  G4double gas4L = 85*mm;
  G4double gas5L = 67.5*mm;

  G4VSolid* pipeSol = new G4Tubs("pipeTube",0,pipeOuterDiam/2,pipeL/2,0.0,360.0*deg);

  // gas is divided in 6 slices inside the chamber (1-6) + at the entrance of the chamber (0)
  G4VSolid* gas1Sol = new G4Tubs("gas1Tube",0,pipeInnerDiam/2,gas1L/2,0.0,360.0*deg);
  G4VSolid* gas2Sol = new G4Tubs("gas2Tube",0,pipeInnerDiam/2,gas2L/2,0.0,360.0*deg);
  G4VSolid* gas3Sol = new G4Tubs("gas3Tube",0,pipeInnerDiam/2,gas3L/2,0.0,360.0*deg);
  G4VSolid* gas4Sol = new G4Tubs("gas4Tube",0,pipeInnerDiam/2,gas4L/2,0.0,360.0*deg);
  G4VSolid* gas5Sol = new G4Tubs("gas5Tube",0,pipeInnerDiam/2,gas5L/2,0.0,360.0*deg);

  gasLog[0] = new G4LogicalVolume(gas1Sol,materials->GetMaterial("gas_pipe0"),"gas0Log",0,0,0);
  gasLog[1] = new G4LogicalVolume(gas2Sol,materials->GetMaterial("gas_pipe1"),"gas1Log",0,0,0);
  gasLog[2] = new G4LogicalVolume(gas3Sol,materials->GetMaterial("gas_pipe2"),"gas2Log",0,0,0);
  gasLog[3] = new G4LogicalVolume(gas4Sol,materials->GetMaterial("gas_pipe3"),"gas3Log",0,0,0);
  gasLog[4] = new G4LogicalVolume(gas5Sol,materials->GetMaterial("gas_pipe4"),"gas4Log",0,0,0);

  G4AssemblyVolume *gas = new G4AssemblyVolume();
  G4ThreeVector tr(0,0,0);
  gas->AddPlacedVolume(gasLog[0],tr,0);
  tr.setZ(gas1L/2+gas2L/2);
  gas->AddPlacedVolume(gasLog[1],tr,0);
  tr.setZ(gas1L/2+gas2L+gas3L/2);
  gas->AddPlacedVolume(gasLog[2],tr,0);
  tr.setZ(gas1L/2+gas2L+gas3L+gas4L/2);
  gas->AddPlacedVolume(gasLog[3],tr,0);
  tr.setZ(gas1L/2+gas2L+gas3L+gas4L+gas5L/2);
  gas->AddPlacedVolume(gasLog[4],tr,0);

  G4LogicalVolume* pipeLog = new G4LogicalVolume(pipeSol,materials->GetMaterial("G4_STAINLESS-STEEL"),"pipeLog",0,0,0);

  auto rotGas = new G4RotationMatrix();
  rotGas->rotateX(0*deg);
  G4ThreeVector trGas(0,0,-pipeL/2+gas1L/2);
  gas->MakeImprint(pipeLog,trGas,rotGas);
  
  pipeLog->SetVisAttributes(color1);
  gasLog[0]->SetVisAttributes(colorgas1);
  gasLog[1]->SetVisAttributes(colorgas2);
  gasLog[2]->SetVisAttributes(colorgas3);
  gasLog[3]->SetVisAttributes(colorgas4);
  gasLog[4]->SetVisAttributes(colorgas5);

  return pipeLog;
}

G4double BeamPipe20nep::GetLength()
{
  return pipeL;
}

G4LogicalVolume* BeamPipe20nep::GetTargetLog(G4int fGasSlice)
{
  GasSlice = fGasSlice;
  return gasLog[GasSlice];
}
