#include "Materials.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "MaterialsMessenger.hh"
#include "TFile.h"

Materials::Materials()
{ 
  materialsMessenger = new MaterialsMessenger(this);
}

Materials::~Materials()
{
  delete materialsMessenger;
}

Materials* Materials::instance = 0;

Materials* Materials::GetInstance()
{
  if (instance == 0)
    {
      instance = new Materials;
     
    }
  return instance;
}

G4Material* Materials::GetMaterial(G4String material)  
{
  //instancing G4NistManager
  nistMan = G4NistManager::Instance();
  nistMan->SetVerbose(0);

  //If not available at NIST, look for the local version of it
  G4Material* mat =  nistMan->FindOrBuildMaterial(material);
  if (!mat) {
    mat = G4Material::GetMaterial(material);
  }
  if (!mat) {G4cout << material << "  Not Found, Please Retry"<< G4endl;}
  return mat;
}


void Materials::CreateMaterials()
{

  nistMan = G4NistManager::Instance();
  nistMan->SetVerbose(1);
  
  // Define non NIST materials below.

  auto elCe  = nistMan->FindOrBuildElement("Ce");
  auto elBr  = nistMan->FindOrBuildElement("Br");
  auto elAl  = nistMan->FindOrBuildElement("Al");
  auto elTa  = nistMan->FindOrBuildElement("Ta");
  auto elN  = nistMan->FindOrBuildElement("N");
  auto elTi  = nistMan->FindOrBuildElement("Ti");
  auto elC  = nistMan->FindOrBuildElement("C");
  auto elH  = nistMan->FindOrBuildElement("H");
  auto elOx  = nistMan->FindOrBuildElement("O");
  auto elFe  = nistMan->FindOrBuildElement("Fe");
  auto elCr  = nistMan->FindOrBuildElement("Cr");
  auto elNi  = nistMan->FindOrBuildElement("Ni");
  auto elMo  = nistMan->FindOrBuildElement("Mo");
  auto elMn  = nistMan->FindOrBuildElement("Mn");
  auto elP  = nistMan->FindOrBuildElement("P");
  auto elS  = nistMan->FindOrBuildElement("S");

  // Stainless steel 316
  density = 8.0*g/cm3;
  G4Material* StainlessSteel316 = new G4Material(name="StainlessSteel316", density, nComponents=8);
  StainlessSteel316->AddElement(elFe, nAtoms=6500);
  StainlessSteel316->AddElement(elCr, nAtoms=1700);
  StainlessSteel316->AddElement(elNi, nAtoms=1300);
  StainlessSteel316->AddElement(elMo, nAtoms=290);
  StainlessSteel316->AddElement(elMn, nAtoms=200);
  StainlessSteel316->AddElement(elC, nAtoms=5);
  StainlessSteel316->AddElement(elP, nAtoms=2);
  StainlessSteel316->AddElement(elS, nAtoms=3);

  // Al2O3
  density = 3.987*g/cm3;
  G4Material* Al2O3 = new G4Material(name="Al2O3", density, nComponents=2);
  Al2O3->AddElement(elAl, nAtoms=2);
  Al2O3->AddElement(elOx, nAtoms=3);

  // CeBr3
  density = 5.1*g/cm3;
  G4Material* CeBr3 = new G4Material(name="CeBr3", density, nComponents=2);
  CeBr3->AddElement(elCe, nAtoms=1);
  CeBr3->AddElement(elBr, nAtoms=3);

  // Ta2O5
  density = 8.3*g/cm3;
  G4Material* Ta2O5 = new G4Material(name="Ta2O5", density, nComponents=2);
  Ta2O5->AddElement(elTa, nAtoms=2);
  Ta2O5->AddElement(elOx, nAtoms=5);
  
  // Tyvek
  density = 0.5*g/cm3;
  G4Material* Tyvek = new G4Material(name="Tyvek", density, nComponents=2);
  Tyvek->AddElement(elC, nAtoms=1);
  Tyvek->AddElement(elH, nAtoms=2);

  // Epoxy - Bisphenol A diglycidyl ether
  density = 1.5*g/cm3;
  G4Material* Epoxy = new G4Material(name="Epoxy", density, nComponents=3);
  Epoxy->AddElement(elC, nAtoms=21);
  Epoxy->AddElement(elH, nAtoms=24);
  Epoxy->AddElement(elOx, nAtoms=4);

  // Ta2O165
  a = 15.994914620 * g / mole;
  G4Isotope* isO16 = new G4Isotope(name = "isO16", iz = 8, ia = 16, a);
  G4Element* elO16 = new G4Element(name = "elO16", symbol = "elO16", nElem = 1);
  elO16->AddIsotope(isO16, abundance = 100. * perCent);

  density = 8.3 * g / cm3;
  G4Material* Ta2O165 = new G4Material(name = "Ta2O165", density, nComponents = 2);
  Ta2O165->AddElement(elTa, nAtoms = 2);
  Ta2O165->AddElement(elO16, nAtoms = 5);

  // CD2
  a = 2.0141017781 * g / mole;
  G4Isotope* isD = new G4Isotope(name = "isD", iz = 1, ia = 2, a);
  G4Element* elD = new G4Element(name = "elD", symbol = "D", nElem = 1);
  elD->AddIsotope(isD, abundance = 100. * perCent);

  density = 1.02 * g / cm3;
  G4Material* CD2 = new G4Material(name = "CD2", density, nComponents = 2);
  CD2->AddElement(elC, nAtoms = 1);
  CD2->AddElement(elD, nAtoms = 2);
  
  
  if(Layer0Type == "TiN") {
    
    // N element
    G4Isotope* isN14 = new G4Isotope(name="isN14", iz=7, ia=14, a = 14.00307400478*g/mole);
    G4Isotope* isN15 = new G4Isotope(name="isN15", iz=7, ia=15,  a = 15.0001*g/mole);
    elN = new G4Element(name="elN",symbol="N",nElem=2);
    elN->AddIsotope(isN14, abundance=99.636*perCent);
    elN->AddIsotope(isN15, abundance=0.364*perCent);
    
    // TiN material
    density = 5.22*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=2, kStateSolid);
    TargetLayer0Mat->AddElement(elN, nAtoms=1);
    TargetLayer0Mat->AddElement(elTi, nAtoms=1);
    
  }
  
  if(Layer0Type == "Ti14N") {
    // 14N element
    a = 14.00307400478*g/mole;
    G4Isotope* isN14 = new G4Isotope(name="isN14", iz=7, ia=14, a);
    G4Element* elN14 = new G4Element(name="elN14",symbol="N14",nElem=1);
    elN14->AddIsotope(isN14, abundance=100.*perCent);
    
    // 14NTi material
    density = 5.22*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=2, kStateSolid);
    TargetLayer0Mat->AddElement(elN14, nAtoms=1);
    TargetLayer0Mat->AddElement(elTi, nAtoms=1);	
  }

  if(Layer0Type == "TaF5") {
    // 19F element
    a = 19.0*g/mole;
    G4Isotope* isF19 = new G4Isotope(name="isF19", iz=9, ia=19, a);
    G4Element* elF19 = new G4Element(name="elF19",symbol="F19",nElem=1);
    elF19->AddIsotope(isF19, abundance=100.*perCent);
    
    // TaF5 material
    density = 4.74*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=2, kStateSolid);
    TargetLayer0Mat->AddElement(elF19, nAtoms=5);
    TargetLayer0Mat->AddElement(elTa, nAtoms=1);	
  }

  if(Layer0Type == "CaF2") {
    // 19F element
    a = 19.0*g/mole;
    G4Isotope* isF19 = new G4Isotope(name="isF19", iz=9, ia=19, a);
    G4Element* elF19 = new G4Element(name="elF19",symbol="F19",nElem=1);
    elF19->AddIsotope(isF19, abundance=100.*perCent);

    // 40Ca element
    a = 40.0*g/mole;
    G4Isotope* isCa40 = new G4Isotope(name="isCa40", iz=20, ia=40, a);
    G4Element* elCa40 = new G4Element(name="elCa40",symbol="Ca40",nElem=1);
    elCa40->AddIsotope(isCa40, abundance=100.*perCent);
    
    // CaF2 material
    density = 3.18*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=2, kStateSolid);
    TargetLayer0Mat->AddElement(elF19, nAtoms=2);
    TargetLayer0Mat->AddElement(elCa40, nAtoms=1);	
  }

  if(Layer0Type == "FeF3") {
    // 19F element
    a = 19.0*g/mole;
    G4Isotope* isF19 = new G4Isotope(name="isF19", iz=9, ia=19, a);
    G4Element* elF19 = new G4Element(name="elF19",symbol="F19",nElem=1);
    elF19->AddIsotope(isF19, abundance=100.*perCent);

    // 56FE element
    a = 56.0*g/mole;
    G4Isotope* isFe56 = new G4Isotope(name="isFe56", iz=26, ia=56, a);
    G4Element* elFe56 = new G4Element(name="elFe56",symbol="Fe40",nElem=1);
    elFe56->AddIsotope(isFe56, abundance=100.*perCent);
    
    // CaF2 material
    density = 3.87*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=2, kStateSolid);
    TargetLayer0Mat->AddElement(elF19, nAtoms=3);
    TargetLayer0Mat->AddElement(elFe56, nAtoms=1);	
  }
  
  if(Layer0Type == "14N") {
    // 14N element
    a = 14.00307400478*g/mole;
    G4Isotope* isN14 = new G4Isotope(name="isN14", iz=7, ia=14, a);
    G4Element* elN14 = new G4Element(name="elN14",symbol="N14",nElem=1);
    elN14->AddIsotope(isN14, abundance=100.*perCent);
    
    // 14N material
    density = 5.22*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=1, kStateSolid);
    TargetLayer0Mat->AddElement(elN14, nAtoms=1);
  }
  
  if(Layer0Type == "12C") {
    // 12C element
    a = 12.011*g/mole;
    G4Isotope* isC12 = new G4Isotope(name="isC12", iz=6, ia=12, a);
    G4Element* elC12 = new G4Element(name="elC12",symbol="C12",nElem=1);
    elC12->AddIsotope(isC12, abundance=100.*perCent);
    
    // 12C material
    density = 2.26*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=1, kStateSolid);
    TargetLayer0Mat->AddElement(elC12, nAtoms=1);
  }
  
  if(Layer0Type == "9Be") {
    // 9Be element
    a = 9.0122*g/mole;
    G4Isotope* isBe9 = new G4Isotope(name="isBe9", iz=4, ia=9, a);
    G4Element* elBe9 = new G4Element(name="elBe9",symbol="Be9",nElem=1);
    elBe9->AddIsotope(isBe9, abundance=100.*perCent);
    
    // 9Be material
    density = 1.848*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=1, kStateSolid);
    TargetLayer0Mat->AddElement(elBe9, nAtoms=1);
  }
  
  if(Layer0Type == "10B") {
    // 10B element
    a = 10.81*g/mole;
    G4Isotope* isB10 = new G4Isotope(name="isB10", iz=5, ia=10, a);
    G4Element* elB10 = new G4Element(name="elB10",symbol="B10",nElem=1);
    elB10->AddIsotope(isB10, abundance=100.*perCent);
    
    // 10B material
    density = 2.34*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=1, kStateSolid);
    TargetLayer0Mat->AddElement(elB10, nAtoms=1);
  }

  if(Layer0Type == "11B") {
    // 10B element
    a = 10.81*g/mole;
    G4Isotope* isB11 = new G4Isotope(name="isB11", iz=5, ia=10, a);
    G4Element* elB11 = new G4Element(name="elB11",symbol="B11",nElem=1);
    elB11->AddIsotope(isB11, abundance=100.*perCent);
    
    // 10B material
    density = 2.34*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=1, kStateSolid);
    TargetLayer0Mat->AddElement(elB11, nAtoms=1);
  }

  if(Layer0Type == "10B11B") {
    // 10B element
    a = 10.0*g/mole;
    G4Isotope* isB10 = new G4Isotope(name="isB10", iz=5, ia=10, a);
    G4Element* elB10 = new G4Element(name="elB10",symbol="B10",nElem=1);
    elB10->AddIsotope(isB10, abundance=100.*perCent);

    // 11B element
    a = 11.0*g/mole;
    G4Isotope* isB11 = new G4Isotope(name="isB11", iz=5, ia=11, a);
    G4Element* elB11 = new G4Element(name="elB11",symbol="B11",nElem=1);
    elB11->AddIsotope(isB11, abundance=100.*perCent);
    
    // 10B11B material
    density = 2.34*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=2, kStateSolid);
    TargetLayer0Mat->AddElement(elB10, nAtoms=1);
    TargetLayer0Mat->AddElement(elB11, nAtoms=1);
  }

  if(Layer0Type == "MixB") {
    // B element
    a = 10.81*g/mole;
    G4Isotope* isB10 = new G4Isotope(name="isB10", iz=5, ia=10, a);
    G4Isotope* isB11 = new G4Isotope(name="isB11", iz=5, ia=11, a);
    G4Element* elB = new G4Element(name="elB",symbol="B",nElem=2);
    elB->AddIsotope(isB10, abundance=MixBAb[0]*perCent);
    elB->AddIsotope(isB11, abundance=MixBAb[1]*perCent);
    
    // Be element
    a = 9.0122*g/mole;
    G4Isotope* isBe9 = new G4Isotope(name="isBe9", iz=4, ia=9, a);
    G4Element* elBe = new G4Element(name="elBe",symbol="Be",nElem=1);
    elBe->AddIsotope(isBe9, abundance=100.*perCent);
    
    // Mix material
    G4cout << MixWr[0] << "  " << MixWr[1] << G4endl;
    G4cout << MixRho[0] << "  " << MixRho[1] << G4endl;
    density = ( 1 / ( MixWr[0]/MixRho[0] + MixWr[1]/MixRho[1] ) )*g/cm3;
    G4Material* TargetLayer0Mat = new G4Material(name="TargetMat", density, nComponents=2, kStateSolid);
    TargetLayer0Mat->AddElement(elB, weightRatio=MixWr[0]);
    TargetLayer0Mat->AddElement(elBe, weightRatio=MixWr[1]);
  }

  // Ta2O5 with pure 16O
  if (Layer0Type == "Ta2O165") {
    a = 15.994914620 * g / mole;
    G4Isotope* isO16 = new G4Isotope(name = "isO16", iz = 8, ia = 16, a);
    G4Element* elO16 = new G4Element(name = "elO16", symbol = "elO16", nElem = 1);
    elO16->AddIsotope(isO16, abundance = 100. * perCent);

    density = 8.3 * g / cm3;
    G4Material* TargetLayer0Mat = new G4Material(name = "TargetMat", density, nComponents = 2, kStateSolid);
    TargetLayer0Mat->AddElement(elTa, nAtoms = 2);
    TargetLayer0Mat->AddElement(elO16, nAtoms = 5);
  }
  
  // Target Backing
  if(TargetBacking == "Ta") {
    G4Material* TargetBackingMat =  nistMan->FindOrBuildMaterial("G4_Ta");
    TargetBackingMat->SetName("TargetBackingMat");
  }
  if(TargetBacking == "W") {
    G4Material* TargetBackingMat =  nistMan->FindOrBuildMaterial("G4_W");
    TargetBackingMat->SetName("TargetBackingMat");
  }
  if(TargetBacking == "Ti") {
    G4Material* TargetBackingMat =  nistMan->FindOrBuildMaterial("G4_Ti");
    TargetBackingMat->SetName("TargetBackingMat");
  }
  if(TargetBacking == "Cu") {
    G4Material* TargetBackingMat =  nistMan->FindOrBuildMaterial("G4_Cu");
    TargetBackingMat->SetName("TargetBackingMat");
  }
  
  


  if(GasType == "20Ne") {
    // Ne20
    density = 0.9; // mg/cm3, at 273 K, 1 atm = 1.01325 bar
    MolarMass = 19.99244018E3; // mg/mol
    Npar = Avog / MolarMass; // number of particles/mg;
    
    a = 19.99244018*g/mole;
    G4Isotope* isNe20 = new G4Isotope(name="isNe20", iz=10, ia=20, a);
    G4Element* elNe20 = new G4Element(name="elNe20",symbol="Ne20",nElem=1);
    elNe20->AddIsotope(isNe20, abundance=100.*perCent);
    
    for(int i=0;i<7;i++) {
      pressure    = pressure_0_ch[i]*bar;
      temperature = temperature_0_ch[i]*kelvin;
      densitygas = (pressure_0_ch[i]/1.01325)*(273/temperature_0_ch[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_ch[i] = new G4Material(Form("gas_ch%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_ch[i]->AddElement(elNe20, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_col[i]*bar;
      temperature = temperature_0_col[i]*kelvin;
      densitygas = (pressure_0_col[i]/1.01325)*(273/temperature_0_col[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_col[i] = new G4Material(Form("gas_col%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_col[i]->AddElement(elNe20, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_pipe[i]*bar;
      temperature = temperature_0_pipe[i]*kelvin;
      densitygas = (pressure_0_pipe[i]/1.01325)*(273/temperature_0_pipe[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_pipe[i] = new G4Material(Form("gas_pipe%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_pipe[i]->AddElement(elNe20, weightRatio=1.);
    }
  }
  else if(GasType == "22Ne") {
    // Ne22
    density = 0.9; // mg/cm3, at 273 K, 1 atm = 1.01325 bar
    MolarMass = 21.99138513E3; // mg/mol
    Npar = Avog / MolarMass; // number of particles/mg;

    a = 21.99138513*g/mole;
    G4Isotope* isNe22 = new G4Isotope(name="isNe22", iz=10, ia=22, a);
    G4Element* elNe22 = new G4Element(name="elNe22",symbol="Ne22",nElem=1);
    elNe22->AddIsotope(isNe22, abundance=100.*perCent);
    
    for(int i=0;i<7;i++) {
      pressure    = pressure_0_ch[i]*bar;
      temperature = temperature_0_ch[i]*kelvin;
      densitygas = (pressure_0_ch[i]/1.01325)*(273/temperature_0_ch[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_ch[i] = new G4Material(Form("gas_ch%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_ch[i]->AddElement(elNe22, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_col[i]*bar;
      temperature = temperature_0_col[i]*kelvin;
      densitygas = (pressure_0_col[i]/1.01325)*(273/temperature_0_col[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_col[i] = new G4Material(Form("gas_col%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_col[i]->AddElement(elNe22, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_pipe[i]*bar;
      temperature = temperature_0_pipe[i]*kelvin;
      densitygas = (pressure_0_pipe[i]/1.01325)*(273/temperature_0_pipe[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_pipe[i] = new G4Material(Form("gas_pipe%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_pipe[i]->AddElement(elNe22, weightRatio=1.);
    }
  }
  else if(GasType == "21Ne") {
    // Ne21
    density = 0.9; // mg/cm3, at 273 K, 1 atm = 1.01325 bar
    MolarMass = 20.993846685E3; // mg/mol
    Npar = Avog / MolarMass; // number of particles/mg;
    
    a = 20.993846685*g/mole;
    G4Isotope* isNe21 = new G4Isotope(name="isNe21", iz=10, ia=21, a);
    G4Element* elNe21 = new G4Element(name="elNe21",symbol="Ne21",nElem=1);
    elNe21->AddIsotope(isNe21, abundance=100.*perCent);
    
    for(int i=0;i<7;i++) {
      pressure    = pressure_0_ch[i]*bar;
      temperature = temperature_0_ch[i]*kelvin;
      densitygas = (pressure_0_ch[i]/1.01325)*(273/temperature_0_ch[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_ch[i] = new G4Material(Form("gas_ch%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_ch[i]->AddElement(elNe21, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_col[i]*bar;
      temperature = temperature_0_col[i]*kelvin;
      densitygas = (pressure_0_col[i]/1.01325)*(273/temperature_0_col[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_col[i] = new G4Material(Form("gas_col%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_col[i]->AddElement(elNe21, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_pipe[i]*bar;
      temperature = temperature_0_pipe[i]*kelvin;
      densitygas = (pressure_0_pipe[i]/1.01325)*(273/temperature_0_pipe[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_pipe[i] = new G4Material(Form("gas_pipe%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_pipe[i]->AddElement(elNe21, weightRatio=1.);
    }
  }
  
  else if(GasType == "MixNe") {
    // 20Ne+21Ne+22Ne gas mixture
    //20Ne
    G4Isotope* isNe20 = new G4Isotope(name="isNe20", iz=10, ia=20, a=19.99244018*g/mole);
    
    //21Ne
    G4Isotope* isNe21 = new G4Isotope(name="isNe21", iz=10, ia=21,  a=20.993846685*g/mole);
    
    //22Ne
    G4Isotope* isNe22 = new G4Isotope(name="isNe22", iz=10, ia=22, a=21.99138513*g/mole);
    
    //Mixture Ne
    G4Element* elNe = new G4Element(name="elNe",symbol="Ne",nElem=3);
    elNe->AddIsotope(isNe20, abundance=MixNeAb[0]*perCent);
    G4cout << "20Ne abundance is " << abundance << G4endl;
    elNe->AddIsotope(isNe21, abundance=MixNeAb[1]*perCent);
    G4cout << "21Ne abundance is " << abundance << G4endl;
    elNe->AddIsotope(isNe22, abundance=MixNeAb[2]*perCent);
    G4cout << "22Ne abundance is " << abundance << G4endl;
    
    density = 0.9; // mg/cm3, at 273 K, 1 atm = 1.01325 bar
    MolarMass = 19.99244018E3*MixNeAb[0]/100+20.993846685E3*MixNeAb[1]/100+21.99138513E3*MixNeAb[2]/100; // mg/mol
    G4cout << "MolarMass=" << MolarMass << G4endl;
    Npar = Avog / MolarMass; // number of particles/mg;
    
    for(int i=0;i<7;i++) {
      pressure    = pressure_0_ch[i]*bar;
      temperature = temperature_0_ch[i]*kelvin;
      densitygas = (pressure_0_ch[i]/1.01325)*(273/temperature_0_ch[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_ch[i] = new G4Material(Form("gas_ch%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_ch[i]->AddElement(elNe, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_col[i]*bar;
      temperature = temperature_0_col[i]*kelvin;
      densitygas = (pressure_0_col[i]/1.01325)*(273/temperature_0_col[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_col[i] = new G4Material(Form("gas_col%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_col[i]->AddElement(elNe, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_pipe[i]*bar;
      temperature = temperature_0_pipe[i]*kelvin;
      densitygas = (pressure_0_pipe[i]/1.01325)*(273/temperature_0_pipe[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_pipe[i] = new G4Material(Form("gas_pipe%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_pipe[i]->AddElement(elNe, weightRatio=1.);
    }
  }
  
  else if(GasType == "14N") {
    // N14
    density = 1.2506; // mg/cm3, at 273 K, 1 atm = 1.01325 bar
    MolarMass = 14.00307400478E3; // mg/mol
    Npar = Avog / MolarMass; // number of particles/mg;
    
    a = 14.00307400478*g/mole;
    G4Isotope* isN14 = new G4Isotope(name="isN14", iz=7, ia=14, a);
    G4Element* elN14 = new G4Element(name="elN14",symbol="N14",nElem=1);
    elN14->AddIsotope(isN14, abundance=100.*perCent);
    
    for(int i=0;i<7;i++) {
      pressure    = pressure_0_ch[i]*bar;
      temperature = temperature_0_ch[i]*kelvin;
      densitygas = (pressure_0_ch[i]/1.01325)*(273/temperature_0_ch[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3

      gas_ch[i] = new G4Material(Form("gas_ch%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_ch[i]->AddElement(elN14, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_col[i]*bar;
      temperature = temperature_0_col[i]*kelvin;
      densitygas = (pressure_0_col[i]/1.01325)*(273/temperature_0_col[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_col[i] = new G4Material(Form("gas_col%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_col[i]->AddElement(elN14, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_pipe[i]*bar;
      temperature = temperature_0_pipe[i]*kelvin;
      densitygas = (pressure_0_pipe[i]/1.01325)*(273/temperature_0_pipe[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_pipe[i] = new G4Material(Form("gas_pipe%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_pipe[i]->AddElement(elN14, weightRatio=1.);
    }
  }
  else if(GasType == "2H") {
    // deuterium
    density = 0.180; // mg/cm3, at 273 K, 1 atm = 1.01325 bar
    MolarMass = 2.0141017781E3; // mg/mol
    Npar = Avog / MolarMass; // number of particles/mg;

    a = 2.0141017781*g/mole;
    G4Isotope* isH2 = new G4Isotope(name="isH2", iz=1, ia=2, a);
    G4Element* elH2 = new G4Element(name="elH2",symbol="H2",nElem=1);
    elH2->AddIsotope(isH2, abundance=100.*perCent);

    for(int i=0;i<7;i++) {
      densitygas = (pressure_0_ch[i]/1.01325)*(273/temperature_0_ch[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      pressure    = pressure_0_ch[i]*bar;
      temperature = temperature_0_ch[i]*kelvin;
      
      gas_ch[i] = new G4Material(Form("gas_ch%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_ch[i]->AddElement(elH2, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_col[i]*bar;
      temperature = temperature_0_col[i]*kelvin;
      densitygas = (pressure_0_col[i]/1.01325)*(273/temperature_0_col[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_col[i] = new G4Material(Form("gas_col%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_col[i]->AddElement(elH2, weightRatio=1.);
    }

    for(int i=0;i<5;i++) {
      pressure    = pressure_0_pipe[i]*bar;
      temperature = temperature_0_pipe[i]*kelvin;
      densitygas = (pressure_0_pipe[i]/1.01325)*(273/temperature_0_pipe[i])*density*mg/cm3;
      ndensity = Npar * densitygas/(mg/cm3); // number of particles/cm3
      
      gas_pipe[i] = new G4Material(Form("gas_pipe%i",i), densitygas, nElem=1, kStateGas,temperature,pressure);
      gas_pipe[i]->AddElement(elH2, weightRatio=1.);
    }
  }
  else if(GasType == "vacuum") {
    density = universe_mean_density;
    for(int i=0;i<7;i++) {
      densitygas = (pressure_0_ch[i]/1.01325)*(273/temperature_0_ch[i])*density*mg/cm3;
      pressure    = 1.e-19*pascal;
      temperature = 0.1*kelvin;
      gas_ch[i] = new G4Material(Form("gas_ch%i",i), 1, 1.008*g/mole, density, kStateGas,temperature,pressure);
    }
    for(int i=0;i<5;i++) {
      densitygas = (pressure_0_col[i]/1.01325)*(273/temperature_0_col[i])*density*mg/cm3;
      pressure    = 1.e-19*pascal;
      temperature = 0.1*kelvin;
      gas_col[i] = new G4Material(Form("gas_col%i",i), 1, 1.008*g/mole, density, kStateGas,temperature,pressure);
    }
    for(int i=0;i<5;i++) {
      densitygas = (pressure_0_pipe[i]/1.01325)*(273/temperature_0_pipe[i])*density*mg/cm3;
      pressure    = 1.e-19*pascal;
      temperature = 0.1*kelvin;
      gas_pipe[i] = new G4Material(Form("gas_pipe%i",i), 1, 1.008*g/mole, density, kStateGas,temperature,pressure);
    }
  }
  else if(GasType == "air") {
    a = 14.01*g/mole;
    //G4Element* elN  = new G4Element(name="elN",symbol="N" , 7., a);
    a = 16.00*g/mole;
    G4Element* elO  = new G4Element(name="elO"  ,symbol="O" , 8., a);

    density = 1.290; // mg/cm3, at 273 K, 1 atm = 1.01325 bar

    for(int i=0;i<7;i++) {
      densitygas = (pressure_0_ch[i]/1.01325)*(273/temperature_0_ch[i])*density*mg/cm3;
      pressure    = pressure_0_ch[i]*bar;
      temperature = temperature_0_ch[i]*kelvin;

      gas_ch[i] = new G4Material(Form("gas_ch%i",i), densitygas, nElem=2, kStateGas,temperature,pressure);
      gas_ch[i]->AddElement(elN, 0.7);
      gas_ch[i]->AddElement(elO, 0.3);
    }

    for(int i=0;i<5;i++) {
      densitygas = (pressure_0_col[i]/1.01325)*(273/temperature_0_col[i])*density*mg/cm3;
      pressure    = pressure_0_col[i]*bar;
      temperature = temperature_0_col[i]*kelvin;

      gas_col[i] = new G4Material(Form("gas_col%i",i), densitygas, nElem=2, kStateGas,temperature,pressure);
      gas_col[i]->AddElement(elN, 0.7);
      gas_col[i]->AddElement(elO, 0.3);
    }

    for(int i=0;i<5;i++) {
      densitygas = (pressure_0_pipe[i]/1.01325)*(273/temperature_0_pipe[i])*density*mg/cm3;
      pressure    = pressure_0_pipe[i]*bar;
      temperature = temperature_0_pipe[i]*kelvin;

      gas_pipe[i] = new G4Material(Form("gas_pipe%i",i), densitygas, nElem=2, kStateGas,temperature,pressure);
      gas_pipe[i]->AddElement(elN, 0.7);
      gas_pipe[i]->AddElement(elO, 0.3);
    }
  }

  //G4cout << "Gas target is " << GasType << G4endl;
}
