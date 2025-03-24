#include "ParticleHPND2AInelasticFS.hh"

#include "G4Alpha.hh"
#include "G4Deuteron.hh"
#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4IonTable.hh"

ParticleHPND2AInelasticFS::ParticleHPND2AInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPND2AInelasticFS_F16");
}

G4HadFinalState* ParticleHPND2AInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // these are the particle types in the final state

  G4ParticleDefinition* theDefs[4];
  theDefs[0] = G4Neutron::Neutron();
  theDefs[1] = G4Deuteron::Deuteron();
  theDefs[2] = G4Alpha::Alpha();
  theDefs[3] = G4Alpha::Alpha();

  // fill the final state
  ParticleHPInelasticBaseFS::BaseApply(theTrack, theDefs, 4);

  // return the result
  return theResult.Get();
}

void ParticleHPND2AInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                       G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticBaseFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 10;
    ResidualZ = Z - 5;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 10;
    ResidualZ = Z - 4;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A - 9;
    ResidualZ = Z - 4;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A - 8;
    ResidualZ = Z - 4;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A - 8;
    ResidualZ = Z - 3;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A - 7;
    ResidualZ = Z - 3;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 1;
    ResidualZ = Z + 1;
  }

  ParticleHPInelasticBaseFS::InitGammas(ResidualA, ResidualZ);
}
