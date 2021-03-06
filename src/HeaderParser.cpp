#include "HeaderParser.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/Utils.h" //InitializePreprocessor
#include "clang/Basic/TargetInfo.h" //TargetInfo
#include "llvm/Support/Host.h" //llvm::sys::getDefaultTargetTriple
#include "clang/Lex/Preprocessor.h" 
#include "clang/Lex/HeaderSearch.h" //HeaderSearch HeaderSearchOptions
#include "clang/Basic/Version.h"
#include <algorithm>
#include <iostream>

namespace TruckBoris {
  HeaderParser::HeaderParser()
  {
    m_source = std::string();
    m_headersPaths = std::vector<std::string>();
    
    m_ci.createDiagnostics();
    m_ci.createFileManager();
    m_ci.createSourceManager(m_ci.getFileManager());
    #if (CLANG_VERSION_MAJOR == 3 && CLANG_VERSION_MINOR >= 5)		
      std::shared_ptr<clang::TargetOptions> pto = std::make_shared<clang::TargetOptions>();
      pto->Triple = llvm::sys::getDefaultTargetTriple();
      clang::TargetInfo *pti = clang::TargetInfo::CreateTargetInfo(m_ci.getDiagnostics(), pto);
      m_ci.setTarget(pti);
      m_ci.createPreprocessor(clang::TU_Complete);		
    #else		
      m_hso = llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions>(new clang::HeaderSearchOptions());
      llvm::IntrusiveRefCntPtr<clang::TargetOptions> pto( new clang::TargetOptions());
      pto->Triple = llvm::sys::getDefaultTargetTriple();
      clang::TargetInfo *pti = clang::TargetInfo::CreateTargetInfo(m_ci.getDiagnostics(), pto.getPtr());
      m_ci.setTarget(pti);
      m_ci.createPreprocessor(); 		
    #endif     
    m_ciInitialized = true;
    m_headerElements = NULL;
  }
  HeaderParser::HeaderParser( std::string sourceFile, std::vector<std::string> headersPaths)
  {
    m_source = std::string();
    m_headersPaths = std::vector<std::string>();
    
    m_ci.createDiagnostics();
    m_ci.createFileManager();
    m_ci.createSourceManager(m_ci.getFileManager());
    #if (CLANG_VERSION_MAJOR == 3 && CLANG_VERSION_MINOR >= 5)		
      std::shared_ptr<clang::TargetOptions> pto = std::make_shared<clang::TargetOptions>();
      pto->Triple = llvm::sys::getDefaultTargetTriple();
      clang::TargetInfo *pti = clang::TargetInfo::CreateTargetInfo(m_ci.getDiagnostics(), pto);
      m_ci.setTarget(pti);
      m_ci.createPreprocessor(clang::TU_Complete);		
    #else		
      m_hso = llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions>(new clang::HeaderSearchOptions());
      llvm::IntrusiveRefCntPtr<clang::TargetOptions> pto( new clang::TargetOptions());
      pto->Triple = llvm::sys::getDefaultTargetTriple();
      clang::TargetInfo *pti = clang::TargetInfo::CreateTargetInfo(m_ci.getDiagnostics(), pto.getPtr());
      m_ci.setTarget(pti);
      m_ci.createPreprocessor(); 		
    #endif
    m_ciInitialized = true;
    addSourceFile(sourceFile);
    addSearchPaths(headersPaths);
    m_headerElements = NULL;
  }
  HeaderParser::~HeaderParser()
  {
  // FIXME 
    //delete m_ci;
    //delete m_headerElements;
  }
  bool HeaderParser::addSourceFile( std::string fileName)
  {
    if(!m_ciInitialized)
      return false; // TODO add an error message ?

    const clang::FileEntry *pFile = m_ci.getFileManager().getFile(fileName.c_str());
    if(!pFile)
    {
      m_source = std::string();
      return  false;
    }
    clang::FileID id = m_ci.getSourceManager().createFileID(pFile,
                                                          clang::SourceLocation(),
                                                          clang::SrcMgr::C_User);
    m_ci.getSourceManager().setMainFileID(id);
    m_source = fileName;

    return true;   
  }
  void HeaderParser::addSearchPath( std::string pathName)
  {
    if (std::find(m_headersPaths.begin(), m_headersPaths.end(), pathName) == m_headersPaths.end())
    {
      m_ci.getHeaderSearchOpts().AddPath( pathName.c_str(),
                      clang::frontend::Angled,
                      false,
                      false);
      m_headersPaths.push_back(pathName);
    }
  }
  void HeaderParser::addSearchPaths( std::vector<std::string> pathNames)
  {
    std::vector<std::string>::const_iterator it;
    for( it = pathNames.begin(); it != pathNames.end(); ++it)
    {
      addSearchPath((*it));
    }
  }
  bool 
  HeaderParser::parse(bool mainFile)
  {
    //ci not initialized or no source to parse
    if(!m_ciInitialized || (m_source == std::string()) )
      return false;
    //clean all allowing to relaunch a parse  
    //if ( m_headerElements )
    //{
      // FIXME
      //delete m_headersElements;
    //}
#if (CLANG_VERSION_MAJOR == 3 && CLANG_VERSION_MINOR >= 7)		
   m_ci.createPreprocessor(clang::TU_Complete);
   clang::InitializePreprocessor(m_ci.getPreprocessor(),
                                m_ci.getPreprocessorOpts(),
                                m_ci.getPCHContainerReader(),
                        				m_ci.getFrontendOpts());
#elif (CLANG_VERSION_MAJOR == 3 && CLANG_VERSION_MINOR >= 5)		
   //get gcc header with helpers 
//    GenericGcc::GCCInstallationDetector gcc();
//    if(gcc.isValid())
//      gcc.print(llvm::outs); 
   m_ci.createPreprocessor(clang::TU_Complete);
   clang::InitializePreprocessor(m_ci.getPreprocessor(),
                                m_ci.getPreprocessorOpts(),
                        				m_ci.getFrontendOpts());
#else
   m_ci.createPreprocessor();	
   clang::InitializePreprocessor(m_ci.getPreprocessor(),
                                m_ci.getPreprocessorOpts(),
                                m_ci.getHeaderSearchOpts(),
		                          	m_ci.getFrontendOpts()); 
#endif

    m_headerElements = new HeaderElements(&(getSourceManager()), mainFile);
#if (CLANG_VERSION_MAJOR == 3 && CLANG_VERSION_MINOR >= 5)		
    m_ci.setASTConsumer(llvm::make_unique<clang::ASTConsumer>(*m_headerElements));
#else
    m_ci.setASTConsumer(m_headerElements);
#endif
    m_ci.createASTContext();
    m_ci.getDiagnosticClient().BeginSourceFile(m_ci.getLangOpts()/*m_langOpts*/,
                                               &m_ci.getPreprocessor());
    clang::ParseAST(m_ci.getPreprocessor(), m_headerElements, m_ci.getASTContext());
    m_ci.getDiagnosticClient().EndSourceFile();
    return true;
  }
  clang::LangOptions& 
  HeaderParser::getLangOpts ()
  {
    return m_ci.getLangOpts()/*m_langOpts*/;
  }
  clang::SourceManager&
  HeaderParser::getSourceManager() const
  {
    return m_ci.getSourceManager();
  }
  int 
  HeaderParser::nbFunctions() const
  {
    if(m_source == std::string())
      return 0;
    else
      return m_headerElements->nbFunctions();
  }
  Function
  HeaderParser::getFunction(int i) const
  {
    if(m_source == std::string())
      return Function();
    int j = i;
    int max = m_headerElements->nbFunctions() - 1;
    if (i < 0)
      j = 0;
    else if ( i > max)
      j = max;
    return m_headerElements->getFunction(j);
  }
  int 
  HeaderParser::nbStructures() const
  {
    if(m_source == std::string())
      return 0;
    else
      return m_headerElements->nbStructures();
  }
  Structure
  HeaderParser::getStructure(int i) const
  {
    if(m_source == std::string())
      return Structure();
    int j = i;
    int max = m_headerElements->nbStructures() - 1;
    if (i < 0)
      j = 0;
    else if ( i > max)
      j = max;
    return m_headerElements->getStructure(j);
  }
  int 
  HeaderParser::nbEnums() const
  {
    if(m_source == std::string())
      return 0;
    else
      return m_headerElements->nbEnums();
  }
  Enum
  HeaderParser::getEnum(int i) const
  {
    if(m_source == std::string())
      return Enum();
    int j = i;
    int max = m_headerElements->nbEnums() - 1;
    if (i < 0)
      j = 0;
    else if ( i > max)
      j = max;
    return m_headerElements->getEnum(j);
  }
  int 
  HeaderParser::nbUnions() const
  {
    if(m_source == std::string())
      return 0;
    else
      return m_headerElements->nbUnions();
  }
  Union
  HeaderParser::getUnion(int i) const
  {
    if(m_source == std::string())
      return Union();
    int j = i;
    int max = m_headerElements->nbUnions() - 1;
    if (i < 0)
      j = 0;
    else if ( i > max)
      j = max;
    return m_headerElements->getUnion(j);
  }
  int 
  HeaderParser::nbTypedefs() const
  {
    if(m_source == std::string())
      return 0;
    else
      return m_headerElements->nbTypedefs();
  }
  Typedef
  HeaderParser::getTypedef(int i) const
  {
    if(m_source == std::string())
      return Typedef();
    int j = i;
    int max = m_headerElements->nbTypedefs() - 1;
    if (i < 0)
      j = 0;
    else if ( i > max)
      j = max;
    return m_headerElements->getTypedef(j);
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
  std::vector<TagDeclaration> 
  HeaderParser::getClasses() const
  {
    if (m_source == std::string())
      return std::vector<TagDeclaration>();

    return m_headerElements->getClasses();
  }
  bool HeaderParser::isInitialized() const
  {
    return m_ciInitialized;
  }
}
