/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Element.hh"
#include "G4Material.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VSDFilter.hh"
#include "G4PSCellFlux.hh"
#include "G4SDParticleFilter.hh"
#include "G4SDKineticEnergyFilter.hh"
#include "G4PhysicsVector.hh"
#include "G4LogicalVolumeStore.hh"

#include "B1OptrMultiParticleChangeCrossSection.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4UImanager.hh"
#include <iomanip>

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0), 
  fMolybdenum(0),
  fTiT(0),
  fCopper(0),
  fAuX(0),
  fAl8(0),
  fGe73(0),
  fGe76(0),
  fAl7(0)

  { 
    fDetectorMessenger = new DetectorMessenger(this);
  }

B1DetectorConstruction::~B1DetectorConstruction()
{ 
   delete fDetectorMessenger;
}

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{ 
  //***********************************************************************************************************
  //***********************************************************************************************************
  //***********************************************************************************************************
  //*********************THIS IS THE FIRST PART OF THE SIMULATION(ACCELERATOR LINE & FLANGE)*******************
  //***********************************************************************************************************
  //***********************************************************************************************************
  //***********************************************************************************************************

  // Define Materials:

  // Get nist material manager
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
   //Nist material:
    G4NistManager *nist    = G4NistManager::Instance();

   //Determine materials:
    G4Material *vacuum     = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material *air        = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *stainSteel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4Material *tantalum   = nist->FindOrBuildMaterial("G4_Ta");
    G4Material *aluminum   = nist->FindOrBuildMaterial("G4_Al");
    G4Material *molybdenum = nist->FindOrBuildMaterial("G4_Mo");
    G4Material *copper     = nist->FindOrBuildMaterial("G4_Cu");

   //Determine the Tritium Element (isotope):
    G4Isotope *tr = new G4Isotope("T", 1, 3, 3.01604928 * g / mole);
    G4Element *tritiumEle = new G4Element("Tele", "H3", 1);
    tritiumEle->AddIsotope(tr, 100. * perCent);

    //Determine the Helium3 Element (isotope):
    G4Isotope *helium3Iso = new G4Isotope("3He", 2, 3, 3.016029 * g / mole);
    G4Element *helium3 = new G4Element("3Helium", "He3", 1);
    helium3->AddIsotope(helium3Iso, 100. * perCent);

    //Determine the Titanium material:  
    G4Material *titanium = nist->FindOrBuildMaterial("G4_Ti");
    
    //Determine the TiT material and add the T, He and Ti into this:
    G4Material *TiT = new G4Material("TiT", 3.75 * g / cm3, 3);
    TiT->AddElement(tritiumEle, 0.4280745);
    TiT->AddElement(helium3, 0.1786855);
    TiT->AddMaterial(titanium, 0.39324); 

    //Determine the Silicon Carbide element:
    G4bool isotopes = true;
    G4Element *Si = nist->FindOrBuildElement("Si", isotopes);
    G4Element *C  = nist->FindOrBuildElement("C", isotopes);
    G4double density = 3.21 * g / cm3;

    //Making of the compounds and the material SiC:
    G4Material *SiC = new G4Material("SiliconCarbide", density, 2);
    SiC->AddElement(Si,1);
    SiC->AddElement(C,1);

   //Making of the world:
   G4Orb *solidWorld = new G4Orb("World", 10.0*m);

   //It is the logical volume named world:
   G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, //Volume..
                                                     air,  //Consists of..
                                                     "World"); //name..
    
    //It is the physical volume named world:
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,
                                                     G4ThreeVector(0., 0., 0.), //its position
                                                     logicWorld, //consistency
                                                     "World", //name
                                                     0,  //mother volume
                                                     false,
                                                     0,
                                                     true);  //check overlaps 

   //-------------------------------------------------------------------------
   //Determination of the line, 2.353cm<r<3.18cm, -140cm<z<0:

   G4ThreeVector posLine = G4ThreeVector(0., 0., 0.); //starting of the line

   // Polycon for the basic line, starting towards before z=0.
   G4double zPosLine[] = {0. * cm, -26.35 * cm, -26.35 * cm, -140. * cm};
   G4double inRadiusLine[] = {2.353 * cm, 2.353 * cm, 2.353 * cm, 2.353 * cm};
   G4double outRadiusLine[] = {3.18 * cm, 3.18 * cm, 2.71 * cm, 2.71 * cm};

   G4Polycone *lineSolid = new G4Polycone("line solid",
                                          0. *deg,
                                          360. *deg,
                                          4, 
                                          zPosLine, 
                                          inRadiusLine,
                                          outRadiusLine);

  G4LogicalVolume *logicLine = new G4LogicalVolume(lineSolid,
                                                   stainSteel,
                                                   "line_log");
  new G4PVPlacement(0,
                    posLine,
                    logicLine,
                    "line",
                    logicWorld,
                    false,
                    0,
                    true);

  //--------------------------------------------------------------------------
  //Determination of the LineVacuum, 0<r<2.353cm, -140cm<z<0:

  G4ThreeVector posVacuumLine = G4ThreeVector(0., 0., 0.);

  G4double zPosVacuumLine[] = {0. *cm, -140. *cm};
  G4double inRadVacuumLine[]   = {0. * cm, 0 * cm};
  G4double outRadVacuumLine[]  = {2.353 * cm, 2.353 * cm};

  G4Polycone *vacuumLineSolid = new G4Polycone("vacuumLineSolid",
                                               0. * deg,
                                               360. *deg,
                                               2, 
                                               zPosVacuumLine,
                                               inRadVacuumLine,
                                               outRadVacuumLine);

  G4LogicalVolume *vacuumLineLogic = new G4LogicalVolume(vacuumLineSolid,
                                                         vacuum,
                                                         "vacuumLine_logic");

  new G4PVPlacement(0,
                    posVacuumLine,
                    vacuumLineLogic,
                    "vacuumLine",
                    logicWorld,
                    false,
                    0,
                    true);
  
  //------------------------------------------------------------------------------
  //Collimator's Base. It is into the Vaccum the line. 0<z<0.983cm, 0.892cm<r<2.353cm

  G4ThreeVector posCollBase = G4ThreeVector(0., 0., -68.85 *cm);

  G4double zPosCol[]        = {0.    * cm, 0.04  * cm, 0.04  * cm, 0.318 * cm, 0.318 * cm, 0.715 * cm, 0.715 * cm, 0.983 * cm};
  G4double innerRadiusCol[] = {2.087 * cm, 2.087 * cm, 0.892 * cm, 0.892 * cm, 0.892 * cm, 0.892 * cm, 0.892 * cm, 0.892 * cm};
  G4double outerRadiusCol[] = {2.353 * cm, 2.353 * cm, 2.353 * cm, 2.353 * cm, 1.379 * cm, 1.379 * cm, 2.353 * cm, 2.353 * cm};

  G4Polycone *collBaseSolid = new G4Polycone("collimatorBase_Solid",
                                             0. *deg,
                                             360. *deg,
                                             8,
                                             zPosCol,
                                             innerRadiusCol,
                                             outerRadiusCol);

  G4LogicalVolume *logicColBase = new G4LogicalVolume(collBaseSolid, 
                                                  stainSteel,
                                                  "collimatorBase_log");

  new G4PVPlacement(0,
                    posCollBase,
                    logicColBase,
                    "collBase_phys",
                    vacuumLineLogic,  //mother volume of the collimator base is the vacuum line.
                    false,
                    0,
                    true);

  //---------------------------------------------------------------------------------------------------
  //Collimator. 0.168cm<r<2.087cm

  G4ThreeVector posColl = G4ThreeVector(0., 0., -68.83 * cm);

  G4Tubs *solidColl = new G4Tubs("collimator_solid",
                                  0.168 * cm,
                                  2.087 * cm,
                                  0.02 * cm,
                                  0. * deg,
                                  360. *deg);
                                
  G4LogicalVolume *logicColl = new G4LogicalVolume(solidColl,
                                                   tantalum,
                                                   "collimator_logic");

  new G4PVPlacement(0,
                    posColl,
                    logicColl,
                    "collimator_phys",
                    vacuumLineLogic,
                    false,
                    0,
                    true);

  //---------------------------------------------------------------------------------------
  //Antiscatterer's Base 

  G4ThreeVector posAntiBase = G4ThreeVector(0., 0., -28.364 * cm);

  G4double zPosAnti[]        = {0. * cm, 0.051 * cm, 0.051 * cm, 0.566 * cm, 0.566 * cm, 1.522 * cm, 1.522 * cm, 2.014 * cm}; 
  G4double innerRadiusAnti[] = {1.405 * cm, 1.405 * cm, 0.449 * cm, 0.449 * cm, 0.449 * cm, 0.449 * cm, 0.449 * cm, 0.449 * cm}; 
  G4double outerRadiusAnti[] = {2.353 * cm, 2.353 * cm, 2.353 * cm, 2.353 * cm, 1.332 * cm, 1.332 * cm, 2.353 * cm, 2.353 * cm};

  G4Polycone *antiBaseSolid = new G4Polycone("antiBase_Solid",
                                             0. * deg,
                                             360. * deg,
                                             8,
                                             zPosAnti, 
                                             innerRadiusAnti,
                                             outerRadiusAnti);
                                            
  G4LogicalVolume *logicAntiBase = new G4LogicalVolume(antiBaseSolid, 
                                                       aluminum,
                                                       "antiBase_log");
  
  new G4PVPlacement(0, 
                    posAntiBase, 
                    logicAntiBase,
                    "antiBase_phys",
                    vacuumLineLogic,
                    false,
                    0, 
                    true);
  
  //------------------------------------------------------------------------------------------
  //Antiscatterer

  G4ThreeVector posAnti = G4ThreeVector(0., 0., -28.3385 * cm);

  G4Tubs *solidAnti = new G4Tubs("anti_solid",
                                 0.205 * cm,
                                 1.405 * cm, 
                                 0.0255 * cm,
                                 0. * deg,
                                 360. *deg);
  
  G4LogicalVolume *logicAnti = new G4LogicalVolume(solidAnti, 
                                                   tantalum,
                                                   "anti_logic");

  new G4PVPlacement(0, 
                    posAnti, 
                    logicAnti,
                    "anti_phys", 
                    vacuumLineLogic, 
                    false,
                    0, 
                    true);

  //------------------------------------------------------------------------------------------------------
  //Flange

  G4ThreeVector posFlange = G4ThreeVector(0., 0., 0.);

  G4double zPosFlange[]   = {0. * cm, 3. * cm, 3 * cm, 15.8 * cm, 15.8 * cm, 16.5 * cm, 16.5 * cm, 17.8 * cm, 17.8 * cm, 18.3 * cm, 18.3 * cm, 18.5 * cm};
  G4double inRadFlange[]  = {2.353 * cm, 2.353 * cm, 5. * cm, 5. * cm, 4.5 * cm, 4.5 * cm, 2.5 * cm, 2.5 * cm, 1.425 * cm, 1.425 * cm, 0. * cm, 0. * cm};
  G4double outRadFlange[] = {9. * cm, 9. * cm, 5.7 * cm, 5.7 * cm, 5.7 * cm, 5.7 * cm, 5.7 * cm, 5.7 * cm, 5.7 * cm, 5.7 * cm, 5.7 * cm, 5.7 * cm};
  G4double endOfFlange    = 18.5 * cm;

  G4Polycone *solidFlange = new G4Polycone("flange", 
                                           0. *deg,
                                           360. * deg, 
                                           12, 
                                           zPosFlange, 
                                           inRadFlange, 
                                           outRadFlange);

  G4LogicalVolume *logicFlange = new G4LogicalVolume(solidFlange, 
                                                     aluminum, 
                                                     "flange_logic");

  new G4PVPlacement(0,
                    posFlange, 
                    logicFlange,
                    "flange_phys",
                    logicWorld,
                    false,
                    0,
                    true);
  
  //-------------------------------------------------------------------------------------------------------
  //Flange vacuum 

  G4ThreeVector posVacuumFlange = G4ThreeVector(0., 0., 0.);
  
  G4double zPosVacuumFlange[] = {0. * cm, 3. * cm, 3 * cm, 15.8 * cm, 15.8 * cm, 16.5 * cm, 16.5 * cm, 17.8 * cm, 17.8 * cm, 18.3 * cm};
  G4double inRadVacuumFlange[] = {0. * cm, 0. * cm, 0. * cm, 0. * cm, 0. * cm, 0. * cm, 0. * cm, 0. * cm, 0. * cm, 0. * cm};
  G4double outRadVacuumFlange[] = {2.353 * cm, 2.353 * cm, 5. * cm, 5. * cm, 4.5 * cm, 4.5 * cm, 2.5 * cm, 2.5 * cm, 1.425 * cm, 1.425 * cm};

  G4Polycone *solidVacuumFlange = new G4Polycone("vacuumFlange",
                                                 0. * deg,
                                                 360. * deg,
                                                 10,
                                                 zPosVacuumFlange,
                                                 inRadVacuumFlange,
                                                 outRadVacuumFlange);

  G4LogicalVolume *logicVacuumFlange = new G4LogicalVolume(solidVacuumFlange,
                                                           vacuum,
                                                           "vacuumFlange_logic");

  new G4PVPlacement(0,
                    posVacuumFlange,
                    logicVacuumFlange,
                    "vacuumFlange_phys",
                    logicWorld, 
                    false, 
                    0, 
                    true);

  //--------------------------------------------------------------------------------------
  //Molybdenum

  G4ThreeVector posMoly = G4ThreeVector(0., 0., 18.19893 * cm);

  G4Tubs *solidMoly = new G4Tubs("moly_solid",
                                 0. * cm,
                                 1.425 * cm,
                                 0.0005 * cm,
                                 0. * deg, 
                                 360. * deg);

  G4LogicalVolume *logicMoly = new G4LogicalVolume(solidMoly,
                                                   molybdenum,
                                                   "moly_logic");

  new G4PVPlacement(0, 
                    posMoly,
                    logicMoly, 
                    "moly_phys",
                    logicVacuumFlange,
                    false, 
                    0,
                    true);

  //-------------------------------------------------------------------------------
  //TiT

  G4ThreeVector posTit = G4ThreeVector(0., 0., 18.199715 * cm);

  G4Tubs *solidTit = new G4Tubs("Tit_solid",
                                0. * cm, 
                                1.27 * cm, 
                                0.000285 * cm,
                                0. * deg, 
                                360. * deg);

  G4LogicalVolume *logicTit = new G4LogicalVolume(solidTit,
                                                  TiT, 
                                                  "Tit_logic");

  new G4PVPlacement(0, 
                    posTit,
                    logicTit,
                    "Tit_phys",
                    logicVacuumFlange,
                    false,
                    0,
                    true);

  //-----------------------------------------------------------------------------------
  //Copper

  G4ThreeVector posCopper = G4ThreeVector(0., 0., 18.25 * cm);

  G4Tubs *solidCop = new G4Tubs("cop_solid",
                                0. * cm,
                                1.425 * cm, 
                                0.05 * cm,
                                0. * deg, 
                                360. * deg);

  G4LogicalVolume *logicCop = new G4LogicalVolume(solidCop,
                                                  copper,
                                                  "copper_logic");

  new G4PVPlacement(0, 
                   posCopper, 
                   logicCop,
                   "copper_phys",
                   logicVacuumFlange,
                   false,
                   0,
                   true);


                                  //#####DETECTOR#####
                                  //##################

    G4ThreeVector posDetector = G4ThreeVector(0., 0., 40 *cm); //28.2764401 *cm (in the initial experiment with only the first part).

    G4Tubs *solidDetector = new G4Tubs("detector_solid", 
                                       0.   *cm, 
                                       3.   *cm,
                                       2.5  *cm, 
                                       0.   *deg, 
                                       360. *deg);

    G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector,
                                                         vacuum, 
                                                         "detector_logic");

    new G4PVPlacement(0, 
                      posDetector, 
                      logicDetector, 
                      "detector_phys",
                      logicWorld, 
                      false, 
                      0, 
                      true);

        
  //***********************************************************************************************************
  //***********************************************************************************************************
  //***********************************************************************************************************
  //************************THIS IS THE SECOND PART OF THE LINE (5 EXTRA COMPLEX FOILS)************************
  //***********************************************************************************************************
  //***********************************************************************************************************
  //***********************************************************************************************************  
  
  //MATERIALS DEFINITION:

  //Determine new materials:
  //We need: aluminum, iron, hydrogen, oxygen, carbon, chlorine, gold, germanium
  //**Aluminum foil is determined in the first part**
  G4Material *iron      = nist->FindOrBuildMaterial("G4_Fe");
  G4Material *hydrogen  = nist->FindOrBuildMaterial("G4_H");
  G4Material *oxygen    = nist->FindOrBuildMaterial("G4_O");
  G4Material *carbon    = nist->FindOrBuildMaterial("G4_C");
  G4Material *chlorine  = nist->FindOrBuildMaterial("G4_Cl");
  G4Material *gold      = nist->FindOrBuildMaterial("G4_Au");
  G4Material *germanium = nist->FindOrBuildMaterial("G4_Ge");

  //DETERMINE SPECIAL MATERIALS:
  //WE NEED: mylar_mat, Ge73_mat (natural), PVC_mat.
  /////////////////////////////////////////////////////////////////
  //Densities:
  G4double density_mylar  = 1.40 * g / cm3; //mylar
  G4double density_Ge73   = 2.82 * g / cm3; //Ge73
  G4double density_Ge76   = 3.04 * g / cm3; //Ge76
  G4double density_PVC    = 1.40 * g / cm3; //PVC
  //----------------------------------------------------
  //Determination of the mylar material which consists of hydrogen, carbon and oxygen:
  G4Material *mylar_mat = new G4Material("mylar", density_mylar, 3);
  //Add the consistency of the materials inside the mylar_mat:
  mylar_mat->AddMaterial(hydrogen, 0.041959);
  mylar_mat->AddMaterial(carbon,   0.625017);
  mylar_mat->AddMaterial(oxygen,   0.333025);
  //Determination of the Ge73 material which consists of oxygen and the isotopes Ge-70, Ge-72, Ge-73, Ge-74, Ge-76.
  //Isotopes of Ge:
  G4Isotope *isGe70inGe73 = new G4Isotope("isGe-70-in-Ge73", 32, 70, 69.92424900  * g / mole);
  G4Isotope *isGe72inGe73 = new G4Isotope("isGe-72-in-Ge73", 32, 72, 71.92207580  * g / mole);
  G4Isotope *isGe73inGe73 = new G4Isotope("isGe-73-in-Ge73", 32, 73, 72.92345900  * g / mole);
  G4Isotope *isGe74inGe73 = new G4Isotope("isGe-74-in-Ge73", 32, 74, 73.92117776  * g / mole);
  G4Isotope *isGe76inGe73 = new G4Isotope("isGe-76-in-Ge73", 32, 76, 75.92140270  * g / mole);
  //Determination of all the isotopes as elements: 
  G4Element *Ge70ElinGe73 = new G4Element("Ge70_Element-in-Ge73", "Ge70", 1);
  G4Element *Ge72ElinGe73 = new G4Element("Ge72_Element-in-Ge73", "Ge72", 1);
  G4Element *Ge73ElinGe73 = new G4Element("Ge73_Element-in-Ge73", "Ge73", 1);
  G4Element *Ge74ElinGe73 = new G4Element("Ge74_Element-in-Ge73", "Ge74", 1);
  G4Element *Ge76ElinGe73 = new G4Element("Ge76_Element-in-Ge73", "Ge76", 1);
  Ge70ElinGe73->AddIsotope(isGe70inGe73, 100. * perCent);
  Ge72ElinGe73->AddIsotope(isGe72inGe73, 100. * perCent);
  Ge73ElinGe73->AddIsotope(isGe73inGe73, 100. * perCent);
  Ge74ElinGe73->AddIsotope(isGe74inGe73, 100. * perCent);
  Ge76ElinGe73->AddIsotope(isGe76inGe73, 100. * perCent);
  //Add the consistency of the materials inside the Ge73_mat:
  G4Material *Ge73_mat = new G4Material("Ge73", density_Ge73, 6);
  Ge73_mat->AddElement(Ge70ElinGe73,  0.000278033260464 * 100. * perCent);
  Ge73_mat->AddElement(Ge72ElinGe73,  0.019740361492929 * 100. * perCent);
  Ge73_mat->AddElement(Ge73ElinGe73,  0.667766383318889 * 100. * perCent);
  Ge73_mat->AddElement(Ge74ElinGe73,  0.007159356456942 * 100. * perCent);
  Ge73_mat->AddElement(Ge76ElinGe73,  0.000139016630232 * 100. * perCent);
  Ge73_mat->AddMaterial(oxygen,       0.304916848840545 * 100. * perCent);

  //------------------------------------------------------
  //Determination of the Ge76 material which consists of oxygen and the isotopes Ge-70, Ge-72, Ge-73, Ge-74, Ge-76.
  //Isotopes of Ge:
  G4Isotope *isGe70inGe76 = new G4Isotope("isGe-70-in-Ge76", 32, 70, 69.92424900  * g / mole);
  G4Isotope *isGe72inGe76 = new G4Isotope("isGe-72-in-Ge76", 32, 72, 71.92207580  * g / mole);
  G4Isotope *isGe73inGe76 = new G4Isotope("isGe-73-in-Ge76", 32, 73, 72.92345900  * g / mole);
  G4Isotope *isGe74inGe76 = new G4Isotope("isGe-74-in-Ge76", 32, 74, 73.92117776  * g / mole);
  G4Isotope *isGe76inGe76 = new G4Isotope("isGe-76-in-Ge76", 32, 76, 75.92140270  * g / mole);
  //Determination of all the isotopes as elements: 
  G4Element *Ge70ElinGe76 = new G4Element("Ge70_Element-in-Ge76", "Ge70", 1);
  G4Element *Ge72ElinGe76 = new G4Element("Ge72_Element-in-Ge76", "Ge72", 1);
  G4Element *Ge73ElinGe76 = new G4Element("Ge73_Element-in-Ge76", "Ge73", 1);
  G4Element *Ge74ElinGe76 = new G4Element("Ge74_Element-in-Ge76", "Ge74", 1);
  G4Element *Ge76ElinGe76 = new G4Element("Ge76_Element-in-Ge76", "Ge76", 1);
  Ge70ElinGe76->AddIsotope(isGe70inGe76, 100. * perCent);
  Ge72ElinGe76->AddIsotope(isGe72inGe76, 100. * perCent);
  Ge73ElinGe76->AddIsotope(isGe73inGe76, 100. * perCent);
  Ge74ElinGe76->AddIsotope(isGe74inGe76, 100. * perCent);
  Ge76ElinGe76->AddIsotope(isGe76inGe76, 100. * perCent);
  //Add the consistency of the materials inside the Ge76_mat:
  G4Material *Ge76_mat = new G4Material("Ge76", density_Ge76, 6);
  Ge76_mat->AddElement(Ge70ElinGe76,  0.000422132532509 * 100. * perCent);
  Ge76_mat->AddElement(Ge72ElinGe76,  0.000633198798763 * 100. * perCent);
  Ge76_mat->AddElement(Ge73ElinGe76,  0.000422132532509 * 100. * perCent);
  Ge76_mat->AddElement(Ge74ElinGe76,  0.079712693222053 * 100. * perCent);
  Ge76_mat->AddElement(Ge76ElinGe76,  0.622364063761943 * 100. * perCent);
  Ge76_mat->AddMaterial(oxygen,       0.29644577915223  * 100. * perCent);
  //------------------------------------------------------------------------------
  //Determination of PVC material which consists of chlorine, hydrogen, oxygen:
  G4Material *PVC_mat = new G4Material("PVC", density_PVC, 3);
  PVC_mat->AddMaterial(chlorine, 0.56726);
  PVC_mat->AddMaterial(hydrogen, 0.04838);
  PVC_mat->AddMaterial(oxygen,   0.38435);
  
  //-----------------------------------------------------------------------------------------------------------
  //TARGET HOLDERS: There are three target holders which hold the five foils. 
  //They consist of iron and they are three rectangular parallelepiped: the target_holder_bottom (#1),
  //the target_holder_left (#2) and the target_holder_right (#3).
  //We determine, in general, the base and the height of the holder in the (x,y,z) system having in mind that the center (0,0,0) 
  //is the center of the target foils. Also, we determine the distance beetween the end of the flange and the left 
  //corner of the holder and so, the distance beetween the end of the flange and the center of holder.
  //-----------------------------------------------------------------------------------------------------------
  //Outter radius of the rings:
  G4double r_out = 2.983 * cm;
  //Bases and heights of each holder:
  //Bottom:
  G4double b_bottom  = 7.000 * cm;   //base
  G4double h_bottom  = 0.500 * cm;   //height
  //Left:
  G4double b_left    = 0.515 * cm;   //base
  G4double h_left    = 4.500 * cm;   //height
  //Right:
  G4double b_right   = 0.515 * cm;   //base
  G4double h_right   = 4.500 * cm;   //height

  //-----------------------------------------------------------------------------------------------------------
  //TARGET HOLDER BOTTOM: 
  //Variables:
  //x-axis and y-axis centers:
  G4double center_bottom_x = 0;   //x axis center
  G4double center_bottom_y = -(r_out + h_bottom / 2);   //y axis center
  //depth of bottom holder (in z axis):
  G4double l_bottom = 4.0 * cm;
  //Distance beetween the end of the flange and the left corner of the bottom holder:
  G4double d_flange_holder_bottom = 2.3 * cm;
  //z-axis position of the center of the bottom target holder:
  G4double center_bottom_z = endOfFlange + d_flange_holder_bottom + l_bottom * 0.5; 
  //Position in (x,y,z) for the center of the bottom holder:
  G4ThreeVector pos_bottom_holder = G4ThreeVector(center_bottom_x, center_bottom_y, center_bottom_z);

  //Starting the construction of the geometry:
  //Target holder bottom:
  G4Box *bottom_holder = new G4Box("target_holder_bottom",
                                             b_bottom / 2,
                                             h_bottom / 2,
                                             l_bottom / 2);

  G4LogicalVolume *logic_bottom_holder = new G4LogicalVolume(bottom_holder,
                                                                      iron, 
                                                      "bottom_holder_logic");


  new G4PVPlacement(                 0, 
                     pos_bottom_holder, 
                   logic_bottom_holder,
                  "bottom_holder_phys",
                            logicWorld,
                                 false,
                                     0,
                                  true);

  //-----------------------------------------------------------------------------------------------------------
  //TARGET HOLDER RIGHT:
  //Variables:
  //x-axis and y-axis centers:
  G4double center_right_x =   r_out + b_right / 2;   //x axis center
  G4double center_right_y = -(r_out - h_right / 2);  //y axis center
  //depth of right holder (in z axis):
  G4double l_right = 3.7 * cm;
  //Distance beetween the end of the flange and the left corner of the right holder:
  G4double d_flange_holder_right = 2.3 * cm;
  //z-axis position of the center of the right target holder:
  G4double center_right_z = endOfFlange + d_flange_holder_right + l_right * 0.5; 
  //Position in (x,y,z) for the center of the right holder:
  G4ThreeVector pos_right_holder = G4ThreeVector(center_right_x, center_right_y, center_right_z);

  //Starting the construction of the geometry:
  //Target holder right:
  G4Box *right_holder = new G4Box("target_holder_right",
                                            b_right / 2,
                                            h_right / 2,
                                            l_right / 2);

  G4LogicalVolume *logic_right_holder = new G4LogicalVolume(right_holder,
                                                                    iron, 
                                                    "right_holder_logic");


  new G4PVPlacement(                 0, 
                      pos_right_holder, 
                    logic_right_holder,
                   "right_holder_phys",
                            logicWorld,
                                 false,
                                     0,
                                  true);

//-----------------------------------------------------------------------------------------------------------
  //TARGET HOLDER LEFT:
  //Variables:
  //x-axis and y-axis centers:
  G4double center_left_x =  -(r_out + b_left / 2);   //x axis center
  G4double center_left_y =  -(r_out - h_left / 2);  //y axis center
  //depth of left holder (in z axis):
  G4double l_left = 3.7 * cm;
  //Distance beetween the end of the flange and the left corner of the left holder:
  G4double d_flange_holder_left = 2.3 * cm;
  //z-axis position of the center of the left target holder:
  G4double center_left_z = endOfFlange + d_flange_holder_left + l_left * 0.5; 
  //Position in (x,y,z) for the center of the left holder:
  G4ThreeVector pos_left_holder = G4ThreeVector(center_left_x, center_left_y, center_left_z);

  //Starting the construction of the geometry:
  //Target holder left:
  G4Box *left_holder = new G4Box("target_holder_left",
                                            b_left / 2,
                                            h_left / 2,
                                            l_left / 2);

  G4LogicalVolume *logic_left_holder = new G4LogicalVolume(left_holder,
                                                                  iron, 
                                                    "left_holder_logic");


  new G4PVPlacement(                 0, 
                       pos_left_holder, 
                     logic_left_holder,
                    "left_holder_phys",
                            logicWorld,
                                 false,
                                     0,
                                  true);
  //-----------------------------------------------------------------------------------------------------------
  //FIRST FOIL: Name: 'AuX-Al8' 
  //Consists of the 'target_AuX', 'target_Al8', 'ring_AuX_Al8', 'mylar_AuX_Al8'. 
  //We need to set (a) the distance between the end of flange and the left corner of every 'subfoil', 
  //(b) the center of every 'subfoil', (c) the depth of each and (d) the radius of each. 
  //-----------------------------------------------------------------------------------------------------------
  //Variables: 
  //Distances between the end of flange and the left corner of every 'subfoil':
  G4double d_flange_target_AuX     = 2.34 * cm;
  G4double d_flange_target_Al8     = 2.40 * cm;
  G4double d_flange_ring_AuX_Al8   = 2.40 * cm;
  G4double d_flange_mylar_AuX_Al8  = 2.40 * cm;
  //Depths for every 'subfoil':
  G4double l_target_AuX     = 0.06 * cm;
  G4double l_target_Al8     = 0.05 * cm;
  G4double l_ring_AuX_Al8   = 0.14 * cm;
  G4double l_mylar_AuX_Al8  = 0.14 * cm;
  //Radiuses:
  G4double r_target_AuX            = 1.000 * cm;
  G4double r_target_Al8            = 1.000 * cm;
  G4double r_ring_min_AuX_Al8      = 2.431 * cm;
  G4double r_ring_max_AuX_Al8      = 2.983 * cm;
  G4double r_mylar_min_AuX_Al8     = 1.000 * cm;
  G4double r_mylar_max_Aux_Al8     = 2.431 * cm;
  //z-axis position of the left corners of the 'subfoils':
  G4double z_flange_target_AuX = endOfFlange + d_flange_target_AuX;
  G4double z_flange_target_Al8 = endOfFlange + d_flange_target_Al8;
  G4double z_flange_ring_AuX_Al8   = endOfFlange + d_flange_ring_AuX_Al8;
  G4double z_flange_mylar_AuX_Al8  = endOfFlange + d_flange_mylar_AuX_Al8;
  //z-axis positions in the centers of the 'subfoils':
  G4double center_target_AuX = z_flange_target_AuX    + l_target_AuX     * 0.5;
  G4double center_target_Al8 = z_flange_target_Al8    + l_target_Al8     * 0.5;
  G4double center_ring_AuX_Al8   = z_flange_ring_AuX_Al8  + l_ring_AuX_Al8   * 0.5;
  G4double center_mylar_AuX_Al8  = z_flange_mylar_AuX_Al8 + l_mylar_AuX_Al8  * 0.5;
  //-----------------------------------------------------------------------------------------------------------
  //Starting the construction of the geometry:
  //AuX-target. Material = Gold.
  G4Tubs *target_AuX = new G4Tubs("target-AuX", 
                                            0,
                                 r_target_AuX,  
                             l_target_AuX / 2,
                                   0.   * deg,
                                   360. * deg);

  G4LogicalVolume *logic_target_AuX = new G4LogicalVolume(target_AuX, 
                                                                gold, 
                                                 "logical_target_AuX");

  new G4PVPlacement(                                       0,
                    G4ThreeVector(0., 0., center_target_AuX), 
                                            logic_target_AuX,
                                           "AuX_target_phys",
                                                  logicWorld,
                                                       false,
                                                           0,
                                                        true);


  //Al8-target. Material = aluminum.
  G4Tubs *target_Al8 = new G4Tubs("target-Al8", 
                                            0,
                                 r_target_Al8,  
                             l_target_Al8 / 2,
                                   0.   * deg,
                                   360. * deg);

  G4LogicalVolume *logic_target_Al8 = new G4LogicalVolume(target_Al8, 
                                                            aluminum, 
                                                 "logical_target_Al8");

  new G4PVPlacement(                                       0,
                    G4ThreeVector(0., 0., center_target_Al8), 
                                            logic_target_Al8,
                                           "Al8_target_phys",
                                                  logicWorld,
                                                       false,
                                                           0,
                                                        true);

  //AuX-Al8-ring. Material = iron.
  G4Tubs *ring_AuX_Al8 = new G4Tubs("ring-AuX-Al8", 
                            r_ring_min_AuX_Al8,
                            r_ring_max_AuX_Al8,  
                            l_ring_AuX_Al8 / 2,
                                    0.   * deg,
                                    360. * deg);

  G4LogicalVolume *logic_ring_AuX_Al8 = new G4LogicalVolume(ring_AuX_Al8, 
                                                                    iron, 
                                                  "logical_ring_AuX_Al8");

  new G4PVPlacement(                                     0,
                    G4ThreeVector(0., 0., center_ring_AuX_Al8), 
                                            logic_ring_AuX_Al8,
                                           "AuX_Al8_ring_phys",
                                                    logicWorld,
                                                         false,
                                                             0,
                                                          true);


  //AuX-Al8-mylar.
  G4Tubs *mylar_AuX_Al8 = new G4Tubs( "mylar-AuX-Al8", 
                                  r_mylar_min_AuX_Al8,
                                  r_mylar_max_Aux_Al8,  
                                  l_mylar_AuX_Al8 / 2,
                                           0.   * deg,
                                           360. * deg);

  G4LogicalVolume *logic_mylar_AuX_Al8 = new G4LogicalVolume(mylar_AuX_Al8, 
                                                                 mylar_mat, 
                                                    "logical_mylar_AuX_Al8");

  new G4PVPlacement(                                          0,
                    G4ThreeVector(0., 0., center_mylar_AuX_Al8), 
                                            logic_mylar_AuX_Al8,
                                           "AuX_Al8_mylar_phys",
                                                     logicWorld,
                                                          false,
                                                              0,
                                                           true);
   
//-----------------------------------------------------------------------------------------------------------
  //SECOND FOIL: Name: 'Ge73' 
  //Consists of the 'target_Ge73', 'ring_Ge73', 'mylar_Ge73'. 
  //We need to set (a) the distance between the end of flange and the left corner of every 'subfoil', 
  //(b) the center of every 'subfoil', (c) the depth of each and (d) the radius of each. 
  //-----------------------------------------------------------------------------------------------------------
  //Variables: 
  //Distances between the end of flange and the left corner of every 'subfoil':
  G4double d_flange_target_Ge73 = 2.497 * cm;
  G4double d_flange_ring_Ge73   = 2.800 * cm;
  G4double d_flange_mylar_Ge73  = 2.800 * cm;
  //Depths for every 'subfoil':
  G4double l_target_Ge73 = 0.303 * cm;
  G4double l_ring_Ge73   = 0.140 * cm;
  G4double l_mylar_Ge73  = 0.140 * cm;
  //Radiuses:
  G4double r_target_Ge73    = 1.000 * cm;
  G4double r_ring_min_Ge73  = 2.431 * cm;
  G4double r_ring_max_Ge73  = 2.983 * cm;
  G4double r_mylar_Ge73     = 2.431 * cm;
  //z-axis position of the left corners of the 'subfoils':
  G4double z_flange_target_Ge73 = endOfFlange + d_flange_target_Ge73;
  G4double z_flange_ring_Ge73   = endOfFlange + d_flange_ring_Ge73;
  G4double z_flange_mylar_Ge73  = endOfFlange + d_flange_mylar_Ge73;
  //z-axis positions in the centers of the 'subfoils':
  G4double center_target_Ge73 = z_flange_target_Ge73 + l_target_Ge73 * 0.5;
  G4double center_ring_Ge73   = z_flange_ring_Ge73   + l_ring_Ge73   * 0.5;
  G4double center_mylar_Ge73  = z_flange_mylar_Ge73  + l_mylar_Ge73  * 0.5;
  //-----------------------------------------------------------------------------------------------------------
  //Starting the construction of the geometry:
  //Ge73-target. Material = Ge73_mat.
  G4Tubs *target_Ge73 = new G4Tubs("target-Ge73", 
                                               0,
                                   r_target_Ge73,  
                               l_target_Ge73 / 2,
                                      0.   * deg,
                                      360. * deg);

  G4LogicalVolume *logic_target_Ge73 = new G4LogicalVolume(target_Ge73, 
                                                              Ge73_mat, 
                                                  "logical_target_Ge73");

  new G4PVPlacement(                                       0,
                    G4ThreeVector(0., 0., center_target_Ge73), 
                                            logic_target_Ge73,
                                           "Ge73_target_phys",
                                                  logicWorld,
                                                       false,
                                                           0,
                                                        true);

  //Ge73-ring. Material = PVC.
  G4Tubs *ring_Ge73 = new G4Tubs("ring-Ge73", 
                            r_ring_min_Ge73,
                            r_ring_max_Ge73,  
                            l_ring_Ge73 / 2,
                                0.   * deg,
                                360. * deg);

  G4LogicalVolume *logic_ring_Ge73 = new G4LogicalVolume(ring_Ge73, 
                                                            PVC_mat, 
                                                "logical_ring_Ge73");

  new G4PVPlacement(                                      0,
                    G4ThreeVector(0., 0., center_ring_Ge73), 
                                            logic_ring_Ge73,
                                           "Ge73_ring_phys",
                                                 logicWorld,
                                                      false,
                                                          0,
                                                        true);


  //Ge76-mylar.
  G4Tubs *mylar_Ge73 = new G4Tubs( "mylar-Ge76", 
                                              0,
                                   r_mylar_Ge73,  
                               l_mylar_Ge73 / 2,
                                     0.   * deg,
                                     360. * deg);

  G4LogicalVolume *logic_mylar_Ge73 = new G4LogicalVolume(mylar_Ge73, 
                                                           mylar_mat, 
                                                 "logical_mylar_Ge73");

  new G4PVPlacement(                                      0,
                    G4ThreeVector(0., 0., center_mylar_Ge73), 
                                            logic_mylar_Ge73,
                                           "Ge73_mylar_phys",
                                                  logicWorld,
                                                       false,
                                                           0,
                                                        true);                                                  

  //-----------------------------------------------------------------------------------------------------------
  //THIRD FOIL: Name: 'Ge76' 
  //Consists of the 'target_Ge76', 'ring_Ge76', 'mylar_Ge76'. 
  //We need to set (a) the distance between the end of flange and the left corner of every 'subfoil', 
  //(b) the center of every 'subfoil', (c) the depth of each and (d) the radius of each. 
  //-----------------------------------------------------------------------------------------------------------
  //Variables: 
  //Distances between the end of flange and the left corner of every 'subfoil':
  G4double d_flange_target_Ge76 = 3.0 * cm;
  G4double d_flange_ring_Ge76   = 3.0 * cm;
  G4double d_flange_mylar_Ge76  = 3.0 * cm;
  //Depths for every 'subfoil':
  G4double l_target_Ge76 = 0.238 * cm;
  G4double l_ring_Ge76   = 0.140 * cm;
  G4double l_mylar_Ge76  = 0.140 * cm;
  //Radiuses:
  G4double r_target_Ge76        = 1.000 * cm;
  G4double r_ring_min_Ge76      = 2.431 * cm;
  G4double r_ring_max_Ge76      = 2.983 * cm;
  G4double r_mylar_min_Ge76     = 1.000 * cm;
  G4double r_mylar_max_Ge76     = 2.431 * cm; 
  //z-axis position of the left corners of the 'subfoils':
  G4double z_flange_target_Ge76 = endOfFlange + d_flange_target_Ge76;
  G4double z_flange_ring_Ge76   = endOfFlange + d_flange_ring_Ge76;
  G4double z_flange_mylar_Ge76  = endOfFlange + d_flange_mylar_Ge76;
  //z-axis positions in the centers of the 'subfoils':
  G4double center_target_Ge76 = z_flange_target_Ge76 + l_target_Ge76 * 0.5;
  G4double center_ring_Ge76   = z_flange_ring_Ge76   + l_ring_Ge76   * 0.5;
  G4double center_mylar_Ge76  = z_flange_mylar_Ge76  + l_mylar_Ge76  * 0.5;
  //-----------------------------------------------------------------------------------------------------------
  //Starting the construction of the geometry:
  //Ge76-target. Material = Ge76_mat.
  G4Tubs *target_Ge76 = new G4Tubs("target-Ge76", 
                                               0,
                                   r_target_Ge76,  
                               l_target_Ge76 / 2,
                                      0.   * deg,
                                      360. * deg);

  G4LogicalVolume *logic_target_Ge76 = new G4LogicalVolume(target_Ge76, 
                                                              Ge76_mat, 
                                                  "logical_target_Ge76");

  new G4PVPlacement(                                       0,
                    G4ThreeVector(0., 0., center_target_Ge76), 
                                            logic_target_Ge76,
                                           "Ge76_target_phys",
                                                  logicWorld,
                                                       false,
                                                           0,
                                                        true);

  //Ge76-ring. Material = aluminum.
  G4Tubs *ring_Ge76 = new G4Tubs("ring-Ge76", 
                            r_ring_min_Ge76,
                            r_ring_max_Ge76,  
                            l_ring_Ge76 / 2,
                                 0.   * deg,
                                 360. * deg);

  G4LogicalVolume *logic_ring_Ge76 = new G4LogicalVolume(ring_Ge76, 
                                                          aluminum, 
                                                "logical_ring_Ge76");

  new G4PVPlacement(                                      0,
                    G4ThreeVector(0., 0., center_ring_Ge76), 
                                            logic_ring_Ge76,
                                           "Ge76_ring_phys",
                                                 logicWorld,
                                                      false,
                                                          0,
                                                        true);


  //Ge76-mylar.
  G4Tubs *mylar_Ge76 = new G4Tubs( "mylar-Ge76", 
                               r_mylar_min_Ge76,
                               r_mylar_max_Ge76,  
                               l_mylar_Ge76 / 2,
                                     0.   * deg,
                                     360. * deg);

  G4LogicalVolume *logic_mylar_Ge76 = new G4LogicalVolume(mylar_Ge76, 
                                                          mylar_mat, 
                                                 "logical_mylar_Ge76");

  new G4PVPlacement(                                      0,
                    G4ThreeVector(0., 0., center_mylar_Ge76), 
                                            logic_mylar_Ge76,
                                           "Ge76_mylar_phys",
                                                  logicWorld,
                                                       false,
                                                           0,
                                                        true);                                                  


//-----------------------------------------------------------------------------------------------------------
  //FORTH FOIL: Name: 'Al7' 
  //Consists of the 'target_Al7', 'ring_Al7', 'mylar_Al7'. 
  //We need to set (a) the distance between the end of flange and the left corner of every 'subfoil', 
  //(b) the center of every 'subfoil', (c) the depth of each and (d) the radius of each. 
  //-----------------------------------------------------------------------------------------------------------
  //Variables: 
  //Distances between the end of flange and the left corner of every 'subfoil':
  G4double d_flange_target_Al7 = 3.35 * cm;
  G4double d_flange_ring_Al7   = 3.40 * cm;
  G4double d_flange_mylar_Al7  = 3.40 * cm;
  //Depths for every 'subfoil':
  G4double l_target_Al7 = 0.05   * cm;
  G4double l_ring_Al7   = 0.14   * cm;
  G4double l_mylar_Al7  = 0.14   * cm;
  //Radiuses:
  G4double r_target_Al7    = 1.000 * cm;
  G4double r_ring_min_Al7  = 2.431 * cm;
  G4double r_ring_max_Al7  = 2.983 * cm;
  G4double r_mylar_Al7     = 2.431 * cm;
  //z-axis position of the left corners of the 'subfoils':
  G4double z_flange_target_Al7 = endOfFlange + d_flange_target_Al7;
  G4double z_flange_ring_Al7   = endOfFlange + d_flange_ring_Al7;
  G4double z_flange_mylar_Al7  = endOfFlange + d_flange_mylar_Al7;
  //z-axis positions in the centers of the 'subfoils':
  G4double center_target_Al7 = z_flange_target_Al7 + l_target_Al7 * 0.5;
  G4double center_ring_Al7   = z_flange_ring_Al7   + l_ring_Al7   * 0.5;
  G4double center_mylar_Al7  = z_flange_mylar_Al7  + l_mylar_Al7  * 0.5;
  //-----------------------------------------------------------------------------------------------------------
  //Starting the construction of the geometry:
  //Al7-target. Material = aluminum.
  G4Tubs *target_Al7 = new G4Tubs("target-Al7", 
                                            0,
                                 r_target_Al7,  
                             l_target_Al7 / 2,
                                   0.   * deg,
                                   360. * deg);

  G4LogicalVolume *logic_target_Al7 = new G4LogicalVolume(target_Al7, 
                                                            aluminum, 
                                                 "logical_target_Al7");

  new G4PVPlacement(                                       0,
                    G4ThreeVector(0., 0., center_target_Al7), 
                                            logic_target_Al7,
                                           "Al7_target_phys",
                                                  logicWorld,
                                                       false,
                                                           0,
                                                        true);

  //Al7-ring. Material = iron.
  G4Tubs *ring_Al7 = new G4Tubs("ring-Al7", 
                            r_ring_min_Al7,
                            r_ring_max_Al7,  
                            l_ring_Al7 / 2,
                                0.   * deg,
                                360. * deg);

  G4LogicalVolume *logic_ring_Al7 = new G4LogicalVolume(ring_Al7, 
                                                            iron, 
                                               "logical_ring_Al7");

  new G4PVPlacement(                                     0,
                    G4ThreeVector(0., 0., center_ring_Al7), 
                                            logic_ring_Al7,
                                           "Al7_ring_phys",
                                                logicWorld,
                                                     false,
                                                         0,
                                                       true);


  //Al7-mylar.
  G4Tubs *mylar_Al7 = new G4Tubs( "mylar-Al7", 
                                            0,
                                  r_mylar_Al7,  
                              l_mylar_Al7 / 2,
                                   0.   * deg,
                                   360. * deg);

  G4LogicalVolume *logic_mylar_Al7 = new G4LogicalVolume(mylar_Al7, 
                                                          mylar_mat, 
                                                 "logical_mylar_Al7");

  new G4PVPlacement(                                      0,
                    G4ThreeVector(0., 0., center_mylar_Al7), 
                                            logic_mylar_Al7,
                                           "Al7_mylar_phys",
                                                 logicWorld,
                                                      false,
                                                          0,
                                                       true);
//----------------------------------------------------------------------------------------------------------------
//End of the geometry.
//----------------------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------------
    //Connection to other classes:
    //First part (flange):
    fScoringVolume = logicDetector;
    fMolybdenum    = logicMoly;
    fTiT           = logicTit;
    fCopper        = logicCop;
    //-----------------------------------------------------
    //Second part (5 extra foils):
    fAuX           = logic_target_AuX;  //1st foil.
    fAl8           = logic_target_Al8;  //1st foil. 
    fGe73          = logic_target_Ge73; //2nd foil.
    fGe76          = logic_target_Ge76; //3rd foil. 
    fAl7           = logic_target_Al7;  //4th foil.          

    //------------------------------------------------------
    //Always return the physical world: 
    return physWorld;
}

void B1DetectorConstruction::ConstructSDandField()
{

// biasing tries
// -- Fetch volume for biasing:
  G4LogicalVolume* logicTest1 = G4LogicalVolumeStore::GetInstance()->GetVolume("moly_logic");
  //G4LogicalVolume* logicTest2 = G4LogicalVolumeStore::GetInstance()->GetVolume("Tit_logic"); //
  //G4LogicalVolume* logicTest3 = G4LogicalVolumeStore::GetInstance()->GetVolume("copper_logic");


// ----------------------------------------------
//Operator creation and attachment to volume:
  B1OptrMultiParticleChangeCrossSection* testMany = new B1OptrMultiParticleChangeCrossSection(); //
  
  //Particle which is about to be biased:
  testMany->AddParticle("deuteron"); //
  
  //Attach the foils for biasing:
  testMany->AttachTo(logicTest1);
  //testMany->AttachTo(logicTest2); // 
  //testMany->AttachTo(logicTest3);

  //Print progress:
  //G4cout << " Attaching biasing operator " << testMany->GetName()
        // << " to logical volume " << logicTest1->GetName() << " / " << logicTest2->GetName() << " / " << logicTest3->GetName()
        // << G4endl;


}