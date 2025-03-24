#include "PDHamamatsuS3204Hit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<PDHamamatsuS3204Hit> PDHamamatsuS3204HitAllocator;

PDHamamatsuS3204Hit::PDHamamatsuS3204Hit()
{
}

PDHamamatsuS3204Hit::~PDHamamatsuS3204Hit()
{
}

PDHamamatsuS3204Hit::PDHamamatsuS3204Hit(const PDHamamatsuS3204Hit& right): G4VHit()
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

const PDHamamatsuS3204Hit& PDHamamatsuS3204Hit::operator=(const PDHamamatsuS3204Hit& right)
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

G4int PDHamamatsuS3204Hit::operator==(const PDHamamatsuS3204Hit& right) const
{
  return (this==&right) ? 1 : 0;
}

void PDHamamatsuS3204Hit::Draw()
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

void PDHamamatsuS3204Hit::Print()
{
  //G4cout << "  copy number: " << copyno << "  energy deposition: " << G4BestUnit(edep,"Energy") << "  particle: " << partName << "  vertexpos: " << vertexpos << "  fStep: " << fStep  << G4endl;
}
