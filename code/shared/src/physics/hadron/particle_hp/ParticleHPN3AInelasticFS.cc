#include "ParticleHPN3AInelasticFS.hh"

#include "G4Alpha.hh"
#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4IonTable.hh"

ParticleHPN3AInelasticFS::ParticleHPN3AInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPN3AInelasticFS_F07");
}

G4HadFinalState* ParticleHPN3AInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // these are the particle types in the final state

  G4ParticleDefinition* theDefs[4];
  theDefs[0] = G4Neutron::Neutron();
  theDefs[1] = G4Alpha::Alpha();
  theDefs[2] = G4Alpha::Alpha();
  theDefs[3] = G4Alpha::Alpha();

  // fill the final state
  ParticleHPInelasticBaseFS::BaseApply(theTrack, theDefs, 4);

  // return the result
  return theResult.Get();
}

void ParticleHPN3AInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                      G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticBaseFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A - 12;
    ResidualZ = Z - 6;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A - 12;
    ResidualZ = Z - 5;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A - 11;
    ResidualZ = Z - 5;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A - 10;
    ResidualZ = Z - 5;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A - 10;
    ResidualZ = Z - 4;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A - 9;
    ResidualZ = Z - 4;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A - 1;
    ResidualZ = Z;
  }

  ParticleHPInelasticBaseFS::InitGammas(ResidualA, ResidualZ);
}
