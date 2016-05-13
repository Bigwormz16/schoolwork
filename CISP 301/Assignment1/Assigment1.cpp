//  NAME  : Ian Rosner
//  CLASS : CISP 301, MW 2:00
//  PROGRAM TITLE : A Sample Payroll Program
//  Purpose: Assignment 1
//  Software Change(Modifications) Record
//  date         what              who
//  6/21/2007    Flush and Hold    Dixon
//	9/17/2012	 Tax, gross, net   Rosner
/*
    Program Design --> Data Design + Algorithm Design
    Data Design
    IPO Chart
    Input(s)           Processed               Output(s)
     (givens)            (derived)              (reported)
    =========          ===========             ===========
    lastName(s)         gross(f)                all Input(s)     
    firstName(s)        tax(f)                  all derive(s)       
    hours(f)            net(f)
    payrate(f)          fullName
    
    There are ONLY four(4) fundamental design data types:
          (s) string, (c) character, (i) integer, (f) real--> float point                                      
*/
#include  <stdio.h>
#include <string>
#define addr(var) &var
#define REPORTHEADING1 "     Employee               Pay           Hours     Gross     Tax        Net  \n"
#define REPORTHEADING2 "     Name                   Rate          Worked    Pay       Amount     Pay  \n"
#define REPORTHEADING3 "     ========               =====         ======    =====     ======     =====\n"
#define REPORTHEADERS (REPORTHEADING1 REPORTHEADING2 REPORTHEADING3) //sets all 3 headings into 1 var
#define FORMAT         "     %-23s%5.2f%15.2f%9.2f%11.2f%10.2f\n"
#define TAXRATE 0.15

	
	int main(void)
	{
	   // char firstName[10+1];
	    char lastName[10+1];
	    char fullName[10+10+2+1];
	    float payrate,hours,gross; // variables declaration section
	    float tax;
	    float netpay;
	    char answer;
	    // For a report file, STEP 1: declare a report file variable
        FILE * reportFile;
        // Step 2: open the report file for "write mode access"
        reportFile = fopen("c:\\temp\\report.txt","wt");               
	    fprintf(reportFile,REPORTHEADERS); //prints headers to report file (only once)
	    do 
		{
	      printf("Enter employee's first name: ");  // input section
	      scanf("%s",firstName);
	      printf("Enter employee's last name: ");
	      scanf("%s",lastName);
	      printf("Enter hourly pay rate: ");
	      scanf("%f",addr(payrate));
	      printf("Enter hours worked this pay period: ");
	      scanf("%f",addr(hours));
	      
	      
	      if (hours <= 40) //gross = hours * payrate;   /* processing */
	         gross = hours * payrate;
	      else
              gross = 40 * payrate + (hours-40)*1.5*payrate;   
          tax = gross * TAXRATE;
          netpay = gross-tax;    
          // step 3: where appropriate, change printf() --> fprintf()
          
          strcpy(fullName,lastName);
	      strcat(fullName,", ");
	      strcat(fullName,firstName);
	      
	      
	      printf(REPORTHEADERS);
	      printf(FORMAT,fullName,payrate,hours,gross,tax,netpay); /* output */
	      
	      
	      fprintf(reportFile,FORMAT,fullName,payrate,hours,gross,tax,netpay);
	      fflush(stdin); // clear keyboard buffer before answer input
	      printf("Another employee(Y/N) ");
	      scanf("%c",addr(answer));
		} while (answer == 'Y' || answer == 'y');
		// step 4: close the report file
		fclose(reportFile);
		printf("Report file created and saved."); //notify user of report success
	    fflush(stdin);
	    getchar();
		return 0;

	}
