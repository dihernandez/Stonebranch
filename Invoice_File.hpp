#ifndef Invoice_File_hpp
#define Invoice_File_hpp
#include "CSV_File.hpp"
#include "Customer_Master_File.hpp"
#include "Invoice_Master_File.hpp"
#include "Customer_Sample_File.hpp"

class Invoice_File : public CSV_File {
  int customer_code_size;
  int invoice_code_size;
public:
  // Creates header
  Invoice_File(std::string filename);

  // Takes the set of invoice codes and customer codes and creates all the invoices
  // from the invoice codes mapped to a random selection form the customer codes.
  // warning: O(n^2)
  void generate(Invoice_Master_File &invoice_codes, Customer_Master_File &customer_codes);

  // Generates an invoice file with num_invoices invoices and num_customers customers
  void generate(int num_invoices, int num_customers);

  // Generates a smaller CSV_File of the invoices whose customer code from samples matches
  // the invoice's cusotmer code.
  CSV_File sample(Customer_Sample_File &customer_samples);

  // O(n) version of sample.
  CSV_File sample_fast(Customer_Sample_File &customer_samples);
};


#endif /* Invoice_File_hpp */
