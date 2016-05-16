/*  Name: Taylor McCart, Ian Rosner, Shannon Sietmann, Alice Zhang
|   Date Created: (2/11/13)
|   Date Modified: (2/20/13)
|   Purpose: Challenges compiled into 1 program with menu
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>

using namespace std;

int main(void)
{
    int choice;
    cout << setfill('-') << setw(71) << "-" << endl;
    cout << "|1. Miles per Gallon   | 9. Automobile Costs   |17. Monthly Payments  |" << endl;
    cout << "|2. Stadium Seating    |10. Celsius to Faren.  |18. Pizza Pi          |" << endl;
    cout << "|3. Test Average       |11. Currency           |19. How Many Pizzas?  |" << endl;
    cout << "|4. Average Rainfall   |12. Monthly Sales Tax  |20. Angle Calculator  |" << endl;
    cout << "|5. Box Office         |13. Property Tax       |21. Stock Transaction |" << endl;
    cout << "|6. How Many Widgets?  |14. Senior Citizen Tax |22. Word Game         |" << endl;
    cout << "|7. How Many Calories? |15. Math Tutor         |                      |" << endl;
    cout << "|8. How Much Insurance?|16. Interest Earned    |                      |" << endl;
    cout << setfill('-') << setw(71) << "-" << endl;
    cout << "Enter program choice: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
    case 1: // gas prices
          {
              double miles,
                     gallons;
              cout << "Input number of gallons car can hold: ";
              cin >> gallons;
              cout << "Input number of miles car can go with full tank of gas: ";
              cin >> miles;

              cout << "\nYour car can go " << miles / gallons << " miles per gallon!\n";
              break;
          }
    case 2: // stadium
        {
            float ClassA;
            float ClassB;
            float ClassC;
            float Revenue;

            cout << "How many Class A tickets were sold?  ";
            cin >> ClassA;
            cout << "How many Class B tickets were sold?  ";
            cin >> ClassB;
            cout << "How many Class C tickets were sold?  ";
            cin >> ClassC;
            Revenue = (ClassA * (15)) + (ClassB * (12)) + (ClassC * (9));

            cout << "\nTotal revenue is $" <<setprecision(2) << fixed << showpoint << Revenue<<"\n\n";
            break;
        }
    case 3: // test average
        {
            float test1 = 0.0,
                  test2 = 0.0,
                  test3 = 0.0,
                  test4 = 0.0,
                  test5 = 0.0, 
                  avg = 0.0;

            cout << "Test Score Calculator!\n\n";
            cout << "Please enter the first test score:";
            cin >> test1;
            cout << "Please enter the second test score:";
            cin >> test2;
            cout << "Please enter the third test score:";
            cin >> test3;
            cout << "Please enter the fourth test score:";
            cin >> test4;
            cout << "Please enter the fifth test score:"; 
            cin >> test5;

            avg = (test1 + test2 + test3 + test4 + test5)/(5);

            cout << "\nYour test score average is " << setprecision(1) <<fixed<< avg << ".\n\n";
            system("pause");
            break;
        }
    case 4: // rainfall
        {
            string month1, month2, month3;
            float rainfall1, rainfall2, rainfall3;

            cout <<"Enter name of the first month.  ";
            cin >> month1;
            cout <<"How many inches of rain occured in " <<month1<< "?  ";
            cin >> rainfall1;
            cout <<"Enter name of the second month.  ";
            cin >> month2;
            cout <<"How many inches of rain occured in " <<month2<< "?  ";
            cin >> rainfall2;
            cout <<"Enter name of the third month.  ";
            cin >> month3;
            cout <<"How many inches of rain occured in " <<month3<< "?  ";
            cin >> rainfall3;

            cout <<"\nThe average rainfall for " <<month1<<", " <<month2<<", and " <<month3<<" is " << setprecision (2) << fixed << (rainfall1 + rainfall2 + rainfall3) / (3)<< " inches.\n\n";
            break;
        }
    case 5: // box office
        {
            const float ADULTPRICE = 6.00;
            const double CHILDPRICE = 3.00;
            const float PERCENTAGE = .20;
            float theatreGross = 0.0,
                  theatreNet = 0.0,
                  distributorProfit = 0.0;
            string movieTitle;
            int adultTickets = 0,
                childTickets = 0;

            cout<< "Please enter the name of the movie:";
            getline (cin, movieTitle);
            cin.ignore (0);
            cout << "\nPlease enter the amount of adult tickets sold:";
            cin>> adultTickets;
            cout<< "\nPlease enter the amount of child tickets sold:"; 
            cin>> childTickets;

            theatreGross = ((adultTickets*ADULTPRICE) + (childTickets*CHILDPRICE));
            theatreNet = (theatreGross * PERCENTAGE);
            distributorProfit = (theatreGross - theatreNet);

            cout << "\n\nMovie Name:              " <<setw(10)<<right<< char(34)<< movieTitle<< char(34);
            cout << "\nAdult Tickets Sold:        " <<setw(10)<<right<< adultTickets;
            cout << "\nChild Tickets Sold:        " <<setw(10)<<right<< childTickets;
            cout << "\nGross Box Office Profits:  " <<setw(10)<<right<< theatreGross;
            cout << "\nNet Box Office Profits:    " <<setw(10)<<right<< theatreNet;
            cout << "\nAmount paid to Distributor:" <<setw(10)<<right<< distributorProfit<< "\n\n";
            break;
        }
    case 6: // widgets
        {
            float palletBase,
                  palletWidg,
                  widgetCt;

            cout << "What is the weight of an empty pallet in pounds?\n";
            cin >> palletBase;
            cout << "What is the weight (lbs) of the pallet with widgets on it?\n";
            cin >> palletWidg;

            widgetCt = ((palletWidg - palletBase) / 9.2);

            cout << "There are " << widgetCt << " widgets on the pallet!\n";
            break;
        }
    case 7: // calories
        {
            int cookiesAte;

            cout << "How many cookies did you eat?\n";
            cin >> cookiesAte;
    
            if (cookiesAte > 40)
            {
                cout << "You have eaten more than a bag's worth of cookies!\n";
            }

            cout << "You consumed " << (30 * cookiesAte) << " calories!\n";
            break;
        }
    case 8: // insurance
        {
            float buildingCost = 0.0,
                    insuranceNeeded = 0.0;

            cout << "Insurance Calculator!!!\n\n";
            cout << "\nWhat is the replacement cost of your building? ";
            cin >> buildingCost;
    
            insuranceNeeded = buildingCost * .80;

            cout << "\nThe minimum amount of insurance needed is: " << insuranceNeeded << endl;
            break;
        }
    case 9: // automobile
        {
            float loanPayment = 0.0,
                    insurance = 0.0,
                    gas = 0.0,
                    oil = 0.0,
                    tires = 0.0,
                    maintenance = 0.0,
                    monthlyTotal = 0.0,
                    annualTotal = 0.0;

            cout << "Automobile Costs Calculator!!!!!!\n\n";
            cout << "How much is your loan payment per month? ";
            cin >> loanPayment;
            cout << "How much is your insurance payment monthly? ";
            cin >> insurance;
            cout << "How much do you spend on oil per month? ";
            cin >> oil;
            cout << "How much do you spend on tires per month? ";
            cin >> tires;
            cout << "How much do you spend on gas per month? ";
            cin >> gas;
            cout << "How much do you spend on maintenance per month? ";
            cin >> maintenance;

            monthlyTotal = loanPayment + insurance + gas + oil + tires + maintenance;
            annualTotal = monthlyTotal * 12;

            cout << "Your monthly total spent on car stuff is: " << monthlyTotal << endl;
            cout << "Your annual total spent on car stuff is: " << annualTotal << endl << endl;
            break;
        }
    case 10: // temp convert
        {
            float temperature = 0,
                converted = 0;

            cout << "Input degrees in Celsius\n";
            cin >> temperature;

            converted = (((1.8) * temperature) + 32);
            cout << "Degrees in Farenheit is " << converted << ".\n";
            system("pause");
            break;
        }
    case 11: // currency
        {
            float dollars = 0.0;
            float yen = 0.0;
            float euros = 0.0;
            const float YENPERDOLLAR = 92.75;
            const float EUROSPERDOLLAR = .75;

            cout << "How many dollars do you have? ";
            cin >> dollars;
    
            yen = dollars * YENPERDOLLAR;
            euros = dollars * EUROSPERDOLLAR;

            cout << "\nYou have the equvalent of " << fixed << setprecision(2) << showpoint << yen << " yen.\n";
            cout << "\nYou have the equvalent of " << euros << " euros.\n\n";
            break;
        }
    case 12: // sales tax
        {
            string month;
            string year;
            float totalcollected = 0.0, sales = 0.0, countySalesTax = 0.0, stateSalesTax = 0.0, totalSalesTax = 0.0;
            const float STATETAX = .04, COUNTYTAX = .02;

            cout << "What is the month?  ";
            cin >> month;
            cout << "\nWhat is the year?  ";
            cin >> year;
            cout << "\nWhat is the total amount collected at the cash register?  ";
            cin >> totalcollected;

            sales = (totalcollected) / (1 + STATETAX + COUNTYTAX);
            countySalesTax = sales * COUNTYTAX;
            stateSalesTax = sales * STATETAX;
            totalSalesTax = countySalesTax + stateSalesTax;
    
            cout << "\nMonth and year:  " << month << ", " << year <<" \n";
            cout << "\---------------------------  \n";
            cout << "Total collected:   $ " << setw(9)<< fixed << setprecision(2) << showpoint << totalcollected <<" \n";
            cout << "Sales:             $ " << setw(9)<< fixed << setprecision(2) << showpoint << sales <<" \n";
            cout << "County Sales Tax:  $ " << setw(9)<< fixed << setprecision(2) << showpoint << countySalesTax <<" \n";
            cout << "State Sales Tax:   $ " << setw(9)<< fixed << setprecision(2) << showpoint << stateSalesTax <<" \n";
            cout << "Total Sales Tax:   $ " << setw(9)<< fixed << setprecision(2) << showpoint << totalSalesTax <<" \n\n";
            break;
        }
    case 13: // property tax
        {
            float actualValue = 0.0, assessedValue = 0.0, propertyTax = 0.0;
            const float ASSESSEDRATE = .6, TAXRATE = .0064;

            cout << "What is the actual value of the property?  ";
            cin >> actualValue;

            assessedValue = (actualValue * ASSESSEDRATE);
            propertyTax = (assessedValue * TAXRATE);
    
            cout << "Assessment Value:   $ " << setw(11)<< fixed << setprecision(2) << showpoint << assessedValue <<" \n";
            cout << "Property Tax:       $ " << setw(11)<< fixed << setprecision(2) << showpoint << propertyTax <<" \n\n";
            break;
        }
    case 14: // senior tax
        {
            const float PERCENTAGE = .60;
            float propTax = 0.0;
            float landValue = 0.0;
            float SCassessValue = 0.0;
            float landTax = 0.0;
            float quarterlyTax = 0.0;

            cout<< "Senior Citizen Property Value Calculator!\n\n";
            cout << "Please enter the value of your land:";
            cin >> landValue;
            cout << "Please enter this year's current tax rate:";
            cin>> propTax;

            SCassessValue = ((landValue * PERCENTAGE)-5000);

            landTax = ((SCassessValue/100) * propTax);

            quarterlyTax = (landTax / 4);

            cout << "\n\nActual Value:  \t"<<setprecision(2)<<fixed<<landValue;
            cout<< "\nAssessement Value:\t"<<setprecision(2)<<fixed<<SCassessValue;
            cout<< "\nProperty Tax: \t"<<setprecision(2)<<fixed<<landTax;
            cout<< "\nQuarterly Tax:    \t"<<setprecision(2)<<fixed<<quarterlyTax<<"\n\n";
            break;
        }
    case 15: // math tutor
        {
            const int UPPERRANGE=500;
            unsigned seed = time(0);
            int numberOne = 0;
            unsigned numberTwo = 0;
            int answer = 0;
            char random = 0;

            cout << "Math Tutor!\nUse me to help improve your addition skills!\n\nGet a pencil and paper ready, and solve the following!\n";
            cout<< "when you have solved the equation, press enter to see if you're correct!\n\n";

            srand(seed);

            numberOne = 1 + rand() % UPPERRANGE;
            numberTwo = 1 + rand() % UPPERRANGE;

            cout<<"  "<<numberOne<<endl;
            cout<< "+ "<<numberTwo<<endl;
            cout<< "_____\n";
            cin.get();
            answer = numberOne + numberTwo;
            cout <<answer<<endl<<endl;
            cout<< "did you get it right :)?\n\n\n";
            break;
        }
    case 16: // interest
        {
            float Principal = 0.0,
                  interestRate = 0.0,
                  interestDecimal = 0.0,
                  Compounded = 0.0,
                  Interest=0.0,
                  Amount = 0.0;

            cout<<"Interest Calculator!\nUnderstand how much you're getting in a year";
            cout<<"\n\nPlease Enter the current balance in your savings Account(Principal):";
            cin >>Principal;
            cout<<"\n\nPlease Enter the Interest Rate:";
            cin >>interestRate;
            cout<<"\n\nPlease Enter the Number of times Interest is compounded per year:";
            cin >>Compounded;

            interestDecimal = interestRate / 100;

            Amount = (Principal * (pow(1+(interestDecimal/Compounded), Compounded)));

            Interest = Amount - Principal;

            cout<<"\n\nInterest Rate:              "<<right<<interestRate<<"%";
            if (Compounded < 100)
            {
                if (Compounded < 10)
                {
                    cout<<"\nTimes Compounded:              "<<right<<Compounded;
                }
                else
                {
                    cout<<"\nTimes Compounded:             "<<right<<Compounded;
                }
            }
            else
            {
                    cout<<"\nTimes Compounded:            "<<right<<Compounded;
            }
            cout<<"\nPrincipal:               "<<right<<fixed<<setprecision(2)<<Principal;
            cout<<"\nInterest:                  "<<right<<fixed<<setprecision(2)<<Interest;
            cout<<"\nAmount in Savings:       "<<right<<fixed<<setprecision(2)<<Amount<<"\n\n";
            break;
        }
    case 17: // monthlypay
        {
            float monthRate,
                    annualRate,
                    paymentAmt, // dollar value of a payment
                    payments, // number of payments
                    loan;

            cout << "Input annual interest rate: ";
            cin >> annualRate;
            cout << "Input loan amount: ";
            cin >> loan;
            cout << "Input amount of payments: ";
            cin >> payments;
    
            monthRate = (annualRate / 12) / 100;
            paymentAmt = ((monthRate * pow((1 + monthRate),payments)) / (pow((1 + monthRate),payments) - 1)) * loan;


            cout << fixed << showpoint << setprecision(2) << endl;

            cout << "Loan Amount:               $" << setw(10) << right << loan << endl;
            cout << "Monthly Interest Rate:      " << setw(9) << right << (int)annualRate / 12 << "%" << endl;
            cout << "Number of Payments:         " << setw(10) << right << (int)payments << endl;
            cout << "Monthly Payment:           $" << setw(10) << right << paymentAmt << endl;
            cout << "Amount Paid Back:          $" << setw(10) << right << paymentAmt * payments << endl;
            cout << "Interest Paid:             $" << setw(10) << right << (paymentAmt * payments) - loan << endl;
            break;
        }
    case 18: // pizzapi
        {
            double diameter;
            const double pi = atan(1)*4;

            cout << "Input pizza diameter: ";
            cin >> diameter;

            cout << endl << "Your pizza has " << fixed << setprecision(1) << (pi * pow((diameter / 2),2)) / 14.125 << " slices!" << endl;
            break;
        }
    case 19: // pizzaparty
        {
            double diameter,
                   slices;
            int attendees;
            const double pi = atan(1)*4;

            cout << "How many people are attending the party? ";
            cin >> attendees;
            cout << "Input pizza diameter: ";
            cin >> diameter;

            slices = (pi * pow((diameter / 2),2)) / 14.125;

            cout << endl << "You will need to order " << fixed << setprecision(1) << ((attendees*4)/slices) << " pizzas, at " << slices << " slices per pizza!" << endl;
            break;
        }
    case 20: // anglecalc
        {
            float angle = 0.0,
                  cosine = 0.0,
                  sine = 0.0,
                  tangent = 0.0;

            cout << "An Angle Calculator!\n\n";
            cout << "Please enter an angle in radians. ";
            cin >> angle;

            cosine = cos(angle);
            sine = sin(angle);
            tangent = tan(angle);

            cout << setprecision(4) << fixed;
            cout << "The cosine of the angle " << angle << " is: " << cosine << endl;
            cout << "The sine of the angle " << angle << " is: " << sine << endl;
            cout << "The tangent of the angle " << angle << " is: " << tangent << endl << endl;
            break;
        }
    case 21: // stock
        {
            const int sharesPurchased = 1000,
                sharesSold = 1000;
             double pricePerStock = 32.87,
                  sellingPrice = 0.0,
                  soldStockFor = 33.92,
                  commissionPercent = .02,
                  netPriceBuy = 0.0,
                  netPriceSell = 0.0,
                  profit = 0.0,
                  netPrice = 0.0,
                  totalPrice = 0.0;

            cout << "John's Stock Purchases~!\n\n";

            totalPrice = sharesPurchased * pricePerStock;
            cout << "John paid " << totalPrice << " for the stock." << endl;

            netPrice = totalPrice * commissionPercent;
            cout << "John paid " << netPrice << " for commission." << endl;

            sellingPrice = soldStockFor * sharesSold;
            cout << "John sold the stock for " << sellingPrice << "." << endl;

            netPriceSell = sellingPrice * commissionPercent;
            cout << "John paid " << netPriceSell << " for commission while selling his stock." << endl;

            profit = (sellingPrice - totalPrice) - (netPriceSell + netPrice);
            cout << "John made " << profit << " in profits." << endl;
            break;
        }
    case 22: // wordgame
        {
            string personName,
                   cityName,
                   collegeName,
                   professionName,
                   animalType,
                   petsName;
            int age;

            cout << "Let's Play A Word Game!\n\n";
            cout << "Please enter your name: ";
            cin >> personName;
            cout << "Please enter your age: ";
            cin >> age;
            cout << "Please enter the name of a city: ";
            cin >> cityName;
            cout << "Please enter the name of a college: ";
            cin >> collegeName;
            cout << "Please enter a type of profession: ";
            cin >> professionName;
            cout << "Please enter a type of animal: ";
            cin >> animalType;
            cout << "Please enter the name of a pet: ";
            cin >> petsName ;
            cout << "\n";
            cout << "There once was a person named " << personName << " who lived in " << cityName << ". " << endl;
            cout << "At the age of " << age << ", " << personName << " went to college at " << collegeName << ". " << endl;
            cout << personName << " graduated and went to work as a " << professionName << ". " << endl;
            cout << "Then, " << personName << " adopted a(n) " << animalType << " named " << petsName << ". " << endl;
            cout << "They lived happily ever after!" << endl;
            cout << "\n";
            break;
        }
    default:
        {
            cout << "Please enter a valid option.";
            break;
        }
    }
    system("pause");
}