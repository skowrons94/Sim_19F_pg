#include "DetectorConstructionMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* DC):detectorConstruction(DC)
{ 
  DCDir = new G4UIdirectory("/DetectorConstruction/");
  DCDir->SetGuidance("DetectorConstruction control.");

  SourcePosCmd = new G4UIcommand("/DetectorConstruction/SourcePos",this);
  SourcePosCmd->SetGuidance("Set position of Source");
  SourcePosCmd->SetGuidance("format: x y z unit");
  G4UIparameter* SourcePosX = new G4UIparameter("SourcePosX",'d',false);
  SourcePosX->SetGuidance("PosX");
  SourcePosCmd->SetParameter(SourcePosX);
  G4UIparameter* SourcePosY = new G4UIparameter("SourcePosY",'d',false);
  SourcePosY->SetGuidance("PosY");
  SourcePosCmd->SetParameter(SourcePosY);
  G4UIparameter* SourcePosZ = new G4UIparameter("SourcePosZ",'d',false);
  SourcePosZ->SetGuidance("PosZ");
  SourcePosCmd->SetParameter(SourcePosZ);
  G4UIparameter* SourcePosUnit = new G4UIparameter("SourcePosUnit",'s',false);
  SourcePosUnit->SetGuidance("Pos Unit");
  SourcePosCmd->SetParameter(SourcePosUnit);
  
  MaxStepCmd = new G4UIcommand("/DetectorConstruction/MaxStep",this);
  MaxStepCmd->SetGuidance("Set the maximum step size in the target");
  MaxStepCmd->SetGuidance("format: x unit");
  G4UIparameter* MaxStepVal = new G4UIparameter("MaxStepVal",'d',false);
  MaxStepVal->SetGuidance("MaxStepVal");
  MaxStepCmd->SetParameter(MaxStepVal);
  G4UIparameter* MaxStepUnit = new G4UIparameter("MaxStepUnit",'s',false);
  MaxStepUnit->SetGuidance("MaxStep Unit");
  MaxStepCmd->SetParameter(MaxStepUnit);

  BGO14NpPosCmd = new G4UIcommand("/DetectorConstruction/BGO14NpPos",this);
  BGO14NpPosCmd->SetGuidance("Set position of BGO14Np");
  BGO14NpPosCmd->SetGuidance("format: x y z unit");
  G4UIparameter* BGO14NpPosX = new G4UIparameter("BGO14NpPosX",'d',false);
  BGO14NpPosX->SetGuidance("BGO14NpPosX");
  BGO14NpPosCmd->SetParameter(BGO14NpPosX);
  G4UIparameter* BGO14NpPosY = new G4UIparameter("BGO14NpPosY",'d',false);
  BGO14NpPosY->SetGuidance("BGO14NpPosY");
  BGO14NpPosCmd->SetParameter(BGO14NpPosY);
  G4UIparameter* BGO14NpPosZ = new G4UIparameter("BGO14NpPosZ",'d',false);
  BGO14NpPosZ->SetGuidance("BGO14NpPosZ");
  BGO14NpPosCmd->SetParameter(BGO14NpPosZ);
  G4UIparameter* BGO14NpPosUnit = new G4UIparameter("BGO14NpPosUnit",'s',false);
  BGO14NpPosUnit->SetGuidance("BGO14NpPos Unit");
  BGO14NpPosCmd->SetParameter(BGO14NpPosUnit);
  
  BGO14NpTargetHolderPosCmd = new G4UIcommand("/DetectorConstruction/BGO14NpTargetHolderPos",this);
  BGO14NpTargetHolderPosCmd->SetGuidance("Set position of BGO14Np Target Holder");
  BGO14NpTargetHolderPosCmd->SetGuidance("format: x y z unit");
  G4UIparameter* BGO14NpTargetHolderPosX = new G4UIparameter("BGO14NpTargetHolderPosX",'d',false);
  BGO14NpTargetHolderPosX->SetGuidance("BGO14NpTargetHolderPosX");
  BGO14NpTargetHolderPosCmd->SetParameter(BGO14NpTargetHolderPosX);
  G4UIparameter* BGO14NpTargetHolderPosY = new G4UIparameter("BGO14NpTargetHolderPosY",'d',false);
  BGO14NpTargetHolderPosY->SetGuidance("BGO14NpTargetHolderPosY");
  BGO14NpTargetHolderPosCmd->SetParameter(BGO14NpTargetHolderPosY);
  G4UIparameter* BGO14NpTargetHolderPosZ = new G4UIparameter("BGO14NpTargetHolderPosZ",'d',false);
  BGO14NpTargetHolderPosZ->SetGuidance("BGO14NpTargetHolderPosZ");
  BGO14NpTargetHolderPosCmd->SetParameter(BGO14NpTargetHolderPosZ);
  G4UIparameter* BGO14NpTargetHolderPosUnit = new G4UIparameter("BGO14NpTargetHolderPosUnit",'s',false);
  BGO14NpTargetHolderPosUnit->SetGuidance("BGO14NpTargetHolderPos Unit");
  BGO14NpTargetHolderPosCmd->SetParameter(BGO14NpTargetHolderPosUnit);

  PhysicsCmd = new G4UIcmdWithAString("/DetectorConstruction/Physics",this);
  PhysicsCmd->SetGuidance("R for reaction or S for radioactive source.");
  PhysicsCmd->SetParameterName("Physics",true,true);
  PhysicsCmd->SetCandidates("R S");
  PhysicsCmd->SetDefaultValue("S");

  SourceHolderCmd = new G4UIcmdWithAString("/DetectorConstruction/SourceHolder",this);
  SourceHolderCmd->SetGuidance("A for 60Co and 137Cs, B for 133Ba.");
  SourceHolderCmd->SetParameterName("SourceHolder",true,true);
  SourceHolderCmd->SetCandidates("A B");
  SourceHolderCmd->SetDefaultValue("A");
}

DetectorConstructionMessenger::~DetectorConstructionMessenger()
{
  delete SourcePosCmd;
  delete MaxStepCmd;
  delete BGO14NpPosCmd;
  delete BGO14NpTargetHolderPosCmd;
  delete PhysicsCmd;
  delete SourceHolderCmd;
}

void DetectorConstructionMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if (command == SourcePosCmd) {
    G4double v1, v2, v3;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> v2 >> v3 >> unt;
    G4ThreeVector vec(v1,v2,v3);
    vec *= G4UIcommand::ValueOf(unt);
    detectorConstruction->SetSourcePos(vec);
  }
  else if (command == BGO14NpPosCmd) {
    G4double v1, v2, v3;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> v2 >> v3 >> unt;
    G4ThreeVector vec(v1,v2,v3);
    vec *= G4UIcommand::ValueOf(unt);
    detectorConstruction->SetBGO14NpPos(vec);
  }
  else if (command == BGO14NpTargetHolderPosCmd) {
    G4double v1, v2, v3;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> v2 >> v3 >> unt;
    G4ThreeVector vec(v1,v2,v3);
    vec *= G4UIcommand::ValueOf(unt);
    detectorConstruction->SetBGO14NpTargetHolderPos(vec);
  }
  else if(command == PhysicsCmd) {
    detectorConstruction->SetPhysics(newValue);
  }
  else if(command == SourceHolderCmd) {
    detectorConstruction->SetSourceHolder(newValue);
  }
  
  else if (command == MaxStepCmd) {
    G4double v1;
    G4String unt;
    std::istringstream is(newValue);
    is >> v1 >> unt;
    v1 *= G4UIcommand::ValueOf(unt);
    detectorConstruction->SetMaxStep(v1);
  }
}
