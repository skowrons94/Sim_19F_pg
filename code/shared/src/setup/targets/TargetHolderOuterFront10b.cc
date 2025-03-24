#include "TargetHolderOuterFront10b.hh"
#include "TargetHolderOuterFront10bMessenger.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4GDMLParser.hh"

TargetHolderOuterFront10b::TargetHolderOuterFront10b(){
  targetholderouterfront10bMessenger = new TargetHolderOuterFront10bMessenger(this);
}


TargetHolderOuterFront10b::~TargetHolderOuterFront10b(){
  delete targetholderouterfront10bMessenger;
}

TargetHolderOuterFront10b* TargetHolderOuterFront10b::instance = 0;

TargetHolderOuterFront10b* TargetHolderOuterFront10b::GetInstance()
{
  if (instance == 0)
    {
      instance = new TargetHolderOuterFront10b;

    }
  return instance;
}

G4LogicalVolume *TargetHolderOuterFront10b::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,0.,1.0));

  auto aGDMLParser = new G4GDMLParser();
  aGDMLParser->Read(fileName);
  auto TargetHolderOuterFront10bLog = aGDMLParser->GetVolume("LV_screwy_target_holder_outer_front");
  TargetHolderOuterFront10bLog->SetMaterial(materials->GetMaterial("G4_STAINLESS-STEEL"));

  TargetHolderOuterFront10bLog->SetVisAttributes(color);
  
  return TargetHolderOuterFront10bLog;
}
