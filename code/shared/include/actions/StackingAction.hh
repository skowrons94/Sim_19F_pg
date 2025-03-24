#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

class StackingAction : public G4UserStackingAction
{
public:
  StackingAction();
  ~StackingAction();
  
  G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
  virtual void NewStage();
  virtual void PrepareNewEvent();

private:

};

#endif
