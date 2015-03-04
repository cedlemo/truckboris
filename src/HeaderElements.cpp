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
        if( !(m_inMainFile == true && !m_sourceManager->isInMainFile(fd->getLocStart())) )
        {
          Function fn(fd);  
          m_functions.push_back(fn);
        }
      }
      else if(clang::TypedefDecl *td = llvm::dyn_cast<clang::TypedefDecl>(*it))
      {
        if( !(m_inMainFile == true && !m_sourceManager->isInMainFile(td->getLocStart())) )
        {
          Typedef t_dc(td);
          m_typedefs.push_back(t_dc);
        }  
      }
    }
    return true;
  }
  void 
  HeaderElements::HandleTagDeclDefinition( clang::TagDecl * d)
  {
    if(d)
    {
      if( !(m_inMainFile == true && !m_sourceManager->isInMainFile(d->getLocStart())) )
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
  }
  int
  HeaderElements::nbFunctions() const
  {
    return m_functions.size();
  }
  Function
  HeaderElements::getFunction(int i) const
  {
    return m_functions[i];
  }
  int
  HeaderElements::nbTypedefs() const
  {
    return m_typedefs.size();
  }
  Typedef
  HeaderElements::getTypedef(int i) const
  {
    return m_typedefs[i];
  }
  std::vector<Typedef>
  HeaderElements::getTypedefs() const
  {
    return m_typedefs;
  }
  int
  HeaderElements::nbStructures() const
  {
    return m_structures.size();
  }
  Structure
  HeaderElements::getStructure(int i) const
  {
    return m_structures[i];
  }
  int
  HeaderElements::nbUnions() const
  {
    return m_unions.size();
  }
  Union
  HeaderElements::getUnion(int i) const
  {
    return m_unions[i];
  }
  int
  HeaderElements::nbEnums() const
  {
    return m_enums.size();
  }
  Enum
  HeaderElements::getEnum(int i) const
  {
    return m_enums[i];
  }
  std::vector<TagDeclaration> HeaderElements::getClasses() const
  {
    return m_classes;
  }
}
