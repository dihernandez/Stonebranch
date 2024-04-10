#ifndef Application_hpp
#define Application_hpp
#include "Customer_File.hpp"
#include "Invoice_File.hpp"
#include "Invoice_Item_File.hpp"
#include "Customer_Master_File.hpp"
#include "Invoice_Master_File.hpp"
#include "Customer_Sample_File.hpp"

struct SmallerFiles{
  CSV_File smaller_customer_file;
  CSV_File smaller_invoice_file;
  CSV_File smaller_invoice_item_file;
};

class Application {
  Customer_Master_File customer_master_file;
  Customer_File customer_file;
  Invoice_File invoice_file;
  Invoice_Item_File invoice_item_file;
  SmallerFiles smaller_files;
public:
  // Creates an application with default values of 500k customers in customer_master_file
  // and 1 million invoices in invoice_master_file as seeds and 5 million invoice items.
  Application();

  // Creates an application with specified num_customers customers in customer_master_file
  // and num_invoices in invoice_master_file and num_invoice_items in invoice_items file.
  Application(int num_customers, int num_invoices, int num_invoice_items);

  // Extracts all the smaller files based on customer_samples and returns a
  // struct containing handles to all the files.
  SmallerFiles* extract_smaller_files(Customer_Sample_File &customer_samples);

  // Extracts all the smaller files based on customer_samples creating smaller customer, invoice,
  // and invoice_items files.
  // void extract_smaller_files(Customer_Sample_File &customer_samples);
};

#endif /* Application_hpp */
