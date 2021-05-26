#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class MyDetectorMessenger;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    G4VPhysicalVolume* GetCrystalPV() const;
    void SetCrystalMat(G4String& matName);
    const G4int GetNumOfLayers() const;
    G4String fcrystalMatName;

  private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    MyDetectorMessenger*  fMessenger;   // messenger
    const G4int fNumOfLayers = 30;
    const G4double fLayerThickness = 0.001*mm;
    const G4double fLayerRadius = 3.*mm;
    G4LogicalVolume* fLayerLV;
    G4VPhysicalVolume* fCrystalPV;
    G4bool  fCheckOverlaps;

};
