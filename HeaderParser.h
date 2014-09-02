#ifndef HEADER_PARSER_H
#define HEADER_PARSER_H
#include "HeaderElements.h"
#include "clang/Frontend/CompilerInstance.h"
#include <string>
namespace TruckBoris {
  class HeaderParser
  {
    public:
      /*HeaderParser(); ambiguous with the following methods when no args*/
      HeaderParser(clang::InputKind langage = clang::IK_C);
      HeaderParser( const std::string&  sourceFile, const std::vector<std::string>& headersPaths, clang::InputKind langage = clang::IK_C);
      ~HeaderParser();
      bool addSourceFile(const std::string& fileName);
      void addSearchPath(const std::string& pathName);
      void addSearchPaths(const std::vector<std::string>& pathNames);
      bool parse();
      //bool parse(std::string langage);
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
      clang::CompilerInstance *m_ci;
      clang::InputKind m_langage;
      clang::LangOptions m_langOpts;
      HeaderElements * m_headerElements; 
      bool m_Cpp;
  };
}
#endif
