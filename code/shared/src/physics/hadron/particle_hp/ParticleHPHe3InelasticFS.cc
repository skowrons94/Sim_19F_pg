#include "ParticleHPHe3InelasticFS.hh"

#include "G4He3.hh"
#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4IonTable.hh"

ParticleHPHe3InelasticFS::ParticleHPHe3InelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPHe3InelasticFS_F26");
}

void ParticleHPHe3InelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                      G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticCompFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 2;
    ResidualZ = Z - 2;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 2;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A - 1;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A;
    ResidualZ = Z;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A + 1;
    ResidualZ = Z;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 9;
    ResidualZ = Z + 4;
  }

  ParticleHPInelasticCompFS::InitGammas(ResidualA, ResidualZ);
}

G4HadFinalState* ParticleHPHe3InelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // do the final state
  ParticleHPInelasticCompFS::CompositeApply(theTrack, G4He3::He3());

  // return the result
  return theResult.Get();
}
