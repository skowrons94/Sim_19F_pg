#ifndef ScPSD_h
#define ScPSD_h 1

#include "G4VSensitiveDetector.hh"
#include "ScPHit.hh"
#include "G4SystemOfUnits.hh"

class G4Step;
class G4HCofThisEvent;

class ScPSD : public G4VSensitiveDetector
{
public:
  ScPSD(G4String);
  ScPSD();
  ~ScPSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  G4int HCID;
  G4String HCname;
  ScPHitsCollection* ScPCollection;
};

#endif
