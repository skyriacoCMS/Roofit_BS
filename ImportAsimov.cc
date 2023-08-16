#include <TFile.h>
#include <RooWorkspace.h>
#include <RooDataSet.h>

void ImportAsimov() {
  // Open the original workspace file
  TFile* original_file = TFile::Open("width_workspace.root", "READ");
  RooWorkspace* original_workspace = dynamic_cast<RooWorkspace*>(original_file->Get("w"));

  // Create a new workspace as a deep copy of the original
  RooWorkspace* new_workspace = new RooWorkspace(*original_workspace);




  // Open the file with the new dataset
  //TFile* new_dataset_file = TFile::Open("higgsCombinegamma_floatRVRFexp.MultiDimFit.mH125.123456.root", "READ");
  TFile* new_dataset_file = TFile::Open("weighted_Dataset.root", "READ");
 
  if (!new_dataset_file || new_dataset_file->IsZombie()) {
    std::cerr << "Error opening new dataset file." << std::endl;
    return 1;
  }


  // Get the new RooDataSet
  


  //RooDataSet* new_dataset = dynamic_cast<RooDataSet*>(new_dataset_file->Get("toys/toy_asimov"));
  RooDataSet* new_dataset = dynamic_cast<RooDataSet*>(new_dataset_file->Get("data_obs"));

  if (!new_dataset) {
    std::cerr << "Error retrieving new dataset." << std::endl;
    return 1;
  }
  new_dataset->Print();
  new_dataset->SetName("data_obs");

  //new_workspace->Print();

  
 
  /*
  // Rename the old dataset and delete it
   //delete old_data;
  */
  

  // Import the new dataset
  RooDataSet* old_data = dynamic_cast<RooDataSet*>(original_workspace->data("data_obs"));
  old_data->SetName("olddata");

  original_workspace->RecursiveRemove(old_data);
  //original_workspace->renameSet("data_obs","old_data");
  original_workspace->import(*new_dataset);

  // Save the modified workspace
  TFile* modified_file = TFile::Open("modified_workspace.root", "RECREATE");
  original_workspace->Write();
  modified_file->Close();
 
}
