/// \file B1TrackingAction.cc
/// \brief Implementation of the TrackingAction class

#include "B1TrackingAction.hh"

// #include "Run.hh"
// #include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "G4PhysicsTable.hh"
#include "B1DetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4INCLThreeVector.hh"
#include "G4ThreeVector.hh"

#include "G4Run.hh"
#include "G4WrapperProcess.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1TrackingAction::B1TrackingAction(B1EventAction *eventAction)
    : G4UserTrackingAction(),
      feventAction(eventAction),
      fNbStep1(0), fNbStep2(0), fTrackLen1(0.), fTrackLen2(0.), fTime1(0.), fTime2(0.),
      fTargetVolume(0), fScoringVolume(0), frunID(0)
{

  //   if (frunID == 10) {
  //    const B1RunAction* malakies =
  //     static_cast<const B1RunAction*>
  //    (G4RunManager::GetRunManager()->GetUserRunAction());
  //    frunID = malakies->GetRunId();
  //    G4cout << "RUUUUUUUUUNNNNNNID = " << frunID <<G4endl;
  //   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1TrackingAction::PreUserTrackingAction(const G4Track *track)
{
  fNbStep1 = fNbStep2 = 0;
  fTrackLen1 = fTrackLen2 = 0.;
  fTime1 = fTime2 = 0.;

  // if (frunID == 10) {
  //    const B1RunAction* malakies =
  //     static_cast<const B1RunAction*>
  //    (G4RunManager::GetRunManager()->GetUserRunAction());
  //    frunID = malakies->GetRunId();
  //    G4cout << "RUUUUUUUUUNNNNNNID = " << frunID <<G4endl;
  //   }
  // }
  //  const B1DetectorConstruction* detectorConstruction
  // = static_cast<const B1DetectorConstruction*>
  //   (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  //    fScoringVolume = detectorConstruction->GetScoringVolume();
  //    fTargetVolume = detectorConstruction->GetTargetVolume();
  // G4LogicalVolume* volume = track->GetVolume();
  //
  //
  /// / if (volume != fScoringVolume) return;
  //
  // G4String particle = track->GetParticleDefinition()->GetParticleName();
  //
  // if (particle == "neutron" )
  // {
  //   G4double NeutronEnergy = 0.;
  //   NeutronEnergy = track->GetKineticEnergy();
  //   G4double NeutronEnergyVertex = track->GetVertexKineticEnergy();
  //            G4cout <<"Vertex= " << NeutronEnergyVertex<< G4endl;
  //    G4cout <<"Neutron energy= " << NeutronEnergy<< G4endl;
  //    if (fScoringVolume == volume)
  //    {
  //      G4cout << "Volume1 = " <<fScoringVolume<< G4endl;
  //    }
  //    if (fTargetVolume == volume)
  //    {
  //      G4cout << "Volume2 = " <<fTargetVolume<< G4endl;
  //    }
  // }
  // if (particle == "proton")
  // {
  //   G4double ProtonEnergy = 0.;
  //   ProtonEnergy = track->GetKineticEnergy();
  //   G4cout <<"Proton energy= " << ProtonEnergy<< G4endl;
  // }

  // G4double KinEnergy = track->GetKineticEnergy();

  // G4cout << "energy= " << KinEnergy <<G4endl;
  // if (trackID > 1){
  // G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();

  // if(secondaries){
  // G4String particle = track->GetParticleDefinition()->GetParticleName();
  // size_t  nSecondaries = secondaries->size();
  // G4cout <<"particle = " << nSecondaries << G4endl;
  // for (size_t i=0; i< nSecondaries; i++)
  // {
  //
  //   G4String secondariesName = track->GetParticleDefinition()->GetParticleName();
  //   G4cout <<"secondariesNAME = " << secondariesName<< G4endl;
  //   if (secondariesName == "neutron")
  //
  //   {
  //     G4double NeutronEnergy = 0.;
  //     NeutronEnergy = track->GetKineticEnergy();
  //     feventAction->neutronKinEn(NeutronEnergy);
  //   }
  // }
  // }
  // G4cout <<"secondaries are = " << secondaries << G4endl;
  //}
}
// G4int currentStep = track->GetCurrentStepNumber();
// if (trackID == 2)
// {
//    G4String parId = track->GetParticleDefinition()->GetParticleName();
//    if (parId == "neutron")
//    {
//   //   G4double kinPre= track->GetStep()->GetPreStepPoint()->GetKineticEnergy();
// //     G4double kinPost = track->GetStep()->GetPostStepPoint()->GetKineticEnergy();
// //     G4cout << "kinPROOOOOO= " << kinPost<< " "<<track->GetKineticEnergy()<<G4endl;
//      G4cout << "kinPREEEEEE= " << " "<<track->GetKineticEnergy() <<G4endl;
//    }
//     G4cout << "parIdPREEEE= " << parId <<G4endl;
// }
//    G4String parId=track->GetParticleDefinition()->GetParticleName();
// G4int parentId = track->GetParentID();
// if (parId == "neutron" && parentId == 0){
//   nOfNeutrons++;
//   feventAction->neutronsNo(nOfNeutrons);
// // G4cout << "NUMBER OF NEUTRONS " << nOfNeutrons << G4endl;
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void B1TrackingAction::UpdateTrackInfo(const G4Track* track)
// {
//   // const G4double thermal = 1*eV;
//   // if (ekin > thermal) {
//   //   fNbStep1++; fTrackLen1 = trackl; fTime1 = time;
//   // } else {
//   //   fNbStep2++; fTrackLen2 = trackl - fTrackLen1; fTime2 = time - fTime1;
//   // }
//   // nOfNeutrons = 0;
//
// // G4Track* track = new G4Track();
// // G4String parId=track->GetParticleDefinition()->GetParticleName();
// // G4int parentId = track->GetParentID();
// // if (parId == "neutron" && parentId > 0){
// //   nOfNeutrons++;
// //
// // G4cout << "Number Of neutronS " << nOfNeutrons << G4endl;
// // }
// // nOfNeutrons++;
// // feventAction->neutronsNo(nOfNeutrons);
//
// }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1TrackingAction::PostUserTrackingAction(const G4Track *track)
{
  // keep only primary neutron
  //
 // if (!fTargetVolume)
 // {
 //   const B1DetectorConstruction *detectorConstruction = static_cast<const B1DetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
 //   fTargetVolume = detectorConstruction->GetTargetVolume();
 // }
 // // G4LogicalVolume* volume = track->GetVolume()->GetLogicalVolume();
//
 // // if (volume == fTargetVolume)
 // // {
//
 // // G4cout<<"fTargetVolume = " <<volume->GetName()<<G4endl;
//
 // //       = track->GetStep()->GetPostStepPoint()->GetTouchableHandle()
 // //         ->GetVolume()->GetLogicalVolume();// //
 // //     if (volume != fTargetVolume) return;//
 // if (track->GetParentID() == 0)
 // {
 //   // auto parentPosition = track->GetPosition();
 //   // G4cout<< "Parentposition = " <<parentPosition*cm<<G4endl;
 //   G4TrackVector *secondaries = fpTrackingManager->GimmeSecondaries();
//
 //   if (secondaries)
 //   {
 //     size_t nSecondaries = secondaries->size();
//
 //     for (size_t i = 0; i < nSecondaries; i++)
 //     {
 //       G4Track *secTrack = secondaries->at(i);
 //       G4String secondariesName = secTrack->GetParticleDefinition()->GetParticleName();
 //    //  G4cout << "secname =  " << secondariesName << G4endl;
 //       auto process = secTrack->GetCreatorProcess()->GetProcessName();
 //    // G4cout << "process =  " << process  << G4endl;
//
 //     // auto length = track->GetCreatorProcess();
 //      // G4WrapperProcess *proc = new G4WrapperProcess();
 //    //  auto kati =track->GetCreatorProcess()->GetCurrentInteractionLength();
//// G4cout<< "proc = " << G4BestUnit(kati,"Length") <<G4endl;
 //       G4LogicalVolume *volume = secTrack->GetVolume()->GetLogicalVolume();
 //       if (volume == fTargetVolume)
 //       {
//
 //         if (secondariesName == "neutron")
//
 //         {
 //           G4double NeutronEnergy = 0.;
  //          NeutronEnergy = secTrack->GetKineticEnergy();
             // auto parentPosition = track->GetPosition();
             // G4cout<< "Parentposition = " <<parentPosition/cm<<G4endl;
             // auto PREparentPosition = track->GetStep()->GetPreStepPoint()->GetPosition();
             // G4cout<< "PREParentposition = " <<PREparentPosition/cm<<G4endl;
             // auto VertexparentPosition = track->GetVertexPosition();
             // G4cout<< "VERTEXParentposition = " <<VertexparentPosition/cm<<G4endl;
             // auto parentEnergy = track->GetKineticEnergy();
             // G4cout<< "ParentEnergy = " <<parentEnergy<<G4endl;
             // auto PREparentENERGY = track->GetStep()->GetPreStepPoint()->GetKineticEnergy();
             // G4cout<< "PREEParentEnergy = " <<PREparentENERGY <<G4endl;
             // auto VERTEXparentEnergy = track->GetVertexKineticEnergy();
             // G4cout<< "VERTEXParentEnergy = " <<VERTEXparentEnergy <<G4endl;
            //G4cout <<"energy= " << NeutronEnergy<< G4endl;
            // G4double NeutronEnergyVertex = 0.;
            // feventAction->neutronKinEn(NeutronEnergy);
            // NeutronEnergyVertex = secTrack->GetVertexKineticEnergy();
            // G4cout <<"Vertex= " << NeutronEnergyVertex<< G4endl;
//            auto position = secTrack->GetPosition();
 //           // G4cout<< "position = " <<position/cm <<G4endl;
 //           G4double posX = position.getX();
 //           G4double posY = position.getY();
 //           G4double posZ = position.getZ();
           // auto process = secTrack->GetCreatorProcess()->GetProcessName();
          //  auto process2 = track->GetStep()->GetCurrentStepNumber()

          // G4cout << "PROCESS =  " << process2 << G4endl;
           // if (frunID == 0)
           // {
           //   const B1RunAction *malakies =
           //       static_cast<const B1RunAction *>(G4RunManager::GetRunManager()->GetUserRunAction());
           //   frunID = malakies->GetRunId();
           //   G4cout << "RUUUUUUUUUNNNNNNID skdjlasdjhaslkdj= " << frunID << G4endl;
           // }

            // if (frunID == 0){
 //          static std::ofstream stuff("gamiesaiFb10000000.txt");

 //          static bool first = true;
 //          if (first)
 //          {
 //            first = false;
 //            stuff << "positionX [cm]" << std::setw(10) << ""
 //                  << "positionY [cm]" << std::setw(10) << ""
 //                  << "positionZ [cm]" << std::setw(10) << ""
 //                  << "NeutronKinEn [MeV]" << std::setw(10) << ""
 //                  << "processName" << std::endl;
 //          }
 //          stuff << std::setw(12) << posX / cm 
 //                << std::setw(12) << "" 
 //                << std::setw(12) << posY / cm 
 //                << std::setw(12) << "" 
 //                << std::setw(12) << posZ / cm 
 //                << std::setw(12) << ""
 //                << std::setw(12) << NeutronEnergy 
 //                << std::setw(12) << ""
 //                << std::setw(12) << process << std::endl;
            // }
            // if (frunID == 1)
            // {
            //   static std::ofstream stuff2("gamiesaiKSANA.txt");
            //
            //  static bool first = true;
            //  if (first) {
            //  first = false;
            //  stuff2 << "positionX [cm]" <<std::setw (10) << ""<< "positionY [cm]" <<std::setw (10)<<""<<"positionZ [cm]" << std::endl;
            //  }
            //  stuff2 << std::setw (12) << posX/cm << std::setw (12)<< "" << std::setw (12) << posY/cm  << std::setw (12) << std::setw (12)<< "" << posZ/cm << std::endl;
            // }

            // static std::ofstream stuff2("stuff.txt");
            // static bool second = true;
            // if (second) {
            // second = false;
            // stuff2 << "#,eDep/keV,…"<< std::endl;
            // }
            // stuff2 << "," << posY /* … */ << std::endl;

            //    auto Vertexposition = secTrack->GetVertexPosition();
            //  //  G4cout<< "Vertex position = " <<Vertexposition <<G4endl;
            //    auto parentPosition = track->GetPosition();
            // //  G4cout<< "Parentposition = " <<parentPosition/cm<<G4endl;
            //   auto parentEnergy = track->GetKineticEnergy();
            // //  G4cout<< "Parentposition = " <<parentEnergy<<G4endl;
            //   auto energy = secTrack->GetKineticEnergy();
            //  G4cout<< "energy = " <<energy<<G4endl;
            //     G4int current_step = secTrack->GetCurrentStepNumber();
            //     G4int PARENTcurrent_step = track->GetCurrentStepNumber();
            // G4cout<< "PARENTstepNumber = " <<PARENTcurrent_step<<G4endl;
            //  G4cout<< "stepNumber = " <<current_step <<G4endl;
            //  G4cout<<"fTargetVolume = " <<volume->GetName()<<G4endl;
            //

            //
 //          }
// 
 //        } // //
 //      }   //
 //    }
 //  }
}

  //     if (!fScoringVolume) {
  //  const B1DetectorConstruction* detectorConstruction
  //    = static_cast<const B1DetectorConstruction*>
  //      (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  //  fScoringVolume = detectorConstruction->GetScoringVolume();
  // }
  //  G4LogicalVolume* volume
  //    = track->GetStep()->GetPreStepPoint()->GetTouchableHandle()
  //       ->GetVolume()->GetLogicalVolume();
  // if (volume != fScoringVolume) return;
  //   //
  // G4String particle = track->GetParticleDefinition()->GetParticleName();
  // if (particle == "neutron")
  // {
  //   G4double NeutronEnergy = 0.;
  //   NeutronEnergy = track->GetKineticEnergy();
  //    G4cout <<"Neutron energy= " << NeutronEnergy<< G4endl;
  // }
  // if (particle == "proton")
  // {
  //   G4double ProtonEnergy = 0.;
  //   ProtonEnergy = track->GetKineticEnergy();
  //   G4cout <<"Proton energy= " << ProtonEnergy<< G4endl;

  // if (trackID > 1) return;
  // G4String parId=track->GetParticleDefinition()->GetParticleName();
  // G4int parentId = track->GetParentID();
  // //parId == "neutron" &&
  // if (parId == "neutron" && parentId > 0){

  //f (trackID == 1)
  //
  //  G4int currentStep = track->GetCurrentStepNumber();
  //  G4double kinPre= track->GetStep()->GetPreStepPoint()->GetKineticEnergy();
  //  G4double kinPost = track->GetStep()->GetPostStepPoint()->GetKineticEnergy();
  //  G4String parId = track->GetStep()->GetTrack()->GetParticleDefinition()->GetParticleName();
  //
  // // G4cout << "currentStep= " << currentStep <<G4endl;
  // //    G4cout << "kinPre= " << kinPre <<G4endl;
  // //     G4cout << "kinPost= " << kinPost <<G4endl;
  // //      G4cout << "parID= " << parId <<G4endl;
  //
  // }

  // if (trackID == 2){
  //
  // G4String parId = track->GetStep()->GetTrack()->GetParticleDefinition()->GetParticleName();
  // G4int currentStep = track->GetCurrentStepNumber();
  // if (parId == "neutron" )
  // {
  //   G4double kinPre= track->GetStep()->GetPreStepPoint()->GetKineticEnergy();
  //   G4double kinPost = track->GetStep()->GetPostStepPoint()->GetKineticEnergy();
  //   G4cout << "kinPROOOOOO= " << kinPost <<G4endl;
  //   G4cout << "kinPREEEEEE= " << kinPre <<G4endl;
  // }
  //  G4double kinPre= track->GetStep()->GetPreStepPoint()->GetKineticEnergy();
  // G4double kinPost = track->GetStep()->GetPostStepPoint()->GetKineticEnergy();
  //  G4cout << "OUTkinPROOOOOO= " << kinPost <<G4endl;
  //   G4cout << "OUTkinPREEEEEE= " << kinPre <<G4endl;
  //  G4cout << "parIdPREEEE= " << parId <<G4endl;
  //  G4cout << "CURRREEENT STEP= " << currentStep <<G4endl;
  //
  //
  //
  //
  //
  //
  //

  //}
  //  if (trackID == 0 )
  //   feventAction->neutronsNo(nOfNeutrons);
  //G4cout << "NUMBER OF NEUTRONS " << nOfNeutrons << G4endl;
  // }

  // Run* run
  //    = static_cast<Run*>(
  //        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  // run->SumTrackLength(fNbStep1,fNbStep2,fTrackLen1,fTrackLen2,fTime1,fTime2);

  // histograms
  //
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // analysisManager->FillH1(1,fNbStep1);
  // analysisManager->FillH1(2,fTrackLen1);
  // analysisManager->FillH1(3,fTime1);
  // analysisManager->FillH1(4,fNbStep2);
  // analysisManager->FillH1(5,fTrackLen2);
  // analysisManager->FillH1(6,fTime2);
  // }

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
