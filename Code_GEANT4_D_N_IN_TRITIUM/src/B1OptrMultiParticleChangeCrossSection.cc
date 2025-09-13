/// \file GB01/src/GB01BOptrMultiParticleChangeCrossSection.cc
/// \brief Implementation of the GB01BOptrMultiParticleChangeCrossSection class
//
#include "B1OptrMultiParticleChangeCrossSection.hh"
#include "G4BiasingProcessInterface.hh"

#include "B1OptrChangeCrossSection.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1OptrMultiParticleChangeCrossSection::B1OptrMultiParticleChangeCrossSection()
  : G4VBiasingOperator("TestManyExponentialTransform")
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1OptrMultiParticleChangeCrossSection::AddParticle(G4String particleName)
{
  const G4ParticleDefinition* particle =
    G4ParticleTable::GetParticleTable()->FindParticle( particleName );
  
  if ( particle == 0 )
    {
      G4ExceptionDescription ed;
      ed << "Particle `" << particleName << "' not found !" << G4endl;
      G4Exception("GB01BOptrMultiParticleChangeCrossSection::AddParticle(...)",
                  "exGB01.02",
                  JustWarning,
                  ed);
      return;
    }
  
  B1OptrChangeCrossSection* optr = new B1OptrChangeCrossSection(particleName);
  fParticlesToBias.push_back( particle );
  fBOptrForParticle[ particle ] = optr;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VBiasingOperation*
B1OptrMultiParticleChangeCrossSection::
ProposeOccurenceBiasingOperation(const G4Track* track,
                                 const G4BiasingProcessInterface* callingProcess)
{
  // -- examples of limitations imposed to apply the biasing:
  // -- limit application of biasing to primary particles only:
  if ( track->GetParentID() != 0 ) return 0; 
  // -- limit to at most 5 biased interactions:
  if ( fnInteractions > 4 )        return 0; 
  // -- and limit to a weight of at least 0.05:
  if ( track->GetWeight() < 0.05 ) return 0;
  
  if ( fCurrentOperator ) return fCurrentOperator->
                            GetProposedOccurenceBiasingOperation(track, callingProcess);
  else                    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1OptrMultiParticleChangeCrossSection::StartTracking( const G4Track* track )
{
  // -- fetch the underneath biasing operator, if any, for the current particle type:
  const G4ParticleDefinition* definition = track->GetParticleDefinition();
  std::map < const G4ParticleDefinition*, B1OptrChangeCrossSection* > :: iterator
    it = fBOptrForParticle.find( definition );
  fCurrentOperator = 0;
  if ( it != fBOptrForParticle.end() ) fCurrentOperator = (*it).second;

  // -- reset count for number of biased interactions:
  fnInteractions = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void 
B1OptrMultiParticleChangeCrossSection::
OperationApplied( const G4BiasingProcessInterface*               callingProcess, 
                  G4BiasingAppliedCase                              biasingCase,
                  G4VBiasingOperation*                occurenceOperationApplied, 
                  G4double                        weightForOccurenceInteraction,
                  G4VBiasingOperation*               finalStateOperationApplied, 
                  const G4VParticleChange*               particleChangeProduced )
{
  // -- count number of biased interactions:
  fnInteractions++;

  // -- inform the underneath biasing operator that a biased interaction occured:
  if ( fCurrentOperator ) fCurrentOperator->ReportOperationApplied( callingProcess,
                                                                    biasingCase,
                                                                    occurenceOperationApplied,
                                                                    weightForOccurenceInteraction,
                                                                    finalStateOperationApplied,
                                                                    particleChangeProduced );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
