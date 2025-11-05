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
/*
  int Nhist = 100;
  p.fill_histograms(Nextractions, Nhist);
  p.compute_unc(Nhist);
  std::cout << "select bin:" << '\n';
  int i;
  std::cin >> i;
  p.get_unc(i);
*/

  int Ntoy = 100;
  p.histo_from_function("histo.png");
  p.bin_smeering(Ntoy);
  std::cout << "select bin:" << '\n';
  int i;
  std::cin >> i;
  p.get_unc_smeering(i);


  return 0;
}