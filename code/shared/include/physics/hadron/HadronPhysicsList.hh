#ifndef HadronPhysicsList_h
#define HadronPhysicsList_h 1

#include "globals.hh"
#include "HadronPhysics.hh"

class HadronPhysicsListMessenger;
class G4ComponentAntiNuclNuclearXS;
class G4ComponentGGHadronNucleusXsc;

class HadronPhysicsList : public HadronPhysics
{
public: 

  // constructor
  HadronPhysicsList(G4int ver = 1);

  HadronPhysicsList(const G4String& name,
		    G4int ver = 1, G4bool ftf = false, G4bool bert = false,
		    G4bool chips = false, G4bool hp = false, 
		    G4bool glauber = false);
  
  virtual ~HadronPhysicsList();

  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type 
  void ConstructProcess() override;

  void SetHPinelFlagProt(G4bool fHPinelFlagProt) {HPinelFlagProt = fHPinelFlagProt;};
  void SetHPinelFlagDeut(G4bool fHPinelFlagDeut) {HPinelFlagDeut = fHPinelFlagDeut;};
  void SetHPinelFlagTrit(G4bool fHPinelFlagTrit) {HPinelFlagTrit = fHPinelFlagTrit;};
  void SetHPinelFlagHe3(G4bool fHPinelFlagHe3) {HPinelFlagHe3 = fHPinelFlagHe3;};
  void SetHPinelFlagAlph(G4bool fHPinelFlagAlph) {HPinelFlagAlph = fHPinelFlagAlph;};
  void SetHPinelFlagC12(G4bool fHPinelFlagC12) {HPinelFlagC12 = fHPinelFlagC12;};
  void SetInelFlagProt(G4bool fInelFlagProt) {InelFlagProt = fInelFlagProt;};
  void SetInelFlagDeut(G4bool fInelFlagDeut) {InelFlagDeut = fInelFlagDeut;};
  void SetInelFlagTrit(G4bool fInelFlagTrit) {InelFlagTrit = fInelFlagTrit;};
  void SetInelFlagHe3(G4bool fInelFlagHe3) {InelFlagHe3 = fInelFlagHe3;};
  void SetInelFlagAlph(G4bool fInelFlagAlph) {InelFlagAlph = fInelFlagAlph;};
  void SetInelFlagC12(G4bool fInelFlagC12) {InelFlagC12 = fInelFlagC12;};
  void SetPartCapType(G4String fPartCapType) {PartCapType = fPartCapType;};
  void SetPartCapFlag(G4bool fPartCapFlag) {PartCapFlag = fPartCapFlag;};

private:

  HadronPhysicsListMessenger *hadronPhysicsListMessenger;
  // copy constructor and hide assignment operator
  HadronPhysicsList(HadronPhysicsList &);
  HadronPhysicsList & operator=(const HadronPhysicsList &right);

  G4int    verbose;

  G4bool HPinelFlagProt;
  G4bool HPinelFlagDeut;
  G4bool HPinelFlagTrit;
  G4bool HPinelFlagHe3;
  G4bool HPinelFlagAlph;
  G4bool HPinelFlagC12;
  G4bool InelFlagProt;
  G4bool InelFlagDeut;
  G4bool InelFlagTrit;
  G4bool InelFlagHe3;
  G4bool InelFlagAlph;
  G4bool InelFlagC12;
  G4String PartCapType;
  G4bool PartCapFlag;
};

#endif
