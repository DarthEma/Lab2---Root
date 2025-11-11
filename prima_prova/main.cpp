#include "class.hpp"

int main() {
  ////*LAB 1*////

  prima_prova p;
  int Nextractions = 1e6;

  // punto 1 //
  p.set_parameters();
  p.draw_function();
  p.function_normalized();

  // punto 2 //

  p.random_extraction(Nextractions);
  p.normalize(Nextractions);
  p.draw_hist("function2.png");

  // punto 3.1 //

  p.compute_variance();

  // punto 3.2 //

  int Nhist = 100;
  bool is_rmss_computed = false;
  /*
      p.fill_histograms(Nextractions, Nhist, false);
      p.compute_unc(Nhist);
      std::cout << "select bin:" << '\n';
      int i;
      std::cin >> i;
      p.get_unc(i);

      is_rmss_computed = true;
  */
  // punto 3.3 //
  /*
    int Ntoy = 100;
    p.histo_from_function("histo.png");
    p.bin_smeering(Ntoy);
    std::cout << "select bin:" << '\n';
    int j;
    std::cin >> j;
    p.get_unc_smeering(j);
  */
  // punto 3.4 //
  /*
    p.fill_histograms(Nextractions, Nhist, true);
    p.compute_unc(Nhist);
    p.get_unc(i);
    p.bin_smeering(Ntoy);
    p.get_unc_smeering(j);
  */

  ////*LAB 2*////

  p.random_extraction(Nextractions);
  p.normalize(Nextractions);
  p.fit("fit.png");

  // quando faccio il fit, mi modifica il valore dei parametri della funzione f1

  /*per l'esecuzione di questo punto, necessario calcolare le rmss
  (in ciascun bin) nel punto 3.2 (necessarie fill_histograms e compute_unc)*/
  if (is_rmss_computed == false) {
    std::cout << "computing rmss now" << '\n';
    p.set_parameters();
    p.fill_histograms(Nextractions, Nhist, false);
    p.compute_unc(Nhist);
    p.get_unc(2);
  }

  p.compute_remainder();

  return 0;
}