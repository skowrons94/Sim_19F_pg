#ifndef AnalysisManager_h
#define AnalysisManager_h 1

#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class TFile;
class TH1D;
class TH2D;
class TTree;

class AnalysisMessenger;

class AnalysisManager
{
  
public:
  AnalysisManager ();
  virtual ~AnalysisManager ();

public:
  void BeginOfRun();
  void EndOfRun();

  void SetFileName(G4String filename) {fileName = filename;};
  void SetGamma1(G4double fGamma1) {Gamma1 = fGamma1;};
  void SetGamma2(G4double fGamma2) {Gamma2 = fGamma2;};
  void SetCapFragIonA(G4double fCapFragIonA) {CapFragIonA = fCapFragIonA;};
  void SetCapFragIonZ(G4double fCapFragIonZ) {CapFragIonZ = fCapFragIonZ;};
  void SetFragIonA1(G4double fFragIonA1) {FragIonA1 = fFragIonA1;};
  void SetFragIonZ1(G4double fFragIonZ1) {FragIonZ1 = fFragIonZ1;};
  void SetFragIonA2(G4double fFragIonA2) {FragIonA2 = fFragIonA2;};
  void SetFragIonZ2(G4double fFragIonZ2) {FragIonZ2 = fFragIonZ2;};
  void SetAllEventFlag(G4bool AllEventFlag) {fAllEventFlag = AllEventFlag;};
  void SetAllFusionEventFlag(G4bool AllFusionEventFlag) {fAllFusionEventFlag = AllFusionEventFlag;};
  void SetZintTreeFlag(G4bool ZintTreeFlag) {fZintTreeFlag = ZintTreeFlag;};
  void SetEpTreeFlag(G4bool EpTreeFlag) {fEpTreeFlag = EpTreeFlag;};
  void SetEgammaTreeFlag(G4bool EgammaTreeFlag) {fEgammaTreeFlag = EgammaTreeFlag;};
  void SetPgammaTreeFlag(G4bool PgammaTreeFlag) {fPgammaTreeFlag = PgammaTreeFlag;};
  void SetEdepTreeFlag(G4bool EdepTreeFlag) {fEdepTreeFlag = EdepTreeFlag;};
   void SetBeamPosTreeFlag(G4bool BeamPosTreeFlag) {fBeamPosTreeFlag = BeamPosTreeFlag;};
  void SetBeamKinETreeFlag(G4bool BeamKinETreeFlag) {fBeamKinETreeFlag = BeamKinETreeFlag;};
  void SetBeamThetaTreeFlag(G4bool BeamThetaTreeFlag) {fBeamThetaTreeFlag = BeamThetaTreeFlag;};
  void SetMultThreshold(G4double fMultThr) {MultThr = fMultThr;};
  
  
  
  

  void ClearVariables();
  void ClearPrimaries();
  void FillhBGO14NpTotEdep(G4double,G4double,G4int,G4int,G4int,G4double,G4double);
  void FillHistogramsAndTree();
  void FillhPrimaries(G4ThreeVector,G4double,G4ThreeVector);
  void FillhSecondaries(G4int,G4double*,G4ThreeVector*,G4ParticleDefinition**,G4double*,G4ThreeVector*,G4ThreeVector*,G4ParticleDefinition**,G4int*);

private:

  G4String fileName;
  G4String fileType;

  TFile*   rootFile;
  
  G4double totEGauss_BGO14Np[6];
  std::vector<G4double> totE_BGO14Np {0,0,0,0,0,0};
  std::vector<G4double> Z_interaction;
  std::vector<G4double> GammaKinEneRes;
  std::vector<G4double> GammaKinEneDC;
  std::vector<G4double> GammaMomx;
  std::vector<G4double> GammaMomy;
  std::vector<G4double> GammaMomz;
  std::vector<G4double> Z_energy;
  std::vector<G4double> BeamX;
  std::vector<G4double> BeamY;
  std::vector<G4double> BeamZ;
  std::vector<G4double> BeamKinE;
  std::vector<G4double> BeamTheta;
  std::vector<G4int> mult;

  G4ThreeVector MomSrcGamma[2];

  G4ThreeVector MomIon[2];
  G4ParticleDefinition *DefIon[2];

  G4ThreeVector MomCapIon[2];
  G4ParticleDefinition *DefCapIon[2];
  G4ThreeVector MomCapGamma[100];


  G4double Gamma1;
  G4double Gamma2;
  G4double CapFragIonA;
  G4double CapFragIonZ;
  G4double FragIonA1;
  G4double FragIonZ1;
  G4double FragIonA2;
  G4double FragIonZ2;
  G4double MultThr;
  G4bool fAllEventFlag;
  G4bool fAllFusionEventFlag;
  G4bool fZintTreeFlag;
  G4bool fEpTreeFlag;
  G4bool fEgammaTreeFlag;
  G4bool fPgammaTreeFlag;
  G4bool fEdepTreeFlag;
  G4bool fBeamPosTreeFlag;
  G4bool fBeamKinETreeFlag;
  G4bool fBeamThetaTreeFlag;
  G4bool fFusionEvent=false;

  TTree *tree1;

  // EventAction
  TH2D *hKinvsAnglePart1;
  TH2D *hKinvsAnglePart2;
  TH2D *hKinvsAnglePart3;
  TH2D *hGammavsAnglePart1;
  TH2D *hGammavsAnglePart2;
  TH2D *hGammavsAnglePart3;

  AnalysisMessenger* analysisMessenger;

};

#endif
