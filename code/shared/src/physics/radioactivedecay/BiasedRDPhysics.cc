#include "BiasedRDPhysics.hh"

#include "G4Radioactivation.hh"
#include "G4GenericIon.hh"
#include "globals.hh"
#include "G4PhysicsListHelper.hh"
#include "G4EmParameters.hh"
#include "G4VAtomDeexcitation.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4LossTableManager.hh"
#include "G4NuclearLevelData.hh"
#include "G4DeexPrecoParameters.hh"
#include "G4NuclideTable.hh"

// factory
#include "G4PhysicsConstructorFactory.hh"

G4_DECLARE_PHYSCONSTR_FACTORY(BiasedRDPhysics);


BiasedRDPhysics::BiasedRDPhysics(G4int)
 : G4VPhysicsConstructor("G4Radioactivation")
{
  G4EmParameters::Instance()->AddPhysics("World","G4Radioactivation");
  G4DeexPrecoParameters* deex = G4NuclearLevelData::GetInstance()->GetParameters();
  deex->SetStoreICLevelData(true);
  deex->SetMaxLifeTime(1E6);
  /*
  deex->SetMaxLifeTime(G4NuclideTable::GetInstance()->GetThresholdOfHalfLife()
                       /std::log(2.));
  */
  deex->SetIsomerProduction(true);
}

BiasedRDPhysics::BiasedRDPhysics(const G4String&)
 : BiasedRDPhysics(0)
{}


BiasedRDPhysics::~BiasedRDPhysics()
{}


void BiasedRDPhysics::ConstructParticle()
{
  G4GenericIon::GenericIon();
}


void BiasedRDPhysics::ConstructProcess()
{
  G4LossTableManager* man = G4LossTableManager::Instance();
  G4VAtomDeexcitation* ad = man->AtomDeexcitation();
  if(!ad) {
    G4EmParameters::Instance()->SetAugerCascade(true);
    ad = new G4UAtomicDeexcitation();
    man->SetAtomDeexcitation(ad);
    ad->InitialiseAtomicDeexcitation();
  }

  G4PhysicsListHelper::GetPhysicsListHelper()->
    RegisterProcess(new G4Radioactivation(), G4GenericIon::GenericIon());
}
