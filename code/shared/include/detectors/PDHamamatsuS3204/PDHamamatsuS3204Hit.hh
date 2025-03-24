#ifndef PDHamamatsuS3204Hit_h
#define PDHamamatsuS3204Hit_h 1
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class PDHamamatsuS3204Hit : public G4VHit
{
public:
  
  PDHamamatsuS3204Hit();
  ~PDHamamatsuS3204Hit();
  PDHamamatsuS3204Hit(const PDHamamatsuS3204Hit&);
  const PDHamamatsuS3204Hit& operator=(const PDHamamatsuS3204Hit&);
  G4int operator==(const PDHamamatsuS3204Hit&) const;
  
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
  void SetVertexPos(G4ThreeVector vxvyvz){ vertexpos = vxvyvz; };
  void SetFirstStep(G4bool firstStep){ fStep = firstStep; };
  void SetLevelEnergy(G4double levelenergy){ levelEnergy = levelenergy; };
  void SetOriginalEnergy(G4double originalenergy){ originalEnergy = originalenergy; };
  
  G4int GetTrackID(){ return trackID; };
  G4String GetParticleName(){ return partName; };
  G4int GetParticleCode(){ return pCode; };
  G4double GetEdep(){ return edep; };      
  G4ThreeVector GetPos(){ return pos; };
  G4int GetCopyNo(){ return copyno; };
  G4double GetParticleTime(){ return partTime; };
  G4ThreeVector GetVertexPos(){ return vertexpos; };
  G4bool GetFirstStep(){ return fStep; };
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
  G4ThreeVector vertexpos;
  G4bool        fStep;
  G4double      levelEnergy;
  G4double      originalEnergy;
};

typedef G4THitsCollection<PDHamamatsuS3204Hit> PDHamamatsuS3204HitsCollection;

extern G4Allocator<PDHamamatsuS3204Hit> PDHamamatsuS3204HitAllocator;

inline void* PDHamamatsuS3204Hit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) PDHamamatsuS3204HitAllocator.MallocSingle();
  return aHit;
}

inline void PDHamamatsuS3204Hit::operator delete(void *aHit)
{
  PDHamamatsuS3204HitAllocator.FreeSingle((PDHamamatsuS3204Hit*) aHit);
}

#endif
