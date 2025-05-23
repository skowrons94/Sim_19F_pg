#include "PhysListEmStandardNR.hh"

#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4LossTableManager.hh"
#include "G4EmParameters.hh"
//#include "G4EmProcessOptions.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"
#include "G4PEEffectFluoModel.hh"
#include "G4KleinNishinaModel.hh"
#include "G4LowEPComptonModel.hh"
#include "G4PenelopeGammaConversionModel.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4CoulombScattering.hh"
#include "G4eCoulombScatteringModel.hh"
#include "G4UrbanMscModel.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4Generator2BS.hh"
#include "G4SeltzerBergerModel.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4eplusAnnihilation.hh"
#include "G4UAtomicDeexcitation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"

#include "G4ScreenedNuclearRecoil.hh"

#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"

#include "IonC12.hh"

PhysListEmStandardNR::PhysListEmStandardNR(const G4String& name)
   :  G4VPhysicsConstructor(name)
{
  G4EmParameters* param = G4EmParameters::Instance();
  param->SetDefaults();
  param->SetStepFunction(0.2, 100*um);
  param->SetStepFunctionMuHad(0.2, 50*um);          
  param->SetStepFunctionLightIons(0.1, 10*um);
  param->SetStepFunctionIons(0.1, 1*um);
  param->SetFluo(true);
  SetPhysicsType(bElectromagnetic);

  G4LossTableManager::Instance();
}

PhysListEmStandardNR::~PhysListEmStandardNR()
{}

void PhysListEmStandardNR::ConstructProcess()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  // muon & hadron bremsstrahlung and pair production
  G4MuBremsstrahlung* mub = new G4MuBremsstrahlung();
  G4MuPairProduction* mup = new G4MuPairProduction();

  G4ScreenedNuclearRecoil* nucr = new G4ScreenedNuclearRecoil();
  G4double energyLimit = 100.*MeV;
  nucr->SetMaxEnergyForScattering(energyLimit);
  nucr->SetCrossSectionHardening(1,10000);
  nucr->EnableRecoils(false);
  //nucr->EnableRecoils(true);
  G4eCoulombScatteringModel* csm = new G4eCoulombScatteringModel();
  csm->SetActivationLowEnergyLimit(energyLimit);

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {

       // Compton scattering
      G4ComptonScattering* cs = new G4ComptonScattering;
      cs->SetEmModel(new G4KleinNishinaModel(),1);
      ph->RegisterProcess(cs, particle);

      // Photoelectric
      G4PhotoElectricEffect* pe = new G4PhotoElectricEffect();
      G4VEmModel* theLivermorePEModel = new G4LivermorePhotoElectricModel();
      theLivermorePEModel->SetHighEnergyLimit(10*GeV);
      pe->SetEmModel(theLivermorePEModel,1);
      ph->RegisterProcess(pe, particle);

      // Gamma conversion
      G4GammaConversion* gc = new G4GammaConversion();
      G4VEmModel* thePenelopeGCModel = new G4PenelopeGammaConversionModel();
      thePenelopeGCModel->SetHighEnergyLimit(1*GeV);
      gc->SetEmModel(thePenelopeGCModel,1);
      ph->RegisterProcess(gc, particle);

      // Rayleigh scattering
      ph->RegisterProcess(new G4RayleighScattering(), particle);
      
    } else if (particleName == "e-") {

      // ionisation
      G4eIonisation* eIoni = new G4eIonisation();
      eIoni->SetStepFunction(0.2, 100*um);

      // bremsstrahlung
      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();

      ph->RegisterProcess(new G4eMultipleScattering(), particle);
      ph->RegisterProcess(eIoni, particle);
      ph->RegisterProcess(eBrem, particle);
            
    } else if (particleName == "e+") {
      // ionisation
      G4eIonisation* eIoni = new G4eIonisation();
      eIoni->SetStepFunction(0.2, 100*um);

      // bremsstrahlung
      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();

      ph->RegisterProcess(new G4eMultipleScattering(), particle);
      ph->RegisterProcess(eIoni, particle);
      ph->RegisterProcess(eBrem, particle);

      // annihilation at rest and in flight
      ph->RegisterProcess(new G4eplusAnnihilation(), particle);
            
    } else if (particleName == "mu+" || 
               particleName == "mu-"    ) {

      G4MuIonisation* muIoni = new G4MuIonisation();
      muIoni->SetStepFunction(0.2, 50*um);          

      ph->RegisterProcess(muIoni, particle);
      ph->RegisterProcess(mub, particle);
      ph->RegisterProcess(mup, particle);
      ph->RegisterProcess(new G4CoulombScattering(), particle);
             
    } else if (particleName == "alpha" || particleName == "He3") {

      G4hMultipleScattering* msc = new G4hMultipleScattering();
      G4UrbanMscModel* model = new G4UrbanMscModel();
      model->SetActivationLowEnergyLimit(energyLimit);
      msc->SetEmModel(model, 1);
      ph->RegisterProcess(msc, particle);

      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetStepFunction(0.1, 10*um);
      ph->RegisterProcess(ionIoni, particle);

      //ph->RegisterProcess(nucr, particle);

    } else if (particleName == "GenericIon" ) { 

      G4hMultipleScattering* msc = new G4hMultipleScattering();
      G4UrbanMscModel* model = new G4UrbanMscModel();
      model->SetActivationLowEnergyLimit(energyLimit);
      msc->SetEmModel(model, 1);
      ph->RegisterProcess(msc, particle);

      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetEmModel(new G4IonParametrisedLossModel());
      ionIoni->SetStepFunction(0.1, 1*um);
      ph->RegisterProcess(ionIoni, particle);

      ph->RegisterProcess(nucr, particle);
     
    } else if (particleName == "proton" ||
               particleName == "deuteron" ||
               particleName == "triton") { 

      G4hMultipleScattering* msc = new G4hMultipleScattering();
      G4UrbanMscModel* model = new G4UrbanMscModel();
      model->SetActivationLowEnergyLimit(energyLimit);
      msc->SetEmModel(model, 1);
      ph->RegisterProcess(msc, particle);

      G4hIonisation* hIoni = new G4hIonisation();
      hIoni->SetStepFunction(0.05, 1*um);
      ph->RegisterProcess(hIoni, particle);

      if(particleName == "deuteron") ph->RegisterProcess(nucr, particle);

    } else if (particleName == "C12") { 

      G4hMultipleScattering* msc = new G4hMultipleScattering();
      G4UrbanMscModel* model = new G4UrbanMscModel();
      model->SetActivationLowEnergyLimit(energyLimit);
      msc->SetEmModel(model, 1);
      ph->RegisterProcess(msc, particle);

      G4hIonisation* hIoni = new G4hIonisation();
      hIoni->SetStepFunction(0.05, 1*um);
      ph->RegisterProcess(hIoni, particle);

    } else if ((!particle->IsShortLived()) &&
               (particle->GetPDGCharge() != 0.0) && 
               (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino

      ph->RegisterProcess(new G4hMultipleScattering(), particle);
      ph->RegisterProcess(new G4hIonisation(), particle);
    }
  }
  
  // Deexcitation
  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);
  de->SetFluo(true);
}
