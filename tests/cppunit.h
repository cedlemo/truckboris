#ifndef COMPAT_CPPUNIT_H
#define COMPAT_CPPUNIT_H
/*Code taken from cppunit/extensions/HelperMacros.h version 1.13
If the system doesn't supports the auto_ptr, then this code is used. Otherwise
the cppunit Macros stays untouched.
*/
#ifndef HAVE_UNIQUE_PTR
    #include <cppunit/extensions/HelperMacros.h>

    #undef CPPUNIT_TEST_SUITE_END
#define CPPUNIT_TEST_SUITE_END()                                               \
    }                                                                          \
      									       \
    struct CppUnitExDeleter { /* avoid deprecated auto_ptr warnings */         \
	CPPUNIT_NS::TestSuite *suite;					       \
	CppUnitExDeleter() : suite (0) {}				       \
	~CppUnitExDeleter() { delete suite; }				       \
	CPPUNIT_NS::TestSuite *release() {                                     \
		CPPUNIT_NS::TestSuite *tmp = suite; suite = NULL; return tmp;  \
        }                                                                      \
    };                                                                         \
                                                                               \
public:									       \
    static CPPUNIT_NS::TestSuite *suite()                                      \
    {                                                                          \
      const CPPUNIT_NS::TestNamer &namer = getTestNamer__();                   \
      CppUnitExDeleter guard;                                                  \
      guard.suite = new CPPUNIT_NS::TestSuite( namer.getFixtureName() );       \
      CPPUNIT_NS::ConcretTestFixtureFactory<TestFixtureType> factory;          \
      CPPUNIT_NS::TestSuiteBuilderContextBase context( *guard.suite,           \
                                                       namer,                  \
                                                       factory );              \
      TestFixtureType::addTestsToSuite( context );                             \
      return guard.release();                                                  \
    }                                                                          \
  private: /* dummy typedef so that the macro can still end with ';'*/         \
    typedef int CppUnitDummyTypedefForSemiColonEnding__
#else
	#include <cppunit/extensions/HelperMacros.h>
#endif /*HAVE_UNIQUE_PTR*/

#endif /* COMPAT_CPPUNIT_H */
