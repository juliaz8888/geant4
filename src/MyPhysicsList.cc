#include "MyPhysicsList.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4hImpactIonisation.hh"
#include "G4EmDNAPhysics.hh"
#include "G4EmParameters.hh"

#include "G4BuilderType.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4PhysicsListHelper.hh"

// gamma
#include "G4PhotoElectricEffect.hh"
#include "G4PenelopePhotoElectricModel.hh"

#include "G4ComptonScattering.hh"
#include "G4PenelopeComptonModel.hh"

#include "G4GammaConversion.hh"
#include "G4PenelopeGammaConversionModel.hh"

#include "G4RayleighScattering.hh"
#include "G4PenelopeRayleighModel.hh"

// e-

#include "G4eIonisation.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4eBremsstrahlung.hh"
#include "G4PenelopeBremsstrahlungModel.hh"

// e+
#include "G4eplusAnnihilation.hh"
#include "G4PenelopeAnnihilationModel.hh"

// mu
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

// hadrons, ions
#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"

// deexcitation
#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4SystemOfUnits.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyPhysicsList::MyPhysicsList()
: G4VModularPhysicsList(){
  // EM physics
  RegisterPhysics(new G4EmPenelopePhysics());	
  RegisterPhysics(new G4EmStandardPhysics_option3());
  }

MyPhysicsList::~MyPhysicsList()
{
}



void MyPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}


