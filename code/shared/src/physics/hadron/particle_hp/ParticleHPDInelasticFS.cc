#include "ParticleHPDInelasticFS.hh"

#include "G4Deuteron.hh"
#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4IonTable.hh"

ParticleHPDInelasticFS::ParticleHPDInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPDInelasticFS_F24");
}

void ParticleHPDInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                    G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticCompFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 1;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 1;
    ResidualZ = Z;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A;
    ResidualZ = Z;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A + 1;
    ResidualZ = Z;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A + 1;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A + 2;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 10;
    ResidualZ = Z + 5;
  }

  ParticleHPInelasticCompFS::InitGammas(ResidualA, ResidualZ);
}

G4HadFinalState* ParticleHPDInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // do the final state
  ParticleHPInelasticCompFS::CompositeApply(theTrack, G4Deuteron::Deuteron());

  // return the result
  return theResult.Get();
}
