#include "Function.h"
#include <string>
#include <vector>
#include "Declarations.h"
namespace TruckBoris {
  Function::Function() : m_function(NULL)
  {}
  Function::Function(clang::FunctionDecl * fn): m_function(fn)
  {}
  Function& Function::Equals(const Function& fct)
  {
    m_function = fct.m_function;
    return *this;
  }
  void Function::setPtr(clang::FunctionDecl * fn) //for ruby interface
  {
    m_function = fn;
  }
  clang::FunctionDecl * Function::getPtr() const
  {
    return m_function; 
  }
  std::string Function::getName() const
  {
    if(m_function)
      return m_function->getDeclName().getAsString();
    else
      return std::string();
  }
  bool Function::isMain() const
  {
    if(m_function)
      return m_function->isMain();
    else
      return false;
  }
  Type Function::getReturn() const
  {
    if(m_function)
      return Type(m_function->getReturnType() );
    else
      return Type();
  }
  int Function::getParamsNumber() const
  {
    if(m_function)
      return m_function->getNumParams();
    else
      return 0;
  }
  std::vector<Parameter>
  Function::getParameters() const
  {
    std::vector<Parameter> params;
    if(!m_function)
      return params;

    for(int i=0; i < m_function->getNumParams(); i++)
    {
      Parameter p(m_function->getParamDecl(i));
      params.push_back(p);
    }
    return params;
  }
  clang::ParmVarDecl * Function::getParameter(int i) const //for ruby interface
  {
    if(!m_function)
      return NULL;

    int j;
    if(i < 0)
      j = 0;
    else if( i > m_function->getNumParams() )
      j = m_function->getNumParams();
    else
      j = i;

    return m_function->getParamDecl(j);
  }
  std::string Function::getRaw(clang::SourceManager &sm, const clang::LangOptions& lopt) const
  {
    clang::SourceLocation b(m_function->getLocStart()), _e(m_function->getLocEnd());
    clang::SourceLocation e(clang::Lexer::getLocForEndOfToken(_e, 0, 
                                                              sm, 
                                                              lopt));
   
    return std::string(sm.getCharacterData(b), sm.getCharacterData(e)-sm.getCharacterData(b));
  }
}
