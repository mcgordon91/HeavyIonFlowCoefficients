// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dOsl73_x8664_gcc485dIobjdIStRootdIStEpdUtildIStEpdUtil_Cint

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "StEpdFastSim/StEpdTrivialEventGenerator.h"
#include "StEpdFastSim/StEpdFastSim.h"
#include "StBbcGeom.h"
#include "StEpdGeom.h"
#include "StEpdEpInfo.h"
#include "StEpdEpFinder.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *StEpdTrivialEventGenerator_Dictionary();
   static void StEpdTrivialEventGenerator_TClassManip(TClass*);
   static void *new_StEpdTrivialEventGenerator(void *p = 0);
   static void *newArray_StEpdTrivialEventGenerator(Long_t size, void *p);
   static void delete_StEpdTrivialEventGenerator(void *p);
   static void deleteArray_StEpdTrivialEventGenerator(void *p);
   static void destruct_StEpdTrivialEventGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StEpdTrivialEventGenerator*)
   {
      ::StEpdTrivialEventGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::StEpdTrivialEventGenerator));
      static ::ROOT::TGenericClassInfo 
         instance("StEpdTrivialEventGenerator", "StEpdFastSim/StEpdTrivialEventGenerator.h", 13,
                  typeid(::StEpdTrivialEventGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &StEpdTrivialEventGenerator_Dictionary, isa_proxy, 0,
                  sizeof(::StEpdTrivialEventGenerator) );
      instance.SetNew(&new_StEpdTrivialEventGenerator);
      instance.SetNewArray(&newArray_StEpdTrivialEventGenerator);
      instance.SetDelete(&delete_StEpdTrivialEventGenerator);
      instance.SetDeleteArray(&deleteArray_StEpdTrivialEventGenerator);
      instance.SetDestructor(&destruct_StEpdTrivialEventGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StEpdTrivialEventGenerator*)
   {
      return GenerateInitInstanceLocal((::StEpdTrivialEventGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::StEpdTrivialEventGenerator*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *StEpdTrivialEventGenerator_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::StEpdTrivialEventGenerator*)0x0)->GetClass();
      StEpdTrivialEventGenerator_TClassManip(theClass);
   return theClass;
   }

   static void StEpdTrivialEventGenerator_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *StEpdFastSim_Dictionary();
   static void StEpdFastSim_TClassManip(TClass*);
   static void *new_StEpdFastSim(void *p = 0);
   static void *newArray_StEpdFastSim(Long_t size, void *p);
   static void delete_StEpdFastSim(void *p);
   static void deleteArray_StEpdFastSim(void *p);
   static void destruct_StEpdFastSim(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StEpdFastSim*)
   {
      ::StEpdFastSim *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::StEpdFastSim));
      static ::ROOT::TGenericClassInfo 
         instance("StEpdFastSim", "StEpdFastSim/StEpdFastSim.h", 10,
                  typeid(::StEpdFastSim), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &StEpdFastSim_Dictionary, isa_proxy, 0,
                  sizeof(::StEpdFastSim) );
      instance.SetNew(&new_StEpdFastSim);
      instance.SetNewArray(&newArray_StEpdFastSim);
      instance.SetDelete(&delete_StEpdFastSim);
      instance.SetDeleteArray(&deleteArray_StEpdFastSim);
      instance.SetDestructor(&destruct_StEpdFastSim);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StEpdFastSim*)
   {
      return GenerateInitInstanceLocal((::StEpdFastSim*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::StEpdFastSim*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *StEpdFastSim_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::StEpdFastSim*)0x0)->GetClass();
      StEpdFastSim_TClassManip(theClass);
   return theClass;
   }

   static void StEpdFastSim_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_StBbcGeom(void *p = 0);
   static void *newArray_StBbcGeom(Long_t size, void *p);
   static void delete_StBbcGeom(void *p);
   static void deleteArray_StBbcGeom(void *p);
   static void destruct_StBbcGeom(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StBbcGeom*)
   {
      ::StBbcGeom *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StBbcGeom >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StBbcGeom", ::StBbcGeom::Class_Version(), "StBbcGeom.h", 34,
                  typeid(::StBbcGeom), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StBbcGeom::Dictionary, isa_proxy, 4,
                  sizeof(::StBbcGeom) );
      instance.SetNew(&new_StBbcGeom);
      instance.SetNewArray(&newArray_StBbcGeom);
      instance.SetDelete(&delete_StBbcGeom);
      instance.SetDeleteArray(&deleteArray_StBbcGeom);
      instance.SetDestructor(&destruct_StBbcGeom);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StBbcGeom*)
   {
      return GenerateInitInstanceLocal((::StBbcGeom*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::StBbcGeom*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StEpdGeom(void *p = 0);
   static void *newArray_StEpdGeom(Long_t size, void *p);
   static void delete_StEpdGeom(void *p);
   static void deleteArray_StEpdGeom(void *p);
   static void destruct_StEpdGeom(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StEpdGeom*)
   {
      ::StEpdGeom *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StEpdGeom >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StEpdGeom", ::StEpdGeom::Class_Version(), "StEpdGeom.h", 24,
                  typeid(::StEpdGeom), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StEpdGeom::Dictionary, isa_proxy, 4,
                  sizeof(::StEpdGeom) );
      instance.SetNew(&new_StEpdGeom);
      instance.SetNewArray(&newArray_StEpdGeom);
      instance.SetDelete(&delete_StEpdGeom);
      instance.SetDeleteArray(&deleteArray_StEpdGeom);
      instance.SetDestructor(&destruct_StEpdGeom);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StEpdGeom*)
   {
      return GenerateInitInstanceLocal((::StEpdGeom*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::StEpdGeom*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *StEpdEpInfo_Dictionary();
   static void StEpdEpInfo_TClassManip(TClass*);
   static void *new_StEpdEpInfo(void *p = 0);
   static void *newArray_StEpdEpInfo(Long_t size, void *p);
   static void delete_StEpdEpInfo(void *p);
   static void deleteArray_StEpdEpInfo(void *p);
   static void destruct_StEpdEpInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StEpdEpInfo*)
   {
      ::StEpdEpInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::StEpdEpInfo));
      static ::ROOT::TGenericClassInfo 
         instance("StEpdEpInfo", "StEpdEpInfo.h", 11,
                  typeid(::StEpdEpInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &StEpdEpInfo_Dictionary, isa_proxy, 4,
                  sizeof(::StEpdEpInfo) );
      instance.SetNew(&new_StEpdEpInfo);
      instance.SetNewArray(&newArray_StEpdEpInfo);
      instance.SetDelete(&delete_StEpdEpInfo);
      instance.SetDeleteArray(&deleteArray_StEpdEpInfo);
      instance.SetDestructor(&destruct_StEpdEpInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StEpdEpInfo*)
   {
      return GenerateInitInstanceLocal((::StEpdEpInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::StEpdEpInfo*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *StEpdEpInfo_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::StEpdEpInfo*)0x0)->GetClass();
      StEpdEpInfo_TClassManip(theClass);
   return theClass;
   }

   static void StEpdEpInfo_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_StEpdEpFinder(void *p = 0);
   static void *newArray_StEpdEpFinder(Long_t size, void *p);
   static void delete_StEpdEpFinder(void *p);
   static void deleteArray_StEpdEpFinder(void *p);
   static void destruct_StEpdEpFinder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StEpdEpFinder*)
   {
      ::StEpdEpFinder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StEpdEpFinder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StEpdEpFinder", ::StEpdEpFinder::Class_Version(), "StEpdEpFinder.h", 100,
                  typeid(::StEpdEpFinder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StEpdEpFinder::Dictionary, isa_proxy, 4,
                  sizeof(::StEpdEpFinder) );
      instance.SetNew(&new_StEpdEpFinder);
      instance.SetNewArray(&newArray_StEpdEpFinder);
      instance.SetDelete(&delete_StEpdEpFinder);
      instance.SetDeleteArray(&deleteArray_StEpdEpFinder);
      instance.SetDestructor(&destruct_StEpdEpFinder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StEpdEpFinder*)
   {
      return GenerateInitInstanceLocal((::StEpdEpFinder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::StEpdEpFinder*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr StBbcGeom::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StBbcGeom::Class_Name()
{
   return "StBbcGeom";
}

//______________________________________________________________________________
const char *StBbcGeom::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StBbcGeom*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StBbcGeom::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StBbcGeom*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StBbcGeom::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StBbcGeom*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StBbcGeom::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StBbcGeom*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StEpdGeom::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StEpdGeom::Class_Name()
{
   return "StEpdGeom";
}

//______________________________________________________________________________
const char *StEpdGeom::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StEpdGeom*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StEpdGeom::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StEpdGeom*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StEpdGeom::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StEpdGeom*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StEpdGeom::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StEpdGeom*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StEpdEpFinder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StEpdEpFinder::Class_Name()
{
   return "StEpdEpFinder";
}

//______________________________________________________________________________
const char *StEpdEpFinder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StEpdEpFinder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StEpdEpFinder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StEpdEpFinder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StEpdEpFinder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StEpdEpFinder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StEpdEpFinder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StEpdEpFinder*)0x0)->GetClass(); }
   return fgIsA;
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StEpdTrivialEventGenerator(void *p) {
      return  p ? new(p) ::StEpdTrivialEventGenerator : new ::StEpdTrivialEventGenerator;
   }
   static void *newArray_StEpdTrivialEventGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::StEpdTrivialEventGenerator[nElements] : new ::StEpdTrivialEventGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_StEpdTrivialEventGenerator(void *p) {
      delete ((::StEpdTrivialEventGenerator*)p);
   }
   static void deleteArray_StEpdTrivialEventGenerator(void *p) {
      delete [] ((::StEpdTrivialEventGenerator*)p);
   }
   static void destruct_StEpdTrivialEventGenerator(void *p) {
      typedef ::StEpdTrivialEventGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StEpdTrivialEventGenerator

namespace ROOT {
   // Wrappers around operator new
   static void *new_StEpdFastSim(void *p) {
      return  p ? new(p) ::StEpdFastSim : new ::StEpdFastSim;
   }
   static void *newArray_StEpdFastSim(Long_t nElements, void *p) {
      return p ? new(p) ::StEpdFastSim[nElements] : new ::StEpdFastSim[nElements];
   }
   // Wrapper around operator delete
   static void delete_StEpdFastSim(void *p) {
      delete ((::StEpdFastSim*)p);
   }
   static void deleteArray_StEpdFastSim(void *p) {
      delete [] ((::StEpdFastSim*)p);
   }
   static void destruct_StEpdFastSim(void *p) {
      typedef ::StEpdFastSim current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StEpdFastSim

//______________________________________________________________________________
void StBbcGeom::Streamer(TBuffer &R__b)
{
   // Stream an object of class StBbcGeom.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StBbcGeom::Class(),this);
   } else {
      R__b.WriteClassBuffer(StBbcGeom::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StBbcGeom(void *p) {
      return  p ? new(p) ::StBbcGeom : new ::StBbcGeom;
   }
   static void *newArray_StBbcGeom(Long_t nElements, void *p) {
      return p ? new(p) ::StBbcGeom[nElements] : new ::StBbcGeom[nElements];
   }
   // Wrapper around operator delete
   static void delete_StBbcGeom(void *p) {
      delete ((::StBbcGeom*)p);
   }
   static void deleteArray_StBbcGeom(void *p) {
      delete [] ((::StBbcGeom*)p);
   }
   static void destruct_StBbcGeom(void *p) {
      typedef ::StBbcGeom current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StBbcGeom

//______________________________________________________________________________
void StEpdGeom::Streamer(TBuffer &R__b)
{
   // Stream an object of class StEpdGeom.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StEpdGeom::Class(),this);
   } else {
      R__b.WriteClassBuffer(StEpdGeom::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StEpdGeom(void *p) {
      return  p ? new(p) ::StEpdGeom : new ::StEpdGeom;
   }
   static void *newArray_StEpdGeom(Long_t nElements, void *p) {
      return p ? new(p) ::StEpdGeom[nElements] : new ::StEpdGeom[nElements];
   }
   // Wrapper around operator delete
   static void delete_StEpdGeom(void *p) {
      delete ((::StEpdGeom*)p);
   }
   static void deleteArray_StEpdGeom(void *p) {
      delete [] ((::StEpdGeom*)p);
   }
   static void destruct_StEpdGeom(void *p) {
      typedef ::StEpdGeom current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StEpdGeom

namespace ROOT {
   // Wrappers around operator new
   static void *new_StEpdEpInfo(void *p) {
      return  p ? new(p) ::StEpdEpInfo : new ::StEpdEpInfo;
   }
   static void *newArray_StEpdEpInfo(Long_t nElements, void *p) {
      return p ? new(p) ::StEpdEpInfo[nElements] : new ::StEpdEpInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_StEpdEpInfo(void *p) {
      delete ((::StEpdEpInfo*)p);
   }
   static void deleteArray_StEpdEpInfo(void *p) {
      delete [] ((::StEpdEpInfo*)p);
   }
   static void destruct_StEpdEpInfo(void *p) {
      typedef ::StEpdEpInfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StEpdEpInfo

//______________________________________________________________________________
void StEpdEpFinder::Streamer(TBuffer &R__b)
{
   // Stream an object of class StEpdEpFinder.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StEpdEpFinder::Class(),this);
   } else {
      R__b.WriteClassBuffer(StEpdEpFinder::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StEpdEpFinder(void *p) {
      return  p ? new(p) ::StEpdEpFinder : new ::StEpdEpFinder;
   }
   static void *newArray_StEpdEpFinder(Long_t nElements, void *p) {
      return p ? new(p) ::StEpdEpFinder[nElements] : new ::StEpdEpFinder[nElements];
   }
   // Wrapper around operator delete
   static void delete_StEpdEpFinder(void *p) {
      delete ((::StEpdEpFinder*)p);
   }
   static void deleteArray_StEpdEpFinder(void *p) {
      delete [] ((::StEpdEpFinder*)p);
   }
   static void destruct_StEpdEpFinder(void *p) {
      typedef ::StEpdEpFinder current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StEpdEpFinder

namespace {
  void TriggerDictionaryInitialization_StEpdUtil_Cint_Impl() {
    static const char* headers[] = {
"StEpdFastSim/StEpdTrivialEventGenerator.h",
"StEpdFastSim/StEpdFastSim.h",
"StBbcGeom.h",
"StEpdGeom.h",
"StEpdEpInfo.h",
"StEpdEpFinder.h",
0
    };
    static const char* includePaths[] = {
".sl73_x8664_gcc485/obj/StRoot/StEpdUtil",
"StRoot/StEpdUtil",
"StRoot/StEpdUtil",
"StRoot",
".sl73_x8664_gcc485/include",
"/afs/rhic.bnl.gov/star/packages/SL20d/StRoot/StEpdUtil",
"/afs/rhic.bnl.gov/star/packages/SL20d",
"/afs/rhic.bnl.gov/star/packages/SL20d/StRoot",
"/afs/rhic.bnl.gov/star/packages/SL20d/.sl73_x8664_gcc485/include",
"/afs/rhic.bnl.gov/star/ROOT/6.16.00/.sl73_x8664_gcc485/rootdeb/include",
"/afs/rhic.bnl.gov/star/ROOT/37/6.16.00/.sl73_x8664_gcc485/rootdeb/include",
"/direct/star+u/mcgordon/PicoDSTAccess/accessPicos/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "StEpdUtil_Cint dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$StEpdFastSim/StEpdTrivialEventGenerator.h")))  StEpdTrivialEventGenerator;
class __attribute__((annotate("$clingAutoload$StEpdFastSim/StEpdFastSim.h")))  StEpdFastSim;
class __attribute__((annotate("$clingAutoload$StBbcGeom.h")))  StBbcGeom;
class __attribute__((annotate("$clingAutoload$StEpdGeom.h")))  StEpdGeom;
class __attribute__((annotate("$clingAutoload$StEpdEpInfo.h")))  StEpdEpInfo;
class __attribute__((annotate("$clingAutoload$StEpdEpFinder.h")))  StEpdEpFinder;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "StEpdUtil_Cint dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef ROOT_CINT
  #define ROOT_CINT 1
#endif
#ifndef __ROOT__
  #define __ROOT__ 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "StEpdFastSim/StEpdTrivialEventGenerator.h"
#include "StEpdFastSim/StEpdFastSim.h"
#include "StBbcGeom.h"
#include "StEpdGeom.h"
#include "StEpdEpInfo.h"
#include "StEpdEpFinder.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"StBbcGeom", payloadCode, "@",
"StEpdEpFinder", payloadCode, "@",
"StEpdEpInfo", payloadCode, "@",
"StEpdFastSim", payloadCode, "@",
"StEpdGeom", payloadCode, "@",
"StEpdTrivialEventGenerator", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("StEpdUtil_Cint",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_StEpdUtil_Cint_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_StEpdUtil_Cint_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_StEpdUtil_Cint() {
  TriggerDictionaryInitialization_StEpdUtil_Cint_Impl();
}
