/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"

#include "G4TrackVector.hh"
#include "G4DynamicParticle.hh"
#include "G4VCrossSectionDataSet.hh"
#include "G4BiasingProcessInterface.hh"
#include "G4VProcess.hh"

#include "G4TrackingManager.hh"
#include "G4UserTrackingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
//---------------------------------------------------------------------------------------------------

B1SteppingAction::B1SteppingAction(B1EventAction *eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction),
      fScoringVolume(0),
      fFlange(0),
      fOxygen(0),
      fCarbon(0),
      fMolybdenum(0),
      fTiT(0),
      fCopper(0),
      fAl7(0),
      fGe76(0),
      fGe_nat(0),
      fAl8(0),
      fAulight(0),
      biasFoil(0),
      killFoil(0),
      lastBiasFoil(0)

{}

B1SteppingAction::~B1SteppingAction()
{}

void B1SteppingAction::UserSteppingAction(const G4Step *step)
{
  G4double NeutronEnergy = 0.;
  G4String particle = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  const B1DetectorConstruction *detectorConstruction = static_cast<const B1DetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  

  if (!fScoringVolume)  {fScoringVolume  = detectorConstruction->GetScoringVolume();  }  
  if (!fFlange)         {fFlange         = detectorConstruction->GetFlangeVolume();   }
  if (!fOxygen)         {fOxygen         = detectorConstruction->GetOxygenVolume();  }
  if (!fOxygen)         {fOxygenColl     = detectorConstruction->GetOxygenCollVolume();  }
  if (!fOxygen)         {fOxygenAnt      = detectorConstruction->GetOxygenAntVolume();  }
  if (!fCarbon)         {fCarbon         = detectorConstruction->GetCarbonVolume();   }
  if (!fCarbon)         {fCarbonColl     = detectorConstruction->GetCarbonCollVolume();   }
  if (!fCarbon)         {fCarbonAnt      = detectorConstruction->GetCarbonAntVolume();   }
  if (!fMolybdenum)     {fMolybdenum     = detectorConstruction->GetMolyVolume();     }
  if (!fTiT)            {fTiT            = detectorConstruction->GetTiTVolume();      }
  if (!fCopper)         {fCopper         = detectorConstruction->GetCopperVolume();   }
  if (!fAl7)            {fAl7            = detectorConstruction->GetAl7Volume();      }
  if (!fGe76)           {fGe76           = detectorConstruction->GetGe76Volume();     }
  if (!fGe_nat)         {fGe_nat         = detectorConstruction->GetGenatVolume();    }
  if (!fAl8)            {fAl8            = detectorConstruction->GetAl8Volume();      }
  if (!fAulight)        {fAulight        = detectorConstruction->GetAulightVolume();  }

  if (!biasFoil)     {biasFoil     = detectorConstruction->GetBiasFoil();    }
  if (!killFoil)     {killFoil     = detectorConstruction->GetKillFoil();    }
  if (!lastBiasFoil) {lastBiasFoil = detectorConstruction->GetLasBiasFoil(); }

  G4LogicalVolume *volume     = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  G4LogicalVolume *postvolume = 0;

  G4int    parent = step->GetTrack()->GetParentID();
  G4double weight = step->GetTrack()->GetWeight();

  if (step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()) 
  { 
    postvolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume(); 
  }

  if (biasFoil != lastBiasFoil)
  { 
    if (parent == 0 && volume != killFoil && postvolume == killFoil) { step->GetTrack()->SetTrackStatus(fStopAndKill); } 
  }

  if (volume != biasFoil && parent == 0)
  {
    auto secondaries = step->GetSecondary();
    
    if (secondaries) 
    {
      size_t nSecondaries = secondaries->size();

      for (size_t i = 0; i < nSecondaries; i++)
      {
        G4Track *secTrack = secondaries->at(i);
        G4String secondariesName = secTrack->GetParticleDefinition()->GetParticleName();

        if (secondariesName != "deuteron") { secTrack->SetTrackStatus(fStopAndKill); }
    }
  }   
}

  if (particle == "neutron")
  {

    G4double NeutronEnergy = 0.;

    NeutronEnergy     = step->GetPreStepPoint()->GetKineticEnergy();
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();

        // All this information goes to event action and then to run action:
    if (volume != fCarbon    &&  postvolume  == fCarbon && (vertexVolume == fOxygenAnt || vertexVolume == fOxygenColl || vertexVolume == fOxygen))  { fEventAction->oxygenNeutronEnergy(NeutronEnergy);} 
    if (volume != fMolybdenum    &&  postvolume  == fMolybdenum    && (vertexVolume == fCarbonAnt || vertexVolume == fCarbonColl || vertexVolume == fCarbon))  { fEventAction->carbonNeutronEnergy(NeutronEnergy);  } 
    if (volume != fTiT    &&  postvolume  == fTiT    && vertexVolume == fMolybdenum)  { fEventAction->molyNeutronEnergy(NeutronEnergy);  } 
    if (volume != fCopper &&  postvolume  == fCopper && vertexVolume == fTiT)         { fEventAction->TiTNeutronEnergy(NeutronEnergy);   }
    if (volume == fCopper &&  postvolume  != fCopper && vertexVolume == fCopper)      { fEventAction->copperNeutronEnergy(NeutronEnergy);} 

    if (volume != fAl7     && postvolume == fAl7)      { fEventAction->Al7NeutronEnergy(NeutronEnergy);   }
    if (volume != fGe76    && postvolume == fGe76)     { fEventAction->Ge76NeutronEnergy(NeutronEnergy);  }
    if (volume != fGe_nat  && postvolume == fGe_nat)   { fEventAction->GeNatNeutronEnergy(NeutronEnergy); }
    if (volume != fAl8     && postvolume == fAl8)      { fEventAction->Al8NeutronEnergy(NeutronEnergy);   }
    if (volume != fAulight && postvolume == fAulight)  { fEventAction->Al8NeutronEnergy(NeutronEnergy);   }

    if (volume != fAl7 && postvolume == fAl7 && vertexVolume == fOxygen)                                { fEventAction->Al7NeutronEnergyfromOxygen(NeutronEnergy);       }
    if (volume != fAl7 && postvolume == fAl7 && vertexVolume == fCarbon)                                { fEventAction->Al7NeutronEnergyfromCarbon(NeutronEnergy);       }
    if (volume != fAl7 && postvolume == fAl7 && vertexVolume == fMolybdenum)                            { fEventAction->Al7NeutronEnergyfromMoly(NeutronEnergy);       }
    if (volume != fAl7 && postvolume == fAl7 && vertexVolume == fTiT)                                   { fEventAction->Al7NeutronEnergyfromTiT(NeutronEnergy);        }
    if (volume != fAl7 && postvolume == fAl7 && vertexVolume == fCopper)                                { fEventAction->Al7NeutronEnergyfromCopper(NeutronEnergy);     } 
    if (volume != fAl7 && postvolume == fAl7 && vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->Al7NeutronEnergyNotFromMoAndCu(NeutronEnergy); }
    
  }
} 

 



