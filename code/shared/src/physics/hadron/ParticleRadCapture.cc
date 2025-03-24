#include "ParticleRadCapture.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4Fragment.hh"
#include "G4FragmentVector.hh"
#include "G4NucleiProperties.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4Electron.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "G4RandomDirection.hh"
#include "G4HadronicParameters.hh"
#include "G4PhysicsModelCatalog.hh"
#include "G4DeexPrecoParameters.hh"
#include "G4NuclearLevelData.hh"
#include "G4LevelManager.hh"

ParticleRadCapture::ParticleRadCapture() 
  : G4HadronicInteraction("particleRadCapture"),lab4mom(0.,0.,0.,0.)
{
  verboseLevel = 1;
  lowestEnergyLimit = 10*CLHEP::eV;
  minExcitation = 0.1*CLHEP::keV;
  SetMinEnergy( 0.0*CLHEP::GeV );
  SetMaxEnergy( G4HadronicParameters::Instance()->GetMaxEnergy() );
  
  electron = G4Electron::Electron();
  icID = -1;
  secID = -1;
  theTableOfIons = G4ParticleTable::GetParticleTable()->GetIonTable();
}

ParticleRadCapture::~ParticleRadCapture()
{
}

void ParticleRadCapture::InitialiseModel()
{
  G4DeexPrecoParameters* param = 
    G4NuclearLevelData::GetInstance()->GetParameters();
  minExcitation = param->GetMinExcitation();
  icID =  G4PhysicsModelCatalog::GetModelID("model_e-InternalConversion");
  secID = G4PhysicsModelCatalog::GetModelID("model_" + GetModelName());

  //out.open("CaptureGammas.txt");
}

G4HadFinalState* ParticleRadCapture::ApplyYourself(const G4HadProjectile& aTrack, G4Nucleus& theNucleus)
{
  theParticleChange.Clear();
  theParticleChange.SetStatusChange(stopAndKill);
  
  G4int A = theNucleus.GetA_asInt();
  G4int Z = theNucleus.GetZ_asInt();
  
  G4double time = aTrack.GetGlobalTime();
  
  // Create initial state
  
  lab4mom.set(0.,0.,0.,G4NucleiProperties::GetNuclearMass(A, Z));
  //G4cout << "lab4mom(target): " << lab4mom << G4endl;
  //G4cout << "projectile mass: " << aTrack.Get4Momentum().m() << G4endl;
  lab4mom += aTrack.Get4Momentum();
  //G4cout << "lab4mom(target+projectile): " << lab4mom << G4endl;
  
  G4double M  = lab4mom.mag();
  A = A + aTrack.GetDefinition()->GetAtomicMass();
  Z = Z + aTrack.GetDefinition()->GetAtomicNumber();
  G4double mass = G4NucleiProperties::GetNuclearMass(A, Z);
  /*
  G4cout << "Projectile: " << aTrack.GetDefinition()->GetParticleName()
	 << " A: " << aTrack.GetDefinition()->GetAtomicMass()
	 << " Z: " << aTrack.GetDefinition()->GetAtomicNumber() << G4endl;
  
  G4cout << "Capture start: Z= " << Z << " A= " << A 
	 << " LabM= " << M << " Mcompound= " << mass << G4endl;
  */
  
  G4ThreeVector bst = lab4mom.boostVector();
  
  if(M - mass <= lowestEnergyLimit) {
    return &theParticleChange;
  }
  
  if (verboseLevel > 1) {
    G4cout << "ParticleRadCapture::DoIt: Eini(MeV)=" 
	   << aTrack.GetKineticEnergy()/MeV << "  Eexc(MeV)= " 
	   << (M - mass)/MeV 
	   << "  Z= " << Z << "  A= " << A << G4endl;
  }

  //G4cout << G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV)
  //	 <<  "  " << G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelEnergy((M - mass)/MeV) << G4endl;
  std::vector<G4double> StateToCapture(G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV)+1);
  std::vector<G4double> Pop(G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV)+1);
  std::vector<G4double> A1perA0(G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV)+1);
  std::vector<G4double> A2perA0(G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV)+1);
  std::vector<G4double> A3perA0(G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV)+1);
  std::vector<G4double> A4perA0(G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV)+1);
  G4int temp;
  G4double CumPop = 0;

  char* directory = std::getenv("G4RADIATIVECAPTURE");
  std::ostringstream ss;
  ss << directory << "/" << aTrack.GetDefinition()->GetParticleName() << "/z" << Z << ".a" << A;
  std::ifstream in(ss.str());

  for(int i=0;i<=G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV);i++) {
    in >> temp >> Pop[i] >> A1perA0[i] >> A2perA0[i] >> A3perA0[i] >> A4perA0[i];
    CumPop += Pop[i];
    StateToCapture[i] = G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->LevelEnergy(i);
  }
  for(int i=0;i<=G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV);i++) {
    Pop[i] /= CumPop;
  }

  G4double NormCumPop = 0;
  G4int index = 0;
  G4double randomN = G4UniformRand();
  for(int i=0;i<=G4NuclearLevelData::GetInstance()->GetLevelManager(Z,A)->NearestLowEdgeLevelIndex((M - mass)/MeV);i++) {
    NormCumPop += Pop[i];
    if(randomN<NormCumPop) {
      index = i;
      break;
    }
  }

  G4double ChosenStateToCapture = StateToCapture[index];

  G4double cosThetacm;
 RandcosThetacm:
  G4double cosThetacmInit = 2 * G4UniformRand() - 1;
  G4double cosThetacmU = 2*G4UniformRand();
  G4double pol1 = A1perA0[index]*cosThetacmInit;
  G4double pol2 = A2perA0[index]*0.5*(3*cosThetacmInit*cosThetacmInit-1);
  G4double pol3 = A3perA0[index]*0.5*(5*cosThetacmInit*cosThetacmInit*cosThetacmInit-3*cosThetacmInit);
  G4double pol4 = A4perA0[index]*0.125*(35*cosThetacmInit*cosThetacmInit*cosThetacmInit*cosThetacmInit-30*cosThetacmInit*cosThetacmInit+3);
  G4double Dist = 1+pol1+pol2+pol3+pol4;
  if(cosThetacmU < Dist) {
    cosThetacm = cosThetacmInit;
  }
  else goto RandcosThetacm;

  G4double Thetacm = acos(cosThetacm)*rad;
  G4double Phicm = CLHEP::twopi*G4UniformRand();
  G4ThreeVector gammadirection(sin(Thetacm)*cos(Phicm),sin(Thetacm)*sin(Phicm),cos(Thetacm));
  //G4cout << "ParticleRadCapture::Thetacm  " << Thetacm << G4endl;

  G4double e1 = (M - mass)*(M + mass)/(2*M) - ChosenStateToCapture;
  //G4cout << e1 << G4endl;
  G4LorentzVector lv2(e1*gammadirection.unit(),e1);
  lv2.boost(bst);
  G4HadSecondary* news = 
    new G4HadSecondary(new G4DynamicParticle(G4Gamma::Gamma(), lv2));
  news->SetTime(time);
  theParticleChange.AddSecondary(*news);
  delete news;
  /*
  G4cout << " --- ParticleRadCapture --- " << G4endl;
  G4cout << "cm energy: " << e1/keV << " cm theta: " << gammadirection.theta()/deg << G4endl;
  G4cout << "lab energy: " << lv2.e()/keV << " lab theta: " << lv2.theta()/deg << G4endl;
  */
  //out << (e1*gammadirection.unit()).theta()/deg << "\t" << (sqrt((e1*gammadirection.unit()).mag2()+G4Gamma::Gamma()->GetPDGMass()*G4Gamma::Gamma()->GetPDGMass())-G4Gamma::Gamma()->GetPDGMass())/keV << G4endl;;

  const G4ParticleDefinition* theDef = 0;
  
  lab4mom -= lv2; 
  theDef = theTableOfIons->GetIon(Z,A,ChosenStateToCapture,noFloat,0);
  
  if (verboseLevel > 1) {
    G4cout << "Gamma 4-mom: " << lv2 << "   " 
	   << theDef->GetParticleName() << "   " << lab4mom << G4endl;
  }
  if(theDef) {
    news = new G4HadSecondary(new G4DynamicParticle(theDef, lab4mom));
    news->SetTime(time);
    theParticleChange.AddSecondary(*news);
    delete news;
  }
  
  
  //G4cout << "Capture done" << G4endl;
  return &theParticleChange;
}

