#ifndef CLASS_HPP
#define CLASS_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "TH1F.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TRandom3.h"

class prima_prova {
  TF1* f1 = new TF1("name", "(pow(cos([0]*x + [1]), 2.0) + [2])*[3]", -0.5, 5.5);
  TF1* f1_norm = new TF1("name", "(pow(cos([0]*x + [1]), 2.0) + [2])*[3]", -0.5, 5.5);
  double k = 5.2;
  double phi = 1.8;
  double b = 0.2;
  int Nbins{200};
  // int Nextractions{1e5};

  // punto 3.2 //
  TH1F* h1 = new TH1F("name", "estrazioni", Nbins, 0.0, 5.0);
  std::vector<std::vector<double>> histograms;
  std::vector<double> means;
  std::vector<double> rmss;
  std::vector<std::vector<double>> ibin;

  // punto 3.3 //
  TH1F* h_f_f = new TH1F("name", "istogramma da funzione", Nbins, 0.0, 5.0);
  std::vector<std::vector<double>> sim_val;
  std::vector<double> means_smeering;
  std::vector<double> rmss_smeering;


 public:
  void draw_function(const char* outPng1 = "function1.png");

  void function_normalized();

  void random_extraction(int Nextractions);

  void normalize(int Nextractions);

  void draw_hist(const char* outPng2);

  void compute_variance();

  void fill_histograms(int Nextractions, int Nhist);

  void compute_unc(int Nhist);

  void get_unc(int i);

  void histo_from_function(const char* outPng3);

  void bin_smeering(int Ntoy);

  void get_unc_smeering(int i);
};

#endif