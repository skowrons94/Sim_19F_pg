#include "BGO14NpTargetMessenger.hh"

#include "BGO14NpTarget.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "globals.hh"

BGO14NpTargetMessenger::BGO14NpTargetMessenger(BGO14NpTarget* BGO14NPTARGET):bgo14NpTarget(BGO14NPTARGET)
{ 
  BGO14NPTARGETDir = new G4UIdirectory("/BGO14NpTarget/");
  BGO14NPTARGETDir->SetGuidance("BGO14Np Target control.");

  BGO14NpTargetCmd = new G4UIcommand("/BGO14NpTarget/BGOTargetSize",this);
  BGO14NpTargetCmd->SetGuidance("Input the 14Np target sizes R z in mm.");
  BGO14NpTargetCmd->SetGuidance("format: d0 d1");
  G4UIparameter* BGO14NpTargetSize0 = new G4UIparameter("BGO14NpTargetSize0",'d',false);
  BGO14NpTargetSize0->SetGuidance("BGO14NpTargetSize0");
  BGO14NpTargetCmd->SetParameter(BGO14NpTargetSize0);
  G4UIparameter* BGO14NpTargetSize1 = new G4UIparameter("BGO14NpTargetSize1",'d',false);
  BGO14NpTargetSize1->SetGuidance("BGO14NpTargetSize1");
  BGO14NpTargetCmd->SetParameter(BGO14NpTargetSize1);
  
}

BGO14NpTargetMessenger::~BGO14NpTargetMessenger()
{
  delete BGO14NpTargetCmd;

}

void BGO14NpTargetMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if (command == BGO14NpTargetCmd) {
    G4double d0, d1;
    std::istringstream is(newValue);
    is >> d0 >> d1;
    std::vector<G4double> vec = {d0,d1};
    bgo14NpTarget->SetBGO14NpTargetSize(vec);
  }
  
}
