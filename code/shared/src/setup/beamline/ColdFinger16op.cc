#include "ColdFinger16op.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"


#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

ColdFinger16op::ColdFinger16op(){;}
ColdFinger16op::~ColdFinger16op(){;}

G4LogicalVolume *ColdFinger16op::Construct()
{
  
  
  materials = Materials::GetInstance();
  
  // Cold Trap
  lengthColdTrap = 170 * mm;
  const G4double rInnerColdTrap = 0.5 * 25 * mm;
  const G4double rOuterColdTrap = 0.5 * 28 * mm;
  
  const G4double phiStart = 0*deg;
  const G4double phiTotal = 360*deg;
  
  /// Solids
  auto solidTrap
    = new G4Tubs("Trap",
                 rInnerColdTrap, rOuterColdTrap,
                 0.5*lengthColdTrap,
                 phiStart,phiTotal);
  
  /// Logical
  G4LogicalVolume* logicTrap = new G4LogicalVolume(solidTrap, materials->GetMaterial("G4_Cu"),"logicTrap");
  
  /// Visualization attributes
  logicTrap->SetVisAttributes(G4VisAttributes(G4Colour::Brown()));
  
  return logicTrap;
}
G4double ColdFinger16op::GetLength()
{
  return lengthColdTrap;
}
