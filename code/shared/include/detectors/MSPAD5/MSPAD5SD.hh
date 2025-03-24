#ifndef MSPAD5SD_h
#define MSPAD5SD_h 1

#include "G4VSensitiveDetector.hh"
#include "MSPAD5Hit.hh"
#include "G4SystemOfUnits.hh"

class G4Step;
class G4HCofThisEvent;

class MSPAD5SD : public G4VSensitiveDetector
{
public:
  MSPAD5SD(G4String);
  MSPAD5SD();
  ~MSPAD5SD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  G4int HCID;
  G4String HCname;
  MSPAD5HitsCollection* MSPAD5Collection;
};

#endif
