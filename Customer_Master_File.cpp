#include "Customer_Master_File.hpp"
#include <numeric>
#include <random>
#include <algorithm>
#include <queue>
#include <iostream>

Customer_Master_File::Customer_Master_File(std::string filename) : CSV_File(filename), customer_code_size(30) {
  write_line("\"CUSTOMER_CODE\"\n");
}

void Customer_Master_File::generate(int num_rows) {
  std::vector<int> available_code_nums(num_rows);
  std::iota(available_code_nums.begin(), available_code_nums.end(),0);
  std::shuffle(available_code_nums.begin(), available_code_nums.end(), std::mt19937 {std::random_device{}()});
  std::queue<int> code_num_queue;
  for(auto available_code : available_code_nums) {
    code_num_queue.push(available_code);
  }
  for(int i = 0; i < num_rows; i++) {
    std::string CUSTOMER_CODE = "\"CUST";
    int code_num = code_num_queue.front();
    code_num_queue.pop();
    std::string customer_id = std::to_string(code_num);
    std::string zero_pad = "";
    for(int i = 0; i < customer_code_size - customer_id.size(); i++) {
      zero_pad += "0";
    }
    CUSTOMER_CODE += zero_pad + customer_id + "\"\n";
    write_line(CUSTOMER_CODE);
  }
}

void Customer_Master_File::generate(Customer_Sample_File& seed, int num_rows) {
  int num_rows_in_seed = seed.get_num_rows();
  std::vector<int> available_code_nums((num_rows - num_rows_in_seed) + 1);
  std::iota(available_code_nums.begin(), available_code_nums.end(),num_rows_in_seed);
  std::shuffle(available_code_nums.begin(), available_code_nums.end(), std::mt19937 {std::random_device{}()});
  std::unordered_set<int> rows_reserved_for_seed;
  for(int i = 1; i < num_rows_in_seed; i++) {
    rows_reserved_for_seed.insert(rand()%(num_rows - 1) + 1);
  }

  std::unordered_set<std::string> seed_customers = seed.extract_customers();
  std::queue<std::string> seed_customers_queue;
  for(auto customer : seed_customers) {
    seed_customers_queue.push(customer);
  }

  std::queue<int> code_num_queue;
  for(auto available_code : available_code_nums) {
    code_num_queue.push(available_code);
  }

  for(int i = 0; i < num_rows; i++) {
    if(rows_reserved_for_seed.find(i) != rows_reserved_for_seed.end()) {
      std::string line = seed_customers_queue.front() + '\n';
      seed_customers_queue.pop();
      write_line(line);
    } else {
      std::string CUSTOMER_CODE = "\"CUST";
      int code_num = code_num_queue.front();
      code_num_queue.pop();
      std::string customer_id = std::to_string(code_num);
      std::string zero_pad = "";
      for(int i = 0; i < customer_code_size - customer_id.size(); i++) {
        zero_pad += "0";
      }
      CUSTOMER_CODE += zero_pad + customer_id + "\"\n";
      write_line(CUSTOMER_CODE);
    }
  }
}
