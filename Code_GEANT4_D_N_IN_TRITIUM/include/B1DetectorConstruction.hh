

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "DetectorMessenger.hh"
#include "G4GenericBiasingPhysics.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class B1RunAction;
class DetectorMessenger;

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    B1DetectorConstruction();

    virtual ~B1DetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
   
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    G4LogicalVolume* GetFlangeVolume()  const { return fFlange; }
    G4LogicalVolume* GetOxygenCollVolume()  const { return fOxygenColl; }
    G4LogicalVolume* GetOxygenAntVolume()  const { return fOxygenAnt; }
    G4LogicalVolume* GetCarbonCollVolume()  const { return fCarbonColl; }
    G4LogicalVolume* GetCarbonAntVolume()  const { return fCarbonAnt; }
    G4LogicalVolume* GetOxygenVolume()  const { return fOxygen; }
    G4LogicalVolume* GetCarbonVolume()  const { return fCarbon; }
    G4LogicalVolume* GetMolyVolume()    const { return fMolybdenum; }
    G4LogicalVolume* GetTiTVolume()     const { return fTiT; }
    G4LogicalVolume* GetCopperVolume()  const { return fCopper; }
    G4LogicalVolume* GetAl7Volume()     const { return fAl7; }
    G4LogicalVolume* GetGe76Volume()    const { return fGe76; }
    G4LogicalVolume* GetGenatVolume()   const { return fGe_nat; }
    G4LogicalVolume* GetAl8Volume()     const { return fAl8; }
    G4LogicalVolume* GetAulightVolume() const { return fAulight; }
    G4LogicalVolume* GetBiasFoil()      const { return biasFoil; }
    G4LogicalVolume* GetLasBiasFoil()   const { return lastBiasFoil; }
    G4LogicalVolume* GetKillFoil()      const { return killFoil; }

    int GetBiasingFactor() const { return biasingFactor;} 

  protected:
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

  private:
    DetectorMessenger* fMessenger;
    
  private:
   void SetAttributes();
   void DefineMaterials();
   void ConstructSDandField();

  private:
    int biasingFactor;

};

#endif

