#include "MSPAD5.hh"
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

MSPAD5::MSPAD5(){;}


MSPAD5::~MSPAD5(){;}

G4LogicalVolume *MSPAD5::Construct(G4int CopyNumber)
{
  materials = Materials::GetInstance();

  G4VisAttributes *colorMSPAD5Crystal = new G4VisAttributes(G4Colour(1.,1.,0.0));
  G4VisAttributes *colorMSPAD5Container = new G4VisAttributes(G4Colour(0.5,0.5,0.0));

  G4double CrystalX = 10*mm;
  G4double CrystalY = 10*mm;
  G4double CrystalT = 1*mm;

  G4double SmallCrystalX = 0.8*mm;
  G4double SmallCrystalY = 10*mm;
  G4double SmallCrystalT = 1*mm;

  ContX = 46.8*mm;
  ContY = 16*mm;
  G4double ContT = 3.9*mm;

  G4double GapSize = 0.2*mm;
  G4double ContCutX = 4*CrystalX+SmallCrystalX+4*GapSize+0.4*mm;
  G4double ContCutY = CrystalY+0.4*mm;
  G4double ContCutT = 1.9*mm;

  G4Box* MSPAD5CrystalSol = new G4Box("MSPAD5CrystalSolid", CrystalX/2, CrystalY/2, CrystalT/2);
  G4Box* MSPAD5SmallCrystalSol = new G4Box("MSPAD5SmallCrystalSolid", SmallCrystalX/2, SmallCrystalY/2, SmallCrystalT/2);
  G4Box* MSPAD5Container1Sol = new G4Box("MSPAD5Container1Solid", ContX/2, ContY/2, ContT/2);
  G4Box* MSPAD5ContainerCutSol = new G4Box("MSPAD5ContainerCutSolid", ContCutX/2, ContCutY/2, ContCutT/2);
  G4SubtractionSolid* MSPAD5ContainerSol = new G4SubtractionSolid("MSPAD5ContainerSolid", MSPAD5Container1Sol, MSPAD5ContainerCutSol, 0, G4ThreeVector(0,0,ContT/2-ContCutT/2));

  G4LogicalVolume *MSPAD5ContainerLog = new G4LogicalVolume(MSPAD5ContainerSol, materials->GetMaterial("G4_ALUMINUM_OXIDE"), "MSPAD5ContainerLogical");
  G4LogicalVolume *MSPAD5CrystalLog = new G4LogicalVolume(MSPAD5CrystalSol, materials->GetMaterial("G4_Si"), "MSPAD5CrystalLogical");
  G4LogicalVolume *MSPAD5SmallCrystalLog = new G4LogicalVolume(MSPAD5SmallCrystalSol, materials->GetMaterial("G4_Si"), "MSPAD5SmallCrystalLogical");


  auto *MSPAD5SmallCrystalPhys = new G4PVPlacement(0,G4ThreeVector(0*cm,0*cm,ContT/2-ContCutT-CrystalT/2),MSPAD5SmallCrystalLog,"MSPAD5SmallCrystalPhys",MSPAD5ContainerLog,0,5*CopyNumber);

  G4double posX = -SmallCrystalX/2-GapSize-CrystalX/2;
  auto *MSPAD5CrystalPhys0 = new G4PVPlacement(0,G4ThreeVector(posX,0*cm,ContT/2-ContCutT-CrystalT/2),MSPAD5CrystalLog,"MSPAD5CrystalPhys",MSPAD5ContainerLog,0,5*CopyNumber+1);
  posX = posX - CrystalX/2 - GapSize - CrystalX/2;
  auto *MSPAD5CrystalPhys1 = new G4PVPlacement(0,G4ThreeVector(posX,0*cm,ContT/2-ContCutT-CrystalT/2),MSPAD5CrystalLog,"MSPAD5CrystalPhys",MSPAD5ContainerLog,0,5*CopyNumber+2);
  posX = SmallCrystalX/2 + GapSize + CrystalX/2;
  auto *MSPAD5CrystalPhys2 = new G4PVPlacement(0,G4ThreeVector(posX,0*cm,ContT/2-ContCutT-CrystalT/2),MSPAD5CrystalLog,"MSPAD5CrystalPhys",MSPAD5ContainerLog,0,5*CopyNumber+3);
  posX = posX + CrystalX/2 + GapSize + CrystalX/2;
  auto *MSPAD5CrystalPhys3 = new G4PVPlacement(0,G4ThreeVector(posX,0*cm,ContT/2-ContCutT-CrystalT/2),MSPAD5CrystalLog,"MSPAD5CrystalPhys",MSPAD5ContainerLog,0,5*CopyNumber+4);
   
  MSPAD5CrystalLog->SetVisAttributes(colorMSPAD5Crystal);
  MSPAD5SmallCrystalLog->SetVisAttributes(colorMSPAD5Crystal);
  MSPAD5ContainerLog->SetVisAttributes(colorMSPAD5Container);
  
  // MSPAD5ContainerLog should be the mother of all embedded volumes
  // use union and subtraction of volumes whenever possible

  return MSPAD5ContainerLog;
  
}
G4double MSPAD5::GetX()
{
  return ContX;
}
G4double MSPAD5::GetY()
{
  return ContY;
}
