#ifndef CLASS_HPP
#define CLASS_HPP

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "TH1F.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TRandom3.h"

class prima_prova {
  TF1* f1 = new TF1("name", "(pow(cos([0]*x + [1]), 2.0) + [2])*[3]", -0.5, 5.5);
  int Nbins{200};
  // int Nextractions{1e5};
  TH1F* h1 = new TH1F("name", "estrazioni", Nbins, 0.0, 5.0);

 public:
  void draw_function(double k, double phi, double b,
                     const char* outPng1 = "function1.png");

  void random_extraction(int Nextractions);

  void normalize(const char* outPng2, int Nextractions);

  void compute_variance();
};

#endif