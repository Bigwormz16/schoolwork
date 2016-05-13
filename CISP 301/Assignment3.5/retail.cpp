#include <stdio.h>
#define REPORTHEAD1 " Item Unit Retail Quantity Taxable Extended\n"
#define REPORTHEAD2 " Description Cost Price On Hand (Y/N) Price\n"
#define REPORTHEAD3 " ==================== ==== ====== ======== ====== ======\n"
#define REPORTFORMAT " %-20s%6.2f%12.2f%10d%12c%10.2f\n"
#define MARKUP 0.18
#define TAXRATE 0.0775
/* 1) Create an IPO chart for this program
2) Identify all variables ...
3) Identify the IPO sections of this program
4) Identify the loop within this program
5) Advanced .... decompose this program into functions
Show the Hierarchy Chart and flowchart
*/
int main(void)
{
char iDescription[20+1];
float unitCost;
int quantity;
char taxStatus;
float retailPrice; // variables' declaration section
char answer;
FILE * reportfile;
reportfile = fopen("c:\\temp\\retailReport.lst","wt");
fprintf(reportfile,REPORTHEAD1);
fprintf(reportfile,REPORTHEAD2);
fprintf(reportfile,REPORTHEAD3);
do
{
printf("Enter item description ");
scanf("%s",iDescription);
printf("Enter the unit cost ");
scanf("%f",&unitCost);
printf("Enter the quantity purchased of item ");
scanf("%d",&quantity);
fflush(stdin);
printf("Is this item taxable(y/n) ");
scanf("%c",&taxStatus);
retailPrice = unitCost * (1+MARKUP);
if (taxStatus == 'Y' || taxStatus == 'y')
retailPrice = retailPrice * (1+ TAXRATE);
fprintf(reportfile,REPORTFORMAT,iDescription,unitCost,retailPrice,quantity,taxStatus,retailPrice*quantity);
printf("Do you have another item(y/n) ");
fflush(stdin);
scanf("%c",&answer);
} while (answer == 'Y' || answer == 'y');
fclose(reportfile);
printf("press any key ....\n");
fflush(stdin);
getchar();
return 0;
} // main()