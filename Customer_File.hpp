#ifndef Customer_File_hpp
#define Customer_File_hpp
#include "CSV_File.hpp"
#include "Customer_Master_File.hpp"

class Customer_File : public CSV_File {
  int firstname_size;
  int lastname_size;
public:
  // Creates header
  Customer_File(std::string filename);

  // Creates header and allows for file to create first and last names of different sizes
  Customer_File(std::string filename, int firstname_size, int lastname_size);

  // Generates the customer file from the Customer Master File
  void generate(Customer_Master_File &master);
};

#endif /* Customer_File_hpp */
