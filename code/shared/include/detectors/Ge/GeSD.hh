#ifndef GeSD_h
#define GeSD_h 1

#include "G4VSensitiveDetector.hh"
#include "GeHit.hh"
#include "G4SystemOfUnits.hh"

class G4Step;
class G4HCofThisEvent;

class GeSD : public G4VSensitiveDetector
{
public:
  GeSD(G4String);
  GeSD();
  ~GeSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  G4int HCID;
  G4String HCname;
  GeHitsCollection* GeCollection;
};

#endif
