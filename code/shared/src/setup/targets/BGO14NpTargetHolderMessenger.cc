#include "BGO14NpTargetHolderMessenger.hh"

#include "BGO14NpTargetHolder.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "globals.hh"

BGO14NpTargetHolderMessenger::BGO14NpTargetHolderMessenger(BGO14NpTargetHolder* BGO14NPTARGETHolder):bgo14NpTargetHolder(BGO14NPTARGETHolder)
{ 
  BGO14NPTARGETHOLDERDir = new G4UIdirectory("/BGO14NpTarget/");
  BGO14NPTARGETHOLDERDir->SetGuidance("BGO14Np Target control.");

  BGO14NpTargetHolderCmd = new G4UIcommand("/BGO14NpTarget/TargetBackingThickness",this);
  BGO14NpTargetHolderCmd->SetGuidance("Input the target backing thickness z in mm.");
  BGO14NpTargetHolderCmd->SetGuidance("format: d0");
  G4UIparameter* TargetBackingThickness = new G4UIparameter("TargetBackingThickness",'d',false);
  TargetBackingThickness->SetGuidance("TargetBackingThickness");
  BGO14NpTargetHolderCmd->SetParameter(TargetBackingThickness);
}

BGO14NpTargetHolderMessenger::~BGO14NpTargetHolderMessenger()
{
  delete BGO14NpTargetHolderCmd;
}

void BGO14NpTargetHolderMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if (command == BGO14NpTargetHolderCmd) {
    G4double d0;
    std::istringstream is(newValue);
    is >> d0;
    std::vector<G4double> vec = {d0};
    bgo14NpTargetHolder->SetBGO14NpTargetBackingThickness(vec);
  }
}
