#ifndef _MYEXCEPTION_HPP_
#define _MYEXCEPTION_HPP_
class MyException {
  public:
     MyException(const std::string msg = "") : message(msg) 
    { }
    std::string what()
    {     return message;    }
  private:
    std::string message;
  };


#endif