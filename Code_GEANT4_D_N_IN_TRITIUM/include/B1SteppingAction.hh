/// \file B1SteppingAction.hh
/// \brief Definition of the B1SteppingAction class

#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "B1DetectorConstruction.hh"
#include "globals.hh"
#include "B1RunAction.hh"

class B1EventAction;
class G4LogicalVolume;
class B1RunAction;
class G4BestUnit;

class B1SteppingAction : public G4UserSteppingAction
{
  public:
    B1SteppingAction(B1EventAction* eventAction);
    virtual ~B1SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    B1EventAction*    fEventAction;
    
    G4LogicalVolume*  fScoringVolume;
    G4LogicalVolume*  fFlange;
    G4LogicalVolume*  fOxygenColl;
    G4LogicalVolume*  fCarbonColl;
    G4LogicalVolume*  fOxygenAnt;
    G4LogicalVolume*  fCarbonAnt;
    G4LogicalVolume*  fOxygen;
    G4LogicalVolume*  fCarbon;
    G4LogicalVolume*  fMolybdenum;
    G4LogicalVolume*  fTiT;
    G4LogicalVolume*  fCopper;
    G4LogicalVolume*  fAl7;
    G4LogicalVolume*  fGe76;
    G4LogicalVolume*  fGe_nat;
    G4LogicalVolume*  fAl8;
    G4LogicalVolume*  fAulight;
    G4LogicalVolume*  biasFoil;
    G4LogicalVolume*  lastBiasFoil;
    G4LogicalVolume*  killFoil;


};

#endif
