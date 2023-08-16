#include <TFile.h>
#include <RooWorkspace.h>
#include <RooDataSet.h>
#include <TH1.h>
#include <TRandom3.h>

void change_data() {
  // Open the new dataset file
  TFile* new_dataset_file = TFile::Open("new_dataset.root");
  if (!new_dataset_file || new_dataset_file->IsZombie()) {
    std::cerr << "Error opening new dataset file." << std::endl;
    return;
  }

  // Get the new RooDataSet
  RooDataSet* old_dataset = dynamic_cast<RooDataSet*>(new_dataset_file->Get("toys/toy_asimov"));
  if (!old_dataset) {
    std::cerr << "Error retrieving old dataset." << std::endl;
    return;
  }
  old_dataset->Print();

  // Clone the old dataset into a new dataset

  TFile* fmap = TFile::Open("Untagged.inp.root");
  TH1F* hmap = dynamic_cast<TH1F*>(fmap->Get("data_obs"));
  if (!hmap) {
    std::cerr << "Error retrieving histogram." << std::endl;
    return;
  }
  hmap->SetName("hmap");


  RooRealVar* x_ = new  RooRealVar("CMS_th1x","", 0., 1805 ); 
  RooRealVar* w_ = new  RooRealVar("weight","",0,10000);
  
  old_dataset->get(10)->Print("V");

  
  RooCategory* chan_ = dynamic_cast<RooCategory*>(old_dataset->get()->find("CMS_channel"));

  RooDataSet* new_dataset = new RooDataSet("data_obs","",RooArgSet(*x_,*chan_,*w_),w_->GetName());



 
  for (int i = 0; i < old_dataset->numEntries(); i++) {
    old_dataset->get(i);
    double xval = old_dataset->get(i)->getRealValue("CMS_th1x");


    cout<<chan_<<endl;
    int ibinmap = hmap->FindBin(xval);
    double contmap = hmap->GetBinContent(ibinmap);
    double weight = 1.0;
    
    //RooCategory::Label label = static_cast<RooCategory::Label>(entry->getCatIndex("CMS_channel"));
    //RooCategory* chan_ = dynamic_cast<RooCategory*>(old_dataset->evaluate("CMS_channel"));
    double w = old_dataset->weight();
    //cout<<xval<<" "<<yval<<endl;
    //RooArgSet* entry = new_dataset->get(i);
    x_->setVal(xval);
    if (contmap > 0) {
      w_->setVal(w*0.8);
      cout<<"change"<<endl;
    }
    else{
      w_->setVal(w);
    }
    //y->setVal(w);
    //*chan_,
    //RooCategory::Label label = category->getLabel();
    new_dataset->add( RooArgList(*x_,*chan_, *w_), w_->getVal() );
    new_dataset->get(i);
    //cout<<w <<" " <<new_dataset->weight()<<" "<<yval <<endl;
    //new_dataset->setweight(w)
    cout<<w <<" "<<new_dataset->weight()<<" "<<w_->getVal() <<endl;
      /*
    if (contmap > 0) {
      weight = 0.8;

      RooArgSet args;
      args.add(*chan_);
      args.add(RooRealVar("xval", "", xval));
      new_dataset->add(args, w_);
    }

    */
 
  }

  new_dataset->get(10)->Print("V");
  new_dataset->get(11)->Print("V");

  old_dataset->Print();
  new_dataset->Print();

  // Save the modified dataset
  TFile* modified_file = TFile::Open("weighted_Dataset.root", "RECREATE");
  new_dataset->Write();
  modified_file->Close();
}
