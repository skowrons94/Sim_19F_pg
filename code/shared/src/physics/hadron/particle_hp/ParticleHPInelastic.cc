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
// this code implementation is the intellectual property of
// neutron_hp -- source file
// J.P. Wellisch, Nov-1996
// A prototype of the low energy neutron transport model.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
//
// 070523 bug fix for G4FPE_DEBUG on by A. Howard (and T. Koi)
// 081203 limit maximum trial for creating final states add protection for 1H isotope case by T. Koi
//
// P. Arce, June-2014 Conversion neutron_hp to particle_hp
//
#include "ParticleHPInelastic.hh"
#include "G4SystemOfUnits.hh"
#include "ParticleHPManager.hh"
#include "G4HadronicParameters.hh"
#include "G4Threading.hh"

ParticleHPInelastic::ParticleHPInelastic(G4ParticleDefinition* projectile, const char* name )
  :G4HadronicInteraction(name)
  ,theInelastic(NULL)
  ,numEle(0)
  ,theProjectile(projectile)
{
    G4String baseName; 
    if ( std::getenv("G4PARTICLEHPDATA") ) {
      baseName = std::getenv( "G4PARTICLEHPDATA" );
    }
    //const char* dataDirVariable;
    G4String particleName;
    if ( theProjectile == G4Neutron::Neutron() ) {
      dataDirVariable = "G4NEUTRONHPDATA";
    } else if( theProjectile == G4Proton::Proton() ) {
      dataDirVariable = "G4PROTONHPDATA";
      particleName = "Proton";
    } else if( theProjectile == G4Deuteron::Deuteron() ) {
      dataDirVariable = "G4DEUTERONHPDATA";
      particleName = "Deuteron";
    } else if( theProjectile == G4Triton::Triton() ) {
      dataDirVariable = "G4TRITONHPDATA";
      particleName = "Triton";
    } else if( theProjectile == G4He3::He3() ) {
      dataDirVariable = "G4HE3HPDATA";
      particleName = "He3";
    } else if( theProjectile == G4Alpha::Alpha() ) {
      dataDirVariable = "G4ALPHAHPDATA";
      particleName = "Alpha";
    } else if( theProjectile == G4IonTable::GetIonTable()->GetIon(6, 12, 0.) ) {
      dataDirVariable = "G4C12HPDATA";
      particleName = "C12";
    } else {
      G4String message("ParticleHPInelastic may only be called for neutron, proton, deuteron, triton, He3 or alpha, while it is called for " + theProjectile->GetParticleName());
      throw G4HadronicException(__FILE__, __LINE__,message.c_str());
    }

    SetMinEnergy( 0.0 );
    SetMaxEnergy( 20.*MeV );

    //G4cout << " entering ParticleHPInelastic constructor"<<G4endl;
    if ( !std::getenv("G4PARTICLEHPDATA") && !std::getenv(dataDirVariable) ) {
      G4String message("Please setenv G4PARTICLEHPDATA (recommended) or, at least setenv " +
		       G4String(dataDirVariable) + " to point to the " + theProjectile->GetParticleName() + " cross-section files." );      
      throw G4HadronicException(__FILE__, __LINE__,message.c_str());
    }
    if ( std::getenv(dataDirVariable) ) {
      dirName = std::getenv(dataDirVariable);
    } else {
      dirName = baseName + "/" + particleName;
    }
    
    #ifdef G4VERBOSE
    if ( G4HadronicParameters::Instance()->GetVerboseLevel() > 0 ) G4cout << dirName << G4endl;
    #endif
    
    G4String tString = "/Inelastic";
    dirName = dirName + tString;
    //numEle = G4Element::GetNumberOfElements();

    #ifdef G4VERBOSE
    if ( G4HadronicParameters::Instance()->GetVerboseLevel() > 0 )
      G4cout << "@@@ ParticleHPInelastic instantiated for particle " << theProjectile->GetParticleName() << " data directory variable is " << dataDirVariable << " pointing to " << dirName << G4endl;
    #endif

/*
    theInelastic = new ParticleHPChannelList[numEle];
    for (G4int i=0; i<numEle; i++)
    { 
      theInelastic[i].Init((*(G4Element::GetElementTable()))[i], dirName);
      G4int itry = 0;
      do
      {
	theInelastic[i].Register(&theNFS, "F01"); // has
	theInelastic[i].Register(&theNXFS, "F02");
	theInelastic[i].Register(&the2NDFS, "F03");
 	theInelastic[i].Register(&the2NFS, "F04"); // has, E Done
 	theInelastic[i].Register(&the3NFS, "F05"); // has, E Done
  	theInelastic[i].Register(&theNAFS, "F06");
	theInelastic[i].Register(&theN3AFS, "F07");
	theInelastic[i].Register(&the2NAFS, "F08");
	theInelastic[i].Register(&the3NAFS, "F09");
	theInelastic[i].Register(&theNPFS, "F10");
	theInelastic[i].Register(&theN2AFS, "F11");
	theInelastic[i].Register(&the2N2AFS, "F12");
	theInelastic[i].Register(&theNDFS, "F13");
	theInelastic[i].Register(&theNTFS, "F14");
	theInelastic[i].Register(&theNHe3FS, "F15");
	theInelastic[i].Register(&theND2AFS, "F16");
	theInelastic[i].Register(&theNT2AFS, "F17");
	theInelastic[i].Register(&the4NFS, "F18"); // has, E Done
	theInelastic[i].Register(&the2NPFS, "F19");
	theInelastic[i].Register(&the3NPFS, "F20");
	theInelastic[i].Register(&theN2PFS, "F21");
	theInelastic[i].Register(&theNPAFS, "F22");
  	theInelastic[i].Register(&thePFS, "F23");
	theInelastic[i].Register(&theDFS, "F24");
	theInelastic[i].Register(&theTFS, "F25");
	theInelastic[i].Register(&theHe3FS, "F26");
	theInelastic[i].Register(&theAFS, "F27");
	theInelastic[i].Register(&the2AFS, "F28");
	theInelastic[i].Register(&the3AFS, "F29");
	theInelastic[i].Register(&the2PFS, "F30");
	theInelastic[i].Register(&thePAFS, "F31");
	theInelastic[i].Register(&theD2AFS, "F32");
	theInelastic[i].Register(&theT2AFS, "F33");
	theInelastic[i].Register(&thePDFS, "F34");
	theInelastic[i].Register(&thePTFS, "F35");
	theInelastic[i].Register(&theDAFS, "F36");
	theInelastic[i].RestartRegistration();
        itry++;
      }
      //while(!theInelastic[i].HasDataInAnyFinalState());
      while( !theInelastic[i].HasDataInAnyFinalState() && itry < 6 );
                                                              // 6 is corresponding to the value(5) of ParticleHPChannel. TK  

      if ( itry == 6 ) 
      {
         // No Final State at all.
         G4bool exceptional = false;
         if ( (*(G4Element::GetElementTable()))[i]->GetNumberOfIsotopes() == 1 )
         {
            if ( (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetZ() == 1 && (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetN() == 1 ) exceptional = true;  //1H
         } 
         if ( !exceptional ) throw G4HadronicException(__FILE__, __LINE__, "Channel: Do not know what to do with this element");
      }
    }
*/
/*
    for (G4int i=0; i<numEle; i++)
    { 
      theInelastic.push_back( new ParticleHPChannelList );
      (*theInelastic[i]).Init((*(G4Element::GetElementTable()))[i], dirName, theProjectile);
      G4int itry = 0;
      do
      {
	(*theInelastic[i]).Register(&theNFS, "F01"); // has
	(*theInelastic[i]).Register(&theNXFS, "F02");
	(*theInelastic[i]).Register(&the2NDFS, "F03");
 	(*theInelastic[i]).Register(&the2NFS, "F04"); // has, E Done
 	(*theInelastic[i]).Register(&the3NFS, "F05"); // has, E Done
  	(*theInelastic[i]).Register(&theNAFS, "F06");
	(*theInelastic[i]).Register(&theN3AFS, "F07");
	(*theInelastic[i]).Register(&the2NAFS, "F08");
	(*theInelastic[i]).Register(&the3NAFS, "F09");
	(*theInelastic[i]).Register(&theNPFS, "F10");
	(*theInelastic[i]).Register(&theN2AFS, "F11");
	(*theInelastic[i]).Register(&the2N2AFS, "F12");
	(*theInelastic[i]).Register(&theNDFS, "F13");
	(*theInelastic[i]).Register(&theNTFS, "F14");
	(*theInelastic[i]).Register(&theNHe3FS, "F15");
	(*theInelastic[i]).Register(&theND2AFS, "F16");
	(*theInelastic[i]).Register(&theNT2AFS, "F17");
	(*theInelastic[i]).Register(&the4NFS, "F18"); // has, E Done
	(*theInelastic[i]).Register(&the2NPFS, "F19");
	(*theInelastic[i]).Register(&the3NPFS, "F20");
	(*theInelastic[i]).Register(&theN2PFS, "F21");
	(*theInelastic[i]).Register(&theNPAFS, "F22");
  	(*theInelastic[i]).Register(&thePFS, "F23");
	(*theInelastic[i]).Register(&theDFS, "F24");
	(*theInelastic[i]).Register(&theTFS, "F25");
	(*theInelastic[i]).Register(&theHe3FS, "F26");
	(*theInelastic[i]).Register(&theAFS, "F27");
	(*theInelastic[i]).Register(&the2AFS, "F28");
	(*theInelastic[i]).Register(&the3AFS, "F29");
	(*theInelastic[i]).Register(&the2PFS, "F30");
	(*theInelastic[i]).Register(&thePAFS, "F31");
	(*theInelastic[i]).Register(&theD2AFS, "F32");
	(*theInelastic[i]).Register(&theT2AFS, "F33");
	(*theInelastic[i]).Register(&thePDFS, "F34");
	(*theInelastic[i]).Register(&thePTFS, "F35");
	(*theInelastic[i]).Register(&theDAFS, "F36");
	(*theInelastic[i]).RestartRegistration();
        itry++;
      }
      while( !(*theInelastic[i]).HasDataInAnyFinalState() && itry < 6 );
                                                              // 6 is corresponding to the value(5) of ParticleHPChannel. TK  

      if ( itry == 6 ) 
      {
         // No Final State at all.
         G4bool exceptional = false;
         if ( (*(G4Element::GetElementTable()))[i]->GetNumberOfIsotopes() == 1 )
         {
            if ( (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetZ() == 1 && (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetN() == 1 ) exceptional = true;  //1H
         } 
	 if ( !exceptional ) {
 	 G4cerr << " ELEMENT Z " << (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetZ() << " N " << (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetN() << G4endl;  //1H
throw G4HadronicException(__FILE__, __LINE__, "Channel: Do not know what to do with this element");
	 }
      }

    }
*/

  }

  ParticleHPInelastic::~ParticleHPInelastic()
  {
//    delete [] theInelastic;
    //Vector is shared, only master deletes
    if ( !G4Threading::IsWorkerThread() ) {
        if ( theInelastic != NULL ) {
            for ( std::vector<ParticleHPChannelList*>::iterator
                it = theInelastic->begin() ; it != theInelastic->end() ; it++ ) {
                delete *it;
            }
            theInelastic->clear();
        }
     }
  }
  
  #include "ParticleHPThermalBoost.hh"
  
  G4HadFinalState * ParticleHPInelastic::ApplyYourself(const G4HadProjectile& aTrack, G4Nucleus& aNucleus )
  {
    ParticleHPManager::GetInstance()->OpenReactionWhiteBoard();
    const G4Material * theMaterial = aTrack.GetMaterial();
    G4int n = theMaterial->GetNumberOfElements();
    G4int index = theMaterial->GetElement(0)->GetIndex();
    G4int it=0;
    if(n!=1)
    {
      G4double* xSec = new G4double[n];
      G4double sum=0;
      G4int i;
      const G4double * NumAtomsPerVolume = theMaterial->GetVecNbOfAtomsPerVolume();
      G4double rWeight;    
      ParticleHPThermalBoost aThermalE;
      for (i=0; i<n; i++)
      {
        index = theMaterial->GetElement(i)->GetIndex();
        rWeight = NumAtomsPerVolume[i];
	if ( aTrack.GetDefinition() == G4Neutron::Neutron() ) {
	  xSec[i] = ((*theInelastic)[index])->GetXsec(aThermalE.GetThermalEnergy(aTrack,
									      theMaterial->GetElement(i),
									      theMaterial->GetTemperature()));
	} else {
	  xSec[i] = ((*theInelastic)[index])->GetXsec(aTrack.GetKineticEnergy());
	}
        xSec[i] *= rWeight;
        sum+=xSec[i];
#ifdef G4PHPDEBUG
	#ifdef G4VERBOSE
	if( std::getenv("ParticleHPDebug") && G4HadronicParameters::Instance()->GetVerboseLevel() > 0 )
	  G4cout << " ParticleHPInelastic XSEC ELEM " << i << " = " << xSec[i] << G4endl;
	#endif
#endif

      }
      G4double random = G4UniformRand();
      G4double running = 0;
      for (i=0; i<n; i++)
      {
        running += xSec[i];
        index = theMaterial->GetElement(i)->GetIndex();
        it = i;
        //if(random<=running/sum) break;
        if( sum == 0 || random<=running/sum) break;
      }
      delete [] xSec;
    }

#ifdef G4PHPDEBUG
    #ifdef G4VERBOSE
    if( std::getenv("ParticleHPDebug") && G4HadronicParameters::Instance()->GetVerboseLevel() > 0 )
      G4cout << " ParticleHPInelastic SELECTED ELEM " << it << " = " << theMaterial->GetElement(it)->GetName() << " FROM MATERIAL " << theMaterial->GetName() << G4endl;
    #endif
#endif
    //return theInelastic[index].ApplyYourself(theMaterial->GetElement(it), aTrack);
    G4HadFinalState* result = ((*theInelastic)[index])->ApplyYourself(theMaterial->GetElement(it), aTrack);
    //
    aNucleus.SetParameters(ParticleHPManager::GetInstance()->GetReactionWhiteBoard()->GetTargA(),ParticleHPManager::GetInstance()->GetReactionWhiteBoard()->GetTargZ());
    const G4Element* target_element = (*G4Element::GetElementTable())[index];
    const G4Isotope* target_isotope=NULL;
    G4int iele = target_element->GetNumberOfIsotopes();
    for ( G4int j = 0 ; j != iele ; j++ ) { 
       target_isotope=target_element->GetIsotope( j );
       if ( target_isotope->GetN() == ParticleHPManager::GetInstance()->GetReactionWhiteBoard()->GetTargA() ) break; 
    }
    //G4cout << "Target Material of this reaction is " << theMaterial->GetName() << G4endl;
    //G4cout << "Target Element of this reaction is " << target_element->GetName() << G4endl;
    //G4cout << "Target Isotope of this reaction is " << target_isotope->GetName() << G4endl;
    aNucleus.SetIsotope( target_isotope );

    ParticleHPManager::GetInstance()->CloseReactionWhiteBoard();

    //GDEB
    if( std::getenv("G4PHPTEST") ) {
      G4HadSecondary* seco = result->GetSecondary(0);
      if(seco) {
	G4ThreeVector secoMom =  seco->GetParticle()->GetMomentum();
	#ifdef G4VERBOSE
	if ( G4HadronicParameters::Instance()->GetVerboseLevel() > 0 )
	  G4cout << " ParticleHPinelastic COS THETA " << std::cos(secoMom.theta()) <<" " << secoMom << G4endl;
	#endif
      }
    }

    return result;
  }

const std::pair<G4double, G4double> ParticleHPInelastic::GetFatalEnergyCheckLevels() const
{
      // max energy non-conservation is mass of heavy nucleus
      // This should be same to the hadron default value
      return std::pair<G4double, G4double>(10*perCent,DBL_MAX);
}

/*
void ParticleHPInelastic::addChannelForNewElement()
{
   for ( G4int i = numEle ; i < (G4int)G4Element::GetNumberOfElements() ; i++ ) 
   {
      G4cout << "ParticleHPInelastic Prepairing Data for the new element of " << (*(G4Element::GetElementTable()))[i]->GetName() << G4endl;

      theInelastic.push_back( new ParticleHPChannelList );
      (*theInelastic[i]).Init((*(G4Element::GetElementTable()))[i], dirName, theProjectile);
      G4int itry = 0;
      do
      {
         (*theInelastic[i]).Register(&theNFS, "F01"); // has
         (*theInelastic[i]).Register(&theNXFS, "F02");
         (*theInelastic[i]).Register(&the2NDFS, "F03");
         (*theInelastic[i]).Register(&the2NFS, "F04"); // has, E Done
         (*theInelastic[i]).Register(&the3NFS, "F05"); // has, E Done
         (*theInelastic[i]).Register(&theNAFS, "F06");
         (*theInelastic[i]).Register(&theN3AFS, "F07");
         (*theInelastic[i]).Register(&the2NAFS, "F08");
         (*theInelastic[i]).Register(&the3NAFS, "F09");
         (*theInelastic[i]).Register(&theNPFS, "F10");
         (*theInelastic[i]).Register(&theN2AFS, "F11");
         (*theInelastic[i]).Register(&the2N2AFS, "F12");
         (*theInelastic[i]).Register(&theNDFS, "F13");
         (*theInelastic[i]).Register(&theNTFS, "F14");
         (*theInelastic[i]).Register(&theNHe3FS, "F15");
         (*theInelastic[i]).Register(&theND2AFS, "F16");
         (*theInelastic[i]).Register(&theNT2AFS, "F17");
         (*theInelastic[i]).Register(&the4NFS, "F18"); // has, E Done
         (*theInelastic[i]).Register(&the2NPFS, "F19");
         (*theInelastic[i]).Register(&the3NPFS, "F20");
         (*theInelastic[i]).Register(&theN2PFS, "F21");
         (*theInelastic[i]).Register(&theNPAFS, "F22");
         (*theInelastic[i]).Register(&thePFS, "F23");
         (*theInelastic[i]).Register(&theDFS, "F24");
         (*theInelastic[i]).Register(&theTFS, "F25");
         (*theInelastic[i]).Register(&theHe3FS, "F26");
         (*theInelastic[i]).Register(&theAFS, "F27");
         (*theInelastic[i]).Register(&the2AFS, "F28");
         (*theInelastic[i]).Register(&the3AFS, "F29");
         (*theInelastic[i]).Register(&the2PFS, "F30");
         (*theInelastic[i]).Register(&thePAFS, "F31");
         (*theInelastic[i]).Register(&theD2AFS, "F32");
         (*theInelastic[i]).Register(&theT2AFS, "F33");
         (*theInelastic[i]).Register(&thePDFS, "F34");
         (*theInelastic[i]).Register(&thePTFS, "F35");
         (*theInelastic[i]).Register(&theDAFS, "F36");
         (*theInelastic[i]).RestartRegistration();
         itry++;
      }
      while( !(*theInelastic[i]).HasDataInAnyFinalState() && itry < 6 );
                                                                  // 6 is corresponding to the value(5) of ParticleHPChannel. TK  

      if ( itry == 6 ) 
      {
         // No Final State at all.
         G4bool exceptional = false;
         if ( (*(G4Element::GetElementTable()))[i]->GetNumberOfIsotopes() == 1 )
         {
            if ( (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetZ() == 1 && (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetN() == 1 ) exceptional = true;  //1H
         } 
         if ( !exceptional ) throw G4HadronicException(__FILE__, __LINE__, "Channel: Do not know what to do with this element");
      }
   }

   numEle = (G4int)G4Element::GetNumberOfElements();
}
*/
G4int ParticleHPInelastic::GetVerboseLevel() const
{
   return ParticleHPManager::GetInstance()->GetVerboseLevel();
}
void ParticleHPInelastic::SetVerboseLevel( G4int newValue ) 
{
   ParticleHPManager::GetInstance()->SetVerboseLevel(newValue);
}

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

void ParticleHPInelastic::BuildPhysicsTable(const G4ParticleDefinition& projectile) {

   ParticleHPManager* hpmanager = ParticleHPManager::GetInstance();

   theInelastic = hpmanager->GetInelasticFinalStates( &projectile );

   if ( G4Threading::IsMasterThread() ) {

      if ( theInelastic == NULL ) theInelastic = new std::vector<ParticleHPChannelList*>;

      if ( numEle == (G4int)G4Element::GetNumberOfElements() ) return;

      if ( theInelastic->size() == G4Element::GetNumberOfElements() ) {
         numEle = G4Element::GetNumberOfElements();
         return;
      }
/*
      const char* dataDirVariable;
      if( &projectile == G4Neutron::Neutron() ) {
        dataDirVariable = "G4NEUTRONHPDATA";
      }else if( &projectile == G4Proton::Proton() ) {
        dataDirVariable = "G4PROTONHPDATA";
      }else if( &projectile == G4Deuteron::Deuteron() ) {
        dataDirVariable = "G4DEUTERONHPDATA";
      }else if( &projectile == G4Triton::Triton() ) {
        dataDirVariable = "G4TRITONHPDATA";
      }else if( &projectile == G4He3::He3() ) {
        dataDirVariable = "G4HE3HPDATA";
      }else if( &projectile == G4Alpha::Alpha() ) {
        dataDirVariable = "G4ALPHAHPDATA";
      } else {
         G4String message("ParticleHPInelastic may only be called for neutron, proton, deuteron, triton, He3 or alpha, while it is called for " + projectile.GetParticleName());
         throw G4HadronicException(__FILE__, __LINE__,message.c_str());
      }
      if(!std::getenv(dataDirVariable)){
         G4String message("Please set the environment variable " + G4String(dataDirVariable) + " to point to the " + projectile.GetParticleName() + " cross-section files.");
         throw G4HadronicException(__FILE__, __LINE__,message.c_str());
      }
      dirName = std::getenv(dataDirVariable);
      G4cout << dirName << G4endl;

      G4String tString = "/Inelastic";
      dirName = dirName + tString;

*/
      #ifdef G4VERBOSE
      if ( G4HadronicParameters::Instance()->GetVerboseLevel() > 0 ) {
	hpmanager->DumpSetting();
	G4cout << "@@@ ParticleHPInelastic instantiated for particle " << projectile.GetParticleName() << " data directory variable is " << dataDirVariable << " pointing to " << dirName << G4endl;
      }
      #endif
      for (G4int i = numEle ; i < (G4int)G4Element::GetNumberOfElements(); i++)
      {
        theInelastic->push_back( new ParticleHPChannelList );
        ((*theInelastic)[i])->Init((*(G4Element::GetElementTable()))[i], dirName, const_cast<G4ParticleDefinition*>(&projectile));
        G4int itry = 0;
        do
        {
          ((*theInelastic)[i])->Register( new ParticleHPNInelasticFS , "F01"); // has
          ((*theInelastic)[i])->Register( new ParticleHPNXInelasticFS , "F02");
          ((*theInelastic)[i])->Register( new ParticleHP2NDInelasticFS , "F03");
          ((*theInelastic)[i])->Register( new ParticleHP2NInelasticFS , "F04"); // has, E Done
          ((*theInelastic)[i])->Register( new ParticleHP3NInelasticFS , "F05"); // has, E Done
          ((*theInelastic)[i])->Register( new ParticleHPNAInelasticFS , "F06");
          ((*theInelastic)[i])->Register( new ParticleHPN3AInelasticFS , "F07");
          ((*theInelastic)[i])->Register( new ParticleHP2NAInelasticFS , "F08");
          ((*theInelastic)[i])->Register( new ParticleHP3NAInelasticFS , "F09");
          ((*theInelastic)[i])->Register( new ParticleHPNPInelasticFS , "F10");
          ((*theInelastic)[i])->Register( new ParticleHPN2AInelasticFS , "F11");
          ((*theInelastic)[i])->Register( new ParticleHP2N2AInelasticFS , "F12");
          ((*theInelastic)[i])->Register( new ParticleHPNDInelasticFS , "F13");
          ((*theInelastic)[i])->Register( new ParticleHPNTInelasticFS , "F14");
          ((*theInelastic)[i])->Register( new ParticleHPNHe3InelasticFS , "F15");
          ((*theInelastic)[i])->Register( new ParticleHPND2AInelasticFS , "F16");
          ((*theInelastic)[i])->Register( new ParticleHPNT2AInelasticFS , "F17");
          ((*theInelastic)[i])->Register( new ParticleHP4NInelasticFS , "F18"); // has, E Done
          ((*theInelastic)[i])->Register( new ParticleHP2NPInelasticFS , "F19");
          ((*theInelastic)[i])->Register( new ParticleHP3NPInelasticFS , "F20");
          ((*theInelastic)[i])->Register( new ParticleHPN2PInelasticFS , "F21");
          ((*theInelastic)[i])->Register( new ParticleHPNPAInelasticFS , "F22");
          ((*theInelastic)[i])->Register( new ParticleHPPInelasticFS , "F23");
          ((*theInelastic)[i])->Register( new ParticleHPDInelasticFS , "F24");
          ((*theInelastic)[i])->Register( new ParticleHPTInelasticFS , "F25");
          ((*theInelastic)[i])->Register( new ParticleHPHe3InelasticFS , "F26");
          ((*theInelastic)[i])->Register( new ParticleHPAInelasticFS , "F27");
          ((*theInelastic)[i])->Register( new ParticleHP2AInelasticFS , "F28");
          ((*theInelastic)[i])->Register( new ParticleHP3AInelasticFS , "F29");
          ((*theInelastic)[i])->Register( new ParticleHP2PInelasticFS , "F30");
          ((*theInelastic)[i])->Register( new ParticleHPPAInelasticFS , "F31");
          ((*theInelastic)[i])->Register( new ParticleHPD2AInelasticFS , "F32");
          ((*theInelastic)[i])->Register( new ParticleHPT2AInelasticFS , "F33");
          ((*theInelastic)[i])->Register( new ParticleHPPDInelasticFS , "F34");
          ((*theInelastic)[i])->Register( new ParticleHPPTInelasticFS , "F35");
          ((*theInelastic)[i])->Register( new ParticleHPDAInelasticFS , "F36");
          ((*theInelastic)[i])->RestartRegistration();
          itry++;
        }
        while( !((*theInelastic)[i])->HasDataInAnyFinalState() && itry < 6 ); // Loop checking, 11.05.2015, T. Koi
                                                              // 6 is corresponding to the value(5) of ParticleHPChannel. TK  

        if ( itry == 6 ) {
           // No Final State at all.
           /*
           G4bool exceptional = false;
           if ( (*(G4Element::GetElementTable()))[i]->GetNumberOfIsotopes() == 1 )
           {
              if ( (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetZ() == 1 && (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetN() == 1 ) exceptional = true;  //1H
           } 
	   if ( !exceptional ) {
 	      G4cerr << " ELEMENT Z " << (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetZ() << " N " << (*(G4Element::GetElementTable()))[i]->GetIsotope( 0 )->GetN() << G4endl;  //1H
              throw G4HadronicException(__FILE__, __LINE__, "Channel: Do not know what to do with this element");
	   }
           */
	   #ifdef G4VERBOSE
           if ( ParticleHPManager::GetInstance()->GetVerboseLevel() > 1 &&
		G4HadronicParameters::Instance()->GetVerboseLevel() > 0 ) {
              G4cout << "ParticleHP::Inelastic for " << projectile.GetParticleName() << ". Do not know what to do with element of \"" << (*(G4Element::GetElementTable()))[i]->GetName() << "\"." << G4endl;
              G4cout << "The components of the element are" << G4endl;
 	      //G4cout << "TKDB dataDirVariable = " << dataDirVariable << G4endl;
              for ( G4int ii = 0 ; ii < (G4int)( (*(G4Element::GetElementTable()))[i]->GetNumberOfIsotopes() ) ; ii++ ) { 
 	          G4cout << " Z: " << (*(G4Element::GetElementTable()))[i]->GetIsotope( ii )->GetZ() << ", A: " << (*(G4Element::GetElementTable()))[i]->GetIsotope( ii )->GetN() << G4endl;
              }
              G4cout << "No possible final state data of the element is found in " << dataDirVariable << "." << G4endl;
           }
	   #endif
        }
      }
      hpmanager->RegisterInelasticFinalStates( &projectile , theInelastic );
   }
   numEle = G4Element::GetNumberOfElements();
}

void ParticleHPInelastic::ModelDescription(std::ostream& outFile) const
{
   outFile << "Extension of High Precision model for inelastic reaction of proton, deuteron, triton, He3 and alpha below 20MeV\n";
}

