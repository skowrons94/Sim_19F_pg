#ifndef BGO14Np_h
#define BGO14Np_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"

class Materials;
class BGO14NpMessenger;

class BGO14Np
{
public:

  BGO14Np();
  ~BGO14Np();

  static BGO14Np* GetInstance();

public:

  G4LogicalVolume* Construct();
  
  void SetBGODisp(std::vector<G4double> fbgoDisplacement) {bgoDisplacement = fbgoDisplacement;};
  
private:
  Materials* materials;
  BGO14NpMessenger* bgo14NpMessenger;

 
  std::vector<G4double> bgoDisplacement;
  
  G4VPhysicalVolume* bgoVacPhys;
  G4VPhysicalVolume* bgoAlPhys;
  //G4VPhysicalVolume* bgoCrPhys[6];
  G4VPhysicalVolume* bgoCrPhys;
  
  G4VisAttributes* bgoCas1VisAtt;
  G4VisAttributes* bgoAlVisAtt;
  G4VisAttributes* bgoCrVisAtt;
  G4VisAttributes* bgoVacVisAtt;

  static BGO14Np* instance;
};

#endif
