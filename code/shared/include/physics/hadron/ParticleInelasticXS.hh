#ifndef ParticleInelasticXS_h
#define ParticleInelasticXS_h 1

#include "G4VCrossSectionDataSet.hh"
#include "globals.hh"
#include "G4ElementData.hh"
#include "G4PhysicsVector.hh"
#include "G4Threading.hh"
#include <vector>

class G4DynamicParticle;
class G4ParticleDefinition;
class G4Element;
class G4VComponentCrossSection;

class ParticleInelasticXS final : public G4VCrossSectionDataSet
{
public: 

  explicit ParticleInelasticXS(const G4ParticleDefinition*);

  ~ParticleInelasticXS() override = default;

  G4bool IsElementApplicable(const G4DynamicParticle*, G4int Z,
			     const G4Material* mat = nullptr) final;

  G4bool IsIsoApplicable(const G4DynamicParticle*, G4int Z, G4int A,
			 const G4Element* elm = nullptr,
                         const G4Material* mat = nullptr) final;

  G4double GetElementCrossSection(const G4DynamicParticle*, G4int Z,
                                  const G4Material* mat = nullptr) final;

  G4double GetIsoCrossSection(const G4DynamicParticle*, G4int Z, G4int A,
                              const G4Isotope* iso = nullptr,
                              const G4Element* elm = nullptr,
                              const G4Material* mat = nullptr) final;

  const G4Isotope* SelectIsotope(const G4Element*, 
                                 G4double kinEnergy, G4double logE) final;

  void BuildPhysicsTable(const G4ParticleDefinition&) final;

  void CrossSectionDescription(std::ostream&) const final;

  G4double IsoCrossSection(G4double ekin, G4double logE, G4int Z, G4int A);

  ParticleInelasticXS & operator=
  (const ParticleInelasticXS &right) = delete;
  ParticleInelasticXS(const ParticleInelasticXS&) = delete;

private: 

  void Initialise(G4int Z);

  void InitialiseOnFly(G4int Z);

  const G4String& FindDirectoryPath();

  inline const G4PhysicsVector* GetPhysicsVector(G4int Z);

  G4PhysicsVector* RetrieveVector(std::ostringstream& in, G4bool warn);

  G4VComponentCrossSection* highEnergyXsection = nullptr;
  const G4ParticleDefinition* particle;

  std::vector<G4double> temp;

  G4int index = 0;
  G4bool isMaster = false;

  static const G4int MAXZINELP = 93;
  static G4ElementData* data[6];
  static G4double coeff[MAXZINELP][6];
  static G4String gDataDirectory[6];

#ifdef G4MULTITHREADED
  static G4Mutex particleInelasticXSMutex;
#endif
};

inline
const G4PhysicsVector* ParticleInelasticXS::GetPhysicsVector(G4int Z)
{
  const G4PhysicsVector* pv = data[index]->GetElementData(Z);
  if(pv == nullptr) { 
    InitialiseOnFly(Z);
    pv = data[index]->GetElementData(Z);
  }
  return pv;
}

#endif
