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
#ifndef ParticleHPManager_h
#define ParticleHPManager_h 1

// Class Description
// Manager of NeutronHP 
// Class Description - End

// 121031 First implementation done by T. Koi (SLAC/PPA)
//
#include <map>
#include <vector>
#include "globals.hh"

#include "ParticleHPReactionWhiteBoard.hh"

class G4ParticleDefinition;
class ParticleHPChannel;
class ParticleHPChannelList;
class ParticleHPMessenger;
class ParticleHPVector;
class G4PhysicsTable;
struct E_isoAng;
struct E_P_E_isoAng;

class ParticleHPManager 
{
   public:
      static ParticleHPManager* GetInstance();

   private: 
      ParticleHPManager();
      ParticleHPManager( const ParticleHPManager& ){};
      ~ParticleHPManager();
      static ParticleHPManager* instance;

   public:
      ParticleHPReactionWhiteBoard* GetReactionWhiteBoard();
      void OpenReactionWhiteBoard();
      //void CloseReactionWhiteBoard(){delete RWB; RWB=NULL;};
      void CloseReactionWhiteBoard();

      void GetDataStream( G4String , std::istringstream& iss );
      void GetDataStream2( G4String , std::istringstream& iss );
      void SetVerboseLevel( G4int i ); 
      G4int GetVerboseLevel() {return verboseLevel; }; 

      void DumpDataSource();

      G4bool GetUseOnlyPhotoEvaporation() { return USE_ONLY_PHOTONEVAPORATION; };
      G4bool GetSkipMissingIsotopes() { return SKIP_MISSING_ISOTOPES; };
      G4bool GetNeglectDoppler() { return NEGLECT_DOPPLER; };
      G4bool GetDoNotAdjustFinalState() { return DO_NOT_ADJUST_FINAL_STATE; };
      G4bool GetProduceFissionFragments() { return PRODUCE_FISSION_FRAGMENTS; };
      G4bool GetUseWendtFissionModel() { return USE_WENDT_FISSION_MODEL; };
      G4bool GetUseNRESP71Model() { return USE_NRESP71_MODEL; };

      void SetUseOnlyPhotoEvaporation( G4bool val ) { USE_ONLY_PHOTONEVAPORATION = val; };
      void SetSkipMissingIsotopes( G4bool val ) { SKIP_MISSING_ISOTOPES = val; };
      void SetNeglectDoppler( G4bool val ) { NEGLECT_DOPPLER = val; };
      void SetDoNotAdjustFinalState( G4bool val ) { DO_NOT_ADJUST_FINAL_STATE = val; };
      void SetProduceFissionFragments( G4bool val ) {
	// Make sure both fission fragment models are not active at same time
	USE_WENDT_FISSION_MODEL ? PRODUCE_FISSION_FRAGMENTS = false : PRODUCE_FISSION_FRAGMENTS = val ; };
      void SetUseWendtFissionModel( G4bool val ) { USE_WENDT_FISSION_MODEL = val;
	// Make sure both fission fragment models are not active at same time
	if ( USE_WENDT_FISSION_MODEL ) PRODUCE_FISSION_FRAGMENTS = false; };
      void SetUseNRESP71Model( G4bool val ) { USE_NRESP71_MODEL = val; };

      void DumpSetting(); // Needs to be called somewhere to print out information once per run.
  
      void RegisterElasticCrossSections( G4PhysicsTable* val ){ theElasticCrossSections = val; };
      G4PhysicsTable* GetElasticCrossSections(){ return theElasticCrossSections; };
      void RegisterCaptureCrossSections( G4PhysicsTable* val ){ theCaptureCrossSections = val; };
      G4PhysicsTable* GetCaptureCrossSections(){ return theCaptureCrossSections; };
      void RegisterInelasticCrossSections( const G4ParticleDefinition* , G4PhysicsTable* );
      G4PhysicsTable* GetInelasticCrossSections(const G4ParticleDefinition* );
      void RegisterFissionCrossSections( G4PhysicsTable* val ){ theFissionCrossSections = val; };
      G4PhysicsTable* GetFissionCrossSections(){ return theFissionCrossSections; };

      std::vector<ParticleHPChannel*>* GetElasticFinalStates() { return theElasticFSs; };
      void RegisterElasticFinalStates( std::vector<ParticleHPChannel*>* val ) { theElasticFSs = val; };
      std::vector<ParticleHPChannelList*>* GetInelasticFinalStates( const G4ParticleDefinition* );
      void RegisterInelasticFinalStates( const G4ParticleDefinition* , std::vector<ParticleHPChannelList*>* );
      std::vector<ParticleHPChannel*>* GetCaptureFinalStates() { return theCaptureFSs; };
      void RegisterCaptureFinalStates( std::vector<ParticleHPChannel*>* val ) { theCaptureFSs = val; };
      std::vector<ParticleHPChannel*>* GetFissionFinalStates() { return theFissionFSs; };
      void RegisterFissionFinalStates( std::vector<ParticleHPChannel*>* val ) { theFissionFSs = val; };

      std::map<G4int,std::map<G4double,ParticleHPVector*>*>* GetThermalScatteringCoherentCrossSections() { return theTSCoherentCrossSections; };
      void RegisterThermalScatteringCoherentCrossSections( std::map<G4int,std::map<G4double,ParticleHPVector*>*>* val ) { theTSCoherentCrossSections = val; };
      std::map<G4int,std::map<G4double,ParticleHPVector*>*>* GetThermalScatteringIncoherentCrossSections() { return theTSIncoherentCrossSections; };
      void RegisterThermalScatteringIncoherentCrossSections( std::map<G4int,std::map<G4double,ParticleHPVector*>*>* val ) { theTSIncoherentCrossSections = val; };
      std::map<G4int,std::map<G4double,ParticleHPVector*>*>* GetThermalScatteringInelasticCrossSections() { return theTSInelasticCrossSections; };
      void RegisterThermalScatteringInelasticCrossSections( std::map<G4int,std::map<G4double,ParticleHPVector*>*>* val ) { theTSInelasticCrossSections = val; }; 

      std::map < G4int , std::map < G4double , std::vector < std::pair< G4double , G4double >* >* >* >* GetThermalScatteringCoherentFinalStates(){ return theTSCoherentFinalStates; };
      void RegisterThermalScatteringCoherentFinalStates( std::map < G4int , std::map < G4double , std::vector < std::pair< G4double , G4double >* >* >* >* val ) { theTSCoherentFinalStates = val; };
      std::map < G4int , std::map < G4double , std::vector < E_isoAng* >* >* >* GetThermalScatteringIncoherentFinalStates(){ return theTSIncoherentFinalStates; };
      void RegisterThermalScatteringIncoherentFinalStates( std::map < G4int , std::map < G4double , std::vector < E_isoAng* >* >* >* val ) { theTSIncoherentFinalStates = val; };
      std::map < G4int , std::map < G4double , std::vector < E_P_E_isoAng* >* >* >* GetThermalScatteringInelasticFinalStates(){ return theTSInelasticFinalStates; };
      void RegisterThermalScatteringInelasticFinalStates( std::map < G4int , std::map < G4double , std::vector < E_P_E_isoAng* >* >* >* val ) { theTSInelasticFinalStates = val; };


   private:
      void register_data_file( G4String , G4String );
      std::map<G4String,G4String> mDataEvaluation;
      /*ParticleHPReactionWhiteBoard* RWB;*/

      G4int verboseLevel;

      ParticleHPMessenger* messenger;
      G4bool USE_ONLY_PHOTONEVAPORATION;
      G4bool SKIP_MISSING_ISOTOPES;
      G4bool NEGLECT_DOPPLER;
      G4bool DO_NOT_ADJUST_FINAL_STATE;
      G4bool PRODUCE_FISSION_FRAGMENTS;
      G4bool USE_WENDT_FISSION_MODEL;
      G4bool USE_NRESP71_MODEL;

      G4PhysicsTable* theElasticCrossSections;
      G4PhysicsTable* theCaptureCrossSections;
      std::map< const G4ParticleDefinition* , G4PhysicsTable* > theInelasticCrossSections;
      G4PhysicsTable* theFissionCrossSections;

      std::vector<ParticleHPChannel*>* theElasticFSs;
      std::map< const G4ParticleDefinition* , std::vector<ParticleHPChannelList*>* > theInelasticFSs;
      std::vector<ParticleHPChannel*>* theCaptureFSs;
      std::vector<ParticleHPChannel*>* theFissionFSs;

      std::map< G4int , std::map< G4double , ParticleHPVector* >* >* theTSCoherentCrossSections;
      std::map< G4int , std::map< G4double , ParticleHPVector* >* >* theTSIncoherentCrossSections;
      std::map< G4int , std::map< G4double , ParticleHPVector* >* >* theTSInelasticCrossSections;

      std::map< G4int , std::map< G4double , std::vector< std::pair< G4double , G4double >* >* >* >* theTSCoherentFinalStates;
      std::map< G4int , std::map< G4double , std::vector< E_isoAng* >* >* >* theTSIncoherentFinalStates;
      std::map< G4int , std::map< G4double , std::vector< E_P_E_isoAng* >* >* >* theTSInelasticFinalStates;

};
#endif
