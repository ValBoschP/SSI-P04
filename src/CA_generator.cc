#include "CA_generator.h"
#include "utils.h"

std::unordered_map<int, std::pair<int, int>> prn_taps = {
  {1, {2, 6}}, {2, {3, 7}}, {3, {4, 8}}, {4, {5, 9}}, {5, {1, 9}},
  {6, {2, 10}}, {7, {1, 8}}, {8, {2, 9}}, {9, {3, 10}}, {10, {2, 3}},
  {11, {3, 4}}, {12, {5, 6}}, {13, {6, 7}}, {14, {7, 8}}, {15, {8, 9}},
  {16, {9, 10}}, {17, {1, 4}}, {18, {2, 5}}, {19, {3, 6}}, {20, {4, 7}},
  {21, {5, 8}}, {22, {6, 9}}, {23, {1, 3}}, {24, {4, 6}}, {25, {5, 7}},
  {26, {6, 8}}, {27, {7, 9}}, {28, {8, 10}}, {29, {1, 6}}, {30, {2, 7}},
  {31, {3, 8}}, {32, {4, 9}}
};

std::pair<int, int> CAGenerator::GetTaps(int sat_id) {
  return prn_taps[sat_id];
}

void CAGenerator::ShifRegisters() {
  int new_g1 = g1_[2] ^ g1_[9];
  int new_g2_ = g2_[1] ^ g2_[2] ^ g2_[5] ^ g2_[7] ^ g2_[8] ^ g2_[9];
  std::rotate(g1_.rbegin(), g1_.rbegin() + 1, g1_.rend());
  std::rotate(g2_.rbegin(), g2_.rbegin() + 1, g2_.rend());
  g1_[0] = new_g1;
  g2_[0] = new_g2_;
}

void CAGenerator::PrintTableHeader() {
  std::cout << "\nSalida:\n";
  std::cout << "Paso | G1         | G2        | C/A PRN\n";
  std::cout << "--------------------------------------\n";
}

void CAGenerator::PrintLSFRState(int step) {
  std::cout << std::setw(5) << step << " | ";
  for (int bit : g1_) std::cout << bit;
  std::cout << " | ";
  for (int bit : g2_) std::cout << bit;
}

std::vector<int> CAGenerator::GenerateSequence(int length, bool show_table) {
  std::vector<int> sequence;
  auto [tap1, tap2] = GetTaps(satellite_id_);
  if (show_table) PrintTableHeader();
  for (int i = 0; i < length; ++i) {
    int ca_bit = g1_[9] ^ (g2_[tap1 - 1] ^ g2_[tap2 - 1]);
    sequence.push_back(ca_bit);
    if (show_table) {
      PrintLSFRState(i);
      std::cout << " | " << ca_bit << "\n";
    }
    ShifRegisters();
  }
  return sequence;
}

