#ifndef RESULT_H
#define RESULT_H

#include <iomanip>
#include <iostream>
#include <string>

#ifdef WIN
    #include <windows.h>
#endif


class Result
{
    private:

        // Width of the text
        static const int MAX_COL = 80;

        // Separator character
        static const char SEPARATOR = '.';

        // If we want to print results using colors
        static const bool COLOR = true;

    public:

        static const int OK = 0;
        static const int FAILED = -1;

        /**
         * Print a text and before inserting the result adds '.'
         * until it reaches the desired width
         *
         * @param text Text to show
         * @param result 0 on OK else FAILED
         * @return result parameter
         */
        static int print (std::string text, int result)
        {
            #ifdef WIN
                CONSOLE_SCREEN_BUFFER_INFO bfi;
            #endif

            // Add space between text and separators
            text += " ";

            // Print text followed by separators
            std::cout << std::setfill (SEPARATOR) << std::setw (MAX_COL - 11) << std::left << text << " [ ";

            // Store color schema
            #ifdef WIN
                if (COLOR) GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &bfi);
            #endif

            // Print result
            if (result == OK)
            {
                // Change to green color with the same background
                #ifdef WIN
                    if (COLOR) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_GREEN | bfi.wAttributes);
                #else
                    if (COLOR) std::cout << "\033[32;1m";
                #endif

                std::cout << "  OK  ";

                // Back to previous color schema
                #ifdef WIN
                    if (COLOR) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), bfi.wAttributes);
                #else
                    if (COLOR) std::cout << "\033[0m";
                #endif
            }
            else
            {
                // Change to red color with the same background
                #ifdef WIN
                        if (COLOR) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), FOREGROUND_RED | bfi.wAttributes);
                #else
                    if (COLOR) std::cout << "\033[31;1m";
                #endif

                std::cout << "FAILED";

                // Back to previous color schema
                #ifdef WIN
                    if (COLOR) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), bfi.wAttributes);
                #else
                    if (COLOR) std::cout << "\033[0m";
                #endif
            }

            std::cout << " ]" << std::endl;

            return result;
        }
};

#endif

