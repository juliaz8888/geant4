#include "MyRunAction.hh"
#include "MyAnalysis.hh"
#include "MyDetectorConstruction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <string>
#include <iostream>

MyRunAction::MyRunAction(const MyDetectorConstruction* Det)
 : G4UserRunAction(),
   fNumOfLayers(Det->GetNumOfLayers()),
   fDetConstruction(Det),
   fEdep(nullptr)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyRunAction::~MyRunAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyRunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    fEdep = new std::vector<G4double>[fNumOfLayers];
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyRunAction::EndOfRunAction(const G4Run* /*run*/)
{
// Verbose Mode:
//
    // G4cout << "In MeV:" << G4endl;
    // for(G4int i = 0; i < fNumOfLayers; i++){
//        G4cout << "Layer#" << i << "  "
//               << this->getSum(i) / MeV << G4endl;
    }

    std::ofstream output;
    G4String fileName = fDetConstruction->fcrystalMatName + ".out";
    output.open(fileName);
    for(G4int i = 0; i < fNumOfLayers; i++){
        output  << "" << i << " ";
        G4double myMean = 0;
        G4double myStdErr = 0;
        G4int cnt = 0;
        for(G4double eee : fEdep[i]){
        	myMean += eee;
        	myStdErr += eee * eee;
        	cnt++;
        }
        myMean /= cnt;
        myStdErr = myStdErr / cnt - myMean * myMean;
        output  << myMean << " " 
        	<< myStdErr << " "
        	<< G4endl;
    }
    G4cout << "=========== Run finished =============" << G4endl;
    delete[] fEdep;
}

G4double MyRunAction::getSum(const G4int iLayer){
    G4double ttt = 0;
    for(G4double eee : fEdep[iLayer])
        ttt += eee;
    return ttt;
}
