#include "HeavyIonPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4hMultipleScattering.hh"
#include "G4ionIonisation.hh"
#include "G4NuclearStopping.hh"
#include "G4Radioactivation.hh"
#include "G4NuclearLevelData.hh"

#include "IonC12.hh"

#include "G4HadronInelasticProcess.hh"
#include "G4BinaryLightIonReaction.hh"
#include "G4ComponentGGNuclNuclXsc.hh"
#include "G4CrossSectionInelastic.hh"

#include "G4PreCompoundModel.hh"
#include "G4ExcitationHandler.hh"
#include "G4FTFBuilder.hh"
#include "G4HadronicInteraction.hh"
#include "G4BuilderType.hh"
#include "G4HadronicInteractionRegistry.hh"

#include "G4HadronicParameters.hh"
#include "G4HadronElasticProcess.hh"
#include "G4HadProcesses.hh"
#include "G4HadronElastic.hh"

using namespace std;

// factory
#include "G4PhysicsConstructorFactory.hh"
//
G4_DECLARE_PHYSCONSTR_FACTORY(HeavyIonPhysics);

HeavyIonPhysics::HeavyIonPhysics(G4int ver)
  : HeavyIonPhysics("HeavyIonPhysics", ver)
{}

HeavyIonPhysics::HeavyIonPhysics(const G4String& nname, G4int ver)
  : G4VPhysicsConstructor(nname),verbose(ver)
{
  SetPhysicsType(bIons);
  if(verbose > 1) { G4cout << "### HeavyIonPhysics: " << nname << G4endl; }
}

HeavyIonPhysics::~HeavyIonPhysics()
{}

void HeavyIonPhysics::ConstructParticle()
{
  //  Construct heavy ions
  IonC12::theIonC12();
}

void HeavyIonPhysics::ConstructProcess()
{
  // electromagnetic
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  ph->RegisterProcess(new G4hMultipleScattering(), IonC12::theIonC12());
  ph->RegisterProcess(new G4ionIonisation(), IonC12::theIonC12());
  ph->RegisterProcess(new G4NuclearStopping(), IonC12::theIonC12());
  
  // Elastic
  G4HadronicParameters* param = G4HadronicParameters::Instance();
  G4bool useFactorXS = param->ApplyFactorXS();
  //G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  G4HadronElasticProcess* hel = new G4HadronElasticProcess();
  auto xsNN = G4HadProcesses::ElasticXS("Glauber-Gribov Nucl-nucl");
  G4HadronElastic* lhep0 = new G4HadronElastic();
  hel = new G4HadronElasticProcess();
  hel->AddDataSet(xsNN);
  hel->RegisterMe(lhep0);
  if( useFactorXS ) hel->MultiplyCrossSectionBy( param->XSFactorHadronElastic() );
  ph->RegisterProcess(hel,IonC12::theIonC12());

  // Radioactive decay
  //G4NuclearLevelData::GetInstance()->GetParameters()->SetMaxLifeTime(100*ps);
  //ph->RegisterProcess(new G4Radioactivation(), IonC12::theIonC12());
}

void HeavyIonPhysics::AddProcess(const G4String& name, 
			      G4ParticleDefinition* part,
			      G4HadronicInteraction* theIonBC,
			      G4HadronicInteraction* theFTFP,
			      G4VCrossSectionDataSet* xs)
{
  G4HadronInelasticProcess* hadi = new G4HadronInelasticProcess(name, part);
  G4ProcessManager* pManager = part->GetProcessManager();
  pManager->AddDiscreteProcess(hadi);
    
  hadi->AddDataSet(xs);
    
  hadi->RegisterMe(theIonBC);
  if(theFTFP) { hadi->RegisterMe(theFTFP); }
}
