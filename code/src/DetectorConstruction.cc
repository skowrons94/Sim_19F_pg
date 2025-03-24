#include "DetectorConstruction.hh"
#include "BGO14Np.hh"
#include "BGO14NpSD.hh"
#include "BGO14NpTarget.hh"
#include "BGO14NpTargetHolder.hh"
#include "SourceNo138_139_140.hh"
#include "TargetChamber16op.hh"
#include "ColdFinger16op.hh"
#include "LeadShielding16op.hh"
#include "SourceNo110_114.hh"
#include "Materials.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4UserLimits.hh"

#include "DetectorConstructionMessenger.hh"

DetectorConstruction::DetectorConstruction():G4VUserDetectorConstruction()
{
  detectorConstructionMessenger = new DetectorConstructionMessenger(this);
  materials = Materials::GetInstance();
  ABGO = BGO14Np::GetInstance();
  ATarget = BGO14NpTarget::GetInstance();
  ATargetHolder = BGO14NpTargetHolder::GetInstance();
  ATargetChamber = TargetChamber16op::GetInstance();
}

DetectorConstruction::~DetectorConstruction()
{
  delete detectorConstructionMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  materials->CreateMaterials();
 
  G4bool checkOverlaps = false; 
  
  G4double distFromTarget = 15.*mm; 
  G4double SourceThickness = 0;

  auto WorldSol = new G4Box("WorldSol",50*m,50*m,50*m);
  auto WorldLog = new G4LogicalVolume(WorldSol,materials->GetMaterial("G4_Galactic"),"WorldLog",0,0,0);
  auto WorldPhys = new G4PVPlacement(0,G4ThreeVector(),WorldLog,"WorldPhys",0,0,0);
  auto WorldVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  WorldVisAtt->SetVisibility(false);
  WorldLog->SetVisAttributes(WorldVisAtt);

   if(Physics == "S") {
   	
    if(SourceHolder == "A") {
      // SourceNo138_139_140 for 60Co and 137Cs
      auto rotSource = new G4RotationMatrix();
      auto ASource = new SourceNo138_139_140();
      auto ASourceLog  = ASource->Construct();
      auto ASourcePhys = new G4PVPlacement(rotSource,SourcePos,ASourceLog,"ASourcePhys",WorldLog,false,0,checkOverlaps);
      SourceThickness = ASource->GetThickness();
    }
    else if(SourceHolder == "B") {
      // SourceNo110_114 for 133Ba
      auto rotSource = new G4RotationMatrix();
      auto ASource = new SourceNo110_114();
      auto ASourceLog  = ASource->Construct();
      auto ASourcePhys = new G4PVPlacement(rotSource,SourcePos,ASourceLog,"ASourcePhys",WorldLog,0,0);
      SourceThickness = ASource->GetThickness();
    }

  }	
  
  // TargetChamber
	 // ATargetChamber = new TargetChamber16op();
  	auto ATargetChamberLog  = ATargetChamber->Construct();
  	G4RotationMatrix* rotTargetChamber = new G4RotationMatrix();
  	rotTargetChamber->rotateX(0*deg);
  	auto ATargetChamberPhys = new G4PVPlacement(rotTargetChamber,G4ThreeVector(0,0,-ATargetChamber->GetLength() + SourceThickness),ATargetChamberLog,"ATargetChamberPhys",WorldLog,false,0,checkOverlaps);

  	
  	// ColdFinger
	  AColdFinger = new ColdFinger16op();
  	auto AColdFingerLog  = AColdFinger->Construct();
  	G4RotationMatrix* rotColdFinger = new G4RotationMatrix();
  	rotColdFinger->rotateX(0*deg);
  	auto AColdFingerPhys = new G4PVPlacement(rotColdFinger,G4ThreeVector(0,0,-AColdFinger->GetLength()/2 + SourceThickness - distFromTarget),AColdFingerLog,"AColdFingerPhys",WorldLog,false,0,checkOverlaps);

	  // LeadShielding
  	ALeadShielding = new LeadShielding16op();
  	auto ALeadShieldingLog  = ALeadShielding->Construct();
  	G4RotationMatrix* rotLeadShielding = new G4RotationMatrix();
  	rotLeadShielding->rotateZ(0*deg);
  	auto ALeadShieldingPhys = new G4PVPlacement(rotLeadShielding,G4ThreeVector(-ALeadShielding->GetWidth(),0,-ALeadShielding->GetLength()),ALeadShieldingLog,"ALeadShieldingPhys",WorldLog,false,0,checkOverlaps);
  
  	 // TargetHolder
 	//ATargetHolder = new BGO14NpTargetHolder();
  	auto ATargetHolderLog  = ATargetHolder->Construct();
  	G4RotationMatrix* rotTargetHolder = new G4RotationMatrix();
  	rotTargetHolder->rotateX(0*deg);
  	auto ATargetHolderPhys = new G4PVPlacement(rotTargetHolder,G4ThreeVector(0,0,-ATargetHolder->GetTargetPosition() + SourceThickness),ATargetHolderLog,"ATargetHolderPhys",WorldLog,false,0,checkOverlaps);
  
    // Target
    //ATarget = new BGO14NpTarget();
    auto ATargetLog  = ATarget->Construct();
  	G4RotationMatrix* rotTarget = new G4RotationMatrix();
  	rotTarget->rotateX(0.*deg);
   	auto ATargetPhys  = new G4PVPlacement(rotTarget,G4ThreeVector(0,0,ATargetHolder->GetTargetPosition()+ATarget->GetTargetThickness()/2),ATargetLog,"ATargetPhys",ATargetHolderLog,false,0,checkOverlaps);
  	
  	
	auto StepLimit = new G4UserLimits(MaxStep);
    ATarget->GetTargetLog()->SetUserLimits(StepLimit);
  
  // BGO
  auto ABGOLog  = ABGO->Construct();
  G4RotationMatrix* rotBGO = new G4RotationMatrix();
  rotBGO->rotateX(0.*deg);
  auto ABGOPhys = new G4PVPlacement(rotBGO,BGO14NpPos,ABGOLog,"ABGOPhys",WorldLog,false,0,checkOverlaps);


  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  G4String BGOSDname = "/BGO14NpSD";
  BGO14NpSD* ABGOSD = new BGO14NpSD(BGOSDname);
  SDman->AddNewDetector(ABGOSD);
  GetSensitiveDetector(ABGOPhys)->SetSensitiveDetector(ABGOSD);

  //------------------------------------------------------------------

  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  DumpGeometricalTree(WorldPhys);

  return WorldPhys;
}

void DetectorConstruction::DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth)
{
  for(int isp=0;isp<depth;isp++)
    { G4cout << "  "; }
  G4cout << aVolume->GetName() << "[" << aVolume->GetCopyNo() << "] "
         << aVolume->GetLogicalVolume()->GetName() << " "
         << aVolume->GetLogicalVolume()->GetNoDaughters() << " "
         << aVolume->GetLogicalVolume()->GetMaterial()->GetName();
  if(aVolume->GetLogicalVolume()->GetSensitiveDetector())
    {
      G4cout << " " << aVolume->GetLogicalVolume()->GetSensitiveDetector()
	->GetFullPathName();
    }
  G4cout << G4endl;
  for(int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++)
    { DumpGeometricalTree(aVolume->GetLogicalVolume()->GetDaughter(i),depth+1); }
}

G4LogicalVolume* DetectorConstruction::GetSensitiveDetector(G4VPhysicalVolume* aVolume,G4int depth)
{
  for(int isp=0;isp<depth;isp++)
    /*
      { G4cout << "  "; }
      G4cout << aVolume->GetName() << "[" << aVolume->GetCopyNo() << "] "
      << aVolume->GetLogicalVolume()->GetName() << " "
      << aVolume->GetLogicalVolume()->GetNoDaughters() << " "
      << aVolume->GetLogicalVolume()->GetMaterial()->GetName();
      G4cout << G4endl;
    */
    if(aVolume->GetName()=="bgoCrPhys") {
      //G4cout << "Detector Construction, Sensitive volume found: " << aVolume->GetName() << "copy number: " <<  aVolume->GetCopyNo() << ", logical volume: " <<  aVolume->GetLogicalVolume() << G4endl;
      SensitiveLogicalVolume = aVolume->GetLogicalVolume();
      break;
    }

  for(int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++)
    { GetSensitiveDetector(aVolume->GetLogicalVolume()->GetDaughter(i),depth+1); }

  return SensitiveLogicalVolume;
}

G4ThreeVector DetectorConstruction::GetSourcePos()
{
  return SourcePos/mm;
}

G4String DetectorConstruction::GetPhysics()
{
  return Physics;
}

G4String DetectorConstruction::GetSourceHolder()
{
  return SourceHolder;
}
