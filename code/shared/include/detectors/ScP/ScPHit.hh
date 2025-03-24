#ifndef ScPHit_h
#define ScPHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class ScPHit : public G4VHit
{
public:
  
  ScPHit();
  ~ScPHit();
  ScPHit(const ScPHit&);
  const ScPHit& operator=(const ScPHit&);
  G4int operator==(const ScPHit&) const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
  void Draw();
  void Print();
  
public:
  
  void SetTrackID(G4int track){ trackID = track; };
  void SetParticleName(G4String pname){ partName = pname; };
  void SetParticleCode(G4int pcode){ pCode = pcode; };
  void SetEdep(G4double de){ edep = de; };
  void SetPos(G4ThreeVector xyz){ pos = xyz; };
  void SetCopyNo(G4int CopyNo){ copyno = CopyNo; };
  void SetParticleTime(G4double ptime){ partTime = ptime; };
  
  G4int GetTrackID(){ return trackID; };
  G4String GetParticleName(){ return partName; };
  G4int GetParticleCode(){ return pCode; };
  G4double GetEdep(){ return edep; };      
  G4ThreeVector GetPos(){ return pos; };
  G4int GetCopyNo(){ return copyno; };
  G4double GetParticleTime(){ return partTime; };
  
private:
  
  G4int         trackID;
  G4String      partName;
  G4int         pCode;
  G4double      edep;
  G4ThreeVector pos;
  G4int         copyno;
  G4double      partTime;
};

typedef G4THitsCollection<ScPHit> ScPHitsCollection;

extern G4Allocator<ScPHit> ScPHitAllocator;

inline void* ScPHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) ScPHitAllocator.MallocSingle();
  return aHit;
}

inline void ScPHit::operator delete(void *aHit)
{
  ScPHitAllocator.FreeSingle((ScPHit*) aHit);
}

#endif
