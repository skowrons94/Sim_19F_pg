#include "TargetChamber16opMessenger.hh"

#include "TargetChamber16op.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

TargetChamber16opMessenger::TargetChamber16opMessenger(TargetChamber16op* TARGETCHAMBER16OP):targetchamber16op(TARGETCHAMBER16OP)
{ 
  TARGETCH16OPDir = new G4UIdirectory("/TargetChamber16op/");
  TARGETCH16OPDir->SetGuidance("Target chamber 16op control.");
	
  TargetCh16opCmd = new G4UIcmdWithAString("/TargetChamber16op/TargetChamber16opType",this);
  TargetCh16opCmd->SetGuidance("Input the target chamber 16 op material. ");
  TargetCh16opCmd->SetParameterName("TargetChamber16opType",true,true);
  TargetCh16opCmd->SetCandidates("Al Steel");
  TargetCh16opCmd->SetDefaultValue("Al");
 
}

TargetChamber16opMessenger::~TargetChamber16opMessenger()
{
  delete TargetCh16opCmd;
}

void TargetChamber16opMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
 	if(command == TargetCh16opCmd ) {
     targetchamber16op->SetTargetCh16opMat(newValue);
  }
}
