double CalcMassExcessWB(int Zws, int Nws){

	int Aws = Zws + Nws;
	
	double bvol   = 15.67;
	double bsurf  = 17.23;
	double bCoul  = 0.714;
	double bsym   = 93.13;
	double bpair  = 11.2;
	
	double Evol  =  bvol  * Aws;
	double Esurf = -bsurf * TMath::Power(Aws,2./3.);
	double Ecoul = -bCoul * Zws * (Zws-1) * TMath::Power(Aws,-1./3.);
	double Esym  = -bsym  * TMath::Power(Nws-Zws,2.) / (4.0 * Aws);
	double Epair = 0;
	
	if ((Aws%2==0) && (Zws%2==0)){     Epair =  bpair * TMath::Power(Aws,-1./2.); }
	else if((Aws%2==0) && (Zws%2!=0)){ Epair = -bpair * TMath::Power(Aws,-1./2.); }

	double Bws = Evol + Esurf + Ecoul + Esym + Epair;
	
	return 938.782*Zws +  939.553*Nws - Bws ;
}

void DrawNuclearChart(){


	gROOT->ProcessLine("zone");
	TH2F *h2 = new TH2F("h2name", "h2title", 201, -0.5, 200.5, 201, -0.5, 200.5);

	for(int z=0;z<=200;z++){

		for(int n=0;n<=200;n++){

			TString IsotopeName = gAtomicMassTable->GetIsotopeName(z,z+n);
			
			if(IsotopeName.Sizeof()>1){

				double mass_ame = gAtomicMassTable->GetNucleusMass(z,z+n); 
				double mass_ws  = CalcMassExcessWB(z,n);
				double diffmass = mass_ame - mass_ws;
				h2->Fill(n,z,mass_ame);

			}
	
		}
	
	}

	h2->Draw("colz");
} 
