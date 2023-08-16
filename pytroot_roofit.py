import ROOT
import random



def change_roo_dataset():
    # Open the new dataset file
    new_dataset_file = ROOT.TFile.Open("new_dataset.root")
    if new_dataset_file.IsZombie():
        print("Error opening new dataset file.")
        return

    # Get the new RooDataSet
    old_dataset = new_dataset_file.Get("toys/toy_asimov")
    old_dataset.Print()
    # Clone the old dataset into a new dataset
    new_dataset = old_dataset.Clone("new_dataset")
    new_dataset.reset()




    fmap = ROOT.TFile("Untagged.inp.root")
    hmap = fmap.Get("data_obs")
    hmap.SetName("hmap")
    
    for i in range(old_dataset.numEntries()):
        entr=  old_dataset.get(i)
        
        xval = old_dataset.get(i).getRealValue("CMS_th1x")
        chan_ =  old_dataset.get(i).find("CMS_channel")
        w_ =  old_dataset.weight()  #find("weight:_weight_")

        print chan_
        '''
        print w_
        #print xval
        #entr.Print()
        ibinmap = hmap.FindBin(xval)
        contmap = hmap.GetBinContent(ibinmap)
        weight = 1
        if contmap >  0: 

            weight = 0.8
            rand = random.uniform(0, 1)
            
            if rand < 0.95: 
                new_dataset.add(ROOT.RooArgList(xval,chan_),w_)

        else : 

             
            new_dataset.add(entr)

        #print old_dataset.get(i).getRealValue("CMS_channel")
        #print old_dataset.get(i).getRealValue("weight:_weight_")
        #print "- ---- "
        '''
    
    new_dataset.Print()
    # Save the modified dataset
    modified_file = ROOT.TFile("weighted_Dataset.root", "RECREATE")
    new_dataset.Write()
    modified_file.Close()

change_roo_dataset()
