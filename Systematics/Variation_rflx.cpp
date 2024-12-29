// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Variation_rflx
#define R__NO_DEPRECATION

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

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "Variation.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *Variation_Dictionary();
   static void Variation_TClassManip(TClass*);
   static void delete_Variation(void *p);
   static void deleteArray_Variation(void *p);
   static void destruct_Variation(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Variation*)
   {
      ::Variation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Variation));
      static ::ROOT::TGenericClassInfo 
         instance("Variation", "", 11,
                  typeid(::Variation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Variation_Dictionary, isa_proxy, 0,
                  sizeof(::Variation) );
      instance.SetDelete(&delete_Variation);
      instance.SetDeleteArray(&deleteArray_Variation);
      instance.SetDestructor(&destruct_Variation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Variation*)
   {
      return GenerateInitInstanceLocal((::Variation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Variation*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Variation_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Variation*)0x0)->GetClass();
      Variation_TClassManip(theClass);
   return theClass;
   }

   static void Variation_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Variation(void *p) {
      delete ((::Variation*)p);
   }
   static void deleteArray_Variation(void *p) {
      delete [] ((::Variation*)p);
   }
   static void destruct_Variation(void *p) {
      typedef ::Variation current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Variation

namespace {
  void TriggerDictionaryInitialization_Variation_rflx_Impl() {
    static const char* headers[] = {
"0",
0
    };
    static const char* includePaths[] = {
"/afs/rhic.bnl.gov/star/ROOT/38/6.20.08/.sl73_x8664_gcc485/rootdeb/include/",
"/direct/star+u/mcgordon/VnFromEPD/Systematics/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Variation_rflx dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class Variation;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Variation_rflx dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef VARIATION_H
#define VARIATION_H

#include <vector>
#include "TString.h"
#include "TH1D.h"
#include "TFile.h"

class Variation
{
 public:
  Variation(TString prefix, TString order_n_str);
  ~Variation();
  TString ID;

//   TH1D *h_vn_pp;
//   TH1D *h_vn_pm;
//   TH1D *h_vn_kp;
//   TH1D *h_vn_km;
//   TH1D *h_vn_pr;
//   TH1D *h_vn_de;
//   TH1D *h_vn_tr;
//   TH1D *h_vn_he3;
//   TH1D *h_vn_he4;
  
//   TH1D *h_vn_yCM_00to10_pr;
  TH1D *h_vn_yCM_10to40_pr;
//   TH1D *h_vn_yCM_40to60_pr;
//   TH1D *h_vn_yCM_00to10_kp;
  TH1D *h_vn_yCM_10to40_kp;
//   TH1D *h_vn_yCM_40to60_kp;
//   TH1D *h_vn_yCM_00to10_km;
  TH1D *h_vn_yCM_10to40_km;
//   TH1D *h_vn_yCM_40to60_km;
//   TH1D *h_vn_yCM_00to10_pp;
  TH1D *h_vn_yCM_10to40_pp;
//   TH1D *h_vn_yCM_40to60_pp;
//   TH1D *h_vn_yCM_00to10_pm;
  TH1D *h_vn_yCM_10to40_pm;
//   TH1D *h_vn_yCM_40to60_pm;
  
//   TH1D *h_vn_yCM_00to10_pr_symm;
//   TH1D *h_vn_yCM_10to40_pr_symm;
//   TH1D *h_vn_yCM_40to60_pr_symm;

//   TH1D *h_vn_yCM_00to10_de;
  TH1D *h_vn_yCM_10to40_de;
//   TH1D *h_vn_yCM_40to60_de;
//   TH1D *h_vn_yCM_00to10_tr;
  TH1D *h_vn_yCM_10to40_tr;
//   TH1D *h_vn_yCM_40to60_tr;
//   TH1D *h_vn_yCM_00to10_he3;
//   TH1D *h_vn_yCM_10to40_he3;
//   TH1D *h_vn_yCM_40to60_he3;
//   TH1D *h_vn_yCM_00to10_he4;
//   TH1D *h_vn_yCM_10to40_he4;
//   TH1D *h_vn_yCM_40to60_he4;

//   TH1D *h_vn_pT_00to10_pr;
//   TH1D *h_vn_pT_10to40_pr;
//   TH1D *h_vn_pT_40to60_pr;  
//   TH1D *h_vn_pT_00to10_pr_yMid;
//   TH1D *h_vn_pT_10to40_pr_yMid;
//   TH1D *h_vn_pT_40to60_pr_yMid;  
//   TH1D *h_vn_pT_00to10_pr_yFor;
//   TH1D *h_vn_pT_10to40_pr_yFor;
//   TH1D *h_vn_pT_40to60_pr_yFor;  
//   TH1D *h_vn_pT_00to10_pr_yExt;
//   TH1D *h_vn_pT_10to40_pr_yExt;
//   TH1D *h_vn_pT_40to60_pr_yExt;  
//   TH1D *h_vn_pT_00to10_pr_yEnd;
//   TH1D *h_vn_pT_10to40_pr_yEnd;
//   TH1D *h_vn_pT_40to60_pr_yEnd;  
  
//   TH1D *h_vn_pT_00to10_de;
//   TH1D *h_vn_pT_10to40_de;
//   TH1D *h_vn_pT_40to60_de;  
//   TH1D *h_vn_pT_00to10_de_yMid;
//   TH1D *h_vn_pT_10to40_de_yMid;
//   TH1D *h_vn_pT_40to60_de_yMid;  
//   TH1D *h_vn_pT_00to10_de_yFor;
//   TH1D *h_vn_pT_10to40_de_yFor;
//   TH1D *h_vn_pT_40to60_de_yFor;  
//   TH1D *h_vn_pT_00to10_de_yExt;
//   TH1D *h_vn_pT_10to40_de_yExt;
//   TH1D *h_vn_pT_40to60_de_yExt;  
//   TH1D *h_vn_pT_00to10_de_yEnd;
//   TH1D *h_vn_pT_10to40_de_yEnd;
//   TH1D *h_vn_pT_40to60_de_yEnd;  
  
//   TH1D *h_vn_pT_00to10_tr;
//   TH1D *h_vn_pT_10to40_tr;
//   TH1D *h_vn_pT_40to60_tr;  
//   TH1D *h_vn_pT_00to10_tr_yMid;
//   TH1D *h_vn_pT_10to40_tr_yMid;
//   TH1D *h_vn_pT_40to60_tr_yMid;  
//   TH1D *h_vn_pT_00to10_tr_yFor;
//   TH1D *h_vn_pT_10to40_tr_yFor;
//   TH1D *h_vn_pT_40to60_tr_yFor;  
//   TH1D *h_vn_pT_00to10_tr_yExt;
//   TH1D *h_vn_pT_10to40_tr_yExt;
//   TH1D *h_vn_pT_40to60_tr_yExt;  
//   TH1D *h_vn_pT_00to10_tr_yEnd;
//   TH1D *h_vn_pT_10to40_tr_yEnd;
//   TH1D *h_vn_pT_40to60_tr_yEnd;  

//   TH1D *h_vn_pT_00to10_he3;
//   TH1D *h_vn_pT_10to40_he3;
//   TH1D *h_vn_pT_40to60_he3;  
//   TH1D *h_vn_pT_00to10_he3_yMid;
//   TH1D *h_vn_pT_10to40_he3_yMid;
//   TH1D *h_vn_pT_40to60_he3_yMid;  
//   TH1D *h_vn_pT_00to10_he3_yFor;
//   TH1D *h_vn_pT_10to40_he3_yFor;
//   TH1D *h_vn_pT_40to60_he3_yFor;  
//   TH1D *h_vn_pT_00to10_he3_yExt;
//   TH1D *h_vn_pT_10to40_he3_yExt;
//   TH1D *h_vn_pT_40to60_he3_yExt;  
//   TH1D *h_vn_pT_00to10_he3_yEnd;
//   TH1D *h_vn_pT_10to40_he3_yEnd;
//   TH1D *h_vn_pT_40to60_he3_yEnd;  

//   TH1D *h_vn_pT_00to10_he4;
//   TH1D *h_vn_pT_10to40_he4;
//   TH1D *h_vn_pT_40to60_he4;  
//   TH1D *h_vn_pT_00to10_he4_yMid;
//   TH1D *h_vn_pT_10to40_he4_yMid;
//   TH1D *h_vn_pT_40to60_he4_yMid;  
//   TH1D *h_vn_pT_00to10_he4_yFor;
//   TH1D *h_vn_pT_10to40_he4_yFor;
//   TH1D *h_vn_pT_40to60_he4_yFor;  
//   TH1D *h_vn_pT_00to10_he4_yExt;
//   TH1D *h_vn_pT_10to40_he4_yExt;
//   TH1D *h_vn_pT_40to60_he4_yExt;  
//   TH1D *h_vn_pT_00to10_he4_yEnd;
//   TH1D *h_vn_pT_10to40_he4_yEnd;
//   TH1D *h_vn_pT_40to60_he4_yEnd;  

 private:
  TString fileName;
  TFile *file;
  void initialize(TString order_n_str);
  void fixAttributes(TString order_n_str);
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Variation", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Variation_rflx",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Variation_rflx_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Variation_rflx_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Variation_rflx() {
  TriggerDictionaryInitialization_Variation_rflx_Impl();
}
