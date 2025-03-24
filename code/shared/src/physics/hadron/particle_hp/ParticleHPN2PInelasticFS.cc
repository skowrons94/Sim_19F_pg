#include "ParticleHPN2PInelasticFS.hh"

#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4Proton.hh"
#include "G4IonTable.hh"

ParticleHPN2PInelasticFS::ParticleHPN2PInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPN2PInelasticFS_F21");
}

G4HadFinalState* ParticleHPN2PInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // these are the particle types in the final state

  G4ParticleDefinition* theDefs[3];
  theDefs[0] = G4Neutron::Neutron();
  theDefs[1] = G4Proton::Proton();
  theDefs[2] = G4Proton::Proton();

  // fill the final state
  ParticleHPInelasticBaseFS::BaseApply(theTrack, theDefs, 3);

  // return the result
  return theResult.Get();
}

void ParticleHPN2PInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                      G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticBaseFS::Init(A, Z, M, dirName, aFSType, projectile);
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

  ParticleHPInelasticBaseFS::InitGammas(ResidualA, ResidualZ);
}
