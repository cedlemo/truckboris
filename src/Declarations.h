#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include "clang/AST/AST.h"
#include "clang/Lex/Lexer.h"
#include <string>
#include "Type.h"
#if HAVE_CONFIG_H
# include <config.h>
#endif
namespace TruckBoris {
  class Typedef
  {
    public:
      Typedef();
      Typedef(clang::TypedefDecl * var);
      ~Typedef() {}
      Typedef& Equals(const Typedef& tpd);
      void setPtr(clang::TypedefDecl * var); //for ruby interface
      clang::TypedefDecl * getPtr() const; //for ruby interface
      std::string getName() const;
      Type getType() const;
      std::string getRaw(clang::SourceManager &sm, const clang::LangOptions& lopt) const;
    private:
      clang::TypedefDecl * m_var;
  };

  class Parameter
  {
    public:
      Parameter();
      Parameter(clang::ParmVarDecl * var);
      ~Parameter() {}
      Parameter& Equals(const Parameter& pdc);
      void setPtr(clang::ParmVarDecl * var); //for ruby interface
      clang::ParmVarDecl * getPtr() const; //for ruby interface
      std::string getName() const;
      Type getType() const;
    private:
      clang::ParmVarDecl * m_var;
  };
  class Field
  {
    public:
      Field();
      Field(clang::FieldDecl * var);
      ~Field() {}
      Field& Equals(const Field& fld);
      void setPtr(clang::FieldDecl * var); //for ruby interface
      clang::FieldDecl * getPtr() const; //for ruby interface
      std::string getName() const;
      Type getType() const;
    private:
      clang::FieldDecl * m_var;
  };
  class TagDeclaration
  {
    public:
      TagDeclaration(clang::TagDecl * var);
      ~TagDeclaration(){}
      void setPtr(clang::TagDecl * var); //for ruby interface
      clang::TagDecl * getPtr() const; //for ruby interface
      std::string getName() const;
      bool hasNameForLinkage()const;
      bool hasLinkage() const;
      std::string getTypedefName() const;
      std::string getRaw( clang::SourceManager & sm, const clang::LangOptions & lopt) const;
      /*virtual*/TagDeclaration& Equals( const TagDeclaration & tag);
    protected:
      clang::TagDecl * m_var; 
  };
  class Structure : public TagDeclaration
  {
    public:
      Structure();
      Structure(clang::TagDecl * var);
      ~Structure() {}
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Woverloaded-virtual"
      /*virtual*/ Structure& Equals(const Structure& tag);
//#pragma clang diagnostic pop
      std::string getTagType() const;
      int getFieldsNumber() const;
      std::vector<Field> getFields() const;
      clang::FieldDecl * getField(int i) const;
    private:
      std::string m_tagType;
  };
  class Union : public TagDeclaration
  {
    public:
      Union();
      Union(clang::TagDecl * var);
      ~Union() {}
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Woverloaded-virtual"
      /*virtual*/ Union& Equals(const Union& tag);
//#pragma clang diagnostic pop
      std::string getTagType() const;
      int getFieldsNumber() const;
      std::vector<Field> getFields() const;
      clang::FieldDecl * getField(int i) const;
    private:
      std::string m_tagType;
  };
  class EnumConstant
  {
    public:
      EnumConstant();
      EnumConstant(clang::EnumConstantDecl * constant);
      ~EnumConstant() {}
      EnumConstant& Equals(const EnumConstant& cst);
      void setPtr(clang::EnumConstantDecl * constant);
      clang::EnumConstantDecl * getPtr() const;
      std::string getName() const;
      int getValue() const;
    private:
      clang::EnumConstantDecl  * m_constant;
  };
  class Enum : public TagDeclaration
  {
    public:
      Enum();
      Enum(clang::TagDecl * var);
      ~Enum() {}
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Woverloaded-virtual"        
      /*virtual*/ Enum& Equals(const Enum& enu);
//#pragma clang diagnostic pop
      std::string getTagType() const;
      int getConstantsNumber() const;
      std::vector<EnumConstant> getConstants() const;
      clang::EnumConstantDecl * getConstant(int i) const;
  //    void printEnumsConstant() const;
    private:
      std::string m_tagType;
  };
}

#endif
