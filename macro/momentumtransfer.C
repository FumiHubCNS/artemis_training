// Calculate Kinematics (Momentum Space)
// Reaction ( 1 + 2 -> 3 + 4)
//     Injection Particle : 1
//     Target Particle : 2
//     Scatterd Partcle : 3
//     Recoil Particle :4
// Input Parameter Description  
//     a1 : Mass Number for Injection Particle
//     z1 : Proton Number for Injection Particle
//     a2 : Mass Number for Target Particle
//     z2 : Proton Number for Target Particle
//     a3 : Mass Number for Scatterd Partcle
//     z3 : Proton Number for Scatterd Partcle
//     energyPerNucleon : Beam Energy (MeV/u)
//     exmin : Minimum Excitation Energy
//     exmax : Maximum Excitation Energy
//     estep : Calcultion Step for Excitation Energy
//     degmax : Maximum Angle in CM System
//
void momentumtransfer( Int_t a1, Int_t z1, Int_t a2, Int_t z2, Int_t a3, Int_t z3, 
                       Double_t energyPerNucleon, Double_t exmin, Double_t exmax, Double_t estep, Double_t degmax ){
  
  gROOT->ProcessLine("zone");
  TCatTwoBodyKinematics *relkin =  new TCatTwoBodyKinematics(a1, z1, a2, z2, a3, z3); 

  relkin->SetIncidentEnergy(energyPerNucleon);
  
  Int_t nEx = (exmax - exmin) / estep + 1;
  Int_t nQ = degmax*10+1;
  
  Double_t QStep = 0.1;
  Int_t nQLine = (nQ - 1) * QStep + 1;
  
  TGraph **grEx = new TGraph *[nEx];
  TGraph **grTh = new TGraph *[nQLine];
  
  for (Int_t iq = 0; iq != nQLine; iq++) {
    grTh[iq] = new TGraph(nEx);
  }
  
  for (Int_t iEx = 0; iEx != nEx; iEx++) {
    Double_t ex = iEx * estep + exmin;
    ex = (ex > exmax) ? exmax : ex; 
    relkin->SetExcitationEnergy(ex);
    const TArtParticle *recoil = relkin->GetParticle(3);
    grEx[iEx] = new TGraph(nQ);
    
    for (Int_t iq = 0; iq != nQ; iq++) {
      Double_t theta = iq * QStep;
      relkin->SetTheta(theta * TMath::DegToRad() );
      grEx[iEx]->SetPoint(iq, abs(recoil->Pz()/197.) , abs(recoil->Px()/197.));
    
      if (theta == int(theta)) {
        grTh[int(theta)]->SetPoint(iEx, abs(recoil->Pz()/197.), abs(recoil->Px()/197.));
      }   
    }   
  }
  
  if (gDirectory->Get("h")) {
    delete gDirectory->Get("h");
  }
  
  TH2F *h2 = new TH2F("h", "", 100, 0, 2.0, 100, 0, 2.0);
  h2->SetXTitle("q_{z} (fm^{-1})");
  h2->SetYTitle("q_{x} (fm^{-1})");
  h2->GetXaxis()->SetLabelFont(22);
  h2->GetXaxis()->SetTitleFont(22);
  h2->GetYaxis()->SetLabelFont(22);
  h2->GetYaxis()->SetTitleFont(22);

  h2->SetTitle(TString::Format("A=%d,Z=%d+A=%d,Z=%d => A=%d,Z=%d, Ex = %4.1f - %4.1f MeV, Kin = %6.1f MeV/u",
                               a1, z1, a2, z2, a3, z3, exmin, exmax, energyPerNucleon) );

  h2->SetStats(kFALSE);
  h2->Draw();
  
  for (Int_t iEx = 0; iEx < nEx; iEx++) {
    Double_t ex = iEx * estep + exmin;
    ex = (ex > exmax) ? exmax : ex; 
    
    if (int(ex / 10.) == int(ex) / 10.) {
      printf("%d %f\n", int(ex / 10.), int(ex) / 10.);
      grEx[iEx]->SetLineColor(kBlue);
      grEx[iEx]->SetLineWidth(2);
    }   
    
    grEx[iEx]->Draw("C");
  
  }

  for (Int_t iq = 0; iq < nQLine; iq++) {
    if ((iq % 5) == 0) {
      grTh[iq]->SetLineColor(kRed);
      grTh[iq]->SetLineWidth(2);
    }   
   
   grTh[iq]->Draw("C");
  
  }

}
