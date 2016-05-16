/* Name: Taylor McCart, Ian Rosner, Shannon Sietmann, Alice Zhang
   Date Created: (2/25/13)
   Date Modified: (2/27/13)
   Purpose: Temperature Scale Converter
*/

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main ()
{
    float Fahrenheit = 0,
          Celsius = 0,
          Kelvin = 0;
    int   Counter = 0,
          Increment = 0;
    char  Response;
    char  SecondResponse = 0;
    char dg = char(178);

    cout << "What is your starting temperature type? (K/F/C): ";
    cin >> Response;
    
    do
        {
            if(Response == SecondResponse) cout << "\nError: converting to same type! (" << Response << " to " << SecondResponse << ")";
            cout << "\nWhat is your desired ending temperature type? (K/F/C): ";
            cin >>SecondResponse;
            toupper (SecondResponse);
        } while(Response == SecondResponse);

    cout << "\nWhat increment would you like the next ten values to be by?: ";
    cin >> Increment;
   
    switch (SecondResponse)
    {
    case ('K') : if (Response == 'F')
                 {
                    cout << "\n\nPlease enter the temperature in Fahrenheit: ";
                    cin >> Fahrenheit;

                    Kelvin = ((5.0/9) * (Fahrenheit - 32) + 273);
                    
                    cout<< "\n\nFarenheit\t\tKelvin\n";
                    cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Fahrenheit<<"\370\t\t"<<setw(7)<<Kelvin<<"\370\n";
                    for (Counter = 0; Counter < 10; Counter++)
                    {
                        Fahrenheit = Fahrenheit + Increment;
                        Kelvin = ((5.0/9) * (Fahrenheit - 32) + 273);
                        cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Fahrenheit<<"\370\t\t"<<setw(7)<<Kelvin<<"\370\n";
                    }
                 }
                 if (Response == 'C')
                 {
                    cout << "\n\nPlease enter the temperature in Celsius: ";
                    cin >> Celsius;

                    Kelvin = (Celsius + 273);
                    
                    cout<< "\n\nCelsius\t\t\tKelvin\n";
                    cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Celsius<<"\370\t\t"<<setw(7)<<Kelvin<<"\370\n";
                    for (Counter = 0; Counter < 10; Counter++)
                    {
                        Celsius = Celsius + Increment;
                        Kelvin = (Celsius + 273);
                        cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Celsius<<"\370\t\t"<<setw(7)<<Kelvin<<"\370\n";
                    }
                 }
                 break;
    case 'F': if (Response == 'K')
              {
                  cout << "\n\nPlease enter the temperature in Kelvin: ";
                    cin >> Kelvin;

                    Fahrenheit = (((Kelvin - 273) * 1.8 ) + 32);
                    
                    cout<< "\n\nKelvin\t\t\tFahrenheit\n";
                    cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Kelvin<<"\370\t\t"<<setw(7)<<Fahrenheit<<"\370\n";
                    for (Counter = 0; Counter < 10; Counter++)
                    {
                        Kelvin = Kelvin + Increment;
                        Fahrenheit = (((Kelvin - 273) * 1.8 ) + 32);
                        cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Kelvin<<"\370\t\t"<<setw(7)<<Fahrenheit<<"\370\n";
                    }
              }
              if (Response == 'C')
              {
                   cout << "\n\nPlease enter the temperature in Celsius: ";
                    cin >> Celsius;

                    Fahrenheit = (((9.0/5) * Celsius) + 32);
                    
                    cout<< "\n\nCelsius\t\t\tFahrenheit\n";
                    cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Celsius<<"\370\t\t"<<setw(7)<<Fahrenheit<<"\370\n";
                    for (Counter = 0; Counter < 10; Counter++)
                    {
                        Celsius = Celsius + Increment;
                        Fahrenheit = (((9.0/5) * Celsius) + 32);
                        cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Celsius<<"\370\t\t"<<setw(7)<<Fahrenheit<<"\370\n";
                    }
              }
              break;
    case 'C': if (Response == 'K')
              {
                   cout << "\n\nPlease enter the temperature in Kelvin: ";
                   cin >> Kelvin;

                   Celsius = (Kelvin - 273);

                   cout<< "\n\nKelvin\t\t\tCelsius\n";
                   cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Kelvin<<"\370\t\t"<<setw(7)<<Celsius<<"\370\n";
                   for (Counter = 0; Counter < 10; Counter++)
                   {
                       Kelvin = Kelvin + Increment;
                       Celsius = (Kelvin - 273);
                       cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Kelvin<<"\370\t\t"<<setw(7)<<Celsius<<"\370\n";
                   }
              }
              if (Response == 'F')
              {
                   cout << "\n\nPlease enter the temperature in Fahrenheit: ";
                   cin >> Fahrenheit;

                   Celsius = ((5.0/9) * (Fahrenheit - 32));

                   cout<< "\n\nFahrenheit\t\tCelsius\n";
                   cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Fahrenheit<<"\370\t\t"<<setw(7)<<Celsius<<"\370\n";
                   for (Counter = 0; Counter < 10; Counter++)
                   {
                       Fahrenheit = Fahrenheit + Increment;
                       Celsius = ((5.0/9) * (Fahrenheit - 32));
                       cout<<setprecision(2)<<showpoint<<fixed<<right<<setw(7)<<Fahrenheit<<"\370\t\t"<<setw(7)<<Celsius<<"\370\n";
                   }
              }
              break;
    }
    cout << "\n\n";
    system ("pause");
    return 0;
}
