#include "G4VUserActionInitialization.hh"

class MyDetectorConstruction;

/// Action initialization class.
///

class MyActionInitialization : public G4VUserActionInitialization
{
  public:
    MyActionInitialization(MyDetectorConstruction*);
    virtual ~MyActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    MyDetectorConstruction* fDetConstruction;
};
