	//  NAME  : Ian Rosner
	//  CLASS : CISP 301, MW 12:00
	//  PROGRAM TITLE : Sample Payroll Program
	//  Purpose: Assignment 2
	//  Software Change(Modifications) Record
	//  date         what              who
	//	4/6/2013	 Tax, gross, net   Rosner
	//	4/6/2013	 Totals, averages  Rosner
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
	    					empcount
	    				    avgs and tots
							for: hrs,pay,
							gross,tax,net
	    
	    There are ONLY four(4) fundamental design data types:
	          (s) string, (c) character, (i) integer, (f) real--> float point                                      
	*/
	#include  <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#define addr(var) &var
	#define REPORTHEADING1 "     Employee               Pay           Hours     Gross     Tax        Net  \n"
	#define REPORTHEADING2 "     Name                   Rate          Worked    Pay       Amount     Pay  \n"
	#define REPORTHEADING3 "     ========               =====         ======    =====     ======     =====\n"
	#define HEADINGS (REPORTHEADING1 REPORTHEADING2 REPORTHEADING3)
	#define FORMAT         "     %-23s%5.2f%15.2f%9.2f%11.2f%10.2f\n"
	#define TAXRATE 0.15
	
	int main(void)
		{
		    char firstName[11];
		    char lastName[11];
		    char fullName[23];
		    float payrate,hours,gross; // variables declaration section
		    float tax;
		    float netpay;
		    char answer;
		    
		    // averages & totals var declarations
	        float totpay;
	        float tothrs;
	        float totgro;
	        float tottax;
	        float totnet;
			int empcount;
		    
		    // For a report file, STEP 1: declare a report file variable
	        FILE * reportFile;
	        // Step 2: open the report file for "write mode access"
	        reportFile = fopen("c:\\temp\\report.txt","wt");    
			if (reportFile == NULL)
	    	{
	      		printf("Report file not found. Exiting...");
	      		fflush(stdin);
	      		getchar();
	      		exit(-250);
	    	}           
		    fprintf(reportFile,HEADERS); //prints headers to report file (only once)
		    fprintf(reportFile,"\n");//line spacing to seperate values, use \n for blank space
		    
		    // INITIALIZATION STEP (**above loop**)
			totpay = 0.0;
			tothrs = 0.0;
			totgro = 0.0;
			tottax = 0.0;
			totnet = 0.0;
			empcount = 0;
		    
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
	          
	            // totals calculations
	          totpay += payrate;
	          tothrs += hours;
	          totgro += gross;
	          tottax += tax;
	          totnet += netpay;
	          empcount++;
	          // step 3: where appropriate, change printf() --> fprintf()
	          
	          strcpy(fullName,lastName);
		      strcat(fullName,", ");
		      strcat(fullName,firstName);
		      
		      
		      printf(HEADERS);
		      
		      printf(FORMAT,fullName,payrate,hours,gross,tax,netpay); /* output */
		      
		      
		      fprintf(reportFile,FORMAT,fullName,payrate,hours,gross,tax,netpay);
		      fflush(stdin); // clear keyboard buffer before answer input
		      printf("Another employee(Y/N) ");
		      scanf("%c",addr(answer));
			} while (answer == 'Y' || answer == 'y');
			             
			//output our totals and averages to bottom of report file  
	        fprintf(reportFile,"\n");
	        fprintf(reportFile,FORMAT,"Totals",totpay,tothrs,totgro,tottax,totnet);
			fprintf(reportFile,FORMAT,"Averages",totpay/empcount,tothrs/empcount,
					totgro/empcount,tottax/empcount,totnet/empcount);
			// step 4: close the report file
			fclose(reportFile);
			printf("Report file created and saved."); //notify user of report success
		    fflush(stdin);
		    getchar();
			return 0;
	
		}
