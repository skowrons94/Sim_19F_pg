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
#ifndef ParticleHPEnergyDistribution_h
#define ParticleHPEnergyDistribution_h 1

#include <fstream>

#include "globals.hh"
#include "G4ios.hh"
#include "Randomize.hh"
#include "ParticleHPArbitaryTab.hh"
#include "ParticleHPEvapSpectrum.hh"
#include "ParticleHPSimpleEvapSpectrum.hh"
#include "ParticleHPFissionSpectrum.hh"
#include "ParticleHPWattSpectrum.hh"
#include "ParticleHPMadlandNixSpectrum.hh"
#include "VParticleHPEDis.hh"

// we will need a List of these .... one per term.

class ParticleHPEnergyDistribution
{
  public:
  ParticleHPEnergyDistribution()
  {
    theEnergyDistribution = 0;
    theNumberOfPartials = 0;
    theRepresentationType = 0;
  }
  ~ParticleHPEnergyDistribution()
  {
    if(theEnergyDistribution != 0)
    {
      for(G4int i=0; i<theNumberOfPartials; i++) 
      {
        delete theEnergyDistribution[i];
      }
      delete [] theEnergyDistribution;
    }
  }
  
  inline void Init(std::istream & theData)
  {
    G4double dummy;
    theData >> dummy >> theNumberOfPartials;
    theEnergyDistribution = new VParticleHPEDis * [theNumberOfPartials];
    for(G4int i=0; i<theNumberOfPartials; i++) 
    {
      theData >> theRepresentationType;
      switch(theRepresentationType)
      {
	case 1:
          theEnergyDistribution[i] = new ParticleHPArbitaryTab;
          break;
	case 5:        
          theEnergyDistribution[i] = new ParticleHPEvapSpectrum;
          break;
	case 7:
          theEnergyDistribution[i] = new ParticleHPFissionSpectrum;
          break;
	case 9:
          theEnergyDistribution[i] = new ParticleHPSimpleEvapSpectrum;
          break;
	case 11:
          theEnergyDistribution[i] = new ParticleHPWattSpectrum;
          break;
	case 12:
          theEnergyDistribution[i] = new ParticleHPMadlandNixSpectrum;
          break;
      }
      theEnergyDistribution[i]->Init(theData);
    }
  }
  
  inline G4double Sample(G4double anEnergy, G4int & it) 
  {
    G4double result = 0;
    it = 0;
    if (theNumberOfPartials != 0)
    {
      G4double sum=0;
      G4double * running = new G4double[theNumberOfPartials];
      running[0] = 0;
      G4int i;
      for (i=0; i<theNumberOfPartials; i++)
      {	
	if (i!=0) running[i]=running[i-1];
	running[i]+=theEnergyDistribution[i]->GetFractionalProbability(anEnergy);
      }
      sum = running[theNumberOfPartials-1];
      G4double random = G4UniformRand();
      for(i=0; i<theNumberOfPartials; i++)
      {
	it = i;
	if(running[i]/sum>random) break;
      }
      delete [] running;
      if(it==theNumberOfPartials) it--;
      result = theEnergyDistribution[it]->Sample(anEnergy);
    }
    return result;
  }
  
  private:
  
  G4int theNumberOfPartials;
  G4int theRepresentationType;
  VParticleHPEDis ** theEnergyDistribution;
};

#endif
