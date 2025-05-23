#include "ParticleResRadCapture.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4Fragment.hh"
#include "G4FragmentVector.hh"
#include "G4NucleiProperties.hh"
#include "G4VEvaporationChannel.hh"
#include "G4PhotonEvaporation.hh"
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

ParticleResRadCapture::ParticleResRadCapture() 
  : G4HadronicInteraction("particleResRadCapture"),
    photonEvaporation(nullptr),lab4mom(0.,0.,0.,0.)
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

ParticleResRadCapture::~ParticleResRadCapture()
{
  delete photonEvaporation;
}

void ParticleResRadCapture::InitialiseModel()
{
  if(photonEvaporation != nullptr) { return; }
  G4DeexPrecoParameters* param = 
    G4NuclearLevelData::GetInstance()->GetParameters();
  minExcitation = param->GetMinExcitation();
  icID =  G4PhysicsModelCatalog::GetModelID("model_e-InternalConversion");
  secID = G4PhysicsModelCatalog::GetModelID("model_" + GetModelName());

  photonEvaporation = new G4PhotonEvaporation();
  photonEvaporation->Initialise();
  photonEvaporation->SetICM(true);
}

G4HadFinalState* ParticleResRadCapture::ApplyYourself(
		 const G4HadProjectile& aTrack, G4Nucleus& theNucleus)
{
  theParticleChange.Clear();
  theParticleChange.SetStatusChange(stopAndKill);

  G4int A = theNucleus.GetA_asInt();
  G4int Z = theNucleus.GetZ_asInt();

  G4double time = aTrack.GetGlobalTime();

  // Create initial state
  //G4double mass_target = G4NucleiProperties::GetAtomicMass(A, Z);
  G4double mass_target = G4NucleiProperties::GetNuclearMass(A, Z);
  if (verboseLevel > 1) {
    G4cout << " Target: " << A << "  " << Z << "  " << mass_target << G4endl;
  }
  lab4mom.set(0.,0.,0.,G4NucleiProperties::GetNuclearMass(A, Z));
  //lab4mom.set(0.,0.,0.,G4NucleiProperties::GetAtomicMass(A, Z));
  lab4mom += aTrack.Get4Momentum();

  G4double M  = lab4mom.mag();
  A = A + aTrack.GetDefinition()->GetAtomicMass();
  Z = Z + aTrack.GetDefinition()->GetAtomicNumber();
  G4double mass = G4NucleiProperties::GetNuclearMass(A, Z);
  //G4double mass = G4NucleiProperties::GetAtomicMass(A, Z);

  if (verboseLevel > 1) {
    G4cout << "Projectile: " << aTrack.GetDefinition()->GetParticleName()
	   << " A (proj): " << aTrack.GetDefinition()->GetAtomicMass()
	   << " Z (proj): " << aTrack.GetDefinition()->GetAtomicNumber()
	   << " KinE (proj): " << aTrack.GetKineticEnergy()
	   << " Mass(proj): " << aTrack.GetDefinition()->GetPDGMass()
	   << " TotE (proj): " << aTrack.GetTotalEnergy()
	   << " A (final nucleus: " << A
	   << " Z (final nucleus): " << Z
	   << " mass (final nucleus): " << mass
	   << " M (compound): " << M
	   << " Eexc: " << M-mass
	   << " closest level: " << G4NuclearLevelData::GetInstance()->GetLevelEnergy(Z,A,M-mass)
	   << G4endl;
    
    G4cout << "Capture start: Z= " << Z << " A= " << A 
	   << " LabM= " << M << " Mcompound= " << mass << G4endl;
  }

  // simplified method of 1 gamma emission
  if(A <= 4) {

    G4ThreeVector bst = lab4mom.boostVector();

    if(M - mass <= lowestEnergyLimit) {
      return &theParticleChange;
    }
 
    if (verboseLevel > 1) {
      G4cout << "ParticleResRadCapture::DoIt: Eini(MeV)=" 
	     << aTrack.GetKineticEnergy()/MeV << "  Eexc(MeV)= " 
	     << (M - mass)/MeV 
	     << "  Z= " << Z << "  A= " << A << G4endl;
    }
    G4double e1 = (M - mass)*(M + mass)/(2*M);
    G4LorentzVector lv2(e1*G4RandomDirection(),e1);
    lv2.boost(bst);
    G4HadSecondary* news = 
      new G4HadSecondary(new G4DynamicParticle(G4Gamma::Gamma(), lv2));
    news->SetTime(time);
    theParticleChange.AddSecondary(*news);
    delete news;

    const G4ParticleDefinition* theDef = 0;

    lab4mom -= lv2; 
    if      (Z == 1 && A == 2) {theDef = G4Deuteron::Deuteron();}
    else if (Z == 1 && A == 3) {theDef = G4Triton::Triton();}
    else if (Z == 2 && A == 3) {theDef = G4He3::He3();}
    else if (Z == 2 && A == 4) {theDef = G4Alpha::Alpha();}
    else {  theDef = theTableOfIons->GetIon(Z,A,0.0,noFloat,0); }

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
 
  // Use photon evaporation  
  } 

  else {
 
    // protection against wrong kinematic 
    if(M < mass) {
      G4double etot = std::max(mass, lab4mom.e());
      G4double ptot = std::sqrt((etot - mass)*(etot + mass));
      G4ThreeVector v = lab4mom.vect().unit();
      lab4mom.set(v.x()*ptot,v.y()*ptot,v.z()*ptot,etot);
    }

    G4double ekin = (lab4mom.gamma()-1)*lab4mom.m();
    //G4double ekin = std::max(0.0,lab4mom.e() - mass);
    
    G4Fragment* aFragment = new G4Fragment(A, Z, lab4mom);

    if (verboseLevel > 1) {
      G4cout << "ParticleResRadCapture::ApplyYourself initial G4Fragment:" 
	     << G4endl;
      G4cout << lab4mom.e() << G4endl;
      G4cout << " ExcE: " << aFragment->GetExcitationEnergy() << " ekin: " << ekin << G4endl;
    }

    const G4ParticleDefinition* theDef;
    if(fabs(aFragment->GetExcitationEnergy() - G4NuclearLevelData::GetInstance()->GetLevelEnergy(Z,A,M-mass))<0.01) {
      if (verboseLevel > 1) G4cout << " Resonance !! " << G4endl;
      theDef = theTableOfIons->GetIon(Z, A, G4NuclearLevelData::GetInstance()->GetLevelEnergy(Z,A,M-mass), noFloat, 0);
      G4HadSecondary* news = new G4HadSecondary(
						new G4DynamicParticle(theDef,
								      aFragment->GetMomentum().vect().unit(),
								      ekin));
      G4double timeF = aFragment->GetCreationTime();
      if(timeF < 0.0) { timeF = 0.0; }
      news->SetTime(time + timeF);
      if(theDef == electron) { 
        news->SetCreatorModelID(icID); 
      } else {
        news->SetCreatorModelID(secID);
      }
      theParticleChange.AddSecondary(*news);
      delete news;
    }
    else {
      G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
      theDef = particleTable->FindParticle("geantino");
      G4HadSecondary* news = new G4HadSecondary(
						new G4DynamicParticle(theDef,
								      aFragment->GetMomentum().vect().unit(),
								      lab4mom.e()));
      G4double timeF = aFragment->GetCreationTime();
      if(timeF < 0.0) { timeF = 0.0; }
      news->SetTime(time + timeF);
      if(theDef == electron) { 
        news->SetCreatorModelID(icID); 
      } else {
        news->SetCreatorModelID(secID);
      }
      theParticleChange.AddSecondary(*news);
      delete news;
    }
    

    /*
    
    //
    // Sample final state
    //
    G4FragmentVector* fv = photonEvaporation->BreakUpFragment(aFragment);
    if(!fv) { fv = new G4FragmentVector(); }
    fv->push_back(aFragment);
    size_t n = fv->size();

    if (verboseLevel > 1) {
      G4cout << "ParticleResRadCapture: " << n << " final particle icID= " << icID << G4endl;
    }
    for(size_t i=0; i<n; ++i) {

      G4Fragment* f = (*fv)[i];    
      G4double etot = f->GetMomentum().e();

      Z = f->GetZ_asInt();
      A = f->GetA_asInt();

      const G4ParticleDefinition* theDef;
      if(0 == Z && 0 == A) {theDef =  f->GetParticleDefinition();}
      else if (Z == 1 && A == 2) {theDef = G4Deuteron::Deuteron();}
      else if (Z == 1 && A == 3) {theDef = G4Triton::Triton();}
      else if (Z == 2 && A == 3) {theDef = G4He3::He3();}
      else if (Z == 2 && A == 4) {theDef = G4Alpha::Alpha();}
      else {
        G4double eexc = f->GetExcitationEnergy();
	if(eexc <= minExcitation) { eexc = 0.0; }
	theDef = theTableOfIons->GetIon(Z, A, eexc, noFloat, 0);
	//theDef = theTableOfIons->GetIon(Z, A, G4NuclearLevelData::GetInstance()->GetLevelEnergy(Z,A,M-mass), noFloat, 0);

	if (verboseLevel > 1 && eexc > 0) {
	  G4cout << "### NC Find ion Z= " << Z << " A= " << A
		 << " Eexc(MeV)= " << eexc/MeV << "  " 
		 << theDef->GetParticleName() << G4endl;
	}
	  
      }
      G4double ekin = std::max(0.0,etot - theDef->GetPDGMass());
      if (verboseLevel > 1) {
	G4cout << i << ". " << theDef->GetParticleName()
	       << " Ekin(MeV)= " << etot/MeV
	       << " p: " << f->GetMomentum().vect() 
	       << G4endl;
      }
      G4HadSecondary* news = new G4HadSecondary(
	new G4DynamicParticle(theDef,
			      f->GetMomentum().vect().unit(),
			      ekin));
      G4double timeF = f->GetCreationTime();
      if(timeF < 0.0) { timeF = 0.0; }
      news->SetTime(time + timeF);
      if(theDef == electron) { news->SetCreatorModelType(icID); }
      theParticleChange.AddSecondary(*news);
      delete news;
      delete f;
    }
    delete fv;
    */
  }

  if (verboseLevel > 1) G4cout << "Resonant capture done" << G4endl;

  return &theParticleChange;
}

