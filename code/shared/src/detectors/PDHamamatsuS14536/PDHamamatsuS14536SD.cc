#include "PDHamamatsuS14536SD.hh"
#include "TrackInformation.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

PDHamamatsuS14536SD::PDHamamatsuS14536SD(G4String name)
  :G4VSensitiveDetector(name), PDHamamatsuS14536Collection(0), HCID(0)
{
  HCname = "PDHamamatsuS14536Collection";
  collectionName.insert(HCname);
  //G4cout << collectionName.size() << " SD name:  " << name << " collection Name: " << HCname << G4endl;
  HCID = -1;
}

PDHamamatsuS14536SD::PDHamamatsuS14536SD()
  :G4VSensitiveDetector(""), PDHamamatsuS14536Collection(0), HCID(0), HCname("")
{
  HCID = -1;
}

PDHamamatsuS14536SD::~PDHamamatsuS14536SD()
{
}

void PDHamamatsuS14536SD::Initialize(G4HCofThisEvent* HCE)
{
  PDHamamatsuS14536Collection = new PDHamamatsuS14536HitsCollection(SensitiveDetectorName,collectionName[0]);
  if(HCID<0) {
    G4cout << "PDHamamatsuS14536SD::Initialize:  " << SensitiveDetectorName << "   " << collectionName[0] << G4endl;
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  HCE->AddHitsCollection(HCID,PDHamamatsuS14536Collection);
}

G4bool PDHamamatsuS14536SD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{

  //if(aStep->GetTrack()->GetDefinition()->GetParticleName()!="deuteron") {
  /*
    G4cout << "NEW HIT in PDHamamatsuS14536: " << aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber(1) << G4endl;
    G4cout << " Track: " << aStep->GetTrack()->GetTrackID() << "   " << aStep->GetTrack()->GetDefinition()->GetParticleName() << "  ParentID: " << aStep->GetTrack()->GetParentID() << G4endl;
    G4cout << "   Step: " << aStep->GetTrack()->GetCurrentStepNumber() << "  KinE: " << aStep->GetPreStepPoint()->GetKineticEnergy() << "  dE: " << aStep->GetTotalEnergyDeposit() << "  NofSecondariesThisStep: " << aStep->GetNumberOfSecondariesInCurrentStep() << G4endl;
    G4cout << "       Secondaries: " << G4endl;
    for(G4int i=0;i<aStep->GetNumberOfSecondariesInCurrentStep();i++) {
      G4cout << aStep->GetSecondaryInCurrentStep()->at(i)->GetDefinition()->GetParticleName() << "  KinE: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetKineticEnergy() << "  CreatorProcess: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetCreatorProcess()->GetProcessName() << "  ParentID: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetParentID() << G4endl;
    }
  */
    //}

  G4double edep = aStep->GetTotalEnergyDeposit();
  
  //if(edep==0.) return false;

  PDHamamatsuS14536Hit* newHit = new PDHamamatsuS14536Hit();
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


  PDHamamatsuS14536Collection->insert(newHit);
  
  newHit->Print();
  
  return true;
}

void PDHamamatsuS14536SD::EndOfEvent(G4HCofThisEvent*)
{
}

