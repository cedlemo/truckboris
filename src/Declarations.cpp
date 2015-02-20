#include "Declarations.h"
#include <iostream>
namespace TruckBoris {
  Typedef::Typedef(): m_var(NULL)
  {}
  Typedef::Typedef(clang::TypedefDecl * var) : m_var(var)
  {}
/*  void Typedef::setPtr(clang::TypedefDecl * var) //for ruby interface
  {
    m_var = var;
  }*/
  Typedef& Typedef::Equals(const Typedef& tpd)
  {
    m_var = tpd.m_var;
    return *this;
  }
/*  clang::TypedefDecl * Typedef::getPtr() const//for ruby interface
  {
    return m_var;
  }*/
  std::string Typedef::getName() const
  {
    if(m_var)
      return m_var->getNameAsString();
    else
      return std::string();
  }
  Type Typedef::getType() const
  {
    if(m_var)
      return Type(m_var->getUnderlyingType());
    else
      return Type();
  }
  std::string Typedef::getRaw(clang::SourceManager &sm, const clang::LangOptions& lopt) const
  {
    clang::SourceLocation b(m_var->getLocStart()), _e(m_var->getLocEnd());
    clang::SourceLocation e(clang::Lexer::getLocForEndOfToken(_e, 0, 
                                                              sm, 
                                                              lopt));
   
    return std::string(sm.getCharacterData(b), sm.getCharacterData(e)-sm.getCharacterData(b));
  }
  Parameter::Parameter(): m_var(NULL)
  {}
  Parameter::Parameter(clang::ParmVarDecl * var): m_var(var)
  {}
  Parameter& Parameter::Equals(const Parameter& pdc)
  {
    m_var = pdc.m_var;
    return *this;
  }
/*  void Parameter::setPtr(clang::ParmVarDecl * var) //for ruby interface
  {
    m_var = var;
  }
  clang::ParmVarDecl * Parameter::getPtr() const //for ruby interface
  {
    return m_var;
  }*/
  std::string Parameter::getName() const
  {
    if(m_var)
      return m_var->getNameAsString();  
    else
      return std::string();
  }
  Type Parameter::getType() const
  {
    if(m_var)
      return Type(m_var->getOriginalType());
    else
      return Type();
  }
  Field::Field(): m_var(NULL)
  {
  }
  Field::Field(clang::FieldDecl * var): m_var(var)
  {}
  Field& Field::Equals(const Field& fld)
  {
    m_var = fld.m_var;
    return *this;
  }
/*  void Field::setPtr(clang::FieldDecl * var) //for ruby interface
  {
    m_var = var;
  }
  clang::FieldDecl * Field::getPtr() const //for ruby interface
  {
    return m_var;
  }*/
  std::string Field::getName() const
  {
    if(m_var)
      return m_var->getNameAsString();  
    else
      return std::string();
  }
  Type Field::getType() const
  {
    if(m_var)
      return Type(m_var->getType());
    else
      return Type();
  }
  TagDeclaration::TagDeclaration(): m_var(NULL)
  {}
  TagDeclaration::TagDeclaration(clang::TagDecl *var): m_var(var)
  {}
/*  void TagDeclaration::setPtr(clang::TagDecl *var)//for ruby interface
  {
    m_var = var;
  }
  clang::TagDecl * TagDeclaration::getPtr() const//for ruby interface
  {
    return m_var;
  }*/
  std::string TagDeclaration::getName() const
  {
    if(m_var)
      return m_var->getNameAsString();
    else
      return std::string();
  }

  bool TagDeclaration::hasNameForLinkage() const
  {
    if(m_var)
      return m_var->hasNameForLinkage();
    else
      return false;
  }

  bool TagDeclaration::hasLinkage() const
  {
    if(m_var)
      return m_var->hasLinkage();
    else
      return false;
  }
  std::string TagDeclaration::getTypedefName() const
  {
    if(!m_var)
      return std::string();
    clang::TypedefNameDecl * tpdefName = NULL;
    tpdefName = m_var->getTypedefNameForAnonDecl();
    if( tpdefName != NULL )
      return tpdefName->getNameAsString();
    else
      return std::string();
  }
  std::string TagDeclaration::getRaw(clang::SourceManager &sm, const clang::LangOptions& lopt) const
  {
    clang::SourceLocation b(m_var->getLocStart()), _e(m_var->getLocEnd());
    clang::SourceLocation e(clang::Lexer::getLocForEndOfToken(_e, 0, 
                                                              sm, 
                                                              lopt));
   
    return std::string(sm.getCharacterData(b), sm.getCharacterData(e)-sm.getCharacterData(b));
  }
  TagDeclaration & TagDeclaration::Equals(const TagDeclaration& tag)
  {
    m_var = tag.m_var;
    return *this;
  }
  Structure::Structure(): TagDeclaration()
  {
    m_tagType = std::string("structure");
  }
  Structure::Structure(clang::TagDecl * var) : TagDeclaration(var)
  {
    m_tagType = std::string("structure");
  }
  std::string Structure::getTagType() const
  {
    return m_tagType;
  }
  Structure& Structure::Equals(const Structure& tag)
  {
    m_var = tag.m_var;
    return *this;
  }
  std::vector<Field> Structure::getFields() const
  {
    std::vector<Field> fields;
    
    clang::RecordDecl *r;
    r = llvm::cast<clang::RecordDecl>(m_var);
    clang::RecordDecl::field_iterator jt;
    for(jt = r->field_begin(); jt != r->field_end(); ++jt)
    {
      fields.push_back(Field(*jt));
    }
    return fields;
  }
  clang::FieldDecl* Structure::getField(int i) const
  {
    std::vector<clang::FieldDecl *> fields;
    
    clang::RecordDecl *r;
    r = llvm::cast<clang::RecordDecl>(m_var);
    clang::RecordDecl::field_iterator jt;
    for(jt = r->field_begin(); jt != r->field_end(); ++jt)
    {
      fields.push_back((*jt));
    }
    if(i>= 0 && i < fields.size() )
      return fields[i];
    else
      return NULL;
  }
  int Structure::getFieldsNumber() const
  {
    clang::RecordDecl *r;
    r = llvm::cast<clang::RecordDecl>(m_var);
    clang::RecordDecl::field_iterator jt;
    int i =0;
    for(jt = r->field_begin(); jt != r->field_end(); ++jt)
    {
      i++;
    }
    return i;
  }
  Union::Union() : TagDeclaration()
  {
    m_tagType = std::string("union");
  }
  Union::Union(clang::TagDecl * var) : TagDeclaration(var)
  {
    m_tagType = std::string("union");
  }
  std::string Union::getTagType() const
  {
    return m_tagType;
  }
  Union& Union::Equals(const Union& tag)
  {
    m_var = tag.m_var;
    return *this;
  }
  std::vector<Field> Union::getFields() const
  {
    std::vector<Field> fields;
    
    clang::RecordDecl *r;
    r = llvm::cast<clang::RecordDecl>(m_var);
    clang::RecordDecl::field_iterator jt;
    for(jt = r->field_begin(); jt != r->field_end(); ++jt)
    {
      fields.push_back(Field(*jt));
    }
    return fields;
  }
  clang::FieldDecl* Union::getField(int i) const
  {
    std::vector<clang::FieldDecl *> fields;
    
    clang::RecordDecl *r;
    r = llvm::cast<clang::RecordDecl>(m_var);
    clang::RecordDecl::field_iterator jt;
    for(jt = r->field_begin(); jt != r->field_end(); ++jt)
    {
      fields.push_back((*jt));
    }
    if(i>= 0 && i < fields.size() )
      return fields[i];
    else
      return NULL;
  }
  int Union::getFieldsNumber() const
  {
    clang::RecordDecl *r;
    r = llvm::cast<clang::RecordDecl>(m_var);
    clang::RecordDecl::field_iterator jt;
    int i =0;
    for(jt = r->field_begin(); jt != r->field_end(); ++jt)
    {
      i++;
    }
    return i;
  }
  Enum::Enum(): TagDeclaration()
  {
    m_tagType = std::string("enum");
  }
  Enum::Enum(clang::TagDecl *var): TagDeclaration(var)
  {
    m_tagType = std::string("enum");
  }
  Enum& Enum::Equals(const Enum& enu)
  {
    m_var = enu.m_var;
    return *this;
  }
  std::string Enum::getTagType() const
  {
    return m_tagType;
  }
  int Enum::getConstantsNumber() const
  {
    int i = 0;
    clang::EnumDecl *e;
    e = llvm::cast<clang::EnumDecl>(m_var);
    clang::EnumDecl::enumerator_iterator it;
    for(it=e->enumerator_begin(); it !=e->enumerator_end(); ++it)
    {
      i++;
    } 
    return i;
  }
  std::vector<EnumConstant> Enum::getConstants() const
  {
    std::vector<EnumConstant> constants;
    clang::EnumDecl *e;
    e = llvm::cast<clang::EnumDecl>(m_var);
    clang::EnumDecl::enumerator_iterator it;
    for(it=e->enumerator_begin(); it !=e->enumerator_end(); ++it)
    {
      EnumConstant c(*it);
      constants.push_back(c);
    } 
    return constants;
  }
  clang::EnumConstantDecl * Enum::getConstant(int i) const
  {
    clang::EnumDecl *e;
    std::vector<clang::EnumConstantDecl *> constants;
    e = llvm::cast<clang::EnumDecl>(m_var);
    clang::EnumDecl::enumerator_iterator it;
    int j =0;
    for(it=e->enumerator_begin(); it !=e->enumerator_end(); ++it)
    {
      j++;
      constants.push_back(*it);
    }
    if(i>0 && i <j)
      return constants[i];
    else
      return NULL;
  }
  /*void Enum::printEnumsConstant() const
  {
    clang::EnumDecl *e;
    e = llvm::cast<clang::EnumDecl>(m_var);
    clang::EnumDecl::enumerator_iterator it;
    for(it=e->enumerator_begin(); it !=e->enumerator_end(); ++it)
    {
      clang::EnumConstantDecl * enumerator= (*it);
      std::cout << enumerator->getNameAsString() << "  " << enumerator->getInitVal().getSExtValue() << std::endl;
    }
  }*/
  EnumConstant::EnumConstant(): m_constant(NULL)
  {
  }
  EnumConstant::EnumConstant(clang::EnumConstantDecl * constant): m_constant(constant)
  {
  }
  EnumConstant& EnumConstant::Equals(const EnumConstant& cst)
  {
    m_constant = cst.m_constant;
    return *this;
  }
/*  void EnumConstant::setPtr(clang::EnumConstantDecl * constant)
  {
    m_constant = constant;
  }
  clang::EnumConstantDecl * EnumConstant::getPtr() const
  {
    return m_constant;
  }*/
  std::string EnumConstant::getName() const
  {
    return m_constant->getNameAsString();
  }
  int EnumConstant::getValue() const
  {
    return m_constant->getInitVal().getSExtValue();
  }
}
