#ifndef HadronPhysics_h
#define HadronPhysics_h 1

#include "G4VPhysicsConstructor.hh"
#include "G4VHadronModelBuilder.hh"
#include "G4CrossSectionInelastic.hh"
#include "globals.hh"
#include <vector>

class G4ParticleDefinition;
class G4VCrossSectionDataSet;
class G4HadronicProcess;
class G4HadronicInteraction;

class HadronPhysics : public G4VPhysicsConstructor
{
public: 

  HadronPhysics(const G4String& name ="hInelastic", 
		   G4int verbose = 0);

  virtual ~HadronPhysics();

  virtual void ConstructParticle();

  G4HadronicInteraction* BuildModel(G4VHadronModelBuilder*,
				    G4double emin, 
				    G4double emax);

  G4HadronicInteraction* NewModel(G4HadronicInteraction*,
				  G4double emin, 
				  G4double emax);

  void AddInelasticCrossSection(const G4String&, 
				G4VCrossSectionDataSet*);

  void AddInelasticCrossSection(const G4ParticleDefinition*, 
				G4VCrossSectionDataSet*);

  void AddElasticCrossSection(const G4String&, 
			      G4VCrossSectionDataSet*);

  void AddElasticCrossSection(const G4ParticleDefinition*, 
			      G4VCrossSectionDataSet*);

  void AddCaptureCrossSection(G4VCrossSectionDataSet*);

  void AddParticleCaptureCrossSection(const G4ParticleDefinition*, 
				G4VCrossSectionDataSet*);

  void AddFissionCrossSection(G4VCrossSectionDataSet*);

  G4CrossSectionInelastic* InelasticXS(const G4String& componentName);

protected:

  G4HadronicProcess* FindInelasticProcess(const G4String&);

  G4HadronicProcess* FindInelasticProcess(const G4ParticleDefinition*);

  G4HadronicProcess* FindElasticProcess(const G4String&);

  G4HadronicProcess* FindElasticProcess(const G4ParticleDefinition*);

  G4HadronicProcess* FindCaptureProcess();

  G4HadronicProcess* FindParticleCaptureProcess(const G4ParticleDefinition*);

  G4HadronicProcess* FindFissionProcess();

private:

  // copy constructor and hide assignment operator
  HadronPhysics(HadronPhysics &);
  HadronPhysics & operator=(const HadronPhysics &right);

  static G4ThreadLocal std::vector<G4VHadronModelBuilder*>* builders;
};

#endif
