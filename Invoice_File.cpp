#include "Invoice_File.hpp"
#include <unordered_set>
#include <numeric>
#include <random>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>

class Date {
  std::vector<std::string> months = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
  std::string month;
  std::string day;
  int year;
public:
  Date() {
    month = months[rand()%11];
    int day_val = rand()%28;
    if(day_val < 10) {
      day += '0';
    }
    day += std::to_string(day_val);
    year = rand()%1000 + 1024;
  }
  std::string get_string() {
    return day + "-" + month + "-" + std::to_string(year);
  }
};


Invoice_File::Invoice_File(std::string filename) : CSV_File(filename), customer_code_size(30), invoice_code_size(30) {
  std::string header = "\"CUSTOMER_CODE\",\"INVOICE_CODE\",\"AMOUNT\",\"DATE\"\n";
  write_line(header);
}

void Invoice_File::generate(Invoice_Master_File& invoice_codes, Customer_Master_File& customers) {
  for (int i = 1; i < invoice_codes.get_num_rows(); i++) {
    std::string CUSTOMER_CODE =  customers.read_line(rand()%(customers.get_num_rows() - 2) + 1);
    std::string INVOICE_CODE = invoice_codes.read_line(i);
    float amount = rand()%10000;
    Date date;
    std::string line = CUSTOMER_CODE + "," + INVOICE_CODE + ",\"" +
     std::to_string(amount) + "\",\""+ date.get_string() + "\"\n";
    write_line(line);
  }
}

void Invoice_File::generate(int num_invoices, int num_customers) {
  std::vector<int> available_code_nums(num_customers);
  std::iota(available_code_nums.begin(), available_code_nums.end(),0);
  std::shuffle(available_code_nums.begin(), available_code_nums.end(), std::mt19937 {std::random_device{}()});
  for (int i = 0; i < num_invoices; i++) {
    std::string CUSTOMER_CODE = "\"CUST";
    int code_num = available_code_nums[rand()%(num_customers-1)];
    std::string customer_id = std::to_string(code_num);
    std::string zero_pad = "";
    for(int i = 0; i < customer_code_size - customer_id.size(); i++) {
      zero_pad += "0";
    }
    CUSTOMER_CODE += zero_pad + customer_id + "\"";
    std::string INVOICE_CODE = "\"IN";
    std::string invoice_id = std::to_string(i);
    zero_pad = "";
    for(int i = 0; i < invoice_code_size - invoice_id.length(); i++) {
      zero_pad += '0';
    }
    INVOICE_CODE += zero_pad + invoice_id + "\"";
    float amount = rand()%10000;
    Date date;
    std::string line = CUSTOMER_CODE + "," + INVOICE_CODE + ",\"" +
     std::to_string(amount) + "\",\""+ date.get_string() + "\"\n";
    write_line(line);
  }
}

CSV_File Invoice_File::sample(Customer_Sample_File& customer_samples) {
  CSV_File sampled_invoices("smaller_invoice_file.csv");
  std::unordered_set<std::string> customers = customer_samples.extract_customers();
  std::string header = "\"CUSTOMER_CODE\",\"INVOICE_CODE\",\"AMOUNT\",\"DATE\"\n";
  sampled_invoices.write_line(header);
  for(int i = 1; i < num_rows; i++) {
    std::string line = read_line(i);
    std::stringstream ss(line);
    int line_idx = 0;
    std::string CUSTOMER_CODE = line.substr(0,line.find(","));
    if(customers.find(CUSTOMER_CODE) != customers.end()) {
      sampled_invoices.write_line(line + "\n");
    }
  }
  return sampled_invoices;
}

CSV_File Invoice_File::sample_fast(Customer_Sample_File& customer_samples) {
  CSV_File sampled_invoices("smaller_invoice_file.csv");
  std::unordered_set<std::string> customers = customer_samples.extract_customers();
  std::string header = "\"CUSTOMER_CODE\",\"INVOICE_CODE\",\"AMOUNT\",\"DATE\"\n";
  sampled_invoices.write_line(header);
  read_file_handle.open(filename);
  if(!read_file_handle.is_open()) {
    std::cerr << "/* file failed to open in Invoice_File::sample_fast */" << '\n';
  }

  bool is_header = true;
  std::string line;
  while(std::getline(read_file_handle, line)) {
    if(is_header) { // skip first line
      is_header = false;
    } else {
      std::stringstream ss(line);
      int line_idx = 0;
      std::string CUSTOMER_CODE = line.substr(0,line.find(","));
      if(customers.find(CUSTOMER_CODE) != customers.end()) {
        sampled_invoices.write_line(line + "\n");
      }
    }
  }
  read_file_handle.close();
  return sampled_invoices;
}
