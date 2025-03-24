#include "StackingAction.hh"
#include "G4ios.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "Randomize.hh"
#include "G4VProcess.hh"
#include "G4IonTable.hh"
#include "G4PhysicalConstants.hh"
#include <math.h>

StackingAction::StackingAction()
{
}

StackingAction::~StackingAction()
{
}

void StackingAction::PrepareNewEvent()
{ 
}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
    if(( aTrack->GetDefinition()->GetAtomicNumber() == 0 && aTrack->GetDefinition()->GetAtomicMass() > 1)
       || (aTrack->GetDefinition()->GetAtomicNumber() < 0 && aTrack->GetDefinition()->GetAtomicMass() < 1) 
       || aTrack->GetKineticEnergy() < 0) {
    return fKill;
  }
  
  else return fUrgent;

}

void StackingAction::NewStage()
{
}
