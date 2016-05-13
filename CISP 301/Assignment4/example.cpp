#include <stdio.h>
#include <string.h>
#define Addr(var) &var
#define COLUMNHEADINGSA " Employee's    Pay     Hours    Gross  Tax      Net\n"
#define COLUMNHEADINGSB " Name          Rate    Worked   Pay    Amount   Pay\n"
#define COLUMNHEADINGSC " ==========    =====   ======   =====  ======   ===\n"
#define REPORTFORMAT    " %-14s%5.2f%9.2f%8.2f%8.2f%6.2f\n"
#define TRUE 1
#define FALSE 0 
#define BOOLEAN short
#define RETRYMAX 3

//boolean classifier functions
BOOLEAN ValidateString(char inputString[]);
BOOLEAN ValidateNumber(float number,float lowRange,float hiRange);
BOOLEAN isDigit(char aChar);


int main(void)
{
    char lastName[10+1]; 
    char firstName[8+1];
    float payrate;
    float hours;   // variables declaration section
    float grossPay;  
    float taxAmount;
    float netPay;
    const float TAXRATE = 0.15;
    BOOLEAN ValidNumber,ValidString;
    int reTryCount;
    
    
    reTryCount=0;
    do {
      printf("Enter employee's lastname "); // input seclion
      scanf("%s",Addr(lastName[0])) ;
      ValidString = ValidateString(lastName);
      if (!ValidString) reTryCount++;
    } while (reTryCount < RETRYMAX && !ValidString);
    if (!ValidString) strcpy(lastName,"BadName"); // default
    printf("Enter employee's firstName "); // input seclion
    scanf("%s",Addr(firstName[0])) ;
    reTryCount=0;
    do {
      printf("Enter hourly pay rate ==> ");
      scanf("%f",Addr(payrate));
      ValidNumber = ValidateNumber(payrate,0,99.99);
      if (!ValidNumber) reTryCount++;
    } while (reTryCount < RETRYMAX && !ValidNumber);
    if (!ValidNumber) payrate = 0.0; // default
    printf("Enter hours worked this pay period ==> ");
    scanf("%f",Addr(hours));
    if (hours <= 40)
      grossPay = hours * payrate;
    else
      grossPay = 40 * payrate + (hours-40) * 1.5 * payrate;
    taxAmount = grossPay *  TAXRATE;
    netPay = grossPay - taxAmount;
    printf(COLUMNHEADINGSA); // Output section
    printf(COLUMNHEADINGSB); // Output section
    printf(COLUMNHEADINGSC); // Output section
    printf(REPORTFORMAT,lastName, payrate, hours, grossPay,taxAmount,netPay);
    printf("     Press any key ...\n");
    fflush(stdin); // pause screen display
    getchar(); // wait for key press ...
    return 0; 
}
   

BOOLEAN isDigit(char inputChar)
{ 
  if ( inputChar >= '0' && inputChar <= '9')
    return TRUE;
  else
    return FALSE;
}

BOOLEAN ValidateString(char inputString[])
{
   int i;

   for (i=0; i < strlen(inputString); i++)
   {
     if (isDigit(inputString[i])) return FALSE;   
   }	
   return TRUE;
}
  
BOOLEAN ValidateNumber(float number,float lowRange,float hiRange)
{
   if (number >= lowRange && number <= hiRange)
     return TRUE;
   else
     return FALSE;
}
