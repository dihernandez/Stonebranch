#ifndef Customer_Master_File_hpp
#define Customer_Master_File_hpp
#include "CSV_File.hpp"
#include "Customer_Sample_File.hpp"

class Customer_Master_File : public CSV_File {
  int customer_code_size;
public:
  // Creates a customer master file representing all the customer code data and
  // writes the header
  Customer_Master_File(std::string filename);

  // Generates a master file of CUSTOMER_CODEs of size num_rows
  void generate(int num_rows);

  // Takes a seed of CUSTOMER_CODEs in the form of a Customer_Sample_File and uses
  // it to generate a file of CUSTOMER_CODEs of total size num_rows.
  void generate(Customer_Sample_File& seed, int num_rows);
};

#endif
