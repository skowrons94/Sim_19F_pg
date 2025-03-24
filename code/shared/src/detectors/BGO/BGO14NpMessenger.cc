#include "BGO14NpMessenger.hh"

#include "BGO14Np.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

BGO14NpMessenger::BGO14NpMessenger(BGO14Np* BGO14NP):bgo14Np(BGO14NP)
{ 
  BGO14NPDir = new G4UIdirectory("/BGO14Np/");
  BGO14NPDir->SetGuidance("BGO14Np control.");

  BGO14NpCmd = new G4UIcommand("/BGO14Np/BGODisp",this);
  BGO14NpCmd->SetGuidance("Input the BGO displacemente in mm.");
  BGO14NpCmd->SetGuidance("format: d0 d1 d2 d3 d4 d5");
  G4UIparameter* BGODisp0 = new G4UIparameter("BGODisp0",'d',false);
  BGODisp0->SetGuidance("BGODisp0");
  BGO14NpCmd->SetParameter(BGODisp0);
  G4UIparameter* BGODisp1 = new G4UIparameter("BGODisp1",'d',false);
  BGODisp1->SetGuidance("BGODisp1");
  BGO14NpCmd->SetParameter(BGODisp1);
  G4UIparameter* BGODisp2 = new G4UIparameter("BGODisp2",'d',false);
  BGODisp2->SetGuidance("BGODisp2");
  BGO14NpCmd->SetParameter(BGODisp2);
  G4UIparameter* BGODisp3 = new G4UIparameter("BGODisp3",'d',false);
  BGODisp3->SetGuidance("BGODisp3");
  BGO14NpCmd->SetParameter(BGODisp3);
  G4UIparameter* BGODisp4 = new G4UIparameter("BGODisp4",'d',false);
  BGODisp4->SetGuidance("BGODisp4");
  BGO14NpCmd->SetParameter(BGODisp4);
  G4UIparameter* BGODisp5 = new G4UIparameter("BGODisp5",'d',false);
  BGODisp5->SetGuidance("BGODisp5");
  BGO14NpCmd->SetParameter(BGODisp5);
}

BGO14NpMessenger::~BGO14NpMessenger()
{
  delete BGO14NpCmd;
}

void BGO14NpMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if (command == BGO14NpCmd) {
    G4double d0, d1, d2, d3, d4, d5;
    std::istringstream is(newValue);
    is >> d0 >> d1 >> d2 >> d3 >> d4 >> d5;
    std::vector<G4double> vec = {d0,d1,d2,d3,d4,d5};
    bgo14Np->SetBGODisp(vec);
  }
}
