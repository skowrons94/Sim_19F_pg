#include "PrimaryGeneratorAction.hh"
#include "AnalysisManager.hh"
#include "DetectorConstruction.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GeneralParticleSource.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"
#include "G4UImanager.hh"
#include <math.h>
#include "G4IonTable.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "TString.h"

PrimaryGeneratorAction::PrimaryGeneratorAction(AnalysisManager* AM,DetectorConstruction* DC):analysismanager(AM),detectorconstruction(DC)
{
  primaryGeneratorMessenger = new PrimaryGeneratorMessenger(this);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  GPSparticleGun  = new G4GeneralParticleSource();

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete GPSparticleGun;
  delete primaryGeneratorMessenger;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if(detectorconstruction->GetPhysics() == "S") Generate_gpsradsource(anEvent);
  else if(detectorconstruction->GetPhysics() == "R") Generate_reaction(anEvent);
}

void PrimaryGeneratorAction::Generate_reaction(G4Event* anEvent)
{
  GPSparticleGun->GeneratePrimaryVertex(anEvent);
  analysismanager->FillhPrimaries(GPSparticleGun->GetParticlePosition()/mm,GPSparticleGun->GetParticleEnergy()/keV,GPSparticleGun->GetParticleMomentumDirection());
}

void PrimaryGeneratorAction::Generate_gpsradsource(G4Event* anEvent)
{
  G4UImanager* UI = G4UImanager::GetUIpointer();

  TString uicommand;
  uicommand.Form("/gps/pos/centre %f %f %f mm",detectorconstruction->GetSourcePos().x(),detectorconstruction->GetSourcePos().y(),detectorconstruction->GetSourcePos().z());
  UI->ApplyCommand(uicommand.Data());

  GPSparticleGun->GeneratePrimaryVertex(anEvent);
  analysismanager->FillhPrimaries(GPSparticleGun->GetParticlePosition()/mm,GPSparticleGun->GetParticleEnergy()/keV,GPSparticleGun->GetParticleMomentumDirection());
}
