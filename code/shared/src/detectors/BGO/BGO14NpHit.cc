#include "BGO14NpHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<BGO14NpHit> BGO14NpHitAllocator;

BGO14NpHit::BGO14NpHit()
{
}

BGO14NpHit::~BGO14NpHit()
{
}

BGO14NpHit::BGO14NpHit(const BGO14NpHit& right): G4VHit()
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

const BGO14NpHit& BGO14NpHit::operator=(const BGO14NpHit& right)
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

G4int BGO14NpHit::operator==(const BGO14NpHit& right) const
{
  return (this==&right) ? 1 : 0;
}

void BGO14NpHit::Draw()
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

void BGO14NpHit::Print()
{
  //G4cout << "BGO14NpHit copy number: " << copyno << "  energy deposition: " << G4BestUnit(edep,"Energy") << G4endl;
}
