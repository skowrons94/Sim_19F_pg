#include "Dome23napa.hh"
#include "Dome23napaMessenger.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4GDMLParser.hh"

Dome23napa::Dome23napa(){
  dome23napaMessenger = new Dome23napaMessenger(this);
}


Dome23napa::~Dome23napa(){
  delete dome23napaMessenger;
}

Dome23napa* Dome23napa::instance = 0;

Dome23napa* Dome23napa::GetInstance()
{
  if (instance == 0)
    {
      instance = new Dome23napa;

    }
  return instance;
}

G4LogicalVolume *Dome23napa::Construct()
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,0.,1.0));

  auto aGDMLParser = new G4GDMLParser();
  aGDMLParser->Read(fileName);
  auto Dome23napaLog = aGDMLParser->GetVolume("_vol_child_0");
  Dome23napaLog->SetMaterial(materials->GetMaterial("G4_Ag"));

  Dome23napaLog->SetVisAttributes(color);
  
  return Dome23napaLog;
}
