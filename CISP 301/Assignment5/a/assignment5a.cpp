//  NAME  : Ian Rosner
//  CLASS : CISP 301, MW 2:00
//  PROGRAM TITLE : A Sample Payroll Program
//  Purpose: Assignment 5a
//  Software Change(Modifications) Record
//  date         what              who
//  6/21/2007    Flush and Hold    Dixon
//	9/17/2012	 Tax, gross, net   Rosner
//	9/23/2012	 Totals, averages  Rosner
//	10/6/2012	 Modularization    Rosner
//  11/20/2012   Validation	       Rosner
//  12/1/2012    Record format	   Rosner
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
#define BIGLINE		   "     =========================================================================\n"
#define REPORTHEADING1 "     Employee               Pay           Hours     Gross     Tax        Net  \n"
#define REPORTHEADING2 "     Name                   Rate          Worked    Pay       Amount     Pay  \n"
#define REPORTHEADING3 "     ========               =====         ======    =====     ======     =====\n"
#define REPORTHEADERS (REPORTHEADING1 REPORTHEADING2 REPORTHEADING3) //sets all 3 headings into 1 var
#define FORMAT         "     %-23s%5.2f%15.2f%9.2f%11.2f%10.2f\n"
#define TAXRATE 0.15
// -- VALIDATION PREPROCESSORS --
#define BOOL short
#define TRUE 1
#define FALSE 0
#define RETRYMAX 3


void checkFile(FILE*);//3.1  check if report file exists
void getData(float * payrate,float * hours,char firstName[11],char lastName[11],char fullName[23]); //3.2 get inputs
float grossCalc(float payrate,float hours); //3.3 calculate gross
float taxCalc(float gross); // 3.4 calculate tax
float netCalc(float tax,float gross); //3.5 calculate net
void totCalc(float payrate,float hours,float gross,float tax,float net,
			  float * totpay,float * tothrs,float * totgro,
			  float * tottax,float * totnet); //3.6 aggregate totals
void reportData(FILE *reportFile,char fullName[],float payrate,float hours,float gross,float tax,float net); //3.7 report line to screen / file
void loopAsk(char * answer); //3.8 repeat again?
void reportFinish(FILE *reportFile,float totpay,float tothrs,float totgro,
				  float tottax,float totnet,int empcount); //3.9 report totals and averages
//validation modules
void getValidString(char * prompt,char * name);
float getValidNum(char * prompt,float minNum,float maxNum);
BOOL isDigit(char);

int main(void)
{
		typedef struct EmployeeRecord
		{ // start of record field definition list
			char lastName[15+1];
			char firstName[10+1];
			char fullName[23];
			float hours;
			float payrate;
			float gross;
			float tax;
			float net;
		} EmployeeRecord;
		EmployeeRecord employee;
	    char answer;
	    
	    //total var declarations
        float totpay = 0;
        float tothrs = 0;
        float totgro = 0;
        float tottax = 0;
        float totnet = 0;
		int empcount = 0;
	    // file control
	    
	    
        FILE * reportFile;
        reportFile = fopen("c:\\temp\\report.txt","wt");    
        checkFile(reportFile);

	    do 
		{
			getData(&employee.payrate,&employee.hours,employee.firstName,employee.lastName,employee.fullName);
			empcount++;
		    employee.gross = grossCalc(employee.payrate,employee.hours);
		    employee.tax = taxCalc(employee.gross);
		    employee.net = netCalc(employee.tax,employee.gross);
		    totCalc(employee.payrate,employee.hours,employee.gross,employee.tax,employee.net,&totpay,&tothrs,&totgro,&tottax,&totnet);
		    reportData(reportFile,employee.fullName,employee.payrate,
					   employee.hours,employee.gross,employee.tax,employee.net);
		    loopAsk(&answer);
		} while (answer == 'Y' || answer == 'y');
		reportFinish(reportFile,totpay,tothrs,totgro,tottax,totnet,empcount);
		
    	fflush(stdin);
		getchar();
		return 0;
}

void checkFile(FILE *reportFile) //3.1
{
	if (reportFile == NULL)
		{
		printf("Report file not found. Exiting...");
		fflush(stdin);
		getchar();
		exit(-250);
		}
	else
		{
		fprintf(reportFile,REPORTHEADERS); //prints headers to report file (only once)
		fprintf(reportFile,BIGLINE);//line spacing to seperate values, use \n for blank space
		}
}
	
void getData(float *payrate,float *hours,char firstName[],char lastName[],char fullName[]) //3.2
{
	getValidString("Enter employee's first name: ",firstName);
	getValidString("Enter employee's last name: ",lastName);
    *payrate = getValidNum("Enter hourly pay rate: ",0,99.99);
    *hours = getValidNum("Enter hours worked this pay period: ",0,112);
    
	strcpy(fullName,lastName);
	strcat(fullName,", ");
	strcat(fullName,firstName);
	printf(REPORTHEADERS);
}

float grossCalc(float payrate,float hours) //3.3
{
	if (hours <= 40) //gross = hours * payrate;   /* processing */
		return hours * payrate;
	else
		return 40 * payrate + (hours-40)*1.5*payrate;   
}

float taxCalc(float gross) //3.4
{
	return gross * TAXRATE;
}

float netCalc(float tax,float gross) //3.5
{
	return gross-tax;
}

void totCalc(float payrate,float hours,float gross,float tax,float net,
			  float *totpay,float *tothrs,float *totgro,
			  float *tottax,float *totnet)  //3.6
{
	*totpay += payrate;
	*tothrs += hours;
	*totgro += gross;
	*tottax += tax;
	*totnet += net;
}

void reportData(FILE *reportFile,char fullName[],float payrate,float hours,float gross,float tax,float net) //3.6
{
	printf(FORMAT,fullName,payrate,hours,gross,tax,net); /* output */
	fprintf(reportFile,FORMAT,fullName,payrate,hours,gross,tax,net);
}

void loopAsk(char *answer)   //3.8
{
	fflush(stdin); // clear keyboard buffer before answer input
	printf("Another employee(Y/N) ");
	scanf("%c",answer);
}

void reportFinish(FILE *reportFile,float totpay,float tothrs,float totgro,float tottax,float totnet,int empcount) //3.9
{
	fprintf(reportFile,BIGLINE);
	fprintf(reportFile,FORMAT,"Totals",totpay,tothrs,totgro,tottax,totnet);
	fprintf(reportFile,FORMAT,"Averages",totpay/empcount,tothrs/empcount,
						  totgro/empcount,tottax/empcount,totnet/empcount);
	fclose(reportFile);
	printf("Report file created and saved."); //notify user of report success
}

BOOL validateString(char inString[])
{
	int i;

	for (i=0; i < strlen(inString); i++)
	{
		if (isDigit(inString[i]))
    	return FALSE;   
	}	
	return TRUE;
}

BOOL validateNumber(float inNum,float minNum,float maxNum)
{
	if (inNum >= minNum && inNum <= maxNum)
		return TRUE;
	else
		return FALSE;
}

BOOL isDigit(char inChar)
{
	if (inChar >= '0' && inChar <= '9')
		return TRUE;
	else
		return FALSE;
}

void getValidString(char * prompt,char * name)
{
     BOOL ValidString;
     static char response[80+1];
     int retrycount;
     
     retrycount=0;
     do {
           printf(prompt); // input section
           scanf("%s",&response[0]);
           ValidString = validateString(response);
           if (!ValidString)
			{
            	retrycount++;
            	printf("Invalid name. Names should not contain numbers.\n"); //warn user
            }
    } while (retrycount < RETRYMAX && !ValidString);
    if (!ValidString)
       strcpy(name,"BadName"); // set default
    else
       strcpy(name,response);  //proceed with copy  
    
}

float getValidNum(char * prompt,float minNum,float maxNum)
{   
   int retrycount;
   BOOL ValidNumber;
   float inNum;

   retrycount=0;
    do {
		printf(prompt);
		scanf("%f",&inNum);
		ValidNumber = validateNumber(inNum,minNum,maxNum);
		if (!ValidNumber)
		{
			retrycount++;
			printf("Invalid data. Value should be greater than %4.2f, and should not exceed %4.2f.\n",minNum,maxNum); //warn user
		}
    } while (retrycount < RETRYMAX && !ValidNumber);
    if (!ValidNumber) inNum = 0.0; // default
    return inNum;
}
