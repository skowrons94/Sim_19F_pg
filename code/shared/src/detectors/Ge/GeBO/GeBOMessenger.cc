#include "GeBOMessenger.hh"

#include "GeBO.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

GeBOMessenger::GeBOMessenger(GeBO* GEBO):geBO(GEBO)
{ 
  GEBODir = new G4UIdirectory("/GeBO/");
  GEBODir->SetGuidance("GeBO control.");

  DeadSideCmd = new G4UIcommand("/GeBO/DeadSide",this);
  DeadSideCmd->SetGuidance("Set dead layer for the side of the GeBO detector");
  DeadSideCmd->SetGuidance("format: x unit");
  G4UIparameter* DeadSide = new G4UIparameter("DeadSide",'d',false);
  DeadSide->SetGuidance("DeadSide");
  DeadSideCmd->SetParameter(DeadSide);
  G4UIparameter* DeadSideUnit = new G4UIparameter("DeadSideUnit",'s',false);
  DeadSideUnit->SetGuidance("DeadSide Unit");
  DeadSideCmd->SetParameter(DeadSideUnit);

  DeadFrontCmd = new G4UIcommand("/GeBO/DeadFront",this);
  DeadFrontCmd->SetGuidance("Set dead layer for the front of the GeBO detector");
  DeadFrontCmd->SetGuidance("format: x unit");
  G4UIparameter* DeadFront = new G4UIparameter("DeadFront",'d',false);
  DeadFront->SetGuidance("DeadFront");
  DeadFrontCmd->SetParameter(DeadFront);
  G4UIparameter* DeadFrontUnit = new G4UIparameter("DeadFrontUnit",'s',false);
  DeadFrontUnit->SetGuidance("DeadFront Unit");
  DeadFrontCmd->SetParameter(DeadFrontUnit);

  DeadBackCmd = new G4UIcommand("/GeBO/DeadBack",this);
  DeadBackCmd->SetGuidance("Set dead layer for the back of the GeBO detector");
  DeadBackCmd->SetGuidance("format: x unit");
  G4UIparameter* DeadBack = new G4UIparameter("DeadBack",'d',false);
  DeadBack->SetGuidance("DeadBack");
  DeadBackCmd->SetParameter(DeadBack);
  G4UIparameter* DeadBackUnit = new G4UIparameter("DeadBackUnit",'s',false);
  DeadBackUnit->SetGuidance("DeadBack Unit");
  DeadBackCmd->SetParameter(DeadBackUnit);

  DeadHoleCmd = new G4UIcommand("/GeBO/DeadHole",this);
  DeadHoleCmd->SetGuidance("Set dead layer around the hole of the GeBO detector");
  DeadHoleCmd->SetGuidance("format: x unit");
  G4UIparameter* DeadHole = new G4UIparameter("DeadHole",'d',false);
  DeadHole->SetGuidance("DeadHole");
  DeadHoleCmd->SetParameter(DeadHole);
  G4UIparameter* DeadHoleUnit = new G4UIparameter("DeadHoleUnit",'s',false);
  DeadHoleUnit->SetGuidance("DeadHole Unit");
  DeadHoleCmd->SetParameter(DeadHoleUnit);

}

GeBOMessenger::~GeBOMessenger()
{
  delete DeadSideCmd;
  delete DeadFrontCmd;
  delete DeadBackCmd;
  delete DeadHoleCmd;
}

void GeBOMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if (command == DeadSideCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    geBO->SetDeadSide(v1);
  }
  else if (command == DeadFrontCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    geBO->SetDeadFront(v1);
  }
  else if (command == DeadBackCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    geBO->SetDeadBack(v1);
  }
  else if (command == DeadHoleCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    geBO->SetDeadHole(v1);
  }
}
