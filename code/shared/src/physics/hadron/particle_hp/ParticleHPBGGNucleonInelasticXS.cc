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
// -------------------------------------------------------------------
//
// GEANT4 Class file
//
//
// File name:     ParticleHPBGGNucleonInelasticXS
//
// Author:        KOI, Tatsumi
//
// Creation date: 22.03.2012
// Modifications:
//
//
// -------------------------------------------------------------------
//
// P. Arce, June-2014 Conversion neutron_hp to particle_hp
//

#include "ParticleHPBGGNucleonInelasticXS.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ParticleHPBGGNucleonInelasticXS::ParticleHPBGGNucleonInelasticXS(const G4ParticleDefinition* p)
 : G4BGGNucleonInelasticXS( p ) 
{
   fLowEnergyLimitForHPN = 20*MeV;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ParticleHPBGGNucleonInelasticXS::~ParticleHPBGGNucleonInelasticXS()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool ParticleHPBGGNucleonInelasticXS::IsElementApplicable(const G4DynamicParticle* dp, 
						    G4int Z, 
						    const G4Material*)
{
   if ( dp->GetKineticEnergy() < fLowEnergyLimitForHPN ) return false;
   return (1 < Z);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool ParticleHPBGGNucleonInelasticXS::IsIsoApplicable(const G4DynamicParticle* dp, 
						G4int Z, G4int A,  
						const G4Element*,
						const G4Material*)
{
   if ( dp->GetKineticEnergy() < fLowEnergyLimitForHPN ) return false;
   return (1 == Z && 2 >= A);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
