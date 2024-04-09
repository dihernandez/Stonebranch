#include "Invoice_Master_File.hpp"

Invoice_Master_File::Invoice_Master_File(std::string filename) : CSV_File(filename), invoice_code_size(30) {
  write_line("\"INVOICE_CODE\"\n");
}

void Invoice_Master_File::generate(int num_rows) {
  for(int i = 0; i < num_rows; i++) {
    std::string INVOICE_CODE = "\"IN";
    std::string invoice_id = std::to_string(i);
    std::string zero_pad = "";
    for(int i = 0; i < invoice_code_size - invoice_id.length(); i++) {
      zero_pad += '0';
    }
    INVOICE_CODE += zero_pad + invoice_id + '\n';
    write_line(INVOICE_CODE);
  }
}
