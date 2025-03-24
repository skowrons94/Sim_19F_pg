#ifndef AnalysisMessenger_h
#define AnalysisMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithABool.hh"

class AnalysisManager;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;

class AnalysisMessenger: public G4UImessenger
{
public:
  AnalysisMessenger(AnalysisManager* );
  ~AnalysisMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
 
  
private:
  AnalysisManager* Analysis;
  G4UIdirectory* AnalysisDir;

  G4UIcmdWithAString* FileNameCmd;
  G4UIcmdWithADouble* Gamma1Cmd;
  G4UIcmdWithADouble* Gamma2Cmd;
  G4UIcmdWithADouble* MultThrCmd;
  G4UIcmdWithADouble* CapFragIonACmd;
  G4UIcmdWithADouble* CapFragIonZCmd;
  G4UIcmdWithADouble* FragIonA1Cmd;
  G4UIcmdWithADouble* FragIonZ1Cmd;
  G4UIcmdWithADouble* FragIonA2Cmd;
  G4UIcmdWithADouble* FragIonZ2Cmd;
  G4UIcmdWithABool* AllEventCmd;
  G4UIcmdWithABool* AllFusionEventCmd;
  G4UIcmdWithABool* ZintTreeCmd;
  G4UIcmdWithABool* EpTreeCmd;
  G4UIcmdWithABool* EgammaTreeCmd;
  G4UIcmdWithABool* PgammaTreeCmd;
  G4UIcmdWithABool* EdepTreeCmd;
  G4UIcmdWithABool* BeamPosTreeCmd;
  G4UIcmdWithABool* BeamKinETreeCmd;
  G4UIcmdWithABool* BeamThetaTreeCmd;
  G4UIcmdWithADouble* SetMultThreshold;
  
};

#endif
