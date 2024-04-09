#ifndef Invoice_Master_File_hpp
#define Invoice_Master_File_hpp
#include "CSV_File.hpp"

class Invoice_Master_File : public CSV_File {
  int invoice_code_size;
public:
  // Adds header "INVOICE_CODE"
  Invoice_Master_File(std::string filename);

  // Generates a file holding all invoices in record
  void generate(int num_rows);

};

#endif /* Invoice_Master_File_hpp */
