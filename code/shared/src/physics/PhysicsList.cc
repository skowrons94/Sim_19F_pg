#include "PhysicsList.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProductionCuts.hh"
#include "G4SystemOfUnits.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmLowEPPhysics.hh"
#include "PhysListEmStandardNR.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "BiasedRDPhysics.hh"

#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronElasticPhysicsPHP.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "HadronPhysicsList.hh"

#include "G4EmConfigurator.hh"
#include "G4VEmModel.hh"
#include "G4LossTableManager.hh"
#include "G4BetheBlochModel.hh"
#include "G4BraggModel.hh"
#include "G4BraggIonModel.hh"
#include "G4LindhardSorensenIonModel.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4AtimaEnergyLossModel.hh"
#include "G4UrbanMscModel.hh"
#include "G4IonFluctuations.hh"
#include "G4UniversalFluctuation.hh"

#include "G4IonPhysicsXS.hh"
#include "HeavyIonPhysics.hh"

#include "G4NuclearLevelData.hh"

#include "G4CascadeParameters.hh"

#include "StepLimiterPhysics.hh"

#include "PhysicsListMessenger.hh"

PhysicsList::PhysicsList():G4VModularPhysicsList() {

  physicsListMessenger = new PhysicsListMessenger(this);

  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  //RegisterPhysics(new BiasedRDPhysics());
  RegisterPhysics( new StepLimiterPhysics());
  RegisterPhysics( new HeavyIonPhysics());

}

PhysicsList::~PhysicsList()
{ 
  delete physicsListMessenger;
}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
  //SetCutsWithDefault();

  //G4Region *ARegion = G4RegionStore::GetInstance()->GetRegion("SiRegion");
  //G4ProductionCuts* cuts = new G4ProductionCuts();
  //cuts->SetProductionCut(100*mm,G4ProductionCuts::GetIndex("GenericIon"));
  //cuts->SetProductionCut(100*mm,G4ProductionCuts::GetIndex("deuteron"));
  //cuts->SetProductionCut(100*mm,G4ProductionCuts::GetIndex("proton"));
  //cuts->SetProductionCut(100*mm,G4ProductionCuts::GetIndex("Si28"));
  //ARegion->SetProductionCuts(cuts);


  //G4VUserPhysicsList::DumpCutValuesTable();
}
  
void PhysicsList::SetEmPhysics(const G4String EmPhys)
{
  if(EmPhys=="standard") RegisterPhysics(new G4EmStandardPhysics());
  else if(EmPhys=="standardNR") RegisterPhysics(new PhysListEmStandardNR());
  else RegisterPhysics(new G4EmLowEPPhysics());

  /*
  G4EmConfigurator* em_config = G4LossTableManager::Instance()->EmConfigurator();
  G4VEmModel* mod;
  
  mod = new G4BraggIonModel();
  //mod = new G4BraggModel();
  //mod = new G4LindhardSorensenIonModel();
  //mod = new G4AtimaEnergyLossModel();
  //mod = new G4IonParametrisedLossModel();
  mod->SetActivationLowEnergyLimit(0*MeV);
  em_config->SetExtraEmModel("alpha","ionIoni",mod,"FoilRegion",0*MeV,80.0*MeV,new G4IonFluctuations());

  mod = new G4BetheBlochModel();
  mod->SetActivationLowEnergyLimit(0*MeV);
  em_config->SetExtraEmModel("alpha","ionIoni",mod,"FoilRegion",80.0*MeV,100*TeV,new G4IonFluctuations());
  */
}

void PhysicsList::SetHadrPhysFlag(const G4bool HadrPhysFlag)
{
  if(HadrPhysFlag) {
    RegisterPhysics( new G4HadronElasticPhysicsXS());
    RegisterPhysics( new HadronPhysicsList());
  }
}
