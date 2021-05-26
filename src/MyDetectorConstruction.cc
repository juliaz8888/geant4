#include "MyDetectorConstruction.hh"
#include "MyDetectorMessenger.hh"

#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


MyDetectorConstruction::MyDetectorConstruction():
    G4VUserDetectorConstruction(),
    fCheckOverlaps(true),
    fCrystalPV(nullptr),
    fLayerLV(nullptr)
{
    fMessenger = new MyDetectorMessenger(this);
}

MyDetectorConstruction::~MyDetectorConstruction()
{
    delete fMessenger;
}

void MyDetectorConstruction::DefineMaterials(){
  G4NistManager* man = G4NistManager::Instance();

  G4bool isotopes = false;
  G4Element*  O = man->FindOrBuildElement("O" , isotopes);
  G4Element*  N = man->FindOrBuildElement("N" , isotopes);
  G4Element*  P = man->FindOrBuildElement("P" , isotopes);
  G4Element*  U = man->FindOrBuildElement("U" , isotopes);
  G4Element* Si = man->FindOrBuildElement("Si", isotopes);
  G4Element* Lu = man->FindOrBuildElement("Lu", isotopes);
  G4Element* Pb = man->FindOrBuildElement("Pb", isotopes);
  G4Element* Se = man->FindOrBuildElement("Se", isotopes);
  G4Element* Te = man->FindOrBuildElement("Te", isotopes);
  G4Element* Bi = man->FindOrBuildElement("Bi", isotopes);
  G4Element* In = man->FindOrBuildElement("In", isotopes);
  G4Element* Sb = man->FindOrBuildElement("Sb", isotopes);
  G4Element* Cd = man->FindOrBuildElement("Cd", isotopes);
  G4Element* Ga = man->FindOrBuildElement("Ga", isotopes);
  G4Element* As = man->FindOrBuildElement("As", isotopes);
  G4Element* Ge = man->FindOrBuildElement("Ge", isotopes);

  G4Material* PbSe = new G4Material("PbSe", 9.5*g/cm3, 2);
  PbSe->AddElement(Pb,1);
  PbSe->AddElement(Se,1);

  G4Material* PbTe = new G4Material("PbTe", 9.5*g/cm3, 2);
  PbTe->AddElement(Pb,1);
  PbTe->AddElement(Te,1);

  G4Material* BiTe3 = new G4Material("BiTe3", 7.3*g/cm3, 2);
  BiTe3->AddElement(Bi,1);
  BiTe3->AddElement(Te,3);

  G4Material* InSb = new G4Material("InSb", 5.78*g/cm3, 2);
  InSb->AddElement(In,1);
  InSb->AddElement(Sb,1);

  G4Material* CdSe = new G4Material("CdSe", 5.82*g/cm3, 2);
  CdSe->AddElement(Cd,1);
  CdSe->AddElement(Se,1);

  G4Material* GaP = new G4Material("GaP", 4.14*g/cm3, 2);
  GaP->AddElement(Ga,1);
  GaP->AddElement(P,1);

  G4Material* GaSb = new G4Material("GaSb", 5.614*g/cm3, 2);
  GaSb->AddElement(Ga,1);
  GaSb->AddElement(Sb,1);

  G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3);
  LSO->AddElement(Lu, 2);
  LSO->AddElement(Si, 1);
  LSO->AddElement(O , 5);

  G4Material* BSO = new G4Material("Bi12SiO20", 9.20*g/cm3, 3);
  BSO->AddElement(Bi, 12);
  BSO->AddElement(Si, 1);
  BSO->AddElement(O , 20);

  G4Material* UO2 = new G4Material("UO2", 10.97*g/cm3, 2);
  UO2->AddElement(U, 1);
  UO2->AddElement(O, 2);

  G4Material* BGO = new G4Material("Bi4Ge3O12", 7.12*g/cm3, 3);
  BGO->AddElement(Bi, 4);
  BGO->AddElement(Ge, 3);
  BGO->AddElement(O, 12);

  G4Material* Air = new G4Material("Air", 1.290*mg/cm3, 2);
  Air->AddElement(N, 70.0*perCent);
  Air->AddElement(O, 30.0*perCent);

  man->FindOrBuildMaterial("G4_GALLIUM_ARSENIDE");
  man->FindOrBuildMaterial("G4_CADMIUM_TELLURIDE");



}

G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes(){
    auto worldSizeZ = 1.2 * fNumOfLayers * fLayerThickness;
    auto worldSizeXY = 1.2 * fLayerRadius * 2;

    auto defaultMat = G4Material::GetMaterial("Air");
    auto crystalMat = G4Material::GetMaterial("G4_CADMIUM_TELLURIDE");

    //
    // World
    //
    auto worldS = new G4Box("World",           // its name
                   worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size

    auto worldLV
      = new G4LogicalVolume(
                   worldS,           // its solid
                   defaultMat,  // its material
                   "World");         // its name

    auto worldPV
      = new G4PVPlacement(
                   0,                // no rotation
                   G4ThreeVector(),  // at (0,0,0)
                   worldLV,          // its logical volume
                   "World",          // its name
                   0,                // its mother  volume
                   false,            // no boolean operation
                   0,                // copy number
                   fCheckOverlaps);  // checking overlaps

    auto crystalS = new G4Tubs("Crystal", 0, fLayerRadius, fNumOfLayers * fLayerThickness / 2, 0., twopi);
    auto crystalLV = new G4LogicalVolume(crystalS, defaultMat, "Crystal");
    auto crystalPV =   new G4PVPlacement(
                0,                // no rotation
                G4ThreeVector(),  // at (0,0,0)
                crystalLV,          // its logical volume
                "Crystal",    // its name
                worldLV,          // its mother  volume
                false,            // no boolean operation
                1,                // copy number
                fCheckOverlaps);  // checking overlaps

    auto layerS = new G4Tubs("Layer", 0, fLayerRadius, fLayerThickness / 2, 0., twopi);
    auto layerLV = new G4LogicalVolume(layerS, crystalMat, "Layer");
    auto layerPV = new G4PVReplica(
                "Crystal",          // its name
                layerLV,          // its logical volume
                crystalLV,          // its mother
                kZAxis,           // axis of replication
                fNumOfLayers,        // number of replica
                fLayerThickness);  // witdth of replica

    fLayerLV = layerLV;
    //
    // Visualization attributes
    //
    worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

    auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    simpleBoxVisAtt->SetVisibility(true);
    crystalLV->SetVisAttributes(simpleBoxVisAtt);

    //
    // Always return the physical World
    //
    G4cout << "Using Layer Thickness: " << G4BestUnit(fLayerThickness, "Length") << G4endl;
    return worldPV;
}

G4VPhysicalVolume* MyDetectorConstruction::Construct(){
    DefineMaterials();
    return DefineVolumes();
}

G4VPhysicalVolume* MyDetectorConstruction::GetCrystalPV() const{
    return fCrystalPV;
}

void MyDetectorConstruction::SetCrystalMat(G4String& matName){
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* crystalMat = nistManager->FindOrBuildMaterial(matName);
    if ( ! crystalMat ) {
      G4ExceptionDescription msg;
      msg << "Cannot retrieve material " << matName;
      G4Exception("MyDetectorConstruction::SetCrystalMat()",
        "MyCode0001", FatalException, msg);
    }
    fLayerLV->SetMaterial(crystalMat);
    fcrystalMatName = matName;
}

const G4int MyDetectorConstruction::GetNumOfLayers() const{
    return fNumOfLayers;
}
