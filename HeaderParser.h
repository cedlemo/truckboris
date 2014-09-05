#ifndef HEADER_PARSER_H
#define HEADER_PARSER_H
#include "HeaderElements.h"
#include "clang/Frontend/CompilerInstance.h"
#include <string>
namespace TruckBoris {
  class HeaderParser
  {
    public:
      HeaderParser();
      HeaderParser( const std::string&  sourceFile, const std::vector<std::string>& headersPaths);
      ~HeaderParser();
      bool addSourceFile(const std::string& fileName);
      void addSearchPath(const std::string& pathName);
      void addSearchPaths(const std::vector<std::string>& pathNames);
      bool parse();
      const clang::LangOptions& getLangOpts () const;
      clang::SourceManager&   getSourceManager() const;
      std::vector<Function> getFunctions() const;
      std::vector<Structure> getStructures() const;
      std::vector<Union> getUnions() const;
      std::vector<Enum> getEnums() const;
      std::vector<Typedef> getTypedefs() const;
      std::string getSourceFile() const;
      std::vector<std::string> getHeadersPaths() const;
      bool isInitialized() const;
      bool isCpp() const;
    private:
      llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions> m_hso;
      bool m_ciInitialized;
      std::string m_source;
      std::vector<std::string> m_headersPaths;
      clang::CompilerInstance m_ci;
      HeaderElements m_headerElements; 
  };
}
#endif
