#include "LeadShielding16opDownstream.hh"
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

LeadShielding16opDownstream::LeadShielding16opDownstream(){;}


LeadShielding16opDownstream::~LeadShielding16opDownstream(){;}

G4LogicalVolume *LeadShielding16opDownstream::Construct()
{
  materials = Materials::GetInstance();
  
  lengthBox4 = 468*mm;
  
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
  
  G4Polycone *box2 = new G4Polycone("aPolyconeSolid2",0.0 * deg, 360.0 * deg, 4, z1, rInner1, rOuter1 );  //2
  
  std::vector<G4TwoVector> polygon1(11);
  
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
  
  G4TwoVector offsetA1(0,0), offsetB1(0,0);
  G4double scaleA1 = 1, scaleB1 = 1;
  
  G4ExtrudedSolid *box4 = new G4ExtrudedSolid("solid", polygon1, lengthBox4/2, offsetA1, scaleA1, offsetB1, scaleB1);
  G4VSolid *box6= new G4SubtractionSolid("Box+Cylinder", box4, box2, 0, G4ThreeVector(250*mm,0.,0.));	
  
  G4LogicalVolume *logicLeadShield = new G4LogicalVolume(box6, materials->GetMaterial("G4_Pb"), "logicLeadShield");
  
  logicLeadShield->SetVisAttributes(G4VisAttributes(G4Colour::Black()));
  
  return logicLeadShield;
}

G4double LeadShielding16opDownstream::GetLength()
{
  return lengthBox4/2;
}
G4double LeadShielding16opDownstream::GetWidth()
{
  return 250*mm;
}
