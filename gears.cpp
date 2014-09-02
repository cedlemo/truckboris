//#include <vector>
//#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/Utils.h" //InitializePreprocessor
#include "clang/Basic/TargetInfo.h" //TargetInfo
#include "llvm/Support/Host.h" //llvm::sys::getDefaultTargetTriple
#include "clang/Lex/Preprocessor.h" 
#include "clang/Lex/HeaderSearch.h" //HeaderSearch HeaderSearchOptions
//#include "clang/AST/AST.h"
//#include "clang/AST/ASTContext.h"
//#include "clang/AST/ASTConsumer.h"
//#include "clang/Parse/Parser.h"
//#include "clang/Parse/ParseAST.h"
#include <unistd.h> // getopt
#include <iostream> 
#include "gears.h"
#include <string>

void displayUsage(char * progName, const char * error)
{
  if(error)
    std::cerr << error << std::endl;
  std::cout << progName << " SourceFileName" << std::endl;
}

void parseArgs(int argc, char **argv, std::vector<std::string>& sourceFiles, std::vector<std::string>& searchPaths)
{
  if(argc <2)
  {
    displayUsage(argv[0], NULL);
    exit(1);
  } 

  int opt;
  while( (opt = getopt(argc, argv, ":hI:")) !=-1 ) {
    switch(opt){
      case 'h': 
        displayUsage(argv[0], NULL); 
        exit(1);
      case 'I':
        { 
          std::string arg(optarg);
          searchPaths.push_back(arg); 
          break;
        }
      case ':': 
        displayUsage(argv[0],"Missing arguments");
        exit(1);
      case '?': 
        displayUsage(argv[0],"Unrecognized option");
        break;
      default: 
        displayUsage(argv[0],"Unexpected case");
        exit(1);
    }
  }
  
  if(optind < argc)
  {
    for(int i =optind; i < argc; i++)
    {
      std::string last_arg(argv[i]);
      sourceFiles.push_back(last_arg);
    }
  }
}

//using clang::CompilerInstance;
//using clang::TargetOptions;
//using clang::TargetInfo;
//using clang::HeaderSearchOptions;
//using clang::HeaderSearch;
//using clang::FileEntry;

void initializeCompilerInstance(clang::CompilerInstance& ci, const std::vector<std::string>& searchPaths)
{
  ci.createDiagnostics();
  llvm::IntrusiveRefCntPtr<clang::TargetOptions> pto( new clang::TargetOptions());
  pto->Triple = llvm::sys::getDefaultTargetTriple();
  clang::TargetInfo *pti = clang::TargetInfo::CreateTargetInfo(ci.getDiagnostics(), pto.getPtr());
  ci.setTarget(pti);
  ci.createFileManager();
  
  ci.createFileManager();
  ci.createSourceManager(ci.getFileManager());
#ifdef CLANG_3_5
  ci.createPreprocessor(clang::TU_Complete);
#else
  ci.createPreprocessor(); 
#endif  
  
  ci.getPreprocessorOpts().UsePredefines = false; //initialize preprocess with predefines from compiler
  llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions> hso(new clang::HeaderSearchOptions()); 
#ifdef CLANG_3_5
   //get gcc header with helpers 
    GenericGcc::GCCInstallationDetector gcc();
    if(gcc.isValid())
      gcc.print(llvm::outs); 
#endif
  clang::InitializePreprocessor(ci.getPreprocessor(),
                                ci.getPreprocessorOpts(),
                                *hso,
                                ci.getFrontendOpts()); 

  clang::HeaderSearch headerSearch(hso,
                            ci.getSourceManager(),
                            ci.getDiagnostics(),
                            ci.getLangOpts(),
                            pti);
  hso->AddPath( "/usr/include",
                clang::frontend::Angled,
                false,
                false);
  std::vector<std::string>::const_iterator it;
  for( it = searchPaths.begin(); it != searchPaths.end(); ++it)
  {
    hso->AddPath( (*it).c_str(),
                  clang::frontend::Angled,
                  false,
                  false);
  }
}

bool loadSourceFile(clang::CompilerInstance& ci, const std::string& name)
{
  const clang::FileEntry *pFile = ci.getFileManager().getFile(name.c_str());
  if(!pFile)
    return  false;
  
  ci.getSourceManager().createMainFileID(pFile);
  return true;
}

