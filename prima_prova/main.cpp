#include "class.hpp"

int main() {
  prima_prova p;
  int Nextractions = 1e6;
  p.draw_function(5.2, 1.8, 0.2);
  p.random_extraction(Nextractions);
  p.normalize(Nextractions);
  p.draw_hist("function2.png");
  p.compute_variance();

  int Nhist = 100;
  p.riempi_masi(Nextractions, Nhist);
  p.compute_unc(Nhist);
  std::cout << "select bin:" << '\n';
  int i;
  std::cin >> i;
  p.get_unc(i);

  return 0;
}