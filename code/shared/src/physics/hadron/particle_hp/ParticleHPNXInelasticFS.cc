#include "ParticleHPNXInelasticFS.hh"

#include "G4Alpha.hh"
#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4IonTable.hh"

ParticleHPNXInelasticFS::ParticleHPNXInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPNXInelasticFS_F02");
}

G4HadFinalState* ParticleHPNXInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // these are the particle types in the final state

  G4ParticleDefinition* theDefs[2];
  theDefs[0] = G4Neutron::Neutron();

  // fill the final state
  ParticleHPInelasticBaseFS::BaseApply(theTrack, theDefs, 1);

  // return the result
  return theResult.Get();
}

void ParticleHPNXInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                     G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticBaseFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 5;
    ResidualZ = Z - 2;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 5;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A - 4;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A - 3;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A - 3;
    ResidualZ = Z;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A - 2;
    ResidualZ = Z;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 6;
    ResidualZ = Z + 4;
  }

  //   G4double ResidualA = A-5; // wrong, to be improves @@@
  //   G4double ResidualZ = Z-2; // dito @@@
  ParticleHPInelasticBaseFS::InitGammas(ResidualA, ResidualZ);
}
