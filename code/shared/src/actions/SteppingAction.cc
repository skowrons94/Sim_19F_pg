#include "SteppingAction.hh"
#include "EventAction.hh"
//#include "TrackInformation.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "G4SteppingManager.hh"
#include "Randomize.hh"

SteppingAction::SteppingAction(EventAction* EA):eventaction(EA)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{ 

  //Enable tracking only for geantinos
  if (aStep->GetTrack()->GetDefinition()->GetParticleName() == "geantino") {
 
    //Stop tracking before last step
    G4bool isNextStep = true;
    if (aStep->GetTrack()->GetPosition().mag() / m > 20. ) isNextStep = false;

    if (isNextStep) {
  
    G4cout << " Track: " << aStep->GetTrack()->GetTrackID() << "   " << aStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;
    G4cout << "  KinE: " << aStep->GetPreStepPoint()->GetKineticEnergy() / keV << " keV " << "  dE: " << aStep->GetTotalEnergyDeposit() / keV << " keV " << aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << " " << aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() << " [ " << aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial()->GetName() << " ] " << aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName() << " [ " << aStep->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial()->GetName() << " ] " << aStep->GetPostStepPoint()->GetPosition() / cm << " cm " << G4endl;

    }
  }

  //TrackInformation* info = (TrackInformation*)(aStep->GetTrack()->GetUserInformation());

  /*
  G4cout << " Track: " << aStep->GetTrack()->GetTrackID() << "   " << aStep->GetTrack()->GetDefinition()->GetParticleName() << "  ParentID: " << aStep->GetTrack()->GetParentID() << G4endl;
  G4cout << "   Step: " << aStep->GetTrack()->GetCurrentStepNumber() << "  KinE: " << aStep->GetPreStepPoint()->GetKineticEnergy() << "  dE: " << aStep->GetTotalEnergyDeposit() << "  NofSecondariesThisStep: " << aStep->GetNumberOfSecondariesInCurrentStep() << G4endl;
  G4cout << "       Secondaries: " << G4endl;
  for(G4int i=0;i<aStep->GetNumberOfSecondariesInCurrentStep();i++) {
    G4cout << aStep->GetSecondaryInCurrentStep()->at(i)->GetDefinition()->GetParticleName() << "  KinE: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetKineticEnergy() << "  CreatorProcess: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetCreatorProcess()->GetProcessName() << "  ParentID: " << aStep->GetSecondaryInCurrentStep()->at(i)->GetParentID() << G4endl;
  }
  */
  
  const std::vector<const G4Track*>* secondary = aStep->GetSecondaryInCurrentStep();
  
  if((*secondary).size()!=0) {
    //G4cout << " SteppingAction::NofSecinThisStep: " << (*secondary).size() << G4endl;
    
    for(size_t lp=0; lp<(*secondary).size(); lp++) {
      /*      
      G4cout << "Secondary: " << (*secondary)[lp]->GetDefinition()->GetParticleName() << G4endl;
      G4cout << " KinE: " << (*secondary)[lp]->GetKineticEnergy()/keV << "\t Mom: " << (*secondary)[lp]->GetMomentum() << "\t Z: " << (*secondary)[lp]->GetDefinition()->GetAtomicNumber() << "\t A: " << (*secondary)[lp]->GetDefinition()->GetAtomicMass() << "\t PDGMass: " << (*secondary)[lp]->GetDefinition()->GetPDGMass() << "\t KinE from Mom: " << (sqrt(pow((*secondary)[lp]->GetDefinition()->GetPDGMass(),2)+pow((*secondary)[lp]->GetMomentum().mag(),2))-(*secondary)[lp]->GetDefinition()->GetPDGMass())/keV << G4endl;
      
      G4cout << "parent: " << aStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;
      G4cout << "TrackID: " << aStep->GetTrack()->GetTrackID() << "\t KinE: " << aStep->GetPreStepPoint()->GetKineticEnergy()/keV << "\t Mom: " << aStep->GetPreStepPoint()->GetMomentum() << "\t Pos: " << aStep->GetTrack()->GetPosition() << "\t Z: " << aStep->GetTrack()->GetDefinition()->GetAtomicNumber() << "\t A: " << aStep->GetTrack()->GetDefinition()->GetAtomicMass() << "\t PDGMass: " << aStep->GetTrack()->GetDefinition()->GetPDGMass() << "\t KinE from Mom: " << (sqrt(pow(aStep->GetTrack()->GetDefinition()->GetPDGMass(),2)+pow(aStep->GetPreStepPoint()->GetMomentum().mag(),2))-aStep->GetTrack()->GetDefinition()->GetPDGMass())/keV << G4endl;
      */
      eventaction->SetSecondaryInfo((*secondary)[lp]->GetKineticEnergy(),(*secondary)[lp]->GetMomentum(),(*secondary)[lp]->GetDefinition(),aStep->GetPreStepPoint()->GetKineticEnergy(),aStep->GetPreStepPoint()->GetMomentum(),aStep->GetTrack()->GetPosition(),aStep->GetTrack()->GetDefinition(),aStep->GetTrack()->GetTrackID());
    }
  }
  
}
