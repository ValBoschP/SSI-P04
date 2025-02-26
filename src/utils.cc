#include "CA_generator.h"
#include "utils.h"

enum class MenuOption { 
  Generate = 1, 
  ShowTable = 2, 
  RandomTaps = 3,
  Exit = 0
};

void ShowTable() {
  std::cout << "\nTabla de PRN y Taps:\n";
  std::cout << std::setw(10) << "PRN ID" << std::setw(10) << "G2 Taps" << "\n";
  std::cout << "-------------------------\n";
  for (const auto& [prn, taps] : prn_taps) {
    std::cout << std::setw(10) << prn << std::setw(6) << taps.first << " & " << taps.second << "\n";
  }
  std::cout << "\n";
}

void Menu() {
  int opcion, length;
  while (true) {
    std::cout << "\nMenú:\n";
    std::cout << "1. Generar secuencia C/A\n";
    std::cout << "2. Mostrar tabla de PRN y taps\n";
    std::cout << "3. Random Taps\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione una opción: ";
    std::cin >> opcion;
    if (opcion == static_cast<int>(MenuOption::Generate)) {
      int sat_id;
      std::cout << "Ingrese el ID del satélite (1-32): ";
      std::cin >> sat_id;
      if (sat_id < 1 || sat_id > 32) {
        std::cerr << "ID de satélite inválido. Debe estar entre 1 y 32.\n";
        continue;
      }
      std::cout << "Ingrese la longitud de la secuencia: ";
      std::cin >> length;
      CAGenerator generator(sat_id);
      generator.GenerateSequence(length, true);
    } else if (opcion == static_cast<int>(MenuOption::ShowTable)) {
      ShowTable();
    } else if (opcion == static_cast<int>(MenuOption::RandomTaps)) {
      CAGenerator generator;
      generator.GetRandomTapsFromPRN();
      std::cout << "Ingrese la longitud de la secuencia: ";
      std::cin >> length;
      generator.GenerateSequenceRandom(length, true);
    } else if (opcion == static_cast<int>(MenuOption::Exit)) {
      break;
    } else {
      std::cout << "Opción inválida, intente de nuevo.\n";
    }
  }
}