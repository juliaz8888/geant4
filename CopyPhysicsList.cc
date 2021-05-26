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

  G4EmParameters* param = G4EmParameters::Instance();
  param->SetDefaults();
//  param->SetMinEnergy(250*eV);
//  param->SetNumberOfBinsPerDecade(10);
//  param->SetAuger(1);
//  param->SetDeexcitationIgnoreCut(1);
//  param->SetFluo(1);
//  param->SetPixe(1);
}

MyPhysicsList::~MyPhysicsList()
{
}

void MyPhysicsList::ConstructParticle()
{

// gamma
  G4Gamma::GammaDefinition();

// leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
    G4GenericIon::GenericIonDefinition();
    G4Alpha::AlphaDefinition();

}

void MyPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}


void MyPhysicsList::ConstructProcess()
{
    AddTransportation();
    G4PhysicsListHelper* list = G4PhysicsListHelper::GetPhysicsListHelper();

  // Add standard EM Processes

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    G4String particleName = particle->GetParticleName();

    //Applicability range for Penelope models
    //for higher energies, the Standard models are used
    G4double highEnergyLimit = 1*GeV;

    if (particleName == "gamma") {
      // gamma

      G4PhotoElectricEffect* phot = new G4PhotoElectricEffect();
      G4PenelopePhotoElectricModel*
      photModel = new G4PenelopePhotoElectricModel();
      photModel->SetHighEnergyLimit(highEnergyLimit);
      phot->AddEmModel(0, photModel);
      list->RegisterProcess(phot, particle);

      G4ComptonScattering* compt = new G4ComptonScattering();
      G4PenelopeComptonModel*
      comptModel = new G4PenelopeComptonModel();
      comptModel->SetHighEnergyLimit(highEnergyLimit);
      compt->AddEmModel(0, comptModel);
      list->RegisterProcess(compt, particle);

      G4GammaConversion* conv = new G4GammaConversion();
      G4PenelopeGammaConversionModel*
      convModel = new G4PenelopeGammaConversionModel();
      convModel->SetHighEnergyLimit(highEnergyLimit);
      conv->AddEmModel(0, convModel);
      list->RegisterProcess(conv, particle);

      G4RayleighScattering* rayl = new G4RayleighScattering();
      G4PenelopeRayleighModel*
      raylModel = new G4PenelopeRayleighModel();
      raylModel->SetHighEnergyLimit(highEnergyLimit);
      rayl->AddEmModel(0, raylModel);
      list->RegisterProcess(rayl, particle);

    } else if (particleName == "e-") {
      //electron

      G4eIonisation* eIoni = new G4eIonisation();
      G4PenelopeIonisationModel*
      eIoniModel = new G4PenelopeIonisationModel();
      eIoniModel->SetHighEnergyLimit(highEnergyLimit);
      eIoni->AddEmModel(0, eIoniModel, new G4UniversalFluctuation() );
      list->RegisterProcess(eIoni, particle);

      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
      G4PenelopeBremsstrahlungModel*
      eBremModel = new G4PenelopeBremsstrahlungModel();
      eBremModel->SetHighEnergyLimit(highEnergyLimit);
      eBrem->AddEmModel(0, eBremModel);
      list->RegisterProcess(eBrem, particle);

    } else if (particleName == "e+") {
      //positron
      G4eIonisation* eIoni = new G4eIonisation();
      G4PenelopeIonisationModel*
      eIoniModel = new G4PenelopeIonisationModel();
      eIoniModel->SetHighEnergyLimit(highEnergyLimit);
      eIoni->AddEmModel(0, eIoniModel, new G4UniversalFluctuation() );
      list->RegisterProcess(eIoni, particle);

      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
      G4PenelopeBremsstrahlungModel*
      eBremModel = new G4PenelopeBremsstrahlungModel();
      eBremModel->SetHighEnergyLimit(highEnergyLimit);
      eBrem->AddEmModel(0, eBremModel);
      list->RegisterProcess(eBrem, particle);

      G4eplusAnnihilation* eAnni = new G4eplusAnnihilation();
      G4PenelopeAnnihilationModel*
      eAnniModel = new G4PenelopeAnnihilationModel();
      eAnniModel->SetHighEnergyLimit(highEnergyLimit);
      eAnni->AddEmModel(0, eAnniModel);
      list->RegisterProcess(eAnni, particle);

    } else if( particleName == "alpha"|| particleName == "GenericIon" ) {
      list->RegisterProcess(new G4ionIonisation, particle);
    }
  }
  // Deexcitation
  //
  G4VAtomDeexcitation* deex = new G4UAtomicDeexcitation();
  G4LossTableManager::Instance()->SetAtomDeexcitation(deex);
}

