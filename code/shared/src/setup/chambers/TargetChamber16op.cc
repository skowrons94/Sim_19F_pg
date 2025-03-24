#include "TargetChamber16op.hh"
#include "TargetChamber16opMessenger.hh"
#include "Materials.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"


#include "G4UnionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"


TargetChamber16op::TargetChamber16op(){
  targetchamber16opMessenger = new TargetChamber16opMessenger(this);
}


TargetChamber16op::~TargetChamber16op(){
  delete targetchamber16opMessenger;
}

TargetChamber16op* TargetChamber16op::instance = 0;

TargetChamber16op* TargetChamber16op::GetInstance()
{
  if (instance == 0)
    {
      instance = new TargetChamber16op;

    }
  return instance;
}



G4LogicalVolume *TargetChamber16op::Construct()
{


  materials = Materials::GetInstance();
  /// Dimensions
  //

  // CF100 flange upstream
  lengthCF100 = 18 * mm;
  const auto rInnerCF100 = 0.5 * 37  * mm; // Assumed everything is a cylinder with an inner radius of 37 mm
  const auto rOuterCF100 = 0.5 * 114 * mm;

  // CF 40 flange
  lengthCF40 =       13 * mm;
  const auto rInnerCF40 = 0.5 * 37 * mm;
  const auto rOuterCF40 = 0.5 * 70 * mm;

  // Tube
  lengthTube =     234 * mm;
  const auto rInnerTube = 0.5* 37 * mm;
  const auto rOuterTube = 0.5* 40 * mm;

  // Threaded counter flange for target holder installation
  lengthCounterFlange = 13.0 * mm;
  const auto rInnerCounterFlange = 0.5 * 40 * mm;
  const auto rOuterCounterFlange = 0.5 * 52 * mm;

  const auto phiStart =   0*deg;
  const auto phiTotal = 360*deg;

  // Chamber itself
  const G4int chamberNZPlanes = 4;
  const G4double chamberZPlanes[] =
    {
      lengthCF100+lengthCF40,
      lengthCF100+lengthCF40+lengthTube,
      lengthCF100+lengthCF40+lengthTube,
      lengthCF100+lengthCF40+lengthTube+lengthCounterFlange
    };

  const G4double chamberRInner[] =
    {
      rInnerTube,
      rInnerTube,
      rInnerCounterFlange,
      rInnerCounterFlange
    };

  const G4double chamberROuter[] =
    {
      rOuterTube,
      rOuterTube,
      rOuterCounterFlange,
      rOuterCounterFlange
    };

  std::cout << "TargetChamber16op.cc: finished setting dimensions" << std::endl;

  /// Solids
  auto solidCF100
    = new G4Tubs("CF100",
		 rInnerCF100, rOuterCF100,
		 0.5*lengthCF100,
		 phiStart,phiTotal);

  auto solidCF40
    = new G4Tubs("CF40",
		 rInnerCF40, rOuterCF40,
		 0.5*lengthCF40,
		 phiStart,phiTotal);

  auto solidCounterFlange
    = new G4Tubs("CounterFlange",
		 rInnerCounterFlange, rOuterCounterFlange,
		 0.5*lengthCounterFlange,
		 phiStart,phiTotal);

  auto solidTube
    = new G4Tubs("Tube",
		 rInnerTube, rOuterTube,
		 0.5*lengthTube,
		 phiStart,phiTotal);


  auto solidUni0 = new G4UnionSolid("Uni0",solidCF100,solidCF40,0,G4ThreeVector(0,0,lengthCF100/2+lengthCF40/2));
  auto solidUni1 = new G4UnionSolid("Uni1",solidUni0,solidTube,0,G4ThreeVector(0,0,lengthCF100/2+lengthCF40+lengthTube/2));
  auto solidTargetChamber = new G4UnionSolid("TargetChamber",solidUni1,solidCounterFlange,0,G4ThreeVector(0,0,lengthCF100/2+lengthCF40+lengthTube+lengthCounterFlange/2));

  std::cout << "TargetChamber16op.cc: finished creating solids" << std::endl;

  /// Logical volumes
  //
  // Default to aluminium
  G4Material* TargetCh16opMat = materials->GetMaterial("G4_Al");
  std::cout << "TargetChamber16op.cc: created aluminium G4Material* for target chamber" << std::endl;
  if (TargetCh16opType == "Steel") {
    TargetCh16opMat = materials->GetMaterial("G4_STAINLESS-STEEL");
    std::cout << "TargetChamber16op.cc: target chamber material changed to stainless steel" << std::endl;
  }
  G4LogicalVolume* logicTargetChamber = new G4LogicalVolume(solidTargetChamber, TargetCh16opMat, "logicTargetChamber");
	
  std::cout << "TargetChamber16op.cc: created target chamber logical volume" << std::endl;
    
  //G4VPhysicalVolume *physWorld2 = new G4PVPlacement(0, -G4ThreeVector(0.,0.,0), logicTargetChamber, "physWorld2", 0, false, 0, true);


  /*
    G4LogicalVolume* logicCF40 = new G4LogicalVolume(solidCF40, materials->GetMaterial("G4_STAINLESS-STEEL"),
    "logicCF40");
    //G4VPhysicalVolume *physWorld1 = new G4PVPlacement(0, -G4ThreeVector(0.,0.,-24.5), logicCF40, "physWorld1", logicTargetChamber, false, 0, true);
    G4VPhysicalVolume *physWorld1 = new G4PVPlacement(0, -G4ThreeVector(0.,0.,-24), logicCF40, "physWorld1", logicTargetChamber, false, 0, true);





    G4LogicalVolume* logicCF100 = new G4LogicalVolume(solidCF100, materials->GetMaterial("G4_STAINLESS-STEEL"),
    "logicCF100");
    //G4VPhysicalVolume *physWorld = new G4PVPlacement(0, -G4ThreeVector(0.,0.,15.5), logicCF100, "physWorld", logicCF40, false, 0, true);
    */

  std::cout << "TargetChamber16op.cc: finished creating logical volumes" << std::endl;

  /// Visualization attributes
  logicTargetChamber->SetVisAttributes(G4VisAttributes(G4Colour::Yellow()));

  std::cout << "TargetChamber16op.cc: finished setting visual attributes" << std::endl;

  return logicTargetChamber;
}
G4double TargetChamber16op::GetLength()
{
  return lengthCounterFlange+lengthTube+lengthCF40+lengthCF100/2;
}
