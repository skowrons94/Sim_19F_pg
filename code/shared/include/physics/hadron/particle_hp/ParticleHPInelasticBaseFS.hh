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
#ifndef ParticleHPInelasticBaseFS_h
#define ParticleHPInelasticBaseFS_h 1

#include "globals.hh"
#include "G4HadProjectile.hh"
#include "G4HadFinalState.hh"
#include "ParticleHPFinalState.hh"
#include "ParticleHPAngular.hh"
#include "ParticleHPEnergyDistribution.hh"
#include "ParticleHPEnAngCorrelation.hh"
#include "ParticleHPPhotonDist.hh"
#include "ParticleHPDeExGammas.hh"
#include "G4Nucleus.hh"

class ParticleHPInelasticBaseFS : public ParticleHPFinalState
{
  public:
    
    ParticleHPInelasticBaseFS()
    {
      hasXsec = true; 
      theXsection = new ParticleHPVector;
    
      theEnergyDistribution = 0;
      theFinalStatePhotons = 0;
      theEnergyAngData = 0;
      theAngularDistribution = 0;

      theNuclearMassDifference = 0.0;
      Qvalue = 0.0;
    }

    virtual ~ParticleHPInelasticBaseFS()
    {
      delete theXsection;
      if (theEnergyDistribution != 0) delete theEnergyDistribution;
      if (theFinalStatePhotons != 0) delete theFinalStatePhotons;
      if (theEnergyAngData != 0) delete theEnergyAngData;
      if (theAngularDistribution != 0) delete theAngularDistribution;
    }
  
    void Init (G4double A, G4double Z, G4int M, G4String& dirName,
               G4String& bit, G4ParticleDefinition*);

    void BaseApply(const G4HadProjectile& theTrack,
                   G4ParticleDefinition** theDefs, G4int nDef);

    void InitGammas(G4double AR, G4double ZR);

    virtual G4HadFinalState* ApplyYourself(const G4HadProjectile& theTrack) = 0;

    virtual ParticleHPFinalState* New() = 0;
  
    virtual G4double GetXsec(G4double anEnergy)
    {
      return std::max(0., theXsection->GetY(anEnergy));
    }

    virtual ParticleHPVector* GetXsec() {return theXsection;}

  protected:
  
    ParticleHPVector* theXsection;
    ParticleHPEnergyDistribution* theEnergyDistribution;
    ParticleHPAngular* theAngularDistribution;
    ParticleHPEnAngCorrelation* theEnergyAngData;
  
    ParticleHPPhotonDist* theFinalStatePhotons;
    G4double theNuclearMassDifference;
    ParticleHPDeExGammas theGammas;
    G4String gammaPath;

    G4double Qvalue;

  private:
};

#endif
