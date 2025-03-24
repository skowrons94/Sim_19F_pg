#include "GeSD.hh"
#include "TrackInformation.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"

GeSD::GeSD(G4String name)
  :G4VSensitiveDetector(name), GeCollection(0), HCID(0)
{
  HCname = "GeCollection";
  collectionName.insert(HCname);
  //G4cout << collectionName.size() << " SD name:  " << name << " collection Name: " << HCname << G4endl;
  HCID = -1;
}

GeSD::GeSD()
  :G4VSensitiveDetector(""), GeCollection(0), HCID(0), HCname("")
{
  HCID = -1;
}

GeSD::~GeSD()
{
}

void GeSD::Initialize(G4HCofThisEvent* HCE)
{
  GeCollection = new GeHitsCollection(SensitiveDetectorName,collectionName[0]); 
  if(HCID<0) {
    G4cout << "GeSD::Initialize:  " << SensitiveDetectorName << "   " << collectionName[0] << G4endl;
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  HCE->AddHitsCollection(HCID,GeCollection);
}

G4bool GeSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  if(edep==0.) return false;

  TrackInformation* info = (TrackInformation*)(aStep->GetTrack()->GetUserInformation());

  GeHit* newHit = new GeHit();
  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
  newHit->SetParticleCode(aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber());
  newHit->SetParticleTime(aStep->GetPreStepPoint()->GetGlobalTime());
  newHit->SetLevelEnergy(info->GetLevelEnergy());
  newHit->SetOriginalEnergy(info->GetOriginalEnergy());

  GeCollection->insert(newHit);
  
  newHit->Print();
  
  return true;
}

void GeSD::EndOfEvent(G4HCofThisEvent*)
{
}
