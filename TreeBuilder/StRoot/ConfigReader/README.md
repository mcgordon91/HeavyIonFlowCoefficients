# ConfigReader
Class used to read and store values from text files to be used in any STAR anisotropic flow analysis.

To use this class in a flow analysis, first make sure you have a proper config file that it can read. Check `config_3p0GeV_example.txt` for an example, but mainly just make sure you **don't use any spaces on each line** (empty lines are fine). This class is designed to read in all values in an efficient way and make them each available by name so that the main analysis code still looks clean. It does this by reading the values into std::maps that take string->int or string->double and then passing the values from the maps to the corresponding member variables. Errors in reading the config files should be caught, and if anything is not caught or set, they all have a default value of -999 or -999.0.

### Basic Instructions

In your main analysis, create the object, read the config file, and then just retrieve any of the values by name from the object:

```c++
ConfigReader configs;
configs.read(configFileName);

// If you want to abort your analysis when an error is encountered while reading:
if (configs.errorFound()) 
  { 
    std::cout << "There was an error reading the configurations! Aborting analysis!" << std::endl; 
    return 1; 
  }

// Now make some kind of pseudorapidity cut, for example:
if (eta < configs.y_mid) {...}
```

Since this class can currently store a whole list of trigger values, there is a function (`triggersMatch`) that will help check for the proper triggers internally to keep the main analysis code clean. Here is an example trigger cut using it. The idea is that if the trigger you're currently looking at matches one in your configs, then the event is good. It doesn't check if the event contains every trigger in the configs.

```c++
std::vector<UInt_t> triggerIDs;
triggerIDs = event->triggerIds();
Bool_t b_bad_trig = true;

for (UInt_t i = 0; i < triggerIDs.size(); i++) 
  { 
    if ( configs.triggersMatch(triggerIDs[i]) ) 
      { b_bad_trig = false; }
  }

if (b_bad_trig) continue;
```

### Adding New Values to Configs

If your analysis requires you to frequently change an important value that is not present in the config files, that new value can be easily added. Adding new values should also not disrupt any others using this repo that don't need that value. Adding new values takes just 3 steps:

1) Add it to `ConfigReader.h` as an `Int_t`, or `Double_t`. If you want a boolean, make it an `Int_t` and just only use 0 or 1 for the value.
2) Go to the `initialize()` function in `ConfigReader.cxx` and initialize the new variable within the `intValCuts` or `dblValCuts` maps with a value of -999 or -999.0.
3) Go down to the `setAllCuts()` in the same file and initialize the member variable with the same value from the map.

Now you should be able to read the configs and use the new value in your analysis! Nothing needs to be done to the actual `read` function due to use of the maps.
