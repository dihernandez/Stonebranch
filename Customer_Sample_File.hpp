#ifndef Customer_Sample_File_hpp
#define Customer_Sample_File_hpp
#include "CSV_File.hpp"
#include <unordered_set>

class Customer_Sample_File : public CSV_File {
  int customer_code_size;
public:

  // Default constructor, doesn't initialize anything.
  Customer_Sample_File();

  // Creates a customer sample file of name filename and writes header
  Customer_Sample_File(std::string filename);

  // Generates num_rows rows of CUSTOMER_CODEs. CUSTOMER_CODEs are assigned a
  // random unique value with a number between 0 and num_rows.
  void generate(int num_rows);

  // Initializes the Customer_Sample_File object to use an external file with the
  // provided external_filename.
  void pass_handle(std::string external_filename);

  // Goes line by line through the file and extracts all the customer codes as
  // a hash set of strings
  std::unordered_set<std::string> extract_customers();

};


#endif /* Customer_Sample_File_hpp */
