#include "ScPSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

ScPSD::ScPSD(G4String name)
  :G4VSensitiveDetector(name), ScPCollection(0), HCID(0)
{
  HCname = "ScPCollection";
  collectionName.insert(HCname);
  //G4cout << collectionName.size() << " SD name:  " << name << " collection Name: " << HCname << G4endl;
  HCID = -1;
}

ScPSD::ScPSD()
  :G4VSensitiveDetector(""), ScPCollection(0), HCID(0), HCname("")
{
  HCID = -1;
}

ScPSD::~ScPSD()
{
}

void ScPSD::Initialize(G4HCofThisEvent* HCE)
{
  ScPCollection = new ScPHitsCollection(SensitiveDetectorName,collectionName[0]); 
  if(HCID<0) {
    G4cout << "ScPSD::Initialize:  " << SensitiveDetectorName << "   " << collectionName[0] << G4endl;
    HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }
  HCE->AddHitsCollection(HCID,ScPCollection);
}

G4bool ScPSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  
  if(edep==0.) return false;

  ScPHit* newHit = new ScPHit();
  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
  newHit->SetParticleCode(aStep->GetTrack()->GetDefinition()->GetPDGEncoding());
  newHit->SetEdep(edep);
  newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
  newHit->SetCopyNo(aStep->GetPreStepPoint()->GetTouchable()->GetCopyNumber(3));
  newHit->SetParticleTime(aStep->GetPreStepPoint()->GetGlobalTime());

  ScPCollection->insert(newHit);
  
  newHit->Print();
  
  return true;
}

void ScPSD::EndOfEvent(G4HCofThisEvent*)
{
}
