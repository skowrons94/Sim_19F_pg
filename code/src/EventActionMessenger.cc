#include "EventActionMessenger.hh"

#include "EventAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

EventActionMessenger::EventActionMessenger(EventAction* EA):eventAction(EA)
{ 
  EADir = new G4UIdirectory("/EventAction/");
  EADir->SetGuidance("EventAction control.");

  NoiseBGO14NpCmd = new G4UIcmdWithADouble("/EventAction/NoiseBGO14Np",this);
  NoiseBGO14NpCmd->SetGuidance("Input the noise level in eV for BGO14Np.");
  NoiseBGO14NpCmd->SetParameterName("NoiseBGO14Np",true,true);
  NoiseBGO14NpCmd->SetDefaultValue(1.0);

  
}

EventActionMessenger::~EventActionMessenger()
{
  delete NoiseBGO14NpCmd;
}

void EventActionMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  //G4cout << "newValue: " << newValue << G4endl;
  if(command == NoiseBGO14NpCmd) {
    eventAction->SetNoiseBGO14Np(NoiseBGO14NpCmd->GetNewDoubleValue(newValue));
  }
}
