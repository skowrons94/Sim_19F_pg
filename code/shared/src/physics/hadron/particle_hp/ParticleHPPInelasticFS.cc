#include "ParticleHPPInelasticFS.hh"

#include "G4Nucleus.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4Proton.hh"
#include "G4IonTable.hh"

ParticleHPPInelasticFS::ParticleHPPInelasticFS()
{
  secID = G4PhysicsModelCatalog::GetModelID("model_ParticleHPPInelasticFS_F23");
}

void ParticleHPPInelasticFS::Init(G4double A, G4double Z, G4int M, G4String& dirName,
                                    G4String& aFSType, G4ParticleDefinition* projectile)
{
  ParticleHPInelasticCompFS::Init(A, Z, M, dirName, aFSType, projectile);
  G4double ResidualA = 0;
  G4double ResidualZ = 0;
  if (projectile == G4Neutron::Neutron()) {
    ResidualA = A;
    ResidualZ = Z - 1;
  }
  else if (projectile == G4Proton::Proton()) {
    ResidualA = A;
    ResidualZ = Z;
  }
  else if (projectile == G4Deuteron::Deuteron()) {
    ResidualA = A + 1;
    ResidualZ = Z;
  }
  else if (projectile == G4Triton::Triton()) {
    ResidualA = A + 2;
    ResidualZ = Z;
  }
  else if (projectile == G4He3::He3()) {
    ResidualA = A + 2;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4Alpha::Alpha()) {
    ResidualA = A + 3;
    ResidualZ = Z + 1;
  }
  else if (projectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.)) {
    ResidualA = A + 11;
    ResidualZ = Z + 5;
  }

  ParticleHPInelasticCompFS::InitGammas(ResidualA, ResidualZ);
}

G4HadFinalState* ParticleHPPInelasticFS::ApplyYourself(const G4HadProjectile& theTrack)
{
  // do the final state
  ParticleHPInelasticCompFS::CompositeApply(theTrack, G4Proton::Proton());

  // return the result
  return theResult.Get();
}
