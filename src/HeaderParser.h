#ifndef HEADER_PARSER_H
#define HEADER_PARSER_H
#include "HeaderElements.h"
#include "clang/Frontend/CompilerInstance.h"
#if HAVE_CONFIG_H
# include <config.h>
#endif
#include <string>
namespace TruckBoris {
  class HeaderParser
  {
    public:
      HeaderParser();
      HeaderParser( std::string sourceFile, std::vector<std::string> headersPaths);
      ~HeaderParser();
      bool addSourceFile( std::string fileName);
      void addSearchPath( std::string pathName);
      void addSearchPaths(std::vector<std::string> pathNames);
      bool parse(bool mainFile = false);
      clang::LangOptions& getLangOpts ();
      clang::SourceManager&   getSourceManager() const;
      int nbFunctions() const;
      Function getFunction(int) const;
      int nbStructures() const;
      Structure getStructure(int) const;
      int nbUnions() const;
      Union getUnion(int) const;
      std::vector<Union> getUnions() const;
      int nbEnums() const;
      Enum getEnum(int) const;
      std::vector<Enum> getEnums() const;
      int nbTypedefs() const;
      Typedef getTypedef(int) const;
      std::vector<Typedef> getTypedefs() const;
      std::string getSourceFile() const;
      std::vector<std::string> getHeadersPaths() const;
      std::vector<TagDeclaration> getClasses() const;
      bool isInitialized() const;
//      bool isCpp() const;
    private:
      llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions> m_hso;
      bool m_ciInitialized;
      std::string m_source;
      std::vector<std::string> m_headersPaths;
      clang::CompilerInstance m_ci;
      HeaderElements *m_headerElements;
  };
}
#endif
