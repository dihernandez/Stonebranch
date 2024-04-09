#include "Invoice_Item_File.hpp"
#include <random>

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
