#ifndef CSV_File_hpp
#define CSV_File_hpp

#include <fstream>
#include <string>

class CSV_File{
protected:
  std::ofstream write_file_handle;
  std::ifstream read_file_handle;
  std::string filename;
  int num_rows;
public:
  // Takes a string filename and assigns it to filename
  CSV_File(std::string filename);

  // Takes an int indicating which line number to read from. 0th line is the header.
  // Returns the line at that row as a string.
  std::string read_line(int row_num);

  // Takes a string as a new entry into the file. Appends to end of file and increments
  // num_rows
  void write_line(std::string line);

  // return num_rows
  int get_num_rows();
};

#endif /* CSV_File_hpp */
