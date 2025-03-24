#include "ParticleHPAInelasticFS.hh"

#include "G4Alpha.hh"
#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4IonTable.hh"

ParticleHPAInelasticFS::ParticleHPAInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPAInelasticFS_F27");
}

void ParticleHPAInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                    G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticCompFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 3;
    ResidualZ = Z - 2;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 3;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A - 2;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A - 1;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A - 1;
    ResidualZ = Z;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A;
    ResidualZ = Z;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 8;
    ResidualZ = Z + 4;
  }

  ParticleHPInelasticCompFS::InitGammas(ResidualA, ResidualZ);
}

G4HadFinalState* ParticleHPAInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // do the final state
  ParticleHPInelasticCompFS::CompositeApply(theTrack, G4Alpha::Alpha());

  // return the result
  return theResult.Get();
}
