#include "TrackInformation.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<TrackInformation> * aTrackInformationAllocator = 0;

TrackInformation::TrackInformation()
  : G4VUserTrackInformation()
{
  fOriginalTrackID = 0;
  fLevelEnergy = 0.0;
  fOriginalEnergy = 0.;
}

TrackInformation::TrackInformation(const G4Track* aTrack)
  : G4VUserTrackInformation()
{
  //G4String PartName = aTrack->GetDefinition()->GetParticleName();
  //G4int start = PartName.find("[");
  //G4int stop = PartName.find("]");
  //G4String LevelEnergy = PartName.substr(start+1,stop-start-1);
  G4String LevelEnergyStr = aTrack->GetDefinition()->GetParticleName().substr(aTrack->GetDefinition()->GetParticleName().find("[")+1,aTrack->GetDefinition()->GetParticleName().find("]")-aTrack->GetDefinition()->GetParticleName().find("[")-1);
  //G4cout << LevelEnergyStr << G4endl;
  //G4cout << " TrackInformation::OriginalEnergy: " << aTrack->GetKineticEnergy() << G4endl;

  fOriginalTrackID = aTrack->GetTrackID();
  fLevelEnergy = atof(LevelEnergyStr);
  fOriginalEnergy = aTrack->GetKineticEnergy();
}

TrackInformation
::TrackInformation(const TrackInformation* aTrackInfo)
  : G4VUserTrackInformation()
{
  fOriginalTrackID = aTrackInfo->fOriginalTrackID;
  fLevelEnergy = aTrackInfo->fLevelEnergy;
  fOriginalEnergy = aTrackInfo->fOriginalEnergy;
}

TrackInformation::~TrackInformation()
{;}

TrackInformation& TrackInformation
::operator =(const TrackInformation& aTrackInfo)
{
  fOriginalTrackID = aTrackInfo.fOriginalTrackID;
  fLevelEnergy = aTrackInfo.fLevelEnergy;
  fOriginalEnergy = aTrackInfo.fOriginalEnergy;

  return *this;
}

void TrackInformation::Print() const
{
}
