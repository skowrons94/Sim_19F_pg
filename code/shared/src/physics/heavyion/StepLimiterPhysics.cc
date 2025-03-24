#include "StepLimiterPhysics.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"
#include "G4BuilderType.hh"
#include "IonC12.hh"

// factory
#include "G4PhysicsConstructorFactory.hh"
//
G4_DECLARE_PHYSCONSTR_FACTORY(StepLimiterPhysics);

StepLimiterPhysics::StepLimiterPhysics(const G4String& name)
  :  G4VPhysicsConstructor(name),fApplyToAll(false)
{
  SetPhysicsType(bUnknown);
}

StepLimiterPhysics::~StepLimiterPhysics()
{}

void StepLimiterPhysics::ConstructParticle()
{}

void StepLimiterPhysics::ConstructProcess()
{
  auto myParticleIterator=GetParticleIterator();
  myParticleIterator->reset();

  G4StepLimiter* stepLimiter = new G4StepLimiter();
  G4UserSpecialCuts* userSpecialCuts = new G4UserSpecialCuts();
  while ((*myParticleIterator)()) {
    G4ParticleDefinition* particle = myParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4double charge = particle->GetPDGCharge();

    if(!particle->IsShortLived()) {
      if (charge != 0.0 || fApplyToAll) {
	// All charged particles should have a step limiter
	// to make sure that the steps do not get too long.
	pmanager->AddDiscreteProcess(stepLimiter);
	pmanager->AddDiscreteProcess(userSpecialCuts);
      } else {
	// Energy cuts for all other neutral particles
	pmanager->AddDiscreteProcess(userSpecialCuts);
      }
    }
  }

  G4ProcessManager* pmanager = IonC12::theIonC12()->GetProcessManager();
  G4double charge = IonC12::theIonC12()->GetPDGCharge();
  pmanager->AddDiscreteProcess(stepLimiter);
  pmanager->AddDiscreteProcess(userSpecialCuts);
  
}
