#include "Dome23napaMessenger.hh"
#include "Dome23napa.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"

Dome23napaMessenger::Dome23napaMessenger(Dome23napa* DOME23NAPA)
  :dome23napa(DOME23NAPA)

{ 
  Dome23napaDir = new G4UIdirectory("/Dome23napa/");
  Dome23napaDir->SetGuidance("Dome control.");
  
  FileNameCmd = new G4UIcmdWithAString("/Dome23napa/gdmlfile",this);
  FileNameCmd->SetGuidance("Input the name for the gdml file.");
  FileNameCmd->SetParameterName("gdmlfile",true,true);

}

Dome23napaMessenger::~Dome23napaMessenger()
{
  delete FileNameCmd; 
}

void Dome23napaMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == FileNameCmd )
    { 
      dome23napa->SetFileName(newValue);
    }
}
