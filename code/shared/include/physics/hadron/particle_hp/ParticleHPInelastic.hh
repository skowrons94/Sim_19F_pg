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
 // Hadronic Process: High Precision low E neutron tracking
 // original by H.P. Wellisch, TRIUMF, 14-Feb-97
 // Builds and has the Cross-section data for one material.
// P. Arce, June-2014 Conversion neutron_hp to particle_hp
//
#ifndef ParticleHPInelastic_h
#define ParticleHPInelastic_h 1

// Class Description
// Final state production model for a high precision (based on evaluated data
// libraries) description of neutron inelastic scattering below 20 MeV; 
// 36 exclusive final states are consideded.
// To be used in your physics list in case you need this physics.
// In this case you want to register an object of this class with 
// the corresponding process.
// Class Description - End

#include "globals.hh"
#include "ParticleHPChannel.hh"
#include "G4HadronicInteraction.hh"
#include "ParticleHPChannelList.hh"

/*
#include "ParticleHP2AInelasticFS.hh"
#include "ParticleHP2N2AInelasticFS.hh"
#include "ParticleHP2NAInelasticFS.hh"
#include "ParticleHP2NDInelasticFS.hh"
#include "ParticleHP2NInelasticFS.hh"
#include "ParticleHP2NPInelasticFS.hh"
#include "ParticleHP2PInelasticFS.hh"
#include "ParticleHP3AInelasticFS.hh"
#include "ParticleHP3NAInelasticFS.hh"
#include "ParticleHP3NInelasticFS.hh"
#include "ParticleHP3NPInelasticFS.hh"
#include "ParticleHP4NInelasticFS.hh"
#include "ParticleHPAInelasticFS.hh"
#include "ParticleHPD2AInelasticFS.hh"
#include "ParticleHPDAInelasticFS.hh"
#include "ParticleHPDInelasticFS.hh"
#include "ParticleHPHe3InelasticFS.hh"
#include "ParticleHPN2AInelasticFS.hh"
#include "ParticleHPN2PInelasticFS.hh"
#include "ParticleHPN3AInelasticFS.hh"
#include "ParticleHPNAInelasticFS.hh"
#include "ParticleHPND2AInelasticFS.hh"
#include "ParticleHPNDInelasticFS.hh"
#include "ParticleHPNHe3InelasticFS.hh"
#include "ParticleHPNInelasticFS.hh"
#include "ParticleHPNPAInelasticFS.hh"
#include "ParticleHPNPInelasticFS.hh"
#include "ParticleHPNT2AInelasticFS.hh"
#include "ParticleHPNTInelasticFS.hh"
#include "ParticleHPNXInelasticFS.hh"
#include "ParticleHPPAInelasticFS.hh"
#include "ParticleHPPDInelasticFS.hh"
#include "ParticleHPPInelasticFS.hh"
#include "ParticleHPPTInelasticFS.hh"
#include "ParticleHPT2AInelasticFS.hh"
#include "ParticleHPTInelasticFS.hh"
*/
#include "G4ParticleDefinition.hh"

class ParticleHPInelastic : public G4HadronicInteraction
{
  public: 

  ParticleHPInelastic(G4ParticleDefinition* projectile = G4Neutron::Neutron(), const char* name = "NeutronHPInelastic" );

  ~ParticleHPInelastic();
  
  G4HadFinalState * ApplyYourself(const G4HadProjectile & aTrack, G4Nucleus & aTargetNucleus);
  virtual const std::pair<G4double, G4double> GetFatalEnergyCheckLevels() const;

  public:
      G4int GetVerboseLevel() const;
      void SetVerboseLevel( G4int );
      void BuildPhysicsTable(const G4ParticleDefinition&);
      virtual void ModelDescription(std::ostream& outFile) const;

protected:
  
  //ParticleHPChannelList * theInelastic; // one List per element
  std::vector<ParticleHPChannelList*>* theInelastic; // one List per element
  G4String dataDirVariable;
  G4String dirName;
  G4int numEle;

  private:
 /* 
   ParticleHP2AInelasticFS the2AFS;
   ParticleHP2N2AInelasticFS the2N2AFS;
   ParticleHP2NAInelasticFS the2NAFS;
   ParticleHP2NDInelasticFS the2NDFS;
   ParticleHP2NInelasticFS the2NFS;
   ParticleHP2NPInelasticFS the2NPFS;
   ParticleHP2PInelasticFS the2PFS;
   ParticleHP3AInelasticFS the3AFS;
   ParticleHP3NAInelasticFS the3NAFS;
   ParticleHP3NInelasticFS the3NFS;
   ParticleHP3NPInelasticFS the3NPFS;
   ParticleHP4NInelasticFS the4NFS;
   ParticleHPAInelasticFS theAFS;
   ParticleHPD2AInelasticFS theD2AFS;
   ParticleHPDAInelasticFS theDAFS;
   ParticleHPDInelasticFS theDFS;
   ParticleHPHe3InelasticFS theHe3FS;
   ParticleHPN2AInelasticFS theN2AFS;
   ParticleHPN2PInelasticFS theN2PFS;
   ParticleHPN3AInelasticFS theN3AFS;
   ParticleHPNAInelasticFS theNAFS;
   ParticleHPND2AInelasticFS theND2AFS;
   ParticleHPNDInelasticFS theNDFS;
   ParticleHPNHe3InelasticFS theNHe3FS;
   ParticleHPNInelasticFS theNFS;
   ParticleHPNPAInelasticFS theNPAFS;
   ParticleHPNPInelasticFS theNPFS;
   ParticleHPNT2AInelasticFS theNT2AFS;
   ParticleHPNTInelasticFS theNTFS;
   ParticleHPNXInelasticFS theNXFS;
   ParticleHPPAInelasticFS thePAFS;
   ParticleHPPDInelasticFS thePDFS;
   ParticleHPPInelasticFS thePFS;
   ParticleHPPTInelasticFS thePTFS;
   ParticleHPT2AInelasticFS theT2AFS;
   ParticleHPTInelasticFS theTFS;
*/

   G4ParticleDefinition* theProjectile;

};

#endif
