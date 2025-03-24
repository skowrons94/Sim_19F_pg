#include "ParticleHPTInelasticFS.hh"

#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4Triton.hh"
#include "G4IonTable.hh"

ParticleHPTInelasticFS::ParticleHPTInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPTInelasticFS_F25");
}

void ParticleHPTInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                    G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticCompFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 2;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 2;
    ResidualZ = Z;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A - 1;
    ResidualZ = Z;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A;
    ResidualZ = Z;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A + 1;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 9;
    ResidualZ = Z + 5;
  }

  ParticleHPInelasticCompFS::InitGammas(ResidualA, ResidualZ);
}

G4HadFinalState* ParticleHPTInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // do the final state
  ParticleHPInelasticCompFS::CompositeApply(theTrack, G4Triton::Triton());

  // return the result
  return theResult.Get();
}
