#include "HeaderParser.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/Utils.h" //InitializePreprocessor
#include "clang/Basic/TargetInfo.h" //TargetInfo
#include "llvm/Support/Host.h" //llvm::sys::getDefaultTargetTriple
#include "clang/Lex/Preprocessor.h" 
#include "clang/Lex/HeaderSearch.h" //HeaderSearch HeaderSearchOptions
#include <algorithm>

inline void initializeCompilerInstance(clang::CompilerInstance * ci)
{
  ci->createDiagnostics();
  llvm::IntrusiveRefCntPtr<clang::TargetOptions> pto( new clang::TargetOptions());
  pto->Triple = llvm::sys::getDefaultTargetTriple();
  clang::TargetInfo *pti = clang::TargetInfo::CreateTargetInfo(ci->getDiagnostics(), pto.getPtr());
  ci->setTarget(pti);
  ci->createFileManager();
  
  ci->createSourceManager(ci->getFileManager());
#ifdef CLANG_3_5
  ci->createPreprocessor(clang::TU_Complete);
#else
  ci->createPreprocessor(); 
#endif  
  ci->getPreprocessorOpts().UsePredefines = false;
}
namespace TruckBoris {
  HeaderParser::HeaderParser()
  {
    m_source = std::string();
    m_headersPaths = std::vector<std::string>();
    m_ci = new clang::CompilerInstance();
    initializeCompilerInstance(m_ci);
    m_hso = llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions>(new clang::HeaderSearchOptions());
    m_ciInitialized = true;
    m_headerElements = NULL;
  }
  HeaderParser::HeaderParser(const std::string& sourceFile, const std::vector<std::string>& headersPaths)
  {
    m_ci = new clang::CompilerInstance();
    initializeCompilerInstance(m_ci);
    m_hso = llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions>(new clang::HeaderSearchOptions());
    m_ciInitialized = true;
    addSourceFile(sourceFile);
    addSearchPaths(headersPaths);
    m_headerElements = NULL;
  }
  HeaderParser::~HeaderParser()
  {
  // FIXME 
    delete m_ci;
    delete m_headerElements;
  }
  bool HeaderParser::addSourceFile(const std::string& fileName)
  {
    if(!m_ciInitialized)
      return false; // TODO add an error message ?

    const clang::FileEntry *pFile = m_ci->getFileManager().getFile(fileName.c_str());
    if(!pFile)
    {
      m_source = std::string();
      return  false;
    }
    m_ci->getSourceManager().createMainFileID(pFile);
    m_source = fileName;
    return true;   
  }
  void HeaderParser::addSearchPath(const std::string& pathName)
  {
    if (std::find(m_headersPaths.begin(), m_headersPaths.end(), pathName) == m_headersPaths.end())
    {
      m_hso->AddPath( pathName.c_str(),
                      clang::frontend::Angled,
                      false,
                      false);
      m_headersPaths.push_back(pathName);
    }
  }
  void HeaderParser::addSearchPaths(const std::vector<std::string>& pathNames)
  {
    std::vector<std::string>::const_iterator it;
    for( it = pathNames.begin(); it != pathNames.end(); ++it)
    {
      addSearchPath((*it));
    }
  }
  bool 
  HeaderParser::parse()
  {
    //ci not initialized or no source to parse
    if(!m_ciInitialized || (m_source == std::string()) )
      return false;
    //clean all allowing to relaunch a parse  
    if ( m_headerElements )
    {
      // FIXME
      //delete m_headersElements;
    }
#ifdef CLANG_3_5
   //get gcc header with helpers 
    GenericGcc::GCCInstallationDetector gcc();
    if(gcc.isValid())
      gcc.print(llvm::outs); 
#endif
  clang::InitializePreprocessor(m_ci->getPreprocessor(),
                                m_ci->getPreprocessorOpts(),
                                *m_hso,
                                m_ci->getFrontendOpts()); 
    m_ci->createASTContext();
    m_headerElements = new HeaderElements();
    m_ci->setASTConsumer(m_headerElements);
    m_ci->getDiagnosticClient().BeginSourceFile(m_ci->getLangOpts()/*m_langOpts*/,
                                               &m_ci->getPreprocessor());
    clang::ParseAST(m_ci->getPreprocessor(), m_headerElements, m_ci->getASTContext());
    m_ci->getDiagnosticClient().EndSourceFile();
    return true;
  }
/*  bool 
  HeaderParser::parse(strd::string langage)
  {
    //ci not initialized or no source to parse
    if(!m_ciInitialized || (m_source == std::string()) )
      return false;
    //clean all allowing to relaunch a parse  
    if ( m_headerElements )
    {
      // FIXME
      //delete m_headersElements;
    }
#ifdef CLANG_3_5
   //get gcc header with helpers 
    GenericGcc::GCCInstallationDetector gcc();
    if(gcc.isValid())
      gcc.print(llvm::outs); 
#endif
  clang::InitializePreprocessor(m_ci->getPreprocessor(),
                                m_ci->getPreprocessorOpts(),
                                *m_hso,
                                m_ci->getFrontendOpts()); 
    m_ci->createASTContext();
    m_headerElements = new HeaderElements();
    m_ci->setASTConsumer(m_headerElements);
    m_ci->getDiagnosticClient().BeginSourceFile(m_langOpts,
                                               &m_ci->getPreprocessor());
    clang::ParseAST(m_ci->getPreprocessor(), m_headerElements, m_ci->getASTContext());
    m_ci->getDiagnosticClient().EndSourceFile();
    return true;
  }*/
  const clang::LangOptions& 
  HeaderParser::getLangOpts () const
  {
    return m_ci->getLangOpts()/*m_langOpts*/;
  }
  clang::SourceManager&
  HeaderParser::getSourceManager() const
  {
    return m_ci->getSourceManager();
  }
  std::vector<Function> 
  HeaderParser::getFunctions() const
  {
    return m_headerElements->getFunctions();
  }
  std::vector<Structure>
  HeaderParser::getStructures() const
  {
    return m_headerElements->getStructures();
  }
  std::vector<Enum>
  HeaderParser::getEnums() const
  {
    return m_headerElements->getEnums();
  }
  std::vector<Union>
  HeaderParser::getUnions() const
  {
    return m_headerElements->getUnions();
  }
  std::vector<Typedef>
  HeaderParser::getTypedefs() const
  {
    return m_headerElements->getTypedefs();
  }
  std::string
  HeaderParser::getSourceFile() const
  {
    return m_source;
  }
  std::vector<std::string>
  HeaderParser::getHeadersPaths() const
  {
    return m_headersPaths;
  }
  bool HeaderParser::isInitialized() const
  {
    return m_ciInitialized;
  }
}
