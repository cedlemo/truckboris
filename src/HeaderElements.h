#ifndef HEADER_ELEMENTS_H
#define HEADER_ELEMENTS_H
#include "clang/AST/AST.h" //DeclGroupRef TagDecl FunctionDecl TypedefDecl
#include "clang/AST/ASTConsumer.h"
#include <vector>
#include "Declarations.h"
#include "Function.h"
#include <iostream>
#if HAVE_CONFIG_H
# include <config.h>
#endif
namespace TruckBoris {
  class HeaderElements : public clang::ASTConsumer
  {
    public:
      HeaderElements(clang::SourceManager *sourceManager, bool inMainFile = false) : clang::ASTConsumer() { 
        m_sourceManager = sourceManager;
        m_inMainFile = inMainFile;
      }
      virtual ~HeaderElements() { }

      virtual bool HandleTopLevelDecl( clang::DeclGroupRef d);
      virtual void HandleTagDeclDefinition( clang::TagDecl * d);
      std::vector<Function> getFunctions() const;
      std::vector<Typedef> getTypedefs() const;
      std::vector<Structure> getStructures() const;
      std::vector<Union> getUnions() const;
      std::vector<Enum> getEnums() const;
      std::vector<TagDeclaration> getClasses() const;
    private:
      std::vector<Function> m_functions;
      std::vector<Typedef> m_typedefs;
      std::vector<Structure> m_structures;
      std::vector<Union> m_unions;
      std::vector<Enum> m_enums;
      std::vector<TagDeclaration> m_classes;
      clang::SourceManager *m_sourceManager;
      bool m_inMainFile;
      /*add methods for classes*/
  };
}
#endif
