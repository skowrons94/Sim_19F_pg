#ifndef Foil23napa_h
#define Foil23napa_h 1

#include "globals.hh"
#include "G4LogicalVolume.hh"
#include <tuple>


class Materials;
class Foil23napaMessenger;

class Foil23napa
{
public:
    
  Foil23napa();
  ~Foil23napa();
    
    void SetFoilThickness(G4double fThickness) {Thickness = fThickness;
    };

    void SetFoilAlThickness(G4double fThicknessAl) {ThicknessAl = fThicknessAl;};
    static Foil23napa* GetInstance();
    
    G4double GetThickness();
    G4double GetThicknessAl();

public:

    std::tuple<G4LogicalVolume*, G4LogicalVolume*, G4LogicalVolume*,G4LogicalVolume*> Construct(G4double, G4double);

  
private:
  Materials* materials;
  Foil23napaMessenger* foil23napaMessenger;
  G4double Thickness;
  G4double ThicknessAl;
    
  static Foil23napa* instance;
};

#endif
