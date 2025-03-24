#include "SiHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<SiHit> SiHitAllocator;

SiHit::SiHit()
{
}

SiHit::~SiHit()
{
}

SiHit::SiHit(const SiHit& right): G4VHit()
{
  trackID   = right.trackID;
  partName  = right.partName;
  pCode  = right.pCode;
  edep      = right.edep;
  pos       = right.pos;
  copyno    = right.copyno;
  partTime  = right.partTime;
  vertexpos = right.vertexpos;
  fStep = right.fStep;
}

const SiHit& SiHit::operator=(const SiHit& right)
{
  trackID   = right.trackID;
  partName  = right.partName;
  pCode  = right.pCode;
  edep      = right.edep;
  pos       = right.pos;
  copyno    = right.copyno;
  partTime  = right.partTime;
  vertexpos = right.vertexpos;
  fStep = right.fStep;
  return *this;
}

G4int SiHit::operator==(const SiHit& right) const
{
  return (this==&right) ? 1 : 0;
}

void SiHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
    {
      G4Circle circle(pos);
      circle.SetScreenSize(2.);
      circle.SetFillStyle(G4Circle::filled);
      G4Colour colour(1.,0.,0.);
      G4VisAttributes attribs(colour);
      circle.SetVisAttributes(attribs);
      pVVisManager->Draw(circle);
    }
}

void SiHit::Print()
{
  //G4cout << "  copy number: " << copyno << "  energy deposition: " << G4BestUnit(edep,"Energy") << "  particle: " << partName << "  vertexpos: " << vertexpos << "  fStep: " << fStep  << G4endl;
}
