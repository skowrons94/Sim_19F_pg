#include "SiSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

SiSD::SiSD(G4String name)
  :G4VSensitiveDetector(name), SiCollection(0), HCID(0)
{
  HCname = "SiCollection";
  collectionName.insert(HCname);
  //G4cout << collectionName.size() << " SD name:  " << name << " collection Name: " << HCname << G4endl;
  HCID = -1;
}

SiSD::SiSD()
  :G4VSensitiveDetector(""), SiCollection(0), HCID(0), HCname("")
{
  HCID = -1;
}

SiSD::~SiSD()
{
}

void SiSD::Initialize(G4HCofThisEvent* HCE)
{
  SiCollection = new SiHitsCollection(SensitiveDetectorName,collectionName[0]); 
  if(HCID<0) {
    G4cout << "SiSD::Initialize:  " << SensitiveDetectorName << "   " << collectionName[0] << G4endl;
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  HCE->AddHitsCollection(HCID,SiCollection);
}

G4bool SiSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  /*
  //if(aStep->GetTrack()->GetDefinition()->GetParticleName()!="deuteron") {
    G4cout << "NEW HIT in Si: " << aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber(1) << G4endl;
    G4cout << " Track: " << aStep->GetTrack()->GetTrackID() << "   " << aStep->GetTrack()->GetDefinition()->GetParticleName() << "  ParentID: " << aStep->GetTrack()->GetParentID() << G4endl;
    G4cout << "   Step: " << aStep->GetTrack()->GetCurrentStepNumber() << "  KinE: " << aStep->GetPreStepPoint()->GetKineticEnergy() << "  dE: " << aStep->GetTotalEnergyDeposit() << "  NofSecondariesThisStep: " << aStep->GetNumberOfSecondariesInCurrentStep() << G4endl;
    G4cout << "       Secondaries: " << G4endl;
    for(G4int i=0;i<aStep->GetNumberOfSecondariesInCurrentStep();i++) {
      G4cout << aStep->GetSecondaryInCurrentStep()->at(i)->GetDefinition()->GetParticleName() << "  KinE: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetKineticEnergy() << "  CreatorProcess: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetCreatorProcess()->GetProcessName() << "  ParentID: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetParentID() << G4endl;
    }
    //}
    */
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  //if(edep==0.) return false;

  SiHit* newHit = new SiHit();
  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
  newHit->SetParticleCode(aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  //newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetCopyNo());
  newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber(1));
  newHit->SetParticleTime(aStep->GetPreStepPoint()->GetGlobalTime());
  newHit->SetVertexPos(aStep->GetTrack()->GetVertexPosition());
  newHit->SetFirstStep(aStep->IsFirstStepInVolume());
  //G4cout << aStep->GetTrack()->GetDefinition()->GetPDGEncoding() << "  " << aStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;


  SiCollection->insert(newHit);
  
  newHit->Print();
  
  return true;
}

void SiSD::EndOfEvent(G4HCofThisEvent*)
{
}
