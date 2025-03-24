#include "GePDMessenger.hh"

#include "GePD.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

GePDMessenger::GePDMessenger(GePD* GEPD):gePD(GEPD)
{ 
  GEPDDir = new G4UIdirectory("/GePD/");
  GEPDDir->SetGuidance("GePD control.");

  DeadSideCmd = new G4UIcommand("/GePD/DeadSide",this);
  DeadSideCmd->SetGuidance("Set dead layer for the side of the GePD detector");
  DeadSideCmd->SetGuidance("format: x unit");
  G4UIparameter* DeadSide = new G4UIparameter("DeadSide",'d',false);
  DeadSide->SetGuidance("DeadSide");
  DeadSideCmd->SetParameter(DeadSide);
  G4UIparameter* DeadSideUnit = new G4UIparameter("DeadSideUnit",'s',false);
  DeadSideUnit->SetGuidance("DeadSide Unit");
  DeadSideCmd->SetParameter(DeadSideUnit);

  DeadFrontCmd = new G4UIcommand("/GePD/DeadFront",this);
  DeadFrontCmd->SetGuidance("Set dead layer for the front of the GePD detector");
  DeadFrontCmd->SetGuidance("format: x unit");
  G4UIparameter* DeadFront = new G4UIparameter("DeadFront",'d',false);
  DeadFront->SetGuidance("DeadFront");
  DeadFrontCmd->SetParameter(DeadFront);
  G4UIparameter* DeadFrontUnit = new G4UIparameter("DeadFrontUnit",'s',false);
  DeadFrontUnit->SetGuidance("DeadFront Unit");
  DeadFrontCmd->SetParameter(DeadFrontUnit);

  DeadBackCmd = new G4UIcommand("/GePD/DeadBack",this);
  DeadBackCmd->SetGuidance("Set dead layer for the back of the GePD detector");
  DeadBackCmd->SetGuidance("format: x unit");
  G4UIparameter* DeadBack = new G4UIparameter("DeadBack",'d',false);
  DeadBack->SetGuidance("DeadBack");
  DeadBackCmd->SetParameter(DeadBack);
  G4UIparameter* DeadBackUnit = new G4UIparameter("DeadBackUnit",'s',false);
  DeadBackUnit->SetGuidance("DeadBack Unit");
  DeadBackCmd->SetParameter(DeadBackUnit);

  DispCmd = new G4UIcommand("/GePD/Disp",this);
  DispCmd->SetGuidance("Set displacement for the ge crystal of the GePD detector");
  DispCmd->SetGuidance("format: x unit");
  G4UIparameter* Disp = new G4UIparameter("Disp",'d',false);
  Disp->SetGuidance("Disp");
  DispCmd->SetParameter(Disp);
  G4UIparameter* DispUnit = new G4UIparameter("DispUnit",'s',false);
  DispUnit->SetGuidance("Disp Unit");
  DispCmd->SetParameter(DispUnit);

}

GePDMessenger::~GePDMessenger()
{
  delete DeadSideCmd;
  delete DeadFrontCmd;
  delete DeadBackCmd;
  delete DispCmd;
}

void GePDMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if (command == DeadSideCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    gePD->SetDeadSide(v1);
  }
  else if (command == DeadFrontCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    gePD->SetDeadFront(v1);
  }
  else if (command == DeadBackCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    gePD->SetDeadBack(v1);
  }
  else if (command == DispCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    gePD->SetDisp(v1);
  }
}
