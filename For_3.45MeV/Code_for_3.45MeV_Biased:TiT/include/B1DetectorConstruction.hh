/// \file B1DetectorConstruction.hh
/// \brief Definition of the B1DetectorConstruction class

#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class B1RunAction;
class DetectorMessenger;
/// Detector construction class to define materials and geometry.

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B1DetectorConstruction();
    virtual ~B1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    //Inline functions for stepping action class:
    
    //First part (flange):
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    G4LogicalVolume* GetMolyVolume()    const { return fMolybdenum; }
    G4LogicalVolume* GetTiTVolume()     const { return fTiT; }
    G4LogicalVolume* GetCopperVolume()  const { return fCopper; }

    //Second part (5 extra foils):
    G4LogicalVolume* GetAuXVolume()     const { return fAuX; }
    G4LogicalVolume* GetAl8Volume()     const { return fAl8; }
    G4LogicalVolume* GetGe73Volume()    const { return fGe73; }
    G4LogicalVolume* GetGe76Volume()    const { return fGe76; }
    G4LogicalVolume* GetAl7Volume()     const { return fAl7; }
  
     
    void ConstructSDandField();


  protected:
    //First part (flange):
    G4LogicalVolume*  fScoringVolume;
    G4LogicalVolume*  fMolybdenum;
    G4LogicalVolume*  fTiT;
    G4LogicalVolume*  fCopper;

    //Second part (5 extra foils):
    G4LogicalVolume*  fAuX;   //1st foil (a)
    G4LogicalVolume*  fAl8;   //1st foil (b)
    G4LogicalVolume*  fGe73;  //2nd foil
    G4LogicalVolume*  fGe76;  //3rd foil
    G4LogicalVolume*  fAl7;   //4th foil

    B1RunAction* run;

  private:
    DetectorMessenger* fDetectorMessenger;

};

#endif

