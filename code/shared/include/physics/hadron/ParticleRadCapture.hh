#ifndef ParticleRadCapture_h
#define ParticleRadCapture_h 1
 
#include "globals.hh"
#include "G4HadronicInteraction.hh"
#include "G4HadProjectile.hh"
#include "G4Nucleus.hh"
#include "G4LorentzVector.hh"

class G4VEvaporationChannel;
class G4IonTable;

class ParticleRadCapture : public G4HadronicInteraction
{
public:

  explicit ParticleRadCapture();

  virtual ~ParticleRadCapture();
 
  virtual G4HadFinalState* ApplyYourself(const G4HadProjectile & aTrack, 
					 G4Nucleus & targetNucleus) final;

  virtual void InitialiseModel() final;

private:

  ParticleRadCapture & operator=(const ParticleRadCapture &right) = delete;
  ParticleRadCapture(const ParticleRadCapture&) = delete;

  G4int icID;   // creator model ID for electrons produced by internal conversion
  G4int secID;  // creator model ID for the other secondaries produced by this model
  const G4ParticleDefinition* electron;
  G4double lowestEnergyLimit;
  G4double minExcitation;
  G4VEvaporationChannel* photonEvaporation;
  G4IonTable*  theTableOfIons;
  G4LorentzVector lab4mom;
  std::ofstream out;
};

#endif
