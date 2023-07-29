#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "ConfigReader.h"

// ConfigReader must be compiled using the flag -std=c++11 due to the 
//manner in which the two maps are initialized below.
void ConfigReader::initialize()
{
  intValCuts = {{"fixed_target",   -999},
		{"epd_max_weight", -999},
		{"nHits",          -999},
		{"nHits_dEdx",     -999},
		{"m_nHits",        -999},
		{"m_nHits_dEdx",   -999},
		{"min_tracks",     -999},
		{"shift_terms",    -999},
		{"epdA_inner_row", -999},
		{"epdA_outer_row", -999},
		{"epdB_inner_row", -999},
		{"epdB_outer_row", -999}};


  dblValCuts = {{"sqrt_s_NN",     -999.0},
		{"y_mid",         -999.0},
		{"y_beam",        -999.0},
		{"order_n",       -999.0},
		{"order_m",       -999.0},
		{"epd_threshold", -999.0},

		{"nHits_ratio",   -999.0},
		{"dca",           -999.0},
		{"m_nHits_ratio", -999.0},
		{"m_dca",         -999.0},

		{"r_vtx",        -999.0},
		{"z_vtx_low",    -999.0},
		{"z_vtx_high",   -999.0},
		{"m_r_vtx",      -999.0},
		{"m_z_vtx_low",  -999.0},
		{"m_z_vtx_high", -999.0},

		{"tpc_A_low_eta",  -999.0},
		{"tpc_A_high_eta", -999.0},
		{"tpc_B_low_eta",  -999.0},
		{"tpc_B_high_eta", -999.0},

		{"nSig_pi_low",  -999.0},
		{"nSig_pi_high", -999.0},
		{"nSig_ka_low",  -999.0},
		{"nSig_ka_high", -999.0},
		{"nSig_pr_low",  -999.0},
		{"nSig_pr_high", -999.0},

		{"z_de_low",  -999.0},
		{"z_de_high", -999.0},
		{"z_tr_low",  -999.0},
		{"z_tr_high", -999.0},

		{"m2_pi_low",  -999.0},
		{"m2_pi_high", -999.0},
		{"m2_ka_low",  -999.0},
		{"m2_ka_high", -999.0},
		{"m2_de_low",  -999.0},
		{"m2_de_high", -999.0},
		{"m2_tr_low",  -999.0},
		{"m2_tr_high", -999.0},

		{"yCM_norm_pi_low",  -999.0},
		{"yCM_norm_pi_high", -999.0},
		{"pt_norm_pi_low",   -999.0},
		{"pt_norm_pi_high",  -999.0},
		{"yCM_yExt_pi_low",  -999.0},
		{"yCM_yExt_pi_high", -999.0},
		{"pt_yExt_pi_low",   -999.0},
		{"pt_yExt_pi_high",  -999.0},

		{"yCM_norm_ka_low",  -999.0},
		{"yCM_norm_ka_high", -999.0},
		{"pt_norm_ka_low",   -999.0},
		{"pt_norm_ka_high",  -999.0},
		{"yCM_yExt_ka_low",  -999.0},
		{"yCM_yExt_ka_high", -999.0},
		{"pt_yExt_ka_low",   -999.0},
		{"pt_yExt_ka_high",  -999.0},

		{"yCM_norm_pr_low",  -999.0},
		{"yCM_norm_pr_high", -999.0},
		{"pt_norm_pr_low",   -999.0},
		{"pt_norm_pr_high",  -999.0},
		{"yCM_yDep_pr_low",  -999.0},
		{"yCM_yDep_pr_high", -999.0},
		{"pt_yDep_pr_low",   -999.0},
		{"pt_yDep_pr_high",  -999.0},

		{"yCM_yExt_pr_low",  -999.0},
		{"yCM_yExt_pr_high", -999.0},
		{"pt_yExt_pr_low",   -999.0},
		{"pt_yExt_pr_high",  -999.0},
		{"yCM_ySym_pr_low",  -999.0},
		{"yCM_ySym_pr_high", -999.0},
		{"pt_ySym_pr_low",   -999.0},
		{"pt_ySym_pr_high",  -999.0},

		{"yCM_yFor_pr_low",  -999.0},
		{"yCM_yFor_pr_high", -999.0},
		{"pt_yFor_pr_low",   -999.0},
		{"pt_yFor_pr_high",  -999.0},
		{"yCM_alt_pr_low",   -999.0},
		{"yCM_alt_pr_high",  -999.0},
		{"pt_alt_pr_low",    -999.0},
		{"pt_alt_pr_high",   -999.0},

		{"yCM_norm_de_low",  -999.0},
		{"yCM_norm_de_high", -999.0},
		{"pt_norm_de_low",   -999.0},
		{"pt_norm_de_high",  -999.0},
		
		{"yCM_norm_tr_low",  -999.0},
		{"yCM_norm_tr_high", -999.0},
		{"pt_norm_tr_low",   -999.0},
		{"pt_norm_tr_high",  -999.0},
		
		{"KT_pdt_low",  -999.0},
		{"KT_pdt_high", -999.0},};
}

void ConfigReader::setAllCuts()
{
  fixed_target = intValCuts["fixed_target"];
  epd_max_weight = intValCuts["epd_max_weight"];
  nHits = intValCuts["nHits"];
  nHits_dEdx = intValCuts["nHits_dEdx"];
  m_nHits = intValCuts["m_nHits"];
  m_nHits_dEdx = intValCuts["m_nHits_dEdx"];
  min_tracks = intValCuts["min_tracks"];
  shift_terms = intValCuts["shift_terms"];
  epdA_inner_row = intValCuts["epdA_inner_row"];
  epdA_outer_row = intValCuts["epdA_outer_row"];
  epdB_inner_row = intValCuts["epdB_inner_row"];
  epdB_outer_row = intValCuts["epdB_outer_row"];

  sqrt_s_NN = dblValCuts["sqrt_s_NN"];
  order_n = dblValCuts["order_n"]; 
  order_m = dblValCuts["order_m"]; 
  y_mid = dblValCuts["y_mid"]; 
  y_beam = dblValCuts["y_beam"];   

  epd_threshold = dblValCuts["epd_threshold"]; 
  nHits_ratio = dblValCuts["nHits_ratio"]; 
  dca = dblValCuts["dca"]; 
  m_nHits_ratio = dblValCuts["m_nHits_ratio"]; 
  m_dca = dblValCuts["m_dca"]; 

  tpc_A_low_eta = dblValCuts["tpc_A_low_eta"]; 
  tpc_A_high_eta = dblValCuts["tpc_A_high_eta"]; 
  tpc_B_low_eta = dblValCuts["tpc_B_low_eta"]; 
  tpc_B_high_eta = dblValCuts["tpc_B_high_eta"]; 

  r_vtx = dblValCuts["r_vtx"]; 
  z_vtx_low = dblValCuts["z_vtx_low"]; 
  z_vtx_high = dblValCuts["z_vtx_high"]; 
  m_r_vtx = dblValCuts["m_r_vtx"]; 
  m_z_vtx_low = dblValCuts["m_z_vtx_low"]; 
  m_z_vtx_high = dblValCuts["m_z_vtx_high"]; 

  nSig_pi_low = dblValCuts["nSig_pi_low"]; 
  nSig_pi_high = dblValCuts["nSig_pi_high"]; 
  nSig_ka_low = dblValCuts["nSig_ka_low"]; 
  nSig_ka_high = dblValCuts["nSig_ka_high"]; 
  nSig_pr_low = dblValCuts["nSig_pr_low"]; 
  nSig_pr_high = dblValCuts["nSig_pr_high"]; 

  z_de_low = dblValCuts["z_de_low"]; 
  z_de_high = dblValCuts["z_de_high"]; 
  z_tr_low = dblValCuts["z_tr_low"]; 
  z_tr_high = dblValCuts["z_tr_high"]; 

  m2_pi_low = dblValCuts["m2_pi_low"]; 
  m2_pi_high = dblValCuts["m2_pi_high"]; 
  m2_ka_low = dblValCuts["m2_ka_low"]; 
  m2_ka_high = dblValCuts["m2_ka_high"]; 
  m2_de_low = dblValCuts["m2_de_low"]; 
  m2_de_high = dblValCuts["m2_de_high"]; 
  m2_tr_low = dblValCuts["m2_tr_low"]; 
  m2_tr_high = dblValCuts["m2_tr_high"]; 

  yCM_norm_pi_low = dblValCuts["yCM_norm_pi_low"];
  yCM_norm_pi_high = dblValCuts["yCM_norm_pi_high"];
  pt_norm_pi_low = dblValCuts["pt_norm_pi_low"]; 
  pt_norm_pi_high = dblValCuts["pt_norm_pi_high"]; 
  yCM_yExt_pi_low = dblValCuts["yCM_yExt_pi_low"];
  yCM_yExt_pi_high = dblValCuts["yCM_yExt_pi_high"];
  pt_yExt_pi_low = dblValCuts["pt_yExt_pi_low"];
  pt_yExt_pi_high = dblValCuts["pt_yExt_pi_high"];

  yCM_norm_ka_low = dblValCuts["yCM_norm_ka_low"];
  yCM_norm_ka_high = dblValCuts["yCM_norm_ka_high"];
  pt_norm_ka_low = dblValCuts["pt_norm_ka_low"]; 
  pt_norm_ka_high = dblValCuts["pt_norm_ka_high"]; 
  yCM_yExt_ka_low = dblValCuts["yCM_yExt_ka_low"];
  yCM_yExt_ka_high = dblValCuts["yCM_yExt_ka_high"];
  pt_yExt_ka_low = dblValCuts["pt_yExt_ka_low"];
  pt_yExt_ka_high = dblValCuts["pt_yExt_ka_high"];

  yCM_norm_pr_low = dblValCuts["yCM_norm_pr_low"];
  yCM_norm_pr_high = dblValCuts["yCM_norm_pr_high"];
  pt_norm_pr_low = dblValCuts["pt_norm_pr_low"]; 
  pt_norm_pr_high = dblValCuts["pt_norm_pr_high"]; 
  yCM_yDep_pr_low = dblValCuts["yCM_yDep_pr_low"];
  yCM_yDep_pr_high = dblValCuts["yCM_yDep_pr_high"];
  pt_yDep_pr_low = dblValCuts["pt_yDep_pr_low"]; 
  pt_yDep_pr_high = dblValCuts["pt_yDep_pr_high"]; 
  yCM_yExt_pr_low = dblValCuts["yCM_yExt_pr_low"];
  yCM_yExt_pr_high = dblValCuts["yCM_yExt_pr_high"];
  pt_yExt_pr_low = dblValCuts["pt_yExt_pr_low"];
  pt_yExt_pr_high = dblValCuts["pt_yExt_pr_high"];
  yCM_ySym_pr_low = dblValCuts["yCM_ySym_pr_low"];
  yCM_ySym_pr_high = dblValCuts["yCM_ySym_pr_high"];
  pt_ySym_pr_low = dblValCuts["pt_ySym_pr_low"];
  pt_ySym_pr_high = dblValCuts["pt_ySym_pr_high"];
  yCM_yFor_pr_low = dblValCuts["yCM_yFor_pr_low"];
  yCM_yFor_pr_high = dblValCuts["yCM_yFor_pr_high"];
  pt_yFor_pr_low = dblValCuts["pt_yFor_pr_low"];
  pt_yFor_pr_high = dblValCuts["pt_yFor_pr_high"];
  yCM_alt_pr_low = dblValCuts["yCM_alt_pr_low"];
  yCM_alt_pr_high = dblValCuts["yCM_alt_pr_high"];
  pt_alt_pr_low = dblValCuts["pt_alt_pr_low"];
  pt_alt_pr_high = dblValCuts["pt_alt_pr_high"];


  yCM_norm_de_low = dblValCuts["yCM_norm_de_low"];
  yCM_norm_de_high = dblValCuts["yCM_norm_de_high"];
  pt_norm_de_low = dblValCuts["pt_norm_de_low"]; 
  pt_norm_de_high = dblValCuts["pt_norm_de_high"]; 

  yCM_norm_tr_low = dblValCuts["yCM_norm_tr_low"];
  yCM_norm_tr_high = dblValCuts["yCM_norm_tr_high"];
  pt_norm_tr_low = dblValCuts["pt_norm_tr_low"]; 
  pt_norm_tr_high = dblValCuts["pt_norm_tr_high"]; 

  KT_pdt_low = dblValCuts["KT_pdt_low"];
  KT_pdt_high = dblValCuts["KT_pdt_high"];
}

ConfigReader::ConfigReader() 
{ 
  initialize();
  errorFlag = false; 
}

ConfigReader::~ConfigReader()
{}

bool ConfigReader::errorFound()
{ return errorFlag; }

void ConfigReader::notifyError()
{
  std::cout << std::endl;
  std::cout << "There was an error in reading the config file." << std::endl;

  if (lastKey != "")
    { std::cout << "The last key and value read were: " << lastKey << ", " << lastValue << std::endl; }
  else
    { std::cout << "There were no keys or values read successfully." << std::endl; }
}

Bool_t ConfigReader::triggersMatch(UInt_t readTrigger)
{
  Bool_t triggerMatchFound = false;
  for (unsigned int i = 0; i < triggers.size(); i++)
    { 
      if (readTrigger == triggers[i]) 
	{ 
	  triggerMatchFound = true; 
	  break;
	} 
    }
  return triggerMatchFound;
}

void ConfigReader::read(std::string fileName)
{
  std::ifstream inputStream(fileName.c_str());

  std::string line;
  std::getline(inputStream, line);  // Get the first line

  // Loop over lines of input in current file
  while (inputStream.good())
    {
      // Skip the text lines and the empty lines
      if (line[0] == '#' || line.empty())
	{
	  std::getline(inputStream, line);
	  continue;
	}

      // Split string by delimeter '='
      std::string delimeter = "=";
      size_t pos = line.find(delimeter);

      if (pos == std::string::npos) 
	{ 
	  std::cout << "Missing \'=\' in a line of the config file." << std::endl; 
	  errorFlag = true;
	  break;
	}

      std::string key   = line.substr(0, pos);
      std::string value = line.substr(pos+1, std::string::npos);
      
      lastKey   = key;
      lastValue = value;

      // Now check if "value" is actually a list of values, if so, split it and try to save the triggers.
      size_t commaPos = value.find(",");

      if (commaPos != std::string::npos && key.compare("triggers") == 0)
	{
	  std::stringstream valueStream(value);

	  while(valueStream.good())
	    {
	      std::string subString;
	      std::getline(valueStream, subString, ',');
	      try
		{ 
		  UInt_t triggerValue = (UInt_t)std::atoi(subString.c_str()); 
		  triggers.push_back(triggerValue);
		}
	      catch (...)
		{
		  std::cout << "Error parsing this value: " << value << std::endl;
		  errorFlag = true;
		  break;
		}
	    }
	}
      else if (key.compare("triggers") == 0) // No commas, so only one trigger
	{
	  try
	    { 
	      UInt_t triggerValue = (UInt_t)std::atoi(value.c_str()); 
	      triggers.push_back(triggerValue); 
	    }
	  catch (...)
	    {
	      std::cout << "Error in this value for triggers: " << value << std::endl;
	      errorFlag = true;
	    }
	}
      if (errorFlag) break;

      if (key.compare("triggers") != 0)
	{
	  try
	    { intValCuts.at(key) = std::atoi(value.c_str()); }
	  catch (...)//(const std::out_of_range& oorInt) 
	    {
	      try
		{ dblValCuts.at(key) = std::atof(value.c_str()); }
	      catch (...)//(const std::out_of_range& oorDbl) 
		{
		  std::cout << "Unknown config key: " << key << std::endl;
		  errorFlag = true;
		  break;	      
		}
	    }
	}

      std::getline(inputStream, line); // Get the next line
    }// End while(inputStream.good())

  if (errorFlag) { notifyError(); }
  setAllCuts();
}// End function read()


void ConfigReader::printAll()
{
  std::map<std::string, int>::iterator intIt;
  std::map<std::string, double>::iterator dblIt;

  for (intIt = intValCuts.begin(); intIt != intValCuts.end(); intIt++)
    {
      std::cout << intIt->first    // string (key)
		<< ':'
		<< intIt->second   // string's value 
		<< std::endl;
    }

  for (dblIt = dblValCuts.begin(); dblIt != dblValCuts.end(); dblIt++)
    {
      std::cout << dblIt->first    // string (key)
		<< ':'
		<< dblIt->second   // string's value 
		<< std::endl;
    }
}// End function printAll()

void ConfigReader::checkForNonSetKeys()
{
  std::map<std::string, int>::iterator intIt;
  std::map<std::string, double>::iterator dblIt;
  std::vector<std::string> nonSetKeys;

  for (intIt = intValCuts.begin(); intIt != intValCuts.end(); intIt++)
    {
      if (intIt->second == -999) nonSetKeys.push_back(intIt->first);
    }

  for (dblIt = dblValCuts.begin(); dblIt != dblValCuts.end(); dblIt++)
    {
      if (dblIt->second == -999) nonSetKeys.push_back(dblIt->first);
    }

  if (nonSetKeys.size() == 0)
    {
      std::cout << "All known keys are set." << std::endl;
    }
  else
    {
      std::cout << "These known keys were never set:" << std::endl;

      for (unsigned int i = 0; i < nonSetKeys.size(); i++)
	{
	  std::cout << nonSetKeys.at(i) << std::endl;
	}
    }
}// End function checkForNonSetKeys()
