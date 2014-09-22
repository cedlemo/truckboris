#include "HeaderElements.h"
#include <iostream>
namespace TruckBoris {
  bool 
  HeaderElements::HandleTopLevelDecl( clang::DeclGroupRef d ) 
  {
    clang::DeclGroupRef::iterator it;
    for( it = d.begin(); it != d.end(); it++)
    {
        if(clang::FunctionDecl *fd = llvm::dyn_cast<clang::FunctionDecl>(*it))
        {
          Function fn(fd);  
          m_functions.push_back(fn);
        }
        else if(clang::TypedefDecl *td = llvm::dyn_cast<clang::TypedefDecl>(*it))
        {
            Typedef t_dc(td);
            m_typedefs.push_back(t_dc);
        }
    }
    return true;
  }
  void 
  HeaderElements::HandleTagDeclDefinition( clang::TagDecl * d)
  {
    if(d)
    {
      TagDeclaration tag(d);
      if(d->isStruct())
      {
        Structure s(d);
        m_structures.push_back(s);
      }
      if(d->isUnion())
      {
        Union u(d);
        m_unions.push_back(u);
      }
      if(d->isEnum())
      {
        Enum e(d);
        m_enums.push_back(e);
      }
      if(d->isClass())
        m_classes.push_back(tag);
    }
  }
  std::vector<Function> 
  HeaderElements::getFunctions() const
  {
    return m_functions;
  }
  std::vector<Typedef>
  HeaderElements::getTypedefs() const
  {
    return m_typedefs;
  }
  std::vector<Structure>
  HeaderElements::getStructures() const
  {
    return m_structures;
  }
  std::vector<Union>
  HeaderElements::getUnions() const
  {
    return m_unions;
  }
  std::vector<Enum>
  HeaderElements::getEnums() const
  {
    return m_enums;
  }
  std::vector<TagDeclaration> HeaderElements::getClasses() const
  {
    return m_classes;
  }
}
