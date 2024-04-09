#include "Customer_Sample_File.hpp"
#include <vector>
#include <iostream>
#include <numeric>
#include <random>
#include <algorithm>

Customer_Sample_File::Customer_Sample_File(std::string filename) : CSV_File(filename), customer_code_size(30) {
  write_line("\"CUSTOMER_CODE\"\n");
}

void Customer_Sample_File::generate(int num_rows) {
  std::vector<int> available_code_nums(num_rows);
  std::iota(available_code_nums.begin(), available_code_nums.end(),0);
  std::shuffle(available_code_nums.begin(), available_code_nums.end(), std::mt19937 {std::random_device{}()});
  for(auto code_num : available_code_nums) {
    std::string CUSTOMER_CODE = "\"CUST";
    std::string customer_id = std::to_string(code_num);
    std::string zero_pad = "";
    for(int i = 0; i < customer_code_size - customer_id.size(); i++) {
      zero_pad += "0";
    }
    CUSTOMER_CODE += zero_pad + customer_id + "\"\n";
    write_line(CUSTOMER_CODE);
  }
}

std::unordered_set<std::string> Customer_Sample_File::extract_customers() {
  std::unordered_set<std::string> customers;
  for(int i = 1; i < num_rows; i++) {
    customers.insert(read_line(i));
  }
  return customers;
}
