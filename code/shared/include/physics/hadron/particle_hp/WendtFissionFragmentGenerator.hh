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
/*
 * File:   WendtFissionFragmentGenerator.hh
 * Author: B. Wendt (wendbryc@isu.edu)
 *
 * Created on June 21, 2013, 13:58 MST
 */

#ifndef WendtFissionFragmentGenerator_h
#define WendtFissionFragmentGenerator_h 1

#include <map>

#include "G4HadFinalState.hh"

#include "G4FissionFragmentGenerator.hh"
#include "ParticleHPNames.hh"

class WendtFissionFragmentGenerator
{
public:
	G4HadFinalState* ApplyYourself(const G4HadProjectile& projectile, G4int Z, G4int A);
	static WendtFissionFragmentGenerator* GetInstance() {
           if ( instance == NULL) instance = new WendtFissionFragmentGenerator();
           return instance;
        }

	void InitializeANucleus(const G4int A, const G4int Z, const G4int M, const G4String& dataDirectory);
	~WendtFissionFragmentGenerator();

private:
	// SINGLETON!!!
	WendtFissionFragmentGenerator();
	WendtFissionFragmentGenerator(WendtFissionFragmentGenerator const&);
	void operator=(WendtFissionFragmentGenerator const&);

        static G4ThreadLocal WendtFissionFragmentGenerator* instance;
	// SINGLETON!!!

	/** A map of all the fission isotopes loaded at initialization */
    std::map< const G4int, G4FissionFragmentGenerator* > fissionIsotopes;
    ParticleHPNames fileNames;

    G4int Verbosity_;
  
    G4int secID;  // Creator model ID for the fission fragments
};
#endif
