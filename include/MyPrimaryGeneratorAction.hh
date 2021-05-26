#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

/// The primary generator action class with particle gum.
///
/// It defines a single particle which hits the calorimeter
/// perpendicular to the input face. The type of the particle
/// can be changed via the G4 build-in commands of G4ParticleGun class
/// (see the macros provided with this example).

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  MyPrimaryGeneratorAction();
  virtual ~MyPrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* event);

private:
  G4ParticleGun*  fParticleGun; // G4 particle gun
};
