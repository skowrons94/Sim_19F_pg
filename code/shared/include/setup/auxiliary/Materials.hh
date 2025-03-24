#ifndef Materials_hh
#define Materials_hh 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

class MaterialsMessenger;

class Materials
{
public:

  ~Materials();
  
  static Materials* GetInstance();
  
  G4Material* GetMaterial(G4String);

  void SetGasType(G4String fGasType) {GasType = fGasType;};
  void SetLayer0Type(G4String fLayer0Type) {Layer0Type = fLayer0Type;};
  void SetTargetBacking(G4String fTargetBacking) {TargetBacking = fTargetBacking;};
  void SetGasPrCh(std::vector<G4double> fpressure_0_ch) {pressure_0_ch = fpressure_0_ch;};
  void SetGasTCh(std::vector<G4double> ftemperature_0_ch) {temperature_0_ch = ftemperature_0_ch;};
  void SetGasPrCol(std::vector<G4double> fpressure_0_col) {pressure_0_col = fpressure_0_col;};
  void SetGasTCol(std::vector<G4double> ftemperature_0_col) {temperature_0_col = ftemperature_0_col;};
  void SetGasPrPipe(std::vector<G4double> fpressure_0_pipe) {pressure_0_pipe = fpressure_0_pipe;};
  void SetGasTPipe(std::vector<G4double> ftemperature_0_pipe) {temperature_0_pipe = ftemperature_0_pipe;};
  void SetMixNeAb(std::vector<G4double> fMixNeAb) {MixNeAb = fMixNeAb;};
  void SetMixBAb(std::vector<G4double> fMixBAb) {MixBAb = fMixBAb;};
  void SetMixWr(std::vector<G4double> fMixWr) {MixWr = fMixWr;};
  void SetMixRho(std::vector<G4double> fMixRho) {MixRho = fMixRho;};
  G4String GetGasType() {return GasType;};
  G4String GetLayer0Type() {return Layer0Type;};
  std::vector<G4double> GetGasPrCh() {return pressure_0_ch;};
  std::vector<G4double> GetGasTCh() {return temperature_0_ch;};
  std::vector<G4double> GetGasPrCol() {return pressure_0_col;};
  std::vector<G4double> GetGasTCol() {return temperature_0_col;};
  std::vector<G4double> GetGasPrPipe() {return pressure_0_pipe;};
  std::vector<G4double> GetGasTPipe() {return temperature_0_pipe;};

public:
  
  Materials();
  
  void CreateMaterials();

private:

  static Materials* instance;

  G4NistManager*     nistMan;

  MaterialsMessenger* materialsMessenger;

  G4String name, symbol;
  G4double density, densitygas, a, abundance, MolarMass, Npar, ndensity, weightRatio;
  G4double pressure,temperature;
  G4int iz,ia,nElem,nComponents,nAtoms;
  const G4double Avog = 6.02214129E23; // number of particles/mol

  G4String GasType;
  G4String Layer0Type;
  G4String TargetBacking;
  std::vector<G4double> pressure_0_ch;
  std::vector<G4double> temperature_0_ch;
  std::vector<G4double> pressure_0_col;
  std::vector<G4double> temperature_0_col;
  std::vector<G4double> pressure_0_pipe;
  std::vector<G4double> temperature_0_pipe;
  std::vector<G4double> MixNeAb;
  std::vector<G4double> MixBAb;
  std::vector<G4double> MixWr;
  std::vector<G4double> MixRho;

  G4Material* gas_ch[7];
  G4Material* gas_col[5];
  G4Material* gas_pipe[5];
};

#endif
