#include "ParticleHP2AInelasticFS.hh"

#include "G4Alpha.hh"
#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4IonTable.hh"

ParticleHP2AInelasticFS::ParticleHP2AInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHP2AInelasticFS_F28");
}

G4HadFinalState* ParticleHP2AInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // these are the particle types in the final state

  G4ParticleDefinition* theDefs[2];
  theDefs[0] = G4Alpha::Alpha();
  theDefs[1] = G4Alpha::Alpha();

  // fill the final state
  ParticleHPInelasticBaseFS::BaseApply(theTrack, theDefs, 2);

  // return the result
  return theResult.Get();
}

void ParticleHP2AInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                     G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticBaseFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 7;
    ResidualZ = Z - 4;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 7;
    ResidualZ = Z - 3;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A - 6;
    ResidualZ = Z - 3;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A - 5;
    ResidualZ = Z - 3;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A - 5;
    ResidualZ = Z - 2;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A - 4;
    ResidualZ = Z - 2;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 4;
    ResidualZ = Z + 2;
  }

  ParticleHPInelasticBaseFS::InitGammas(ResidualA, ResidualZ);
}
