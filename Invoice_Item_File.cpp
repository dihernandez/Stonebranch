#include "Invoice_Item_File.hpp"
#include <random>
#include <unordered_set>
#include <iostream>
#include <sstream>

Invoice_Item_File::Invoice_Item_File(std::string filename) : CSV_File(filename), item_code_size(30), invoice_code_size(30) {
  std::string header = "\"INVOICE_CODE\",\"ITEM_CODE\",\"AMOUNT\",\"QUANTITY\"\n";
  write_line(header);
}

Invoice_Item_File::Invoice_Item_File(std::string filename, int item_code_size) : CSV_File(filename), item_code_size(item_code_size) {
  std::string header = "\"INVOICE_CODE\",\"ITEM_CODE\",\"AMOUNT\",\"QUANTITY\"\n";
  write_line(header);
}

void Invoice_Item_File::generate(int num_invoices, int total_num_invoice_items) {

  std::vector<int> available_code_nums(num_invoices);
  std::iota(available_code_nums.begin(), available_code_nums.end(),0);
  std::shuffle(available_code_nums.begin(), available_code_nums.end(), std::mt19937 {std::random_device{}()});

  for(int i = 0; i < total_num_invoice_items; i++) {
    std::string INVOICE_CODE = "\"IN";
    std::string invoice_id = std::to_string(available_code_nums[rand()%(num_invoices-1)]);
    std::string zero_pad = "";
    for(int i = 0; i < invoice_code_size - invoice_id.length(); i++) {
      zero_pad += '0';
    }
    INVOICE_CODE += zero_pad + invoice_id + "\"";
    std::string ITEM_CODE = "";
    for(int i = 0; i < item_code_size; i++) {
      char c = rand()%26 + 65; // uppercase
      ITEM_CODE += c;
    }
    float amount = rand()%10000000;
    int quantity = rand()%10000000;
    std::string line = INVOICE_CODE + ",\"" + ITEM_CODE +  "\",\"" + std::to_string(amount) +
     "\",\"" + std::to_string(quantity) + "\"\n";
     write_line(line);
  }
}

void Invoice_Item_File::generate(Invoice_Master_File &invoices, int total_num_invoice_items) {
  for(int i = 0; i < total_num_invoice_items; i++) {
    std::string INVOICE_CODE = invoices.read_line(rand()%(invoices.get_num_rows() - 2) + 1);
    std::string ITEM_CODE = "";
    for(int i = 0; i < item_code_size; i++) {
      char c = rand()%26 + 65; // uppercase
      ITEM_CODE += c;
    }
    float amount = rand()%10000000;
    int quantity = rand()%10000000;
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

  for(int i = 1; i < num_rows; i++) {
    std::string line = read_line(i);
    std::string INVOICE_CODE = line.substr(0,line.find(","));
    if(invoice_codes.find(INVOICE_CODE) != invoice_codes.end()) {
      sampled_invoice_items.write_line(line + "\n");
    }
  }
  return sampled_invoice_items;
}

CSV_File Invoice_Item_File::sample_fast(CSV_File& smaller_invoice_file) {
  CSV_File sampled_invoice_items("smaller_invoice_item_file.csv");
  std::string header = "\"INVOICE_CODE\",\"ITEM_CODE\",\"AMOUNT\",\"QUANTITY\"\n";
  sampled_invoice_items.write_line(header);
  std::unordered_set<std::string> invoice_codes;

  std::ifstream* smaller_invoice_read_file_handle = smaller_invoice_file.get_read_file_handle();
  smaller_invoice_read_file_handle->open(smaller_invoice_file.get_filename());
  if(!smaller_invoice_read_file_handle->is_open()) {
    std::cerr << "/* smaller invoice file failed to open in Invoice_Item_File::sample_fast */" << '\n';
  }

  bool is_header = true;
  std::string line;
  while(std::getline(*smaller_invoice_read_file_handle, line)) {
    if(is_header) {
      is_header = false;
      continue;
    }
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
  smaller_invoice_read_file_handle->close();
  for(auto code : invoice_codes) {
    //std::cout << code << std::endl;
  }

  read_file_handle.open(filename);
  if(!read_file_handle.is_open()) {
    std::cerr << "/* file failed to open in Invoice_Item_File::sample_fast */" << '\n';
  }

  is_header = true;
  while(std::getline(read_file_handle, line)) {
    if(is_header) {
      is_header = false;
      continue;
    }
    std::string INVOICE_CODE = line.substr(0,line.find(","));
    if(invoice_codes.find(INVOICE_CODE) != invoice_codes.end()) {
      sampled_invoice_items.write_line(line + "\n");
    }
  }
  read_file_handle.close();
  return sampled_invoice_items;
}
