#include "Customer_File.hpp"

Customer_File::Customer_File(std::string filename) : CSV_File(filename), firstname_size(100), lastname_size(100) {
  std::string header = "\"CUSTOMER_CODE\",\"FIRSTNAME\",\"LASTNAME\"\n";
  write_line(header);
}

Customer_File::Customer_File(std::string filename, int firstname_size, int lastname_size) : CSV_File(filename), firstname_size(firstname_size), lastname_size(lastname_size) {
  std::string header = "\"CUSTOMER_CODE\",\"FIRSTNAME\",\"LASTNAME\"\n";
  write_line(header);
}

void Customer_File::generate(Customer_Master_File& master) {
  for(int i = 1; i < master.get_num_rows(); i++) {
    std::string CUSTOMER_CODE = master.read_line(i);
    std::string FIRSTNAME = "";
    for(int i = 0; i < firstname_size; i++) {
      char c;
      if(i == 0) {
        c = rand()%26 + 65; // uppercase
      } else {
        c = rand()%26 + 97; // lowercase
      }
      FIRSTNAME += c;
    }
    std::string LASTNAME = "";
    for(int i = 0; i < lastname_size; i++) {
      char c;
      if(i == 0) {
        c = rand()%26 + 65; // uppercase
      } else {
        c = rand()%26 + 97; // lowercase
      }
      LASTNAME += c;
    }
    std::string line = CUSTOMER_CODE + ",\"" + FIRSTNAME +"\",\"" + LASTNAME + "\"\n";
    write_line(line);
  }
}
