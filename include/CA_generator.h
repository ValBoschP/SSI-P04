#ifndef CA_GENERATOR_H
#define CA_GENERATOR_H

#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <iomanip>
#include <algorithm>

extern std::unordered_map<int, std::pair<int, int>> prn_taps;

class CAGenerator {
 public:
  CAGenerator() {
    g1_.fill(1);
    g2_.fill(1);
  }
  CAGenerator(const int& satellite_id) : satellite_id_(satellite_id) {
    g1_.fill(1);
    g2_.fill(1);
  }
  
  std::vector<int> GenerateSequence(int length, bool show_table = false);
  void ShifRegisters();
  std::pair<int, int> GetRandomTapsFromPRN();
  // Modificacion
  std::vector<int> GenerateSequenceRandom(int length, bool show_table);

  int GetSatelliteID() { return satellite_id_; }
  std::array <int, 10> GetG1() { return g1_; }
  std::array <int, 10> GetG2() { return g2_; }

  std::pair<int, int> GetTaps(int sat_id);

  void PrintLSFRState(int step);
  void PrintTableHeader();

 private:
  int satellite_id_;
  std::array<int, 10> g1_;
  std::array<int, 10> g2_;
};

#endif // CA_GENERATOR_H