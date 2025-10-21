#include "class.hpp"

int main() {
  prima_prova p;
  int Nextractions = 1e6;
  p.draw_function(5.2, 1.8, 0.2);
  p.random_extraction(Nextractions);
  p.normalize("function2.png", Nextractions);
  p.compute_variance();
  return 0;
}