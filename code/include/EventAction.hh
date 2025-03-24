#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"

class AnalysisManager;
class G4Event;
class EventActionMessenger;

class EventAction : public G4UserEventAction
{
public:
  EventAction(AnalysisManager*);
  ~EventAction();
  
public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

  void SetSecondaryInfo(G4double,G4ThreeVector,G4ParticleDefinition*,G4double,G4ThreeVector,G4ThreeVector,G4ParticleDefinition*,G4int);

  void SetNoiseBGO14Np(G4double fN_BGO14Np) {N_BGO14Np = fN_BGO14Np;};

private:
  AnalysisManager*    analysismanager;
  G4int BGO14NpCollID;
  EventActionMessenger* eventActionMessenger;
  G4double N_BGO14Np;
  G4int NofSec;
  G4double SecKinE[10000];
  G4ThreeVector SecMom[10000];
  G4ParticleDefinition *SecPartDef[10000];
  G4double ParKinE[10000];
  G4ThreeVector ParMom[10000];
  G4ThreeVector ParPos[10000];
  G4ParticleDefinition *ParPartDef[10000];
  G4int ParTrackID[10000];
};

#endif
