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
#ifndef ParticleHPNT2AInelasticFS_h
#define ParticleHPNT2AInelasticFS_h 1

#include "globals.hh"
#include "G4HadProjectile.hh"
#include "G4HadFinalState.hh"
#include "ParticleHPInelasticBaseFS.hh"
#include "ParticleHPAngular.hh"
#include "ParticleHPEnergyDistribution.hh"
#include "ParticleHPEnAngCorrelation.hh"
#include "ParticleHPPhotonDist.hh"

class ParticleHPNT2AInelasticFS : public ParticleHPInelasticBaseFS
{
  public:
  
  ParticleHPNT2AInelasticFS();
  ~ParticleHPNT2AInelasticFS(){}
  void Init (G4double A, G4double Z, G4int M, G4String & dirName, G4String & aFSType, G4ParticleDefinition*);
  G4HadFinalState * ApplyYourself(const G4HadProjectile & theTrack);
  ParticleHPFinalState * New() 
  {
   ParticleHPNT2AInelasticFS * theNew = new ParticleHPNT2AInelasticFS;
   return theNew;
  }
  
  private:
  
};
#endif
