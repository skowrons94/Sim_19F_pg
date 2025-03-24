#include "BGO14Np.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "BGO14NpMessenger.hh"

BGO14Np::BGO14Np(){
  bgo14NpMessenger = new BGO14NpMessenger(this);
}


BGO14Np::~BGO14Np(){
  delete bgo14NpMessenger;
}

BGO14Np* BGO14Np::instance = 0;

BGO14Np* BGO14Np::GetInstance()
{
  if (instance == 0)
    {
      instance = new BGO14Np;

    }
  return instance;
}

G4LogicalVolume *BGO14Np::Construct()
{
  materials = Materials::GetInstance();
  
G4RunManager* runManager=G4RunManager::GetRunManager();
 G4double bgoCas1aInDiam = 60*mm;
  G4double bgoCas1aOutDiam = 246*mm;
  G4double bgoCas1aL = 306*mm;

  G4double bgoCas1bInDiam = 245*mm;
  G4double bgoCas1bOutDiam = 290*mm;
  G4double bgoCas1bL = 22*mm;

  G4double bgoVacInDiam = 60*mm;
  G4double bgoVacOutDiam = 240*mm;
  G4double bgoVacL = 284*mm;

  G4double bgoAlInDiam = 60*mm;
  G4double bgoAlOutDiam = 61.6*mm;
  G4double bgoAlL = 284*mm;

  G4double bgoCr1L = 280*mm;
  G4double bgoCr2L = 115.2*mm;
  G4double bgoCr3L = 34.4*mm;
  G4double bgoCr4L = 70*mm;
  
  G4double DetDist[6];
  for (int i=0;i<6;i++){
  	DetDist[i] = 30*mm+bgoCr4L/2+(bgoAlOutDiam-bgoAlInDiam)/2+bgoDisplacement[i]*mm;
  }
  
  G4bool checkOverlaps = false;
  
  G4double RotAng[6] = {0*deg,60*deg,120*deg,180*deg,240*deg,300*deg};
  G4RotationMatrix* rot[6];

  G4RotationMatrix* rotSrc = new G4RotationMatrix;
  rotSrc->rotateX(90*deg);

  G4RotationMatrix* rotHold = new G4RotationMatrix;
  rotHold->rotateY(180*deg);

  for(G4int i=0;i<6;i++) {
    rot[i] = new G4RotationMatrix;
    rot[i]->rotateY(90*deg);
    rot[i]->rotateX(RotAng[i]);
    
  }
  
   // BGO case
  G4VSolid* bgoCas1aSol = new G4Tubs("bgoCas1aTube",bgoCas1aInDiam/2,bgoCas1aOutDiam/2,bgoCas1aL/2,0*deg,360.0*deg);
  G4VSolid* bgoCas1bSol = new G4Tubs("bgoCas1bTube",bgoCas1bInDiam/2,bgoCas1bOutDiam/2,bgoCas1bL/2,0*deg,360.0*deg);
  G4VSolid* bgoCas1dSol = new G4Tubs("bgoCas1dTube",bgoCas1bInDiam/2,bgoCas1bOutDiam/2,bgoCas1bL/2,0*deg,360.0*deg);
  G4UnionSolid* bgoCas1cSol = new G4UnionSolid("bgoCas1cTube", bgoCas1aSol, bgoCas1bSol, 0, G4ThreeVector(0,0,-bgoCas1aL/2+bgoCas1bL/2));
  G4UnionSolid* bgoCas1Sol = new G4UnionSolid("bgoCas1Tube", bgoCas1cSol, bgoCas1dSol, 0, G4ThreeVector(0,0,bgoCas1aL/2-bgoCas1bL/2));
 
  //G4LogicalVolume* bgoCas1Log = new G4LogicalVolume(bgoCas1Sol,materials->GetMaterial("G4_STAINLESS-STEEL"),"bgoCas1Log",0,0,0);
  G4LogicalVolume* bgoCas1Log = new G4LogicalVolume(bgoCas1Sol,materials->GetMaterial("StainlessSteel316"),"bgoCas1Log",0,0,0);
  
  // BGO vacuum
  G4VSolid* bgoVacSol = new G4Tubs("bgoVacTube",bgoVacInDiam/2,bgoVacOutDiam/2,bgoVacL/2,0.0,360.0*deg);

  G4LogicalVolume* bgoVacLog = new G4LogicalVolume(bgoVacSol,materials->GetMaterial("G4_Galactic"),"bgoVacLog",0,0,0);

  // BGO aluminum
  G4VSolid* bgoAlSol = new G4Tubs("bgoAlTube",bgoAlInDiam/2,bgoAlOutDiam/2,bgoAlL/2,0.0,360.0*deg);

  G4LogicalVolume* bgoAlLog = new G4LogicalVolume(bgoAlSol,materials->GetMaterial("G4_Al"),"bgoAlLog",0,0,0);

  // BGO crystal
  G4VSolid* bgoCrSol = new G4Trd("bgoCrTrd", bgoCr1L/2, bgoCr1L/2, bgoCr2L/2, bgoCr3L/2, bgoCr4L/2);

  G4LogicalVolume* bgoCrLog = new G4LogicalVolume(bgoCrSol,materials->GetMaterial("G4_BGO"),"bgoCrLog",0,0,0);
  
  
  //Physical volumes
  bgoVacPhys = new G4PVPlacement(0,G4ThreeVector(0,0,0),bgoVacLog,"bgoVacPhys",bgoCas1Log,false,0,checkOverlaps);
  bgoAlPhys = new G4PVPlacement(0,G4ThreeVector(0,0,0),bgoAlLog,"bgoAlPhys",bgoVacLog,false,0,checkOverlaps);

  for(G4int i=0;i<6;i++) {
    bgoCrPhys = new G4PVPlacement(rot[i],G4ThreeVector(cos(-RotAng[i])*DetDist[i],sin(-RotAng[i])*DetDist[i],0),bgoCrLog,"bgoCrPhys",bgoVacLog,0,i);
    G4cout<<"BGO14Np bgoCrPrhy copynumber" << i << "rot[" << i<<"]= " << rot[i] << "G4ThreeVector= " << G4ThreeVector(cos(-RotAng[i])*DetDist[i],sin(-RotAng[i])*DetDist[i],0) << rot[i] <<G4endl;
    if (checkOverlaps){
  	 if (bgoCrPhys->CheckOverlaps()==true){
  	 	 G4cout<<"BGO14Np Found overlapping abort esecution" <<G4endl;
  	 	 runManager->AbortRun();
	   }
	   else G4cout<<"BGO14Np No overlapping found" <<G4endl;
	}
   }
   
   
  bgoCas1VisAtt = new G4VisAttributes(G4Colour(1.0,2.0,0.0,0.2));
  bgoCas1VisAtt->SetVisibility(true);
  bgoCas1Log->SetVisAttributes(bgoCas1VisAtt);
  
 // bgo: purple
  bgoCrVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0,0.3));
  bgoCrVisAtt->SetVisibility(true);
  bgoCrLog->SetVisAttributes(bgoCrVisAtt);

  ////
  bgoAlVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  bgoAlVisAtt->SetVisibility(true);
  bgoAlLog->SetVisAttributes(bgoAlVisAtt);

  bgoVacVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,0.0));
  bgoVacVisAtt->SetVisibility(true);
  bgoVacLog->SetVisAttributes(bgoVacVisAtt);
  
  return bgoCas1Log;

}
