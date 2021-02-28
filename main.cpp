#include <dirent.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <array>
#include <map>

#include <string.h>
#include <stdio.h>

using namespace std;

class Registers{

    public:
    std::vector<std::string> memory;
    int accumulator = 0;
    int additional_register = 0;
    int program_counter = 0;
    int zero_result_bit = 0;
    int overflow_bit = 0;
    std::map<std::string, int> data;

};


class interpret: public Registers{

    public:
    int interpreter(const std::string& sal_per_line) {

        std::string instruction = sal_per_line.substr(0, 3);
        if (sal_per_line.length() > 3)
        {
            std::string symbol = sal_per_line.substr(4);

            if (instruction == "DEC")
            {
                memory[program_counter] = symbol;
                data.insert(pair<std::string, int>(symbol, 0));

                std::cout <<"Variable "<< symbol<<" declares " << std::endl;

            }

            else if (instruction == "LDA")
            {
                accumulator = data[symbol];
                std::cout <<"Byte at data at memory address of "<< symbol<<" loaded into the accumulator" << std::endl;

            }

            else if (instruction == "LDB")
            {
                additional_register = data[symbol];
                std::cout <<symbol <<" loaded into additional_register " << std::endl;

            }


            else if (instruction == "LDI")
            {
                accumulator = std::stoi(symbol);
                std::cout <<symbol <<" loaded into accumulator " << std::endl;

            }

            else if (instruction == "STR")
            {
                data[symbol] = accumulator;
                std::cout <<accumulator <<" stored at " <<symbol << std::endl;

            }

            else if (instruction == "JMP")
            {
                program_counter = std::stoi(symbol);
                std::cout <<"Transfered control to instruction at address " <<symbol << std::endl;
                return 0;

            }
            else if (instruction == "JZS")
            {
                if (zero_result_bit == 1){
                    program_counter = std::stoi(symbol);
                    std::cout <<"Transfered control to instruction at address " <<symbol <<" as zero-result bit is set."<< std::endl;
                    return(0);
                }

            }
            else if (instruction == "JVS")
            {
                if(overflow_bit == 1) {
                    program_counter = std::stoi(symbol);
                    std::cout <<"Transfered control to instruction at address " <<symbol<<" as overflow_bit is set."<< std::endl;
                    return (0);
                }

            }

        }
        else if (instruction=="HLT")
        {
            std::cout << "******Reached Halt******" << std::endl;

        }
        else if(instruction=="XCH") {
            int temp = accumulator;
            accumulator = additional_register;
            additional_register = temp;
            std::cout << "Content of accumulator and additional_register exchanged " << std::endl;

        }

        else if(instruction=="ADD")
        {

            int result=accumulator + additional_register;
            if ((accumulator>0 && additional_register>0 && result<0) || (accumulator<0 && additional_register<0 && result>0))
            {
                overflow_bit = 1;
                std::cout << "overflow_bit is set" << std::endl;
            }
            else
                overflow_bit = 0;

            std::cout << accumulator<<" and " << additional_register <<" added"<< std::endl;
            accumulator = accumulator + additional_register;

            if (accumulator == 0)
            {
                zero_result_bit = 1;
                std::cout << "zero_result_bit is set" << std::endl;
            }

        }

        else{
            std::cout << "Incorrect SAL command." << std::endl;

        }

        program_counter++;

        std::cout << "program_counter updated "<< program_counter<< std::endl;

        return(0);
    }

};




int main()
{

    interpret intp;

//To run 'l' after 'a'
//    std::vector<std::string> source_code;

    std::vector<std::string> files;

    DIR *d;
    char *p1,*p2;
    struct dirent *dir;
    d = opendir(".");//Note: current working directory is cmake-build-debug,where Project4.exe exists with SAL.
    if (d)
    {
        while ((dir = readdir(d)) != nullptr)
        {
            p1=strtok(dir->d_name,".");
            p2=strtok(nullptr,".");
            if(p2!=nullptr)
            {
                if(strcmp(p2,"txt")==0 && strcmp(p1, "CMakeCache") != 0)
                {
                    std::cout << p1 << std::endl;
                    files.emplace_back(p1);
                }
            }
        }
        closedir(d);
    }

    std::cout <<"Please choose any SAL file above and enter it's name:"<< std::endl;
    std::string input;
    std::cin >> input;
    if (std::find(files.begin(), files.end(), input) != files.end())
    {
        string line;
        ifstream myfile (input+".txt");
        int i=0;
        while ( myfile.good() )
        {
            getline (myfile,line);
            intp.memory.push_back(line);
            i++;
            if(i==256){
                std::cout << "Memory is full" << std::endl;
                break;
            }
        }
        myfile.close();

//To run 'l' after 'a'
//        source_code=intp.memory;
    }


    int f=1;
    while(f)
    {
        std::cout <<
        "\nEnter any of these command:\n"
        "l : To execute a line of code.\n"
        "a : To execute all instruction.\n"
        "q : To quit."
        << std::endl;

        char c;
        std::cin >> c;

        switch(c) {
            case 'l'  : {
                ptrdiff_t pos = find(intp.memory.begin(), intp.memory.end(), "HLT") - intp.memory.begin();

                if (std::count(intp.memory.begin(), intp.memory.end(), "HLT") && intp.program_counter == pos + 1 ) {
                    std::cout <<"You reached the HLT statement"<< std::endl;
                }
                else if(intp.program_counter == pos){
                    std::cout <<"You reached the end of instructions"<< std::endl;
                }
                else{
                    intp.interpreter(intp.memory[intp.program_counter]);
                    std::cout <<
                    "\n***All the instructions are executed***\n"
                    "Accumulator A="<< intp.accumulator<< "\n"<<
                    "Additional register B= "<< intp.additional_register<< "\n"<<
                    "Zero result bit ="<< intp.zero_result_bit<< "\n"<<
                    "Overflow bit = "<< intp.overflow_bit<< "\n"<<
                    "Program counter = "<< intp.program_counter
                    << std::endl;

                    std::cout << "Memory:" <<", "; //print memory content
                    for (auto & i : intp.memory)
                        std::cout << i<<", ";
                    std::cout <<"\n"<< std::endl;

                }
                continue;
            }

            case 'a'  : {
                ptrdiff_t pos = find(intp.memory.begin(), intp.memory.end(), "HLT") - intp.memory.begin();

                if (std::count(intp.memory.begin(), intp.memory.end(), "HLT")) {
                    while (intp.program_counter != pos + 1)
                        intp.interpreter(intp.memory[intp.program_counter]);
                }
                else{
                    while (intp.program_counter != pos)
                        intp.interpreter(intp.memory[intp.program_counter]);
                }

                std::cout <<
                "\n***All the instructions are executed***\n"
                "Accumulator A="<< intp.accumulator<< "\n"<<
                "Additional register B= "<< intp.additional_register<< "\n"<<
                "Zero result bit ="<< intp.zero_result_bit<< "\n"<<
                "Overflow bit = "<< intp.overflow_bit<< "\n"<<
                "Program counter = "<< intp.program_counter
                << std::endl;

                std::cout << "Memory:" <<", "; //print memory content
                for (auto & i : intp.memory)
                    std::cout << i<<", ";

//If we want to use 'l' after 'a' from address 0.
//                intp.memory=source_code;
//                intp.accumulator = 0;
//                intp.additional_register = 0;
//                intp.program_counter = 0;
//                intp.zero_result_bit = 0;
//                intp.overflow_bit = 0;
//                intp.data.clear();

                continue;
            }

            case 'q'  :{
                std::cout << "\nQuitting from command loop" << std::endl;
                f = 0;
                break;
            }

            default :
                std::cout << "Command loop does not recognize " << c << std::endl;
                continue;

        }

    }

    return(0);
}
