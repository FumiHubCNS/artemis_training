void GetDecayBranchFromPDG( const char* hname = "Lambda0")
{	
	TDatabasePDG* gPDGMassTable = new TDatabasePDG();
	TString HadronName = hname;
	TParticlePDG *ParentHadron = gPDGMassTable->GetParticle(HadronName.Data());
	Int_t NumOfDecayChannel = ParentHadron->NDecayChannels();
	
	std::cout << "  Parent Hadron : " << HadronName.Data() << ", Mass : " << ParentHadron->Mass()*1.e3 << "[MeV], Life Time : " << ParentHadron->Lifetime() << "[s]" << std::endl;

	for(Int_t i=0; i<NumOfDecayChannel; i++){

		TDecayChannel * DecayChannel = ParentHadron->DecayChannel(i);
		Double_t Val =  DecayChannel->BranchingRatio();
		Int_t NumOfDaughter = DecayChannel->NDaughters();

		std::cout << "    Decay Channel " << i << ", Branching Ratio : " << Val << ", Daughter List : "; 
		
		for(Int_t j=0; j<NumOfDaughter; j++){

			TParticlePDG *DaughterHadron = gPDGMassTable->GetParticle(DecayChannel->DaughterPdgCode(j));
			std::cout << DaughterHadron->GetName() << " " ;
		
		}

		std::cout << std::endl;
	}

}
