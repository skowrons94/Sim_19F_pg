#ifndef TrackInformation_h
#define TrackInformation_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"

class TrackInformation : public G4VUserTrackInformation
{
public:
  TrackInformation();
  TrackInformation(const G4Track* aTrack);
  TrackInformation(const TrackInformation* aTrackInfo);
  virtual ~TrackInformation();

  inline void *operator new(size_t);
  inline void operator delete(void *aTrackInfo);

  TrackInformation& operator =(const TrackInformation& right);


  virtual void Print() const;

public:
  inline G4int GetOriginalTrackID() const {return fOriginalTrackID;}
  inline G4double GetOriginalEnergy() const {return fOriginalEnergy;}
  inline G4double GetLevelEnergy() const {return fLevelEnergy;}

  void SetOriginalTrackID(G4int OriginalTrackID) {fOriginalTrackID = OriginalTrackID;};
  void SetOriginalEnergy(G4double OriginalEnergy) {fOriginalEnergy = OriginalEnergy;};
  void SetLevelEnergy(G4double LevelEnergy) {fLevelEnergy = LevelEnergy;};

private:
  G4int                 fOriginalTrackID;
  G4double              fOriginalEnergy;
  G4double              fLevelEnergy;
};

extern G4ThreadLocal G4Allocator<TrackInformation> * aTrackInformationAllocator;

inline void* TrackInformation::operator new(size_t)
{
  if(!aTrackInformationAllocator)
    aTrackInformationAllocator = new G4Allocator<TrackInformation>;
  return (void*)aTrackInformationAllocator->MallocSingle();
}

inline void TrackInformation::operator delete(void *aTrackInfo)
{ aTrackInformationAllocator->FreeSingle((TrackInformation*)aTrackInfo);}

#endif
