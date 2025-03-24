#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"

class PhysicsListMessenger;
class G4GenericBiasingPhysics;

class PhysicsList: public G4VModularPhysicsList
{
public:
  PhysicsList();
  virtual ~PhysicsList();
  
  virtual void SetCuts();

  void SetEmPhysics(G4String EmPhys);
  void SetHadrPhysFlag(G4bool HadrPhysFlag);

private:
  PhysicsListMessenger *physicsListMessenger;
};

#endif
