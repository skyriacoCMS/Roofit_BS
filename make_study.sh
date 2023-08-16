#!/bin/bash
#./run_gamma_mu_offshellexp.sh
#cp higgsCombinegamma_floatRVRFexp.MultiDimFit.mH125.123456.root new_dataset.root 
python change_data.py 
root -l ImportAsimov.cc
