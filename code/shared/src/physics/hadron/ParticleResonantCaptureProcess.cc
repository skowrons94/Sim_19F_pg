#include "ParticleResonantCaptureProcess.hh"
#include "G4Proton.hh"
#include "G4Deuteron.hh"
#include "G4Triton.hh"
#include "G4He3.hh"
#include "G4Alpha.hh"
#include "IonC12.hh"
#include "ParticleResonantCaptureXS.hh"
//#include "ParticleResonantCaptureDataSet.hh"

ParticleResonantCaptureProcess::ParticleResonantCaptureProcess(const G4String& processName) : 
  G4HadronicProcess(processName, fCapture)
{
  //AddDataSet(new ParticleResonantCaptureXS());
}

ParticleResonantCaptureProcess::~ParticleResonantCaptureProcess()
{}

G4bool
ParticleResonantCaptureProcess::IsApplicable(const G4ParticleDefinition& aParticleType)
{
  return (&aParticleType == G4Proton::Proton() || &aParticleType == G4Deuteron::Deuteron() || &aParticleType == G4Triton::Triton() || &aParticleType == G4He3::He3() || &aParticleType == G4Alpha::Alpha() || &aParticleType == IonC12::theIonC12());
}

void ParticleResonantCaptureProcess::ProcessDescription(std::ostream& outFile) const
{
  outFile << "ParticleResonantCaptureProcess handles the resonant capture of particles by nuclei\n"
	  << "following by gamma/electron de-excitation cascade. One or more\n"
          << "hadronic models and hadronic cross section sets may be invoked.\n";
}

