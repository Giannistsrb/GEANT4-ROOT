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

B1DetectorConstruction::B1DetectorConstruction() : G4VUserDetectorConstruction() { 
   DefineMaterials();
   fMessenger = new DetectorMessenger(this);
}

B1DetectorConstruction::~B1DetectorConstruction() {
}

void B1DetectorConstruction::DefineMaterials() {

   //Density Parameters
   G4double density_tritium     = 3.01604928     * g / mole;
   G4double density_deuteron    = 2.013553212745 * g / mole;
   G4double density_TiT         = 3.75  * g / cm3;
   G4double density_mylar       = 1.40  * g / cm3; 
   G4double density_Ge76        = 3.04  * g / cm3; 
   G4double density_Ge_nat      = 4.83  * g / cm3; 
   G4double density_PVC         = 1.40  * g / cm3; 
   G4double density_SolidOxygen = 1.426 * g / cm3;

   // TiT with deuteron implantation

   G4NistManager *mat = G4NistManager::Instance();

   G4Isotope *tritium = new G4Isotope("T", 1, 3, density_tritium);
   G4Element *tritiumEle = new G4Element("Tele", "H3", 1);
   tritiumEle->AddIsotope(tritium, 100. * perCent);

   G4Isotope *deuteron = new G4Isotope("Deuteron_Isotope", 1, 2, density_deuteron);
   G4Element *deuteronEle = new G4Element("Deuteron", "D3", 1);
   deuteronEle->AddIsotope(deuteron, 100. * perCent);

   G4Material *titanium = mat->FindOrBuildMaterial("G4_Ti");

   G4Material *TiT = new G4Material("TiT", density_TiT, 3);
   TiT->AddElement(tritiumEle,  0.468161098011474);
   TiT->AddMaterial(titanium,   0.520277186727906);
   TiT->AddElement(deuteronEle, 0.01156171526062);
    
  //Mylar
  
  G4Material *hydrogen  = mat->FindOrBuildMaterial("G4_H");
  G4Material *carbon    = mat->FindOrBuildMaterial("G4_C");
  G4Material *oxygen = mat->FindOrBuildMaterial("G4_O");
  G4Material *mylar_mat = new G4Material("mylar", density_mylar, 3);
  mylar_mat->AddMaterial(hydrogen, 0.041959);
  mylar_mat->AddMaterial(carbon,   0.625017);
  mylar_mat->AddMaterial(oxygen,   0.333025);

  //Ge76

  G4Isotope *isGe70 = new G4Isotope("isGe-70", 32, 70, 69.92424900  * g / mole);
  G4Isotope *isGe72 = new G4Isotope("isGe-72", 32, 72, 71.92207580  * g / mole);
  G4Isotope *isGe73 = new G4Isotope("isGe-73", 32, 73, 72.92345900  * g / mole);
  G4Isotope *isGe74 = new G4Isotope("isGe-74", 32, 74, 73.92117776  * g / mole);
  G4Isotope *isGe76 = new G4Isotope("isGe-76", 32, 76, 75.92140270  * g / mole);
  G4Element *Ge70El = new G4Element("Ge70_Element", "Ge70", 1);
  G4Element *Ge72El = new G4Element("Ge72_Element", "Ge72", 1);
  G4Element *Ge73El = new G4Element("Ge73_Element", "Ge73", 1);
  G4Element *Ge74El = new G4Element("Ge74_Element", "Ge74", 1);
  G4Element *Ge76El = new G4Element("Ge76_Element", "Ge76", 1);
  G4Material *Ge76_mat = new G4Material("Ge76", density_Ge76, 6);
  Ge70El->AddIsotope(isGe70, 100. * perCent);
  Ge72El->AddIsotope(isGe72, 100. * perCent);
  Ge73El->AddIsotope(isGe73, 100. * perCent);
  Ge74El->AddIsotope(isGe74, 100. * perCent);
  Ge76El->AddIsotope(isGe76, 100. * perCent);
  Ge76_mat->AddElement(Ge70El,  0.000422132532509 * 100. * perCent);
  Ge76_mat->AddElement(Ge72El,  0.000633198798763 * 100. * perCent);
  Ge76_mat->AddElement(Ge73El,  0.000422132532509 * 100. * perCent);
  Ge76_mat->AddElement(Ge74El,  0.079712693222053 * 100. * perCent);
  Ge76_mat->AddElement(Ge76El,  0.622364063761943 * 100. * perCent);
  Ge76_mat->AddMaterial(oxygen, 0.29644577915223  * 100. * perCent);

  //Ge Natural
  G4Material *germanium = mat->FindOrBuildMaterial("G4_Ge");
  G4Material *matGe_nat = new G4Material("Ge_nat", density_Ge_nat, 2);
  matGe_nat->AddMaterial(germanium, 0.6942);
  matGe_nat->AddMaterial(oxygen, 0.3058);

  //PVC
  G4Material *chlorine  = mat->FindOrBuildMaterial("G4_Cl");
  G4Material *PVC_mat = new G4Material("PVC", density_PVC, 3);
  PVC_mat->AddMaterial(chlorine, 0.56726);
  PVC_mat->AddMaterial(hydrogen, 0.04838);
  PVC_mat->AddMaterial(oxygen,   0.38435);

  // Solid Oxygen

  G4Material *solidOxygen = new G4Material("SolidOxygen", density_SolidOxygen, 1);
  solidOxygen->AddMaterial(oxygen, 100. * perCent);

  // New air for deuterons
  // Define elements
  G4double   z, a; 

  G4Element* N = new G4Element("Nitrogen", "N", z = 7., a = 14.01 * g/mole);
  G4Element* O = new G4Element("Oxygen", "O", z = 8., a = 16.00 * g/mole);
  G4Element* Ar = new G4Element("Argon", "Ar", z = 18., a = 39.95 * g/mole);
  G4Element* C = new G4Element("Carbon", "C", z = 6., a = 12.01 * g/mole);

  // Define air as a mixture of elements
  G4double density = 1.290 * mg/cm3; // Density of air at STP
  G4Material* air = new G4Material("Air", density, 4); // Four components

// Add elements by fractional mass
air->AddElement(N, 0.755);  // Nitrogen ~75.5%
air->AddElement(O, 0.232);  // Oxygen ~23.2%
air->AddElement(Ar, 0.012); // Argon ~1.2%
air->AddElement(C, 0.0003); // Carbon ~0.03%

}

// main function for geometry
G4VPhysicalVolume *B1DetectorConstruction::Construct() {
   // Get nist material manager
   // get parameters who are predifined
   G4NistManager *nist = G4NistManager::Instance();

   G4Material *stainSteel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
   G4Material *tantalum = nist->FindOrBuildMaterial("G4_Ta");
   G4Material *aluminum = nist->FindOrBuildMaterial("G4_Al");
   G4Material *vacuum = nist->FindOrBuildMaterial("G4_Galactic");
   G4Material *molybdenum = nist->FindOrBuildMaterial("G4_Mo");
   G4Material *TiT = nist->FindOrBuildMaterial("TiT");
   G4Material *copper = nist->FindOrBuildMaterial("G4_Cu");
   G4Material *titanium = nist->FindOrBuildMaterial("G4_Ti");
   G4Material *carbon = nist->FindOrBuildMaterial("G4_C");
   G4Material *oxygen = nist->FindOrBuildMaterial("SolidOxygen");
   G4Material *mylar  = nist->FindOrBuildMaterial("mylar");
   G4Material *Ge76  = nist->FindOrBuildMaterial("Ge76");
   G4Material *GeNat  = nist->FindOrBuildMaterial("Ge_nat");
   G4Material *iron = nist->FindOrBuildMaterial("G4_Fe");
   G4Material *PVC  = nist->FindOrBuildMaterial("PVC");
   G4Material *gold = nist->FindOrBuildMaterial("G4_Au");
   G4Material * air = nist->FindOrBuildMaterial("Air");

   G4bool checkOverlaps = true;

   //
   // Geometry Parameters
   //
   G4double BeamLineLength = 140 * cm;
   G4double BeamLineExternalRadius = 2.71 * cm;
   G4double BeamLineThickness = 3.57 * mm;
   G4double CollimatorToLineEndDistance = 68.83 * cm;
   G4double CollimatorHole = 1.68 * mm;
   G4double CollimatorThickness = 400 * um;
   G4double CollimatorRadius = 2.087 * cm;
   G4double CollimatorBaseInnerRadius = 8.92 * mm;
   G4double CollimatorOxygenRadius = 2.087 * cm;
   G4double CollimatorCarbonRadius = 2.087 * cm; 
   G4double CollimatorOxygenInnerRadius = 0.168 * cm;
   G4double CollimatorCarbonInnerRadius = 0.168 * cm;
   G4double CollimatorOxygenThickness = 6. * um; 
   G4double CollimatorCarbonThickness = 4. * um;
   G4double CollimatorBaseLength = 9.83 * mm;
   G4double CollimatorBaseMidSectionLength = 3.97 * mm;
   G4double CollimatorBaseMidSectionRadius = 1.379 * cm;
   G4double CollimatorBaseEndSectionLength = 2.68 * mm;
   G4double AntiscattererToLineEndDistance = 28.3385 * cm;
   G4double AntiscattererHole = 2.05 * mm;
   G4double AntiscattererRadius = 1.405 * cm;
   G4double AntiscattererThickness = 510 * um;
   G4double AntiscattererOxygenThickness = 2. * um;
   G4double AntiscattererCarbonThickness = 1. * um;
   G4double AntiscattererOxygenRadius = 1.405 * cm; 
   G4double AntiscattererCarbonRadius = 1.405 * cm; 
   G4double AntiscattererOxygenInnerRadius = 0.205 * cm;
   G4double AntiscattererCarbonInnerRadius = 0.205 * cm;
   G4double AntiscattererBaseInnerRadius = 4.49 * mm;
   G4double AntiscattererBaseLength = 2.014 * cm;
   G4double AntiscattererBaseMidSectionLength = 9.56 * mm;
   G4double AntiscattererBaseMidSectionRadius = 1.332 * cm;
   G4double AntiscattererBaseEndSectionLength = 4.92 * mm;
   G4double VaneLength = 17.8 * cm;
   G4double VaneThickness = 1.2 * cm;
   G4double VaneExternalRadius = 9. * cm;
   G4double FlangeLength = .7 * cm;
   G4double FlangeExternalRadius = 5.7 * cm;
   G4double FlangeInternalRadius = 1.425 * cm;
   G4double FlangeEndThickness = 2 * mm;
   G4double endOfFlange    = 18.5 * cm;
   G4double OxygenThickness = 6. *um;
   G4double CarbonThickness = 4. * um;
   G4double MolybdenumThickness = 10 * um;
   G4double MolybdenumRadius = 1.425 * cm;
   G4double TiTThickness = 5.7 * um;
   G4double TiTRadius = 1.27 * cm;
   G4double CuThickness = 1. * mm;
   G4double CuRadius = 1.425 * cm;
   G4double DetectorRadius = 2. * cm; 
   G4double DetectorThickness = 0.0705 * cm;

   //Holder:
   G4double r_out = 2.983 * cm;
   G4double b_bottom  = 7.000 * cm;   
   G4double h_bottom  = 0.500 * cm;   
   G4double b_left    = 0.515 * cm;   
   G4double h_left    = 4.500 * cm;   
   G4double b_right   = 0.515 * cm;   
   G4double h_right   = 4.500 * cm; 
   G4double l_bottom = 4.0 * cm;
   G4double d_flange_holder_bottom = 2.3 * cm; 
   G4double l_right = 3.7 * cm;
   G4double d_flange_holder_right = 2.3 * cm; 
   G4double l_left = 3.7 * cm;
   G4double d_flange_holder_left = 2.3 * cm;

   //Holder Foils:
   G4double d_flange_target_Al7 = 2.59 * cm;
   G4double d_flange_ring_Al7   = 2.50 * cm;
   G4double d_flange_mylar_Al7  = 2.64 * cm;
   G4double l_target_Al7 = 0.0500   * cm;
   G4double l_ring_Al7   = 0.1400   * cm;
   G4double l_mylar_Al7  = 0.0006 * cm;
   G4double r_target_Al7    = 1.000 * cm;
   G4double r_ring_min_Al7  = 2.431 * cm;
   G4double r_ring_max_Al7  = 2.983 * cm;
   G4double r_mylar_Al7     = 2.983 * cm;
   G4double d_flange_target_Ge76 = 2.7000 * cm;
   G4double d_flange_ring_Ge76   = 2.7000 * cm;
   G4double d_flange_mylar_Ge76  = 2.6994 * cm;
   G4double l_target_Ge76 = 0.2380 * cm;
   G4double l_ring_Ge76   = 0.1400 * cm;
   G4double l_mylar_Ge76  = 0.0006 * cm;
   G4double r_target_Ge76    = 1.000 * cm;
   G4double r_ring_min_Ge76  = 2.431 * cm;
   G4double r_ring_max_Ge76  = 2.983 * cm;
   G4double r_mylar_Ge76     = 2.983 * cm;
   G4double d_flange_target_Ge_nat = 3.115 * cm;
   G4double d_flange_ring_Ge_nat   = 3.100 * cm;
   G4double d_flange_mylar_Ge_nat  = 3.240 * cm;
   G4double l_target_Ge_nat = 0.1250  * cm;
   G4double l_ring_Ge_nat   = 0.1400  * cm;
   G4double l_mylar_Ge_nat  = 0.0006  * cm;
   G4double r_target_Ge_nat    = 1.000 * cm;
   G4double r_ring_min_Ge_nat  = 2.431 * cm;
   G4double r_ring_max_Ge_nat  = 2.983 * cm;
   G4double r_mylar_Ge_nat     = 2.983 * cm;
   G4double d_flange_target_Al8 = 3.39 * cm;
   G4double d_flange_ring_Al8   = 3.30 * cm;
   G4double d_flange_mylar_Al8  = 3.44 * cm;
   G4double l_target_Al8 = 0.0500 * cm;
   G4double l_ring_Al8   = 0.1400 * cm;
   G4double l_mylar_Al8  = 0.0006 * cm;
   G4double r_target_Al8    = 1.000 * cm;
   G4double r_ring_min_Al8  = 2.431 * cm;
   G4double r_ring_max_Al8  = 2.983 * cm;
   G4double r_mylar_Al8     = 2.983 * cm;
   G4double d_flange_target_Au_light = 3.70 * cm;
   G4double d_flange_ring_Au_light   = 3.70 * cm;
   G4double d_flange_mylar_Au_light  = 0 * cm;
   G4double l_target_Au_light = 0.005 * cm;
   G4double l_ring_Au_light   = 0.140 * cm;
   G4double r_target_Au_light    = 1.100 * cm;
   G4double r_ring_min_Au_light  = 2.431 * cm;
   G4double r_ring_max_Au_light  = 2.983 * cm;
   G4double r_mylar_Au_light     = 0 * cm;

   //
   // Geometry Parameters Calculations
   //
   
   G4double worldHalfZ = 150. *cm;
   G4double WorldR = 20. *cm;

   G4double posLineZ = -worldHalfZ + (BeamLineLength / 2.);
   G4double BeamLineInternalRadius = BeamLineExternalRadius - BeamLineThickness;

   G4double posColZ = (BeamLineLength / 2.) - CollimatorToLineEndDistance;
   G4double posColBaseZ = posColZ - (CollimatorThickness / 2.);
   G4double posCarbonColZ = posColBaseZ - (CollimatorCarbonThickness + CollimatorThickness) / 2.;
   G4double posOxygenColZ = posCarbonColZ- (CollimatorCarbonThickness + CollimatorOxygenThickness)/ 2.;

   G4double posAntiZ = (BeamLineLength / 2.) - AntiscattererToLineEndDistance;
   G4double posAntiBaseZ = posAntiZ - (AntiscattererThickness / 2.);
   G4double posCarbonAntZ = posAntiBaseZ - (AntiscattererThickness + AntiscattererOxygenThickness) / 2.;
   G4double posOxygenAntZ = posCarbonAntZ - (AntiscattererOxygenThickness + AntiscattererCarbonThickness) / 2;

   G4double posVaneZ = posLineZ + (BeamLineLength / 2.);

   G4double posFlangeZ = posVaneZ + VaneLength;
   G4double posFlangeVacuumZ = posFlangeZ + ((FlangeLength - FlangeEndThickness) / 2.);
   G4double posCuZ = (FlangeLength - FlangeEndThickness - CuThickness) / 2.;
   G4double posTiTZ = posCuZ - ((TiTThickness + CuThickness) / 2.);
   G4double posMoZ = posTiTZ - ((TiTThickness + MolybdenumThickness) / 2.);
   G4double posCarbonZ = posMoZ - ((CarbonThickness + MolybdenumThickness) / 2.);
   G4double posOxygenZ = posCarbonZ - ((CarbonThickness + OxygenThickness) / 2.);

   //Holder
   G4double center_bottom_x = 0;   
   G4double center_bottom_y = -(r_out + h_bottom / 2);   
   G4double center_bottom_z = endOfFlange + d_flange_holder_bottom + l_bottom * 0.5;  
   
   G4double center_right_x =   r_out + b_right / 2;  
   G4double center_right_y = -(r_out - h_right / 2);  
   G4double center_right_z = endOfFlange + d_flange_holder_right + l_right * 0.5;  

   G4double center_left_x =  -(r_out + b_left / 2);   
   G4double center_left_y =  -(r_out - h_left / 2);  
   G4double center_left_z = endOfFlange + d_flange_holder_left + l_left * 0.5; 

   G4double posDet = endOfFlange + 39. * cm;
   //G4double posDet = (posMoZ + posCarbonZ) / 2.;

   //Holder Foils
   G4double z_flange_target_Ge76 = endOfFlange + d_flange_target_Ge76;
   G4double z_flange_ring_Ge76   = endOfFlange + d_flange_ring_Ge76;
   G4double z_flange_mylar_Ge76  = endOfFlange + d_flange_mylar_Ge76;
   G4double z_flange_target_Ge_nat = endOfFlange + d_flange_target_Ge_nat;
   G4double z_flange_ring_Ge_nat   = endOfFlange + d_flange_ring_Ge_nat;
   G4double z_flange_mylar_Ge_nat = endOfFlange + d_flange_mylar_Ge_nat;
   G4double z_flange_target_Al8 = endOfFlange + d_flange_target_Al8;
   G4double z_flange_ring_Al8   = endOfFlange + d_flange_ring_Al8;
   G4double z_flange_mylar_Al8  = endOfFlange + d_flange_mylar_Al8;
   G4double z_flange_target_Au_light = endOfFlange + d_flange_target_Au_light;
   G4double z_flange_ring_Au_light   = endOfFlange + d_flange_ring_Au_light;
   G4double z_flange_mylar_Au_light  = endOfFlange + d_flange_mylar_Au_light;
   G4double z_flange_target_Al7 = endOfFlange + d_flange_target_Al7;
   G4double z_flange_ring_Al7   = endOfFlange + d_flange_ring_Al7;
   G4double z_flange_mylar_Al7  = endOfFlange + d_flange_mylar_Al7;
   G4double center_target_Al7 = z_flange_target_Al7 + l_target_Al7 * 0.5;
   G4double center_ring_Al7   = z_flange_ring_Al7   + l_ring_Al7   * 0.5;
   G4double center_mylar_Al7  = z_flange_mylar_Al7  + l_mylar_Al7  * 0.5;
   G4double center_target_Ge76 = z_flange_target_Ge76 + l_target_Ge76 * 0.5;
   G4double center_ring_Ge76   = z_flange_ring_Ge76   + l_ring_Ge76   * 0.5;
   G4double center_mylar_Ge76  = z_flange_mylar_Ge76  + l_mylar_Ge76  * 0.5;
   G4double center_target_Ge_nat = z_flange_target_Ge_nat +  l_target_Ge_nat * 0.5;
   G4double center_ring_Ge_nat = z_flange_ring_Ge_nat     +  l_ring_Ge_nat   * 0.5;
   G4double center_mylar_Ge_nat  = z_flange_mylar_Ge_nat  +  l_mylar_Ge_nat  * 0.5;
   G4double center_target_Al8 = z_flange_target_Al8 + l_target_Al8 * 0.5;
   G4double center_ring_Al8   = z_flange_ring_Al8   + l_ring_Al8   * 0.5;
   G4double center_mylar_Al8  = z_flange_mylar_Al8  + l_mylar_Al8  * 0.5;
   G4double center_target_Au_light = z_flange_target_Au_light +  l_target_Au_light * 0.5;
   G4double center_ring_Au_light   = z_flange_ring_Au_light   +  l_ring_Au_light   * 0.5;
   G4double center_mylar_Au_light  = z_flange_mylar_Au_light;
   
   //
   // World
   //
  // G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");

   G4Tubs *solidWorld = new G4Tubs("World", 0., WorldR, worldHalfZ, 0 * deg, 360 * deg);
   G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
   G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "World", 0, false, 0, checkOverlaps);

   //
   // Line
   //
   G4ThreeVector posLine = G4ThreeVector(0., 0., posLineZ);

   G4Tubs *lineSolid = new G4Tubs("line_solid", BeamLineInternalRadius, BeamLineExternalRadius, BeamLineLength / 2., 0 * deg, 360 * deg);
   G4LogicalVolume *logicLine = new G4LogicalVolume(lineSolid, stainSteel, "line_log");
   new G4PVPlacement(0, posLine, logicLine, "line", logicWorld, false, 0, checkOverlaps);

   //
   //  LineVacuum
   //
   G4Tubs *vacuumLineSolid = new G4Tubs("vacuumLineSolid", 0., BeamLineInternalRadius, BeamLineLength / 2., 0 * deg, 360 * deg);
   G4LogicalVolume *vacuumLineLogic = new G4LogicalVolume(vacuumLineSolid, vacuum, "vacuumLine_logic");
   new G4PVPlacement(0, posLine, vacuumLineLogic, "vaccumLine", logicWorld, false, 0, checkOverlaps);

   //
   // Collimator
   //
   G4ThreeVector posColl = G4ThreeVector(0., 0., posColZ);

   G4Tubs *solidColl = new G4Tubs("collimator_solid", CollimatorHole, CollimatorRadius, CollimatorThickness / 2., 0. * deg, 360. * deg);
   G4LogicalVolume *logicColl = new G4LogicalVolume(solidColl, tantalum, "collimator_logic");
   new G4PVPlacement(0, posColl, logicColl, "coll_phys", vacuumLineLogic, false, 0, checkOverlaps);

   //
   //   Collimator's Base
   //
   G4ThreeVector posCollBase = G4ThreeVector(0., 0., posColBaseZ);

   G4double zPosCol[] = {0. * cm, CollimatorThickness, CollimatorThickness,
                         CollimatorBaseLength - CollimatorBaseEndSectionLength - CollimatorBaseMidSectionLength,
                         CollimatorBaseLength - CollimatorBaseEndSectionLength - CollimatorBaseMidSectionLength,
                         CollimatorBaseLength - CollimatorBaseEndSectionLength,
                         CollimatorBaseLength - CollimatorBaseEndSectionLength,
                         CollimatorBaseLength}; // zplane apo aristera pros ta
                                                // deksia
   G4double innerRadiusCol[] = {CollimatorRadius, CollimatorRadius,
                                CollimatorBaseInnerRadius, CollimatorBaseInnerRadius,
                                CollimatorBaseInnerRadius, CollimatorBaseInnerRadius,
                                CollimatorBaseInnerRadius, CollimatorBaseInnerRadius}; // inerRadius
   G4double outerRadiusCol[] = {BeamLineInternalRadius, BeamLineInternalRadius,
                                BeamLineInternalRadius, BeamLineInternalRadius,
                                CollimatorBaseMidSectionRadius, CollimatorBaseMidSectionRadius,
                                BeamLineInternalRadius, BeamLineInternalRadius};

   G4Polycone *collBaseSolid = new G4Polycone("collimatorBase_Solid", // name
                                              0. * deg,               // phiStart
                                              360. * deg,             // phiTotal
                                              8,                      // num of Z planes
                                              zPosCol,                // positions of z planes
                                              innerRadiusCol,         // Inner radius
                                              outerRadiusCol);        // outside radius
   G4LogicalVolume *logicCollBase = new G4LogicalVolume(collBaseSolid, stainSteel, "collimatorBase_log");
   new G4PVPlacement(0, posCollBase, logicCollBase, "collBase_phys", vacuumLineLogic, false, 0, checkOverlaps);

   //
   //Oxygen collimator:
   //

  G4ThreeVector posOxygenCollZ = G4ThreeVector(0., 0., posOxygenColZ);
  G4Tubs *solidOxygenColl = new G4Tubs("oxygenColl_solid",
                                       CollimatorOxygenInnerRadius,
                                       CollimatorOxygenRadius, 
                                       CollimatorOxygenThickness / 2., 
                                       0. * deg,
                                       360. * deg);

  fOxygenColl = new G4LogicalVolume(solidOxygenColl, oxygen, "oxygenColl_logic");
  new G4PVPlacement(0, posOxygenCollZ, fOxygenColl, "OxygenColl_phys", vacuumLineLogic, false, 0, checkOverlaps);

   
   //
  //Carbon collimator:
  //
  
  G4ThreeVector posCarbonCollZ = G4ThreeVector(0., 0., posCarbonColZ);
  G4Tubs *solidCarbonColl = new G4Tubs("carbonColl_solid",
                                       CollimatorCarbonInnerRadius,
                                       CollimatorCarbonRadius, 
                                       CollimatorCarbonThickness / 2., 
                                       0. * deg,
                                       360. * deg);

  fCarbonColl = new G4LogicalVolume(solidCarbonColl, carbon, "carbonColl_logic");
  new G4PVPlacement(0, posCarbonCollZ, fCarbonColl, "CarbonColl_phys", vacuumLineLogic, false, 0, checkOverlaps);

   //
   // Antiscatterer
   //
   G4ThreeVector posAnti = G4ThreeVector(0., 0., posAntiZ);

   G4Tubs *solidAnti = new G4Tubs("anti_solid", AntiscattererHole, AntiscattererRadius, AntiscattererThickness / 2., 0. * deg, 360. * deg);
   G4LogicalVolume *logicAnti = new G4LogicalVolume(solidAnti, tantalum, "anti_logic");
   new G4PVPlacement(0, posAnti, logicAnti, "anti_phys", vacuumLineLogic, false, 0, checkOverlaps);

   //
   // Antiscatterer's Base
   //
   G4ThreeVector posAntiBase = G4ThreeVector(0., 0., posAntiBaseZ);

   G4double zPosAnti[] = {0. * cm, AntiscattererThickness, AntiscattererThickness,
                          AntiscattererBaseLength - AntiscattererBaseEndSectionLength - AntiscattererBaseMidSectionLength,
                          AntiscattererBaseLength - AntiscattererBaseEndSectionLength - AntiscattererBaseMidSectionLength,
                          AntiscattererBaseLength - AntiscattererBaseEndSectionLength,
                          AntiscattererBaseLength - AntiscattererBaseEndSectionLength,
                          AntiscattererBaseLength}; 
   G4double innerRadiusAnti[] = {AntiscattererRadius, AntiscattererRadius,
                                 AntiscattererBaseInnerRadius, AntiscattererBaseInnerRadius,
                                 AntiscattererBaseInnerRadius, AntiscattererBaseInnerRadius,
                                 AntiscattererBaseInnerRadius, AntiscattererBaseInnerRadius}; 
   G4double outerRadiusAnti[] = {BeamLineInternalRadius,
                                 BeamLineInternalRadius,
                                 BeamLineInternalRadius,
                                 BeamLineInternalRadius,
                                 AntiscattererBaseMidSectionRadius,
                                 AntiscattererBaseMidSectionRadius,
                                 BeamLineInternalRadius,
                                 BeamLineInternalRadius};

   G4Polycone *antiBaseSolid = new G4Polycone("antiBase_Solid", // name
                                              0. * deg,         // phiStart
                                              360. * deg,       // phiTotal
                                              8,                // num of Z planes
                                              zPosAnti,         // positions of z planes
                                              innerRadiusAnti,  // Inner radius
                                              outerRadiusAnti); // outside radius
   G4LogicalVolume *logicAntiBase = new G4LogicalVolume(antiBaseSolid, aluminum, "antiBase_log");
   new G4PVPlacement(0, posAntiBase, logicAntiBase, "antiBase_phys", vacuumLineLogic, false, 0, checkOverlaps);

   //
   //Oxygen antiscatterer:
   //

  G4ThreeVector posOxygenAntiZ = G4ThreeVector(0., 0., posOxygenAntZ);
  G4Tubs *solidOxygenAnti = new G4Tubs("oxygenAnti_solid",
                                       AntiscattererOxygenInnerRadius,
                                       AntiscattererOxygenRadius, 
                                       AntiscattererOxygenThickness / 2., 
                                       0. * deg,
                                       360. * deg);

  fOxygenAnt = new G4LogicalVolume(solidOxygenAnti, oxygen, "oxygenAnti_logic");
  new G4PVPlacement(0, posOxygenAntiZ, fOxygenAnt, "OxygenAnti_phys", vacuumLineLogic, false, 0, checkOverlaps);
   
   //
  //Carbon antiscatterer:
  //
  
  G4ThreeVector posCarbonAntiZ = G4ThreeVector(0., 0., posCarbonAntZ);
  G4Tubs *solidCarbonAnti = new G4Tubs("carbonAnti_solid",
                                       AntiscattererCarbonInnerRadius,
                                       AntiscattererCarbonRadius, 
                                       AntiscattererCarbonThickness / 2., 
                                       0. * deg,
                                       360. * deg);

  fCarbonAnt = new G4LogicalVolume(solidCarbonAnti, carbon, "carbonAnti_logic");
  new G4PVPlacement(0, posCarbonAntiZ, fCarbonAnt, "CarbonAnti_phys", vacuumLineLogic, false, 0, checkOverlaps);

   //
   // Vane
   //
   G4ThreeVector posVane = G4ThreeVector(0., 0., posVaneZ);

   G4double zPosVane[] = {0. * cm, VaneThickness, VaneThickness,
                          VaneLength - VaneThickness,
                          VaneLength - VaneThickness,
                          VaneLength};
   G4double inRadVane[] = {BeamLineInternalRadius,
                           BeamLineInternalRadius,
                           VaneExternalRadius - VaneThickness,
                           VaneExternalRadius - VaneThickness,
                           BeamLineInternalRadius,
                           BeamLineInternalRadius};
   G4double outRadVane[] = {VaneExternalRadius, VaneExternalRadius,
                            VaneExternalRadius, VaneExternalRadius,
                            VaneExternalRadius, VaneExternalRadius};

   G4Polycone *solidVane = new G4Polycone("vane", 0. * deg, 360. * deg, 6, zPosVane, inRadVane, outRadVane);
   G4LogicalVolume *logicVane =  new G4LogicalVolume(solidVane, aluminum, "vane_logic");
   new G4PVPlacement(0, posVane, logicVane, "vane_phys", logicWorld, false, 0, checkOverlaps);

   //
   // Vane Vacuum
   //
   G4double zPosVaneVacuum[] = {0. * cm, VaneThickness, VaneThickness,
                                VaneLength - VaneThickness,
                                VaneLength - VaneThickness,
                                VaneLength};
   G4double inRadVaneVacuum[] = {0., 0., 0., 0., 0., 0.};
   G4double outRadVaneVacuum[] = {BeamLineInternalRadius,
                                  BeamLineInternalRadius,
                                  VaneExternalRadius - VaneThickness,
                                  VaneExternalRadius - VaneThickness,
                                  BeamLineInternalRadius,
                                  BeamLineInternalRadius};

   G4Polycone *solidVaneVacuum = new G4Polycone("vaneVacuum", 0. * deg, 360. * deg, 6, zPosVaneVacuum, inRadVaneVacuum, outRadVaneVacuum);
   G4LogicalVolume *logicVaneVacuum = new G4LogicalVolume(solidVaneVacuum, vacuum, "vaneVacuum_logic");
   new G4PVPlacement(0, posVane, logicVaneVacuum, "vaneVacuum_phys", logicWorld, false, 0, checkOverlaps);

   //
   // Flange
   //
   G4ThreeVector posFlange = G4ThreeVector(0., 0., posFlangeZ);

   G4double zPosFlange[] = {0. * cm, FlangeLength - FlangeEndThickness,
                            FlangeLength - FlangeEndThickness, FlangeLength};
   G4double inRadFlange[] = {FlangeInternalRadius, FlangeInternalRadius, 0., 0.};
   G4double outRadFlange[] = {FlangeExternalRadius, FlangeExternalRadius,
                              FlangeExternalRadius, FlangeExternalRadius};

   G4Polycone *solidFlange = new G4Polycone("flange", 0. * deg, 360. * deg, 4, zPosFlange, inRadFlange, outRadFlange);
   fFlange = new G4LogicalVolume(solidFlange, stainSteel, "flange_logic");
   new G4PVPlacement(0, posFlange, fFlange, "flange_phys", logicWorld, false, 0, checkOverlaps);
   

   //
   // Flange vacuum
   //
   G4ThreeVector posVacuumFlange = G4ThreeVector(0., 0., posFlangeVacuumZ);

   G4Tubs *solidVacuumFlange = new G4Tubs("vacummFlange", 0., FlangeInternalRadius, (FlangeLength - FlangeEndThickness) / 2., 0. * deg, 360. * deg);
   G4LogicalVolume *logicVacuumFlange = new G4LogicalVolume(solidVacuumFlange, vacuum, "vacuumFlange_logic");
   new G4PVPlacement(0, posVacuumFlange, logicVacuumFlange, "vacuumFlange_phys", logicWorld, false, 0, checkOverlaps);
   

   //
   // Oxygen
   //
   G4ThreeVector posOxygen = G4ThreeVector(0., 0., posOxygenZ);
   
   G4Tubs *solidOxygen = new G4Tubs("oxygen_solid",0. * cm, FlangeInternalRadius, OxygenThickness / 2., 0. * deg, 360. * deg);
   fOxygen = new G4LogicalVolume(solidOxygen, oxygen, "oxygen_logic");
   new G4PVPlacement(0, posOxygen, fOxygen, "oxygen_phys", logicVacuumFlange, false, 0, checkOverlaps);
   
   //
   // Carbon
   //
   G4ThreeVector posCarbon = G4ThreeVector(0., 0., posCarbonZ);
   
   G4Tubs *solidCarbon = new G4Tubs("carbon_solid",0. * cm, FlangeInternalRadius, CarbonThickness / 2., 0. * deg, 360. * deg);
   fCarbon = new G4LogicalVolume(solidCarbon, carbon, "carbon_logic");
   new G4PVPlacement(0, posCarbon, fCarbon, "carbon_phys", logicVacuumFlange, false, 0, checkOverlaps);

   //
   // Molybdenum
   //
   G4ThreeVector posMoly = G4ThreeVector(0., 0., posMoZ);

   G4Tubs *solidMoly = new G4Tubs("moly_solid", 0. * cm, MolybdenumRadius, MolybdenumThickness / 2., 0. * deg, 360. * deg);
   fMolybdenum = new G4LogicalVolume(solidMoly, molybdenum, "moly_logic");
   new G4PVPlacement(0, posMoly, fMolybdenum, "moly_phys", logicVacuumFlange, false, 0, checkOverlaps);

   //
   // TiT
   //
   G4ThreeVector posTit = G4ThreeVector(0., 0., posTiTZ);

   G4Tubs *solidTit = new G4Tubs("Tit_solid", 0. * cm, TiTRadius, TiTThickness / 2., 0. * deg, 360. * deg);
   fTiT = new G4LogicalVolume(solidTit, TiT, "Tit_logic");
   new G4PVPlacement(0, posTit, fTiT, "Tit_phys", logicVacuumFlange, false, 0, checkOverlaps);
   //
   // Copper
   //
   G4ThreeVector posCopper = G4ThreeVector(0., 0., posCuZ);

   G4Tubs *solidCop = new G4Tubs("cop_solid", 0. * cm, CuRadius, CuThickness / 2., 0. * deg, 360. * deg);
   fCopper = new G4LogicalVolume(solidCop, copper, "copper_logic");
   new G4PVPlacement(0, posCopper, fCopper, "copper_phys", logicVacuumFlange, false, 0, checkOverlaps);
   
   //
   // Holder
   //
   G4ThreeVector pos_bottom_holder = G4ThreeVector(center_bottom_x, center_bottom_y, center_bottom_z);

   G4Box *bottom_holder = new G4Box("target_holder_bottom",b_bottom / 2,h_bottom / 2,l_bottom / 2);
   G4LogicalVolume *logic_bottom_holder = new G4LogicalVolume(bottom_holder,iron,"bottom_holder_logic");
   new G4PVPlacement(0, pos_bottom_holder, logic_bottom_holder,"bottom_holder_phys",logicWorld,false,0,checkOverlaps);
   
   G4ThreeVector pos_right_holder = G4ThreeVector(center_right_x, center_right_y, center_right_z);
   
   G4Box *right_holder = new G4Box("target_holder_right",b_right / 2,h_right / 2,l_right / 2);
   G4LogicalVolume *logic_right_holder = new G4LogicalVolume(right_holder,iron,"right_holder_logic");
   new G4PVPlacement(0, pos_right_holder, logic_right_holder,"right_holder_phys",logicWorld,false,0,checkOverlaps);
   
   G4ThreeVector pos_left_holder = G4ThreeVector(center_left_x, center_left_y, center_left_z);

   G4Box *left_holder = new G4Box("target_holder_left",b_left / 2,h_left / 2,l_left / 2);
   G4LogicalVolume *logic_left_holder = new G4LogicalVolume(left_holder,iron,"left_holder_logic");
   new G4PVPlacement(0,pos_left_holder,logic_left_holder,"left_holder_phys",logicWorld,false,0,checkOverlaps);

   //
   // Al7
   // 
   G4Tubs *target_Al7 = new G4Tubs("target-Al7", 0,r_target_Al7,l_target_Al7 / 2,0.* deg,360. * deg);
   fAl7 = new G4LogicalVolume(target_Al7,aluminum,"logical_target_Al7");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_target_Al7),fAl7,"Al7_target_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *ring_Al7 = new G4Tubs("ring-Al7",r_ring_min_Al7,r_ring_max_Al7,  l_ring_Al7 / 2,0.* deg,360.* deg);
   G4LogicalVolume *logic_ring_Al7 = new G4LogicalVolume(ring_Al7, iron,"logical_ring_Al7");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_ring_Al7), logic_ring_Al7,"Al7_ring_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *mylar_Al7 = new G4Tubs( "mylar-Al7", 0,r_mylar_Al7,  l_mylar_Al7 / 2,0.   * deg, 360. * deg);
   G4LogicalVolume *logic_mylar_Al7 = new G4LogicalVolume(mylar_Al7,mylar,"logical_mylar_Al7");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_mylar_Al7), logic_mylar_Al7,"Al7_mylar_phys",logicWorld,false,0,
                     checkOverlaps);
   
   //
   // Ge76
   //
   G4Tubs *target_Ge76 = new G4Tubs("target-Ge76", 0,r_target_Ge76,  l_target_Ge76 / 2,0. * deg,360. * deg);
   fGe76 = new G4LogicalVolume(target_Ge76,Ge76,"logical_target_Ge76");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_target_Ge76), fGe76,"Ge76_target_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *ring_Ge76 = new G4Tubs("ring-Ge76",r_ring_min_Ge76,r_ring_max_Ge76,  l_ring_Ge76 / 2,0.   * deg,360. * deg);
   G4LogicalVolume *logic_ring_Ge76 = new G4LogicalVolume(ring_Ge76,aluminum, "logical_ring_Ge76");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_ring_Ge76), logic_ring_Ge76,"Ge76_ring_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *mylar_Ge76 = new G4Tubs( "mylar-Ge76", 0,r_mylar_Ge76,  l_mylar_Ge76 / 2,0.   * deg,360. * deg);
   G4LogicalVolume *logic_mylar_Ge76 = new G4LogicalVolume(mylar_Ge76, mylar, "logical_mylar_Ge76");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_mylar_Ge76),logic_mylar_Ge76,"Ge76_mylar_phys",logicWorld,false,0,
                     checkOverlaps);

   //
   // GeNat
   //
   G4Tubs *target_Ge_nat = new G4Tubs("target-Ge_nat",0,r_target_Ge_nat,  l_target_Ge_nat / 2,0.   * deg,360. * deg);
   fGe_nat = new G4LogicalVolume(target_Ge_nat, GeNat, "logical_target_Ge_nat");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_target_Ge_nat), fGe_nat,"Ge_nat_target_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *ring_Ge_nat = new G4Tubs("ring-Ge_nat", r_ring_min_Ge_nat,r_ring_max_Ge_nat,l_ring_Ge_nat / 2,0. * deg,360. * deg);
   G4LogicalVolume *logic_ring_Ge_nat = new G4LogicalVolume(ring_Ge_nat, PVC, "logical_ring_Ge_nat");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_ring_Ge_nat), logic_ring_Ge_nat,"Ge_nat_ring_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *mylar_Ge_nat = new G4Tubs( "mylar-Ge_nat", 0,r_mylar_Ge_nat,  l_mylar_Ge_nat / 2,0.* deg,360. * deg);
   G4LogicalVolume *logic_mylar_Ge_nat = new G4LogicalVolume(mylar_Ge_nat, mylar, "logical_mylar_Ge_nat");
   new G4PVPlacement(0, G4ThreeVector(0., 0., center_mylar_Ge_nat), logic_mylar_Ge_nat,"Ge_nat_mylar_phys",logicWorld,false,0,
                     checkOverlaps);

   //
   // Al8
   //
   G4Tubs *target_Al8 = new G4Tubs("target-Al8", 0,r_target_Al8,  l_target_Al8 / 2,0.   * deg,360. * deg);
   fAl8 = new G4LogicalVolume(target_Al8, aluminum, "logical_target_Al8");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_target_Al8), fAl8,"Al8_target_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *ring_Al8 = new G4Tubs("ring-Al8", r_ring_min_Al8,r_ring_max_Al8,  l_ring_Al8 / 2,0.   * deg,360. * deg);
   G4LogicalVolume *logic_ring_Al8 = new G4LogicalVolume(ring_Al8, iron,  "logical_ring_Al8");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_ring_Al8),logic_ring_Al8,"Al8_ring_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *mylar_Al8 = new G4Tubs( "mylar-Al8", 0,r_mylar_Al8,  l_mylar_Al8 / 2,0.   * deg, 360. * deg);
   G4LogicalVolume *logic_mylar_Al8 = new G4LogicalVolume(mylar_Al8, mylar,"logical_mylar_Al8");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_mylar_Al8),logic_mylar_Al8,"Al8_mylar_phys",logicWorld,false,0,
                     checkOverlaps);


   
   //
   // Au Light
   //
   G4Tubs *target_Au_light = new G4Tubs("target-Au_light", 0,r_target_Au_light,  l_target_Au_light / 2,0.   * deg,360. * deg);
   fAulight = new G4LogicalVolume(target_Au_light, gold, "logical_target_Au_light");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_target_Au_light), fAulight,"Au_light_target_phys",logicWorld,false,0,
                     checkOverlaps);
   G4Tubs *ring_Au_light = new G4Tubs("ring-Au_light", r_ring_min_Au_light,r_ring_max_Au_light,  l_ring_Au_light / 2,0.   * deg,360. * deg);
   G4LogicalVolume *logic_ring_Au_light= new G4LogicalVolume(ring_Au_light,iron,"logical_ring_Au_light");
   new G4PVPlacement(0,G4ThreeVector(0., 0., center_ring_Au_light),logic_ring_Au_light,"Au_light_ring_phys",logicWorld,false,0,
                     checkOverlaps);


   //
   // Scoring Volume
   //
   G4ThreeVector posDetector = G4ThreeVector(0., 0., posDet); 
  
   G4Tubs *solidDetector = new G4Tubs("detector_solid", 0. *cm, DetectorRadius, DetectorThickness, 0. *deg, 360.*deg);
   fScoringVolume = new G4LogicalVolume(solidDetector, vacuum, "detector_logic");
   new G4PVPlacement(0, posDetector, fScoringVolume, "detector_phys",logicWorld, false, 0, checkOverlaps);
  
   SetAttributes();
   
   return physWorld;
}

#include "G4LogicalVolumeStore.hh"
#include "G4VisAttributes.hh"

void B1DetectorConstruction::SetAttributes() {
   G4VisAttributes *InvisibleAtt = new G4VisAttributes(false);
   G4VisAttributes *CarbonAtt = new G4VisAttributes(true, G4Color(0., 1., 0.));
   G4VisAttributes *AlAtt = new G4VisAttributes(true, G4Colour(.8, .8, .8, .5));
   G4VisAttributes *SSAtt = new G4VisAttributes(true, G4Colour(.2, .2, .2, .5));
   G4VisAttributes *TaAtt = new G4VisAttributes(true, G4Colour(0., 0., 1., 1.));
   G4VisAttributes *MoAtt = new G4VisAttributes(true, G4Colour(1., 0., 0., 1.));
   G4VisAttributes *TiTAtt = new G4VisAttributes(true, G4Colour(0., .5, 0., 1.));
   G4VisAttributes *CuAtt = new G4VisAttributes(true, G4Colour(1., .9, 0., 1.));
   G4VisAttributes *FeAtt = new G4VisAttributes(true, G4Colour(1., 0., 0.));
   G4VisAttributes *mylarAtt = new G4VisAttributes(true, G4Colour(0., 1., 1.));
   G4VisAttributes *GeAtt = new G4VisAttributes(true, G4Colour(0., 0., 0.));
   G4VisAttributes *PVCAtt = new G4VisAttributes(true, G4Colour(0.5, 0.5, 0.5));
   G4VisAttributes *AuAtt = new G4VisAttributes(true, G4Colour(1., 1., 0.));
   G4VisAttributes *DetAtt = new G4VisAttributes(true, G4Color(0., 0., 1., 1.));

   G4LogicalVolumeStore *LStore = G4LogicalVolumeStore::GetInstance();
   for (auto itx = LStore->begin(); itx != LStore->end(); ++itx) {
      G4LogicalVolume *lVol = *itx;
      G4String lVolName = lVol->GetName();
      G4String matName = lVol->GetMaterial()->GetName();
      if (matName == "G4_Galactic" || matName == "G4_AIR")
         lVol->SetVisAttributes(InvisibleAtt);
      else if (matName == "G4_C")
         lVol->SetVisAttributes(CarbonAtt);
      else if (matName == "G4_Al")
         lVol->SetVisAttributes(AlAtt);
      else if (matName == "G4_STAINLESS-STEEL")
         lVol->SetVisAttributes(SSAtt);
      else if (matName == "G4_Ta")
         lVol->SetVisAttributes(TaAtt);
      else if (matName == "G4_Mo")
         lVol->SetVisAttributes(MoAtt);
      else if (matName == "TiT")
         lVol->SetVisAttributes(TiTAtt);
      else if (matName == "G4_Cu")
         lVol->SetVisAttributes(CuAtt);
      else if (matName == "G4_Fe")
         lVol->SetVisAttributes(FeAtt);
      else if (matName == "mylar")
         lVol->SetVisAttributes(mylarAtt);
      else if (matName == "Ge76" || matName == "Ge_nat")
         lVol->SetVisAttributes(GeAtt);
      else if (matName == "PVC")
         lVol->SetVisAttributes(PVCAtt);
      else if (matName == "G4_Au")
         lVol->SetVisAttributes(AuAtt);
      else if (lVolName == "detector_logic")
         lVol->SetVisAttributes(DetAtt);
   }
}


void B1DetectorConstruction::ConstructSDandField()
{ 
  biasFoil      = fTiT;
  killFoil      = fCopper; 
  biasingFactor = 1000;
  lastBiasFoil  = fCopper;
  
  B1OptrMultiParticleChangeCrossSection* testMany = new B1OptrMultiParticleChangeCrossSection();
  
    testMany->AddParticle("deuteron"); 
    testMany->AttachTo(biasFoil); 

}

