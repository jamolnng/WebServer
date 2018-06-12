#pragma once
#ifdef max
#undef max
#endif
#include <iostream>
#include <limits>
#include <stack>
#include <string>
#include <vector>

template <typename ptr = unsigned short>
class BrainFuck {
 public:
  BrainFuck(size_t _MAX_PROGRAM_SIZE = 4096, size_t _MAX_STACK_SIZE = 512)
      : MAX_PROGRAM_SIZE(_MAX_PROGRAM_SIZE), MAX_STACK_SIZE(_MAX_STACK_SIZE) {}
  void compile(const std::string& str) {
    program.clear();
    ptr pc = 0;
    ptr jump;
    std::stack<ptr> stack;
    for (char c : str) {
      if (pc == MAX_PROGRAM_SIZE)
        throw std::exception("max program size reached");
      switch (c) {
        case ']':
          if (stack.size() == 0) throw std::exception("stack not populated");
          jump = stack.top();
          stack.pop();
          program.push_back(Instruction(c, jump));
          program[jump].operand = pc;
          break;
        case '[':
          if (stack.size() == MAX_STACK_SIZE)
            throw std::exception("max stack size reached");
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
    if (!stack.empty()) throw std::exception("stack error");
    if (pc == MAX_PROGRAM_SIZE) throw std::exception("pc error");
    program.push_back(Instruction('\0'));
  }

  template <class _in, class _out>
  void run(_in& in, _out& out) {
    std::vector<ptr> data(MAX_DATA_SIZE, ptr());
    ptr pc = 0;
    ptr p = 0;
    while (program[pc].opt != '\0' && p < MAX_DATA_SIZE) {
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
    if (p == MAX_DATA_SIZE)
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
  size_t MAX_PROGRAM_SIZE;
  size_t MAX_STACK_SIZE;
  size_t MAX_DATA_SIZE{std::numeric_limits<ptr>::max()};
};
