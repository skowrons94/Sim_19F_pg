#include "AnalysisMessenger.hh"
#include "AnalysisManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"

AnalysisMessenger::AnalysisMessenger(AnalysisManager* analysisManager)
  :Analysis(analysisManager)

{ 
  AnalysisDir = new G4UIdirectory("/analysis/");
  AnalysisDir->SetGuidance("analysis control.");
  
  FileNameCmd = new G4UIcmdWithAString("/analysis/filename",this);
  FileNameCmd->SetGuidance("Input the name for the output file.");
  FileNameCmd->SetParameterName("filename",true,true);
  FileNameCmd->SetDefaultValue("/nfs/luna01/simulations/elekes/SimLuna-build/SimLunaDefault.root");

  Gamma1Cmd = new G4UIcmdWithADouble("/analysis/Gamma1",this);
  Gamma1Cmd->SetGuidance("Input the energy of the first gamma for correlation plot in MeV.");
  Gamma1Cmd->SetParameterName("Gamma1",true,true);
  Gamma1Cmd->SetDefaultValue(1.0);

  Gamma2Cmd = new G4UIcmdWithADouble("/analysis/Gamma2",this);
  Gamma2Cmd->SetGuidance("Input the energy of the second gamma for correlation plot in MeV.");
  Gamma2Cmd->SetParameterName("Gamma2",true,true);
  Gamma2Cmd->SetDefaultValue(1.0);

  CapFragIonACmd = new G4UIcmdWithADouble("/analysis/CapFragIonA",this);
  CapFragIonACmd->SetGuidance("Input the atomic mass of the fragment ion in capture process for kinematics plot.");
  CapFragIonACmd->SetParameterName("FragIonA1",true,true);
  CapFragIonACmd->SetDefaultValue(1.0);

  CapFragIonZCmd = new G4UIcmdWithADouble("/analysis/CapFragIonZ",this);
  CapFragIonZCmd->SetGuidance("Input the atomic number of the fragment ion in capture process for kinematics plot.");
  CapFragIonZCmd->SetParameterName("CapFragIonZ",true,true);
  CapFragIonZCmd->SetDefaultValue(1.0);

  FragIonA1Cmd = new G4UIcmdWithADouble("/analysis/FragIonA1",this);
  FragIonA1Cmd->SetGuidance("Input the atomic mass of the first fragment ion for kinematics plot.");
  FragIonA1Cmd->SetParameterName("FragIonA1",true,true);
  FragIonA1Cmd->SetDefaultValue(1.0);

  FragIonZ1Cmd = new G4UIcmdWithADouble("/analysis/FragIonZ1",this);
  FragIonZ1Cmd->SetGuidance("Input the atomic number of the first fragment ion for kinematics plot.");
  FragIonZ1Cmd->SetParameterName("FragIonZ1",true,true);
  FragIonZ1Cmd->SetDefaultValue(1.0);

  FragIonA2Cmd = new G4UIcmdWithADouble("/analysis/FragIonA2",this);
  FragIonA2Cmd->SetGuidance("Input the atomic mass of the second fragment ion for kinematics plot.");
  FragIonA2Cmd->SetParameterName("FragIonA2",true,true);
  FragIonA2Cmd->SetDefaultValue(1.0);

  FragIonZ2Cmd = new G4UIcmdWithADouble("/analysis/FragIonZ2",this);
  FragIonZ2Cmd->SetGuidance("Input the atomic number of the second fragment ion for kinematics plot.");
  FragIonZ2Cmd->SetParameterName("FragIonZ2",true,true);
  FragIonZ2Cmd->SetDefaultValue(1.0);
  
  AllEventCmd = new G4UIcmdWithABool("/analysis/AllEventFlag",this);
  AllEventCmd->SetGuidance("Set the flag to save all events in the TTree.");
  AllEventCmd->SetParameterName("AllEventFlag",true,true);
  AllEventCmd->SetDefaultValue("true");
  
  AllFusionEventCmd = new G4UIcmdWithABool("/analysis/AllFusionEventFlag",this);
  AllFusionEventCmd->SetGuidance("Set the flag to save all fusion events in the TTree.");
  AllFusionEventCmd->SetParameterName("AllFusionEventFlag",true,true);
  AllFusionEventCmd->SetDefaultValue("true");
  
  ZintTreeCmd = new G4UIcmdWithABool("/analysis/ZintTreeFlag",this);
  ZintTreeCmd->SetGuidance("Set the flag to save Zint in the TTree.");
  ZintTreeCmd->SetParameterName("ZintTreeFlag",true,true);
  ZintTreeCmd->SetDefaultValue("true");
  
  EpTreeCmd = new G4UIcmdWithABool("/analysis/EpTreeFlag",this);
  EpTreeCmd->SetGuidance("Set the flag to save Ep in the TTree.");
  EpTreeCmd->SetParameterName("EpTreeFlag",true,true);
  EpTreeCmd->SetDefaultValue("true");
  
  
  EgammaTreeCmd = new G4UIcmdWithABool("/analysis/EgammaTreeFlag",this);
  EgammaTreeCmd->SetGuidance("Set the flag to save Egamma in the TTree.");
  EgammaTreeCmd->SetParameterName("EgammaTreeFlag",true,true);
  EgammaTreeCmd->SetDefaultValue("true");
  
   PgammaTreeCmd = new G4UIcmdWithABool("/analysis/PgammaTreeFlag",this);
  PgammaTreeCmd->SetGuidance("Set the flag to save Pgamma in the TTree.");
  PgammaTreeCmd->SetParameterName("PgammaTreeFlag",true,true);
  PgammaTreeCmd->SetDefaultValue("true");
  
  EdepTreeCmd = new G4UIcmdWithABool("/analysis/EdepTreeFlag",this);
  EdepTreeCmd->SetGuidance("Set the flag to save Edep in the TTree.");
  EdepTreeCmd->SetParameterName("EdepTreeFlag",true,true);
  EdepTreeCmd->SetDefaultValue("true");
  
  BeamPosTreeCmd = new G4UIcmdWithABool("/analysis/BeamPosTreeFlag",this);
  BeamPosTreeCmd->SetGuidance("Set the flag to save Beam position in the TTree.");
  BeamPosTreeCmd->SetParameterName("BeamPosTreeFlag",true,true);
  BeamPosTreeCmd->SetDefaultValue("true");
  
  BeamKinETreeCmd = new G4UIcmdWithABool("/analysis/BeamKinETreeFlag",this);
  BeamKinETreeCmd->SetGuidance("Set the flag to save Beam Kinetic Energy in the TTree.");
  BeamKinETreeCmd->SetParameterName("BeamKinETreeFlag",true,true);
  BeamKinETreeCmd->SetDefaultValue("true");
  
  BeamThetaTreeCmd = new G4UIcmdWithABool("/analysis/BeamThetaTreeFlag",this);
  BeamThetaTreeCmd->SetGuidance("Set the flag to save Beam angle in the TTree.");
  BeamThetaTreeCmd->SetParameterName("BeamThetaTreeFlag",true,true);
  BeamThetaTreeCmd->SetDefaultValue("true");
  
  MultThrCmd = new G4UIcmdWithADouble("/analysis/MultThr",this);
  MultThrCmd->SetGuidance("Input the energy threshold for multiplicity in keV.");
  MultThrCmd->SetParameterName("MultThr",true,true);
  MultThrCmd->SetDefaultValue(50.0);
 

}

AnalysisMessenger::~AnalysisMessenger()
{
  delete FileNameCmd; 
  delete Gamma1Cmd; 
  delete Gamma2Cmd; 
  delete CapFragIonACmd; 
  delete CapFragIonZCmd; 
  delete FragIonA1Cmd; 
  delete FragIonZ1Cmd; 
  delete FragIonA2Cmd; 
  delete FragIonZ2Cmd; 
  delete AllEventCmd; 
  delete AllFusionEventCmd; 
   delete ZintTreeCmd; 
   delete EpTreeCmd; 
   delete EgammaTreeCmd;
   delete PgammaTreeCmd; 
   delete EdepTreeCmd; 
   delete BeamPosTreeCmd; 
   delete BeamKinETreeCmd; 
   delete BeamThetaTreeCmd; 
   delete MultThrCmd; 
  
  
}

void AnalysisMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == FileNameCmd )
    { 
      Analysis->SetFileName(newValue);
    }
  else if(command == Gamma1Cmd)
    {
      Analysis->SetGamma1(Gamma1Cmd->GetNewDoubleValue(newValue));
    }
  else if(command == Gamma2Cmd)
    {
      Analysis->SetGamma2(Gamma2Cmd->GetNewDoubleValue(newValue));
    }
  else if(command == CapFragIonACmd)
    {
      Analysis->SetCapFragIonA(CapFragIonACmd->GetNewDoubleValue(newValue));
    }
  else if(command == CapFragIonZCmd)
    {
      Analysis->SetCapFragIonZ(CapFragIonZCmd->GetNewDoubleValue(newValue));
    }
  else if(command == FragIonA1Cmd)
    {
      Analysis->SetFragIonA1(FragIonA1Cmd->GetNewDoubleValue(newValue));
    }
  else if(command == FragIonZ1Cmd)
    {
      Analysis->SetFragIonZ1(FragIonZ1Cmd->GetNewDoubleValue(newValue));
    }
  else if(command == FragIonA2Cmd)
    {
      Analysis->SetFragIonA2(FragIonA2Cmd->GetNewDoubleValue(newValue));
    }
  else if(command == FragIonZ2Cmd)
    {
      Analysis->SetFragIonZ2(FragIonZ2Cmd->GetNewDoubleValue(newValue));
    }
    else if(command == AllEventCmd) {
    Analysis->SetAllEventFlag(AllEventCmd->GetNewBoolValue(newValue));
  }
  else if(command == AllFusionEventCmd) {
    Analysis->SetAllFusionEventFlag(AllFusionEventCmd->GetNewBoolValue(newValue));
  }
  else if(command == ZintTreeCmd) {
    Analysis->SetZintTreeFlag(ZintTreeCmd->GetNewBoolValue(newValue));
  }
   else if(command == EpTreeCmd) {
    Analysis->SetEpTreeFlag(EpTreeCmd->GetNewBoolValue(newValue));
  }
   else if(command == EgammaTreeCmd) {
    Analysis->SetEgammaTreeFlag(EgammaTreeCmd->GetNewBoolValue(newValue));
  }
  else if(command == PgammaTreeCmd) {
    Analysis->SetPgammaTreeFlag(PgammaTreeCmd->GetNewBoolValue(newValue));
  }
   else if(command == EdepTreeCmd) {
    Analysis->SetEdepTreeFlag(EdepTreeCmd->GetNewBoolValue(newValue));
  }
   else if(command == BeamPosTreeCmd) {
    Analysis->SetBeamPosTreeFlag(BeamPosTreeCmd->GetNewBoolValue(newValue));
  }
  else if(command == BeamKinETreeCmd) {
    Analysis->SetBeamKinETreeFlag(BeamKinETreeCmd->GetNewBoolValue(newValue));
  }
  else if(command == BeamThetaTreeCmd) {
    Analysis->SetBeamThetaTreeFlag(BeamThetaTreeCmd->GetNewBoolValue(newValue));
  }
  else if(command == MultThrCmd)
    {
      Analysis->SetMultThreshold(MultThrCmd->GetNewDoubleValue(newValue));
    }
  
}
