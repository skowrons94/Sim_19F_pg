#ifndef ParticleResRadCapture_h
#define ParticleResRadCapture_h 1
 
#include "globals.hh"
#include "G4HadronicInteraction.hh"
#include "G4HadProjectile.hh"
#include "G4Nucleus.hh"
#include "G4LorentzVector.hh"

class G4VEvaporationChannel;
class G4IonTable;

class ParticleResRadCapture : public G4HadronicInteraction
{
public:

  explicit ParticleResRadCapture();

  virtual ~ParticleResRadCapture();
 
  virtual G4HadFinalState* ApplyYourself(const G4HadProjectile & aTrack, 
					 G4Nucleus & targetNucleus) final;

  virtual void InitialiseModel() final;

private:

  ParticleResRadCapture & operator=(const ParticleResRadCapture &right) = delete;
  ParticleResRadCapture(const ParticleResRadCapture&) = delete;

  G4int icID;   // creator model ID for electrons produced by internal conversion
  G4int secID;  // creator model ID for the other secondaries produced by this model
  const G4ParticleDefinition* electron;
  G4double lowestEnergyLimit;
  G4double minExcitation;
  G4VEvaporationChannel* photonEvaporation;
  G4IonTable*  theTableOfIons;
  G4LorentzVector lab4mom;

};

#endif
