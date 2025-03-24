#include "TargetHolderOuterFront10bMessenger.hh"
#include "TargetHolderOuterFront10b.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"

TargetHolderOuterFront10bMessenger::TargetHolderOuterFront10bMessenger(TargetHolderOuterFront10b* TARGETHOLDEROUTERFRONT10B)
  :targetholderouterfront10b(TARGETHOLDEROUTERFRONT10B)

{ 
  TargetHolderOuterFront10bDir = new G4UIdirectory("/TargetHolderOuterFront10b/");
  TargetHolderOuterFront10bDir->SetGuidance("TargetHolderOuterFront control.");
  
  FileNameCmd = new G4UIcmdWithAString("/TargetHolderOuterFront10b/gdmlfile",this);
  FileNameCmd->SetGuidance("Input the name for the gdml file.");
  FileNameCmd->SetParameterName("gdmlfile",true,true);

}

TargetHolderOuterFront10bMessenger::~TargetHolderOuterFront10bMessenger()
{
  delete FileNameCmd; 
}

void TargetHolderOuterFront10bMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == FileNameCmd )
    { 
      targetholderouterfront10b->SetFileName(newValue);
    }
}
