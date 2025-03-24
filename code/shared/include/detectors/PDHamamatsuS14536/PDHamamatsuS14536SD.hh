#ifndef PDHamamatsuS14536SD_h
#define PDHamamatsuS14536SD_h 1

#include "G4VSensitiveDetector.hh"
#include "PDHamamatsuS14536Hit.hh"
#include "G4SystemOfUnits.hh"

class G4Step;
class G4HCofThisEvent;

class PDHamamatsuS14536SD : public G4VSensitiveDetector
{
public:
  PDHamamatsuS14536SD(G4String);
  PDHamamatsuS14536SD();
  ~PDHamamatsuS14536SD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  G4int HCID;
  G4String HCname;
  PDHamamatsuS14536HitsCollection* PDHamamatsuS14536Collection;
};

#endif
