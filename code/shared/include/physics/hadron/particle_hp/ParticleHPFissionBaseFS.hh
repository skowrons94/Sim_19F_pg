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
#ifndef ParticleHPFissionBaseFS_h
#define ParticleHPFissionBaseFS_h 1

#include "globals.hh"
#include "G4ReactionProduct.hh"
#include "G4DynamicParticleVector.hh"
#include "ParticleHPFinalState.hh"
#include "ParticleHPNames.hh"
#include "ParticleHPVector.hh"
#include "ParticleHPEnergyDistribution.hh"
#include "ParticleHPAngular.hh"
#include "G4Cache.hh"

class ParticleHPFissionBaseFS : public ParticleHPFinalState
{
  struct toBeCached
  {
    const G4ReactionProduct* theNeutronRP;
    const G4ReactionProduct* theTarget;
    toBeCached() : theNeutronRP(0),theTarget(0) {}
  };

public:
  
  ParticleHPFissionBaseFS()
  { 
    hasXsec = true; 
    theXsection = new ParticleHPVector;
  }

  virtual ~ParticleHPFissionBaseFS()
  {
    delete theXsection;
  }

  void Init (G4double A, G4double Z, G4int M,
             G4String & dirName, G4String & bit, G4ParticleDefinition*);

  G4DynamicParticleVector * ApplyYourself(G4int Prompt);

  virtual G4double GetXsec(G4double anEnergy)
  {
    return std::max(0., theXsection->GetY(anEnergy));
  }

  virtual ParticleHPVector * GetXsec()
  {
    return theXsection;
  }

  inline void SetNeutronRP(const G4ReactionProduct & aNeutron)
  { 
    fCache.Get().theNeutronRP = &aNeutron;
    theAngularDistribution.SetProjectileRP(aNeutron);
  }
  
  inline void SetTarget(const G4ReactionProduct & aTarget)
  { 
    fCache.Get().theTarget = &aTarget; 
    theAngularDistribution.SetTarget(aTarget);
  }
  
private:
  
  G4HadFinalState * ApplyYourself(const G4HadProjectile & ) {return 0;}
  
  ParticleHPVector * theXsection;
  ParticleHPEnergyDistribution theEnergyDistribution;
  ParticleHPAngular theAngularDistribution;
  
  G4Cache<toBeCached> fCache;
};

#endif
