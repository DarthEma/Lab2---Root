#include "class.hpp"

// g++ -std=c++17 -O2 main.cpp class.cpp $(root-config --cflags --libs) -o prova
// ./prova

void prima_prova::draw_function(const char* outPng1) {
  // TF1* f1 = new TF1("name", "pow(cos([0]*x + [1]), 2.0) + [2]",
  // -0.5, 5.5);
  f1->SetParameter(0, k);
  f1->SetParameter(1, phi);
  f1->SetParameter(2, b);
  f1->SetParameter(3, 1.0);
  TCanvas* C1 = new TCanvas("C1", "Distribuzione Teorica", 1200, 600);
  f1->Draw();
  C1->SaveAs(outPng1);
}

void prima_prova::function_normalized() {
  double integ = f1->Integral(0.0, 5.0);
  f1_norm->SetParameter(0, k);
  f1_norm->SetParameter(1, phi);
  f1_norm->SetParameter(2, b);
  f1_norm->SetParameter(3, (1.0 / integ));
}

void prima_prova::random_extraction(int Nextractions) {
  gRandom->SetSeed(0);
  for (int N{1}; N <= Nextractions; ++N) {
    h1->Fill(f1->GetRandom());
  }
}

void prima_prova::normalize(/*const char* outPng2*/ int Nextractions) {
  for (int N{1}; N <= Nbins; ++N) {
    double x = h1->GetBinContent(N);
    double y = (5.0 / Nbins) * Nextractions;
    h1->SetBinContent(N, (x / y));
  }
};

void prima_prova::draw_hist(const char* outPng2) {
  TCanvas* C2 = new TCanvas("C2", "Istogramma", 1200, 600);
  // TH1F* h1 = new TH1F("name", "estrazioni", Nbins, 0.0, 5.0);
  f1_norm->Draw();
  h1->Draw("sameHIST");
  C2->SaveAs(outPng2);
}

void prima_prova::compute_variance() {
  double rms;
  double somma{0};
  for (int N{1}; N <= Nbins; ++N) {
    double x = h1->GetBinCenter(N);
    double f1val = f1->Eval(x);
    double h1val = h1->GetBinContent(N);
    somma += pow(f1val - h1val, 2);
  }
  rms = sqrt(somma / Nbins);
  std::cout << "the rms is: " << rms << '\n';
}

//// METODI 3.2 ////

void prima_prova::fill_histograms(int Nextractions, int Nhist, bool err) {
  double area = (5.0 / Nbins) * Nextractions;
  histograms.resize(Nhist);
  gRandom->SetSeed(0);
  
  for (int H = 0; H < Nhist; ++H) {
    h1->Reset();
  
    if (err == true) {
    f1->SetParameter(0, gRandom->Gaus(k, k_var));
    f1->SetParameter(1, gRandom->Gaus(phi, phi_var));
    f1->SetParameter(2, gRandom->Gaus(b, b_var));
    f1->SetParameter(3, 1.0);
  }

    for (int N{1}; N <= Nextractions; ++N) {
      h1->Fill(f1->GetRandom());
    }

    histograms[H].clear();
    histograms[H].resize(Nbins);
    for (int bin = 1; bin <= Nbins; ++bin) {
      histograms[H][bin - 1] = ((h1->GetBinContent(bin)) / area);
    }
    if (histograms[H].size() != Nbins) {
      throw std::runtime_error{"filling has failed"};
    }
  }
  if (histograms.size() != Nhist) {
    throw std::runtime_error{"wrong number of histograms"};
  }
}

void prima_prova::compute_unc(int Nhist) {
  ibin.resize(Nbins);
  means.resize(Nbins);
  rmss.resize(Nbins);

  for (int i = 0; i < Nbins; ++i) {
    ibin[i].resize(Nhist);

    for (int k = 0; k < Nhist; ++k) {
      if (k >= (int)histograms.size() || i >= (int)histograms[k].size()) {
        std::cerr << "Errore dimensioni histograms\n";
        return;
      }

      ibin[i][k] = (histograms[k][i]);
    }

    means[i] = std::accumulate(ibin[i].begin(), ibin[i].end(), 0.0) / Nhist;
    double sum = 0.0;
    for (int k = 0; k < Nhist; ++k) {
      sum += pow((ibin[i][k] - means[i]), 2);
    }
    rmss[i] = sqrt(sum / (Nhist - 1));
  }
}

void prima_prova::get_unc(int i) {
  std::cout << "the mean value in bin " << i << " is: " << means[i] << '\n';
  std::cout << "and the rms is: " << rmss[i] << '\n';
}

//// METODI 3.3 ////

void prima_prova::histo_from_function(const char* outPng3) {
  for (int N = 1; N <= Nbins; ++N) {
    double inf = (N - 1) * 5.0 / 200;
    double sup = N * 5.0 / 200;
/*
    if (err == true) {
    f1_norm->SetParameter(0, gRandom->Gaus(k, k_var));
    f1_norm->SetParameter(1, gRandom->Gaus(phi, phi_var));
    f1_norm->SetParameter(2, gRandom->Gaus(b, b_var));
    /// eventualmente risettare il parametro 3
  }
*/
    double mean_func_val = (f1_norm->Integral(inf, sup)) / (sup - inf);
    h_f_f->SetBinContent(N, mean_func_val);
  }
  TCanvas* C3 = new TCanvas("C3", "istogramma teorico", 1200, 600);
  h_f_f->Draw();
  C3->SaveAs(outPng3);
};

void prima_prova::bin_smeering(int Ntoy) {
  gRandom->SetSeed(0);
  sim_val.resize(Nbins);
  means_smeering.resize(Nbins);
  rmss_smeering.resize(Nbins);

  for (int N = 1; N <= Nbins; ++N) {
    sim_val[N - 1].resize(Ntoy);
    double mean = h_f_f->GetBinContent(N);
    double variance = rmss[N - 1];

    for (int k = 0; k < Ntoy; ++k) {
      sim_val[N - 1][k] = gRandom->Gaus(mean, variance);  //////
    }

    means_smeering[N - 1] =
        std::accumulate(sim_val[N - 1].begin(), sim_val[N - 1].end(), 0.0) /
        Ntoy;
    double sum = 0.0;
    for (int k = 0; k < Ntoy; ++k) {
      sum += pow((sim_val[N - 1][k] - means_smeering[N - 1]), 2);
    }
    rmss_smeering[N - 1] = sqrt(sum / (Ntoy - 1));
  }
}

void prima_prova::get_unc_smeering(int i) {
  std::cout << "using the bin smeering method," << '\n';
  std::cout << "the mean value in bin " << i << " is: " << means_smeering[i]
            << '\n';
  std::cout << "and the rms is: " << rmss_smeering[i] << '\n';
}

/////// AREA DI LAVORO!!!!! ////////     /!\

