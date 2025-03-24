#include "ScP.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

ScP::ScP(){;}


ScP::~ScP(){;}

ScP* ScP::instance = 0;

ScP* ScP::GetInstance()
{
  if (instance == 0)
    {
      instance = new ScP;

    }
  return instance;
}

G4LogicalVolume *ScP::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *colorAlCylinder = new G4VisAttributes(G4Colour(0.5,0.5,0.0));
  G4VisAttributes *colorReflectorCylinder = new G4VisAttributes(G4Colour(1.,0.,0.0));
  G4VisAttributes *colorVacuumCylinder = new G4VisAttributes(G4Colour(0.,0.,1.0));
  G4VisAttributes *colorCeBrCylinder = new G4VisAttributes(G4Colour(0.0,1.,0.0));

  G4double CrystalL = 50.8*mm;
  G4double CrystalDiam = 50.8*mm;

  //Al Cylinder
  G4double ThicknessAddition = 0.0*mm;
  G4Tubs* AlCylinder1Sol = new G4Tubs("AlCylinder1Solid", 0, (ThicknessAddition+57*mm)/2, 42.5*mm/2, 0.0, 360.0*deg);
  G4Tubs* AlCylinder2Sol = new G4Tubs("AlCylinder2Solid", 0, (ThicknessAddition+58.8*mm)/2, 108.5*mm/2, 0.0, 360.0*deg);
  G4UnionSolid* AlCylinderSol   = new G4UnionSolid("AlCylinderSol", AlCylinder1Sol, AlCylinder2Sol, 0, G4ThreeVector(0,0,42.5*mm/2+108.5*mm/2));

  //Epoxy Cylinder
  G4Tubs* EpoxyCylinderSol = new G4Tubs("EpoxyCylinderSolid", 0, 58*mm/2, 108.5*mm/2, 0.0, 360.0*deg);

  //Reflector Cylinder
  G4Tubs* ReflectorCylinderSol = new G4Tubs("ReflectorCylinderSolid", 0, 56.2*mm/2, 150.6*mm/2, 0.0, 360.0*deg);

  //Vacuum Cylinder
  G4Tubs* VacuumCylinderSol = new G4Tubs("VacuumCylinderSolid", 0, CrystalDiam/2, 149.6*mm/2, 0.0, 360.0*deg);

  //CeBr Cylinder
  G4Tubs* CeBrCylinderSol = new G4Tubs("CeBrCylinderSolid", 0, CrystalDiam/2, CrystalL/2, 0.0, 360.0*deg);


  //Al Cylinder
  G4LogicalVolume *AlCylinderLog = new G4LogicalVolume(AlCylinderSol, materials->GetMaterial("G4_Al"), "AlCylinderLogical");

  //Epoxy Cylinder
  G4LogicalVolume *EpoxyCylinderLog = new G4LogicalVolume(EpoxyCylinderSol, materials->GetMaterial("Epoxy"), "AlCylinderLogical");

  //Reflector Cylinder
  //G4LogicalVolume *ReflectorCylinderLog = new G4LogicalVolume(ReflectorCylinderSol, materials->GetMaterial("Al2O3"), "ReflectorCylinderLogical");
  //G4LogicalVolume *ReflectorCylinderLog = new G4LogicalVolume(ReflectorCylinderSol, materials->GetMaterial("G4_TEFLON"), "ReflectorCylinderLogical");
  G4LogicalVolume *ReflectorCylinderLog = new G4LogicalVolume(ReflectorCylinderSol, materials->GetMaterial("Tyvek"), "ReflectorCylinderLogical");

  //Vacuum Cylinder
  G4LogicalVolume *VacuumCylinderLog = new G4LogicalVolume(VacuumCylinderSol, materials->GetMaterial("G4_Galactic"), "VacuumCylinderLogical");

  //CeBr Cylinder 
  G4LogicalVolume *CeBrCylinderLog = new G4LogicalVolume(CeBrCylinderSol, materials->GetMaterial("CeBr3"), "CeBrCylinderLogical");

  auto *EpoxyCylinderPhys = new G4PVPlacement(0,G4ThreeVector(0*cm,0*cm,42.5*mm/2+108.5*mm/2),EpoxyCylinderLog,"EpoxyCylinderPhys",AlCylinderLog,0,0);
  auto *ReflectorCylinderPhys = new G4PVPlacement(0,G4ThreeVector(0*cm,0*cm,-42.5*mm/2+150.6*mm/2+0.4*mm),ReflectorCylinderLog,"ReflectorCylinderPhys",AlCylinderLog,0,0);
  auto *VacuumCylinderPhys = new G4PVPlacement(0,G4ThreeVector(0*cm,0*cm,0.5*mm),VacuumCylinderLog,"VacuumCylinderPhys",ReflectorCylinderLog,0,0);
  auto *CeBrCylinderPhys = new G4PVPlacement(0,G4ThreeVector(0*cm,0*cm,-149.6*mm/2+CrystalL/2),CeBrCylinderLog,"CeBrCylinderPhys",VacuumCylinderLog,0,0);
 
  AlCylinderLog->SetVisAttributes(colorAlCylinder);
  ReflectorCylinderLog->SetVisAttributes(colorReflectorCylinder);
  VacuumCylinderLog->SetVisAttributes(colorVacuumCylinder);
  CeBrCylinderLog->SetVisAttributes(colorCeBrCylinder);

   
  // MotherCylinderLog should be the mother of all embedded volumes
  // use union and subtraction of volumes whenever possible
  return AlCylinderLog;
  
}
