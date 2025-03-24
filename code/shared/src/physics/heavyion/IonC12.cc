#include "IonC12.hh"

#include "G4ParticleTable.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"

IonC12* IonC12::theInstance = nullptr;

IonC12* IonC12::Definition()
{
  if (theInstance != nullptr) return theInstance;

  const G4String name = "C12";
  // search in particle table]
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* anInstance = pTable->FindParticle(name);
  if (anInstance == nullptr) {
    // create particle
    //
    //    Arguments for constructor are as follows
    //               name             mass          width         charge
    //             2*spin           parity  C-conjugation
    //          2*Isospin       2*Isospin3       G-parity
    //               type    lepton number  baryon number   PDG encoding
    //             stable         lifetime    decay table
    //             shortlived      subType    anti_encoding
    // clang-format off
   anInstance = new G4ParticleDefinition(
	         name,   11.17486338798439*GeV,       0.0*MeV,        +6.0*eplus, 
		    0,              +1,             0,          
		    0,               0,             0,             
	    "nucleus",               0,           +12,        1000060120,
	      true,               -1.0,       nullptr,
             false,           "static",   -1000060120
	      );
    // clang-format on
  }
  theInstance = static_cast<IonC12*>(anInstance);
  return theInstance;
}

IonC12* IonC12::theIonC12Definition()
{
  return Definition();
}

IonC12* IonC12::theIonC12()
{
  return Definition();
}
