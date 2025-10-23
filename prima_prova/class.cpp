#include "class.hpp"

// g++ -std=c++17 -O2 main.cpp class.cpp $(root-config --cflags --libs) -o prova
// ./prova

void prima_prova::draw_function(double k, double phi, double b,
                                const char* outPng1) {
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
  double integ = f1->Integral(0.0, 5.0);
  f1->SetParameter(3, (1.0 / integ));
  /*
    TCanvas* C2 = new TCanvas("C2", "Istogramma", 1200, 600);
    f1->Draw();
    h1->Draw("sameHIST");
    C2->SaveAs(outPng2);
    */
};

void prima_prova::draw_hist(const char* outPng2) {
  TCanvas* C2 = new TCanvas("C2", "Istogramma", 1200, 600);
  f1->Draw();
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

void prima_prova::riempi_masi(int Nextractions, int Nhist) {
  histograms.resize(Nhist);

  for (int H = 0; H < Nhist; H++) {
    gRandom->SetSeed(0);
    for (int N{1}; N <= Nextractions; ++N) {
      h1->Fill(f1->GetRandom());
    }

    histograms[H].resize(Nbins);

    for (int bin = 1; bin <= Nbins; ++bin) {
      histograms[H].push_back(h1->GetBinContent(bin));
    }
  }
}

void prima_prova::compute_unc(int Nhist) {

  ibin.resize(Nbins); 
  

  for (int i = 0; i < Nbins; ++i) {
    ibin[i].resize(Nhist);
    
    for (int k = 0; k < Nhist; ++k) {
      if (k >= (int)histograms.size() || i >= (int)histograms[k].size()) {
        std::cerr << "Errore dimensioni masi\n";
        return;
      }

      ibin[i].push_back(histograms[k][i]);
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
  std::cout << means[i];
  std::cout << rmss[i];
}

/*
  for (int i = 1; i <= Nbins; ++i ) {
    double sum = 0;

    for(int k = 0; k < Nhist; ++k) {
     sum += masi[k][i]
    }

    means[i] = sum / Nhist

    for (int j = 0; j < Nhist; ++j)
    {
    }
  }

  */

/*
void prima_prova::compare() {
  for (int N{1}; N <= Nbins; ++N) {
    double x = h1->GetBinCenter

  }
}
*/
/*

void draw_function(double k, double phi, double b,
                   const char* outPng = "function.png") {
  TF1* f1 = new TF1("name", "pow(cos([0]*x + [1]), 2.0) + [2]", -0.5, 5.5);
  f1->SetParameter(0, k);
  f1->SetParameter(1, phi);
  f1->SetParameter(2, b);
  TCanvas* C = new TCanvas("C", "Distribuzione Teorica", 1200, 600);
  f1->Draw();
  C->SaveAs(outPng);

  double a{0.0};
  double b{5.0};
  double max = f1->GetMaximum(a, b);
  int trials{0};
  int Nevents{3000};
  int Nbins{100};
  int N{0};
  std::vector<double> values;

      TRandom3 rnd(seed);

  while (N <= Nevents)
  {
    double x = rnd.Uniform(a, b);
    double y = rnd.Uniform(0.0, max);
    if(y <= (f1->Eval(x))) {
      values.push_back(y);
      ++N;
    }
  }




}

int main() {
  draw_function(5.2, 1.8, 0.2);
  return 0;
}

*/