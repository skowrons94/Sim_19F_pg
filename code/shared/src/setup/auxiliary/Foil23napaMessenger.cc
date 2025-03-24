#include "Foil23napaMessenger.hh"
#include "Foil23napa.hh"

#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"

#include "G4SystemOfUnits.hh"

Foil23napaMessenger::Foil23napaMessenger(Foil23napa* FOIL23NAPA)
  :foil23napa(FOIL23NAPA)
{
    Foil23napaDir = new G4UIdirectory("/Foil23napa/");
    Foil23napaDir->SetGuidance("Foils thickness control.");

    FoilTCmd = new G4UIcommand("/Foil23napa/FoilThickness",this);
    FoilTCmd->SetGuidance("Set Mylar foil thickness");
    FoilTCmd->SetGuidance("format: x unit");
    G4UIparameter* FoilT = new G4UIparameter("FoilT",'d',false);
    FoilT->SetGuidance("FoilT");
    FoilTCmd->SetParameter(FoilT);
    G4UIparameter* FoilTUnit = new G4UIparameter("FoilTUnit",'s',false);
    FoilTUnit->SetGuidance("FoilT Unit");
    FoilTCmd->SetParameter(FoilTUnit);
    FoilT->SetDefaultValue(3.46*um);
    
    FoilAlTCmd = new G4UIcommand("/Foil23napa/FoilAlThickness",this);
    FoilAlTCmd->SetGuidance("Set Aluminum foil thickness");
    FoilAlTCmd->SetGuidance("format: x unit");
    G4UIparameter* FoilAlT = new G4UIparameter("FoilAlT",'d',false);
    FoilAlT->SetGuidance("FoilAlT");
    FoilAlTCmd->SetParameter(FoilAlT);
    G4UIparameter* FoilAlTUnit = new G4UIparameter("FoilAlTUnit",'s',false);
    FoilAlTUnit->SetGuidance("FoilAlT Unit");
    FoilAlTCmd->SetParameter(FoilAlTUnit);
    FoilAlT->SetDefaultValue(0.04*um);

}

Foil23napaMessenger::~Foil23napaMessenger()
{

    delete FoilTCmd;
    delete FoilAlTCmd;
}

void Foil23napaMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
if(command == FoilTCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    foil23napa->SetFoilThickness(v1);
    }
    else if (command == FoilAlTCmd) {
      G4double v1;
      G4String unt;
      std::istringstream is(newValue);
      is >> v1 >> unt;
      v1 *= G4UIcommand::ValueOf(unt);
      foil23napa->SetFoilAlThickness(v1);
    }
    
}

