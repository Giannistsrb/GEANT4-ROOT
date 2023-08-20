/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4THitsMap.hh"
#include "G4AnalysisManager.hh" 
#include <map>

class B1RunAction;

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction(B1RunAction* runAction);
    virtual ~B1EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void PrestepKin(G4double);
    void PoststepKin(G4double);
    void neutronKinEn(G4double);
    void NeutronEnergy(G4double);
    
    //First part (flange):
    //Neutron energies from the foils:
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
    //For Ge73:
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

    //-----------------------------------------------------------
    
    //Get the deuteron energy function:
    void DeuteronEnergy(G4double);

    



    void AddEdep2(G4String,G4double);
  private:
   G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                          const G4Event* event) const;
  G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
  void PrintEventStatistics(G4double neuFlux) const;

  G4int fneuFluxHCID;

    B1RunAction* fRunAction;
    G4double     fEdep;
    G4double totprot;
    G4double totel;
    G4double totgamma;
    G4double totneu;
    G4int noofneutronss;




    std::map<G4String,G4double> malakia;
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
