#include "MSPAD5SD.hh"
#include "TrackInformation.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

MSPAD5SD::MSPAD5SD(G4String name)
  :G4VSensitiveDetector(name), MSPAD5Collection(0), HCID(0)
{
  HCname = "MSPAD5Collection";
  collectionName.insert(HCname);
  //G4cout << collectionName.size() << " SD name:  " << name << " collection Name: " << HCname << G4endl;
  HCID = -1;
}

MSPAD5SD::MSPAD5SD()
  :G4VSensitiveDetector(""), MSPAD5Collection(0), HCID(0), HCname("")
{
  HCID = -1;
}

MSPAD5SD::~MSPAD5SD()
{
}

void MSPAD5SD::Initialize(G4HCofThisEvent* HCE)
{
  MSPAD5Collection = new MSPAD5HitsCollection(SensitiveDetectorName,collectionName[0]); 
  if(HCID<0) {
    G4cout << "MSPAD5SD::Initialize:  " << SensitiveDetectorName << "   " << collectionName[0] << G4endl;
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  HCE->AddHitsCollection(HCID,MSPAD5Collection);
}

G4bool MSPAD5SD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  if(edep==0.) return false;

  TrackInformation* info = (TrackInformation*)(aStep->GetTrack()->GetUserInformation());

  MSPAD5Hit* newHit = new MSPAD5Hit();
  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
  newHit->SetParticleCode(aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  //newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetCopyNo());
  newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber());
  newHit->SetParticleTime(aStep->GetPreStepPoint()->GetGlobalTime());
  newHit->SetVertexPos(aStep->GetTrack()->GetVertexPosition());
  newHit->SetFirstStep(aStep->IsFirstStepInVolume());
  newHit->SetLevelEnergy(info->GetLevelEnergy());
  newHit->SetOriginalEnergy(info->GetOriginalEnergy());
  //G4cout << aStep->GetTrack()->GetDefinition()->GetPDGEncoding() << "  " << aStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;


  MSPAD5Collection->insert(newHit);
  
  newHit->Print();
  
  return true;
}

void MSPAD5SD::EndOfEvent(G4HCofThisEvent*)
{
}
