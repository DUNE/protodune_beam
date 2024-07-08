grab_ifbeam.py
  Interface to IFBeam. Uses wget to download csv files of the devices which provide necessary information for the analysis scripts in AnaScripts.
  Packs them into a tree which is compatible with those scripts.

  usage: 
    python grab_ifbeam.py --start <start time> --end <end time> --interval <interval>
      Will retrieve data between the stated times, in batches defined by <interval>

