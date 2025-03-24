#include "Foilddgas.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

Foilddgas::Foilddgas(){
}


Foilddgas::~Foilddgas(){
}

G4LogicalVolume *Foilddgas::Construct(G4double Thickness)
{
  materials = Materials::GetInstance();

  G4VisAttributes *color = new G4VisAttributes(G4Colour(1.,0.,1.0));

  G4Box *FoilddgasSol = new G4Box("FoilddgasSolid", 10*mm, 10*mm, Thickness/2);

  G4LogicalVolume *FoilddgasLog = new G4LogicalVolume(FoilddgasSol, materials->GetMaterial("G4_MYLAR"), "FoilddgasLogical");
  
  FoilddgasLog->SetVisAttributes(color);
  
  return FoilddgasLog;
}
