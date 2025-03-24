#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <iostream>
#include <fstream>
using namespace std;

class G4Timer;
class G4Run;
class G4ParticleDefinition;
class AnalysisManager;

class RunAction : public G4UserRunAction
{
public:
  RunAction(AnalysisManager*);
  ~RunAction();
  
public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);
  
private:
  AnalysisManager*    analysismanager;
  G4Timer* timer;
  
};

#endif
