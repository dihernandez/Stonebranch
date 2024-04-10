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
  smaller_files.smaller_customer_file = customer_file.sample(customer_samples);
  smaller_files.smaller_invoice_file = invoice_file.sample(customer_samples);
  smaller_files.smaller_invoice_item_file = invoice_item_file.sample(smaller_files.smaller_invoice_file);
  return &smaller_files;
}

// void Application::extract_smaller_files(Customer_Sample_File &customer_samples) {
//   customer_file.sample(customer_samples);
//   std::cout << "after creating smaller customer file \n";
//   CSV_File sampled_invoices = invoice_file.sample(customer_samples);
//   std::cout << "after creating smaller invoice file \n";
//   invoice_item_file.sample(sampled_invoices);
//   std::cout << "after creating smaller invoice item file \n";
// }
