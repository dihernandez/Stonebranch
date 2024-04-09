#include "Invoice_File.hpp"
#include <unordered_set>
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


Invoice_File::Invoice_File(std::string filename) : CSV_File(filename) {
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
    // while(std::getline(ss, CUSTOMER_CODE,',')) {
    //   if(line_idx == 1){
    //     break;
    //   }
    //   line_idx++;
    // }
    // std::cout << "customer code is " << CUSTOMER_CODE << std::endl;
    if(customers.find(CUSTOMER_CODE) != customers.end()) {
      sampled_invoices.write_line(line + "\n");
    }
  }
  return sampled_invoices;
}
