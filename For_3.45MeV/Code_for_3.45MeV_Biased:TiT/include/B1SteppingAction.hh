/// \file B1SteppingAction.hh
/// \brief Definition of the B1SteppingAction class

#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "B1RunAction.hh"

class B1EventAction;

class G4LogicalVolume;
class B1RunAction;
class G4BestUnit;
/// Stepping action class
/// 

class B1SteppingAction : public G4UserSteppingAction
{
  public:
    B1SteppingAction(B1EventAction* eventAction);
    virtual ~B1SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
      B1EventAction*  fEventAction;
    //First part (flange):
    G4LogicalVolume* fScoringVolume;
    G4LogicalVolume* fMolybdenum;
    G4LogicalVolume* fTiT;
    G4LogicalVolume* fCopper;

    //Second part (5 extra foils):
    G4LogicalVolume*  fAuX;
    G4LogicalVolume*  fAl8;
    G4LogicalVolume*  fGe73;
    G4LogicalVolume*  fGe76;
    G4LogicalVolume*  fAl7;

    
    B1RunAction* frun;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
