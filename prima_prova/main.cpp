#include "class.hpp"

int main() {
  prima_prova p;
  int Nextractions = 1e6;
  p.draw_function();
  p.function_normalized();
  p.random_extraction(Nextractions);
  p.normalize(Nextractions);
  p.draw_hist("function2.png");
  p.compute_variance();

  //// punto 3.2 ///

  int Nhist = 100;
  p.fill_histograms(Nextractions, Nhist, false);
  p.compute_unc(Nhist);
  std::cout << "select bin:" << '\n';
  int i;
  std::cin >> i;
  p.get_unc(i);

  //// punto 3.3 ///

  int Ntoy = 100;
  p.histo_from_function("histo.png");
  p.bin_smeering(Ntoy);
  std::cout << "select bin:" << '\n';
  int j;
  std::cin >> j;
  p.get_unc_smeering(j);

  //// punto 3.4 ////

  p.fill_histograms(Nextractions, Nhist, true);
  p.compute_unc(Nhist);
  p.get_unc(i);
  p.bin_smeering(Ntoy);
  p.get_unc_smeering(j);

  //// LAB 2 ////

  p.random_extraction(Nextractions);




  return 0;
}