#ifndef BGO14NpSD_h
#define BGO14NpSD_h 1

#include "G4VSensitiveDetector.hh"
#include "BGO14NpHit.hh"
#include "G4SystemOfUnits.hh"

class G4Step;
class G4HCofThisEvent;

class BGO14NpSD : public G4VSensitiveDetector
{
public:
  BGO14NpSD(G4String);
  BGO14NpSD();
  ~BGO14NpSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  G4int HCID;
  G4String HCname;
  BGO14NpHitsCollection* BGO14NpCollection;
};

#endif
