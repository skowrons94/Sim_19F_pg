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
// Class Description
// Keep Information about current reaction
// 121031 First implementation done by T. Koi (SLAC/PPA)
// P. Arce, June-2014 Conversion neutron_hp to particle_hp
//
#include "ParticleHPReactionWhiteBoard.hh"

ParticleHPReactionWhiteBoard::ParticleHPReactionWhiteBoard()
:targZ(0)
,targA(0)
,targM(0)
{
;
}
ParticleHPReactionWhiteBoard::~ParticleHPReactionWhiteBoard()
{
   mapStringPair.clear();
}

void ParticleHPReactionWhiteBoard::Dump()
{
   G4cout << "ParticleHPReactionWhiteBoard::Dump" << G4endl;
   G4cout << "Target Z = " << targZ << G4endl;
   G4cout << "Target A = " << targA << G4endl;
   G4cout << "Target M = " << targM << G4endl;

   for ( std::map< G4String,G4String >::iterator 
         it = mapStringPair.begin(); it != mapStringPair.end(); it++ )
   {
      G4cout << it->first << " " << it->second << G4endl; 
   }
   //,,,
   G4cout << G4endl;
}

bool ParticleHPReactionWhiteBoard::AddRecord( std::pair<G4String,G4String> new_record )
{
   if ( mapStringPair.find( new_record.first ) !=  mapStringPair.end() ) {
      G4cout << "This key is already used in the current reaction white board!" << G4endl;
      return false;
   }
   mapStringPair.insert ( new_record );
   return true;
}

G4String ParticleHPReactionWhiteBoard::GetValue( G4String key )
{
   std::map< G4String,G4String >::iterator it = mapStringPair.find( key );
   if ( it == mapStringPair.end() ) {
      G4cout << "No entry for this key " << key << " in the current reaction white board!" << G4endl;
      return "NONE";
   }
   return it->second;
}

G4int ParticleHPReactionWhiteBoard::GetValueInInt( G4String key )
{
   G4String result = GetValue( key );  
   if ( result == "NONE" ) return 0;
   std::stringstream ss;
   ss << key;
   G4int i;
   ss >> i;
   return i;
}

G4double ParticleHPReactionWhiteBoard::GetValueInDouble( G4String key )
{
   G4String result = GetValue( key );  
   if ( result == "NONE" ) return 0.0;
   std::stringstream ss;
   ss << key;
   G4double x;
   ss >> x;
   return x;
}
