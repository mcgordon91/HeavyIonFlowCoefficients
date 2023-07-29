#include <iostream>
#include "TFile.h"
#include "TH2D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TClassTable.h"
#include "TSystem.h"

const Double_t D_M0_PI = 0.139571;   //Rest masses
const Double_t D_M0_KA = 0.493677;
const Double_t D_M0_PR = 0.938272;
const Double_t D_M0_DE = 1.875613;   // Deuteron
const Double_t D_M0_TR = 2.808921;   // Triton
const Double_t D_M0_HE3 = 2.809414;   // Helium-3
const Double_t D_M0_AL = 3.727379;   // Alpha
const Double_t D_M0_HE6 = 6.01888*0.931494;   // Helium-6
const Double_t D_M0_LI6 = 6.015122*0.931494;   // Lithium-6
const Double_t D_M0_LI7 = 7.015122*0.931494;   // Lithium-7

const Double_t D_ScaleCharge = 1.00;   // Lithium-7


class Bichsel;
Bichsel *m_Bichsel = 0;

Double_t bichselZ(Double_t *x,Double_t *par) 
{
  Double_t pove   = x[0];
  Double_t poverm = pove/par[0];
  return TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(poverm),par[1]));
}

Double_t bichselZneg(Double_t *x,Double_t *par) 
{
  Double_t pove   = -x[0];
  Double_t poverm = pove/par[0];
  return TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(poverm),par[1]));
}

Double_t bichselZcharge2(Double_t *x,Double_t *par) 
{
  //Double_t pove   = 2.0 * x[0];
  Double_t pove   = 2.0 * x[0];
  Double_t poverm = pove/par[0];
  //poverm * = 2.0;
  //return 2.0 * 2.0 * TMath::Exp(Bichsel::Instance()->GetMostProbableZ(TMath::Log10(poverm),par[1])); // Not fit
  //return TMath::Exp(Bichsel::Instance()->GetI70M(TMath::Log10(poverm),par[1])); // Not working, but this works in Xionghong's code
  //return TMath::Exp(Bichsel::Instance()->GetI70M(TMath::Log10(poverm),1)); // Not working, but this works in Xionghong's code
  //return 2.0 * 2.0 * TMath::Exp(Bichsel::Instance()->GetI70M(TMath::Log10(poverm),1)); // Not working, but this works in Xionghong's code
  //return D_ScaleCharge * D_ScaleCharge * 2.0 * 2.0 * TMath::Exp(Bichsel::Instance()->GetMostProbableZM(TMath::Log10(poverm),par[1])); // Currently best oftion
  return D_ScaleCharge * D_ScaleCharge * 2.0 * 2.0 * TMath::Exp(Bichsel::Instance()->GetMostProbableZM(TMath::Log10(poverm),1.)); // Currently best oftion
}

Double_t bichselZcharge3(Double_t *x,Double_t *par) 
{
  Double_t pove   = 3.0 * x[0];
  Double_t poverm = pove/par[0];
  return D_ScaleCharge * D_ScaleCharge * 3.0 * 3.0 * TMath::Exp(Bichsel::Instance()->GetMostProbableZM(TMath::Log10(poverm),par[1])); // Currently best oftion
  //return TMath::Exp(Bichsel::Instance()->GetI70M(TMath::Log10(poverm),par[1])); // Not working, but this works in Xionghong's code
  //return TMath::Exp(Bichsel::Instance()->GetI70M(TMath::Log10(poverm),1)); // Not working, but this works in Xionghong's code
  //return 3.0 * 3.0 * TMath::Exp(Bichsel::Instance()->GetI70M(TMath::Log10(poverm),1)); // Not working, but this works in Xionghong's code
  //return 3.0 * 3.0 * TMath::Exp(Bichsel::Instance()->GetI70M(TMath::Log10(poverm),par[1])); // Not working, but this works in Xionghong's code
}



void bichselComparison()
{
  if (gClassTable->GetID("StBichsel") < 0) { gSystem->Load("libStBichsel"); }
  if (!m_Bichsel) m_Bichsel = Bichsel::Instance();

  //TFile *file = TFile::Open("../flow/results_3p0_FXT/Normal.picoDst.result.combined.root", "READ");
  //TFile *file = TFile::Open("/star/data01/pwg/cracz/flowResults/2A3CDD3C0689D117F919A0C31499D1D2.picoDst.result.combined.root", "READ");
  //TFile *file = TFile::Open("3ECC87829E372126A6EF44AB30C5ADEE.picoDst.result.combined.root", "READ");
  TFile *file = TFile::Open("../qapid.01092023.root", "READ");

  if (!file) { std::cout << "File error!" << std::endl; return; }

  Double_t log2dx = 1.0;
  Double_t xStartPos = 0.01;
  Double_t xStopPos  = 6.0;
  Double_t xStartNeg = -3.0;
  Double_t xStopNeg  = -0.01;
  Int_t npx = 100000;
  //                      Mass  log2(dx) 
  Double_t params[2] = {  1.0,   log2dx  };

  params[0] = D_M0_PI;
  TF1 *bichselZ_pi = new TF1(Form("BichselZ_pi_log2dx_%i",(int)log2dx),bichselZ,xStartPos,xStopPos,2);
  if (!bichselZ_pi) { std::cout << "Pi function error" << std::endl; }
  bichselZ_pi->SetParameters(params); 
  bichselZ_pi->SetNpx(npx);
  bichselZ_pi->SetLineColor(3);

  TF1 *bichselZ_pi_neg = new TF1(Form("BichselZneg_pi_log2dx_%i",(int)log2dx),bichselZneg,xStartNeg,xStopNeg,2);
  if (!bichselZ_pi_neg) { std::cout << "Pi function error" << std::endl; }
  bichselZ_pi_neg->SetParameters(params); 
  bichselZ_pi_neg->SetNpx(npx);
  bichselZ_pi_neg->SetLineColor(4);


  params[0] = D_M0_KA;
  TF1 *bichselZ_ka = new TF1(Form("BichselZ_ka_log2dx_%i",(int)log2dx),bichselZ,xStartPos,xStopPos,2);
  if (!bichselZ_ka) { std::cout << "Ka function error" << std::endl; }
  bichselZ_ka->SetParameters(params); 
  bichselZ_ka->SetNpx(npx);
  bichselZ_ka->SetLineColor(5);

  TF1 *bichselZ_ka_neg = new TF1(Form("BichselZneg_ka_log2dx_%i",(int)log2dx),bichselZneg,xStartNeg,xStopNeg,2);
  if (!bichselZ_ka_neg) { std::cout << "Ka function error" << std::endl; }
  bichselZ_ka_neg->SetParameters(params); 
  bichselZ_ka_neg->SetNpx(npx);
  bichselZ_ka_neg->SetLineColor(6);


  params[0] = D_M0_PR;
  TF1 *bichselZ_pr = new TF1(Form("BichselZ_pr_log2dx_%i",(int)log2dx),bichselZ,xStartPos,xStopPos,2);
  if (!bichselZ_pr) { std::cout << "Pr function error" << std::endl; }
  bichselZ_pr->SetParameters(params); 
  bichselZ_pr->SetNpx(npx);
  bichselZ_pr->SetLineColor(7);


  params[0] = D_M0_DE;
  TF1 *bichselZ_de = new TF1(Form("BichselZ_de_log2dx_%i",(int)log2dx),bichselZ,xStartPos,xStopPos,2);
  if (!bichselZ_de) { std::cout << "De function error" << std::endl; }
  bichselZ_de->SetParameters(params); 
  bichselZ_de->SetNpx(npx);
  bichselZ_de->SetLineColor(8);


  params[0] = D_M0_TR;
  TF1 *bichselZ_tr = new TF1(Form("BichselZ_tr_log2dx_%i",(int)log2dx),bichselZ,xStartPos,xStopPos,2);
  if (!bichselZ_tr) { std::cout << "Tr function error" << std::endl; }
  bichselZ_tr->SetParameters(params); 
  bichselZ_tr->SetNpx(npx);
  bichselZ_tr->SetLineColor(1);

  params[0] = D_M0_HE3;
  TF1 *bichselZ_he3 = new TF1(Form("BichselZ_he3_log2dx_%i",(int)log2dx),bichselZcharge2,xStartPos,xStopPos,2);
  if (!bichselZ_he3) { std::cout << "He3 function error" << std::endl; }
  bichselZ_he3->SetParameters(params); 
  bichselZ_he3->SetNpx(npx);
  bichselZ_he3->SetLineColor(2);

  params[0] = D_M0_AL;
  TF1 *bichselZ_al = new TF1(Form("BichselZ_al_log2dx_%i",(int)log2dx),bichselZcharge2,xStartPos,xStopPos,2);
  if (!bichselZ_al) { std::cout << "Al function error" << std::endl; }
  bichselZ_al->SetParameters(params); 
  bichselZ_al->SetNpx(npx);
  bichselZ_al->SetLineColor(4);

  params[0] = D_M0_HE6;
  TF1 *bichselZ_he6 = new TF1(Form("BichselZ_he6_log2dx_%i",(int)log2dx),bichselZcharge2,xStartPos,xStopPos,2);
  if (!bichselZ_he6) { std::cout << "He6 function error" << std::endl; }
  bichselZ_he6->SetParameters(params); 
  bichselZ_he6->SetNpx(npx);
  bichselZ_he6->SetLineColor(5);

  params[0] = D_M0_LI6;
  TF1 *bichselZ_li6 = new TF1(Form("BichselZ_li6_log2dx_%i",(int)log2dx),bichselZcharge3,xStartPos,xStopPos,2);
  if (!bichselZ_li6) { std::cout << "Li6 function error" << std::endl; }
  bichselZ_li6->SetParameters(params); 
  bichselZ_li6->SetNpx(npx);
  bichselZ_li6->SetLineColor(6);

  params[0] = D_M0_LI7;
  TF1 *bichselZ_li7 = new TF1(Form("BichselZ_li7_log2dx_%i",(int)log2dx),bichselZcharge3,xStartPos,xStopPos,2);
  if (!bichselZ_li7) { std::cout << "Li7 function error" << std::endl; }
  bichselZ_li7->SetParameters(params); 
  bichselZ_li7->SetNpx(npx);
  bichselZ_li7->SetLineColor(7);

  TH2D *h2 = (TH2D*)file->Get("h2_dEdx_vs_qp");
  //TH2D *h2 = (TH2D*)file->Get("h2_dEdx_vs_qp_0");
  //TH2D *h2 = (TH2D*)file->Get("h2_dEdx_vs_qp_1");
  //TH2D *h2 = (TH2D*)file->Get("h2_dEdx_vs_qp_2");

  // Recreate ROOT 6 kBird palette
  const Int_t Number = 9;
  Double_t red[Number]   = { 0.2082, 0.0592, 0.0780, 0.0232, 0.1802, 0.5301, 0.8186, 0.9956, 0.9764};
  Double_t green[Number] = { 0.1664, 0.3599, 0.5041, 0.6419, 0.7178, 0.7492, 0.7328, 0.7862, 0.9832};
  Double_t blue[Number]  = { 0.5293, 0.8684, 0.8385, 0.7914, 0.6425, 0.4662, 0.3499, 0.1968, 0.0539};
  Double_t stops[Number] = { 0.0000, 0.1250, 0.2500, 0.3750, 0.5000, 0.6250, 0.7500, 0.8750, 1.0000};
  Int_t nb = 255;
  TColor::CreateGradientColorTable(Number,stops,red,green,blue,nb);


  TCanvas *canvas = new TCanvas("canvas", "canvas", 875, 675);
  canvas->SetLogz();
  canvas->SetTicks();
  canvas->SetRightMargin(0.13);
  gStyle->SetOptStat(0);
  gStyle->SetOptDate(0);

  h2->Draw("colz");
  bichselZ_pi->Draw("CSAME");
  bichselZ_pi_neg->Draw("CSAME");
  bichselZ_ka->Draw("CSAME");
  bichselZ_ka_neg->Draw("CSAME");
  bichselZ_pr->Draw("CSAME");
  bichselZ_de->Draw("CSAME");
  bichselZ_tr->Draw("CSAME");
  bichselZ_he3->Draw("CSAME");
  bichselZ_al->Draw("CSAME");
  bichselZ_he6->Draw("CSAME");
  bichselZ_li6->Draw("CSAME");
  bichselZ_li7->Draw("CSAME");
  TLegend *leg = new TLegend(0.65,0.45,0.75,0.9,"");
  leg->AddEntry(bichselZ_pi,"#pi^{+}");
  leg->AddEntry(bichselZ_pi_neg,"#pi^{-}");
  leg->AddEntry(bichselZ_ka,"K^{+}");
  leg->AddEntry(bichselZ_ka_neg,"K^{-}");
  leg->AddEntry(bichselZ_pr,"p");
  leg->AddEntry(bichselZ_de,"d");
  leg->AddEntry(bichselZ_tr,"t");
  leg->AddEntry(bichselZ_he3,"^{3}He");
  leg->AddEntry(bichselZ_al,"#alpha");
  leg->AddEntry(bichselZ_he6,"^{6}He");
  leg->AddEntry(bichselZ_li6,"^{6}Li");
  leg->AddEntry(bichselZ_li7,"^{7}Li");
  leg->Draw("same");
  //const Int_t NMasses = 19;
  //const Double_t kAu2Gev=0.9314943228;
  //struct Part_t {
  //  const Char_t *Name;
  //  Int_t         PiD;
  //  Int_t         Charge;
  //  Int_t         Index;
  //  Double_t      Mass;
  //};
  //Part_t Part[NMasses] = {
  //  //name,   PiD, Charge,  Index, Mass
  //  {"p",       1,      1,      4, 0.93827231},                 // 0 p
  //  {"K",       2,      1,      3, 0.493677},                   // 1 K
  //  {"#pi",     3,      1,      2, 0.13956995},                 // 2 pi
  //  {"e",       0,      1,      0, 0.51099907e-3},              // 3 e
  //  {"d",       5,      1,      5, 1.87561339},                 // 4 d
  //  {"#mu",     4,      1,      1, 0.1056584},                  // 5 mu
  //  {"t",       6,      1,      6, 2.80925},                    // 6 t
  //  {"He3",     7,      2,      7, 2.80923}, //GEANT3           // 7 He3
  //  {"#alpha",  8,      2,      8, 3.727417}, //GEANT3          // 8 He4
  //  {"He6",    -1,      2,     12, 3*kAu2Gev+14.931e-3},        // 9
  //  {"Li6",    10,      3,     10, 5.6031},                     //10 Li6
  //  {"Li7",     9,      3,      9, 6.5354},                     //11 Li7
  //  {"Be7",    -1,      4,      0, 7.016003437*kAu2Gev},        //12
  //  {"Be9",    -1,      4,      0, 9.01218307*kAu2Gev},        //13
  //  {"Be10",   -1,      4,      0, 10.01353470*kAu2Gev},        //14
  //  {"B10",    -1,      5,      0, 10.01353470*kAu2Gev},        //15
  //  {"B11",    -1,      5,      0, 11.009305167*kAu2Gev},       //16
  //  {"2#pi",    3,     -1,     -2, -0.13956995},                //17 2*pi
  //  {"2p",      1,     -1,      0, -0.93827231}                 //18 2*p
  //};

  //TLegend *leg = new TLegend(0.65,0.45,0.75,0.9,"");
  //leg->AddEntry(bichselZ_pi,Part[2].Name);
  //leg->AddEntry(bichselZ_ka,Part[1].Name);
  //leg->AddEntry(bichselZ_pr,Part[0].Name);
  //leg->AddEntry(bichselZ_de,Part[4].Name);
  //leg->AddEntry(bichselZ_tr,Part[6].Name);
  //leg->AddEntry(bichselZ_al,Part[8].Name);


  canvas->SaveAs("dEdx_vs_qp.png");
  //canvas->SaveAs("dEdx_vs_qp_0.png");
  //canvas->SaveAs("dEdx_vs_qp_1.png");
  //canvas->SaveAs("dEdx_vs_qp_2.png");
  //canvas->SaveAs("dEdx_vs_qp.pdf");
  canvas->Clear();

  delete canvas;

  delete bichselZ_pi;
  delete bichselZ_pi_neg;
  delete bichselZ_ka;
  delete bichselZ_ka_neg;
  delete bichselZ_pr;
  delete bichselZ_de;
  delete bichselZ_tr;
  delete bichselZ_he3;
  delete bichselZ_al;
}
