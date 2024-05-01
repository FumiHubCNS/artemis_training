void CalcHadron2BodyReactionTempl(Int_t imax=100000){

	TDatabasePDG* gPDGMassTable = new TDatabasePDG();
	// Create Tree and root
 	TFile *file = new TFile("./output/sim.hadron.2body.root", "RECREATE");
 	TTree *tree = new TTree("tree", "Data Tree");
 	
 	TArtParticle *fKmBeam     = NULL ;
 	
	TArtParticle *fLambdaCM   = NULL ;
 	TArtParticle *fPi0CM      = NULL ;
 	TArtParticle *fGamma1CM   = NULL ;
 	TArtParticle *fGamma2CM   = NULL ;
 	TArtParticle *fProCM      = NULL ;
 	TArtParticle *fPimCM      = NULL ;
	
	TArtParticle *fLambdaLab  = NULL ;
 	TArtParticle *fPi0Lab     = NULL ;
 	TArtParticle *fGamma1Lab  = NULL ;
 	TArtParticle *fGamma2Lab  = NULL ;
 	TArtParticle *fProLab     = NULL ;
 	TArtParticle *fPimLab     = NULL ;


	tree->Branch("BeamLab"   , &fKmBeam   );
	tree->Branch("LambdaCM"  , &fLambdaCM );
 	tree->Branch("Pi0CM"     , &fPi0CM    );
 	tree->Branch("Gamma1CM"  , &fGamma1CM );
 	tree->Branch("Gamma2CM"  , &fGamma2CM );
 	tree->Branch("ProtonCM"  , &fProCM    );
 	tree->Branch("PiMinusCM" , &fPimCM    );
	tree->Branch("LambdaLab" , &fLambdaLab);
 	tree->Branch("Pi0Lab"    , &fPi0Lab   );
 	tree->Branch("Gamma1Lab" , &fGamma1Lab);
 	tree->Branch("Gamma2Lab" , &fGamma2Lab);
 	tree->Branch("ProtonLab" , &fProLab   );
 	tree->Branch("PiMinusLab", &fPimLab   );

	//Generate Beam Particle
	TArtParticle *KmBeam = new TArtParticle();
	KmBeam->SetXYZM(0,0,1000.,gPDGMassTable->GetParticle("K-")->Mass()*1000.);
	
	for(Int_t i=0;i<imax;i++){
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//                                                                                                 //
		//  K- + p -> Λ + π0 -> γ + γ + p + π-                                                             //
		//                                                                                                 //
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		
		// Generate Pre Reaction Particle  K- + p with( K- + p ->[ M ]-> Lambda + pi0) reaction
		TArtParticle *KmPr_Km_S1CM = KmBeam;
		TArtParticle *KmPr_Pr1_S1CM = new TArtParticle();
		KmPr_Pr1_S1CM->SetKineticEnergy(0, gAtomicMassTable->GetNucleusMass(1,1));
		
		// Calculate Scattered Particle
		TLorentzVector KmPr_M0_LVec_S1CM = static_cast<TLorentzVector>(*KmPr_Km_S1CM) + static_cast<TLorentzVector>(*KmPr_Pr1_S1CM);
		TArtParticle *KmPr_M0_S1CM = new TArtParticle(KmPr_M0_LVec_S1CM.Vect(), KmPr_M0_LVec_S1CM.E() );
		KmPr_M0_S1CM->SetTwoBodyDecay(gPDGMassTable->GetParticle("Lambda0")->Mass()*1000.,gPDGMassTable->GetParticle("pi0")->Mass()*1000.);
		KmPr_M0_S1CM->Decay();
		
		//Get Scattered Particle 
		TArtParticle *KmPr_Lm_S1CM   = KmPr_M0_S1CM->GetDaughterAtRest(0);
		TArtParticle *KmPr_Pi0_S1CM  = KmPr_M0_S1CM->GetDaughterAtRest(1);
		TArtParticle *KmPr_Lm_S1Lab  = KmPr_M0_S1CM->GetDaughter(0);
		TArtParticle *KmPr_Pi0_S1Lab = KmPr_M0_S1CM->GetDaughter(1);
	
		//Calculate pi0 Decay
		TArtParticle *KmPr_M1_S2CM = new TArtParticle( KmPr_Pi0_S1CM->Vect(), KmPr_Pi0_S1CM->E() );
		KmPr_M1_S2CM->SetTwoBodyDecay(0.,0.);
		KmPr_M1_S2CM->Decay();
	
		TArtParticle *KmPr_Gamma1_S2CM = KmPr_M1_S2CM->GetDaughterAtRest(0); 
		TArtParticle *KmPr_Gamma2_S2CM = KmPr_M1_S2CM->GetDaughterAtRest(1);
		TArtParticle *KmPr_Gamma1_S1CM = KmPr_M1_S2CM->GetDaughter(0); 
		TArtParticle *KmPr_Gamma2_S1CM = KmPr_M1_S2CM->GetDaughter(1);
	
		TArtParticle *KmPr_Gamma1_S1Lab = new TArtParticle( KmPr_Gamma1_S1CM->Vect(), KmPr_Gamma1_S1CM->E() ); 
		TArtParticle *KmPr_Gamma2_S1Lab = new TArtParticle( KmPr_Gamma2_S1CM->Vect(), KmPr_Gamma2_S1CM->E() );
		
		KmPr_Gamma1_S1Lab->Boost( KmPr_M0_S1CM->BoostVector() );
		KmPr_Gamma2_S1Lab->Boost( KmPr_M0_S1CM->BoostVector() );
	
		//Calculate Lamda Decay
		TArtParticle *KmPr_M2_S3CM = new TArtParticle( KmPr_Lm_S1CM->Vect(), KmPr_Lm_S1CM->E() );
		KmPr_M2_S3CM->SetTwoBodyDecay( gAtomicMassTable->GetNucleusMass(1,1), gPDGMassTable->GetParticle("pi-")->Mass()*1000. );
		KmPr_M2_S3CM->Decay();
	
		TArtParticle *KmPr_Pr2_S3CM = KmPr_M2_S3CM->GetDaughterAtRest(0); 
		TArtParticle *KmPr_Pim_S3CM = KmPr_M2_S3CM->GetDaughterAtRest(1);
		TArtParticle *KmPr_Pr2_S1CM = KmPr_M2_S3CM->GetDaughter(0); 
		TArtParticle *KmPr_Pim_S1CM = KmPr_M2_S3CM->GetDaughter(1);
	
		TArtParticle *KmPr_Pr2_S1Lab = new TArtParticle( KmPr_Pr2_S1CM->Vect(), KmPr_Pr2_S1CM->E() ); 
		TArtParticle *KmPr_Pim_S1Lab = new TArtParticle( KmPr_Pim_S1CM->Vect(), KmPr_Pim_S1CM->E() );
		
		
		KmPr_Pr2_S1Lab->Boost( KmPr_M0_S1CM->BoostVector() );
		KmPr_Pim_S1Lab->Boost( KmPr_M0_S1CM->BoostVector() );
		
		fKmBeam    = KmPr_Km_S1CM;
		fLambdaCM  = KmPr_Lm_S1CM;
	 	fPi0CM     = KmPr_Pi0_S1CM;
	 	fGamma1CM  = KmPr_Gamma1_S1CM;
	 	fGamma2CM  = KmPr_Gamma2_S1CM;
	 	fProCM     = KmPr_Pr2_S1CM;
	 	fPimCM     = KmPr_Pim_S1CM;
		fLambdaLab = KmPr_Lm_S1Lab;
	 	fPi0Lab    = KmPr_Pi0_S1Lab;
	 	fGamma1Lab = KmPr_Gamma1_S1Lab;
	 	fGamma2Lab = KmPr_Gamma2_S1Lab;
	 	fProLab    = KmPr_Pr2_S1Lab;
	 	fPimLab    = KmPr_Pim_S1Lab;
	
		tree->Fill();
	
		delete KmPr_Pr1_S1CM;
		delete KmPr_M0_S1CM;
		delete KmPr_M1_S2CM;
		delete KmPr_Gamma1_S1Lab;
		delete KmPr_Gamma2_S1Lab;
		delete KmPr_M2_S3CM;
		delete KmPr_Pr2_S1Lab;
		delete KmPr_Pim_S1Lab;
		
	}
	
	tree->Write();
	file->Close();
	delete file;
	delete KmBeam;
}

