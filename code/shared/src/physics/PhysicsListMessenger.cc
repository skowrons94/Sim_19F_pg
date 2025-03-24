#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

PhysicsListMessenger::PhysicsListMessenger(PhysicsList* PL):physicsList(PL)
{ 
  PhysDir = new G4UIdirectory("/PhysicsList/");
  PhysDir->SetGuidance("PhysicsList control.");

  EmPhysCmd = new G4UIcmdWithAString("/PhysicsList/EmPhysics",this);
  EmPhysCmd->SetGuidance("Input the electromagnetic physics (standard, lowEP, standardNR).");
  EmPhysCmd->SetParameterName("EmPhysics",true,true);
  EmPhysCmd->SetCandidates("standard lowEP standardNR");
  EmPhysCmd->SetDefaultValue("lowEP");

  HadrPhysCmd = new G4UIcmdWithABool("/PhysicsList/HadronPhysicsFlag",this);
  HadrPhysCmd->SetGuidance("Set the flag for hadronphysics.");
  HadrPhysCmd->SetParameterName("HadrPhys",true,true);
  HadrPhysCmd->SetDefaultValue("false");
}

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete EmPhysCmd;
  delete HadrPhysCmd;
}

void PhysicsListMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  //G4cout << "newValue: " << newValue << G4endl;
  if(command == EmPhysCmd) {
    physicsList->SetEmPhysics(newValue);
  }
  else if(command == HadrPhysCmd) {
    physicsList->SetHadrPhysFlag(HadrPhysCmd->GetNewBoolValue(newValue));
  }
}
