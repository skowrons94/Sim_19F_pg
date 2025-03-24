#include "TrackingAction.hh"
#include "TrackInformation.hh"

#include "G4TrackingManager.hh"
#include "G4Track.hh"

TrackingAction::TrackingAction()
  :G4UserTrackingAction()
{;}

void TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
  if(aTrack->GetParentID()==0 && aTrack->GetUserInformation()==0)
    {
      origInfo = new TrackInformation(aTrack);
      G4Track* theTrack = (G4Track*)aTrack;
      theTrack->SetUserInformation(origInfo);
      OriginalEnergy = origInfo->GetOriginalEnergy();
    }
  if(aTrack->GetParentID()==1 && aTrack->GetUserInformation()!=0)
    {
      TrackInformation* anInfo = new TrackInformation(aTrack);
      anInfo->SetOriginalEnergy(OriginalEnergy);
      G4Track* theTrack = (G4Track*)aTrack;
      theTrack->SetUserInformation(anInfo);
    }

}

void TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  
  if(secondaries)
    {
      
      TrackInformation* info =
	(TrackInformation*)(aTrack->GetUserInformation());
      
      size_t nSeco = secondaries->size();
      
      if(nSeco>0)
	{
	  for(size_t i=0;i<nSeco;i++)
	    {
	      TrackInformation* infoNew = new TrackInformation(info);
	      (*secondaries)[i]->SetUserInformation(infoNew);
	    }
	}
    }
}
