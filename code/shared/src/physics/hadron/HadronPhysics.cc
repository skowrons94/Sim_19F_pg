#include "HadronPhysics.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4VCrossSectionDataSet.hh"
#include "G4HadronicProcessType.hh"
#include "G4HadronicProcessStore.hh"
#include "G4HadronInelasticProcess.hh"
#include "G4HadronElasticProcess.hh"
#include "G4NeutronCaptureProcess.hh"
#include "ParticleCaptureProcess.hh"
#include "G4NeutronFissionProcess.hh"
#include "G4Neutron.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4ProcessVector.hh"
#include "G4ProcessManager.hh"
#include "G4CrossSectionDataSetRegistry.hh"

G4ThreadLocal std::vector<G4VHadronModelBuilder*>* HadronPhysics::builders = nullptr;

HadronPhysics::HadronPhysics(const G4String& aName, G4int verb)
  : G4VPhysicsConstructor(aName)
{
  SetVerboseLevel(verb);
  if (verboseLevel>1) {
    G4cout << "### HadronPhysics: <" << aName << "> is created "
	   << G4endl;
  }
}

HadronPhysics::~HadronPhysics() 
{
  if ( builders ) {
    G4int n = builders->size();
    for(G4int i=0; i<n; ++i) {delete (*builders)[i];}
  }
  delete builders;
  builders = nullptr;
}

void HadronPhysics::ConstructParticle()
{
  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();
}

G4HadronicInteraction* 
HadronPhysics::BuildModel(G4VHadronModelBuilder* mBuilder,
			     G4double emin, 
			     G4double emax)
{
  if ( builders == 0 ) builders = new std::vector<G4VHadronModelBuilder*>;
  builders->push_back(mBuilder);                           
  G4HadronicInteraction* model = mBuilder->GetModel();
  model->SetMinEnergy(emin);
  model->SetMaxEnergy(emax);
  if (verboseLevel>1) {
    G4cout << "### HadronPhysics <" 
	   << model->GetModelName() << " Emin(GeV)= " 
	   << emin/GeV << "  Emax(GeV)= " << emax/GeV
	   << G4endl;
  }

  return model;
}

G4HadronicInteraction* 
HadronPhysics::NewModel(G4HadronicInteraction* model,
			   G4double emin, 
			   G4double emax)
{
  if(!model) return model;
  model->SetMinEnergy(emin);
  model->SetMaxEnergy(emax);
  if (verboseLevel>1) {
    G4cout << "### HadronPhysics <" 
	   << model->GetModelName() << " Emin(GeV)= " 
	   << emin/GeV << "  Emax(GeV)= " << emax/GeV
	   << G4endl;
  }
  return model;
}

void 
HadronPhysics::AddInelasticCrossSection(const G4String& pname, 
					   G4VCrossSectionDataSet* xsec)
{
  const G4ParticleDefinition* p =
    G4ParticleTable::GetParticleTable()->FindParticle(pname);
  if(!p) {
    G4cout << "### HadronPhysics WARNING: fails to find particle "
	   << pname << G4endl;
  } else {
    AddInelasticCrossSection(p, xsec);
  }
}
 
void 
HadronPhysics::AddInelasticCrossSection(const G4ParticleDefinition* p, 
					   G4VCrossSectionDataSet* xsec)
{
  if(!p) return;
  G4HadronicProcess* had = FindInelasticProcess(p);
  if(!had) return;
  had->AddDataSet(xsec);
  if (verboseLevel>1) {
    G4cout << "### HadronPhysics: the inelastic cross section " 
	   << " is added for " << p->GetParticleName() 
	   << G4endl;
  }
}

void 
HadronPhysics::AddElasticCrossSection(const G4String& pname, 
					   G4VCrossSectionDataSet* xsec)
{
  const G4ParticleDefinition* p =
    G4ParticleTable::GetParticleTable()->FindParticle(pname);
  if(!p) {
    G4cout << "### HadronPhysics WARNING: fails to find particle "
	   << pname << G4endl;
  } else {
    AddElasticCrossSection(p, xsec);
  }
}
 
void 
HadronPhysics::AddElasticCrossSection(const G4ParticleDefinition* p, 
					   G4VCrossSectionDataSet* xsec)
{
  if(!p) return;
  G4HadronicProcess* had = FindElasticProcess(p);
  if(!had) return;
  had->AddDataSet(xsec);
  if (verboseLevel>1) {
    G4cout << "### HadronPhysics: the inelastic cross section " 
	   << " is added for " << p->GetParticleName() 
	   << G4endl;
  }
}

void 
HadronPhysics::AddCaptureCrossSection(G4VCrossSectionDataSet* xsec)
{
  G4HadronicProcess* had = FindCaptureProcess();
  if(!had) return;
  had->AddDataSet(xsec);
  if (verboseLevel>1) {
    G4cout << "### HadronPhysics: the capture cross section " 
	   << " is added for neutron" 
	   << G4endl;
  }
}

void 
HadronPhysics::AddParticleCaptureCrossSection(const G4ParticleDefinition* p, 
					   G4VCrossSectionDataSet* xsec)
{
  if(!p) return;
  G4HadronicProcess* had = FindParticleCaptureProcess(p);
  if(!had) return;
  had->AddDataSet(xsec);
  if (verboseLevel>1) {
    G4cout << "### HadronPhysics: the capture cross section " 
	   << " is added for " << p->GetParticleName() 
	   << G4endl;
  }
}

void 
HadronPhysics::AddFissionCrossSection(G4VCrossSectionDataSet* xsec)
{
  G4HadronicProcess* had = FindFissionProcess();
  if(!had) return;
  had->AddDataSet(xsec);
  if (verboseLevel>1) {
    G4cout << "### HadronPhysics: the fission cross section " 
	   << " is added for neutron" 
	   << G4endl;
  }
}

G4CrossSectionInelastic* 
HadronPhysics::InelasticXS(const G4String& cName)
{
  G4VComponentCrossSection* component =
    G4CrossSectionDataSetRegistry::Instance()->GetComponentCrossSection(cName);
  G4CrossSectionInelastic* ptr = (component) 
    ? new G4CrossSectionInelastic(component) : nullptr;
  return ptr;
}

G4HadronicProcess* 
HadronPhysics::FindInelasticProcess(const G4String& pname)
{
  G4HadronicProcess* had = nullptr;
  const G4ParticleDefinition* p =
    G4ParticleTable::GetParticleTable()->FindParticle(pname);
  if(!p) {
    G4cout << "### HadronPhysics WARNING: fails to find particle "
	   << pname << G4endl;
    return had;
  }
  return FindInelasticProcess(p);
}

G4HadronicProcess* 
HadronPhysics::FindInelasticProcess(const G4ParticleDefinition* p)
{
  G4HadronicProcess* had = nullptr;
  if(!p) return had;
  G4ProcessManager* pmanager = p->GetProcessManager();
  G4ProcessVector*  pv = pmanager->GetProcessList();
  size_t n = pv->size();
  if(0 < n) {
    for(size_t i=0; i<n; ++i) {
      if(fHadronInelastic == ((*pv)[i])->GetProcessSubType()) {
	had = static_cast<G4HadronicProcess*>((*pv)[i]);
	return had;
      }
    }
  }
  G4ParticleDefinition* part = const_cast<G4ParticleDefinition*>(p);
  //G4cout << "### HadronPhysics particle: " << part->GetParticleName() << G4endl;
  had = new G4HadronInelasticProcess(part->GetParticleName()+"Inelastic",part);
  pmanager->AddDiscreteProcess(had);
  return had;
}

G4HadronicProcess* 
HadronPhysics::FindElasticProcess(const G4String& pname)
{
  G4HadronicProcess* had = nullptr;
  const G4ParticleDefinition* p =
    G4ParticleTable::GetParticleTable()->FindParticle(pname);
  if(!p) {
    G4cout << "### HadronPhysics WARNING: fails to find particle "
	   << pname << G4endl;
    return had;
  }
  return FindElasticProcess(p);
}

G4HadronicProcess* 
HadronPhysics::FindElasticProcess(const G4ParticleDefinition* p)
{
  G4HadronicProcess* had = nullptr;
  if(!p) return had;
  G4ProcessManager* pmanager = p->GetProcessManager();
  G4ProcessVector*  pv = pmanager->GetProcessList();
  size_t n = pv->size();
  if(0 < n) {
    for(size_t i=0; i<n; ++i) {
      if(fHadronElastic == ((*pv)[i])->GetProcessSubType()) {
	had = static_cast<G4HadronicProcess*>((*pv)[i]);
	return had;
      }
    }
  }
  had = new G4HadronElasticProcess("hElastic");
  pmanager->AddDiscreteProcess(had);
  return had;
}

G4HadronicProcess* HadronPhysics::FindCaptureProcess()
{
  G4HadronicProcess* had = nullptr;
  G4ProcessManager* pmanager = 
    G4Neutron::Neutron()->GetProcessManager();
  G4ProcessVector*  pv = pmanager->GetProcessList();
  size_t n = pv->size();
  if(0 < n) {
    for(size_t i=0; i<n; ++i) {
      if(fCapture == ((*pv)[i])->GetProcessSubType()) {
	had = static_cast<G4HadronicProcess*>((*pv)[i]);
	return had;
      }
    }
  }
  had = new G4NeutronCaptureProcess("nCapture");
  pmanager->AddDiscreteProcess(had);
  return had;
}

G4HadronicProcess* 
HadronPhysics::FindParticleCaptureProcess(const G4ParticleDefinition* p)
{
  G4HadronicProcess* had = nullptr;
  if(!p) return had;
  G4ProcessManager* pmanager = p->GetProcessManager();
  G4ProcessVector*  pv = pmanager->GetProcessList();
  size_t n = pv->size();
  if(0 < n) {
    for(size_t i=0; i<n; ++i) {
      if(fCapture == ((*pv)[i])->GetProcessSubType()) {
	had = static_cast<G4HadronicProcess*>((*pv)[i]);
	return had;
      }
    }
  }
  G4ParticleDefinition* part = const_cast<G4ParticleDefinition*>(p);
  //had = new ParticleCaptureProcess(part->GetParticleName()+"Capture",part);
  had = new ParticleCaptureProcess(part->GetParticleName()+"Capture");
  pmanager->AddDiscreteProcess(had);
  return had;
}

G4HadronicProcess* HadronPhysics::FindFissionProcess()
{
  G4HadronicProcess* had = nullptr;
  G4ProcessManager* pmanager = 
    G4Neutron::Neutron()->GetProcessManager();
  G4ProcessVector*  pv = pmanager->GetProcessList();
  size_t n = pv->size();
  if(0 < n) {
    for(size_t i=0; i<n; ++i) {
      if(fFission == ((*pv)[i])->GetProcessSubType()) {
	had = static_cast<G4HadronicProcess*>((*pv)[i]);
	return had;
      }
    }
  }
  had = new G4NeutronFissionProcess("nFission");
  pmanager->AddDiscreteProcess(had);
  return had;
}

