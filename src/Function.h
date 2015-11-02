#ifndef FUNCTION_H
#define FUNCTION_H
#include "clang/AST/AST.h"
#include <string>
#include <vector>
#include "Declarations.h"
#if HAVE_CONFIG_H
# include <config.h>
#endif
namespace TruckBoris {
  class Function 
  {
    public:
      Function();
      Function(clang::FunctionDecl * fn);
      ~Function() {}
      Function& Equals(const Function& fct);
      std::string getName() const; 
      bool isMain() const;
      Type getReturn() const;
 //     void setPtr(clang::FunctionDecl * fn); //for ruby interface
 //     clang::FunctionDecl * getPtr() const; //for ruby interface
      unsigned int nbParameters() const;
      Parameter getParameter(unsigned int i) const; //for ruby interface
      std::string getRaw(clang::SourceManager &sm, const clang::LangOptions& lopt) const;
    private:
    clang::FunctionDecl * m_function;
  };
}
#endif
