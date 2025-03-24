#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"

class G4ParticleDefinition;
class G4GeneralParticleSource;
class G4Event;
class AnalysisManager;
class DetectorConstruction;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction(AnalysisManager*,DetectorConstruction*);
  ~PrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event* anEvent);
  void Generate_reaction(G4Event* anEvent);
  void Generate_gpsradsource(G4Event* anEvent);
  
private:
  AnalysisManager*    analysismanager;
  DetectorConstruction*    detectorconstruction;
  G4GeneralParticleSource* GPSparticleGun;

  PrimaryGeneratorMessenger* primaryGeneratorMessenger;

};

#endif
