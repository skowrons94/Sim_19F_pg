#include "LeadShielding16opUpstream.hh"
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

LeadShielding16opUpstream::LeadShielding16opUpstream(){;}


LeadShielding16opUpstream::~LeadShielding16opUpstream(){;}

G4LogicalVolume *LeadShielding16opUpstream::Construct()
{
  materials = Materials::GetInstance();
  
  lengthBox3 = 305.5*mm;
  
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
  
  G4Polycone *box1 = new G4Polycone("aPolyconeSolid",0.0 * deg, 360.0 * deg, 4, z, rInner, rOuter );  //1
  
  std::vector<G4TwoVector> polygon(12);
  
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
  
  G4TwoVector offsetA(0,0), offsetB(0,0);
  G4double scaleA = 1, scaleB = 1;
  
  G4ExtrudedSolid *box3 = new G4ExtrudedSolid("solid", polygon, lengthBox3/2, offsetA, scaleA, offsetB, scaleB);
  G4VSolid *box5= new G4SubtractionSolid("Box+Cylinder", box3, box1, 0, G4ThreeVector(250*mm,0.,0));	
  
  G4LogicalVolume *logicLeadShield = new G4LogicalVolume(box5, materials->GetMaterial("G4_Pb"), "logicLeadShield");
  
  logicLeadShield->SetVisAttributes(G4VisAttributes(G4Colour::Black()));
  
  return logicLeadShield;
}

G4double LeadShielding16opUpstream::GetLength()
{
  return lengthBox3/2;
}
G4double LeadShielding16opUpstream::GetWidth()
{
  return 250*mm;
}
