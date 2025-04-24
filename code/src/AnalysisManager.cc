#include "AnalysisManager.hh"
#include "AnalysisMessenger.hh"

#include "G4UnitsTable.hh"
#include "G4IonTable.hh"

#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"

AnalysisManager::AnalysisManager():
  fileName("/nfs/luna01/simulations/elekes/SimLuna-build/SimLunaDefault.root")
{
  for(int i=0;i<6;i++) {
    totE_BGO14Np[i] = 0;
    totEGauss_BGO14Np[i] = 0;
  }

  MomSrcGamma[0] = G4ThreeVector(-999,-999,-999);
  MomSrcGamma[1] = G4ThreeVector(-999,-999,-999);

  for(int i=0;i<100;i++) {
    MomCapGamma[i] = G4ThreeVector(-999,-999,-999);
  }
  
  MomIon[0] = G4ThreeVector(-999,-999,-999);
  MomIon[1] = G4ThreeVector(-999,-999,-999);

  MomCapIon[0] = G4ThreeVector(-999,-999,-999);

  analysisMessenger = new AnalysisMessenger(this);
}

AnalysisManager::~AnalysisManager()
{
  delete analysisMessenger;
}

void AnalysisManager::ClearPrimaries(){
  BeamX.clear();
  BeamY.clear();
  BeamZ.clear();
  BeamKinE.clear();
  BeamTheta.clear();
}

void AnalysisManager::ClearVariables()
{
  for(int i=0;i<6;i++) {
    totE_BGO14Np[i] = 0;
    totEGauss_BGO14Np[i] = 0;
  }
  Z_interaction.resize(0);
  Z_energy.resize(0);
  GammaKinEneRes.resize(0);
  GammaKinEneDC.resize(0);
  GammaMomx.resize(0);
  GammaMomy.resize(0);
  GammaMomz.resize(0);
  mult.resize(0);
  fFusionEvent=false;

  MomSrcGamma[0] = G4ThreeVector(-999,-999,-999);
  MomSrcGamma[1] = G4ThreeVector(-999,-999,-999);

  for(int i=0;i<100;i++) {
    MomCapGamma[i] = G4ThreeVector(-999,-999,-999);
  }

  MomIon[0] = G4ThreeVector(-999,-999,-999);
  MomIon[1] = G4ThreeVector(-999,-999,-999);

  MomCapIon[0] = G4ThreeVector(-999,-999,-999);
}

void AnalysisManager::FillhBGO14NpTotEdep(G4double feDep,G4double feDepGauss,G4int fcopyNo,G4int fNofHits,G4int fparticleCode,G4double flevelEnergy,G4double fOriginalEnergy)
{
  //G4cout << "Analysis Manager, copy number: "  << fcopyNo << ", Edep:   " << feDep << " level energy,  " << flevelEnergy << ", original energy  " << fOriginalEnergy << G4endl;
  totE_BGO14Np[fcopyNo] += feDep;
  totEGauss_BGO14Np[fcopyNo] += feDepGauss;
}

void AnalysisManager::FillHistogramsAndTree()
{

 if(fAllEventFlag) tree1->Fill();
 else if(!fAllEventFlag &&  fAllFusionEventFlag && fFusionEvent) tree1->Fill();
 else if(!fAllEventFlag && !fAllFusionEventFlag && (totE_BGO14Np[0]!=0 || totE_BGO14Np[1]!=0 || totE_BGO14Np[2]!=0 || totE_BGO14Np[3]!=0 || totE_BGO14Np[4]!=0 || totE_BGO14Np[5]!=0)) tree1->Fill();

}

void AnalysisManager::FillhPrimaries(G4ThreeVector fPos,G4double fkinE,G4ThreeVector fmom)
{
  BeamX.push_back(fPos.x());
  BeamY.push_back(fPos.y());
  BeamZ.push_back(fPos.z());
  BeamKinE.push_back(fkinE);
  BeamTheta.push_back(fmom.theta()/deg);
}

void AnalysisManager::FillhSecondaries(G4int fNofSec, G4double *fSecKinE, G4ThreeVector *fSecMom, G4ParticleDefinition **fSecPartDef, G4double *fParKinE, G4ThreeVector *fParMom, G4ThreeVector *fParPos, G4ParticleDefinition **fParPartDef, G4int *fParTrackID)
{
  //G4cout << "AnalysisManager:" << G4endl;
  //G4cout << "NofSec: " << fNofSec << G4endl;

  G4int NofGamma = 0;
  G4int NofIon = 0;
  G4int multiplicity=0;
  for (int i=0;i<6;i++){
  	if (totE_BGO14Np[i]>MultThr) multiplicity++;
  }
  mult.push_back(multiplicity);
  
  for(int i=0;i<fNofSec;i++) {
    //G4cout << fSecPartDef[i]->GetParticleName() << "  " << fParPartDef[i]->GetAtomicMass() << "  " << fParPartDef[i]->GetAtomicNumber() << "  " << fSecKinE[i]/keV << "  " << fParPos[i].z() << "  " << fParPartDef[i]->GetParticleName() << "  " << fParTrackID[i] << G4endl;

    if(fSecPartDef[i]->GetAtomicMass() == 16 && fSecPartDef[i]->GetAtomicNumber() == 8) {
      //G4cout << fSecPartDef[i]->GetParticleName() << "  " << fParPartDef[i]->GetAtomicMass() << "  " << fParPartDef[i]->GetAtomicNumber() << "  " << fParKinE[i]/keV << "  " << fParPos[i].z() << "  " << fParPartDef[i]->GetParticleName() << "  " << fParTrackID[i] << "  " << fOrigTrackID[i] << "  " << fLevelEnergy[i] << "  " << G4endl;
       Z_energy.push_back(fParKinE[i]/keV);
    }

    if(fSecPartDef[i] == G4Gamma::Gamma()) {

      if(fParPartDef[i]->GetAtomicMass() == FragIonA1 && fParPartDef[i]->GetAtomicNumber() == FragIonZ1) {
        hGammavsAnglePart1->Fill(fSecMom[i].theta()/deg,fSecKinE[i]/keV);
    	}
      if(fParPartDef[i]->GetAtomicMass() == FragIonA2 && fParPartDef[i]->GetAtomicNumber() == FragIonZ2) {
        hGammavsAnglePart2->Fill(fSecMom[i].theta()/deg,fSecKinE[i]/keV);
    	}
      if(fParPartDef[i]->GetAtomicMass() == CapFragIonA && fParPartDef[i]->GetAtomicNumber() == CapFragIonZ) {
        hGammavsAnglePart3->Fill(fSecMom[i].theta()/deg,fSecKinE[i]/keV);
    	}

      MomCapGamma[NofGamma] = fSecMom[i];
      NofGamma++;
    }
    else if(fSecPartDef[i]->GetAtomicMass()>0 && fSecPartDef[i]->GetAtomicNumber()>0) {
      //std::cout << "Secondary: " << fSecPartDef[i]->GetParticleName() << "  " << fSecPartDef[i]->GetAtomicMass() << "  " << fSecPartDef[i]->GetAtomicNumber() << "  " << fSecKinE[i]/keV << "  " << fSecMom[i].z() << G4endl;
      if(fSecPartDef[i]->GetAtomicMass() == FragIonA1 && fSecPartDef[i]->GetAtomicNumber() == FragIonZ1) {
        MomIon[0] = fSecMom[i];
        DefIon[0] = fSecPartDef[i];
        hKinvsAnglePart1->Fill(fSecMom[i].theta()/deg,fSecKinE[i]/keV);
	      //G4cout << "MomIon1: " << MomIon[0] << G4endl;
      }
      else if(fSecPartDef[i]->GetAtomicMass() == FragIonA2 && fSecPartDef[i]->GetAtomicNumber() == FragIonZ2) {
        MomIon[1] = fSecMom[i];
        DefIon[1] = fSecPartDef[i];
        hKinvsAnglePart2->Fill(fSecMom[i].theta()/deg,fSecKinE[i]/keV);
        //G4cout << "MomIon2: " << MomIon[1] << G4endl;
      }
      else if(fSecPartDef[i]->GetAtomicMass() == CapFragIonA && fSecPartDef[i]->GetAtomicNumber() == CapFragIonZ) {
        MomCapIon[0] = fSecMom[i];
        DefCapIon[0] = fSecPartDef[i];
        hKinvsAnglePart3->Fill(fSecMom[i].theta()/deg,fSecKinE[i]/keV);
        //G4cout << "MomIon2: " << MomIon[1] << G4endl;
      }
      NofIon++;
    }
  }
}

void AnalysisManager::BeginOfRun()
{ 
  rootFile = new TFile(fileName,"RECREATE");

  // Tree
  tree1 = new TTree("Tree1", "RawData");
   if(fEdepTreeFlag) tree1->Branch("Edep", &totE_BGO14Np);
   if(fZintTreeFlag) tree1->Branch("Zint", &Z_interaction);
   if(fEpTreeFlag) tree1->Branch("Ep", &Z_energy);
    if(fEgammaTreeFlag){
    	tree1->Branch("EgammaRes", &GammaKinEneRes);
    	tree1->Branch("EgammaDC", &GammaKinEneDC);
	} 
  if(fPgammaTreeFlag){
   tree1->Branch("Pgx", &GammaMomx); 
   tree1->Branch("Pgy", &GammaMomy); 
   tree1->Branch("Pgz", &GammaMomz); 
	}
	if(fBeamPosTreeFlag){
		tree1->Branch("BeamX", &BeamX); 
		tree1->Branch("BeamY", &BeamY); 
		tree1->Branch("BeamZ", &BeamZ); 
	}
	if(fBeamKinETreeFlag) tree1->Branch("BeamKinE", &BeamKinE);
	if(fBeamThetaTreeFlag) tree1->Branch("BeamTheta", &BeamTheta);
	tree1->Branch("Multiplicity", &mult);

  hKinvsAnglePart1 = new TH2D("KinPart1vsAnglePart1","",360,0,180,5000,0,5000);
  hKinvsAnglePart2 = new TH2D("KinPart2vsAnglePart2","",360,0,180,5000,0,5000);
  hKinvsAnglePart3 = new TH2D("KinPart3vsAnglePart3","",360,0,180,5000,0,5000);

  hGammavsAnglePart1 = new TH2D("GammavsAnglePart1","",360,0,180,2000,0,20000);
  hGammavsAnglePart2 = new TH2D("GammavsAnglePart2","",360,0,180,2000,0,20000);
  hGammavsAnglePart3 = new TH2D("GammavsAnglePart3","",360,0,180,2000,0,20000);

}

void AnalysisManager::EndOfRun()
{
  if(rootFile) {
    rootFile->Write();
    rootFile->Close();
  }
}
