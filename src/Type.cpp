#include "Type.h"
namespace TruckBoris {
  Type::Type(): m_empty(true)
  {}
  Type::Type(const clang::QualType & type) : m_type(type), m_empty(false)
  {}
  Type& Type::Equals(const Type& tpe)
  {
    m_empty = tpe.m_empty;
    m_type = tpe.m_type;
    return *this;
  }
  std::string Type::getName() const
  {
    if(m_empty)
      return std::string();
    else
      return m_type.getAsString();
  }
  bool Type::isCanonical() const
  {
    if(m_empty)
      return false;
      
    return m_type.isCanonical();
  }
  Type Type::withConst() const
  {
    if(m_empty)
      return Type();
    else
      return Type(m_type.withConst());
  }
  Type Type::withVolatile() const
  {
    if(m_empty)
      return Type();
    else
      return Type(m_type.withVolatile());
  }  
  Type Type::withRestrict() const
  {
    if(m_empty)
      return Type();
    else
      return Type(m_type.withRestrict());
  }
  Type Type::getCanonicalType() const
  {
    if(m_empty)
      return Type();
    else
      return Type(m_type.getCanonicalType());
  }
  Type Type::getUnqualifiedType() const
  {
    if(m_empty)
      return Type();
    else
      return Type(m_type.getUnqualifiedType());

  }
  Type Type::getLocalUnqualifiedType() const
  {
    if(m_empty)
      return Type();
    else
      return Type(m_type.getLocalUnqualifiedType());
  }
  Type Type::getLocallyUnqualifiedSingleStepDesugaredType() const
  {
    if(m_empty)
      return Type();
    else
      return Type(m_type.getTypePtr()->getLocallyUnqualifiedSingleStepDesugaredType());
  }
  Type Type::getNonReferenceType() const
  {
    if(m_empty)
      return Type();
    else
      return Type(m_type.getNonReferenceType());
  }
  bool Type::isEmpty() const
  {
    return m_empty;
  }
  void Type::setClangQualType(const clang::QualType & type)
  {
    m_type = type;
    m_empty = false;
  }
  clang::QualType Type::getClangQualType() const
  {
    return m_type;
  }
  const clang::Type * Type::getClangTypePtr() const
  {
    return m_type.getTypePtr();
  }
  std::string Type::getClangTypeClassName() const
  {
    return std::string(m_type.getTypePtr()->getTypeClassName());
  }
} 
