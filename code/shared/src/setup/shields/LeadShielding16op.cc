#include "LeadShielding16op.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4Polycone.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4ExtrudedSolid.hh"

LeadShielding16op::LeadShielding16op(){;}


LeadShielding16op::~LeadShielding16op(){;}

G4LogicalVolume *LeadShielding16op::Construct()
{
  materials = Materials::GetInstance();
  
  G4double ScPHoleDiam = 70*mm;
  G4double ScPHoleL = 150*mm;

  G4double GeHoleDiam = 130*mm;
  G4double GeHoleL = 300*mm;

  G4double OuterShieldGeInnerDiam = 130*mm;
  G4double OuterShieldGeOuterDiam = 420*mm;
  G4double OuterShieldGeL = 314.75*mm;

  G4double OuterShieldCutX = 600*mm;
  G4double OuterShieldCutY = 600*mm;
  G4double OuterShieldCutZ = 314.75*mm;

  lengthBox3 = 305.5*mm;
  lengthBox4 = 468*mm;
  
  G4double *rInner  =new G4double[4]; //1
  rInner[0]=0*mm;
  rInner[1]=0*mm;
  rInner[2]=0*mm;
  rInner[3]=0*mm;
  
  G4double *rOuter  =new G4double[4]; //1
  rOuter[0]=57.5*mm;
  rOuter[1]=57.5*mm;
  rOuter[2]=147*mm;
  rOuter[3]=147*mm;

  G4double *z  =new G4double[4];     //1 //-306.5,0,0,305.5
  z[0]=-153.75*mm;
  z[1]=-3.75*mm;
  z[2]=-3.75*mm;
  z[3]=153.75*mm;
  
  G4double *rInner1  =new G4double[4];  //2
  rInner1[0]=0*mm;
  rInner1[1]=0*mm;
  rInner1[2]=0*mm;
  rInner1[3]=0*mm;
  
  G4double *rOuter1  =new G4double[4]; //2   //65,65,145,145
  rOuter1[0]=145*mm;
  rOuter1[1]=145*mm;
  rOuter1[2]=65*mm;
  rOuter1[3]=65*mm;
  
  G4double *z1  =new G4double[4];  //2  //0,150*2,150*2,468*2
  z1[0]=-235*mm;
  z1[1]=83*mm;
  z1[2]=83*mm;
  z1[3]=235*mm;
  
  G4Polycone *box1 = new G4Polycone("aPolyconeSolid",0.0 * deg, 360.0 * deg, 4, z, rInner, rOuter );  //1
  G4Polycone *box2 = new G4Polycone("aPolyconeSolid2",0.0 * deg, 360.0 * deg, 4, z1, rInner1, rOuter1 );  //2
  
  std::vector<G4TwoVector> polygon(12);
  std::vector<G4TwoVector> polygon1(11);
  
  polygon[0] = G4TwoVector(0,150);
  polygon[1] = G4TwoVector(100,250);
  polygon[2] = G4TwoVector(355,250);
  polygon[3] = G4TwoVector(500,105);
  polygon[4] = G4TwoVector(500,-107);
  polygon[5] = G4TwoVector(415,-192);
  polygon[6] = G4TwoVector(362,-192);
  polygon[7] = G4TwoVector(362,-225);
  polygon[8] = G4TwoVector(128,-225);
  polygon[9] = G4TwoVector(128,-192);
  polygon[10] = G4TwoVector(40,-192);
  polygon[11] = G4TwoVector(0,-152);
  
  polygon1[0] = G4TwoVector(0,210);
  polygon1[1] = G4TwoVector(40,250);
  polygon1[2] = G4TwoVector(355,250);
  polygon1[3] = G4TwoVector(500,105);
  polygon1[4] = G4TwoVector(500,-107);
  polygon1[5] = G4TwoVector(415,-192);
  polygon1[6] = G4TwoVector(362,-192);
  polygon1[7] = G4TwoVector(362,-225);
  polygon1[8] = G4TwoVector(128,-225);
  polygon1[9] = G4TwoVector(128,-192);
  polygon1[10] = G4TwoVector(0,-192);
  
  G4TwoVector offsetA(0,0), offsetB(0,0);
  G4double scaleA = 1, scaleB = 1;
  
  G4TwoVector offsetA1(0,0), offsetB1(0,0);
  G4double scaleA1 = 1, scaleB1 = 1;
  
  G4ExtrudedSolid *box3 = new G4ExtrudedSolid("solid", polygon, lengthBox3/2, offsetA, scaleA, offsetB, scaleB);
  G4VSolid *box5= new G4SubtractionSolid("Box+Cylinder", box3, box1, 0, G4ThreeVector(250*mm,0.,0));	
  
  G4ExtrudedSolid *box4 = new G4ExtrudedSolid("solid", polygon1, lengthBox4/2, offsetA1, scaleA1, offsetB1, scaleB1);
  G4VSolid *box6= new G4SubtractionSolid("Box+Cylinder", box4, box2, 0, G4ThreeVector(250*mm,0.,0.));	
  
  auto solidUni0 = new G4UnionSolid("Uni0",box5,box6,0,G4ThreeVector(0,0,lengthBox3/2+lengthBox4/2));
  
  auto solidScPHole
    = new G4Tubs("ScPHole",
		 0, ScPHoleDiam/2,
		 ScPHoleL/2,
		 0*deg,360*deg);

  auto solidGeHole
    = new G4Tubs("GeHole",
		 0, GeHoleDiam/2,
		 GeHoleL/2,
		 0*deg,360*deg);

  auto solidOuterShieldGe0
    = new G4Tubs("OuterShieldGe0",
		 OuterShieldGeInnerDiam/2, OuterShieldGeOuterDiam/2,
		 OuterShieldGeL/2,
		 0*deg,360*deg);

  auto solidOuterShieldCut
    = new G4Box("OuterShieldCut",
		 OuterShieldCutX/2, OuterShieldCutY/2,
		 OuterShieldCutZ/2);


  G4RotationMatrix* rotOuterShieldCut = new G4RotationMatrix();
  rotOuterShieldCut->rotateY(-35*deg);

  G4VSolid *solidOuterShieldGe = new G4SubtractionSolid("OuterShieldGe", solidOuterShieldGe0, solidOuterShieldCut, rotOuterShieldCut, G4ThreeVector(-OuterShieldCutZ/2*sin(35*deg),0,-OuterShieldCutZ/2*cos(35*deg)));

  G4RotationMatrix* rotScPHole = new G4RotationMatrix();
  rotScPHole->rotateX(90*deg);

  G4RotationMatrix* rotGeHole = new G4RotationMatrix();
  rotGeHole->rotateY(55*deg);
  //rotGeHole->rotateY(90*deg);

  //G4VSolid *solidSub0 = new G4SubtractionSolid("Sub0", solidUni0, solidScPHole, rotScPHole, G4ThreeVector(250*mm,180*mm,lengthBox3/2));
  //G4VSolid *solidSub1 = new G4SubtractionSolid("Sub1", solidSub0, solidGeHole, rotGeHole, G4ThreeVector(250*mm-250*mm*sin(55*deg),0,lengthBox3/2+250*mm*cos(55*deg)));
  G4VSolid *solidSub1 = new G4SubtractionSolid("Sub1", solidUni0, solidGeHole, rotGeHole, G4ThreeVector(250*mm-250*mm*sin(55*deg),0,lengthBox3/2+8.55*mm+250*mm*cos(55*deg)));
  
  G4RotationMatrix* rotOuterShield = new G4RotationMatrix();
  rotOuterShield->rotateZ(180*deg);
  rotOuterShield->rotateY(-55*deg);

  auto solidLeadShield = new G4UnionSolid("LeadShield",solidSub1,solidOuterShieldGe,rotOuterShield,G4ThreeVector(0,0,lengthBox3/2+8.55*mm+250*mm*tan(35*deg)));

  G4LogicalVolume *logicLeadShield = new G4LogicalVolume(solidLeadShield, materials->GetMaterial("G4_Pb"), "logicLeadShield");
  //G4LogicalVolume *logicLeadShield = new G4LogicalVolume(solidOuterShieldGe, materials->GetMaterial("G4_Pb"), "logicLeadShield");
  //G4LogicalVolume *logicLeadShield = new G4LogicalVolume(box3, materials->GetMaterial("G4_Pb"), "logicLeadShield");
  
  logicLeadShield->SetVisAttributes(G4VisAttributes(G4Colour::Black()));
  
  return logicLeadShield;
}

G4double LeadShielding16op::GetLength()
{
  return lengthBox3/2;
}
G4double LeadShielding16op::GetWidth()
{
  return 250*mm;
}
