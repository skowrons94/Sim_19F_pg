#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(PrimaryGeneratorAction* PGA):primaryGeneratorAction(PGA)
{ 
  PGADir = new G4UIdirectory("/PrimaryGeneratorAction/");
  PGADir->SetGuidance("PrimaryGeneratorAction control.");
}

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
}
