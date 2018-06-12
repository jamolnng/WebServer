#pragma once
#ifdef max
#undef max
#endif
#include <limits>
#include <stack>
#include <string>
#include <vector>

template <typename _data_type = unsigned short>
class BrainFuck {
 public:
  using data_type = _data_type;

  BrainFuck(size_t maxProgramSize = 4096, size_t maxStackSize = 512)
      : maxProgramSize(maxProgramSize), maxStackSize(maxStackSize) {}

  void compile(const std::string& str) {
    program.clear();
    std::stack<data_type> stack;
    for (char c : str) {
      if (program.size() == maxProgramSize)
        throw std::exception("Program excedes max program size.");
      switch (c) {
        case ']':
          if (stack.size() == 0)
            throw std::exception(
                "Stack error. Are you missing an opening '['?");
          program.push_back(Instruction(c, stack.top()));
          program[program.back().operand].operand =
              static_cast<data_type>(program.size());
          stack.pop();
          break;
        case '[':
          if (stack.size() == maxStackSize)
            throw std::exception("Max stack size exceded.");
          stack.push(static_cast<data_type>(program.size()));
        case '>':
        case '<':
        case '+':
        case '-':
        case '.':
        case ',':
          program.push_back(Instruction(c));
          break;
      }
    }
    if (!stack.empty())
      throw std::exception("Stack error. Are you missing a closing ']'?");
    if (program.size() > maxProgramSize)
      throw std::exception("Program excedes max program size.");
  }

  template <class _in, class _out>
  void exec(_in& in, _out& out) {
    std::vector<data_type> data(maxDataSize, data_type());
    auto ptr = data.begin();
    for (auto pos = program.begin(); pos != program.end() && ptr != data.end();
         ++pos) {
      switch (pos->opt) {
        case '>':
          ++ptr;
          break;
        case '<':
          --ptr;
          break;
        case '+':
          (*ptr)++;
          break;
        case '-':
          (*ptr)--;
          break;
        case '.':
          out.put(static_cast<typename std::ostream::char_type>(*ptr));
          break;
        case ',':
          *ptr = static_cast<data_type>(in.get());
          break;
        case '[':
          if (!*ptr) pos = std::next(program.begin(), pos->operand);
          break;
        case ']':
          if (*ptr) pos = std::next(program.begin(), pos->operand);
          break;
        default:
          throw std::exception("invalid operator");
      }
    }
    if (ptr == data.end())
      throw std::exception("data limit exceeded during execution");
  }

 private:
  class Instruction {
   public:
    Instruction(char opt) : opt(opt) {}
    Instruction(char opt, data_type ptr) : opt(opt), operand(ptr) {}
    char opt{};
    data_type operand{};
  };
  std::vector<Instruction> program;
  size_t maxProgramSize;
  size_t maxStackSize;
  size_t maxDataSize{std::numeric_limits<data_type>::max()};
};
