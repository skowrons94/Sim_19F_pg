#ifndef SiSD_h
#define SiSD_h 1

#include "G4VSensitiveDetector.hh"
#include "SiHit.hh"
#include "G4SystemOfUnits.hh"

class G4Step;
class G4HCofThisEvent;

class SiSD : public G4VSensitiveDetector
{
public:
  SiSD(G4String);
  SiSD();
  ~SiSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  G4int HCID;
  G4String HCname;
  SiHitsCollection* SiCollection;
};

#endif
