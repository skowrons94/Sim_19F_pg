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
//
// 25-08-06 New Final State type (refFlag==3 , Legendre (Low Energy) + Probability (High Energy) )
//          is added by T. KOI
//
// P. Arce, June-2014 Conversion neutron_hp to particle_hp
//
#ifndef ParticleHPElasticFS_h
#define ParticleHPElasticFS_h 1

#include "globals.hh"
#include "G4HadProjectile.hh"
#include "G4HadFinalState.hh"
#include "ParticleHPFinalState.hh"
#include "ParticleHPLegendreStore.hh"
#include "ParticleHPPartial.hh"
#include "ParticleHPFastLegendre.hh"
#include "ParticleHPInterpolator.hh"
#include "ParticleHPNames.hh"

class ParticleHPElasticFS : public ParticleHPFinalState
{
  public:
  
  ParticleHPElasticFS();
  ~ParticleHPElasticFS()
  {
    if(theCoefficients!=0) delete theCoefficients;
    if(theProbArray!=0) delete theProbArray;
  }
  void Init (G4double A, G4double Z, G4int M, G4String & dirName, G4String & aFSType, G4ParticleDefinition*);
  G4HadFinalState * ApplyYourself(const G4HadProjectile & theTrack);
  ParticleHPFinalState * New() 
  {
   ParticleHPElasticFS * theNew = new ParticleHPElasticFS;
   return theNew;
  }
  
  private:
  G4int repFlag;    // Legendre coeff(1), or probability array(2), or isotropic(0).
                    // add 3: for Legendre (Low Energy) + Probability (High Energy)
  G4double tE_of_repFlag3; // transition energy in case of  repFlag 3:
  G4double targetMass; // in neutronmass units.
  G4int frameFlag;  // CMS or Lab system.
  
  ParticleHPLegendreStore * theCoefficients; // the legendre coefficients
  ParticleHPPartial * theProbArray; // the probability array p,costh for energy
  ParticleHPInterpolator theInt; // interpolation
  
  ParticleHPFastLegendre theLegend; // fast look-up for leg-integrals
};
#endif
