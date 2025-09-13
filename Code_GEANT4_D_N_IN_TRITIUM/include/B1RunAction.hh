/// \file B1RunAction.hh
/// \brief Definition of the B1RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "G4GenericAnalysisManager.hh"
#include "G4Timer.hh"
#include "B1SteppingAction.hh"
#include "B1TrackingAction.hh"

class G4Run;
class B1RunAction : public G4UserRunAction

{
  public:
    B1RunAction();
    virtual ~B1RunAction();
    
    virtual void   BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction  (const G4Run*);
    
    G4int GetRunId() const {return fRunID; };
    
    void oxygenNeutronEnergy(G4double);
    void carbonNeutronEnergy(G4double);
    void molyNeutronEnergy(G4double);
    void TiTNeutronEnergy(G4double);
    void copperNeutronEnergy(G4double);

    void Al7NeutronEnergy(G4double);
    void Ge76NeutronEnergy(G4double);
    void GeNatNeutronEnergy(G4double);
    void Al8NeutronEnergy(G4double);
    void AuLightNeutronEnergy(G4double);
    
    void Al7NeutronEnergyfromOxygen(G4double);
    void Al7NeutronEnergyfromCarbon(G4double);
    void Al7NeutronEnergyfromMoly(G4double);
    void Al7NeutronEnergyfromTiT(G4double);
    void Al7NeutronEnergyfromCopper(G4double);
    void Al7NeutronEnergyNotFromMoAndCu(G4double);
    

   private:
    G4int Nofneutrons;
    G4bool factoryOn; 
    G4Timer* time;

  protected:
  G4int  fRunID;
  G4double neu;

  //Part 1 (flange):
  G4double moly;
  G4double tit;
  G4double cop;

  //Part 2 (5 extra foils):
  G4double al7;
  
 
	void WriteToASCII();

};

#endif

