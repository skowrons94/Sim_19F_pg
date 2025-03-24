#include "Foil23napa.hh"
#include "Foil23napaMessenger.hh"

#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include <tuple>

Foil23napa::Foil23napa(){
    foil23napaMessenger = new Foil23napaMessenger(this);
    
}

Foil23napa::~Foil23napa(){
    delete foil23napaMessenger;
}

Foil23napa* Foil23napa::instance = 0;

Foil23napa* Foil23napa::GetInstance()
{
  if (instance == 0)
    {
      instance = new Foil23napa;

    }
  return instance;
}


std::tuple<G4LogicalVolume*, G4LogicalVolume*, G4LogicalVolume*,G4LogicalVolume*> Foil23napa::Construct(G4double thickness, G4double thicknessAl)
{
  materials = Materials::GetInstance();
  
  //G4cout<<"Thickness in foils "<<thickness<<G4endl;
  G4VisAttributes *color = new G4VisAttributes(G4Colour(0.,0.,1.0));
  G4VisAttributes *colorAl = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
  //dimensions of PD foils minimum/maximum values to avoid overlap
  G4Box *FoilPD23napaSol = new G4Box("FoilPD23napaSolid", 0.5*45.55*mm, 0.5*38.8*mm, thickness/2);
  G4Box *FoilAlPD23napaSol = new G4Box("FoilAlPD23napaSolid", 0.5*45.55*mm, 0.5*38.8*mm, thicknessAl/2);
    
  G4Box *FoilMSPAD23napaSol = new G4Box("FoilMSPAD23napaSolid", 0.5*50*mm, 0.5*30*mm, thickness/2);
  G4Box *FoilAlMSPAD23napaSol = new G4Box("FoilAlPD23napaSolid", 0.5*50*mm, 0.5*30*mm, thicknessAl/2);
    
  G4LogicalVolume *FoilPD23napaLog = new G4LogicalVolume(FoilPD23napaSol, materials->GetMaterial("G4_MYLAR"), "FoilPD23napaLogical");
  G4LogicalVolume *FoilAlPD23napaLog = new G4LogicalVolume(FoilAlPD23napaSol, materials->GetMaterial("G4_Al"), "FoilAlPD23napaLogical");
    
  G4LogicalVolume *FoilMSPAD23napaLog = new G4LogicalVolume(FoilMSPAD23napaSol, materials->GetMaterial("G4_MYLAR"), "FoilMSPAD23napaLogical");
    G4LogicalVolume *FoilAlMSPAD23napaLog = new G4LogicalVolume(FoilAlMSPAD23napaSol, materials->GetMaterial("G4_Al"), "FoilAlMSPAD23napaLogical");
    
  FoilPD23napaLog->SetVisAttributes(color);
    FoilMSPAD23napaLog->SetVisAttributes(color);
  FoilAlPD23napaLog->SetVisAttributes(colorAl);
    FoilAlMSPAD23napaLog->SetVisAttributes(colorAl);

    return std::make_tuple(FoilPD23napaLog, FoilAlPD23napaLog,FoilMSPAD23napaLog,FoilAlMSPAD23napaLog);
}

G4double Foil23napa::GetThickness()
{
  return Thickness;
}

G4double Foil23napa::GetThicknessAl()
{
  return ThicknessAl;
}

