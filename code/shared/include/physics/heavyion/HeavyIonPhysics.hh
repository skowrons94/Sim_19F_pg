#ifndef HeavyIonPhysics_h
#define HeavyIonPhysics_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class G4HadronicInteraction;
class G4VCrossSectionDataSet;
class G4FTFBuilder;

class HeavyIonPhysics : public G4VPhysicsConstructor
{
public:

  HeavyIonPhysics(G4int ver = 0);
  HeavyIonPhysics(const G4String& nname, G4int ver = 0);
  ~HeavyIonPhysics() override;

  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type
  void ConstructParticle() override;
  void ConstructProcess() override;

private:

  virtual void AddProcess(const G4String&, G4ParticleDefinition*,
			  G4HadronicInteraction*, G4HadronicInteraction*, 
			  G4VCrossSectionDataSet*);

protected:

  G4int verbose;
};

#endif
