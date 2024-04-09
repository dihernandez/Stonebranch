/*
Input:
Customers Sample File (1000)
CUSTOMER_CODE | CHAR(30)
Present:
Customer.csv (500000)
CUSTOMER_CODE | CHAR(30)
FIRSTNAME | CHAR(100)
LASTNAME | CHAR(100)
Invoice.csv (1000000)
CUSTOMER_CODE | CHAR(30)
INVOICE_CODE | CHAR(30)
AMOUNT | FLOAT
DATE | DATE
Invoice_Item.csv (5000000)
INVOICE_CODE | CHAR(30)
ITEM_CODE | CHAR(30)
AMOUNT | FLOAT
QUANTITY | INTEGER
Output:
Customer.csv (1000)
CUSTOMER_CODE | CHAR(30)
FIRSTNAME | CHAR(100)
LASTNAME | CHAR(100)
Invoice.csv (1000)
CUSTOMER_CODE | CHAR(30)
INVOICE_CODE | CHAR(30)
AMOUNT | FLOAT
DATE | DATE
Invoice_Item.csv (1000)
INVOICE_CODE | CHAR(30)
ITEM_CODE | CHAR(30)
AMOUNT | FLOAT
QUANTITY | INTEGER
*/

/*
Classes:
CSV_File | a base class that holds a csv file handler,
fstream file
string filename
int num_rows // increment every time we add a line
string read_line(int n) // takes n as a line number and returns the line at that row
void write_line(string line) // write a line to table
takes a filename and opens the file

Customer_Sample_File : CSV_File
constructor writes header
constructor (int num_rows) {
  file.write(line row for row in num_rows)
}
unordered_map<string> extract_customers() {
  go line by line and extract all customer codes
  and return
}

Customer_Master_File : CSV_File
constructor{
  write header
}
void generate (Customer_Sample_File seed, int Y) {
  generate Y - seed.num_rows new rows and add them to file
}

Invoice_Master_File : CSV_File
constructor
  write header
  for i in num rows:
    string INVOICE_CODE // IN + 7 digit preceeded by zeros version of i
    write_line("\"IN\" +"\"INVOICE_CODE\"")

Customer_File : CSV_File
constructor creates header "\"CUSTOMER_CODE\",\"FIRSTNAME\",\"LASTNAME\""
void populate(Customer_Master_File master) {
  for(i in master.num_rows) {
  string CUSTOMER_CODE = master.get_line()
  string FIRSTNAME = generate 30 char rand string
  string LASTNAME = generate 30 char rand string
  write_line("\"CUSTOMER_CODE\",\"FIRSTNAME\",\"LASTNAME\"") // O(n^2)
}
}
CSV_File sample(Customer_Sample_File customer_samples) {
  unordered_map<string> customers = {extract all customers form customer_samples}
  CSV_File sampled_customers;
  while file.isopen:
    string line = getline()
    if line.split()[0] is in customers:
    sampled_customers.append(line);
  )

  return sampled_customers;
}

Invoice_File : CSV_File
constructor
  write header
void populate(Invoice_Master_File invoice_codes, Customer_Master_File customers) {
  for i in range(0, num_rows) {
    // skip header
    string CUSTOMER_CODE =  customers.get_line(rand%(customers.num_rows - 1))
    string INVOICE_CODE = invoice_codes.get_line(i)
    float amount = rand float %10000
    Date date(); // generate a random date object
    string date_str = "\"date.day-date.month-date.year\""
    write_line(CUSTOMER_CODE + INVOICE_CODE + amount + date)
}
}
CSV_File sample(Customer_Sample_File customer_samples) {
  CSV_File sampled_invoices;
  unordered_map<string> customers = customer_samples.extract_customers()
  line by line through current file:
    if line[1] in customers:
    sampled_invoices.write_line(line)
  return sampled_invoices;
}

Invoice_Item : CSV_File
constructor
  write header
void populate(Invoice_Master_File invoices) {
  for i in range 0 to num_rows :
    string INVOICE_CODE = invoices.get_line(rand%(invoices.num_rows-1))
    string ITEM_CODE = gen rand 30 char string
    float amount = random float up to 1000000
    int quantity = random int up to 1000000
    write_line(INVOICE_CODE + ITEM_CODE + amount + quantity)
}
CSV_File sample(CSV_File smaller_invoice_file) {
  CSV_File smaller_invoice_item_file;
  unordered_map<string> invoice_codes = extract smaller_invoice_file invoice invoice_codes
  for line in file:
    if line[0] in invoice_codes
    smaller_invoice_item_file.write_line(line)
  return smaller_invoice_item_file;
}

class Date
months = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}
string month;
string day
int year
constructor
choose a random month
choose a day between 1 and 28 and return as zero padded two digit string
choose a year between 1900 and 2024

struct SmallerFiles{
  CSV_File smaller_customer_file;
  CSV_File smaller_invoice_file;
  CSV_File smaller_invoice_item_file;
 }

Application
holds references to Customer, Invoice, and Invoice_Items, takes
a reference to Input, creates and holds field for Output
Customer_Master_File customer_master_file;
Invoice_Master_File invoice_master_file;
Customer_File customer_file;
Invoice_File invoice_file;
Invoice_Item_File invoice_item_file;
Application(int total_num_customers, int total_num_invoices, int num invoice_items) {
   // construct all files
}

SmallerFiles extract_smaller_files(Customer_Sample_File customer_samples) {
  SmallerFiles;
  SmallerFiles.smaller_customer_file = customer_file.sample(customer_samples);
  SmallerFiles.smaller_invoice_file = invoice_file.sample(customer_samples);
  SmallerFiles.smaller_invoice_item_file = invoice_item_file.sample(SmallerFiles.smaller_invoice_file);
  return SmallerFiles;
}


*/
