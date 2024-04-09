#include "CSV_File.hpp"
#include "Customer_Sample_File.hpp"
#include <iostream>
#include <cassert>

void test_CSV_File() {
  CSV_File test_csv_file("test_csv_file.csv");
  test_csv_file.write_line("ENTRY1\n");
  std::cout << test_csv_file.read_line(0) << std::endl; // should output ENTRY1
  assert(test_csv_file.get_num_rows() == 1);
  std::cout << test_csv_file.get_num_rows() << std::endl; // should return 1
  std::cout << test_csv_file.read_line(4) << std::endl; // should output row not found
}

void test_Customer_Sample_File() {
  int num_rows = 10;
  Customer_Sample_File test_cs_file("test_cs_file.csv");
  std::cout << test_cs_file.read_line(0) << std::endl; // should output "CUSTOMER_CODE"
  test_cs_file.generate(num_rows);
  int num_rows_read = test_cs_file.get_num_rows();
  assert(num_rows_read == num_rows + 1);
  std::cout << num_rows_read << std::endl;
  std::unordered_set<std::string> customers = test_cs_file.extract_customers();
  assert(customers.size() == num_rows_read - 1);
  for(auto customer : customers) {
    std::cout << customer << std::endl;
  }
}

int main() {
//  test_CSV_File();
  test_Customer_Sample_File();
}
