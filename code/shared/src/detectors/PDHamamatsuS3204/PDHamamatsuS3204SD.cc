#include "PDHamamatsuS3204SD.hh"
#include "TrackInformation.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

PDHamamatsuS3204SD::PDHamamatsuS3204SD(G4String name)
  :G4VSensitiveDetector(name), PDHamamatsuS3204Collection(0), HCID(0)
{
  HCname = "PDHamamatsuS3204Collection";
  collectionName.insert(HCname);
  //G4cout << collectionName.size() << " SD name:  " << name << " collection Name: " << HCname << G4endl;
  HCID = -1;
}

PDHamamatsuS3204SD::PDHamamatsuS3204SD()
  :G4VSensitiveDetector(""), PDHamamatsuS3204Collection(0), HCID(0), HCname("")
{
  HCID = -1;
}

PDHamamatsuS3204SD::~PDHamamatsuS3204SD()
{
}

void PDHamamatsuS3204SD::Initialize(G4HCofThisEvent* HCE)
{
  PDHamamatsuS3204Collection = new PDHamamatsuS3204HitsCollection(SensitiveDetectorName,collectionName[0]); 
  if(HCID<0) {
    G4cout << "PDHamamatsuS3204SD::Initialize:  " << SensitiveDetectorName << "   " << collectionName[0] << G4endl;
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  HCE->AddHitsCollection(HCID,PDHamamatsuS3204Collection);
}

G4bool PDHamamatsuS3204SD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  if(edep==0.) return false;

  TrackInformation* info = (TrackInformation*)(aStep->GetTrack()->GetUserInformation());

  PDHamamatsuS3204Hit* newHit = new PDHamamatsuS3204Hit();
  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
  newHit->SetParticleCode(aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber(1));
  newHit->SetParticleTime(aStep->GetPreStepPoint()->GetGlobalTime());
  newHit->SetVertexPos(aStep->GetTrack()->GetVertexPosition());
  newHit->SetFirstStep(aStep->IsFirstStepInVolume());
  newHit->SetLevelEnergy(info->GetLevelEnergy());
  newHit->SetOriginalEnergy(info->GetOriginalEnergy());


  PDHamamatsuS3204Collection->insert(newHit);
  
  newHit->Print();
  
  return true;
}

void PDHamamatsuS3204SD::EndOfEvent(G4HCofThisEvent*)
{
}
