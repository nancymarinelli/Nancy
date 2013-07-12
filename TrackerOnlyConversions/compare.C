
{
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  TFile*  hFile = new TFile ("histosDataWithAssByHit.root");
  TFile*  hFile2 = new TFile ("../dataAssByPos/histosAssByPos.root");
  hFile->cd();

  //  TFile*  hFile = new TFile ("histosForPas.root");

  TCanvas *c1 = new TCanvas("plot1", "plot1",430, 10, 600, 600);
  c1->SetBorderMode(0);
  //regular
  TCanvas *c2 = new TCanvas("plot2", "plot2",430, 10, 700, 450);
  c2->SetBorderMode(0);
  //log
  TCanvas *c3 = new TCanvas("plot3", "plot3",430, 10, 700, 450);
  c3->SetBorderMode(0);
  c3->SetLogy();

  //regular
  TCanvas *cTest = new TCanvas("test", "test",430, 10, 700, 450);
  cTest->SetBorderMode(0);
  cTest->SetLogy();


  TLatex myText;
  myText.SetTextSize(0.05);
  myText.SetNDC();


  /// newntuples  PAS Selection and chi2prob>=0.0005  by candidates
  double r2_use_entries =  499064;
  double r2_use_entries_forw = 40957;
  double r2_use_entries_allforw = 224787;
  double r2_use_entries_forw2 = 6564;
    
  double r1_use_entries = 280083;
  double r1_use_entries_forw = 27223;
  double r1_use_entries_allforw =  131057;
  double r1_use_entries_forw2 = 4162;

  /// newntuples  PAS Selection and chi2prob>=0.0005 + pt  by candidates
  /*
  double r2_use_entries =  89947;
  double r2_use_entries_forw = 6899;
  double r2_use_entries_allforw = 46705;
  double r2_use_entries_forw2 = 950;
    
  double r1_use_entries = 53331;
  double r1_use_entries_forw = 4657;
  double r1_use_entries_allforw =  27817;
  double r1_use_entries_forw2 = 621;
  */



  TLegend *leg = new TLegend(0.60,0.65,0.80,.85);
  leg->SetFillColor(kWhite);
  c3->cd();
  h_mc_photon_pt_ext->SetTitle("");
  h_mc_photon_pt_ext->GetXaxis()->SetTitle("Converted #gamma p_{T} [GeV]");
  h_mc_photon_pt_ext->GetYaxis()->SetTitle("# of conversions");
  h_mc_photon_pt_ext->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_pt_ext->SetLineColor(kBlack);
  h_mc_photon_pt_ext->SetFillColor(kGreen);
  h_mc_photon_pt_ext->SetMinimum(9);
  h_mc_photon_pt_ext->Draw();
  h_mc_photon_pt_fakes_ext->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_pt_fakes_ext->SetLineColor(kYellow);
  h_mc_photon_pt_fakes_ext->SetFillColor(kYellow);
  h_mc_photon_pt_fakes_ext->SetFillStyle(3001);
  leg->AddEntry(h_mc_photon_pt_fakes_ext, "MC fakes - Ass by Hits", "f");
  h_mc_photon_pt_fakes_ext->Draw("same");
  hFile2->cd();
  h_mc_photon_pt_fakes_ext->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_pt_fakes_ext->SetLineColor(kBlack);
  h_mc_photon_pt_fakes_ext->SetFillColor(kBlack);
  h_mc_photon_pt_fakes_ext->SetFillStyle(3017);
  leg->AddEntry(h_mc_photon_pt_fakes_ext, "MC fakes - Ass by Pos", "f");
  h_mc_photon_pt_fakes_ext->Draw("same");
  hFile->cd();
  h_data_photon_pt_ext->SetMarkerStyle(20);
  h_data_photon_pt_ext->SetMarkerColor(kBlack);
  h_data_photon_pt_ext->Draw("esame");
  leg->AddEntry(h_data_photon_pt_ext, "7 TeV data", "pl");
  leg->AddEntry(h_mc_photon_pt_ext, "MC", "f");
  leg->Draw();
  myText.DrawLatex(2.,800.,"CMS Preliminary");
  c3->SaveAs("photon_pt_ext_data.root");
  c3->SaveAs("photon_pt_ext_data.png");
  c3->SaveAs("photon_pt_ext_data.eps");

 
  TLegend *leg = new TLegend(0.60,0.65,0.80,.85); 
  leg->SetFillColor(kWhite);
  c3->cd();
  h_mc_photon_dz_s->SetTitle("");
  h_mc_photon_dz_s->GetXaxis()->SetTitle("Conversion track innermost position #Delta Z [cm]");
  h_mc_photon_dz_s->GetYaxis()->SetTitle("# of conversions");
  h_mc_photon_dz_s->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_dz_s->SetLineColor(kBlack);
  h_mc_photon_dz_s->SetFillColor(kGreen);
  h_mc_photon_dz_s->SetMinimum(9);
  h_mc_photon_dz_s->Draw();
  h_mc_photon_dz_fakes_s->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_dz_fakes_s->SetLineColor(kYellow);
  h_mc_photon_dz_fakes_s->SetFillColor(kYellow);
  h_mc_photon_dz_fakes_s->Draw("same");
  h_data_photon_dz_s->SetMarkerStyle(20);
  h_data_photon_dz_s->SetMarkerColor(kBlack);
  h_data_photon_dz_s->Draw("esame");
  leg->AddEntry(h_data_photon_dz_s, "7 TeV data", "pl");
  leg->AddEntry(h_mc_photon_dz_s, "MC", "f");
  leg->AddEntry(h_mc_photon_dz_fakes_s, "MC fakes ", "f");
  leg->Draw();
  myText.DrawLatex(-4.,800.,"CMS Preliminary");
  c3->SaveAs("photon_dz_data_barrel.png");
  c3->SaveAs("photon_dz_data_barrel.root");
  c3->SaveAs("photon_dz_data_barrel.eps");



  TLegend *leg2 = new TLegend(0.70,0.70,0.90,0.90); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_phi->SetTitle("");
  h_mc_photon_phi->GetXaxis()->SetTitle("#phi (#gamma) ");
  h_mc_photon_phi->GetYaxis()->SetTitle("Conversions/0.0875 rad");
  h_mc_photon_phi->Scale((double)r2_use_entries/r1_use_entries);
  //  h_mc_photon_phi->GetYaxis()->SetRangeUser(0.,1000.);
  h_mc_photon_phi->SetLineColor(kBlack);
  h_mc_photon_phi->SetFillColor(kGreen);
  h_mc_photon_phi->Draw();
  h_mc_photon_fakes_phi->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_phi->SetLineColor(kYellow);
  h_mc_photon_fakes_phi->SetFillColor(kYellow);
  h_mc_photon_fakes_phi->SetFillStyle(3001);
  h_mc_photon_fakes_phi->Draw("same");
  hFile2->cd();
  h_mc_photon_fakes_phi->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_phi->SetLineColor(kBlack);
  h_mc_photon_fakes_phi->SetFillColor(kBlack);
  h_mc_photon_fakes_phi->SetFillStyle(3017);
  leg2->AddEntry(h_mc_photon_fakes_phi, "MC fakes- Ass by Pos ", "f");
  h_mc_photon_fakes_phi->Draw("same");
  hFile->cd();
  h_data_photon_phi->SetMarkerStyle(20);
  h_data_photon_phi->SetMarkerColor(kBlack);
  h_data_photon_phi->Draw("esame");
  leg2->AddEntry(h_data_photon_phi, "Data", "pl");
  leg2->AddEntry(h_mc_photon_phi, "MC", "f");
  leg2->AddEntry(h_mc_photon_fakes_phi, "MC fakes- Ass by Hits", "f");
  leg2->Draw();
  //myText.DrawLatex(-2.5,400.,"CMS Preliminary ");
  //myText.DrawLatex(-2.5,350.,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_phi_data.png");
  c2->SaveAs("photon_phi_data.root");
  c2->SaveAs("photon_phi_data.eps");


  TLegend *leg2 = new TLegend(0.70,0.70,0.90,0.90); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  float nData =  h_data_photon_phi_ZLT26_RLT19->Integral();
  float nMC =  h_mc_photon_phi_ZLT26_RLT19->Integral();
  h_mc_photon_phi_ZLT26_RLT19->SetTitle("");
  h_mc_photon_phi_ZLT26_RLT19->GetXaxis()->SetTitle("#phi (#gamma) ");
  h_mc_photon_phi_ZLT26_RLT19->GetYaxis()->SetTitle("Conversions/0.0875 rad");
  //  h_mc_photon_phi_ZLT26_RLT19->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_phi_ZLT26_RLT19->Scale((double)nData/nMC);
  //  h_mc_photon_phi->GetYaxis()->SetRangeUser(0.,1000.);
  h_mc_photon_phi_ZLT26_RLT19->SetLineColor(kBlack);
  h_mc_photon_phi_ZLT26_RLT19->SetFillColor(kGreen);
  h_mc_photon_phi_ZLT26_RLT19->Draw();
  // h_mc_photon_fakes_phi_ZLT26_RLT19->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_phi_ZLT26_RLT19->Scale((double)nData/nMC);
  h_mc_photon_fakes_phi_ZLT26_RLT19->SetLineColor(kYellow);
  h_mc_photon_fakes_phi_ZLT26_RLT19->SetFillColor(kYellow);
  h_mc_photon_fakes_phi_ZLT26_RLT19->Draw("same");
  h_data_photon_phi_ZLT26_RLT19->SetMarkerStyle(20);
  h_data_photon_phi_ZLT26_RLT19->SetMarkerColor(kBlack);
  h_data_photon_phi_ZLT26_RLT19->Draw("esame");
  leg2->AddEntry(h_data_photon_phi_ZLT26_RLT19, "Data", "pl");
  leg2->AddEntry(h_mc_photon_phi_ZLT26_RLT19, "MC", "f");
  leg2->AddEntry(h_mc_photon_fakes_phi_ZLT26_RLT19, "MC fakes ", "f");
  leg2->Draw();
  //myText.DrawLatex(-2.5,400.,"CMS Preliminary ");
  //myText.DrawLatex(-2.5,350.,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_phi_ZLT26_RLT19_data.png");
  c2->SaveAs("photon_phi_ZLT26_RLT19_data.root");
  c2->SaveAs("photon_phi_ZLT26_RLT19_data.eps");


  TLegend *leg2 = new TLegend(0.60,0.30,0.80,0.55); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  float nData =  h_data_photon_phi_ZLT73_RGT22->Integral();
  float nMC =  h_mc_photon_phi_ZLT73_RGT22->Integral();
  h_mc_photon_phi_ZLT73_RGT22->SetTitle("");
  h_mc_photon_phi_ZLT73_RGT22->GetXaxis()->SetTitle("#phi (#gamma) ");
  h_mc_photon_phi_ZLT73_RGT22->GetYaxis()->SetTitle("Conversions/0.0875 rad");
  //h_mc_photon_phi_ZLT73_RGT22->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_phi_ZLT73_RGT22->Scale((double)nData/nMC);
  //  h_mc_photon_phi->GetYaxis()->SetRangeUser(0.,1000.);
  h_mc_photon_phi_ZLT73_RGT22->SetLineColor(kBlack);
  h_mc_photon_phi_ZLT73_RGT22->SetFillColor(kGreen);
  h_mc_photon_phi_ZLT73_RGT22->Draw();
  // h_mc_photon_fakes_phi_ZLT73_RGT22->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_phi_ZLT73_RGT22->Scale((double)nData/nMC);
  h_mc_photon_fakes_phi_ZLT73_RGT22->SetLineColor(kYellow);
  h_mc_photon_fakes_phi_ZLT73_RGT22->SetFillColor(kYellow);
  h_mc_photon_fakes_phi_ZLT73_RGT22->Draw("same");
  h_data_photon_phi_ZLT73_RGT22->SetMarkerStyle(20);
  h_data_photon_phi_ZLT73_RGT22->SetMarkerColor(kBlack);
  h_data_photon_phi_ZLT73_RGT22->Draw("esame");
  leg2->AddEntry(h_data_photon_phi_ZLT73_RGT22, "Data", "pl");
  leg2->AddEntry(h_mc_photon_phi_ZLT73_RGT22, "MC", "f");
  leg2->AddEntry(h_mc_photon_fakes_phi_ZLT73_RGT22, "MC fakes ", "f");
  leg2->Draw();
  //myText.DrawLatex(-2.5,400.,"CMS Preliminary ");
  //myText.DrawLatex(-2.5,350.,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_phi_ZLT73_RGT22_data.png");
  c2->SaveAs("photon_phi_ZLT73_RGT22_data.root");
  c2->SaveAs("photon_phi_ZLT73_RGT22_data.eps");





  TLegend *leg2 = new TLegend(0.70,0.70,0.90,0.90); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_iphi->SetTitle("");
  h_mc_photon_iphi->GetXaxis()->SetTitle("#phi (#gamma) ");
  h_mc_photon_iphi->GetYaxis()->SetTitle("Conversions/0.0875 rad");
  h_mc_photon_iphi->Scale((double)r2_use_entries/r1_use_entries);
  //h_mc_photon_iphi->GetYaxis()->SetRangeUser(0.,600.);
  h_mc_photon_iphi->SetLineColor(kBlack);
  h_mc_photon_iphi->SetFillColor(kGreen);
  h_mc_photon_iphi->Draw();
  h_mc_photon_fakes_iphi->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_iphi->SetLineColor(kYellow);
  h_mc_photon_fakes_iphi->SetFillColor(kYellow);
  h_mc_photon_fakes_iphi->Draw("same");
  h_data_photon_iphi->SetMarkerStyle(20);
  h_data_photon_iphi->SetMarkerColor(kBlack);
  h_data_photon_iphi->Draw("esame");
  leg2->AddEntry(h_data_photon_iphi, "Data", "pl");
  leg2->AddEntry(h_mc_photon_iphi, "MC", "f");
  leg2->AddEntry(h_mc_photon_fakes_iphi, "MC fakes ", "f");
  leg2->Draw();
  //myText.DrawLatex(-2.5,400.,"CMS Preliminary ");
  //myText.DrawLatex(-2.5,350.,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_iphi_data.png");
  c2->SaveAs("photon_iphi_data.root");
  c2->SaveAs("photon_iphi_data.eps");



  TLegend *leg2 = new TLegend(0.40,0.50,0.60,.70); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_eta->SetTitle("");
  h_mc_photon_eta->GetXaxis()->SetTitle("#eta (#gamma) ");
  h_mc_photon_eta->GetYaxis()->SetTitle("Conversions/0.06");
  h_mc_photon_eta->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_eta->SetLineColor(kBlack);
  h_mc_photon_eta->SetFillColor(kGreen);
  //h_mc_photon_eta->GetYaxis()->SetRangeUser(0.,1000.);
  h_mc_photon_eta->Draw();
  h_mc_photon_fakes_eta->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_eta->SetLineColor(kYellow);
  h_mc_photon_fakes_eta->SetFillColor(kYellow);
  h_mc_photon_fakes_eta->SetFillStyle(3001);
  h_mc_photon_fakes_eta->Draw("same");
  hFile2->cd();
  h_mc_photon_fakes_eta->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_eta->SetLineColor(kBlack);
  h_mc_photon_fakes_eta->SetFillColor(kBlack);
  h_mc_photon_fakes_eta->SetFillStyle(3017);
  leg2->AddEntry(h_mc_photon_fakes_eta, "MC fakes: Ass by Pos", "f");
  h_mc_photon_fakes_eta->Draw("same");
  hFile->cd();
  h_data_photon_eta->SetMarkerStyle(20);
  h_data_photon_eta->SetMarkerColor(kBlack);
  h_data_photon_eta->Draw("esame");
  leg2->AddEntry(h_data_photon_eta, "Data", "pl");
  leg2->AddEntry(h_mc_photon_eta, "MC", "f");
  leg2->AddEntry(h_mc_photon_fakes_eta, "MC fakes: Ass by Hits", "f");
  leg2->Draw();
  //  myText.DrawLatex(-0.8,270.,"CMS Preliminary ");
  //myText.DrawLatex(-0.8,240.,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_eta_data.png");
  c2->SaveAs("photon_eta_data.root");
  c2->SaveAs("photon_eta_data.eps");






  TLegend *leg = new TLegend(0.60,0.65,0.80,.85); 
  leg->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_mass2->SetTitle("");
  h_mc_photon_mass2->GetXaxis()->SetTitle("Conversion track-pair invariant mass [GeV/c^{2}]");
  h_mc_photon_mass2->GetYaxis()->SetTitle("Conversions/0.0025 GeV/c^{2}");
  h_mc_photon_mass2->GetYaxis()->SetTitleOffset(1.2);
  h_mc_photon_mass2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_mass2->SetLineColor(kBlack);
  h_mc_photon_mass2->SetFillColor(kGreen);
  //h_mc_photon_mass2->GetXaxis()->SetRangeUser(0.,0.15);
  h_mc_photon_mass2->Draw();
  h_mc_photon_fakes_mass2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_mass2->SetLineColor(kYellow);
  h_mc_photon_fakes_mass2->SetFillColor(kYellow);
  h_mc_photon_fakes_mass2->SetFillStyle(3001);
  h_mc_photon_fakes_mass2->Draw("same");
  hFile2->cd();
  h_mc_photon_fakes_mass2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_mass2->SetLineColor(kBlack);
  h_mc_photon_fakes_mass2->SetFillColor(kBlack);
  h_mc_photon_fakes_mass2->SetFillStyle(3017);
  leg->AddEntry(h_mc_photon_fakes_mass2, "MC fakes: Ass by Pos ", "f");
  h_mc_photon_fakes_mass2->Draw("same");
  hFile->cd();
  h_mc_photon_fakesGT02_mass2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakesGT02_mass2->SetLineColor(kOrange);
  h_mc_photon_fakesGT02_mass2->SetFillColor(kOrange);
  //  h_mc_photon_fakesGT02_mass2->Draw("same");
  h_data_photon_mass2->SetMarkerStyle(20);
  //  h_data_photon_mass2->SetMarkerSize(0.8);
  h_data_photon_mass2->SetMarkerColor(kBlack);
  h_data_photon_mass2->Draw("esame");
  leg->AddEntry(h_data_photon_mass2, "Data", "pl");
  leg->AddEntry(h_mc_photon_mass2, "MC", "f");
  leg->AddEntry(h_mc_photon_fakes_mass2, "MC fakes: Ass by Hits ", "f");
  leg->Draw();
  //  myText.DrawLatex(0.025.,3000.,"CMS Preliminary ");
  // myText.DrawLatex(0.025.,2750.,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_massMomAtVtx_linear.png");
  c2->SaveAs("photon_massMomAtVtx_linear.eps");
  c2->SaveAs("photon_massMomAtVtx_linear.root");






  TCanvas *c4 = new TCanvas("plot4", "plot4",430, 10, 700, 450);
  c4->SetBorderMode(0);
  TLegend *leg = new TLegend(0.60,0.65,0.80,.85); 
  leg->SetFillColor(kWhite);
  c4->cd();
  h_data_photon_mass2_vs_r->SetTitle("");
  h_data_photon_mass2_vs_r->GetXaxis()->SetTitle("Conversion radius (cm) for |z|< 26cm");
  h_data_photon_mass2_vs_r->GetYaxis()->SetTitle("Conversion track-pair invariant mass [GeV]");
  h_data_photon_mass2_vs_r->SetMarkerColor(kBlack);
  h_data_photon_mass2_vs_r->SetMarkerStyle(2);
  h_data_photon_mass2_vs_r->SetMarkerSize(0.2);
  h_data_photon_mass2_vs_r->Draw("");
  h_mc_photon_mass2_vs_r->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_mass2_vs_r->SetMarkerColor(kGreen);
  h_mc_photon_mass2_vs_r->SetMarkerStyle(2);
  h_mc_photon_mass2_vs_r->SetMarkerSize(0.2);
  h_mc_photon_mass2_vs_r->Draw("same");
  h_mc_photon_fakes_mass2_vs_r->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_mass2_vs_r->SetMarkerColor(kYellow);
  h_mc_photon_fakes_mass2_vs_r->SetMarkerStyle(2);
  h_mc_photon_fakes_mass2_vs_r->SetMarkerSize(0.08);
  h_mc_photon_fakes_mass2_vs_r->Draw("same");
  //  h_mc_photon_fakesGT02_mass2_vs_r->Scale((double)r2_use_entries/r1_use_entries);
  // h_mc_photon_fakesGT02_mass2_vs_r->SetMarkerColor(kOrange);
  // h_mc_photon_fakesGT02_mass2_vs_r->SetMarkerStyle(2);
  //h_mc_photon_fakesGT02_mass2_vs_r->SetMarkerSize(0.5);
  //h_mc_photon_fakesGT02_mass2_vs_r->Draw("same");
  leg->AddEntry(h_data_photon_mass2_vs_r, "7 TeV data", "pl");
  leg->AddEntry(h_mc_photon_mass2_vs_r, "MC", "pl");
  leg->AddEntry(h_mc_photon_fakes_mass2_vs_r, "MC fakes ", "pl");
  leg->Draw();
  myText.DrawLatex(-4.,800.,"CMS Preliminary");
  c4->SaveAs("photon_mass2_vs_r.png");
  c4->SaveAs("photon_mass2_vs_r.root");
  c4->SaveAs("photon_mass2_vs_r.eps");



  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85);
  leg2->SetFillColor(kWhite);
  cTest->cd();
  h_mc_photon_chi2prob->SetTitle("");
  h_mc_photon_chi2prob->GetXaxis()->SetTitle("Conversion #gamma #chi^{2}");
  h_mc_photon_chi2prob->GetYaxis()->SetTitle("# of conversions");
  h_mc_photon_chi2prob->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_chi2prob->SetMinimum(9);
  h_mc_photon_chi2prob->SetLineColor(kBlack);
  h_mc_photon_chi2prob->SetFillColor(kGreen);
  h_mc_photon_chi2prob->Draw();
  h_mc_photon_fakes_chi2prob->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_chi2prob->SetLineColor(kYellow);
  h_mc_photon_fakes_chi2prob->SetFillColor(kYellow);
  h_mc_photon_fakes_chi2prob->SetFillStyle(3001);
  h_mc_photon_fakes_chi2prob->Draw("same");
  hFile2->cd();
  h_mc_photon_fakes_chi2prob->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_chi2prob->SetLineColor(kBlack);
  h_mc_photon_fakes_chi2prob->SetFillColor(kBlack);
  h_mc_photon_fakes_chi2prob->SetFillStyle(3017);
  leg2->AddEntry(h_mc_photon_fakes_chi2prob, "MC fakes: Ass by Pos", "f");
  h_mc_photon_fakes_chi2prob->Draw("same");
  hFile->cd();
  h_data_photon_chi2prob->SetMarkerStyle(20);
  h_data_photon_chi2prob->SetMarkerColor(kBlack);
  h_data_photon_chi2prob->SetMaximum(2500);
  h_data_photon_chi2prob->Draw("esame");
  leg2->AddEntry(h_data_photon_chi2prob, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_photon_chi2prob, "MC", "f");
  leg2->AddEntry(h_mc_photon_fakes_chi2prob, "MC fakes: Ass by Hits", "f");
  leg2->Draw();
  myText.DrawLatex(2.,2400.,"CMS Preliminary");
  cTest->SaveAs("photon_chi2prob_data.png");






  TLegend *leg = new TLegend(0.60,0.65,0.80,.85); 
  leg->SetFillColor(kWhite);
  c3->cd();
  h_mc_photon_minapp->SetTitle("");
  h_mc_photon_minapp->GetXaxis()->SetTitle("Distance of min approach [cm]");
  h_mc_photon_minapp->GetYaxis()->SetTitle("Conversions/0.013 cm");
  h_mc_photon_minapp->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_minapp->SetLineColor(kBlack);
  h_mc_photon_minapp->SetFillColor(kGreen);
  h_mc_photon_minapp->SetMinimum(9);
  h_mc_photon_minapp->Draw();
  h_mc_photon_fakes_minapp->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_minapp->SetLineColor(kYellow);
  h_mc_photon_fakes_minapp->SetFillColor(kYellow);
  h_mc_photon_fakes_minapp->SetFillStyle(3001);
  h_mc_photon_fakes_minapp->Draw("same");
  hFile2->cd();
  h_mc_photon_fakes_minapp->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_minapp->SetLineColor(kBlack);
  h_mc_photon_fakes_minapp->SetFillColor(kBlack);
  h_mc_photon_fakes_minapp->SetFillStyle(3017);
  leg->AddEntry(h_mc_photon_fakes_minapp, "MC fakes: Ass by Pos", "f");
  h_mc_photon_fakes_minapp->Draw("same");
  hFile->cd();
  h_data_photon_minapp->SetMarkerStyle(20);
  h_data_photon_minapp->SetMarkerColor(kBlack);
  h_data_photon_minapp->Draw("esame");
  leg->AddEntry(h_data_photon_minapp, "Data", "pl");
  leg->AddEntry(h_mc_photon_minapp, "MC", "f");
  leg->AddEntry(h_mc_photon_fakes_minapp, "MC fakes: Ass by Hits", "f");
  leg->Draw();
  myText.DrawLatex(0.03.,800.,"CMS Preliminary ");
  myText.DrawLatex(0.03.,500.,"#sqrt{s} = 7 TeV");
  c3->SaveAs("photon_minapp_data.png");
  c3->SaveAs("photon_minapp_data.root");
  c3->SaveAs("photon_minapp_data.eps");

  TLegend *leg = new TLegend(0.65,0.65,0.85,.85); 
  leg->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_dcot->SetTitle("");
  h_mc_photon_dcot->GetXaxis()->SetTitle("Conversion track-pair #Delta cot#theta");
  h_mc_photon_dcot->GetYaxis()->SetTitle("Conversions/0.24 rad");
  h_mc_photon_dcot->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_dcot->SetLineColor(kBlack);
  h_mc_photon_dcot->SetFillColor(kGreen);
  h_mc_photon_dcot->SetMaximum(25000);
  h_mc_photon_dcot->Draw();
  h_mc_photon_fakes_dcot->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_dcot->SetLineColor(kYellow);
  h_mc_photon_fakes_dcot->SetFillColor(kYellow);
  h_mc_photon_fakes_dcot->SetFillStyle(3001);
  h_mc_photon_fakes_dcot->Draw("same");
  hFile2->cd();
  h_mc_photon_fakes_dcot->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_fakes_dcot->SetLineColor(kBlack);
  h_mc_photon_fakes_dcot->SetFillColor(kBlack);
  h_mc_photon_fakes_dcot->SetFillStyle(3017);
  leg->AddEntry(h_mc_photon_fakes_dcot, "MC fakes:As by Pos", "f");
  h_mc_photon_fakes_dcot->Draw("same");
  hFile->cd();
  h_data_photon_dcot->SetMarkerStyle(20);
  h_data_photon_dcot->SetMarkerColor(kBlack);
  h_data_photon_dcot->Draw("esame");
  leg->AddEntry(h_data_photon_dcot, "Data", "pl");
  leg->AddEntry(h_mc_photon_dcot, "MC", "f");
  leg->AddEntry(h_mc_photon_fakes_dcot, "MC fakes:As by Hits", "f");
  leg->Draw();
  myText.DrawLatex(-0.1,400.,"CMS Preliminary ");
  myText.DrawLatex(-0.1,300.,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_dcot_data.png");
  c2->SaveAs("photon_dcot_data.root");
  c2->SaveAs("photon_dcot_data.eps");



  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_tk_algo->SetTitle("");
  h_mc_tk_algo->GetXaxis()->SetTitle("Conversion track algo");
  h_mc_tk_algo->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_algo->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo->SetLineColor(kBlack);
  h_mc_tk_algo->SetFillColor(kGreen);
  h_mc_tk_algo->SetMinimum(0.);
  h_mc_tk_algo->Draw();
  h_mc_tk_algo_fakes->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_fakes->SetLineColor(kYellow);
  h_mc_tk_algo_fakes->SetFillColor(kYellow);
  h_mc_tk_algo_fakes->Draw("same");
  h_mc_tk_algo_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_fakesGT02->SetLineColor(kOrange);
  h_mc_tk_algo_fakesGT02->SetFillColor(kOrange);
  h_mc_tk_algo_fakesGT02->Draw("same");
  h_data_tk_algo->SetMarkerStyle(20);
  h_data_tk_algo->SetMarkerColor(kBlack);
  h_data_tk_algo->Draw("esame");
  leg2->AddEntry(h_data_tk_algo, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_tk_algo, "MC", "f");
  leg2->AddEntry(h_mc_tk_algo_fakes, "MC fakes", "f");
  leg2->Draw();
  //  myText.DrawLatex(5.,2000.,"CMS Preliminary");
  c2->SaveAs("photon_tk_algo_data.eps");
  c2->SaveAs("photon_tk_algo_data.png");



  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_tk_algo_l1->SetTitle("");
  h_mc_tk_algo_l1->GetXaxis()->SetTitle("Conversion track algo for conversions in PXL1");
  h_mc_tk_algo_l1->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_algo_l1->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_l1->SetLineColor(kBlack);
  h_mc_tk_algo_l1->SetFillColor(kGreen);
  h_mc_tk_algo_l1->SetMinimum(0.);
  h_mc_tk_algo_l1->Draw();
  h_mc_tk_algo_fakes_l1->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_fakes_l1->SetLineColor(kYellow);
  h_mc_tk_algo_fakes_l1->SetFillColor(kYellow);
  h_mc_tk_algo_fakes_l1->Draw("same");
  h_mc_tk_algo_fakesGT02_l1->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_fakesGT02_l1->SetLineColor(kOrange);
  h_mc_tk_algo_fakesGT02_l1->SetFillColor(kOrange);
  h_mc_tk_algo_fakesGT02_l1->Draw("same");
  h_data_tk_algo_l1->SetMarkerStyle(20);
  h_data_tk_algo_l1->SetMarkerColor(kBlack);
  h_data_tk_algo_l1->Draw("esame");
  leg2->AddEntry(h_data_tk_algo_l1, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_tk_algo_l1, "MC", "f");
  leg2->AddEntry(h_mc_tk_algo_fakes_l1, "MC fakes", "f");
  leg2->Draw();
  //  myText.DrawLatex(5.,2000.,"CMS Preliminary");
  c2->SaveAs("photon_tk_algo_l1_data.eps");
  c2->SaveAs("photon_tk_algo_l1_data.png");

  TLegend *leg2 = new TLegend(0.20,0.65,0.40,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_tk_algo_l2->SetTitle("");
  h_mc_tk_algo_l2->GetXaxis()->SetTitle("Conversion track algo for conversions in PXL2");
  h_mc_tk_algo_l2->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_algo_l2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_l2->SetLineColor(kBlack);
  h_mc_tk_algo_l2->SetFillColor(kGreen);
  h_mc_tk_algo_l2->SetMinimum(0.);
  h_mc_tk_algo_l2->Draw();
  h_mc_tk_algo_fakes_l2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_fakes_l2->SetLineColor(kYellow);
  h_mc_tk_algo_fakes_l2->SetFillColor(kYellow);
  h_mc_tk_algo_fakes_l2->Draw("same");
  h_mc_tk_algo_fakesGT02_l2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_fakesGT02_l2->SetLineColor(kOrange);
  h_mc_tk_algo_fakesGT02_l2->SetFillColor(kOrange);
  h_mc_tk_algo_fakesGT02_l2->Draw("same");
  h_data_tk_algo_l2->SetMarkerStyle(20);
  h_data_tk_algo_l2->SetMarkerColor(kBlack);
  h_data_tk_algo_l2->Draw("esame");
  leg2->AddEntry(h_data_tk_algo_l2, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_tk_algo_l2, "MC", "f");
  leg2->AddEntry(h_mc_tk_algo_fakes_l2, "MC fakes", "f");
  leg2->Draw();
  //  myText.DrawLatex(5.,2000.,"CMS Preliminary");
  c2->SaveAs("photon_tk_algo_l2_data.eps");
  c2->SaveAs("photon_tk_algo_l2_data.png");


  TLegend *leg2 = new TLegend(0.20,0.65,0.40,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_tk_algo_l3->SetTitle("");
  h_mc_tk_algo_l3->GetXaxis()->SetTitle("Conversion track algo for conversions in PXL3");
  h_mc_tk_algo_l3->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_algo_l3->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_l3->SetLineColor(kBlack);
  h_mc_tk_algo_l3->SetFillColor(kGreen);
  h_mc_tk_algo_l3->SetMinimum(0.);
  h_mc_tk_algo_l3->GetYaxis()->SetRangeUser(0.,4000.);
  h_mc_tk_algo_l3->Draw();
  h_mc_tk_algo_fakes_l3->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_fakes_l3->SetLineColor(kYellow);
  h_mc_tk_algo_fakes_l3->SetFillColor(kYellow);
  h_mc_tk_algo_fakes_l3->Draw("same");
  h_mc_tk_algo_fakesGT02_l3->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_algo_fakesGT02_l3->SetLineColor(kOrange);
  h_mc_tk_algo_fakesGT02_l3->SetFillColor(kOrange);
  h_mc_tk_algo_fakesGT02_l3->Draw("same");
  h_data_tk_algo_l3->SetMarkerStyle(20);
  h_data_tk_algo_l3->SetMarkerColor(kBlack);
  h_data_tk_algo_l3->Draw("esame");
  leg2->AddEntry(h_data_tk_algo_l3, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_tk_algo_l3, "MC", "f");
  leg2->AddEntry(h_mc_tk_algo_fakes_l3, "MC fakes", "f");
  leg2->Draw();
  myText.DrawLatex(5.,2000.,"CMS Preliminary");
  c2->SaveAs("photon_tk_algo_l3_data.eps");
  c2->SaveAs("photon_tk_algo_l3_data.png");




  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_tk_hits->SetTitle("");
  h_mc_tk_hits->GetXaxis()->SetTitle("Conversion track hits");
  h_mc_tk_hits->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_hits->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_hits->SetLineColor(kBlack);
  h_mc_tk_hits->SetFillColor(kGreen);
  h_mc_tk_hits->GetYaxis()->SetRangeUser(0.,120000.);
  h_mc_tk_hits->Draw();
  h_mc_tk_hits_fakes->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_hits_fakes->SetLineColor(kYellow);
  h_mc_tk_hits_fakes->SetFillColor(kYellow);
  h_mc_tk_hits_fakes->Draw("same");
  h_data_tk_hits->SetMarkerStyle(20);
  h_data_tk_hits->SetMarkerColor(kBlack);
  h_data_tk_hits->SetMaximum(2500);
  h_data_tk_hits->Draw("esame");
  leg2->AddEntry(h_data_tk_hits, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_tk_hits, "MC", "f");
  leg2->AddEntry(h_mc_tk_hits_fakes, "MC fakes", "f");
  leg2->Draw();
  myText.DrawLatex(5.,2000.,"CMS Preliminary");
  c2->SaveAs("photon_tk_hits_data.eps");
  c2->SaveAs("photon_tk_hits_data.png");



  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_tk_chi2->SetTitle("");
  h_mc_tk_chi2->GetXaxis()->SetTitle("Conversion track #chi^{2}");
  h_mc_tk_chi2->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_chi2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_chi2->SetLineColor(kBlack);
  h_mc_tk_chi2->SetFillColor(kGreen);
  //h_mc_tk_chi2->GetYaxis()->SetRangeUser(0.,5000.);
  h_mc_tk_chi2->Draw();
  h_mc_tk_chi2_fakes->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_chi2_fakes->SetLineColor(kYellow);
  h_mc_tk_chi2_fakes->SetFillColor(kYellow);
  h_mc_tk_chi2_fakes->Draw("same");
  h_data_tk_chi2->SetMarkerStyle(20);
  h_data_tk_chi2->SetMarkerColor(kBlack);
  h_data_tk_chi2->SetMaximum(2500);
  h_data_tk_chi2->Draw("esame");
  leg2->AddEntry(h_data_tk_chi2, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_tk_chi2, "MC", "f");
  leg2->AddEntry(h_mc_tk_chi2_fakes, "MC fakes", "f");
  leg2->Draw();
  myText.DrawLatex(2.,2400.,"CMS Preliminary");
  c2->SaveAs("photon_tk_chi2_data.eps");
  c2->SaveAs("photon_tk_chi2_data.png");



  TLegend *leg = new TLegend(0.60,0.65,0.80,.85); 
  leg->SetFillColor(kWhite);
  c2->cd();
  h_mc_tk_pt->SetTitle("");
  h_mc_tk_pt->GetXaxis()->SetTitle("Conversion track p_{T}");
  h_mc_tk_pt->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_pt->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt->SetLineColor(kBlack);
  h_mc_tk_pt->SetFillColor(kGreen);
  h_mc_tk_pt->GetXaxis()->SetRangeUser(0.,3.);
  // h_mc_tk_pt->GetYaxis()->SetRangeUser(0.,8000);
  h_mc_tk_pt->SetMinimum(9);
  h_mc_tk_pt->Draw();
  h_mc_tk_pt_fakes->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt_fakes->SetLineColor(kYellow);
  h_mc_tk_pt_fakes->SetFillColor(kYellow);
  h_mc_tk_pt_fakes->Draw("same");
  h_mc_tk_pt_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt_fakesGT02->SetLineColor(kOrange);
  h_mc_tk_pt_fakesGT02->SetFillColor(kOrange);
  // h_mc_tk_pt_fakesGT02->Draw("same");
  h_data_tk_pt->SetMarkerStyle(20);
  h_data_tk_pt->SetMarkerColor(kBlack);
  h_data_tk_pt->SetMaximum(2500);
  h_data_tk_pt->Draw("esame");
  leg->AddEntry(h_data_tk_pt, "7 TeV data", "pl");
  leg->AddEntry(h_mc_tk_pt, "MC", "f");
  leg->AddEntry(h_mc_tk_pt_fakes, "MC fakes", "f");
  leg->Draw();
  //  myText.DrawLatex(2.,2400.,"CMS Preliminary");
  c2->SaveAs("photon_tk_pt_data.eps");
  c2->SaveAs("photon_tk_pt_data.png");





  TLegend *leg = new TLegend(0.60,0.65,0.80,.85); 
  leg->SetFillColor(kWhite);
  c3->cd();
  h_mc_tk_pt1->SetTitle("");
  h_mc_tk_pt1->GetXaxis()->SetTitle("Conversion track p_{T} for PXL1");
  h_mc_tk_pt1->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_pt1->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt1->GetXaxis()->SetRangeUser(0.,2.);
  h_mc_tk_pt1->SetLineColor(kBlack);
  h_mc_tk_pt1->SetFillColor(kGreen);
  h_mc_tk_pt1->SetMinimum(9);
  h_mc_tk_pt1->Draw();
  h_mc_tk_pt1_fakes->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt1_fakes->SetLineColor(kYellow);
  h_mc_tk_pt1_fakes->SetFillColor(kYellow);
  h_mc_tk_pt1_fakes->Draw("same");
  h_mc_tk_pt1_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt1_fakesGT02->SetLineColor(kOrange);
  h_mc_tk_pt1_fakesGT02->SetFillColor(kOrange);
  h_mc_tk_pt1_fakesGT02->Draw("same");
  h_data_tk_pt1->SetMarkerStyle(20);
  h_data_tk_pt1->SetMarkerColor(kBlack);
  h_data_tk_pt1->SetMaximum(2500);
  h_data_tk_pt1->Draw("esame");
  leg->AddEntry(h_data_tk_pt1, "7 TeV data", "pl");
  leg->AddEntry(h_mc_tk_pt1, "MC", "f");
  leg->AddEntry(h_mc_tk_pt1_fakes, "MC fakes", "f");
  leg->Draw();
  myText.DrawLatex(2.,2400.,"CMS Preliminary");
  c3->SaveAs("photon_tk_pt1_data.eps");
  c3->SaveAs("photon_tk_pt1_data.png");


  TLegend *leg = new TLegend(0.60,0.65,0.80,.85); 
  leg->SetFillColor(kWhite);
  c3->cd();
  h_mc_tk_pt2->SetTitle("");
  h_mc_tk_pt2->GetXaxis()->SetTitle("Conversion track p_{T} for PXL2");
  h_mc_tk_pt2->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_pt2->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt2->SetLineColor(kBlack);
  h_mc_tk_pt2->SetFillColor(kGreen);
  h_mc_tk_pt2->SetMinimum(9);
  h_mc_tk_pt2->GetXaxis()->SetRangeUser(0.,2.);
  h_mc_tk_pt2->Draw();
  h_mc_tk_pt2_fakes->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt2_fakes->SetLineColor(kYellow);
  h_mc_tk_pt2_fakes->SetFillColor(kYellow);
  h_mc_tk_pt2_fakes->Draw("same");
  h_mc_tk_pt2_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt2_fakesGT02->SetLineColor(kOrange);
  h_mc_tk_pt2_fakesGT02->SetFillColor(kOrange);
  h_mc_tk_pt2_fakesGT02->Draw("same");
  h_data_tk_pt2->SetMarkerStyle(20);
  h_data_tk_pt2->SetMarkerColor(kBlack);
  h_data_tk_pt2->SetMaximum(2500);
  h_data_tk_pt2->Draw("esame");
  leg->AddEntry(h_data_tk_pt2, "7 TeV data", "pl");
  leg->AddEntry(h_mc_tk_pt2, "MC", "f");
  leg->AddEntry(h_mc_tk_pt2_fakes, "MC fakes", "f");
  leg->Draw();
  myText.DrawLatex(2.,2400.,"CMS Preliminary");
  c3->SaveAs("photon_tk_pt2_data.eps");
  c3->SaveAs("photon_tk_pt2_data.png");


  TLegend *leg = new TLegend(0.60,0.65,0.80,.85); 
  leg->SetFillColor(kWhite);
  c3->cd();
  h_mc_tk_pt3->SetTitle("");
  h_mc_tk_pt3->GetXaxis()->SetTitle("Conversion track p_{T} for PXL3");
  h_mc_tk_pt3->GetYaxis()->SetTitle("# of conversion tracks");
  h_mc_tk_pt3->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt3->SetLineColor(kBlack);
  h_mc_tk_pt3->SetFillColor(kGreen);
  h_mc_tk_pt3->GetXaxis()->SetRangeUser(0.,2.);
  h_mc_tk_pt3->SetMinimum(9);
  h_mc_tk_pt3->Draw();
  h_mc_tk_pt3_fakes->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt3_fakes->SetLineColor(kYellow);
  h_mc_tk_pt3_fakes->SetFillColor(kYellow);
  h_mc_tk_pt3_fakes->Draw("same");
  h_mc_tk_pt3_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_tk_pt3_fakesGT02->SetLineColor(kOrange);
  h_mc_tk_pt3_fakesGT02->SetFillColor(kOrange);
  h_mc_tk_pt3_fakesGT02->Draw("same");
  h_data_tk_pt3->SetMarkerStyle(20);
  h_data_tk_pt3->SetMarkerColor(kBlack);
  h_data_tk_pt3->SetMaximum(2500);
  h_data_tk_pt3->Draw("esame");
  leg->AddEntry(h_data_tk_pt3, "7 TeV data", "pl");
  leg->AddEntry(h_mc_tk_pt3, "MC", "f");
  leg->AddEntry(h_mc_tk_pt3_fakes, "MC fakes", "f");
  leg->Draw();
  myText.DrawLatex(2.,2400.,"CMS Preliminary");
  c3->SaveAs("photon_tk_pt3_data.eps");
  c3->SaveAs("photon_tk_pt3_data.png");





  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_d0->SetTitle("");
  h_mc_d0->GetXaxis()->SetTitle("d0*q");
  h_mc_d0->GetYaxis()->SetTitle("# of conversion tracks ");
  h_mc_d0->Scale((double)r2_use_entries/r1_use_entries);
  //h_mc_d0->GetYaxis()->SetRangeUser(0.,800.);
  h_mc_d0->SetLineColor(kBlack);
  h_mc_d0->SetFillColor(kGreen);
  h_mc_d0->Draw();
  h_mc_fakes_d0->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_fakes_d0->SetLineColor(kYellow);
  h_mc_fakes_d0->SetFillColor(kYellow);
  h_mc_fakes_d0->SetFillStyle(3001);
  h_mc_fakes_d0->Draw("same");
  hFile2->cd();
  h_mc_fakes_d0->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_fakes_d0->SetLineColor(kBlack);
  h_mc_fakes_d0->SetFillColor(kBlack);
  h_mc_fakes_d0->SetFillStyle(3017);
  leg2->AddEntry(h_mc_fakes_d0, "MC fakes: Ass by Pos ", "f");
  h_mc_fakes_d0->Draw("same");
  hFile->cd();
  h_data_d0->SetMarkerStyle(20);
  h_data_d0->SetMarkerColor(kBlack);
  h_data_d0->Draw("esame");
  leg2->AddEntry(h_data_d0, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_d0, "MC", "f");
  leg2->AddEntry(h_mc_fakes_d0, "MC fakes: Ass by Hits ", "f");
  leg2->Draw();
  myText.DrawLatex(0.7,370.,"CMS Preliminary");
  c2->SaveAs("photon_tk_d0_data.png");
  c2->SaveAs("photon_tk_d0_data.root");
  c2->SaveAs("photon_tk_d0_data.eps");


  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c3->cd();
  h_mc_d0_ext->SetTitle("");
  h_mc_d0_ext->GetXaxis()->SetTitle("d0*q");
  h_mc_d0_ext->GetYaxis()->SetTitle("# of conversion tracks ");
  h_mc_d0_ext->Scale((double)r2_use_entries/r1_use_entries);
  //h_mc_d0_ext->GetYaxis()->SetRangeUser(0.,1100.);
  h_mc_d0_ext->SetLineColor(kBlack);
  h_mc_d0_ext->SetFillColor(kGreen);
  h_mc_d0_ext->Draw();
  h_mc_fakes_d0_ext->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_fakes_d0_ext->SetLineColor(kYellow);
  h_mc_fakes_d0_ext->SetFillColor(kYellow);
  h_mc_fakes_d0_ext->SetFillStyle(3001);
  h_mc_fakes_d0_ext->Draw("same");
  hFile2->cd();
  h_mc_fakes_d0_ext->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_fakes_d0_ext->SetLineColor(kBlack);
  h_mc_fakes_d0_ext->SetFillColor(kBlack);
  h_mc_fakes_d0_ext->SetFillStyle(3017);
  leg2->AddEntry(h_mc_fakes_d0_ext, "MC fakes: Ass by Pos ", "f");
  h_mc_fakes_d0_ext->Draw("same");
  hFile->cd();
  h_data_d0_ext->SetMarkerStyle(20);
  h_data_d0_ext->SetMarkerColor(kBlack);
  h_data_d0_ext->Draw("esame");
  leg2->AddEntry(h_data_d0_ext, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_d0_ext, "MC", "f");
  leg2->AddEntry(h_mc_fakes_d0_ext, "MC fakes: Ass by Hits ", "f");
  leg2->Draw();
  myText.DrawLatex(1.5,370.,"CMS Preliminary");
  c3->SaveAs("photon_tk_d0_ext_data.png");
  c3->SaveAs("photon_tk_d0_ext_data.root");
  c3->SaveAs("photon_tk_d0_ext_data.eps");




  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_br_z_pixel->SetTitle("");
  h_mc_photon_br_z_pixel->GetXaxis()->SetTitle("Conversion radius (cm) for |z|< 26cm");
  h_mc_photon_br_z_pixel->GetYaxis()->SetTitle("Conversions/0.2 cm");
  h_mc_photon_br_z_pixel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_pixel->SetLineColor(kBlack);
  h_mc_photon_br_z_pixel->SetFillColor(kGreen);
  //h_mc_photon_br_z_pixel->GetYaxis()->SetRangeUser(0.,1500.);
  h_mc_photon_br_z_pixel->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_br_z_pixel->Draw();
  h_mc_photon_br_z_fakes_pixel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_fakes_pixel->SetLineColor(kYellow);
  h_mc_photon_br_z_fakes_pixel->SetFillColor(kYellow);
  h_mc_photon_br_z_fakes_pixel->Draw("same");
  h_data_photon_br_z_pixel->SetMarkerStyle(20);
  h_data_photon_br_z_pixel->SetMarkerColor(kBlack);
  h_data_photon_br_z_pixel->Draw("esame");
  leg2->AddEntry(h_data_photon_br_z_pixel, "Data", "pl");
  leg2->AddEntry(h_mc_photon_br_z_pixel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_z_fakes_pixel, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_r_z_pixel_data.png");
  c2->SaveAs("photon_r_z_pixel_data.root");
  c2->SaveAs("photon_r_z_pixel_data.eps");



  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c3->cd();
  h_mc_photon_br_z_barrel->SetTitle("");
  h_mc_photon_br_z_barrel->GetXaxis()->SetTitle("Conversion radius (cm) for |z|< 26cm");
  h_mc_photon_br_z_barrel->GetYaxis()->SetTitle("Conversions/0.2 cm");
  h_mc_photon_br_z_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_barrel->SetLineColor(kBlack);
  h_mc_photon_br_z_barrel->SetFillColor(kGreen);
  h_mc_photon_br_z_barrel->SetMinimum(9);
  //h_mc_photon_br_z_barrel->GetYaxis()->SetRangeUser(0.,1500.);
  //  h_mc_photon_br_z_barrel->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_br_z_barrel->Draw();
  h_mc_photon_br_z_fakes_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_fakes_barrel->SetLineColor(kYellow);
  h_mc_photon_br_z_fakes_barrel->SetFillColor(kYellow);
  h_mc_photon_br_z_fakes_barrel->SetFillStyle(3001);
  h_mc_photon_br_z_fakes_barrel->Draw("same");
  hFile2->cd();
  h_mc_photon_br_z_fakes_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_fakes_barrel->SetLineColor(kBlack);
  h_mc_photon_br_z_fakes_barrel->SetFillColor(kBlack);
  h_mc_photon_br_z_fakes_barrel->SetFillStyle(3017);
  leg2->AddEntry(h_mc_photon_br_z_fakes_barrel, "MC fakes: Ass by Pos ", "f");
  h_mc_photon_br_z_fakes_barrel->Draw("same");
  hFile->cd();
  h_data_photon_br_z_barrel->SetMarkerStyle(20);
  h_data_photon_br_z_barrel->SetMarkerSize(0.7);
  h_data_photon_br_z_barrel->SetMarkerColor(kBlack);
  h_data_photon_br_z_barrel->Draw("esame");
  leg2->AddEntry(h_data_photon_br_z_barrel, "Data", "pl");
  leg2->AddEntry(h_mc_photon_br_z_barrel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_z_fakes_barrel, "MC fakes: Ass by Hits ", "f");
  leg2->Draw();
  myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c3->SaveAs("photon_r_z_barrel_data.png");
  c3->SaveAs("photon_r_z_barrel_data.root");
  c3->SaveAs("photon_r_z_barrel_data.eps");


  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_br_z_barrel->SetTitle("");
  h_mc_photon_br_z_barrel->GetXaxis()->SetTitle("Conversion radius (cm) for |z|< 26cm");
  h_mc_photon_br_z_barrel->GetYaxis()->SetTitle("Conversions/0.2 cm");
  //h_mc_photon_br_z_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_barrel->SetLineColor(kBlack);
  h_mc_photon_br_z_barrel->SetFillColor(kGreen);
  h_mc_photon_br_z_barrel->SetMinimum(9);
  h_mc_photon_br_z_barrel->Draw();
  //  h_mc_photon_br_z_fakes_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_fakes_barrel->SetLineColor(kYellow);
  h_mc_photon_br_z_fakes_barrel->SetFillColor(kYellow);
  h_mc_photon_br_z_fakes_barrel->SetFillStyle(3001);
  h_mc_photon_br_z_fakes_barrel->Draw("same");
  hFile2->cd();
  //h_mc_photon_br_z_fakes_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_fakes_barrel->SetLineColor(kBlack);
  h_mc_photon_br_z_fakes_barrel->SetFillColor(kBlack);
  h_mc_photon_br_z_fakes_barrel->SetFillStyle(3017);
  leg2->AddEntry(h_mc_photon_br_z_fakes_barrel, "MC fakes: Ass by Pos ", "f");
  h_mc_photon_br_z_fakes_barrel->Draw("same");
  hFile->cd();
  h_data_photon_br_z_barrel->SetMarkerStyle(20);
  h_data_photon_br_z_barrel->SetMarkerSize(0.7);
  h_data_photon_br_z_barrel->SetMarkerColor(kBlack);
  h_data_photon_br_z_barrel->Draw("esame");
  leg2->AddEntry(h_data_photon_br_z_barrel, "Data", "pl");
  leg2->AddEntry(h_mc_photon_br_z_barrel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_z_fakes_barrel, "MC fakes: Ass by Hits ", "f");
  leg2->Draw();
  //myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  //myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_r_z_barrel_lin_data.png");
  c2->SaveAs("photon_r_z_barrel_lin_data.root");
  c2->SaveAs("photon_r_z_barrel_lin_data.eps");





  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c3->cd();
  h_mc_photon_br_z_barrel->SetTitle("");
  h_mc_photon_br_z_barrel->GetXaxis()->SetTitle("Conversion radius (cm) for |z|< 26cm");
  h_mc_photon_br_z_barrel->GetYaxis()->SetTitle("Conversions/0.2 cm");
  //h_mc_photon_br_z_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_barrel->SetLineColor(kBlack);
  h_mc_photon_br_z_barrel->SetFillColor(kGreen);
  h_mc_photon_br_z_barrel->SetMinimum(9);
  h_mc_photon_br_z_barrel->SetMaximum(1000);
  h_mc_photon_br_z_barrel->GetXaxis()->SetRangeUser(15.,40.);
  h_mc_photon_br_z_barrel->Draw();
  //  h_mc_photon_br_z_fakes_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_fakes_barrel->SetLineColor(kYellow);
  h_mc_photon_br_z_fakes_barrel->SetFillColor(kYellow);
  h_mc_photon_br_z_fakes_barrel->SetFillStyle(3001);
  h_mc_photon_br_z_fakes_barrel->Draw("same");
  hFile2->cd();
  //h_mc_photon_br_z_fakes_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_fakes_barrel->SetLineColor(kBlack);
  h_mc_photon_br_z_fakes_barrel->SetFillColor(kBlack);
  h_mc_photon_br_z_fakes_barrel->SetFillStyle(3017);
  leg2->AddEntry(h_mc_photon_br_z_fakes_barrel, "MC fakes: Ass by Pos ", "f");
  h_mc_photon_br_z_fakes_barrel->Draw("same");
  hFile->cd();
  h_data_photon_br_z_barrel->SetMarkerStyle(20);
  h_data_photon_br_z_barrel->SetMarkerSize(0.7);
  h_data_photon_br_z_barrel->SetMarkerColor(kBlack);
  h_data_photon_br_z_barrel->Draw("esame");
  leg2->AddEntry(h_data_photon_br_z_barrel, "Data", "pl");
  leg2->AddEntry(h_mc_photon_br_z_barrel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_z_fakes_barrel, "MC fakes: Ass by Hits ", "f");
  leg2->Draw();
  //myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  //myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c3->SaveAs("photon_r_z_barrel_zoom_data.png");
  c3->SaveAs("photon_r_z_barrel_zoom_data.root");
  c3->SaveAs("photon_r_z_barrel_zoom_data.eps");



  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_br_z_pixel_rebin->SetTitle("");
  h_mc_photon_br_z_pixel_rebin->GetXaxis()->SetTitle("Conversion radius (cm) for |z|< 26cm && r<20 cm plus |z|<66cm && r>=20 ");
  h_mc_photon_br_z_pixel_rebin->GetYaxis()->SetTitle("Conversions/0.8 cm");
  h_mc_photon_br_z_pixel_rebin->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_pixel_rebin->SetLineColor(kBlack);
  h_mc_photon_br_z_pixel_rebin->SetFillColor(kGreen);
  h_mc_photon_br_z_pixel_rebin->Draw();
  h_mc_photon_br_z_fakes_pixel_rebin->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_z_fakes_pixel_rebin->SetLineColor(kYellow);
  h_mc_photon_br_z_fakes_pixel_rebin->SetFillColor(kYellow);
  //  h_mc_photon_br_z_pixel_rebin->GetYaxis()->SetRangeUser(0.,60.);
  //h_mc_photon_br_z_pixel_rebin->GetYaxis()->SetRangeUser(0.,40.);
  h_mc_photon_br_z_fakes_pixel_rebin->Draw("same");
  h_data_photon_br_z_pixel_rebin->SetMarkerStyle(20);
  h_data_photon_br_z_pixel_rebin->SetMarkerColor(kBlack);
  h_data_photon_br_z_pixel_rebin->Draw("esame");
  leg2->AddEntry(h_data_photon_br_z_pixel_rebin, "Data", "pl");
  leg2->AddEntry(h_mc_photon_br_z_pixel_rebin, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_z_fakes_pixel_rebin, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_r_z_pixel_rebin_data.png");
  c2->SaveAs("photon_r_z_pixel_rebin_data.root");
  c2->SaveAs("photon_r_z_pixel_rebin_data.eps");



  TLegend *leg2 = new TLegend(0.10,0.65,0.30,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_z_pixel->SetTitle("");
  h_mc_photon_z_pixel->GetXaxis()->SetTitle("Conversion z (cm) for |z|>=28cm and r<=20cm");
  h_mc_photon_z_pixel->GetYaxis()->SetTitle("Conversions/0.2 cm");
  h_mc_photon_z_pixel->Scale((double)r2_use_entries_forw/r1_use_entries_forw);
  h_mc_photon_z_pixel->SetLineColor(kBlack);
  h_mc_photon_z_pixel->SetFillColor(kGreen);
  h_mc_photon_z_pixel->GetYaxis()->SetRangeUser(0.,1000.);
  // h_mc_photon_z_pixel->GetYaxis()->SetRangeUser(0.,200.);
  // h_mc_photon_z_pixel->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_z_pixel->Draw();
  h_mc_photon_z_pixel_fakes->Scale((double)r2_use_entries_forw/r1_use_entries_forw);
  h_mc_photon_z_pixel_fakes->SetLineColor(kYellow);
  h_mc_photon_z_pixel_fakes->SetFillColor(kYellow);
  h_mc_photon_z_pixel_fakes->SetFillStyle(3001);
  h_mc_photon_z_pixel_fakes->Draw("same");
  hFile2->cd();
  h_mc_photon_z_pixel_fakes->Scale((double)r2_use_entries_forw/r1_use_entries_forw);
  h_mc_photon_z_pixel_fakes->SetLineColor(kBlack);
  h_mc_photon_z_pixel_fakes->SetFillColor(kBlack);
  h_mc_photon_z_pixel_fakes->SetFillStyle(3017);
  leg2->AddEntry(h_mc_photon_z_pixel_fakes, "MC fakes: Ass by Pos ", "f");
  h_mc_photon_z_pixel_fakes->Draw("same");
  hFile->cd();
  h_data_photon_z_pixel->SetMarkerStyle(20);
  h_data_photon_z_pixel->SetMarkerSize(0.7);
  h_data_photon_z_pixel->SetMarkerColor(kBlack);
  h_data_photon_z_pixel->Draw("esame");
  leg2->AddEntry(h_data_photon_z_pixel, "Data", "pl");
  leg2->AddEntry(h_mc_photon_z_pixel, "MC", "f");
  leg2->AddEntry(h_mc_photon_z_pixel_fakes, "MC fakes: Ass by Hits ", "f");
  leg2->Draw();
  myText.DrawLatex(7,350,"CMS Preliminary ");
  myText.DrawLatex(7,300,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_z_pixel_data.png");
  c2->SaveAs("photon_z_pixel_data.root");
  c2->SaveAs("photon_z_pixel_data.eps");



  TLegend *leg2 = new TLegend(0.60,0.65,0.85,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_z->SetTitle("");
  h_mc_photon_z->GetXaxis()->SetTitle("Conversion z (cm) for |z|>=28cm");
  h_mc_photon_z->GetYaxis()->SetTitle("Conversions/0.2 cm");
  h_mc_photon_z->Scale((double)r2_use_entries_forw/r1_use_entries_forw);
  h_mc_photon_z->SetLineColor(kBlack);
  h_mc_photon_z->SetFillColor(kGreen);
  //h_mc_photon_z->GetYaxis()->SetRangeUser(0.,1200.);
  // h_mc_photon_z->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_z->Draw();
  h_mc_photon_z_fakes->Scale((double)r2_use_entries_allforw/r1_use_entries_allforw);
  h_mc_photon_z_fakes->SetLineColor(kYellow);
  h_mc_photon_z_fakes->SetFillColor(kYellow);
  h_mc_photon_z_fakes->Draw("same");
  h_data_photon_z->SetMarkerStyle(20);
  h_data_photon_z->SetMarkerSize(0.7);
  h_data_photon_z->SetMarkerColor(kBlack);
  h_data_photon_z->Draw("esame");
  leg2->AddEntry(h_data_photon_z, "Data", "pl");
  leg2->AddEntry(h_mc_photon_z, "MC", "f");
  leg2->AddEntry(h_mc_photon_z_fakes, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(7,350,"CMS Preliminary ");
  myText.DrawLatex(7,300,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_z_data.png");
  c2->SaveAs("photon_z_data.root");
  c2->SaveAs("photon_z_data.eps");






  TLegend *leg2 = new TLegend(0.10,0.65,0.30,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_z_flange->SetTitle("");
  h_mc_photon_z_flange->GetXaxis()->SetTitle("Conversion z (cm):  for 20<|z|<40cm &&  12<R<20 cm");
  h_mc_photon_z_flange->GetYaxis()->SetTitle("Conversions/0.2 cm");
  h_mc_photon_z_flange->Scale((double)r2_use_entries_forw2/r1_use_entries_forw2);
  h_mc_photon_z_flange->SetLineColor(kBlack);
  h_mc_photon_z_flange->SetFillColor(kGreen);
  //h_mc_photon_z_flange->GetYaxis()->SetRangeUser(0.,1200.);
  h_mc_photon_z_flange->GetXaxis()->SetRangeUser(20.,40.);
  h_mc_photon_z_flange->Draw();
  h_mc_photon_z_flange_fakes->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_z_flange_fakes->SetLineColor(kYellow);
  h_mc_photon_z_flange_fakes->SetFillColor(kYellow);
  h_mc_photon_z_flange_fakes->Draw("same");
  h_data_photon_z_flange->SetMarkerStyle(20);
  h_data_photon_z_flange->SetMarkerColor(kBlack);
  h_data_photon_z_flange->Draw("esame");
  leg2->AddEntry(h_data_photon_z_flange, "Data", "pl");
  leg2->AddEntry(h_mc_photon_z_flange, "MC", "f");
  leg2->AddEntry(h_mc_photon_z_flange_fakes, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(7,350,"CMS Preliminary ");
  myText.DrawLatex(7,300,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_z_flange_data.png");
  c2->SaveAs("photon_z_flange_data.root");
  c2->SaveAs("photon_z_flange_data.eps");




  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_br_z_pixel->SetTitle("");
  h_mc_photon_br_z_pixel->GetXaxis()->SetTitle("Conversion radius (cm) for |z|< 26cm");
  h_mc_photon_br_z_pixel->GetYaxis()->SetTitle("Conversions/0.2 cm");
  h_mc_photon_br_z_pixel->SetLineColor(kBlack);
  h_mc_photon_br_z_pixel->SetFillColor(kGreen);
  // h_mc_photon_br_z_pixel->GetYaxis()->SetRangeUser(0.,800.);
  h_mc_photon_br_z_pixel->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_br_z_pixel->Draw();
  h_mc_photon_br_z_fakes_pixel->SetLineColor(kYellow);
  h_mc_photon_br_z_fakes_pixel->SetFillColor(kYellow);
  h_mc_photon_br_z_fakes_pixel->Draw("same");
  h_data_photon_br_z_pixel_beampipe->SetMarkerStyle(20);
  h_data_photon_br_z_pixel_beampipe->SetMarkerColor(kBlack);
  h_data_photon_br_z_pixel_beampipe->Draw("esame");
  leg2->AddEntry(h_data_photon_br_z_pixel_beampipe, "Data", "pl");
  leg2->AddEntry(h_mc_photon_br_z_pixel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_z_fakes_pixel, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_r_z_pixel_data_beampipe.png");
  c2->SaveAs("photon_r_z_pixel_data_beampipe.root");
  c2->SaveAs("photon_r_z_pixel_data_beampipe.eps");




  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_br_etaz_pixel->SetTitle("");
  h_mc_photon_br_etaz_pixel->GetXaxis()->SetTitle("Conversion radius (cm) for  |#eta|<1.2 and |z|< 26cm");
  h_mc_photon_br_etaz_pixel->GetYaxis()->SetTitle("# of conversions");
  h_mc_photon_br_etaz_pixel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_etaz_pixel->SetLineColor(kBlack);
  h_mc_photon_br_etaz_pixel->SetFillColor(kGreen);
  h_mc_photon_br_etaz_pixel->GetXaxis()->SetRangeUser(0.,12.); 
  h_mc_photon_br_etaz_pixel->Draw();
  h_mc_photon_br_etaz_fakes_pixel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_etaz_fakes_pixel->SetLineColor(kYellow);
  h_mc_photon_br_etaz_fakes_pixel->SetFillColor(kYellow);
  h_mc_photon_br_etaz_fakes_pixel->Draw("same");
  h_data_photon_br_etaz_pixel->SetMarkerStyle(20);
  h_data_photon_br_etaz_pixel->SetMarkerColor(kBlack);
  h_data_photon_br_etaz_pixel->Draw("esame");
  leg2->AddEntry(h_data_photon_br_etaz_pixel, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_photon_br_etaz_pixel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_etaz_fakes_pixel, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_r_etaz_pixel_data.png");
  c2->SaveAs("photon_r_etaz_pixel_data.root");
  c2->SaveAs("photon_r_etaz_pixel_data.eps");


  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_br_eta_pixel->SetTitle("");
  h_mc_photon_br_eta_pixel->GetXaxis()->SetTitle("Conversion radius (cm) for |#eta|<1.2");
  h_mc_photon_br_eta_pixel->GetYaxis()->SetTitle("# of conversions");
  h_mc_photon_br_eta_pixel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_eta_pixel->SetLineColor(kBlack);
  h_mc_photon_br_eta_pixel->SetFillColor(kGreen);
  h_mc_photon_br_eta_pixel->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_br_eta_pixel->Draw();
  h_mc_photon_br_eta_fakes_pixel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_eta_fakes_pixel->SetLineColor(kYellow);
  h_mc_photon_br_eta_fakes_pixel->SetFillColor(kYellow);
  h_mc_photon_br_eta_fakes_pixel->Draw("same");
  h_data_photon_br_eta_pixel->SetMarkerStyle(20);

  h_data_photon_br_eta_pixel->SetMarkerColor(kBlack);
  h_data_photon_br_eta_pixel->Draw("esame");
  leg2->AddEntry(h_data_photon_br_eta_pixel, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_photon_br_eta_pixel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_eta_fakes_pixel, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_r_eta_pixel_data.png");
  c2->SaveAs("photon_r_eta_pixel_data.root");
  c2->SaveAs("photon_r_eta_pixel_data.eps");


  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c3->cd();
  h_mc_photon_br_eta_barrel->SetTitle("");
  h_mc_photon_br_eta_barrel->GetXaxis()->SetTitle("Conversion radius (cm) for |#eta|<1.2");
  h_mc_photon_br_eta_barrel->GetYaxis()->SetTitle("# of conversions");
  h_mc_photon_br_eta_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_eta_barrel->SetLineColor(kBlack);
  h_mc_photon_br_eta_barrel->SetFillColor(kGreen);
  h_mc_photon_br_eta_barrel->SetMinimum(9);
  //  h_mc_photon_br_eta_barrel->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_br_eta_barrel->Draw();
  h_mc_photon_br_eta_fakes_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_eta_fakes_barrel->SetLineColor(kYellow);
  h_mc_photon_br_eta_fakes_barrel->SetFillColor(kYellow);
  h_mc_photon_br_eta_fakes_barrel->Draw("same");
  h_data_photon_br_eta_barrel->SetMarkerStyle(20);
  h_data_photon_br_eta_barrel->SetMarkerSize(0.7);
  h_data_photon_br_eta_barrel->SetMarkerColor(kBlack);
  h_data_photon_br_eta_barrel->Draw("esame");
  leg2->AddEntry(h_data_photon_br_eta_barrel, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_photon_br_eta_barrel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_eta_fakes_barrel, "MC fakes ", "f");
  leg2->Draw();
  //  myText.DrawLatex(0.5,0.6,"CMS Preliminary ");
  // myText.DrawLatex(0.5,0.55,"#sqrt{s} = 7 TeV");
  c3->SaveAs("photon_r_eta_barrel_data.png");
  c3->SaveAs("photon_r_eta_barrel_data.root");
  c3->SaveAs("photon_r_eta_barrel_data.eps");


 TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c3->cd();
  h_mc_photon_br_eta_barrel->SetTitle("");
  h_mc_photon_br_eta_barrel->GetXaxis()->SetTitle("Conversion radius (cm) for |#eta|<1.2");
  h_mc_photon_br_eta_barrel->GetYaxis()->SetTitle("# of conversions");
  h_mc_photon_br_eta_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_eta_barrel->SetLineColor(kBlack);
  h_mc_photon_br_eta_barrel->SetFillColor(kGreen);
  //  h_mc_photon_br_eta_barrel->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_br_eta_barrel->Draw();
  h_mc_photon_br_eta_fakes_barrel->Scale((double)r2_use_entries/r1_use_entries);
  h_mc_photon_br_eta_fakes_barrel->SetLineColor(kYellow);
  h_mc_photon_br_eta_fakes_barrel->SetFillColor(kYellow);
  h_mc_photon_br_eta_fakes_barrel->Draw("same");
  h_data_photon_br_eta_barrel->SetMarkerStyle(20);
  h_data_photon_br_eta_barrel->SetMarkerSize(0.7);
  h_data_photon_br_eta_barrel->SetMarkerColor(kBlack);
  h_data_photon_br_eta_barrel->Draw("esame");
  leg2->AddEntry(h_data_photon_br_eta_barrel, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_photon_br_eta_barrel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_eta_fakes_barrel, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(0.5,0.6,"CMS Preliminary ");
  myText.DrawLatex(0.5,0.55,"#sqrt{s} = 7 TeV");
  c3->SaveAs("photon_r_eta_barrel_data_log.png");
  c3->SaveAs("photon_r_eta_barrel_data_log.root");
  c3->SaveAs("photon_r_eta_barrel_data_log.eps");





  TLegend *leg2 = new TLegend(0.60,0.65,0.80,.85); 
  leg2->SetFillColor(kWhite);
  c2->cd();
  h_mc_photon_br_eta_pixel->SetTitle("");
  h_mc_photon_br_eta_pixel->GetXaxis()->SetTitle("Conversion radius (cm) for |#eta|<1.2");
  h_mc_photon_br_eta_pixel->GetYaxis()->SetTitle("# of conversions");
  h_mc_photon_br_eta_pixel->SetLineColor(kBlack);
  h_mc_photon_br_eta_pixel->SetFillColor(kGreen);
  h_mc_photon_br_eta_pixel->GetXaxis()->SetRangeUser(0.,12.);
  h_mc_photon_br_eta_pixel->Draw();
  h_mc_photon_br_eta_fakes_pixel->SetLineColor(kYellow);
  h_mc_photon_br_eta_fakes_pixel->SetFillColor(kYellow);
  h_mc_photon_br_eta_fakes_pixel->Draw("same");
  h_data_photon_br_eta_pixel_beampipe->SetMarkerStyle(20);
  h_data_photon_br_eta_pixel_beampipe->SetMarkerColor(kBlack);
  h_data_photon_br_eta_pixel_beampipe->Draw("esame");
  leg2->AddEntry(h_data_photon_br_eta_pixel_beampipe, "7 TeV data", "pl");
  leg2->AddEntry(h_mc_photon_br_eta_pixel, "MC", "f");
  leg2->AddEntry(h_mc_photon_br_eta_fakes_pixel, "MC fakes ", "f");
  leg2->Draw();
  myText.DrawLatex(0.5,0.5,"CMS Preliminary ");
  myText.DrawLatex(0.5,0.45,"#sqrt{s} = 7 TeV");
  c2->SaveAs("photon_r_eta_pixel_data_beampipe.png");
  c2->SaveAs("photon_r_eta_pixel_data_beampipe.root");
  c2->SaveAs("photon_r_eta_pixel_data_beampipe.eps");



  c2->cd();
  hFile->cd();
  TH1F *h_fakeRateHits = new TH1F("h_fakeRateHits", "FakeRate vs R in barrel", 100, 0, 60.);
  TH1F *h_fakeRatePos = new TH1F("h_fakeRatePos", "FakeRate vs R in barrel", 100, 0, 60.);
  h_fakeRateHits->Divide(h_fakeRate_r_n,h_fakeRate_r_d, 1., 1., "b");
  h_fakeRateHits->GetXaxis()->SetTitle("Conversion radius R (cm)");
  h_fakeRateHits->GetYaxis()->SetTitle("FakeRate ");
  h_fakeRateHits->SetLineColor(kBlack);
  h_fakeRateHits->SetFillColor(kYellow);
  h_fakeRateHits->SetFillStyle(3001);
  h_fakeRateHits->Draw("");
  hFile2->cd();
  h_fakeRatePos->Divide(h_fakeRate_r_n,h_fakeRate_r_d, 1., 1., "b");
  h_fakeRatePos->SetLineColor(kBlack);
  h_fakeRatePos->SetFillColor(kBlack);
  h_fakeRatePos->SetFillStyle(3017);
  h_fakeRatePos->Draw("same");
  hFile->cd();
  c2->SaveAs("fakeRate_rg.eps");
  c2->SaveAs("fakeRate_rg.png");



  c2->cd();
  hFile->cd();
  TH1F *h_fakeRateHits = new TH1F("h_fakeRateHits", "FakeRate vs Eta", 100,-2.5, 2.5); 
  TH1F *h_fakeRatePos = new TH1F("h_fakeRatePos", "FakeRate vs Eta", 100,-2.5, 2.5); 
  h_fakeRateHits->Divide(h_fakeRate_eta_n,h_fakeRate_eta_d, 1.,1.,"b");
  h_fakeRateHits ->SetMinimum(0.);
  h_fakeRateHits ->GetXaxis()->SetTitle("Conversion #eta");
  h_fakeRateHits ->GetYaxis()->SetTitle("FakeRate ");
  h_fakeRateHits ->SetLineColor(kBlack);
  h_fakeRateHits ->SetFillColor(kYellow);
  h_fakeRateHits ->SetFillStyle(3001);
  h_fakeRateHits ->SetTitle("");
  h_fakeRateHits ->Draw();
  hFile2->cd();
  h_fakeRatePos->Divide(h_fakeRate_eta_n,h_fakeRate_eta_d, 1.,1.,"b");
  h_fakeRatePos->SetLineColor(kBlack);
  h_fakeRatePos->SetFillColor(kBlack);
  h_fakeRatePos->SetFillStyle(3017);
  h_fakeRatePos->SetTitle("");
  h_fakeRatePos->Draw("same");
  hFile->cd();
  c2->SaveAs("fakeRate_etag.eps");
  c2->SaveAs("fakeRate_etag.png");


  c2->cd();
  hFile->cd();
  TH1F *h_fakeRateHits = new TH1F("h_fakeRateHits", "FakeRate vs pt", 100,0., 25.);
  TH1F *h_fakeRatePos = new TH1F("h_fakeRatePos", "FakeRate vs pt", 100, 0., 25.); 
  h_fakeRateHits->Divide(h_fakeRate_pt_n,h_fakeRate_pt_d, 1.,1.,"b");
  h_fakeRateHits ->SetMinimum(0.);
  h_fakeRateHits ->GetXaxis()->SetTitle("Conversion Pt");
  h_fakeRateHits ->GetYaxis()->SetTitle("FakeRate ");
  h_fakeRateHits->GetXaxis()->SetRangeUser(0.,10.);
  h_fakeRateHits ->SetLineColor(kBlack);
  h_fakeRateHits ->SetFillColor(kYellow);
  h_fakeRateHits ->SetFillStyle(3001);
  h_fakeRateHits ->SetTitle("");
  h_fakeRateHits ->Draw();
  hFile2->cd();
  h_fakeRatePos->Divide(h_fakeRate_pt_n,h_fakeRate_pt_d, 1.,1.,"b");
  h_fakeRatePos->GetXaxis()->SetRangeUser(0.,10.);
  h_fakeRatePos->SetLineColor(kBlack);
  h_fakeRatePos->SetFillColor(kBlack);
  h_fakeRatePos->SetFillStyle(3017);
  h_fakeRatePos->SetTitle("");
  h_fakeRatePos->Draw("same");
  hFile->cd();
  c2->SaveAs("fakeRate_pt.eps");
  c2->SaveAs("fakeRate_pt.png");



  
  c2->cd();
  hFile->cd();
  TH1F *h_effHits = new TH1F("h_effHits", "Eff vs R", 100, 0, 60.);
  TH1F *h_effPos = new TH1F("h_effPos", "Eff vs R", 100, 0, 60.); 
  h_effHits->Divide(h_eff_r_n,h_eff_r_d);
  h_effHits->GetXaxis()->SetTitle("Conversion radius R (cm)");
  h_effHits->GetYaxis()->SetTitle("Efficiency in |#eta|<0.9");
  h_effHits->SetLineColor(kBlack);
  h_effHits->SetFillColor(kYellow);
  h_effHits->SetFillStyle(3001);
  h_effHits->SetTitle("");
  h_effHits->SetMinimum(0.);
  h_effHits->SetMaximum(0.1);
  //h_effHits->SetMaximum(0.02);
  h_effHits->Draw();
  hFile2->cd();
  h_effPos->Divide(h_eff_r_n,h_eff_r_d);
  h_effPos->SetLineColor(kBlack);
  h_effPos->SetFillColor(kBlack);
  h_effPos->SetFillStyle(3017);
  h_effPos->Draw("same");
  hFile->cd();
  c2->SaveAs("eff_rg.eps");
  c2->SaveAs("eff_rg.png");

  c2->cd();
  hFile->cd();
  TH1F *h_effHits = new TH1F("h_effHits", "Eff vs pt", 100, 0., 25.);
  TH1F *h_effPos = new TH1F("h_effPos", "Eff vs pt",    100, 0., 25.);
  h_effHits->Divide(h_eff_pt_n,h_eff_pt_d);
  h_effHits->GetXaxis()->SetTitle("Conversion p_{T} [GeV]");
  h_effHits->GetYaxis()->SetTitle("Efficiency");
  h_effHits->GetXaxis()->SetRangeUser(0.,10.);
  h_effHits->SetLineColor(kBlack);
  h_effHits->SetFillColor(kYellow);
  h_effHits->SetFillStyle(3001);
  h_effHits->SetTitle("");
  h_effHits->SetMinimum(0.);
  h_effHits->Draw();
  hFile2->cd();
  h_effPos->Divide(h_eff_pt_n,h_eff_pt_d);
  h_effPos->GetXaxis()->SetRangeUser(0.,10.);
  h_effPos->SetLineColor(kBlack);
  h_effPos->SetFillColor(kBlack);
  h_effPos->SetFillStyle(3017);
  h_effPos->Draw("same");
  hFile->cd();
  c2->SaveAs("eff_pt.eps");
  c2->SaveAs("eff_pt.png");

  c2->cd();
  hFile->cd();
  TH1F *h_effHits = new TH1F("h_effHits", "Eff vs Eta", 100,-2.5, 2.5);
  TH1F *h_effPos = new TH1F("h_effPos", "Eff vs Eta", 100,-2.5, 2.5);
  h_effHits->Divide(h_eff_eta_n,h_eff_eta_d);
  h_effHits->GetXaxis()->SetTitle("Conversion #eta");
  h_effHits->GetYaxis()->SetTitle("Efficiency");
  h_effHits->SetLineColor(kBlack);
  h_effHits->SetFillColor(kYellow);
  h_effHits->SetFillStyle(3001);
  h_effHits->SetTitle("");
  h_effHits->SetMinimum(0.);
  h_effHits->SetMaximum(0.024);
  //h_effHits->SetMaximum(0.01);
  h_effHits->Draw();
  hFile2->cd();
  h_effPos->Divide(h_eff_eta_n,h_eff_eta_d);
  h_effPos->SetLineColor(kBlack);
  h_effPos->SetFillColor(kBlack);
  h_effPos->SetFillStyle(3017);
  h_effPos->Draw("same");
  hFile->cd();
  c2->SaveAs("eff_eta.eps");
  c2->SaveAs("eff_eta.png");


  c2->cd();
  h2_data_tk_pt_l1->Draw();
  h2_data_tk_pt_l1->GetXaxis()->SetTitle("Track pt 1");
  h2_data_tk_pt_l1->GetYaxis()->SetTitle("Track pt 2");
  c2->SaveAs("data_pt1_vs_pt2_l1.eps");
  c2->SaveAs("data_pt1_vs_pt2_l1.png");

  c2->cd();
  h2_data_tk_pt_l2->Draw();
  h2_data_tk_pt_l2->GetXaxis()->SetTitle("Track pt 1");
  h2_data_tk_pt_l2->GetYaxis()->SetTitle("Track pt 2");
  c2->SaveAs("data_pt1_vs_pt2_l2.eps");
  c2->SaveAs("data_pt1_vs_pt2_l2.png");

  c2->cd();
  h2_data_tk_pt_l3->Draw();
  h2_data_tk_pt_l3->GetXaxis()->SetTitle("Track pt 1");
  h2_data_tk_pt_l3->GetYaxis()->SetTitle("Track pt 2");
  c2->SaveAs("data_pt1_vs_pt2_l3.eps");
  c2->SaveAs("data_pt1_vs_pt2_l3.png");


  c2->cd();
  h_mcTrue_tk1_vs_tk2_l1->Draw();
  h_mcTrue_tk1_vs_tk2_l1->GetXaxis()->SetTitle("Sim Track pt 1");
  h_mcTrue_tk1_vs_tk2_l1->GetYaxis()->SetTitle("Sim Track pt 2");
  c2->SaveAs("mcTruth_pt1_vs_pt2_l1.eps");
  c2->SaveAs("mcTruth_pt1_vs_pt2_l1.png");

  c2->cd();
  h_mcTrue_tk1_vs_tk2_l2->Draw();
  h_mcTrue_tk1_vs_tk2_l2->GetXaxis()->SetTitle("Sim Track pt 1");
  h_mcTrue_tk1_vs_tk2_l2->GetYaxis()->SetTitle("Sim Track pt 2");
  c2->SaveAs("mcTruth_pt1_vs_pt2_l2.eps");
  c2->SaveAs("mcTruth_pt1_vs_pt2_l2.png");

  c2->cd();
  h_mcTrue_tk1_vs_tk2_l3->Draw();
  h_mcTrue_tk1_vs_tk2_l3->GetXaxis()->SetTitle("Sim Track pt 1");
  h_mcTrue_tk1_vs_tk2_l3->GetYaxis()->SetTitle("Sim Track pt 2");
  c2->SaveAs("mcTruth_pt1_vs_pt2_l3.eps");
  c2->SaveAs("mcTruth_pt1_vs_pt2_l3.png");



  c2->cd();
  h_mcTrue_tkMinPt_vs_r->Draw("col");
  h_mcTrue_tkMinPt_vs_r->GetXaxis()->SetRangeUser(0.,60.);
  c2->SaveAs("mcTruth_tkMinPt_vs_r.eps");
  c2->SaveAs("mcTruth_tkMinPt_vs_r.png");
  c2->cd();
  h_mcTrue_tkMaxPt_vs_r->Draw("col");
  h_mcTrue_tkMaxPt_vs_r->GetXaxis()->SetRangeUser(0.,60.);
  c2->SaveAs("mcTruth_tkMaxPt_vs_r.eps");
  c2->SaveAs("mcTruth_tkMaxPt_vs_r.png");
  c2->cd();
  h_mcReco_tkMinPt_vs_r->Draw("col");
  h_mcReco_tkMinPt_vs_r->GetXaxis()->SetRangeUser(0.,60.);
  c2->SaveAs("mcReco_tkMinPt_vs_r.eps");
  c2->SaveAs("mcReco_tkMinPt_vs_r.png");
  c2->cd();
  h_mcReco_tkMaxPt_vs_r->Draw("col");
  h_mcReco_tkMinPt_vs_r->GetXaxis()->SetRangeUser(0.,60.);
  c2->SaveAs("mcReco_tkMaxPt_vs_r.eps");
  c2->SaveAs("mcReco_tkMaxPt_vs_r.png");



  c2->cd();
  h2_data_RvsZ->Draw();
  h2_data_RvsZ->GetXaxis()->SetTitle("Z (cm)");
  h2_data_RvsZ->GetYaxis()->SetTitle("R (cm)");
  c2->SaveAs("data_rz.png");

  c2->cd();
  h2_mc_RvsZ->Draw();
  h2_mc_RvsZ->GetXaxis()->SetTitle("Z (cm)");
  h2_mc_RvsZ->GetYaxis()->SetTitle("R (cm)");
  c2->SaveAs("mc_rz.png");

  c1->cd();
  h2_data_YvsXBarrelPix->Draw();
  h2_data_YvsXBarrelPix->GetXaxis()->SetTitle("X (cm)");
  h2_data_YvsXBarrelPix->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("data_xy_pixel.png");


  c1->cd();
  h2_data_YvsXBarrel->Draw();
  h2_data_YvsXBarrel->GetXaxis()->SetTitle("X (cm)");
  h2_data_YvsXBarrel->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("data_xy.png");

  c1->cd();
  h2_mc_YvsXBarrel->Draw();
  h2_mc_YvsXBarrel->GetXaxis()->SetTitle("X (cm)");
  h2_mc_YvsXBarrel->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("mc_xy.png");

  c1->cd();
  h2_mc_YvsXBarrel_fakes->Draw();
  h2_mc_YvsXBarrel_fakes->GetXaxis()->SetTitle("X (cm)");
  h2_mc_YvsXBarrel_fakes->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("mc_xy_fakes.png");



  c1->cd();
  h2_data_YvsXBarrel->GetXaxis()->SetRangeUser(-30.,30.);
  h2_data_YvsXBarrel->GetYaxis()->SetRangeUser(-30.,30.);
  h2_data_YvsXBarrel->Draw();
  h2_data_YvsXBarrel->GetXaxis()->SetTitle("X (cm)");
  h2_data_YvsXBarrel->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("data_xy_zoom.png");


  c1->cd();
  h2_mc_YvsXBarrel->GetXaxis()->SetRangeUser(-30.,30.);
  h2_mc_YvsXBarrel->GetYaxis()->SetRangeUser(-30.,30.);
  h2_mc_YvsXBarrel->Draw();
  h2_mc_YvsXBarrel->GetXaxis()->SetTitle("X (cm)");
  h2_mc_YvsXBarrel->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("mc_xy_zoom.png");


  c1->cd();
  h2_data_YvsXBarrelPix_eta->Draw();
  h2_data_YvsXBarrelPix_eta->GetXaxis()->SetTitle("X (cm)");
  h2_data_YvsXBarrelPix_eta->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("data_xy_pixel_eta.png");

  c1->cd();
  h2_data_YvsXBarrel_eta->Draw();
  h2_data_YvsXBarrel_eta->GetXaxis()->SetTitle("X (cm)");
  h2_data_YvsXBarrel_eta->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("data_xy_eta.png");

  c1->cd();
  h2_mc_YvsXBarrel_eta->Draw();
  h2_mc_YvsXBarrel_eta->GetXaxis()->SetTitle("X (cm)");
  h2_mc_YvsXBarrel_eta->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("mc_xy_eta.png");



  c1->cd();
  h2_data_YvsX_Z28_32->GetXaxis()->SetRangeUser(-18.,18.);
  h2_data_YvsX_Z28_32->GetYaxis()->SetRangeUser(-18.,18.);
  h2_data_YvsX_Z28_32->Draw();
  h2_data_YvsX_Z28_32->GetXaxis()->SetTitle("X (cm)");
  h2_data_YvsX_Z28_32->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("data_xy_Z28_32.png");


  c1->cd();
  h2_data_YvsX_ZLT110->Draw();
  h2_data_YvsX_ZLT110->GetXaxis()->SetTitle("X (cm)");
  h2_data_YvsX_ZLT110->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("data_xy_ZLT110.png");

  c1->cd();
  h2_data_YvsX_ZGT110->Draw();
  h2_data_YvsX_ZGT110->GetXaxis()->SetTitle("X (cm)");
  h2_data_YvsX_ZGT110->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("data_xy_ZGT110.png");


  c1->cd();
  h2_mc_YvsX_ZLT110->Draw();
  h2_mc_YvsX_ZLT110->GetXaxis()->SetTitle("X (cm)");
  h2_mc_YvsX_ZLT110->GetYaxis()->SetTitle("Y (cm)");
  h2_mc_YvsX_ZLT110->GetXaxis()->SetRangeUser(-30.,30.);
  h2_mc_YvsX_ZLT110->GetYaxis()->SetRangeUser(-30.,30.);
  c1->SaveAs("mc_xy_ZLT110.png");

  c1->cd();
  h2_mc_YvsX_ZGT110->Draw();
  h2_mc_YvsX_ZGT110->GetXaxis()->SetTitle("X (cm)");
  h2_mc_YvsX_ZGT110->GetYaxis()->SetTitle("Y (cm)");
  c1->SaveAs("mc_xy_ZGT110.png");















}
