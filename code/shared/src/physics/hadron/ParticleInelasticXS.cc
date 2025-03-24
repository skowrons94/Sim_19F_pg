#include "ParticleInelasticXS.hh"
#include "G4Neutron.hh"
#include "G4DynamicParticle.hh"
#include "G4ElementTable.hh"
#include "G4Material.hh"
#include "G4Element.hh"
//#include "G4PhysicsLogVector.hh"
#include "G4PhysicsVector.hh"
#include "G4CrossSectionDataSetRegistry.hh"
#include "G4ComponentGGHadronNucleusXsc.hh"
#include "G4ComponentGGNuclNuclXsc.hh"
#include "G4Proton.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4IsotopeList.hh"
#include "G4HadronicParameters.hh"
#include "G4IonTable.hh"

#include <fstream>
#include <sstream>

G4ElementData* ParticleInelasticXS::data[] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
G4double ParticleInelasticXS::coeff[MAXZINELP][6] = {{1.0}, {1.0}, {1.0}, {1.0}, {1.0}, {1.0}};
G4String ParticleInelasticXS::gDataDirectory[] = {"", "", "", "", "", ""};

#ifdef G4MULTITHREADED
  G4Mutex ParticleInelasticXS::particleInelasticXSMutex = G4MUTEX_INITIALIZER;
#endif

ParticleInelasticXS::ParticleInelasticXS(const G4ParticleDefinition* part) 
  : G4VCrossSectionDataSet("ParticleInelasticXS"),
    particle(part)
{
  if(nullptr == part) {
    G4Exception("ParticleInelasticXS::ParticleInelasticXS(..)","had015",
		FatalException, "NO particle definition in constructor");
  } else {
    verboseLevel = 1;
    const G4String& particleName = particle->GetParticleName();
    if(verboseLevel > 1) {
      G4cout << "ParticleInelasticXS::ParticleInelasticXS for " 
	     << particleName << " on atoms with Z < " << MAXZINELP << G4endl;
    }
    if(particleName == "proton") {
      highEnergyXsection = G4CrossSectionDataSetRegistry::Instance()->GetComponentCrossSection("Glauber-Gribov");
      if(highEnergyXsection == nullptr) {
	highEnergyXsection = new G4ComponentGGHadronNucleusXsc();
      }
    } else {
      highEnergyXsection = G4CrossSectionDataSetRegistry::Instance()->GetComponentCrossSection("Glauber-Gribov Nucl-nucl");
      if(highEnergyXsection == nullptr) {
	highEnergyXsection = new G4ComponentGGNuclNuclXsc();
      }
      if(particleName == "deuteron") index = 1; 
      else if(particleName == "triton") index = 2; 
      else if(particleName == "He3") index = 3; 
      else if(particleName == "alpha") index = 4;
      else if(particleName == "C12") index = 5;
      else {
        G4ExceptionDescription ed;
        ed << particleName << " is a wrong particle type";
	G4Exception("ParticleInelasticXS::BuildPhysicsTable(..)","had012",
		    FatalException, ed, "");
      } 
    }
  }
  SetForAllAtomsAndEnergies(true);
}
/*
ParticleInelasticXS::~ParticleInelasticXS()
{
  G4cout << "ParticleInelasticXS::Deleting data" << G4endl;
  if(isMaster) { 
    delete data[index]; 
    data[index] = nullptr;
  }
}
*/
void ParticleInelasticXS::CrossSectionDescription(std::ostream& outFile) const
{
  outFile << "ParticleInelasticXS calculates n, p, d, t, he3, he4 inelastic\n"
          << "cross section on nuclei using data from the high precision\n"
          << "neutron database.  These data are simplified and smoothed over\n"
          << "the resonance region in order to reduce CPU time.\n"
          << "For high energy Glauber-Gribov cross section model is used\n";
}

G4bool 
ParticleInelasticXS::IsElementApplicable(const G4DynamicParticle*, 
					   G4int, const G4Material*)
{
  return true;
}

G4bool 
ParticleInelasticXS::IsIsoApplicable(const G4DynamicParticle*,
				       G4int, G4int,
				       const G4Element*, const G4Material*)
{
  return true;
}

G4double ParticleInelasticXS::GetElementCrossSection(
         const G4DynamicParticle* aParticle,
	 G4int ZZ, const G4Material*)
{
  G4double xs = 0.0;
  G4double ekin = aParticle->GetKineticEnergy();

  G4int Z = (ZZ >= MAXZINELP) ? MAXZINELP - 1 : ZZ; 

  auto pv = GetPhysicsVector(Z);
  if(nullptr == pv) { return xs; }
  //  G4cout  << "ParticleInelasticXS::GetCrossSection e= " << ekin 
  //  << " Z= " << Z << G4endl;

  if(ekin <= pv->GetMaxEnergy()) { 
    //xs = pv->LogVectorValue(ekin, aParticle->GetLogKineticEnergy()); 
    xs = pv->Value(ekin); 
  } else {
    xs = coeff[Z][index]*highEnergyXsection->GetInelasticElementCrossSection(particle,
			        ekin, Z, aeff[Z]);
  }

  if(verboseLevel > 1) {
    G4cout  << "ElmXS: Z= " << Z << " Ekin(MeV)= " << ekin/CLHEP::MeV 
	    << " xs(bn)= " << xs/CLHEP::barn << " element data for "
	    << particle->GetParticleName()
            << " idx= " << index << G4endl;
  }

  return xs;
}

G4double ParticleInelasticXS::GetIsoCrossSection(
         const G4DynamicParticle* aParticle, 
	 G4int Z, G4int A,
	 const G4Isotope*, const G4Element*, const G4Material*)
{
  return IsoCrossSection(aParticle->GetKineticEnergy(), 
                         aParticle->GetLogKineticEnergy(),Z, A);
}

G4double 
ParticleInelasticXS::IsoCrossSection(G4double ekin, G4double logE,
                                       G4int ZZ, G4int A)
{
  G4double xs = 0.0;
  G4int Z = (ZZ >= MAXZINELP) ? MAXZINELP - 1 : ZZ; 
  /*  
  G4cout << "ParticleInelasticXS: IsoCrossSection  Z= " 
         << Z << "  A= " << A 
         << "  Amin= " << amin[Z] << " Amax= " << amax[Z]
         << " E(MeV)= " << ekin << G4endl;
  */
  auto pv = GetPhysicsVector(Z);
  if(pv == nullptr) { return xs; }

  // compute isotope cross section if applicable 
  const G4double emax = pv->GetMaxEnergy(); 
  if(ekin <= emax && amin[Z] < amax[Z] && A >= amin[Z] && A <= amax[Z]) {
    auto pviso = data[index]->GetComponentDataByIndex(Z, A - amin[Z]);
    if(pviso != nullptr) { 
      //xs = pviso->LogVectorValue(ekin, logE);
      xs = pviso->Value(ekin);

      if(verboseLevel > 1) {
	G4cout << "ParticleInelasticXS::IsoXS: for " 
               << particle->GetParticleName() << " Ekin(MeV)= " 
               << ekin/CLHEP::MeV << "  xs(b)= " << xs/CLHEP::barn 
	       << "  Z= " << Z << "  A= " << A 
               << " idx= " << index << G4endl;
      }

      return xs;
    }
  }
  // use element x-section
  if(ekin <= emax) { 
    //xs = pv->LogVectorValue(ekin, logE); 
    xs = pv->Value(ekin); 
  } else {
    xs = coeff[Z][index] *
      highEnergyXsection->GetInelasticElementCrossSection(particle,
			  ekin, Z, aeff[Z]);
  }
  xs *= A/aeff[Z];

  if(verboseLevel > 1) {
    G4cout  << "IsoXS for " << particle->GetParticleName() 
	    << " Target Z= " << Z << " A= " << A 
	    << " Ekin(MeV)= " << ekin/CLHEP::MeV 
	    << " xs(bn)= " << xs/CLHEP::barn
            << " idx= " << index << G4endl;
  }

  return xs;
}

const G4Isotope* ParticleInelasticXS::SelectIsotope(
		 const G4Element* anElement, G4double kinEnergy, G4double logE)
{
  size_t nIso = anElement->GetNumberOfIsotopes();
  const G4Isotope* iso = anElement->GetIsotope(0);

  //G4cout << "SelectIsotope NIso= " << nIso << G4endl;
  if(1 == nIso) { return iso; }

  // more than 1 isotope
  G4int Z = anElement->GetZasInt();
  //G4cout << "SelectIsotope Z= " << Z << G4endl;

  const G4double* abundVector = anElement->GetRelativeAbundanceVector();
  G4double q = G4UniformRand();
  G4double sum = 0.0;
  size_t j;

  // isotope wise cross section not available
  if(amax[Z] == amin[Z] || Z >= MAXZINELP) {
    for (j=0; j<nIso; ++j) {
      sum += abundVector[j];
      if(q <= sum) {
	iso = anElement->GetIsotope(j);
	break;
      }
    }
    return iso;
  }

  size_t nn = temp.size();
  if(nn < nIso) { temp.resize(nIso, 0.); }

  for (j=0; j<nIso; ++j) {
    //G4cout << j << "-th isotope " << (*isoVector)[j]->GetN() 
    //       <<  " abund= " << abundVector[j] << G4endl;
    sum += abundVector[j]*IsoCrossSection(kinEnergy, logE, Z, 
					  anElement->GetIsotope(j)->GetN());
    temp[j] = sum;
  }
  sum *= q;
  for (j=0; j<nIso; ++j) {
    if(temp[j] >= sum) {
      iso = anElement->GetIsotope(j);
      break;
    }
  }
  return iso;
}

void 
ParticleInelasticXS::BuildPhysicsTable(const G4ParticleDefinition& p)
{
  //G4cout << "ParticleInelasticXS particle name: " << p.GetParticleName() << "  ID: " << p.GetParticleDefinitionID() << G4endl;
  if(verboseLevel > 0){
    G4cout << "ParticleInelasticXS::BuildPhysicsTable for " 
	   << p.GetParticleName() << G4endl;
  }
/*
  if(&p != particle) { 
    G4ExceptionDescription ed;
    ed << p.GetParticleName() << " is a wrong particle type -"
       << particle->GetParticleName() << " is expected";
    G4Exception("ParticleInelasticXS::BuildPhysicsTable(..)","had012",
		FatalException, ed, "");
    return; 
  }
  */
  G4int fact = (p.GetParticleName() == "proton") ? 1 : 256;
  SetMaxKinEnergy(G4HadronicParameters::Instance()->GetMaxEnergy() * fact);

  if(data[index] == nullptr) { 
#ifdef G4MULTITHREADED
    G4MUTEXLOCK(&particleInelasticXSMutex);
    if(data[index] == nullptr) { 
#endif
      isMaster = true;
      data[index] = new G4ElementData();
      data[index]->SetName(particle->GetParticleName() + "Inelastic");
      FindDirectoryPath();
#ifdef G4MULTITHREADED
    }
    G4MUTEXUNLOCK(&particleInelasticXSMutex);
#endif
  }

  // it is possible re-initialisation for the new run
  const G4ElementTable* table = G4Element::GetElementTable();
  if(isMaster) {

    // Access to elements
    for ( auto & elm : *table ) {
      G4int Z = std::max( 1, std::min( elm->GetZasInt(), MAXZINELP-1) );
      if ( nullptr == (data[index])->GetElementData(Z) ) { Initialise(Z); }
    }
  }
  // prepare isotope selection
  size_t nIso = temp.size();
  for ( auto & elm : *table ) {
    size_t n = elm->GetNumberOfIsotopes();
    if(n > nIso) { nIso = n; }
  }
  temp.resize(nIso, 0.0);
}

const G4String& ParticleInelasticXS::FindDirectoryPath()
{
  // check environment variable
  // build the complete string identifying the file with the data set
  if(gDataDirectory[index].empty()) {
    char* path = std::getenv("G4PARTICLEXSDATA");
    if (nullptr != path) {
      std::ostringstream ost;
      ost << path << "/" << particle->GetParticleName() << "/inel";
      gDataDirectory[index] = ost.str();
    } else {
      G4Exception("G4NeutronInelasticXS::Initialise(..)","had013",
		  FatalException,
		  "Environment variable G4PARTICLEXSDATA is not defined");
    }
  }
  return gDataDirectory[index];
}

void ParticleInelasticXS::InitialiseOnFly(G4int Z)
{
#ifdef G4MULTITHREADED
   G4MUTEXLOCK(&particleInelasticXSMutex);
   if(nullptr == data[index]->GetElementData(Z)) { 
#endif
     Initialise(Z);
#ifdef G4MULTITHREADED
   }
   G4MUTEXUNLOCK(&particleInelasticXSMutex);
#endif
}

void ParticleInelasticXS::Initialise(G4int Z)
{
  if(nullptr != data[index]->GetElementData(Z)) { return; }

  // upload element data 
  std::ostringstream ost;
  ost << FindDirectoryPath() << Z ;
  G4PhysicsVector* v = RetrieveVector(ost, true);
  data[index]->InitialiseForElement(Z, v);
  /*
  G4cout << "ParticleInelasticXS::Initialise for Z= " << Z 
	 << " idx= " << index
	 << "  Amin= " << amin[Z] 
	 << "  Amax= " << amax[Z] 
	 << "  " << FindDirectoryPath() << G4endl;
  */
  // upload isotope data
  if(amin[Z] < amax[Z]) {
    G4int nmax = amax[Z] - amin[Z] + 1;
    data[index]->InitialiseForComponent(Z, nmax);

    for(G4int A=amin[Z]; A<=amax[Z]; ++A) {
      std::ostringstream ost1;
      ost1 << FindDirectoryPath() << Z << "_" << A;
      G4PhysicsVector* v1 = RetrieveVector(ost1, false);
      data[index]->AddComponent(Z, A, v1); 
      /*
      G4cout << "  Isotope x-section Z= " << Z << " A= " << A 
	     << " v1= " << v1 << G4endl;
      */
    }
  }
  // smooth transition 
  G4double sig1  = (*v)[v->GetVectorLength()-1];
  G4double ehigh = v->GetMaxEnergy();
  G4double sig2 = highEnergyXsection->GetInelasticElementCrossSection(
                  particle, ehigh, Z, aeff[Z]);
  coeff[Z][index] = (sig2 > 0.) ? sig1/sig2 : 1.0;
  /*
  G4cout << "ParticleInelasticXS: index= " << index 
         << " Z= " << Z << " coeff= " << coeff[Z][index] << G4endl; 
  */
}

G4PhysicsVector* 
ParticleInelasticXS::RetrieveVector(std::ostringstream& ost, G4bool warn)
{
  //G4PhysicsLogVector* v = nullptr;
  G4PhysicsVector* v = nullptr;
  std::ifstream filein(ost.str().c_str());
  if (!filein.is_open()) {
    if(warn) { 
      G4ExceptionDescription ed;
      ed << "Data file <" << ost.str().c_str()
	 << "> is not opened!";
      G4Exception("ParticleInelasticXS::RetrieveVector(..)","had014",
		  FatalException, ed, "Check G4PARTICLEXSDATA");
    }
  } else {
    if(verboseLevel > 1) {
      G4cout << "File " << ost.str() 
	     << " is opened by ParticleInelasticXS" << G4endl;
    }
    // retrieve data from DB
    //v = new G4PhysicsLogVector();
    v = new G4PhysicsVector();
    if(!v->Retrieve(filein, true)) {
      G4ExceptionDescription ed;
      ed << "Data file <" << ost.str().c_str()
	 << "> is not retrieved!";
      G4Exception("ParticleInelasticXS::RetrieveVector(..)","had015",
		  FatalException, ed, "Check G4PARTICLEXSDATA");
    }
  }
  return v;
}
