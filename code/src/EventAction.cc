#include "EventAction.hh"
#include "AnalysisManager.hh"
#include "BGO14NpHit.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "AnalysisManager.hh"
#include "EventActionMessenger.hh"

EventAction::EventAction(AnalysisManager* AM):analysismanager(AM)
{
  eventActionMessenger = new EventActionMessenger(this);
  BGO14NpCollID = -1;
  NofSec = 0;
}

EventAction::~EventAction()
{
  delete eventActionMessenger;
}

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  NofSec = 0;
  for(int i=0;i<10000;i++) {
    SecKinE[i] = 0;
    SecMom[i] = G4ThreeVector(0,0,0);
    ParKinE[i] = 0;
    ParMom[i] = G4ThreeVector(0,0,0);
    ParPos[i] = G4ThreeVector(0,0,0);
    ParTrackID[i] = -1;
  }
  analysismanager->ClearVariables();

  G4int eventID = evt->GetEventID();
  //G4cout << " eventID: " << eventID << G4endl;

  G4SDManager * SDman = G4SDManager::GetSDMpointer();
  if(BGO14NpCollID<0)
    {
      G4String colNam;
      BGO14NpCollID = SDman->GetCollectionID(colNam="BGO14NpCollection");
    }
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  if(BGO14NpCollID<0) return;
  
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  BGO14NpHitsCollection* BGO14NpHC = 0;
  
  if(HCE) {
    BGO14NpHC = (BGO14NpHitsCollection*)(HCE->GetHC(BGO14NpCollID));
  }
  
  G4double eDep_BGO14Np = 0;
  G4double eDepGauss_BGO14Np = 0;

  if(BGO14NpHC) {
    int NofHits = BGO14NpHC->entries();
    //G4cout << " NofHits in BGO14Np: " << NofHits << G4endl;
    if(NofHits > 0) {
      for(int i=0;i<NofHits;i++) {
	
	eDep_BGO14Np = (*BGO14NpHC)[i]->GetEdep()/keV;
	
	// noise level : N_BGO14Np
	G4double sigmaE = 0;
	if((*BGO14NpHC)[i]->GetCopyNo() == 0 || (*BGO14NpHC)[i]->GetCopyNo() == 1 || (*BGO14NpHC)[i]->GetCopyNo() == 2 || (*BGO14NpHC)[i]->GetCopyNo() == 3 || (*BGO14NpHC)[i]->GetCopyNo() == 4 || (*BGO14NpHC)[i]->GetCopyNo() == 5 ) sigmaE = N_BGO14Np*sqrt((*BGO14NpHC)[i]->GetEdep()/keV); // keV
	eDepGauss_BGO14Np = eDep_BGO14Np + G4RandGauss::shoot(0.0,sigmaE);

	//G4cout << "Event action Hit: " << i << "  copyNo: " << (*BGO14NpHC)[i]->GetCopyNo() << "  eDep: " << eDep_BGO14Np << G4endl; 
	analysismanager->FillhBGO14NpTotEdep(eDep_BGO14Np,eDepGauss_BGO14Np,(*BGO14NpHC)[i]->GetCopyNo(),NofHits,(*BGO14NpHC)[i]->GetParticleCode(),(*BGO14NpHC)[i]->GetLevelEnergy(),(*BGO14NpHC)[i]->GetOriginalEnergy());

      }
    }
  }

  analysismanager->FillhSecondaries(NofSec,SecKinE,SecMom,SecPartDef,ParKinE,ParMom,ParPos,ParPartDef,ParTrackID);

  analysismanager->FillHistogramsAndTree();
  analysismanager->ClearPrimaries();
  
  

}

void EventAction::SetSecondaryInfo(G4double fSecKinE, G4ThreeVector fSecMom, G4ParticleDefinition *fSecPartDef, G4double fParKinE, G4ThreeVector fParMom, G4ThreeVector fParPos, G4ParticleDefinition *fParPartDef, G4int fParTrackID)
{
  SecKinE[NofSec] = fSecKinE;
  SecMom[NofSec] = fSecMom;
  SecPartDef[NofSec] = fSecPartDef;
  ParKinE[NofSec] = fParKinE;
  ParMom[NofSec] = fParMom;
  ParPos[NofSec] = fParPos;
  ParPartDef[NofSec] = fParPartDef;
  ParTrackID[NofSec] = fParTrackID;

  NofSec++;
}
