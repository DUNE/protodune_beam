grab_ifbeam.py
  Interface to IFBeam. Uses wget to download csv files of the devices which provide necessary information 
  for the analysis scripts in AnaScripts. Packs them into a tree which is compatible with those scripts.

  usage: 
    python grab_ifbeam.py --start <start time> --end <end time> --interval <interval>
      Will retrieve data between the stated times, in batches defined by <interval>



compare_collimators.py
  Script to compare files produced from analysis scripts in the context of 3 collimator settings 
  (10mm, 20mm, 30mm). Can preform 3 different 'routines' to compare 3 different attributes
    * momentum
    * tof
    * triggers

  usage:
    python compare_collimators.py -i <10mm file> <20mm file> <30mm file> -o <output file> --routine <routine>

    routine-specific options:
      momentum:
        --range <low> <high> --- drawing range
        --rebin <N> --- argument to pass to TH1::Rebin

      tof:
        --cut <val> --- value used to check the fraction of events below the cut to estimate non-proton triggers
