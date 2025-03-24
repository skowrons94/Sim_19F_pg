#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"
#include "EventAction.hh"
#include "PhysicsList.hh"
#include "RunAction.hh"
#include "AnalysisManager.hh"
#include "TrackingAction.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SystemOfUnits.hh"


#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4VisExecutive.hh"

#include "TString.h"

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " SimLUNA [-m macro ] [-u UIsession] [-s seedValue]" << G4endl;
  }
}

int main(int argc, char** argv)
{  
  /*
  for ( G4int i=1; i<argc; i=i+2 ) {
    G4cout << i << "  " << argv[i] << "  " << argv[i+1] << G4endl;
  }
  */
  // Run manager
  G4RunManager * runManager = new G4RunManager;

  // Visualization, if you choose to have it!
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  AnalysisManager* analysismanager = new AnalysisManager();

  // UserInitialization classes (mandatory)
  DetectorConstruction* detectorconstruction = new DetectorConstruction();
  runManager->SetUserInitialization(detectorconstruction);

  runManager->SetUserInitialization(new PhysicsList);
  
  // UserAction classes
  PrimaryGeneratorAction* primarygeneratoraction = new PrimaryGeneratorAction(analysismanager,detectorconstruction);
  runManager->SetUserAction(primarygeneratoraction);
  EventAction* eventaction = new EventAction(analysismanager);
  runManager->SetUserAction(eventaction);
  SteppingAction* steppingaction = new SteppingAction(eventaction);
  runManager->SetUserAction(steppingaction);
  StackingAction* stackingaction = new StackingAction();
  runManager->SetUserAction(stackingaction);
  TrackingAction* trackingaction = new TrackingAction();
  runManager->SetUserAction(trackingaction);
  RunAction* runaction = new RunAction(analysismanager);
  runManager->SetUserAction(runaction);

  /*
  if ( argc > 6 ) {
    PrintUsage();
    return 1;
  }
  */
  
  G4String macro;
  G4String session;
  G4String seedValue;
  
  for ( G4int i=1; i<argc; i=i+2 ) {
    G4cout << i << "  " << argv[i] << "  " << argv[i+1] << G4endl;
    if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
    else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
    else if ( G4String(argv[i]) == "-s" ) seedValue = argv[i+1];
    else {
      PrintUsage();
      return 1;
    }
  }
    
  //get the pointer to the User Interface manager 
  G4UImanager * UImanager = G4UImanager::GetUIpointer();  

  // if no macro provided
  G4UIExecutive* ui = nullptr;
  if ( ! macro.size() ) ui = new G4UIExecutive(argc, argv, session);
  
  // macro provided, batch mode
  if ( ui == nullptr ) {
    G4cout << Form("/control/alias seed %i",stoi(seedValue)) << G4endl;
    UImanager->ApplyCommand(Form("/control/alias seed %i",stoi(seedValue)));
    G4String command = "/control/execute ";
    UImanager->ApplyCommand(command+macro);
  }
  else {
    //UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  
  delete visManager;
  delete runManager;
  
  return 0;
}
