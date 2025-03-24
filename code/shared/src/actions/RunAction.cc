#include "G4Timer.hh"
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "AnalysisManager.hh"

RunAction::RunAction(AnalysisManager* AM):analysismanager(AM)
{
  timer = new G4Timer;
}

RunAction::~RunAction()
{
  delete timer;
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  analysismanager->BeginOfRun();
  timer->Start();
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  analysismanager->EndOfRun();
  timer->Stop();

  G4cout << " >>>>> Run summary <<<<<" << G4endl;
  G4cout << " Number of events: " << aRun->GetNumberOfEvent() << G4endl;
  G4cout << " " << *timer << G4endl;
  G4cout << G4endl;

}
