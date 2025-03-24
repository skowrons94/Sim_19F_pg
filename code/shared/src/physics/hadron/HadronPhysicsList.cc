#include "HadronPhysicsList.hh"

#include "G4SystemOfUnits.hh"

#include "G4HadronInelasticProcess.hh"
#include "G4HadronicInteraction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"

#include "G4BGGNucleonInelasticXS.hh"
#include "G4BGGPionInelasticXS.hh"

#include "ParticleInelasticXS.hh"
#include "G4IonPhysicsXS.hh"
#include "G4NeutronInelasticXS.hh"
//#include "G4NeutronHPInelasticData.hh"
//#include "G4NeutronHPInelastic.hh"
//#include "G4NeutronHPCaptureData.hh"
//#include "G4NeutronHPCapture.hh"
#include "NeutronHPInelasticData.hh"
#include "NeutronHPInelastic.hh"
#include "NeutronHPCaptureData.hh"
#include "NeutronHPCapture.hh"

#include "ParticleCaptureXS.hh"
#include "ParticleResonantCaptureXS.hh"
#include "G4NeutronRadCapture.hh"
#include "G4NeutronCaptureProcess.hh"
#include "ParticleRadCapture.hh"
#include "ParticleCaptureProcess.hh"
#include "ParticleResRadCapture.hh"
#include "ParticleResonantCaptureProcess.hh"

#include "ParticleHPInelastic.hh"
#include "ParticleHPInelasticData.hh"

#include "G4CrossSectionInelastic.hh"
//#include "G4PiNuclearCrossSection.hh"
#include "G4ComponentAntiNuclNuclearXS.hh"
//#include "G4CrossSectionPairGG.hh"

#include "G4QGSBuilder.hh"
#include "G4FTFBuilder.hh"

#include "G4ComponentGGHadronNucleusXsc.hh"
#include "G4ChipsHyperonInelasticXS.hh"
#include "G4CrossSectionDataSetRegistry.hh"

#include "G4CascadeInterface.hh"
#include "G4BinaryCascade.hh"
#include "G4BinaryLightIonReaction.hh"

#include "G4PreCompoundModel.hh"
#include "G4ExcitationHandler.hh"
#include "G4Evaporation.hh"
#include "G4HadronicInteractionRegistry.hh"

#include "G4HadronicParameters.hh"

#include "HadronPhysicsListMessenger.hh"
#include "IonC12.hh"

// factory
#include "G4PhysicsConstructorFactory.hh"
//
G4_DECLARE_PHYSCONSTR_FACTORY(HadronPhysicsList);

HadronPhysicsList::HadronPhysicsList(G4int ver) 
  : HadronPhysics("hInelasticQBBC"),verbose(ver)
{
  hadronPhysicsListMessenger = new HadronPhysicsListMessenger(this);
}

HadronPhysicsList::HadronPhysicsList(const G4String&, G4int ver, 
				     G4bool, G4bool,G4bool, G4bool, G4bool) : HadronPhysicsList(ver)
{
  hadronPhysicsListMessenger = new HadronPhysicsListMessenger(this);
}

HadronPhysicsList::~HadronPhysicsList()
{
  delete hadronPhysicsListMessenger;
}

void HadronPhysicsList::ConstructProcess()
{
  if(verbose > 1) {
    G4cout << "### HadronPhysicsList Construct Process " << G4endl;
  }

  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  G4double emax = G4HadronicParameters::Instance()->GetMaxEnergy();

  //G4cout << "HadronPhysicsList::ConstructProcess new PRECO"<< G4endl;

  // PreCompound and Evaporation models are instantiated here
  G4PreCompoundModel* thePreCompound = nullptr;
  G4HadronicInteraction* p =
    G4HadronicInteractionRegistry::Instance()->FindModel("PRECO");
  thePreCompound = static_cast<G4PreCompoundModel*>(p);
  if(!thePreCompound) { thePreCompound = new G4PreCompoundModel(); }
 
  // configure models
  //G4HadronicInteraction* theQGSP = 
  //  BuildModel(new G4QGSBuilder("QGSP",thePreCompound,true,false),12.5*GeV,emax);
  G4HadronicInteraction* theFTFP = 
    BuildModel(new G4FTFBuilder("FTFP",thePreCompound),3.0*GeV,emax);
  G4HadronicInteraction* theFTFP1 = 
    BuildModel(new G4FTFBuilder("FTFP",thePreCompound),3.0*GeV,emax);
  G4HadronicInteraction* theFTFP2 = 
    BuildModel(new G4FTFBuilder("FTFP",thePreCompound),0.0,emax);
  G4HadronicInteraction* theFTFP3 =
    BuildModel(new G4FTFBuilder("FTFP",thePreCompound),19.0*MeV,emax);

  G4CascadeInterface* casc = new G4CascadeInterface();
  casc->usePreCompoundDeexcitation();
  G4HadronicInteraction* theBERT = NewModel(casc,1.0*GeV,5.0*GeV);

  casc = new G4CascadeInterface();
  //casc->usePreCompoundDeexcitation();
  casc->useCascadeDeexcitation();
  G4HadronicInteraction* theBERT1 = NewModel(casc,0.0*GeV,5.0*GeV);

  //G4cout << "HadronPhysicsList::ConstructProcess new Binary"<< G4endl;
  G4BinaryCascade* bic = new G4BinaryCascade(thePreCompound);
  G4HadronicInteraction* theBIC = NewModel(bic,0.0,1.5*GeV);

  G4BinaryLightIonReaction* ionbic = new G4BinaryLightIonReaction(thePreCompound);
  G4HadronicInteraction* theIonBIC = NewModel(ionbic,20.0*MeV,1.5*GeV);
  //G4HadronicInteraction* theIonBIC = NewModel(ionbic,20.0,1.5*GeV);
  //theIonBIC->SetDeExcitation(casc);

  // cross sections
  G4CrossSectionInelastic* anucxs = InelasticXS("AntiAGlauber");
  if(!anucxs) { 
    anucxs = new G4CrossSectionInelastic(new G4ComponentAntiNuclNuclearXS());
  }
  G4CrossSectionInelastic* kaonxs = 
    InelasticXS(G4ComponentGGHadronNucleusXsc::Default_Name());
  if(!kaonxs) { 
    kaonxs = new G4CrossSectionInelastic(new G4ComponentGGHadronNucleusXsc());
  }

  G4HadronicProcess* hp;
  G4HadronicProcess* capture;
  G4HadronicProcess* particlecapture;

  // inelastic channel for C12
  //G4ParticleDefinition* ionC12 = G4IonTable::GetIonTable()->GetIon(6, 12, 0.);
  if(InelFlagC12==true) {
    //hp = FindInelasticProcess(ionC12);
    hp = FindInelasticProcess(IonC12::theIonC12());
    
    if(HPinelFlagC12==true) {
      
      // HPInelastic cross section
      //hp->AddDataSet(new ParticleHPInelasticData(ionC12));
      
      // ParticleInelasticXS cross section
      //hp->AddDataSet(new ParticleInelasticXS(ionC12));
      hp->AddDataSet(new ParticleInelasticXS(IonC12::theIonC12()));
      
      // HPInelastic model
      //ParticleHPInelastic* partInelHP = new ParticleHPInelastic(ionC12,"HPinelastic");
      ParticleHPInelastic* partInelHP = new ParticleHPInelastic(IonC12::theIonC12(),"HPinelastic");
      partInelHP->SetVerboseLevel(1);
      hp->RegisterMe(partInelHP);
    }
    else hp->RegisterMe(theBERT1);
  }
  
  // *** ParticleCapture model and cross section for C12*** //
  if(PartCapFlag==true) {
    if(PartCapType=="non-resonant") {
      particlecapture = FindParticleCaptureProcess(IonC12::theIonC12());
      ParticleRadCapture *captureModel = new ParticleRadCapture();
      captureModel->InitialiseModel();
      particlecapture->RegisterMe(captureModel);
      particlecapture->AddDataSet(new ParticleCaptureXS(IonC12::theIonC12()));
    }
    else if(PartCapType=="resonant") {
      particlecapture = FindParticleCaptureProcess(IonC12::theIonC12());
      ParticleResRadCapture *resCaptureModel = new ParticleResRadCapture();
      resCaptureModel->InitialiseModel();
      particlecapture->RegisterMe(resCaptureModel);
      particlecapture->AddDataSet(new ParticleResonantCaptureXS(IonC12::theIonC12()));
    }
  }
  
  // loop over particles
  auto myParticleIterator=GetParticleIterator();
  myParticleIterator->reset();
  while( (*myParticleIterator)() ) {
    G4ParticleDefinition* particle = myParticleIterator->value();
    G4String pname = particle->GetParticleName();
    if(verbose > 1) { 
      G4cout << "### HadronPhysicsList:  " << pname << G4endl; 
    }
    
    //
    // model and X-section configuration per particle type
    //

    if(pname == "proton" || pname == "deuteron"
       || pname == "triton" || pname == "He3"
       || pname == "alpha") {
      
      // inelastic channel for proton
      if(pname=="proton" && InelFlagProt==true) {
	hp = FindInelasticProcess(particle);

	if(HPinelFlagProt==true) {

	  // HPInelastic cross section
	  //hp->AddDataSet(new ParticleHPInelasticData(particle));

	  // ParticleInelasticXS cross section
	  hp->AddDataSet(new ParticleInelasticXS(particle));

	  // HPInelastic model
	  ParticleHPInelastic* partInelHP = new ParticleHPInelastic(particle,"HPinelastic");
	  partInelHP->SetVerboseLevel(1);
	  hp->RegisterMe(partInelHP);
	}
	else hp->RegisterMe(theBERT1);
      }

      // inelastic channel for deuteron
      else if(pname=="deuteron" && InelFlagDeut==true) {
	hp = FindInelasticProcess(particle);

	if(HPinelFlagDeut==true) {

	  // HPInelastic cross section
	  //hp->AddDataSet(new ParticleHPInelasticData(particle));

	  // ParticleInelasticXS cross section
	  hp->AddDataSet(new ParticleInelasticXS(particle));

	  // HPInelastic model
	  ParticleHPInelastic* partInelHP = new ParticleHPInelastic(particle,"HPinelastic");
	  partInelHP->SetVerboseLevel(1);
	  hp->RegisterMe(partInelHP);
	}
	else hp->RegisterMe(theBERT1);
      }

      // inelastic channel for triton
      else if(pname=="triton" && InelFlagTrit==true) {
	hp = FindInelasticProcess(particle);

	if(HPinelFlagTrit==true) {

	  // HPInelastic cross section
	  //hp->AddDataSet(new ParticleHPInelasticData(particle));

	  // ParticleInelasticXS cross section
	  hp->AddDataSet(new ParticleInelasticXS(particle));

	  // HPInelastic model
	  ParticleHPInelastic* partInelHP = new ParticleHPInelastic(particle,"HPinelastic");
	  partInelHP->SetVerboseLevel(1);
	  hp->RegisterMe(partInelHP);
	}
	else hp->RegisterMe(theBERT1);
      }

      // inelastic channel for He3
      else if(pname=="He3" && InelFlagHe3==true) {
	hp = FindInelasticProcess(particle);

	if(HPinelFlagHe3==true) {

	  // HPInelastic cross section
	  //hp->AddDataSet(new ParticleHPInelasticData(particle));

	  // ParticleInelasticXS cross section
	  hp->AddDataSet(new ParticleInelasticXS(particle));

	  // HPInelastic model
	  ParticleHPInelastic* partInelHP = new ParticleHPInelastic(particle,"HPinelastic");
	  partInelHP->SetVerboseLevel(1);
	  hp->RegisterMe(partInelHP);
	}
	else hp->RegisterMe(theBERT1);
      }

      // inelastic channel for alpha
      else if(pname=="alpha" && InelFlagAlph==true) {
	hp = FindInelasticProcess(particle);

	if(HPinelFlagAlph==true) {

	  // HPInelastic cross section
	  //hp->AddDataSet(new ParticleHPInelasticData(particle));

	  // ParticleInelasticXS cross section
	  hp->AddDataSet(new ParticleInelasticXS(particle));

	  // HPInelastic model
	  ParticleHPInelastic* partInelHP = new ParticleHPInelastic(particle,"HPinelastic");
	  partInelHP->SetVerboseLevel(1);
	  hp->RegisterMe(partInelHP);
	}
	else hp->RegisterMe(theBERT1);
      }

      // *** ParticleCapture model and cross section *** //
      if(PartCapFlag==true) {
	if(PartCapType=="non-resonant") {
	  particlecapture = FindParticleCaptureProcess(particle);
	  ParticleRadCapture *captureModel = new ParticleRadCapture();
	  captureModel->InitialiseModel();
	  particlecapture->RegisterMe(captureModel);
	  particlecapture->AddDataSet(new ParticleCaptureXS(particle));
	}
	else if(PartCapType=="resonant") {
	  particlecapture = FindParticleCaptureProcess(particle);
	  ParticleResRadCapture *resCaptureModel = new ParticleResRadCapture();
	  resCaptureModel->InitialiseModel();
	  particlecapture->RegisterMe(resCaptureModel);
	  particlecapture->AddDataSet(new ParticleResonantCaptureXS(particle));
	}
      }

    }
    
    else if(pname == "neutron") {
      hp = FindInelasticProcess(particle);
      hp->AddDataSet(new G4NeutronInelasticXS());
      hp->AddDataSet(new NeutronHPInelasticData());
      hp->RegisterMe(new NeutronHPInelastic());
      hp->RegisterMe(theFTFP3);
      
      capture = FindCaptureProcess();
      //capture->RegisterMe(new G4NeutronRadCapture());
      capture->AddDataSet(new NeutronHPCaptureData());
      capture->RegisterMe(new NeutronHPCapture());
      capture->RegisterMe(theFTFP3);

    } else if(pname == "pi-" || pname == "pi+") {
      hp = FindInelasticProcess(particle);
      hp->AddDataSet(new G4BGGPionInelasticXS(particle));
      hp->RegisterMe(theFTFP);
      hp->RegisterMe(theBERT1);

    } else if(pname == "kaon-" ) {
      hp = FindInelasticProcess(particle);
      hp->RegisterMe(theFTFP1);
      hp->RegisterMe(theBERT1);
      hp->AddDataSet(kaonxs);

    } else if(pname == "kaon+" ) {
      hp = FindInelasticProcess(particle);
      hp->RegisterMe(theFTFP1);
      hp->RegisterMe(theBERT1);
      hp->AddDataSet(kaonxs);

    } else if(pname == "kaon0S"    ||
              pname == "kaon0L") {
      hp = FindInelasticProcess(particle);
      hp->RegisterMe(theFTFP1);
      hp->RegisterMe(theBERT1);
      hp->AddDataSet(kaonxs);
        
    } else if(pname == "lambda"    ||
              pname == "omega-"    ||
	      pname == "sigma-"    || 
	      pname == "sigma+"    || 
	      pname == "sigma0"    || 
	      pname == "xi-"       || 
	      pname == "xi0") {
      hp = FindInelasticProcess(particle);
      hp->RegisterMe(theFTFP1);
      hp->RegisterMe(theBERT1);
      hp->AddDataSet(G4CrossSectionDataSetRegistry::Instance()->GetCrossSectionDataSet(G4ChipsHyperonInelasticXS::Default_Name()));

    } else if(pname == "anti_alpha"   ||
	      pname == "anti_deuteron"||
              pname == "anti_He3"     ||
	      pname == "anti_proton"  || 
              pname == "anti_triton"  ||  
	      pname == "anti_lambda"  ||
              pname == "anti_neutron" ||
              pname == "anti_omega-"  || 
              pname == "anti_sigma-"  || 
              pname == "anti_sigma+"  || 
              pname == "anti_xi-"     || 
              pname == "anti_xi0"     
	      ) {
      hp = FindInelasticProcess(particle);
      hp->RegisterMe(theFTFP2);
      hp->AddDataSet(anucxs);
    } 
  }
}
