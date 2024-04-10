#ifndef Invoice_Item_File_hpp
#define Invoice_Item_File_hpp
#include "CSV_File.hpp"
#include "Invoice_Master_File.hpp"

class Invoice_Item_File : public CSV_File {
  int item_code_size;
  int invoice_code_size;
public:
  // Write header
  Invoice_Item_File(std::string filename);

  Invoice_Item_File(std::string filename, int item_code_size);

  // generate invoice item file with num_invoices invoices
  void generate(int num_invoices, int total_num_invoice_items);

  // generate the invoice item file from the master invoice file until
  // total_num_invoice_items are generated. May repeat invioce codes.
  void generate(Invoice_Master_File &invoices, int total_num_invoice_items);

  // extract the invoice item file rows that correspond to the invoices that
  // were extracted into the smaller invoice file.
  CSV_File sample(CSV_File& smaller_invoice_file);

  // O(n) implementation of sample
  CSV_File sample_fast(CSV_File& smaller_invoice_file);
};


#endif /* Invoice_Item_File_hpp */
