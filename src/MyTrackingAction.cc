#include "MyTrackingAction.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
MyTrackingAction::MyTrackingAction():G4UserTrackingAction()
{}

MyTrackingAction::~MyTrackingAction()
{}

void MyTrackingAction::PreUserTrackingAction(const G4Track* track){
// Verbose Mode:

   G4cout << "TrackID=" << track->GetTrackID() << "    "
          << "ParentID=" << track->GetParentID() << "  "
          << "Particle=" << track->GetParticleDefinition()->GetParticleName() << " "
          << "GlobalTime=" << G4BestUnit(track->GetGlobalTime(),"Time") << G4endl;
   G4cout << "X, Y, Z, Time taken for this step, energy deposited within this step." << G4endl;
   G4cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << G4endl;
}

void MyTrackingAction::PostUserTrackingAction(const G4Track* track){
// Verbose Mode:

   G4cout << "=============Track Finish!===============" << G4endl;
}
