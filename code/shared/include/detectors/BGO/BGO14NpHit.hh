#ifndef BGO14NpHit_h
#define BGO14NpHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class BGO14NpHit : public G4VHit
{
public:
  
  BGO14NpHit();
  ~BGO14NpHit();
  BGO14NpHit(const BGO14NpHit&);
  const BGO14NpHit& operator=(const BGO14NpHit&);
  G4int operator==(const BGO14NpHit&) const;
  
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
  void SetLevelEnergy(G4double levelenergy){ levelEnergy = levelenergy; };
  void SetOriginalEnergy(G4double originalenergy){ originalEnergy = originalenergy; };
  
  G4int GetTrackID(){ return trackID; };
  G4String GetParticleName(){ return partName; };
  G4int GetParticleCode(){ return pCode; };
  G4double GetEdep(){ return edep; };      
  G4ThreeVector GetPos(){ return pos; };
  G4int GetCopyNo(){ return copyno; };
  G4double GetParticleTime(){ return partTime; };
  G4double GetLevelEnergy(){ return levelEnergy; };
  G4double GetOriginalEnergy(){ return originalEnergy; };
  
private:
  
  G4int         trackID;
  G4String      partName;
  G4int         pCode;
  G4double      edep;
  G4ThreeVector pos;
  G4int         copyno;
  G4double      partTime;
  G4double      levelEnergy;
  G4double      originalEnergy;
};

typedef G4THitsCollection<BGO14NpHit> BGO14NpHitsCollection;

extern G4Allocator<BGO14NpHit> BGO14NpHitAllocator;

inline void* BGO14NpHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) BGO14NpHitAllocator.MallocSingle();
  return aHit;
}

inline void BGO14NpHit::operator delete(void *aHit)
{
  BGO14NpHitAllocator.FreeSingle((BGO14NpHit*) aHit);
}

#endif
