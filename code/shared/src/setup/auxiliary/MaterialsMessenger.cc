#include "MaterialsMessenger.hh"

#include "Materials.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

MaterialsMessenger::MaterialsMessenger(Materials* M):materials(M)
{ 
  MDir = new G4UIdirectory("/Materials/");
  MDir->SetGuidance("Materials control.");

  GasTypeCmd = new G4UIcmdWithAString("/Materials/GasType",this);
  GasTypeCmd->SetGuidance("Input the gas type.");
  GasTypeCmd->SetParameterName("GasType",true,true);
  GasTypeCmd->SetCandidates("21Ne 20Ne 22Ne MixNe 14N 2H air vacuum");
  GasTypeCmd->SetDefaultValue("MixNe");
  
  Layer0TypeCmd = new G4UIcmdWithAString("/Materials/Layer0Type",this);
  Layer0TypeCmd->SetGuidance("Input the BGO Target Layer 0 type of 16Op reaction. ");
  Layer0TypeCmd->SetParameterName("Layer0Type",true,true);
  Layer0TypeCmd->SetCandidates("TiN Ti14N Ti15N 14N 10B 27Al Ta2O165 MixB 12C 9Be 10B11B TaF5 CaF2 FeF3");
  Layer0TypeCmd->SetDefaultValue("Ta2O165");

  TargetBackingCmd = new G4UIcmdWithAString("/Materials/TargetBacking",this);
  TargetBackingCmd->SetGuidance("Input the Target backing material.");
  TargetBackingCmd->SetParameterName("TargetBacking",true,true);
  TargetBackingCmd->SetCandidates("Ta W Ti Cu");
  TargetBackingCmd->SetDefaultValue("Ta");

  GasPrChCmd = new G4UIcommand("/Materials/GasPressureChamber",this);
  GasPrChCmd->SetGuidance("Input the gas pressure in the chamber slices in bar.");
  GasPrChCmd->SetGuidance("format: p0 p1 p2 p3 p4 p5 p6");
  G4UIparameter* GasPrCh0 = new G4UIparameter("GasPrCh0",'d',false);
  GasPrCh0->SetGuidance("GasPrCh0");
  GasPrChCmd->SetParameter(GasPrCh0);
  G4UIparameter* GasPrCh1 = new G4UIparameter("GasPrCh1",'d',false);
  GasPrCh1->SetGuidance("GasPrCh1");
  GasPrChCmd->SetParameter(GasPrCh1);
  G4UIparameter* GasPrCh2 = new G4UIparameter("GasPrCh2",'d',false);
  GasPrCh2->SetGuidance("GasPrCh2");
  GasPrChCmd->SetParameter(GasPrCh2);
  G4UIparameter* GasPrCh3 = new G4UIparameter("GasPrCh3",'d',false);
  GasPrCh3->SetGuidance("GasPrCh3");
  GasPrChCmd->SetParameter(GasPrCh3);
  G4UIparameter* GasPrCh4 = new G4UIparameter("GasPrCh4",'d',false);
  GasPrCh4->SetGuidance("GasPrCh4");
  GasPrChCmd->SetParameter(GasPrCh4);
  G4UIparameter* GasPrCh5 = new G4UIparameter("GasPrCh5",'d',false);
  GasPrCh5->SetGuidance("GasPrCh5");
  GasPrChCmd->SetParameter(GasPrCh5);
  G4UIparameter* GasPrCh6 = new G4UIparameter("GasPrCh6",'d',false);
  GasPrCh6->SetGuidance("GasPrCh6");
  GasPrChCmd->SetParameter(GasPrCh6);

  GasTChCmd = new G4UIcommand("/Materials/GasTemperatureChamber",this);
  GasTChCmd->SetGuidance("Input the gas temperature in K.");
  GasTChCmd->SetGuidance("format: t0 t1 t2 t3 t4 t5 t6");
  G4UIparameter* GasTCh0 = new G4UIparameter("GasTCh0",'d',false);
  GasTCh0->SetGuidance("GasTCh0");
  GasTChCmd->SetParameter(GasTCh0);
  G4UIparameter* GasTCh1 = new G4UIparameter("GasTCh1",'d',false);
  GasTCh1->SetGuidance("GasTCh1");
  GasTChCmd->SetParameter(GasTCh1);
  G4UIparameter* GasTCh2 = new G4UIparameter("GasTCh2",'d',false);
  GasTCh2->SetGuidance("GasTCh2");
  GasTChCmd->SetParameter(GasTCh2);
  G4UIparameter* GasTCh3 = new G4UIparameter("GasTCh3",'d',false);
  GasTCh3->SetGuidance("GasTCh3");
  GasTChCmd->SetParameter(GasTCh3);
  G4UIparameter* GasTCh4 = new G4UIparameter("GasTCh4",'d',false);
  GasTCh4->SetGuidance("GasTCh4");
  GasTChCmd->SetParameter(GasTCh4);
  G4UIparameter* GasTCh5 = new G4UIparameter("GasTCh5",'d',false);
  GasTCh5->SetGuidance("GasTCh5");
  GasTChCmd->SetParameter(GasTCh5);
  G4UIparameter* GasTCh6 = new G4UIparameter("GasTCh6",'d',false);
  GasTCh6->SetGuidance("GasTCh6");
  GasTChCmd->SetParameter(GasTCh6);

  GasPrColCmd = new G4UIcommand("/Materials/GasPressureCollimator",this);
  GasPrColCmd->SetGuidance("Input the gas pressure in the collimator slices in bar.");
  GasPrColCmd->SetGuidance("format: p1 p2 p3 p4 p5");
  G4UIparameter* GasPrCol1 = new G4UIparameter("GasPrCol1",'d',false);
  GasPrCol1->SetGuidance("GasPrCol1");
  GasPrColCmd->SetParameter(GasPrCol1);
  G4UIparameter* GasPrCol2 = new G4UIparameter("GasPrCol2",'d',false);
  GasPrCol2->SetGuidance("GasPrCol2");
  GasPrColCmd->SetParameter(GasPrCol2);
  G4UIparameter* GasPrCol3 = new G4UIparameter("GasPrCol3",'d',false);
  GasPrCol3->SetGuidance("GasPrCol3");
  GasPrColCmd->SetParameter(GasPrCol3);
  G4UIparameter* GasPrCol4 = new G4UIparameter("GasPrCol4",'d',false);
  GasPrCol4->SetGuidance("GasPrCol4");
  GasPrColCmd->SetParameter(GasPrCol4);
  G4UIparameter* GasPrCol5 = new G4UIparameter("GasPrCol5",'d',false);
  GasPrCol5->SetGuidance("GasPrCol5");
  GasPrColCmd->SetParameter(GasPrCol5);

  GasTColCmd = new G4UIcommand("/Materials/GasTemperatureCollimator",this);
  GasTColCmd->SetGuidance("Input the gas temperature in K.");
  GasTColCmd->SetGuidance("format: t1 t2 t3 t4 t5");
  G4UIparameter* GasTCol1 = new G4UIparameter("GasTCol1",'d',false);
  GasTCol1->SetGuidance("GasTCol1");
  GasTColCmd->SetParameter(GasTCol1);
  G4UIparameter* GasTCol2 = new G4UIparameter("GasTCol2",'d',false);
  GasTCol2->SetGuidance("GasTCol2");
  GasTColCmd->SetParameter(GasTCol2);
  G4UIparameter* GasTCol3 = new G4UIparameter("GasTCol3",'d',false);
  GasTCol3->SetGuidance("GasTCol3");
  GasTColCmd->SetParameter(GasTCol3);
  G4UIparameter* GasTCol4 = new G4UIparameter("GasTCol4",'d',false);
  GasTCol4->SetGuidance("GasTCol4");
  GasTColCmd->SetParameter(GasTCol4);
  G4UIparameter* GasTCol5 = new G4UIparameter("GasTCol5",'d',false);
  GasTCol5->SetGuidance("GasTCol5");
  GasTColCmd->SetParameter(GasTCol5);

  GasPrPipeCmd = new G4UIcommand("/Materials/GasPressurePipe",this);
  GasPrPipeCmd->SetGuidance("Input the gas pressure in the beampipe slices in bar.");
  GasPrPipeCmd->SetGuidance("format: p1 p2 p3 p4 p5");
  G4UIparameter* GasPrPipe1 = new G4UIparameter("GasPrPipe1",'d',false);
  GasPrPipe1->SetGuidance("GasPrPipe1");
  GasPrPipeCmd->SetParameter(GasPrPipe1);
  G4UIparameter* GasPrPipe2 = new G4UIparameter("GasPrPipe2",'d',false);
  GasPrPipe2->SetGuidance("GasPrPipe2");
  GasPrPipeCmd->SetParameter(GasPrPipe2);
  G4UIparameter* GasPrPipe3 = new G4UIparameter("GasPrPipe3",'d',false);
  GasPrPipe3->SetGuidance("GasPrPipe3");
  GasPrPipeCmd->SetParameter(GasPrPipe3);
  G4UIparameter* GasPrPipe4 = new G4UIparameter("GasPrPipe4",'d',false);
  GasPrPipe4->SetGuidance("GasPrPipe4");
  GasPrPipeCmd->SetParameter(GasPrPipe4);
  G4UIparameter* GasPrPipe5 = new G4UIparameter("GasPrPipe5",'d',false);
  GasPrPipe5->SetGuidance("GasPrPipe5");
  GasPrPipeCmd->SetParameter(GasPrPipe5);

  GasTPipeCmd = new G4UIcommand("/Materials/GasTemperaturePipe",this);
  GasTPipeCmd->SetGuidance("Input the gas temperature in K.");
  GasTPipeCmd->SetGuidance("format: t1 t2 t3 t4 t5");
  G4UIparameter* GasTPipe1 = new G4UIparameter("GasTPipe1",'d',false);
  GasTPipe1->SetGuidance("GasTPipe1");
  GasTPipeCmd->SetParameter(GasTPipe1);
  G4UIparameter* GasTPipe2 = new G4UIparameter("GasTPipe2",'d',false);
  GasTPipe2->SetGuidance("GasTPipe2");
  GasTPipeCmd->SetParameter(GasTPipe2);
  G4UIparameter* GasTPipe3 = new G4UIparameter("GasTPipe3",'d',false);
  GasTPipe3->SetGuidance("GasTPipe3");
  GasTPipeCmd->SetParameter(GasTPipe3);
  G4UIparameter* GasTPipe4 = new G4UIparameter("GasTPipe4",'d',false);
  GasTPipe4->SetGuidance("GasTPipe4");
  GasTPipeCmd->SetParameter(GasTPipe4);
  G4UIparameter* GasTPipe5 = new G4UIparameter("GasTPipe5",'d',false);
  GasTPipe5->SetGuidance("GasTPipe5");
  GasTPipeCmd->SetParameter(GasTPipe5);
  
  MixNeAbCmd = new G4UIcommand("/Materials/MixNeAbundance",this);
  MixNeAbCmd->SetGuidance("Input the abundance of Neon gas mixture.");
  MixNeAbCmd->SetGuidance("format: ab20Ne ab21Ne ab22Ne");
  G4UIparameter* MixNeAb20Ne = new G4UIparameter("MixNeAb20Ne",'d',false);
  MixNeAb20Ne->SetGuidance("MixNeAb20Ne");
  MixNeAb20Ne->SetDefaultValue(10);
  MixNeAbCmd->SetParameter(MixNeAb20Ne);
  G4UIparameter* MixNeAb21Ne = new G4UIparameter("MixNeAb21Ne",'d',false);
  MixNeAb21Ne->SetGuidance("MixNeAb21Ne");
  MixNeAb21Ne->SetDefaultValue(80);
  MixNeAbCmd->SetParameter(MixNeAb21Ne);
  G4UIparameter* MixNeAb22Ne = new G4UIparameter("MixNeAb22Ne",'d',false);
  MixNeAb22Ne->SetGuidance("MixNeAb22Ne");
  MixNeAb22Ne->SetDefaultValue(20);
  MixNeAbCmd->SetParameter(MixNeAb22Ne);

  MixBAbCmd = new G4UIcommand("/Materials/MixBAbundance",this);
  MixBAbCmd->SetGuidance("Input the abundance of Boron target mixture.");
  MixBAbCmd->SetGuidance("format: ab10B ab11B");
  G4UIparameter* MixBAb10B = new G4UIparameter("MixBAb10B",'d',false);
  MixBAb10B->SetGuidance("MixBAb10B");
  MixBAb10B->SetDefaultValue(20);
  MixBAbCmd->SetParameter(MixBAb10B);
  G4UIparameter* MixBAb11B = new G4UIparameter("MixBAb11B",'d',false);
  MixBAb11B->SetGuidance("MixBAb11B");
  MixBAb11B->SetDefaultValue(80);
  MixBAbCmd->SetParameter(MixBAb11B);

  MixWrCmd = new G4UIcommand("/Materials/MixWr",this);
  MixWrCmd->SetGuidance("Input the target weigth ratios.");
  MixWrCmd->SetGuidance("format: WrB WrBe");
  G4UIparameter* MixWrB = new G4UIparameter("MixWrB",'d',false);
  MixWrB->SetGuidance("MixWrB");
  MixWrB->SetDefaultValue(0.99);
  MixWrCmd->SetParameter(MixWrB);
  G4UIparameter* MixWrBe = new G4UIparameter("MixWrBe",'d',false);
  MixWrBe->SetGuidance("MixWrBe");
  MixWrBe->SetDefaultValue(0.01);
  MixWrCmd->SetParameter(MixWrBe);

  MixRhoCmd = new G4UIcommand("/Materials/MixRho",this);
  MixRhoCmd->SetGuidance("Input the densities.");
  MixRhoCmd->SetGuidance("format: RhoB RhoBe");
  G4UIparameter* MixRhoB = new G4UIparameter("MixRhoB",'d',false);
  MixRhoB->SetGuidance("MixRhoB");
  MixRhoB->SetDefaultValue(0.99);
  MixRhoCmd->SetParameter(MixRhoB);
  G4UIparameter* MixRhoBe = new G4UIparameter("MixRhoBe",'d',false);
  MixRhoBe->SetGuidance("MixRhoBe");
  MixRhoBe->SetDefaultValue(0.01);
  MixRhoCmd->SetParameter(MixRhoBe);
}

MaterialsMessenger::~MaterialsMessenger()
{
  delete GasTypeCmd;
  delete Layer0TypeCmd;
  delete TargetBackingCmd;
  delete GasPrChCmd;
  delete GasTChCmd;
  delete GasPrColCmd;
  delete GasTColCmd;
  delete GasPrPipeCmd;
  delete GasTPipeCmd;
  delete MixNeAbCmd;
  delete MixBAbCmd;
  delete MixWrCmd;
  delete MixRhoCmd;
}

void MaterialsMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  //G4cout << "newValue: " << newValue << G4endl;
  if(command == GasTypeCmd) {
    materials->SetGasType(newValue);
  }
  else if(command == Layer0TypeCmd) {
    materials->SetLayer0Type(newValue);
  }
  else if(command == TargetBackingCmd) {
    materials->SetTargetBacking(newValue);
  }
  else if (command == GasPrChCmd) {
    G4double p0, p1, p2, p3, p4, p5, p6;
    std::istringstream is(newValue);
    is >> p0 >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
    std::vector<G4double> vec = {p0,p1,p2,p3,p4,p5,p6};
    materials->SetGasPrCh(vec);
  }
  else if (command == GasTChCmd) {
    G4double t0, t1, t2, t3, t4, t5, t6;
    std::istringstream is(newValue);
    is >> t0 >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;
    std::vector<G4double> vec = {t0,t1,t2,t3,t4,t5,t6};
    materials->SetGasTCh(vec);
  }
  else if (command == GasPrColCmd) {
    G4double p1, p2, p3, p4, p5;
    std::istringstream is(newValue);
    is >> p1 >> p2 >> p3 >> p4 >> p5;
    std::vector<G4double> vec = {p1,p2,p3,p4,p5};
    materials->SetGasPrCol(vec);
  }
  else if (command == GasTColCmd) {
    G4double t1, t2, t3, t4, t5;
    std::istringstream is(newValue);
    is >> t1 >> t2 >> t3 >> t4 >> t5;
    std::vector<G4double> vec = {t1,t2,t3,t4,t5};
    materials->SetGasTCol(vec);
  }
  else if (command == GasPrPipeCmd) {
    G4double p1, p2, p3, p4, p5;
    std::istringstream is(newValue);
    is >> p1 >> p2 >> p3 >> p4 >> p5;
    std::vector<G4double> vec = {p1,p2,p3,p4,p5};
    materials->SetGasPrPipe(vec);
  }
  else if (command == GasTPipeCmd) {
    G4double t1, t2, t3, t4, t5;
    std::istringstream is(newValue);
    is >> t1 >> t2 >> t3 >> t4 >> t5;
    std::vector<G4double> vec = {t1,t2,t3,t4,t5};
    materials->SetGasTPipe(vec);
  }
  else if (command == MixNeAbCmd) {
    G4double ab20Ne, ab21Ne, ab22Ne;
    std::istringstream is(newValue);
    is >> ab20Ne >> ab21Ne >> ab22Ne;
    std::vector<G4double> vec = {ab20Ne,ab21Ne,ab22Ne};
    materials->SetMixNeAb(vec);
  }
  else if (command == MixBAbCmd) {
    G4double ab10B, ab11B;
    std::istringstream is(newValue);
    is >> ab10B >> ab11B;
    std::vector<G4double> vec = {ab10B,ab11B};
    materials->SetMixBAb(vec);
  }
  else if (command == MixWrCmd) {
    G4double WrB, WrBe;
    std::istringstream is(newValue);
    is >> WrB >> WrBe;
    std::vector<G4double> vec = {WrB,WrBe};
    materials->SetMixWr(vec);
  }
  else if (command == MixRhoCmd) {
    G4double RhoB, RhoBe;
    std::istringstream is(newValue);
    is >> RhoB >> RhoBe;
    std::vector<G4double> vec = {RhoB,RhoBe};
    materials->SetMixRho(vec);
  }
}
