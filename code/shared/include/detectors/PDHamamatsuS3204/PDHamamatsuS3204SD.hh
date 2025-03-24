#ifndef PDHamamatsuS3204SD_h
#define PDHamamatsuS3204SD_h 1

#include "G4VSensitiveDetector.hh"
#include "PDHamamatsuS3204Hit.hh"
#include "G4SystemOfUnits.hh"

class G4Step;
class G4HCofThisEvent;

class PDHamamatsuS3204SD : public G4VSensitiveDetector
{
public:
  PDHamamatsuS3204SD(G4String);
  PDHamamatsuS3204SD();
  ~PDHamamatsuS3204SD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  G4int HCID;
  G4String HCname;
  PDHamamatsuS3204HitsCollection* PDHamamatsuS3204Collection;
};

#endif
