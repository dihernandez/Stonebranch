#include "CSV_File.hpp"
#include "Customer_Sample_File.hpp"
#include "Customer_Master_File.hpp"
#include "Invoice_Master_File.hpp"
#include "Customer_File.hpp"
#include "Invoice_File.hpp"
#include "Invoice_Item_File.hpp"
#include "Application.hpp"
#include <iostream>
#include <cassert>

bool is_number(std::string input_str) {
  if (input_str.empty()) {
    return false;
  }
  for(auto ch : input_str) {
    try {
      if(!std::isdigit(ch)) {
        return false;
      }
    } catch(std::invalid_argument const& ex) {
      return false;
    }
  }
  return true;
}

void test_CSV_File() {
  CSV_File test_csv_file("test_csv_file.csv");
  test_csv_file.write_line("ENTRY1\n");
  std::cout << test_csv_file.read_line(0) << std::endl; // should output ENTRY1
  assert(test_csv_file.get_num_rows() == 1);
  std::cout << test_csv_file.get_num_rows() << std::endl; // should return 1
  std::cout << test_csv_file.read_line(4) << std::endl; // should output row not found
}

void test_Customer_Sample_File() {
  int num_rows = 10;
  Customer_Sample_File test_cs_file("test_cs_file.csv");
  std::cout << test_cs_file.read_line(0) << std::endl; // should output "CUSTOMER_CODE"
  test_cs_file.generate(num_rows);
  int num_rows_read = test_cs_file.get_num_rows();
  assert(num_rows_read == num_rows + 1);
  std::cout << num_rows_read << std::endl;
  std::unordered_set<std::string> customers = test_cs_file.extract_customers();
  assert(customers.size() == num_rows_read - 1);
  for(auto customer : customers) {
    std::cout << customer << std::endl;
  }
}

void test_Customer_Master_File() {
  int num_rows_master = 100;
  int num_rows_seed = 10;
  assert(num_rows_master > num_rows_seed);
  Customer_Sample_File test_cs_file("test_cs_file.csv");
  test_cs_file.generate(num_rows_seed);
  Customer_Master_File test_cm_file("test_cm_file.csv");
  std::cout << test_cm_file.read_line(0) << std::endl; // should output "CUSTOMER_CODE"
  //test_cm_file.generate(test_cs_file, num_rows_master);
  test_cm_file.generate(5000000);
}

Customer_Master_File generate_Customer_Master_File(int num_rows_master, Customer_Sample_File &samples) {
  int num_rows_seed = samples.get_num_rows();
  assert(num_rows_master > num_rows_seed);
  Customer_Master_File test_cm_file("test_cm_file.csv");
  test_cm_file.generate(samples, num_rows_master);
  return test_cm_file;
}

void test_Invoice_Master_File() {
    Invoice_Master_File test_im_file("test_im_file.csv");
    test_im_file.generate(10);
}

void test_Customer_File() {
  Customer_Sample_File test_cs_file("test_cs_file.csv");
  test_cs_file.generate(10);
  Customer_Master_File test_cm_file = generate_Customer_Master_File(100,test_cs_file);
  Customer_File test_customer_file("test_customer_file.csv",6,6);
  //std::cout << test_customer_file.get_num_rows() << std::endl;
  test_customer_file.generate(test_cm_file);
  CSV_File smaller_customer_file = test_customer_file.sample(test_cs_file);
}

void test_Invoice_File() {
  Invoice_File test_invoice_file("test_invoice_file.csv");
  Invoice_Master_File test_im_file("test_im_file.csv");
  test_im_file.generate(100);
  Customer_Sample_File test_cs_file("test_cs_file.csv");
  test_cs_file.generate(10);
  Customer_Master_File test_cm_file = generate_Customer_Master_File(100,test_cs_file);
  test_invoice_file.generate(test_im_file, test_cm_file);
  test_invoice_file.sample(test_cs_file);
}

void test_Invoice_Item_File() {
  Invoice_Item_File test_ii_file("test_ii_file.csv", 6);
  Invoice_File test_invoice_file("test_invoice_file.csv");
  Invoice_Master_File test_im_file("test_im_file.csv");
  test_im_file.generate(100);
  Customer_Sample_File test_cs_file("test_cs_file.csv");
  test_cs_file.generate(10);
  Customer_Master_File test_cm_file = generate_Customer_Master_File(100,test_cs_file);
  test_invoice_file.generate(test_im_file, test_cm_file);
  test_ii_file.generate(test_im_file, 500);
  CSV_File smaller_invoice_file = test_invoice_file.sample(test_cs_file);
  test_ii_file.sample(smaller_invoice_file);
}

void test_sample_fast() {
  int num_customers = 500000;
  int num_invoices = 1000000;
  int num_invoice_items = 5000000;
  int num_samples = 1000;
  Customer_Master_File test_cm_large_file("test_cm_large_file.csv");
  test_cm_large_file.generate(num_customers);
  Customer_File test_customer_large_file("test_customer_large_file.csv");
  test_customer_large_file.generate(test_cm_large_file);
  Customer_Sample_File test_cs_large_file("test_cs_large_file.csv");
  test_cs_large_file.generate(num_samples);
  CSV_File smaller_customer_file = test_customer_large_file.sample_fast(test_cs_large_file);
  std::cout << "smaller customer file has: " << smaller_customer_file.get_num_rows() << " rows " << std::endl;
  Invoice_File test_invoice_large_file("test_invoice_large_file.csv");
  test_invoice_large_file.generate(num_invoices,num_customers);
  CSV_File smaller_invoice_file = test_invoice_large_file.sample_fast(test_cs_large_file);
  std::cout << "smaller invoice file has: " << smaller_invoice_file.get_num_rows() << " rows " << std::endl;
  Invoice_Item_File test_ii_large_file("test_ii_large_file.csv");
  test_ii_large_file.generate(num_invoices, num_invoice_items);
  CSV_File smaller_invoice_item_file = test_ii_large_file.sample_fast(smaller_invoice_file);
  std::cout << "smaller invoice sample file has: " << smaller_invoice_item_file.get_num_rows() << " rows" << std::endl;
}

void test_Application_small() {
  //  Application default_app;
    Application customized(100,200,500);
    Customer_Sample_File sample_file("sample_seed.csv");
    sample_file.generate(10);
    SmallerFiles* smaller_files = customized.extract_smaller_files(sample_file);
    std::cout << "smaller customer file has: " << smaller_files->smaller_customer_file.get_num_rows() << " rows" << std::endl;
    std::cout << "smaller invoice file has: " << smaller_files->smaller_invoice_file.get_num_rows() << " rows" << std::endl;
    std::cout << "smaller invoice item file has: " << smaller_files->smaller_invoice_item_file.get_num_rows() << " rows" << std::endl;
}

void test_Application_large() {
//  Application default_app;
  Application large_app;
  Customer_Sample_File sample_file("sample_seed.csv");
  sample_file.generate(1000);
  large_app.extract_smaller_files(sample_file);
  SmallerFiles* smaller_files = large_app.extract_smaller_files(sample_file);
  std::cout << "smaller customer file has: " << smaller_files->smaller_customer_file.get_num_rows() << " rows" << std::endl;
  std::cout << "smaller invoice file has: " << smaller_files->smaller_invoice_file.get_num_rows() << " rows" << std::endl;
  std::cout << "smaller invoice item file has: " << smaller_files->smaller_invoice_item_file.get_num_rows() << " rows" << std::endl;
}

void test_pass_handle() {

  std::cout << "input filename" << std::endl;
  std::string input_file_name;
  std::cin >> input_file_name;
  Customer_Sample_File customer_sample_file;
  customer_sample_file.pass_handle("test_input_file.csv");
  std::cout << "input file has size " << customer_sample_file.get_num_rows() << '\n';
}

void run_app() {
  std::cout << "This app generates files of default sizes 500k entries for customer file, 1M entries for invoices, and 5M entries for invoice items." << std::endl;
  std::cout << "To use this app, enter Y to use default file sizes, N to continue to size selection." << std::endl;
  std::string default_selection;
  std::cin >> default_selection;
  while(default_selection != "Y" && default_selection != "N") {
    std::cout << "Please enter Y or N" << std::endl;
    std::cin >> default_selection;
  }
  if(default_selection == "Y") {
      Application large_app;
      large_app.run_app();
  } else if(default_selection == "N"){
    int customer_size;
    int invoice_size;
    int invoice_item_size;
    std::string customer_size_str;
    std::string invoice_size_str;
    std::string invoice_item_size_str;
    std::cout << "Enter an integer value for customer file size." << std::endl;
    std::cin >> customer_size_str;
    while(!is_number(customer_size_str)) {
      std::cout << "please enter a valid number" << std::endl;
      std::cin >> customer_size_str;
    }
    customer_size = stoi(customer_size_str);
    std::cout << "Enter an integer value for invoice file size." << std::endl;
    std::cin >> invoice_size_str;
    while(!is_number(invoice_size_str)) {
      std::cout << "please enter a valid number" << std::endl;
      std::cin >> invoice_size_str;
    }
    invoice_size = stoi(invoice_size_str);
    std::cout << "Enter an integer value for invoice item file size." << std::endl;
    std::cin >> invoice_item_size_str;
    while(!is_number(invoice_item_size_str)) {
      std::cout << "please enter a valid number" << std::endl;
      std::cin >> invoice_item_size_str;
    }
    invoice_item_size = stoi(invoice_item_size_str);
    Application custom_app(customer_size, invoice_size, invoice_item_size);
    custom_app.run_app();
  }
}

int main() {
//  test_CSV_File();
//  test_Customer_Sample_File();
//  test_Customer_Master_File();
//  test_Invoice_Master_File();
//  test_Customer_File();
//  test_Invoice_File();
  // test_Invoice_Item_File();
  //test_sample_fast();
  //test_Application_small();
  //test_Application_large();
  //test_pass_handle();
  run_app();
}
