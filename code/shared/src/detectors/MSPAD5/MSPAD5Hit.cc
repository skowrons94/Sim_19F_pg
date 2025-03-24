#include "MSPAD5Hit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<MSPAD5Hit> MSPAD5HitAllocator;

MSPAD5Hit::MSPAD5Hit()
{
}

MSPAD5Hit::~MSPAD5Hit()
{
}

MSPAD5Hit::MSPAD5Hit(const MSPAD5Hit& right): G4VHit()
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
  levelEnergy  = right.levelEnergy;
  originalEnergy  = right.originalEnergy;
}

const MSPAD5Hit& MSPAD5Hit::operator=(const MSPAD5Hit& right)
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
  levelEnergy  = right.levelEnergy;
  originalEnergy  = right.originalEnergy;
  return *this;
}

G4int MSPAD5Hit::operator==(const MSPAD5Hit& right) const
{
  return (this==&right) ? 1 : 0;
}

void MSPAD5Hit::Draw()
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

void MSPAD5Hit::Print()
{
  //G4cout << "  copy number: " << copyno << "  energy deposition: " << G4BestUnit(edep,"Energy") << "  particle: " << partName << "  vertexpos: " << vertexpos << "  fStep: " << fStep  << G4endl;
}
