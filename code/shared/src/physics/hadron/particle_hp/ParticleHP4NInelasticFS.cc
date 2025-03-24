#include "ParticleHP4NInelasticFS.hh"

#include "G4Alpha.hh"
#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4IonTable.hh"

ParticleHP4NInelasticFS::ParticleHP4NInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHP4NInelasticFS_F18");
}

G4HadFinalState* ParticleHP4NInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // these are the particle types in the final state

  G4ParticleDefinition* theDefs[4];
  theDefs[0] = G4Neutron::Neutron();
  theDefs[1] = G4Neutron::Neutron();
  theDefs[2] = G4Neutron::Neutron();
  theDefs[3] = G4Neutron::Neutron();

  // fill the final state
  ParticleHPInelasticBaseFS::BaseApply(theTrack, theDefs, 4);

  // return the result
  return theResult.Get();
}

void ParticleHP4NInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                     G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticBaseFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 3;
    ResidualZ = Z;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 3;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A - 2;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A - 1;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A - 1;
    ResidualZ = Z + 2;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A;
    ResidualZ = Z + 2;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 8;
    ResidualZ = Z + 6;
  }

  ParticleHPInelasticBaseFS::InitGammas(ResidualA, ResidualZ);
}
