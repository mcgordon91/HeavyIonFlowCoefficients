/**** All of this code is located within the loop over TPC tracks ****/


// TOF information here before full PID next
// d_tofBeta = -999.0 if it's not a TOF hit
//=========================================================
//          TOF Beta Cuts
//=========================================================
Double_t d_m2 = -999.0;
Bool_t tofTrack = (d_tofBeta != -999.0);

if (tofTrack)
  {
    d_m2 = d_mom*d_mom*( (1.0 / (d_tofBeta*d_tofBeta)) - 1.0);		    
    h_m2->Fill(d_m2);
    h_tofBeta->Fill(d_tofBeta);		  
    h2_beta_vs_qp->Fill(s_charge*d_mom, 1.0/d_tofBeta);
    h2_m2_vs_qp->Fill(s_charge*d_mom, d_m2);
    h2_pT_vs_eta_TOF->Fill(d_eta, d_pT);
  }
//=========================================================
//          End TOF Beta Cuts
//=========================================================


Double_t d_zDeuteron = (s_charge == 1) ? TMath::Log(d_dEdx / bichselZ_de->Eval(d_mom)) : -999.0;
Double_t d_zTriton   = (s_charge == 1) ? TMath::Log(d_dEdx / bichselZ_tr->Eval(d_mom)) : -999.0;

//=========================================================
//          PID Cuts
//=========================================================
Bool_t pion   = false;
Bool_t kaon   = false;
Bool_t proton = (d_nSigmaPr > configs.nSig_pr_low) && (d_nSigmaPr < configs.nSig_pr_high) && (s_charge == 1);
Bool_t deuteron = false;
Bool_t triton   = false;

if (tofTrack)
  {
    pion = (d_nSigmaPi > configs.nSig_pi_low) &&
      (d_nSigmaPi < configs.nSig_pi_high) &&
      (d_m2 > configs.m2_pi_low) &&
      (d_m2 < configs.m2_pi_high);

    kaon = (d_nSigmaKa > configs.nSig_ka_low) &&
      (d_nSigmaKa < configs.nSig_ka_high) &&
      (d_m2 > configs.m2_ka_low) &&
      (d_m2 < configs.m2_ka_high);
  }


// 3.0 GeV d and t PID
if (!pion && !kaon && configs.sqrt_s_NN == 3.0)
  {
    deuteron = FlowUtils::momDepDeuteronID(configs.sqrt_s_NN, d_mom, d_zDeuteron, tofTrack, d_m2, 
					   configs.z_de_low, configs.z_de_high, configs.m2_de_low, configs.m2_de_high);
    
    triton = FlowUtils::momDepTritonID(configs.sqrt_s_NN, d_mom, d_zTriton, tofTrack, d_m2, 
				       configs.z_tr_low, configs.z_tr_high, configs.m2_tr_low, configs.m2_tr_high);
  }
// Basic d and t PID
 else if (!pion && !kaon && 
	  (configs.sqrt_s_NN == 7.2 || 
	   configs.sqrt_s_NN == 3.22 || 
	   configs.sqrt_s_NN == 3.5 || 
	   configs.sqrt_s_NN == 3.9 || 
	   configs.sqrt_s_NN == 4.5))
   {
     //  DEUTERON
     if (tofTrack)
       {
	 if (d_zDeuteron > configs.z_de_low &&
	     d_zDeuteron < configs.z_de_high &&
	     d_m2 > configs.m2_de_low &&
	     d_m2 < configs.m2_de_high)
	   deuteron = true;
       }

     //  TRITON
     if (tofTrack)
       {
	 if (d_zTriton > configs.z_tr_low &&
	     d_zTriton < configs.z_tr_high &&
	     d_m2 > configs.m2_tr_low &&
	     d_m2 < configs.m2_tr_high)
	   triton = true;
       }
   }

if (deuteron && triton) { deuteron = false; triton = false; } // Ignore tags of both d and t.
if (deuteron && proton) { proton = false; } // d and t will have some contamination from p, but that has been minimized
if (triton && proton)   { proton = false; }

if (pion && proton)   { proton = false; }
if (kaon && proton)   { proton = false; }
//=========================================================
//          END PID Cuts
//=========================================================
