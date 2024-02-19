{
  gStyle->SetOptStat(1111111);
  gStyle->SetOptFit(1111);

   if (0) {
      TString path = gSystem->GetDynamicPath();
      path.Append(":./processors:.");
      gSystem->SetDynamicPath(path);
      gSystem->Load("libuser");
      gSystem->Load("libCAT");
      gSystem->Load("libMinuit");
   }

   
   TCatCmdFactory *cf = TCatCmdFactory::Instance();
   cf->SetOptExactName(kFALSE);
   cf->Register(TCatCmdHelp::Instance());
   cf->Register(TCatCmdHt::Instance());
   cf->Register(TCatCmdHtp::Instance());
   cf->Register(TCatCmdHb::Instance());
   cf->Register(TCatCmdHn::Instance());
   cf->Register(TCatCmdZone::Instance());
   cf->Register(TCatCmdLs::Instance());
   cf->Register(TCatCmdCd::Instance());
   cf->Register(TCatCmdPrx::Instance());
   cf->Register(TCatCmdPry::Instance());
   cf->Register(TCatCmdAvx::Instance());
   cf->Register(TCatCmdAvy::Instance());
   cf->Register(TCatCmdBnx::Instance());
   cf->Register(TCatCmdBny::Instance());
   cf->Register(new TCatCmdLg(TCatCmdLg::kX, 0));
   cf->Register(new TCatCmdLg(TCatCmdLg::kX, 1));
   cf->Register(new TCatCmdLg(TCatCmdLg::kY, 0));
   cf->Register(new TCatCmdLg(TCatCmdLg::kY, 1));
   cf->Register(new TCatCmdLg(TCatCmdLg::kZ, 0));
   cf->Register(new TCatCmdLg(TCatCmdLg::kZ, 1));
   cf->Register(TCatCmdSly::Instance());
   cf->Register(TCatCmdLoopAdd::Instance());
   cf->Register(TCatCmdLoopResume::Instance());
   cf->Register(TCatCmdLoopSuspend::Instance());
   cf->Register(TCatCmdLoopTerminate::Instance());
   cf->Register(new TCatCmdHstore);
   cf->Register(TCatCmdXval::Instance());
   cf->Register(art::TCatCmdListg::Instance());
   //   cf->Register(art::TCmdMWDCCalib::Instance());
   //   cf->Register(art::TCmdMWDCConfig::Instance());
   //   cf->Register(new art::TCmdFiga);
   //   cf->Register(TCmdXsta::Instance());
   cf->Register(new art::TCmdBranchInfo);
   cf->Register(new art::TCmdClassInfo);
   cf->Register(new art::TCmdHdel);
   cf->Register(new art::TCmdFileCd);
   cf->Register(new art::TCmdFileLs);
   cf->Register(art::TCmdPn::Instance());
   cf->Register(art::TCmdPb::Instance());
   cf->Register(art::TCmdPcd::Instance());
   cf->Register(new art::TCmdRg(art::TCmdRg::kX));
   cf->Register(new art::TCmdRg(art::TCmdRg::kY));
   cf->Register(new art::TCmdRg(art::TCmdRg::kZ));
   cf->Register(new art::TCmdSlope);
   cf->Register(art::TCmdPn::Instance());
   cf->Register(art::TCmdPb::Instance());
   cf->Register(art::TCmdPcd::Instance());
   cf->Register(art::TCmdPadZoom::Instance());
   cf->Register(new art::TCmdProcessorDescription);
   cf->Register(new art::TCmdUnZoom);
   cf->Register(new art::TCmdComment);
   cf->Register(new art::TCmdGlobalComment);
   art::TCmdSave *cmdsave = art::TCmdSave::Instance();
   cmdsave->SetDefaultDirectory("figs");
   cmdsave->SetAddDateDir(kTRUE);
   cmdsave->SetAutoName(kTRUE);
   cmdsave->AddFormat("png");
   cmdsave->AddFormat("root");
   cmdsave->AddFormat("pdf", 1);
   cf->Register(cmdsave);
   art::TCmdPrint *pri = new art::TCmdPrint;
   pri->SetOption("-o fit-to-page");
  

   {
      TString path = gSystem->GetIncludePath();
      path.Append("-I./processors");
      gSystem->SetIncludePath(path);
   }
   {
      art::TModuleDecoderFactory *df = art::TModuleDecoderFactory::Instance();
// mod ID 0 : Fixed16
      const Int_t digits0 = 16;
      df->Register(new art::TModuleDecoderFixed<unsigned short>(0,digits0) );
// mod ID 1 : Fixed24
      const Int_t digits1 = 24;
      df->Register(new art::TModuleDecoderFixed<unsigned int>(1,digits1) );
// mod ID 21 : V7XX
      df->Register(new art::TModuleDecoderV7XX);
// mod ID 23 : V767
      df->Register(new art::TModuleDecoderV767);
// mod ID 24 : V1190
      df->Register(new art::TModuleDecoderV1190);
// mod ID 26 : V1190C
      df->Register(new art::TModuleDecoderSkip(26));
// mod ID 63 : V1740
      df->Register(new art::TModuleDecoderV1740);
      
//      TArtDecoderFactory *df = TArtDecoderFactory::Instance();
//      df->Register(TArtDecoderSIS3610::Instance());
//      df->Register(TArtDecoderSIS3820::Instance());
////      TArtDecoderV1190 *dc = (TArtDecoderV1190*)TArtDecoderV1190::Instance();
////      dc->SetTrailingChOffset(128);
////      df->Register(TArtDecoderV1190::Instance());
//      df->Register(new TCatDecoderV1190);
//      df->Register(TArtDecoderFixed16::Instance());
//      df->Register(TArtDecoderV7XX::Instance());
////      df->Register(TCatDecoderV1740::Instance());
   }
}
