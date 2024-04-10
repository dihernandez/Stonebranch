#ifndef Customer_File_hpp
#define Customer_File_hpp
#include "CSV_File.hpp"
#include "Customer_Master_File.hpp"
#include "Customer_Sample_File.hpp"

class Customer_File : public CSV_File {
  int firstname_size;
  int lastname_size;
public:
  // Creates header
  Customer_File(std::string filename);

  // Copy constructor
  Customer_File(Customer_File &t) {
    firstname_size = t.firstname_size;
    lastname_size = t.lastname_size;
  }

  // Creates header and allows for file to create first and last names of different sizes
  Customer_File(std::string filename, int firstname_size, int lastname_size);

  // Generates the customer file from the Customer Master File
  void generate(Customer_Master_File &master);

  // Creates a file containing all the lines where CUSTOMER_CODE matches those in
  // the sample file (a Customer_Sample_File). Returns a CSV_File.
  CSV_File sample(Customer_Sample_File &customer_samples);
};

#endif /* Customer_File_hpp */
