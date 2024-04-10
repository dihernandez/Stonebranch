#include "Invoice_Item_File.hpp"
#include <random>
#include <unordered_set>
#include <iostream>
#include <sstream>

Invoice_Item_File::Invoice_Item_File(std::string filename) : CSV_File(filename), item_code_size(30) {
  std::string header = "\"INVOICE_CODE\",\"ITEM_CODE\",\"AMOUNT\",\"QUANTITY\"\n";
  write_line(header);
}

Invoice_Item_File::Invoice_Item_File(std::string filename, int item_code_size) : CSV_File(filename), item_code_size(item_code_size) {
  std::string header = "\"INVOICE_CODE\",\"ITEM_CODE\",\"AMOUNT\",\"QUANTITY\"\n";
  write_line(header);
}

void Invoice_Item_File::generate(Invoice_Master_File &invoices, int total_num_invoice_items) {
  for(int i = 0; i < total_num_invoice_items; i++) {
    std::string INVOICE_CODE = invoices.read_line(rand()%(invoices.get_num_rows() - 2) + 1);
    std::string ITEM_CODE = "";
    for(int i = 0; i < item_code_size; i++) {
      char c = rand()%26 + 65; // uppercase
      ITEM_CODE += c;
    }
    float amount = rand()%100000;
    int quantity = rand()%100000;
    std::string line = INVOICE_CODE + ",\"" + ITEM_CODE +  "\",\"" + std::to_string(amount) +
     "\",\"" + std::to_string(quantity) + "\"\n";
     write_line(line);
  }
}

CSV_File Invoice_Item_File::sample(CSV_File& smaller_invoice_file) {
  CSV_File sampled_invoice_items("smaller_invoice_item_file.csv");
  std::string header = "\"INVOICE_CODE\",\"ITEM_CODE\",\"AMOUNT\",\"QUANTITY\"\n";
  sampled_invoice_items.write_line(header);
  std::unordered_set<std::string> invoice_codes;
  for(int i = 1; i < smaller_invoice_file.get_num_rows(); i++) {
    std::string line = smaller_invoice_file.read_line(i);
    std::stringstream ss(line);
    std::string INVOICE_CODE;
    int line_idx = 0;
    // get second index for invoice code
    while(std::getline(ss, INVOICE_CODE,',')) {
      if(line_idx == 1){
        break;
      }
      line_idx++;
    }
    invoice_codes.insert(INVOICE_CODE);
  }

  for(auto code : invoice_codes) {
    std::cout << code << std::endl;
  }

  for(int i = 1; i < num_rows; i++) {
    std::string line = read_line(i);
    std::string INVOICE_CODE = line.substr(0,line.find(","));
    if(invoice_codes.find(INVOICE_CODE) != invoice_codes.end()) {
      sampled_invoice_items.write_line(line + "\n");
    }
  }
  return sampled_invoice_items;
}
