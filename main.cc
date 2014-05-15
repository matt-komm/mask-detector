#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "B2aDetectorConstruction.hh"
#include "B2MagneticField.hh"
#include "MaskDetector.hh"

#include "PhysicsList.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include "PrimaryGeneratorAction.hh"

#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Random/MTwistEngine.h"

#include "FTFP_BERT.hh"
#include "QGSP_BERT.hh"

#ifdef WITH_GEANT4_UIVIS
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{
  G4RunManager* runManager = new G4RunManager;
  MaskDetector* detector = new MaskDetector();
  runManager->SetUserInitialization(detector);
  //
  B2MagneticField* magField = new B2MagneticField();
  magField->SetMagFieldValue(G4ThreeVector(0.0,0.0,0.5));
  G4VModularPhysicsList* physicsList = new QGSP_BERT;
  //physicsList->RegisterPhysics(new G4StepLimiterBuilder());
  runManager->SetUserInitialization(physicsList);
  
  RunAction* runAction = new RunAction();
  runManager->SetUserAction(runAction);
  
  PrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
  EventAction* eventAction = new EventAction();
  runManager->SetUserAction(eventAction);
  //G4VUserPhysicsList* physics = new PhysicsList();
  //runManager->SetUserInitialization(physics);
  
  
  runManager->SetUserAction(gen_action);

  runManager->Initialize();

  
  
  #ifdef WITH_GEANT4_UIVIS
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/run/verbose 1");
  UImanager->ApplyCommand("/event/verbose 1");
  UImanager->ApplyCommand("/tracking/verbose 1");
  
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  
  UImanager->ApplyCommand("/control/execute init_vis.mac");
  #endif
  
  G4int numberOfEvent = 10;
  runManager->BeamOn(numberOfEvent);
  
  #ifdef WITH_GEANT4_UIVIS
  ui->SessionStart();
 
  delete visManager;
  #endif
  
  delete runManager;

  return 0;
}


