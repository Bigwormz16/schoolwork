//  NAME  : Ian Rosner
//  CLASS : CISP 301, MW 2:00
//  PROGRAM TITLE : A Sample Payroll Program
//  Purpose: Assignment 5b
//  Software Change(Modifications) Record
//  date         what              who
//  6/21/2007    Flush and Hold    Dixon
//	9/17/2012	 Tax, gross, net   Rosner
//	9/23/2012	 Totals, averages  Rosner
//	10/6/2012	 Modularization    Rosner
//  11/20/2012   Validation	       Rosner
//  12/1/2012    Record format	   Rosner
//  12/10/2012	 Bubble sort	   Rosner
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

// prototypes
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
void reportFinish(FILE *reportFile,float totpay,float tothrs,float totgro,float tottax,float totnet,int empcount,
				  EmployeeRecord employee[],int index[]); //3.9 report totals and averages
//validation modules
void getValidString(char * prompt,char * name);
float getValidNum(char * prompt,float minNum,float maxNum);
BOOL isDigit(char);
void BubbleSort(EmployeeRecord employee[], int index[10],int max);

int main(void)
{
		EmployeeRecord employee[10];
		int index[10];
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
			getData(&employee[empcount].payrate,
					&employee[empcount].hours,
					employee[empcount].firstName,
					employee[empcount].lastName,
					employee[empcount].fullName);
		    employee[empcount].gross = grossCalc(employee[empcount].payrate,
												 employee[empcount].hours);
		    employee[empcount].tax = taxCalc(employee[empcount].gross);
		    employee[empcount].net = netCalc(employee[empcount].tax,
											 employee[empcount].gross);
		    totCalc(employee[empcount].payrate,employee[empcount].hours,
					employee[empcount].gross,employee[empcount].tax,
					employee[empcount].net,&totpay,&tothrs,&totgro,
					&tottax,&totnet);
			printf(FORMAT,employee[empcount].fullName,
				   employee[empcount].payrate,
				   employee[empcount].hours,employee[empcount].gross,
				   employee[empcount].tax,employee[empcount].net); /* output to screen */
			empcount++;
		    loopAsk(&answer);
		} while (answer == 'Y' || answer == 'y');		
		reportFinish(reportFile,totpay,tothrs,totgro,tottax,totnet,
					 empcount,employee,index);
		
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
	fprintf(reportFile,FORMAT,fullName,payrate,hours,gross,tax,net);
}

void loopAsk(char *answer)   //3.8
{
	fflush(stdin); // clear keyboard buffer before answer input
	printf("Another employee(Y/N) ");
	scanf("%c",answer);
}

void reportFinish(FILE *reportFile,float totpay,float tothrs,float totgro,float tottax,float totnet,int empcount,
				  EmployeeRecord employee[],int index[]) //3.9
{
	BubbleSort(employee,index,empcount); //call sort before reporting...
	
	for (int i=0;i<empcount;i++) //print sorted data to file
	{
		reportData(reportFile,employee[index[i]].fullName,
				   employee[index[i]].payrate,
				   employee[index[i]].hours,
				   employee[index[i]].gross,
				   employee[index[i]].tax,
				   employee[index[i]].net);
	}
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

void BubbleSort(EmployeeRecord employee[], int index[10],int max)
{
	int outer, inner;
    for (outer= 0; outer < max; outer++) index[outer]=outer; // init index
	for (outer= 0; outer < max; outer++)
	{
		for (inner =0; inner < max-1; inner++) // pass loop
		{ //test
			if (strcmp(employee[index[inner]].lastName,employee[index[inner+1]].lastName)>0)
			{ //swap
				int temp = index[inner];
				index[inner] = index[inner+1];
				index[inner+1] = temp;
			}
		} // inner loop
	} // outer loop
} // sortbylastname
