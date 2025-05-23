//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// P. Arce, June-2014 Conversion neutron_hp to particle_hp
//
#ifndef ParticleHPSimpleEvapSpectrum_h
#define ParticleHPSimpleEvapSpectrum_h 1

#include <fstream>
#include <CLHEP/Units/SystemOfUnits.h>

#include "globals.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include "G4Exp.hh"
#include "G4Log.hh"
#include "ParticleHPVector.hh"
#include "VParticleHPEDis.hh"

// we will need a List of these .... one per term.

class ParticleHPSimpleEvapSpectrum : public VParticleHPEDis
{
  public:
  ParticleHPSimpleEvapSpectrum()
  {
    expm1 = G4Exp(-1.);
  }
  ~ParticleHPSimpleEvapSpectrum()
  {
  }
  
  inline void Init(std::istream & aDataFile)
  {
    theFractionalProb.Init(aDataFile, CLHEP::eV);
    theThetaDist.Init(aDataFile, CLHEP::eV);
  }
  
  inline G4double GetFractionalProbability(G4double anEnergy)
  {
    return theFractionalProb.GetY(anEnergy);
  }
  
  inline G4double Sample(G4double anEnergy) 
  {
    G4double theta = theThetaDist.GetY(anEnergy)*CLHEP::eV;
    G4double random, cut, max, result;
    max = 10.*theta;
    G4int icounter=0;
    G4int icounter_max=1024;
    do
    {
      icounter++;
      if ( icounter > icounter_max ) {
	 G4cout << "Loop-counter exceeded the threshold value at " << __LINE__ << "th line of " << __FILE__ << "." << G4endl;
         break;
      }
      random = G4UniformRand();
      result = -theta*G4Log(random); 
      cut = G4UniformRand();
    }
    while(cut>result/max); // Loop checking, 11.05.2015, T. Koi
    return result;
  }
  
  private:
  
  inline G4double Evapo(G4double anEnergy, G4double theta)
  {
    G4double result = (anEnergy*CLHEP::eV)*G4Exp(-anEnergy*CLHEP::eV/theta);
    return result;
  }
  
  private:
  
  G4double expm1;
  
  ParticleHPVector theFractionalProb;
  
  ParticleHPVector theThetaDist;
  
};

#endif
