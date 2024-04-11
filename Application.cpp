#include "Application.hpp"
#include <iostream>

Application::Application() :
  customer_master_file("default_customer_master_file.csv"),
  customer_file("default_customer_file.csv"),
  invoice_file("default_invoice_file.csv"),
  invoice_item_file("default_invoice_item_file.csv") {
    int num_customers = 500000;
    int num_invoices = 1000000;
    int num_invoice_items = 5000000;
    customer_master_file.generate(num_customers);
    customer_file.generate(customer_master_file);
    invoice_file.generate(num_invoices, num_customers);
    invoice_item_file.generate(num_invoices, num_invoice_items);
  }

  Application::Application(int num_customers, int num_invoices, int num_invoice_items) :
    customer_master_file("specified_customer_master_file.csv"),
    customer_file("specified_customer_file.csv"),
    invoice_file("specified_invoice_file.csv"),
    invoice_item_file("specified_invoice_item_file.csv") {
      customer_master_file.generate(num_customers);
      customer_file.generate(customer_master_file);
      invoice_file.generate(num_invoices, num_customers);
      invoice_item_file.generate(num_invoices, num_invoice_items);
    }

SmallerFiles* Application::extract_smaller_files(Customer_Sample_File &customer_samples) {
  smaller_files.smaller_customer_file = customer_file.sample_fast(customer_samples);
  smaller_files.smaller_invoice_file = invoice_file.sample_fast(customer_samples);
  smaller_files.smaller_invoice_item_file = invoice_item_file.sample_fast(smaller_files.smaller_invoice_file);
  return &smaller_files;
}

void Application::run_app() {
  std::cout << "Customer, Invoice, and Invoice Item files created. Enter integer to specify sample file size or enter Custom to pass in an input file that already exists.\n";
  int sample_size;
  std::string sample_size_str;
  std::cin >> sample_size_str;
  Customer_Sample_File custom_sample_file;
  bool use_custom_sample_file = false;
  Customer_Sample_File automatic_sample_file("sample_seed.csv");
  while(sample_size_str != "Custom" && !is_number(sample_size_str)) {
    std::cout << "Please enter either Custom or an integer value" << std::endl;
    std::cin >> sample_size_str;
  }
  if(sample_size_str == "Custom") {
    std::cout << "input filename" << std::endl;
    std::string input_file_name;
    std::cin >> input_file_name;
    custom_sample_file = create_customer_sample_file_from_existing_file(input_file_name);
    use_custom_sample_file = true;
  } else {
    sample_size = stoi(sample_size_str);
    automatic_sample_file.generate(sample_size);
  }
  std::cout << "Extracting files" << std::endl;
  SmallerFiles* smaller_files;
  if(use_custom_sample_file) {
    smaller_files = extract_smaller_files(custom_sample_file);
  } else {
    smaller_files = extract_smaller_files(automatic_sample_file);
  }
  std::cout << "smaller customer file has: " << smaller_files->smaller_customer_file.get_num_rows() << " rows" << std::endl;
  std::cout << "smaller invoice file has: " << smaller_files->smaller_invoice_file.get_num_rows() << " rows" << std::endl;
  std::cout << "smaller invoice item file has: " << smaller_files->smaller_invoice_item_file.get_num_rows() << " rows" << std::endl;
}

Customer_Sample_File Application::create_customer_sample_file_from_existing_file(std::string input_file_name) {
  std::ifstream existing_file;
  existing_file.open(input_file_name);
  while(!existing_file.is_open()) {
    std::cout << "file failed to open. Please enter a valid filename." << std::endl;
    std::cin >> input_file_name;
    existing_file.open(input_file_name);
  }
  Customer_Sample_File customer_sample_file;
  customer_sample_file.pass_handle(input_file_name);
  existing_file.close();
  return customer_sample_file;
}

bool Application::is_number(std::string input_str) {
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
