This application is designed to be used via the command line interface. The Makefile was written on OSX and uses gcc. The application takes about 5 minutes to run on a standard laptop if default file sizes are selected (those specified in the document).

The usage is: the user runs make and then ./output to run the program. The instructions will prompt the user to select **Y** to use the default file sizes for the generator and **N** for the user specified file size mode.

If **Y** is selected, a Customer File as specified in the document will be created and generated to hold 500K customers, an Invoice File will be created and generated to hold 1 million invoices, and an Invoice Item File will be created and generated to hold 5 million invoice items. The created files are called *default_customer_file.csv*, *default_invoice_file.csv*, and *default_invoice_item_file.csv*.

Otherwise, the application will prompt the user to enter the values for Customer File, Invoice File, and Invoice Item File sizes. The application will be created and the created files are called *specified_customer_file.csv*, *specified_invoice_file.csv*, and *specified_invoice_item_file.csv*.

The application will then prompt the user to enter a sample size or **Custom** or a number. The number must be a valid integer.

If a number is selected, the application will automatically generate the smaller files for each of Customer, Invoice, and Invoice Item files. If the sample size is bigger than any of the files then all of that file will be selected.

If **Custom** is selected, the application will prompt the user to enter a **filename**, which must be the name of an existing_file. The application will then use this file for extraction operations.

The application will print out the sizes of the files generated and exit. We can expect the smaller customer file to be about the same size as the sample size, the smaller invoice file to be representative of the relative size of the invoice file to the customer file, and the smaller invoice file size to be representative of the relative size of the invoice file to the invoice item file.

The files created are called *smaller_customer_file.csv*, *smaller_invoice_file.csv*, and *smaller_invoice_item_file.csv*. Smaller customer file holds all the entries in customer file whose customer code matches the customer code of the generated customer sample file. Smaller invoice file holds all the entries in invoice file whose customer code matches the customer code of the generated customer sample file, where there may be multiple invoices per customer code. Smaller invoice item file holds all the entries in the invoice item file whose invoice code matches the invoice codes present in *smaller_invoice_file.csv*.

The structure of my application is:

CSV_File
>a base class that handles file creation and writing. Exposes an ifstream handle to allow file reading via a getter method.

Customer_Master_File
>a child of CSV_File that generates all the customer codes to be used throughout the program.

Customer_Sample_File
>a child of CSV_File that generates all the customer codes that will be matched against for generating the samples. Has extract_customers() method which returns a hash set of strings containing all the customer codes that were generated.

Customer_File
>a child of CSV_File that generates a customer file as a csv file as specified in the document. Has a sample method that runs in O(n^2) time and a sample_fast method that runs in O(n) time.

Invoice_File
>a child of CSV_File that generates an invoice file as a csv file as specified in the document. Has a sample method that runs in O(n^2) time and a sample_fast method that runs in O(n) time.

Invoice_Item_File
>a child of CSV_File that generates an invoice item file as a csv file as specified in the document. Has a sample method that runs in O(n^2) time and a sample_fast method that runs in O(n) time.

Invoice_Master_File
>a legacy class, not used

Application
>A way to hold together instances of all the files necessary to run a sample operation on each file specified in the document.
>
>Creates all the files and runs samples on them when the extract_smaller_files method is called. This method returns a pointer to a struct containing CSV_Files that represent the smaller files created in the system.
>
>Has a run_app method, which runs the application.

main.cpp
>holds all the testing methods, which can be activated or deactivated in the main method by uncommenting or commenting the test names out. Used for incremental testing as the application was developed. By default, the run_app() method is activated, meaning that no tests will run but the application will run as described above.
