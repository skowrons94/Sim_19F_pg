#include "RingHolder.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

RingHolder::RingHolder(){;}
RingHolder::~RingHolder(){;}

G4LogicalVolume *RingHolder::Construct()
{


  materials = Materials::GetInstance();

  G4VisAttributes *color1 = new G4VisAttributes(G4Colour(0.,0.,1.0));

  // Ring holder
  lengthRingHolder = 2. * mm;
  const G4double rInnerRingHolder = 23. * mm;
  const G4double rOuterRingHolder = 40. * mm;

  const G4double phiStart = 0*deg;
  const G4double phiTotal = 360*deg;

  /// Solids
  auto solidRingHolder = new G4Tubs("RingHolder", 0.5*rInnerRingHolder, 0.5*rOuterRingHolder, 0.5*lengthRingHolder, phiStart, phiTotal);

  /// Logical
  G4LogicalVolume* logicRingHolder = new G4LogicalVolume(solidRingHolder, materials->GetMaterial("G4_Al"),"logicRingHolder");

  /// Visualization attributes
  logicRingHolder->SetVisAttributes(G4VisAttributes(color1));

  return logicRingHolder;
}

G4double RingHolder::GetLength()
{
  return 0.5*lengthRingHolder;
}
