#include "Si.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

Si::Si(){;}


Si::~Si(){;}

G4LogicalVolume *Si::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *colorSiCrystal = new G4VisAttributes(G4Colour(1.,1.,0.0));
  G4VisAttributes *colorSiContainer = new G4VisAttributes(G4Colour(0.5,0.5,0.0));

  G4Tubs* SiCrystalSol = new G4Tubs("SiCrystalSolid", 0, 11.3*mm/2, 0.3*mm/2, 0.0, 360.0*deg);
  G4Tubs* SiContainerSol = new G4Tubs("SiContainerSolid", 0, 11.3*mm/2, 0.3*mm/2, 0.0, 360.0*deg);

  G4LogicalVolume *SiCrystalLog = new G4LogicalVolume(SiCrystalSol, materials->GetMaterial("G4_Si"), "SiCrystalLogical");

  G4LogicalVolume *SiContainerLog = new G4LogicalVolume(SiContainerSol, materials->GetMaterial("G4_Galactic"), "SiContainerLogical");

  auto *SiCrystalPhys = new G4PVPlacement(0,G4ThreeVector(0*cm,0*cm,0*cm),SiCrystalLog,"SiCrystalPhys",SiContainerLog,0,0);
   
  SiCrystalLog->SetVisAttributes(colorSiCrystal);
  SiContainerLog->SetVisAttributes(colorSiContainer);
  
  // SiContainerLog should be the mother of all embedded volumes
  // use union and subtraction of volumes whenever possible
  return SiContainerLog;
  
}
