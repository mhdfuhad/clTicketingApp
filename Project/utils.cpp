#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds {
   bool debug = false;  // made global in utils.h
   int getTime() {  
      int mins = -1;
      if (debug) {
         Time t(0);
         cout << "Enter current time: ";
         do {
            cin.clear();
            cin >> t;   // needs extraction operator overloaded for Time
            if (!cin) {
               cout << "Invalid time, try again (HH:MM): ";
               cin.clear();
            }
            else {
               mins = int(t);
            }
            cin.ignore(1000, '\n');
         } while (mins < 0);
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }

   int getInt(const char* prompt) {
       string num;
       int m_num;
       bool nan = true;
       if (prompt) {
           cout << prompt;
       }
       while (nan) {
           getline(cin, num);

           bool flag = true;
           unsigned int size = strlen(num.c_str());

           for (unsigned int i = 0; i < size && flag; i++) {
               if (isdigit(num[0])) {
                   if (isdigit(num[i])) flag = true;
                   else {
                       cout << "Enter only an integer, try again: ";
                       flag = false;
                   }
               }
               else if (!isdigit(num[0]) && flag) {
                   cout << "Bad integer value, try again: ";
                   flag = false;
               }
           };

           if (flag) {
               nan = false;
               m_num = stoi(num);
           }
       }
       return m_num;
   };

   int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError) {
       int value = getInt(prompt);
       while (value > max || value < min) {
           if (errorMessage) {
               cout << errorMessage;
               if (showRangeAtError) {
                   cout << "[" << min << " <= value <= " << max << "]: ";
                   value = getInt();
               }
               else {
                   value = getInt();
               }
           }
       }
       return value;
   };

   char* getcstr(const char* prompt, std::istream& istr, char delimiter) {
       char* line = nullptr;
       if (prompt) {
           cout << prompt;
           string linestr;
           getline(istr, linestr, delimiter);
           line = new char[strlen(linestr.c_str()) + 1];
           strcpy(line, linestr.c_str());
       }
       return line;
   }
}