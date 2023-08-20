/// \file B1RunAction.hh
/// \brief Definition of the B1RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "G4AnalysisManager.hh"
#include "G4Timer.hh"
#include "B1SteppingAction.hh"
#include "B1TrackingAction.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.
const G4int MaxNtCol = 1;
class B1RunAction : public G4UserRunAction
{
  public:
    B1RunAction();
    virtual ~B1RunAction();

    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    
    G4int GetRunId() const {return fRunID; };

    void neutronKinEn(G4double);
    void FillDetected(G4double energy, G4int Z, G4int A, G4int particleID, G4double pos_x, G4double pos_y, G4double pos_z, G4int trackID, G4int parentID); // Information about detected particles
    
    void NeutronEnergy(G4double);
    //Part 1 (flange):
    //Neutron energy on each foil:
    void molyNeutronEnergy(G4double);
    void tiTNeutronEnergy(G4double);
    void copperNeutronEnergy(G4double);
    
    //Z-Position of Neutrons generated in each foil:
    void zPosMolyNeutronGenerated(G4double);
    void zPosTiTNeutronGenerated(G4double);
    void zPosCopperNeutronGenerated(G4double);

    //---------------------------------------------------------
    //Second part (5 extra foils):
    //For AuX:
    void AuXNeutronEnergy(G4double);
    void AuXNeutronEnergyfromMoly(G4double);
    void AuXNeutronEnergyfromTiT(G4double);
    void AuXNeutronEnergyfromCopper(G4double);
    void AuXNeutronEnergyNotFromMoAndCu(G4double);
    //For Al8:
    void Al8NeutronEnergy(G4double);
    void Al8NeutronEnergyfromMoly(G4double);
    void Al8NeutronEnergyfromTiT(G4double);
    void Al8NeutronEnergyfromCopper(G4double);
    void Al8NeutronEnergyNotFromMoAndCu(G4double);
    //For Ge76:
    void Ge73NeutronEnergy(G4double);
    void Ge73NeutronEnergyfromMoly(G4double);
    void Ge73NeutronEnergyfromTiT(G4double);
    void Ge73NeutronEnergyfromCopper(G4double);
    void Ge73NeutronEnergyNotFromMoAndCu(G4double);
    //For Ge76:
    void Ge76NeutronEnergy(G4double);
    void Ge76NeutronEnergyfromMoly(G4double);
    void Ge76NeutronEnergyfromTiT(G4double);
    void Ge76NeutronEnergyfromCopper(G4double);
    void Ge76NeutronEnergyNotFromMoAndCu(G4double);
    //For Al7:
    void Al7NeutronEnergy(G4double);
    void Al7NeutronEnergyfromMoly(G4double);
    void Al7NeutronEnergyfromTiT(G4double);
    void Al7NeutronEnergyfromCopper(G4double);
    void Al7NeutronEnergyNotFromMoAndCu(G4double);

    //Get the deuteron energy function:
    void DeuteronEnergy(G4double);

   private:
    G4int Nofneutrons;
    G4bool factoryOn; 
    G4int  fNtColId[MaxNtCol];
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

