#include "BGO14NpSD.hh"
#include "TrackInformation.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

BGO14NpSD::BGO14NpSD(G4String name)
  :G4VSensitiveDetector(name), BGO14NpCollection(0), HCID(0)
{
  HCname = "BGO14NpCollection";
  collectionName.insert(HCname);
  //G4cout << collectionName.size() << " SD name:  " << name << " collection Name: " << HCname << G4endl;
  HCID = -1;
}

BGO14NpSD::BGO14NpSD()
  :G4VSensitiveDetector(""), BGO14NpCollection(0), HCID(0), HCname("")
{
  HCID = -1;
}

BGO14NpSD::~BGO14NpSD()
{
}

void BGO14NpSD::Initialize(G4HCofThisEvent* HCE)
{
  BGO14NpCollection = new BGO14NpHitsCollection(SensitiveDetectorName,collectionName[0]); 
  if(HCID<0) {
    //G4cout << "BGO14NpSD::Initialize:  " << SensitiveDetectorName << "   " << collectionName[0] << G4endl;
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  HCE->AddHitsCollection(HCID,BGO14NpCollection);
}

G4bool BGO14NpSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  if(edep==0.) return false;

  TrackInformation* info = (TrackInformation*)(aStep->GetTrack()->GetUserInformation());

  BGO14NpHit* newHit = new BGO14NpHit();
  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
  newHit->SetParticleCode(aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber());
  newHit->SetParticleTime(aStep->GetPreStepPoint()->GetGlobalTime());
  newHit->SetLevelEnergy(info->GetLevelEnergy());
  newHit->SetOriginalEnergy(info->GetOriginalEnergy());

  BGO14NpCollection->insert(newHit);
  
  newHit->Print();
  
  return true;
}

void BGO14NpSD::EndOfEvent(G4HCofThisEvent*)
{
}
