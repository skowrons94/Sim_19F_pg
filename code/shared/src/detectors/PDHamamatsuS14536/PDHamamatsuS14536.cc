#include "PDHamamatsuS14536.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

PDHamamatsuS14536::PDHamamatsuS14536(){;}


PDHamamatsuS14536::~PDHamamatsuS14536(){;}

G4LogicalVolume *PDHamamatsuS14536::Construct(G4int CopyNumber)
{
  materials = Materials::GetInstance();

  G4VisAttributes *colorPDHamamatsuS14536Crystal = new G4VisAttributes(G4Colour(1.,1.,0.0));
  G4VisAttributes *colorPDHamamatsuS14536Container = new G4VisAttributes(G4Colour(0.5,0.5,0.0));

  G4double CrystalX = 48*mm;
  G4double CrystalY = 48*mm;
  G4double CrystalT = 0.500*mm;

  ContX = 51*mm;
  ContY = 51*mm;
  G4double ContT = 1.9*mm;

  G4double ContCutX = 50.5*mm;
  G4double ContCutY = 50.4*mm;
  G4double ContCutT = 0.500*mm;

  G4Box* PDHamamatsuS14536CrystalSol = new G4Box("PDHamamatsuS14536CrystalSolid", CrystalX/2, CrystalY/2, CrystalT/2);
  G4Box* PDHamamatsuS14536Container1Sol = new G4Box("PDHamamatsuS14536Container1Solid", ContX/2, ContY/2, ContT/2);
  G4Box* PDHamamatsuS14536ContainerCutSol = new G4Box("PDHamamatsuS14536ContainerCutSolid", ContCutX/2, ContCutY/2, ContCutT/2);
  G4SubtractionSolid* PDHamamatsuS14536ContainerSol = new G4SubtractionSolid("PDHamamatsuS14536ContainerSolid", PDHamamatsuS14536Container1Sol, PDHamamatsuS14536ContainerCutSol, 0, G4ThreeVector(0,0,ContT/2-ContCutT/2));

  G4LogicalVolume *PDHamamatsuS14536ContainerLog = new G4LogicalVolume(PDHamamatsuS14536ContainerSol, materials->GetMaterial("G4_ALUMINUM_OXIDE"), "PDHamamatsuS14536ContainerLogical");
  G4LogicalVolume *PDHamamatsuS14536CrystalLog = new G4LogicalVolume(PDHamamatsuS14536CrystalSol, materials->GetMaterial("G4_Si"), "PDHamamatsuS14536CrystalLogical");


  auto *PDHamamatsuS14536CrystalPhys = new G4PVPlacement(0,G4ThreeVector(0*cm,0*cm,ContT/2-ContCutT-CrystalT/2),PDHamamatsuS14536CrystalLog,"PDHamamatsuS14536CrystalPhys",PDHamamatsuS14536ContainerLog,0,CopyNumber);
   
  PDHamamatsuS14536CrystalLog->SetVisAttributes(colorPDHamamatsuS14536Crystal);
  PDHamamatsuS14536ContainerLog->SetVisAttributes(colorPDHamamatsuS14536Container);
  
  // PDHamamatsuS14536ContainerLog should be the mother of all embedded volumes
  // use union and subtraction of volumes whenever possible

  return PDHamamatsuS14536ContainerLog;
  
}
G4double PDHamamatsuS14536::GetX()
{
  return ContX;
}
G4double PDHamamatsuS14536::GetY()
{
  return ContY;
}

