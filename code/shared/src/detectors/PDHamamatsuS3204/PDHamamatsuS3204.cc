#include "PDHamamatsuS3204.hh"
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

PDHamamatsuS3204::PDHamamatsuS3204(){;}


PDHamamatsuS3204::~PDHamamatsuS3204(){;}

G4LogicalVolume *PDHamamatsuS3204::Construct(G4int CopyNumber)
{
  materials = Materials::GetInstance();

  G4VisAttributes *colorPDHamamatsuS3204Crystal = new G4VisAttributes(G4Colour(1.,1.,0.0));
  G4VisAttributes *colorPDHamamatsuS3204Container = new G4VisAttributes(G4Colour(0.5,0.5,0.0));

  G4double CrystalX = 18*mm;
  G4double CrystalY = 18*mm;
  G4double CrystalT = 0.3*mm;

  ContX = 25.2*mm;
  ContY = 25.2*mm;
  G4double ContT = 2.55*mm;

  G4double ContCutX = 21.8*mm;
  G4double ContCutY = 21.8*mm;
  G4double ContCutT = 1.2*mm;

  G4Box* PDHamamatsuS3204CrystalSol = new G4Box("PDHamamatsuS3204CrystalSolid", CrystalX/2, CrystalY/2, CrystalT/2);
  G4Box* PDHamamatsuS3204Container1Sol = new G4Box("PDHamamatsuS3204Container1Solid", ContX/2, ContY/2, ContT/2);
  G4Box* PDHamamatsuS3204ContainerCutSol = new G4Box("PDHamamatsuS3204ContainerCutSolid", ContCutX/2, ContCutY/2, ContCutT/2);
  G4SubtractionSolid* PDHamamatsuS3204ContainerSol = new G4SubtractionSolid("PDHamamatsuS3204ContainerSolid", PDHamamatsuS3204Container1Sol, PDHamamatsuS3204ContainerCutSol, 0, G4ThreeVector(0,0,ContT/2-ContCutT/2));

  G4LogicalVolume *PDHamamatsuS3204ContainerLog = new G4LogicalVolume(PDHamamatsuS3204ContainerSol, materials->GetMaterial("G4_ALUMINUM_OXIDE"), "PDHamamatsuS3204ContainerLogical");
  G4LogicalVolume *PDHamamatsuS3204CrystalLog = new G4LogicalVolume(PDHamamatsuS3204CrystalSol, materials->GetMaterial("G4_Si"), "PDHamamatsuS3204CrystalLogical");


  auto *PDHamamatsuS3204CrystalPhys = new G4PVPlacement(0,G4ThreeVector(0*cm,0*cm,ContT/2-ContCutT-CrystalT/2),PDHamamatsuS3204CrystalLog,"PDHamamatsuS3204CrystalPhys",PDHamamatsuS3204ContainerLog,0,CopyNumber);
   
  PDHamamatsuS3204CrystalLog->SetVisAttributes(colorPDHamamatsuS3204Crystal);
  PDHamamatsuS3204ContainerLog->SetVisAttributes(colorPDHamamatsuS3204Container);
  
  // PDHamamatsuS3204ContainerLog should be the mother of all embedded volumes
  // use union and subtraction of volumes whenever possible

  return PDHamamatsuS3204ContainerLog;
  
}
G4double PDHamamatsuS3204::GetX()
{
  return ContX;
}
G4double PDHamamatsuS3204::GetY()
{
  return ContY;
}
