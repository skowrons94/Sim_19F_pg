#include "GeHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<GeHit> GeHitAllocator;

GeHit::GeHit()
{
}

GeHit::~GeHit()
{
}

GeHit::GeHit(const GeHit& right): G4VHit()
{
  trackID   = right.trackID;
  partName  = right.partName;
  pCode  = right.pCode;
  edep      = right.edep;
  pos       = right.pos;
  copyno    = right.copyno;
  partTime  = right.partTime;
  levelEnergy  = right.levelEnergy;
  originalEnergy  = right.originalEnergy;
}

const GeHit& GeHit::operator=(const GeHit& right)
{
  trackID   = right.trackID;
  partName  = right.partName;
  pCode  = right.pCode;
  edep      = right.edep;
  pos       = right.pos;
  copyno    = right.copyno;
  partTime  = right.partTime;
  levelEnergy  = right.levelEnergy;
  originalEnergy  = right.originalEnergy;
  return *this;
}

G4int GeHit::operator==(const GeHit& right) const
{
  return (this==&right) ? 1 : 0;
}

void GeHit::Draw()
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

void GeHit::Print()
{
  //G4cout << "  copy number: " << copyno << "  energy deposition: " << G4BestUnit(edep,"Energy") << G4endl;
}
