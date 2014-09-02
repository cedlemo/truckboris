#ifndef TYPE_H
#define TYPE_H
#include "clang/AST/AST.h"
#include "string"
namespace TruckBoris {
  class Type
  {
    public:
      Type();
      Type(const clang::QualType & type);
      ~Type() {}
      Type& Equals(const Type& tpe);
      std::string getName() const;
      bool isCanonical() const;
      Type withConst() const;
      Type withVolatile() const;
      Type withRestrict() const;
      Type getCanonicalType() const;
      Type getUnqualifiedType() const;
      Type getLocalUnqualifiedType() const;
      Type getLocallyUnqualifiedSingleStepDesugaredType() const;
      Type getNonReferenceType() const;
      bool isEmpty() const;
      void setClangQualType(const clang::QualType & type);
      clang::QualType getClangQualType() const;
      const clang::Type * getClangTypePtr() const;
      std::string getClangTypeClassName() const;
      //getDecl ( cast<RecordDecl>(cast<RecordType>(T)->getDecl() ) 
    private:
      clang::QualType m_type;
      bool m_empty;
  };
}
#endif
