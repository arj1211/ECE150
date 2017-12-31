//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
// You are allowed float.h

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove

bool stringToFloat(const char input[], float& value);

//////////////////////////////////////////////////////////////
//
// Your code here ...

/*
+1.2345e15
-1.2345e+16
1.2345e-16
-12
-.2
+.2
+1234
 The exponent should only contain whole numbers, so 1.234e1.2 you would return false.


 When the exponential part of the float is too either too large or small, shall we return positive and negatve infinity respectively, or return false?

 Positive and negative infinity, if it is too small, for example: 1e-400, the value should be 0
  



  For an input like 12. 12.e0 or e1, you are supposed to return false. 


  MissingFraction is testing cases where it's missing the decimal part, things like 12. 12.e6 and possibly e5 and .e5
 
MissingExponent is testing cases where the exponent is missing like 12e

0 after e should be valid




*/

struct TheFloat {
  // if negative==1: positive number
  // if negative==-1: negative number
  int floatNegative = 1;
  // decimalPoint is set to true when decimalPoint occurs
  bool decimalPoint = false;
  bool exponential = false; // set to true if 'e' shows up
  int exponent = 0; // this is the exponent
  int exponentNegative = 1; // set to -1 if part after 'e' is negative
  bool floatAlreadyPlus = false;
  bool exponentAlreadyPlus = false;

  float preDecimal = 0; // the number before the decimal
  float postDecimal = 0; // the number after the decimal
  float postDecimalDigits = 0; // # of digits postDecimal has
};


bool stringToFloat(const char input[], float& value) {
  
  // have the line of input in the char array
  int i = 0;
  TheFloat f; // created new float struct, where i will keep the property info of the float
  value = 0;
  while(input[i]!=0)
  {
    // input[i] is current character

    /*
      What are the possible cases?
      1. current char is '-'
      2. current char is '+'
      3. current char is a number in [0,9]
      4. current char is 'e'
      5. current char is '.'
      6. current char is something else
    */

    if (input[i]=='-')
    {

      // if its preexponent and the float is already negative, return false
      // if its on exponent and the exponent is already negative, return false
      if (!f.exponential && f.floatNegative<0) return false;
      if (f.exponential && f.exponentNegative<0) return false;

      // ****make sure this sign is in the right place tho
        // can only be BEFORE preDecimal or BEFORE exponent
      if (!f.preDecimal || (f.preDecimal&&f.exponential&&!f.exponent))
      {// either the float itself can be negative, or the exponent can be negative
      if (f.exponential)
        f.exponentNegative=-1;
      else if (!f.exponential)
        f.floatNegative=-1;
      }
      else 
        return false;
    }
    else if (input[i]=='+')
    {
      // make sure this sign is in the right place tho

      // if its preexponent and the float is already negative, return false
      // if its on exponent and the exponent is already negative, return false
      if (!f.exponential && f.floatNegative<0) return false;
      if (f.exponential && f.exponentNegative<0) return false;

// how about the case with multiple +'s ?


      if (!f.preDecimal || (f.preDecimal&&f.exponential&&!f.exponent));
      // nothing needed cuz this is the default
      else
        return false;

      if (f.floatAlreadyPlus && !f.exponentAlreadyPlus) return false;
      else if (f.exponentAlreadyPlus) return false;
      // if preDecimal==0, floatAlreadyPlus=true;
      // else if exponent==0, exponentAlreadyPlus=true;

      if (!f.preDecimal) f.floatAlreadyPlus=true;
      else if (!f.exponent) f.exponentAlreadyPlus=true;

    }
    else if (input[i]>='0' && input[i]<='9')
    {
      // can either be preDecimal num, postDecimal num, or exponent num
      if (!f.decimalPoint && !f.exponential) // if its before decimal point and e/E hasnt occurred yet, its preDecimal
      {
        // append to preDecimal
        f.preDecimal = 10*f.preDecimal+(input[i]-'0');
      }
      else if (f.decimalPoint && !f.exponential) // if decimal occurred but e/E didnt, its postDecimal
      {
        // append to postDecimal
        f.postDecimal = 10*f.postDecimal+(input[i]-'0');
        f.postDecimalDigits++;
      }
      else if (f.exponential) // only other option is that its the exponent
      {
        // append to exponent
        f.exponent = 10*f.exponent+(input[i]-'0');
      }
    }
    else if (input[i]=='e' || input[i]=='E')
    {

      if (f.exponential) return false;

      f.exponential=true;
      // if preDecimal and postDecimal are both zero, return false
      // if char after this one (char+1) is NOT:
        // a digit [0,9]
          // if (char+1) is '-' or '+'
            // if (char+2) is NOT a digit [0,9], return false
      if (f.preDecimal==0 && f.postDecimal==0) return false;

      if (!(input[i+1]>='0' && input[i+1]<='9'))
      {
        if (input[i+1]=='-' || input[i+1]=='+')
        {
          if (!(input[i+2]>='0' && input[i+2]<='9'))
            return false;

        }
        else return false;
      }
      
    }
    else if (input[i]=='.')
    {
      if (f.decimalPoint) return false;
      f.decimalPoint=true;
      // if the char right after this one is NOT a digit [0,9], return false
      if ( !(input[i+1]>='0' && input[i+1]<='9') ) return false;
    }
    else
      return false;

    i++;
  }

  //if (f.exponential && f.exponent==NULL) return false;

  // if the very last char in the string is NOT a number [0,9], its rejection

  //if (!(input[i-1]>='0' && input[i-1]<='9')) return false;

  float floatPre = (float)f.preDecimal;
  float dividingTerm = 1;
  for (int i = 0; i < f.postDecimalDigits; i++)
  {
    dividingTerm*=10;
  }
  float floatPost = ((float)f.postDecimal)/dividingTerm;
  float multiplier = 1;

  if (f.exponential)
  for (int i = 0; i<f.exponent;i++)
  {
    if(f.exponentNegative>0)
    {
      multiplier*=10.0;
    }
    else if (f.exponentNegative<0)
    {
      multiplier/=10.0;
    }
  }

  value = f.floatNegative*(floatPre+floatPost)*multiplier;
  return true;

}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING
int main(const int argc, const char* const argv[]) {
  
  // Some test driver code here ....
  float argv1;

  if (argc < 2) {
    cerr << "Error: Usage: " << argv[0] << " <float>" << endl;
    return -1;
  }

  if (stringToFloat(argv[1],argv1)) 
    cout << "argv[1] is a float with value: " << argv1 <<endl;
  else
    cout << "argv[1] is not a float. argv[1]: " <<argv[1] << endl;
  return 0;
}

#endif
