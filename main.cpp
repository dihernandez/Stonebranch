#include "CSV_File.hpp"
#include <iostream>


int main() {
  CSV_File test_csv_file("test.csv");
  test_csv_file.write_line("ENTRY1\n");
  std::cout << test_csv_file.read_line(0) << std::endl; // should output ENTRY1
  std::cout << test_csv_file.get_num_rows() << std::endl; // should return 1
  std::cout << test_csv_file.read_line(4) << std::endl; // should output row not found
}
