#include "CSV_File.hpp"
#include <iostream>
#include <filesystem>

CSV_File::CSV_File(){}

CSV_File::CSV_File(std::string filename) : filename(filename) {
  num_rows = 0;

  write_file_handle.open(filename); // create file
  if(!write_file_handle.is_open()) {
    std::cerr << "/* file failed to open in constructor */" << '\n';
  }
  write_file_handle.close();
}

std::ifstream* CSV_File::get_read_file_handle() {
  return &read_file_handle;
}


std::string CSV_File::read_line(int row_num) {
  read_file_handle.open(filename);
  if(!read_file_handle.is_open()) {
    std::cerr << "/* file failed to open in read_line */" << '\n';
  }
  int line_num = 0;
  std::string line;
  while(std::getline(read_file_handle, line)) {
    if(line_num == row_num) {
      break;
    }
    line_num++;
  }
  if(line == "") {
    std::cerr << "/* row " << row_num << " not found */" << '\n';
  }
  read_file_handle.close();
  return line;
}

void CSV_File::write_line(std::string line) {
  write_file_handle.open(filename, std::ios::app);
  if(!write_file_handle.is_open()) {
    std::cerr << "/* file failed to open in write_line */" << '\n';
  }
  write_file_handle << line;
  num_rows++;
  write_file_handle.close();
}

int CSV_File::get_num_rows() {
  return num_rows;
}

std::string CSV_File::get_filename() {
  return filename;
}
