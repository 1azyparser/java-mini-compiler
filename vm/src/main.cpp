#include "Machine.h"
#include "Program.h"
#include <cxxopts.hpp>
#include <iomanip>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv)
{
  cxxopts::Options options("virtual machine",
                           "A VM for running minijava byte code");

  auto adder = options.add_options();
  adder("p,print", "Enable printing parsed operations",
        cxxopts::value<bool>()->default_value("false"));
  adder("i,input", "Input byte code", cxxopts::value<string>());
  adder("h,help", "Print usage");

  auto result = options.parse(argc, argv);

  if (result.count("help"))
  {
    cout << options.help() << endl;
    return 0;
  }
  else
  {
    bool enable_printing = result["print"].as<bool>();
    if (result.count("input"))
    {
      string input_path = result["input"].as<string>();
      try
      {
        Program program = load_program(input_path);

        if (enable_printing)
        {
          json json_obj = program_to_json(program);
          cout << std::setw(4) << json_obj << endl;
        }

        Machine machine(program, 10000);
        machine.run();
      }
      catch (VMError &err)
      {
        cerr << err.msg << endl;
      }
      return 0;
    }
    else
    {
      cout << options.help() << endl;
      return 0;
    }
  }
}