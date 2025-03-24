#ifndef IonC12_h
#define IonC12_h 1

#include "G4ParticleDefinition.hh"

class IonC12 : public G4ParticleDefinition
{
  public:
    static IonC12* Definition();
    static IonC12* theIonC12Definition();
    static IonC12* theIonC12();

  private:  // hide constructor as private
    IonC12() {}
    ~IonC12() override = default;

    static IonC12* theInstance;
};

#endif
