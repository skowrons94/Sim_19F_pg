#ifndef ParticleCaptureProcess_h
#define ParticleCaptureProcess_h 1
 
#include "globals.hh"
#include "G4HadronicProcess.hh"

class ParticleCaptureProcess : public G4HadronicProcess
{
  public:

    explicit ParticleCaptureProcess(const G4String& processName ="particleCapture");
  
    virtual ~ParticleCaptureProcess();
 
    G4bool IsApplicable(const G4ParticleDefinition& aParticleType) final;

    void ProcessDescription(std::ostream& outFile) const final;
};
#endif
