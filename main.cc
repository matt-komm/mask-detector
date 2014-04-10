#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "B2aDetectorConstruction.hh"
#include "B2MagneticField.hh"
#include "MaskDetector.hh"

#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

#include "FTFP_BERT.hh"
#include "QGSP_BERT.hh"

#ifdef G4VIS_USE
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{
  // Construct the default run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes
  //
  
  //G4VUserDetectorConstruction* detector = new DetectorConstruction();
  //G4VUserDetectorConstruction* detector = new B2aDetectorConstruction();
  MaskDetector* detector = new MaskDetector();
  runManager->SetUserInitialization(detector);
  //
  B2MagneticField* magField = new B2MagneticField();
  //magField->SetMagFieldValue(8.0);
  magField->SetMagFieldValue(G4ThreeVector(0.0,0.0,0.5));
  G4VModularPhysicsList* physicsList = new QGSP_BERT;
  //physicsList->RegisterPhysics(new G4StepLimiterBuilder());
  runManager->SetUserInitialization(physicsList);
  
  //G4VUserPhysicsList* physics = new PhysicsList();
  //runManager->SetUserInitialization(physics);

  // set mandatory user action class
  //
  G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
  runManager->SetUserAction(gen_action);

  // Initialize G4 kernel
  //
  runManager->Initialize();

  
  
  #ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
 visManager->Initialize();
  
  // Get the pointer to the UI manager and set verbosities
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/run/verbose 1");
  UImanager->ApplyCommand("/event/verbose 1");
  UImanager->ApplyCommand("/tracking/verbose 1");
  
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  
  UImanager->ApplyCommand("/control/execute init_vis.mac");
  G4int numberOfEvent = 1;
  runManager->BeamOn(numberOfEvent);
  std::cout<<"simulate..."<<std::endl;
  ui->SessionStart();
 
  //delete visManager;
   #endif
  // Start a run
  //
  

  // Job termination
  //
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  //
  delete runManager;

  return 0;
}


