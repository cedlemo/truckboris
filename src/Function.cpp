#include "Function.h"
#include <string>
#include <vector>
#include "Declarations.h"
#include "clang/Basic/Version.h"
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
/*  void Function::setPtr(clang::FunctionDecl * fn) //for ruby interface
  {
    m_function = fn;
  }
  clang::FunctionDecl * Function::getPtr() const
  {
    return m_function; 
  }*/
  std::string Function::getName() const
  {
    if(m_function)
      return m_function->getNameInfo().getAsString();
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
    #if (CLANG_VERSION_MAJOR == 3 && CLANG_VERSION_MINOR >= 5)		
      return Type(m_function->getReturnType() );
    #else
      return Type(m_function->getResultType() );
    #endif	
    else
      return Type();
  }
  unsigned int
  Function::nbParameters() const
  {
    if(m_function)
      return m_function->getNumParams();
    else
      return 0;
  }
  Parameter
  Function::getParameter(unsigned int i) const //for ruby interface
  {
    if(!m_function)
      return NULL;

    unsigned int j;
    if( i > m_function->getNumParams() )
      j = m_function->getNumParams();
    else
      j = i;

    return Parameter(m_function->getParamDecl(j));
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
