#include "Application.hpp"

Application::Application() :
  seed("default_seed_file.csv"),
  customer_master_file("default_customer_master_file.csv"),
  invoice_master_file("default_invoice_master_file.csv"),
  customer_file("default_customer_file.csv"),
  invoice_file("default_invoice_file.csv"),
  invoice_item_file("default_invoice_item_file.csv") {
    seed.generate(1000);
    customer_master_file.generate(seed,500000);
    invoice_master_file.generate(1000000);
    customer_file.generate(customer_master_file);
    invoice_file.generate(invoice_master_file, customer_master_file);
    invoice_item_file.generate(invoice_master_file, 5000000);
  }

  Application::Application(int num_seed, int num_customers, int num_invoices, int num_invoice_items) :
    seed("specified_seed_file.csv"),
    customer_master_file("specified_customer_master_file.csv"),
    invoice_master_file("specified_invoice_master_file.csv"),
    customer_file("specified_customer_file.csv"),
    invoice_file("specified_invoice_file.csv"),
    invoice_item_file("specified_invoice_item_file.csv") {
      seed.generate(num_seed);
      customer_master_file.generate(seed, num_customers);
      invoice_master_file.generate(num_invoices);
      customer_file.generate(customer_master_file);
      invoice_file.generate(invoice_master_file, customer_master_file);
      invoice_item_file.generate(invoice_master_file, num_invoice_items);
    }

SmallerFiles Application::extract_smaller_files(Customer_Sample_File &customer_samples) {
  SmallerFiles smaller_files;
  smaller_files.smaller_customer_file = customer_file.sample(customer_samples);
  smaller_files.smaller_invoice_file = invoice_file.sample(customer_samples);
  smaller_files.smaller_invoice_item_file = invoice_item_file.sample(smaller_files.smaller_invoice_file);
  return smaller_files;
}
