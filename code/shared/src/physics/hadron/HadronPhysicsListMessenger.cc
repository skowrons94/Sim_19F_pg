#include "HadronPhysicsListMessenger.hh"

#include "HadronPhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

HadronPhysicsListMessenger::HadronPhysicsListMessenger(HadronPhysicsList* HPL):hadronPhysicsList(HPL)
{ 
  PhysDir = new G4UIdirectory("/HadronPhysicsList/");
  PhysDir->SetGuidance("HadronPhysicsList control.");

  HPinelProtCmd = new G4UIcmdWithABool("/HadronPhysicsList/HPinelFlagProt",this);
  HPinelProtCmd->SetGuidance("Set the flag for HP inelastic reaction for protons.");
  HPinelProtCmd->SetParameterName("HPinelFlagProt",true,false);
  HPinelProtCmd->SetDefaultValue(false);

  HPinelDeutCmd = new G4UIcmdWithABool("/HadronPhysicsList/HPinelFlagDeut",this);
  HPinelDeutCmd->SetGuidance("Set the flag for HP inelastic reaction for deuterons.");
  HPinelDeutCmd->SetParameterName("HPinelFlagDeut",true,false);
  HPinelDeutCmd->SetDefaultValue(false);

  HPinelTritCmd = new G4UIcmdWithABool("/HadronPhysicsList/HPinelFlagTrit",this);
  HPinelTritCmd->SetGuidance("Set the flag for HP inelastic reaction for tritons.");
  HPinelTritCmd->SetParameterName("HPinelFlagTrit",true,false);
  HPinelTritCmd->SetDefaultValue(false);

  HPinelHe3Cmd = new G4UIcmdWithABool("/HadronPhysicsList/HPinelFlagHe3",this);
  HPinelHe3Cmd->SetGuidance("Set the flag for HP inelastic reaction for He3's.");
  HPinelHe3Cmd->SetParameterName("HPinelFlagHe3",true,false);
  HPinelHe3Cmd->SetDefaultValue(false);

  HPinelAlphCmd = new G4UIcmdWithABool("/HadronPhysicsList/HPinelFlagAlph",this);
  HPinelAlphCmd->SetGuidance("Set the flag for HP inelastic reaction for alphas.");
  HPinelAlphCmd->SetParameterName("HPinelFlagAlph",true,false);
  HPinelAlphCmd->SetDefaultValue(false);

  HPinelC12Cmd = new G4UIcmdWithABool("/HadronPhysicsList/HPinelFlagC12",this);
  HPinelC12Cmd->SetGuidance("Set the flag for HP inelastic reaction for C12's.");
  HPinelC12Cmd->SetParameterName("HPinelFlagC12",true,false);
  HPinelC12Cmd->SetDefaultValue(false);

  InelProtCmd = new G4UIcmdWithABool("/HadronPhysicsList/InelFlagProt",this);
  InelProtCmd->SetGuidance("Set the flag for inelastic reaction for protons.");
  InelProtCmd->SetParameterName("InelFlagProt",true,false);
  InelProtCmd->SetDefaultValue(false);

  InelDeutCmd = new G4UIcmdWithABool("/HadronPhysicsList/InelFlagDeut",this);
  InelDeutCmd->SetGuidance("Set the flag for inelastic reaction for deuterons.");
  InelDeutCmd->SetParameterName("InelFlagDeut",true,false);
  InelDeutCmd->SetDefaultValue(false);

  InelTritCmd = new G4UIcmdWithABool("/HadronPhysicsList/InelFlagTrit",this);
  InelTritCmd->SetGuidance("Set the flag for inelastic reaction for tritons.");
  InelTritCmd->SetParameterName("InelFlagTrit",true,false);
  InelTritCmd->SetDefaultValue(false);

  InelHe3Cmd = new G4UIcmdWithABool("/HadronPhysicsList/InelFlagHe3",this);
  InelHe3Cmd->SetGuidance("Set the flag for inelastic reaction for He3's.");
  InelHe3Cmd->SetParameterName("InelFlagHe3",true,false);
  InelHe3Cmd->SetDefaultValue(false);

  InelAlphCmd = new G4UIcmdWithABool("/HadronPhysicsList/InelFlagAlph",this);
  InelAlphCmd->SetGuidance("Set the flag for inelastic reaction for alphas.");
  InelAlphCmd->SetParameterName("InelFlagAlph",true,false);
  InelAlphCmd->SetDefaultValue(false);

  InelC12Cmd = new G4UIcmdWithABool("/HadronPhysicsList/InelFlagC12",this);
  InelC12Cmd->SetGuidance("Set the flag for inelastic reaction for C12's.");
  InelC12Cmd->SetParameterName("InelFlagC12",true,false);
  InelC12Cmd->SetDefaultValue(false);

  PartCapTypeCmd = new G4UIcmdWithAString("/HadronPhysicsList/PartCapType",this);
  PartCapTypeCmd->SetGuidance("Choose resonant or non-resonant radiative capture (resonant, non-resonant).");
  PartCapTypeCmd->SetParameterName("PartCapType",true,false);
  PartCapTypeCmd->SetCandidates("resonant non-resonant");
  PartCapTypeCmd->SetDefaultValue("resonant");

  PartCapCmd = new G4UIcmdWithABool("/HadronPhysicsList/PartCapFlag",this);
  PartCapCmd->SetGuidance("Set the flag for radiative capture reaction.");
  PartCapCmd->SetParameterName("PartCap",true,false);
  PartCapCmd->SetDefaultValue(false);
}

HadronPhysicsListMessenger::~HadronPhysicsListMessenger()
{
  delete HPinelProtCmd;
  delete HPinelDeutCmd;
  delete HPinelTritCmd;
  delete HPinelHe3Cmd;
  delete HPinelAlphCmd;
  delete HPinelC12Cmd;
  delete InelProtCmd;
  delete InelDeutCmd;
  delete InelTritCmd;
  delete InelHe3Cmd;
  delete InelAlphCmd;
  delete InelC12Cmd;
  delete PartCapTypeCmd;
  delete PartCapCmd;
}

void HadronPhysicsListMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  //G4cout << "newValue: " << newValue << G4endl;
  if(command == HPinelProtCmd) {
    G4String name = newValue;
    hadronPhysicsList->SetHPinelFlagProt(HPinelProtCmd->GetNewBoolValue(name));
  }
  else if(command == HPinelDeutCmd) {
    G4String name = newValue;
    hadronPhysicsList->SetHPinelFlagDeut(HPinelDeutCmd->GetNewBoolValue(name));
  }
  else if(command == HPinelTritCmd) {
    G4String name = newValue;
    hadronPhysicsList->SetHPinelFlagTrit(HPinelTritCmd->GetNewBoolValue(name));
  }
  else if(command == HPinelHe3Cmd) {
    G4String name = newValue;
    hadronPhysicsList->SetHPinelFlagHe3(HPinelHe3Cmd->GetNewBoolValue(name));
  }
  else if(command == HPinelAlphCmd) {
    G4String name = newValue;
    hadronPhysicsList->SetHPinelFlagAlph(HPinelAlphCmd->GetNewBoolValue(name));
  }
  else if(command == HPinelC12Cmd) {
    G4String name = newValue;
    hadronPhysicsList->SetHPinelFlagC12(HPinelC12Cmd->GetNewBoolValue(name));
  }
  else if(command == InelProtCmd) {
    G4String name = newValue;
    hadronPhysicsList->SetInelFlagProt(InelProtCmd->GetNewBoolValue(name));
  }
  else if(command == InelDeutCmd) {
    G4String name = newValue;
    hadronPhysicsList->SetInelFlagDeut(InelDeutCmd->GetNewBoolValue(name));
  }
  else if(command == InelTritCmd) {
    G4String name = newValue;
    hadronPhysicsList->SetInelFlagTrit(InelTritCmd->GetNewBoolValue(name));
  }
  else if(command == InelHe3Cmd) {
    G4String name = newValue;
    hadronPhysicsList->SetInelFlagHe3(InelHe3Cmd->GetNewBoolValue(name));
  }
  else if(command == InelAlphCmd) {
    G4String name = newValue;
    hadronPhysicsList->SetInelFlagAlph(InelAlphCmd->GetNewBoolValue(name));
  }
  else if(command == InelC12Cmd) {
    G4String name = newValue;
    hadronPhysicsList->SetInelFlagC12(InelC12Cmd->GetNewBoolValue(name));
  }
  else if(command == PartCapTypeCmd) {
    hadronPhysicsList->SetPartCapType(newValue);
  }
  else if(command == PartCapCmd) {
    hadronPhysicsList->SetPartCapFlag(PartCapCmd->GetNewBoolValue(newValue));
  }
}
