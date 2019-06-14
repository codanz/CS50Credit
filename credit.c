#include <stdio.h>
#include <cs50.h>
#include <math.h>
// Check validity of credit card number

int main(void) 
{
    // Get credit card number
    long cc = 0;
    cc = get_long("Creditcard number: ");

    // Make variable to store card company and one to store number length
    string type = "invalid";
    int cclength = 0;

    // Determine length of the ccnumber
    if (cc>pow(10, 15))
    {
        cclength = 16;
    }
    else if (cc>pow(10, 14))
    {
        cclength = 15;
    }
    else if (cc>pow(10, 12))
    {
        cclength = 13;
    }
    else 
    {
        type = "INVALID";
        cclength = 4; // Assign length in order to let program run; it will still return invalid
    }
    
    // Isolate the first and first two numbers of the ccnumber in order to check those later
    int firsttwo = (cc % (long)(pow(10, cclength)) / (long)pow(10, cclength - 2));
    int first = (cc % (long)(pow(10, cclength)) / (long)pow(10, cclength - 1));
    
    // Per number length, check if the first or first two numbers coincide with the correct numbers per company
    if (cclength == 13)
    {
        if (first == 4)
        {
            type = "VISA";
        } 
        else 
        {
            type = "INVALID";
        }
    }
    else if (cclength == 15)
    {
        if (firsttwo == 34 || firsttwo == 37)
        {
            type = "AMEX";
        } 
        else 
        {
            type = "INVALID";
        }
    }
    else if (cclength == 16)
    {
        if (first == 4)
        {
            type = "VISA";
        } 
        else if (firsttwo == 51 || firsttwo == 52 || firsttwo == 53 || firsttwo == 54 ||firsttwo == 55)
        {
            type = "MASTERCARD";
        }
        else 
        {
            type = "INVALID";
        }
    }
    
    // Multiply every other number by two, starting with the second to last number
    long modulo = 100;
    long div = 10;
    long total = 0;
    long digit = 0;

    while (modulo < pow(10, cclength + 1))
    {
        digit = cc % modulo / div; // Get digit isolated
        modulo = modulo * 100; // Increase modulo
        div = div * 100; // Increase divisional foot
        int dubbel = digit * 2; // Multiply the digits times two
        int one = dubbel % 10; // Seperate the digits of the product (ones)
        int two = dubbel % 100 /10; // Seperate digits of the product (tens)
        total = total + one + two ; // Add seperate digits of the product to total
    }
    
    // Add all non-multiplied numbers together
    long modulos = 10;
    long divs = 1;
    long totals = 0;
    long digits = 0;

    while (modulos < pow(10, cclength + 1))
    {
        digits = cc % modulos / divs; // Get digit isolated
        modulos = modulos * 100; // Increase modulo
        divs = divs * 100; // Increase divisional foot
        totals = totals + digits; // Multiply digit by two and add both multiplication and digit to total
    }
    
    // Add the product's digits and the unmultiplied digits together
    int luhn = total + totals;
    // Check if total % 10 = 0, i.e. is it a valid number
    int valid = luhn % 10;
        
    // Return type or invalid depending on number check
    if (valid == 0)
    {
       printf("%s\n", type);
    }
    else 
    {
       printf("INVALID\n");
    }
};
