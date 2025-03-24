#ifndef ParticleResonantCaptureProcess_h
#define ParticleResonantCaptureProcess_h 1
 
#include "globals.hh"
#include "G4HadronicProcess.hh"

class ParticleResonantCaptureProcess : public G4HadronicProcess
{
  public:

    explicit ParticleResonantCaptureProcess(const G4String& processName ="particleResonantCapture");
  
    virtual ~ParticleResonantCaptureProcess();
 
    G4bool IsApplicable(const G4ParticleDefinition& aParticleType) final;

    void ProcessDescription(std::ostream& outFile) const final;
};
#endif
