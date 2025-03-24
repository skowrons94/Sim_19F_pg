#ifndef StepLimiterPhysics_h
#define StepLimiterPhysics_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class G4StepLimiter;
class G4UserSpecialCuts;

class StepLimiterPhysics : public G4VPhysicsConstructor
{
public:

  StepLimiterPhysics(const G4String& name = "stepLimiter");
  virtual ~StepLimiterPhysics();

public:

  // This method is dummy for physics
  virtual void ConstructParticle();

  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type
  virtual void ConstructProcess();

  // Option to apply the step limit to all particles
  // (by default the step limit is applied to charged particles only)
  void   SetApplyToAll(G4bool option) { fApplyToAll= option; }
  G4bool GetApplyToAll() const { return fApplyToAll; }

private:

   // hide assignment operator
  StepLimiterPhysics & operator=(const StepLimiterPhysics &right);
  StepLimiterPhysics(const StepLimiterPhysics&);

  G4bool  fApplyToAll;
};

#endif
