#include "Collimator20nep.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AssemblyVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

Collimator20nep::Collimator20nep(){;}


Collimator20nep::~Collimator20nep(){;}

G4AssemblyVolume *Collimator20nep::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color1 = new G4VisAttributes(G4Colour(1.,0.,1.0));
  G4VisAttributes *color2 = new G4VisAttributes(G4Colour(1.,0.,0.0));
  G4VisAttributes *color3 = new G4VisAttributes(G4Colour(0.,1.,0.0));
  G4VisAttributes *color4 = new G4VisAttributes(G4Colour(0.,0.,1.0));

  G4VisAttributes *colorgas0 = new G4VisAttributes(G4Colour(0.6,1.,1.0));
  G4VisAttributes *colorgas1 = new G4VisAttributes(G4Colour(0.45,1.,1.0));
  G4VisAttributes *colorgas2 = new G4VisAttributes(G4Colour(0.3,1.,1.0));
  G4VisAttributes *colorgas3 = new G4VisAttributes(G4Colour(0.15,1.,1.0));
  G4VisAttributes *colorgas4 = new G4VisAttributes(G4Colour(0.0,1.,1.0));

  G4double ringOuterDiam = 30*mm;
  G4double ringInnerDiam = 26*mm;
  ringL = 10.5*mm;

  G4double slabX = 85*mm;
  G4double slabY = 85*mm;
  slabL = 20*mm;

  G4double slabHoleDiam = 17.2*mm;
  G4double slabHoleL = 20.1*mm;

  G4double sheetX = 90*mm;
  G4double sheetY = 90*mm;
  sheetL = 1.9*mm;

  G4double sheetHoleDiam = 30.1*mm;
  G4double sheetHoleL = 2.0*mm;

  G4double screwCutOuterDiam = 32.1*mm;
  G4double screwCutInnerDiam = 17.2*mm;
  screwCutL = ringL+slabL;

  G4double screwOuterDiam = 32*mm;
  G4double screwInnerDiam = 7*mm;
  screwL = screwCutL+10.6*mm;

  G4double gasL = screwL+sheetL;

  // gas is divided in 5 slices inside the collimator length of 43 mm (1-5)
  G4VSolid* gas1Sol = new G4Tubs("gas1Tube",0,screwInnerDiam/2,gasL/5/2,0.0,360.0*deg);
  G4VSolid* gas2Sol = new G4Tubs("gas2Tube",0,screwInnerDiam/2,gasL/5/2,0.0,360.0*deg);
  G4VSolid* gas3Sol = new G4Tubs("gas3Tube",0,screwInnerDiam/2,gasL/5/2,0.0,360.0*deg);
  G4VSolid* gas4Sol = new G4Tubs("gas4Tube",0,screwInnerDiam/2,gasL/5/2,0.0,360.0*deg);
  G4VSolid* gas5Sol = new G4Tubs("gas5Tube",0,screwInnerDiam/2,gasL/5/2,0.0,360.0*deg);

  //G4VSolid* screw1Sol = new G4Tubs("screw1Tube",screwInnerDiam/2,screwOuterDiam/2,screwL/2,0.0,360.0*deg);
  G4VSolid* screw1Sol = new G4Tubs("screw1Tube",0,screwOuterDiam/2,screwL/2,0.0,360.0*deg);
  G4VSolid* screwCutSol = new G4Tubs("screwCutTube",screwCutInnerDiam/2,screwCutOuterDiam/2,screwCutL/2,0.0,360.0*deg);
  G4SubtractionSolid* screwSol = new G4SubtractionSolid("screw", screw1Sol, screwCutSol, 0, G4ThreeVector(0,0,-screwL/2+screwCutL/2));
  
  G4VSolid* ringSol = new G4Tubs("ringTube",ringInnerDiam/2,ringOuterDiam/2,ringL/2,0.0,360.0*deg);

  G4VSolid* slab1Sol = new G4Box("slab1Box",slabX/2,slabY/2,slabL/2);
  G4VSolid* slabHoleSol = new G4Tubs("slabHoleTube",0,slabHoleDiam/2,slabHoleL/2,0.0,360.0*deg);
  G4SubtractionSolid* slabSol = new G4SubtractionSolid("slab", slab1Sol, slabHoleSol, 0, G4ThreeVector(0,0,0));
  
  G4VSolid* sheet1Sol = new G4Box("sheet1Box",sheetX/2,sheetY/2,sheetL/2);
  G4VSolid* sheetHoleSol = new G4Tubs("sheetHoleTube",0,sheetHoleDiam/2,sheetHoleL/2,0.0,360.0*deg);
  G4SubtractionSolid* sheetSol = new G4SubtractionSolid("sheet", sheet1Sol, sheetHoleSol, 0, G4ThreeVector(0,0,0));
  
  G4LogicalVolume* screwLog = new G4LogicalVolume(screwSol,materials->GetMaterial("G4_Cu"),"screwLog",0,0,0);
  G4LogicalVolume* ringLog = new G4LogicalVolume(ringSol,materials->GetMaterial("G4_BRASS"),"ringLog",0,0,0);
  G4LogicalVolume* slabLog = new G4LogicalVolume(slabSol,materials->GetMaterial("G4_BRASS"),"slabLog",0,0,0);
  G4LogicalVolume* sheetLog = new G4LogicalVolume(sheetSol,materials->GetMaterial("G4_POLYETHYLENE"),"sheetLog",0,0,0);

  G4AssemblyVolume* collimator = new G4AssemblyVolume();
  G4ThreeVector tr(0,0,0);
  collimator->AddPlacedVolume(slabLog,tr,0);
  tr.setZ(-slabL/2+screwL/2);
  collimator->AddPlacedVolume(screwLog,tr,0);
  tr.setZ(slabL/2+ringL/2);
  collimator->AddPlacedVolume(ringLog,tr,0);
  tr.setZ(slabL/2+sheetL/2);
  collimator->AddPlacedVolume(sheetLog,tr,0);
  tr.setZ(-slabL/2-sheetL/2);
  collimator->AddPlacedVolume(sheetLog,tr,0);

  gasLog[0] = new G4LogicalVolume(gas1Sol,materials->GetMaterial("gas_col0"),"gas1Log",0,0,0);
  gasLog[1] = new G4LogicalVolume(gas2Sol,materials->GetMaterial("gas_col1"),"gas2Log",0,0,0);
  gasLog[2] = new G4LogicalVolume(gas3Sol,materials->GetMaterial("gas_col2"),"gas3Log",0,0,0);
  gasLog[3] = new G4LogicalVolume(gas4Sol,materials->GetMaterial("gas_col3"),"gas4Log",0,0,0);
  gasLog[4] = new G4LogicalVolume(gas5Sol,materials->GetMaterial("gas_col4"),"gas5Log",0,0,0);

  G4AssemblyVolume *gas = new G4AssemblyVolume();
  G4ThreeVector trGas(0,0,0);
  gas->AddPlacedVolume(gasLog[0],trGas,0);
  trGas.setZ(gasL/5/2+gasL/5/2);
  gas->AddPlacedVolume(gasLog[1],trGas,0);
  trGas.setZ(gasL/5/2+gasL/5+gasL/5/2);
  gas->AddPlacedVolume(gasLog[2],trGas,0);
  trGas.setZ(gasL/5/2+gasL/5+gasL/5+gasL/5/2);
  gas->AddPlacedVolume(gasLog[3],trGas,0);
  trGas.setZ(gasL/5/2+gasL/5+gasL/5+gasL/5+gasL/5/2);
  gas->AddPlacedVolume(gasLog[4],trGas,0);

  auto rotGas = new G4RotationMatrix();
  rotGas->rotateX(0*deg);
  G4ThreeVector trGasComp(0,0,-screwL/2-sheetL+gasL/5/2);
  //G4ThreeVector trGasComp(0,0,0);
  gas->MakeImprint(screwLog,trGasComp,rotGas);

  slabLog->SetVisAttributes(color1);
  sheetLog->SetVisAttributes(color2);
  screwLog->SetVisAttributes(color3);
  ringLog->SetVisAttributes(color4);
  
  gasLog[0]->SetVisAttributes(colorgas0);
  gasLog[1]->SetVisAttributes(colorgas1);
  gasLog[2]->SetVisAttributes(colorgas2);
  gasLog[3]->SetVisAttributes(colorgas3);
  gasLog[4]->SetVisAttributes(colorgas4);

  return collimator;
}

G4double Collimator20nep::GetLength()
{
  return screwL-screwCutL+slabL/2+ringL;
}

G4double Collimator20nep::GetLength2()
{
  return slabL/2+sheetL;
}

G4LogicalVolume* Collimator20nep::GetTargetLog(G4int fGasSlice)
{
  GasSlice = fGasSlice;
  return gasLog[GasSlice];
}
