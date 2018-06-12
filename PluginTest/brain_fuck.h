#pragma once
#ifdef max
#undef max
#endif
#include <limits>
#include <stack>
#include <string>
#include <vector>

template <typename _ptr = unsigned short>
class BrainFuck {
 public:
  using ptr = _ptr;

  BrainFuck(size_t maxProgramSize = 4096, size_t maxStackSize = 512)
      : maxProgramSize(maxProgramSize), maxStackSize(maxStackSize) {}

  void compile(const std::string& str) {
    program.clear();
    ptr pc = 0;
    ptr jump;
    std::stack<ptr> stack;
    for (char c : str) {
      if (pc == maxProgramSize)
        throw std::exception("Program excedes max program size.");
      switch (c) {
        case ']':
          if (stack.size() == 0)
            throw std::exception(
                "Stack error. Are you missing an opening '['?");
          jump = stack.top();
          stack.pop();
          program.push_back(Instruction(c, jump));
          program[jump].operand = pc;
          break;
        case '[':
          if (stack.size() == maxStackSize)
            throw std::exception("Max stack size exceded.");
          stack.push(pc);
        case '>':
        case '<':
        case '+':
        case '-':
        case '.':
        case ',':
          program.push_back(Instruction(c));
          break;
        default:
          pc--;
          break;
      }
      pc++;
    }
    if (!stack.empty())
      throw std::exception("Stack error. Are you missing a closing ']'?");
    if (pc == maxProgramSize)
      throw std::exception("Program excedes max program size.");
    program.push_back(Instruction('\0'));
  }

  template <class _in, class _out>
  void exec(_in& in, _out& out) {
    std::vector<ptr> data(maxDataSize, ptr());
    ptr pc = 0;
    ptr p = 0;
    while (program[pc].opt != '\0' && p < maxDataSize) {
      switch (program[pc].opt) {
        case '>':
          p++;
          break;
        case '<':
          p--;
          break;
        case '+':
          data[p]++;
          break;
        case '-':
          data[p]--;
          break;
        case '.':
          out.put(static_cast<typename _out::char_type>(data[p]));
          break;
        case ',':
          data[p] = static_cast<ptr>(in.get());
          break;
        case '[':
          if (!data[p]) pc = program[pc].operand;
          break;
        case ']':
          if (data[p]) pc = program[pc].operand;
          break;
        default:
          throw std::exception("invalid operator");
      }
      pc++;
    }
    if (p == maxDataSize)
      throw std::exception("data limit exceeded during execution");
  }

 private:
  class Instruction {
   public:
    Instruction(char opt) : opt(opt) {}
    Instruction(char opt, ptr ptr) : opt(opt), operand(ptr) {}
    char opt{};
    ptr operand{};
  };
  std::vector<Instruction> program;
  size_t maxProgramSize;
  size_t maxStackSize;
  size_t maxDataSize{std::numeric_limits<ptr>::max()};
};
