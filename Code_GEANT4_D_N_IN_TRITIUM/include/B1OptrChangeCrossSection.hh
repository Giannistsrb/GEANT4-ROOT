/// \file GB01/include/GB01BOptrChangeCrossSection.hh
/// \brief Definition of the GB01BOptrChangeCrossSection class
//
//---------------------------------------------------------------
//
// GB01BOptrChangeCrossSection
//
// Class Description:
//        A G4VBiasingOperator concrete implementation example to
//    illustrate how to bias physics processes cross-section for
//    one particle type.
//        The G4VBiasingOperation G4BOptnChangeCrossSection is
//    selected by this operator, and is sent to each process
//    calling the operator.
//        A simple constant bias to the cross-section is applied,
//    but more sophisticated changes can be applied.
//
//---------------------------------------------------------------
//

#ifndef B1OptrChangeCrossSection_hh
#define B1OptrChangeCrossSection_hh 1

#include "G4VBiasingOperator.hh"
#include "B1DetectorConstruction.hh"
#include "globals.hh"

class G4BOptnChangeCrossSection;
class G4ParticleDefinition;
#include <map>

class B1OptrChangeCrossSection : public G4VBiasingOperator {
public:
  // ------------------------------------------------------------
  // -- Constructor: takes the name of the particle type to bias:
  // ------------------------------------------------------------
 B1OptrChangeCrossSection(G4String particleToBias, G4String name = "ChangeXS");
  virtual ~B1OptrChangeCrossSection();
  
  // -- method called at beginning of run:
  virtual void StartRun();
  
private:
  // -----------------------------
  // -- Mandatory from base class:
  // -----------------------------
  // -- This method returns the biasing operation that will bias the physics process occurence.
  virtual G4VBiasingOperation*
  ProposeOccurenceBiasingOperation(const G4Track*                            track,
                                   const G4BiasingProcessInterface* callingProcess);
  // -- Methods not used:
  virtual G4VBiasingOperation*
  ProposeFinalStateBiasingOperation(const G4Track*, const G4BiasingProcessInterface*)
  {return 0;}
  virtual G4VBiasingOperation*
  ProposeNonPhysicsBiasingOperation(const G4Track*, const G4BiasingProcessInterface*)
  {return 0;}

private:
  // -- ("using" is avoid compiler complaining against (false) method shadowing.)
  using G4VBiasingOperator::OperationApplied;

  // -- Optionnal base class method implementation.
  // -- This method is called to inform the operator that a proposed operation has been applied.
  // -- In the present case, it means that a physical interaction occured (interaction at
  // -- PostStepDoIt level):
  virtual void OperationApplied( const G4BiasingProcessInterface*                callingProcess,
                                 G4BiasingAppliedCase                               biasingCase,
                                 G4VBiasingOperation*                 occurenceOperationApplied,
                                 G4double                         weightForOccurenceInteraction,
                                 G4VBiasingOperation*                finalStateOperationApplied, 
                                 const G4VParticleChange*                particleChangeProduced );
  
private:
  // -- List of associations between processes and biasing operations:
  std::map< const G4BiasingProcessInterface*, 
            G4BOptnChangeCrossSection*       > fChangeCrossSectionOperations;
  G4bool                                  fSetup;
  const G4ParticleDefinition*    fParticleToBias;

  

};

#endif
