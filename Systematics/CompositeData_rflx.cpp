// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME CompositeData_rflx
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
#include "CompositeData.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *CompositeData_Dictionary();
   static void CompositeData_TClassManip(TClass*);
   static void delete_CompositeData(void *p);
   static void deleteArray_CompositeData(void *p);
   static void destruct_CompositeData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CompositeData*)
   {
      ::CompositeData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::CompositeData));
      static ::ROOT::TGenericClassInfo 
         instance("CompositeData", "", 10,
                  typeid(::CompositeData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &CompositeData_Dictionary, isa_proxy, 0,
                  sizeof(::CompositeData) );
      instance.SetDelete(&delete_CompositeData);
      instance.SetDeleteArray(&deleteArray_CompositeData);
      instance.SetDestructor(&destruct_CompositeData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CompositeData*)
   {
      return GenerateInitInstanceLocal((::CompositeData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::CompositeData*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *CompositeData_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::CompositeData*)0x0)->GetClass();
      CompositeData_TClassManip(theClass);
   return theClass;
   }

   static void CompositeData_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_CompositeData(void *p) {
      delete ((::CompositeData*)p);
   }
   static void deleteArray_CompositeData(void *p) {
      delete [] ((::CompositeData*)p);
   }
   static void destruct_CompositeData(void *p) {
      typedef ::CompositeData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CompositeData

namespace {
  void TriggerDictionaryInitialization_CompositeData_rflx_Impl() {
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
#line 1 "CompositeData_rflx dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class CompositeData;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "CompositeData_rflx dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef COMPOSITEDATA_H
#define COMPOSITEDATA_H

#include <vector>
#include "TH1D.h"
#include "Variation.h"

class CompositeData
{
 public:
  CompositeData(TString prefix, Variation* normalData, Variation* var1Data);
  CompositeData(TString prefix, Variation* normalData, Variation* var1Data, Variation* var2Data);
  CompositeData(TString prefix, Variation* normalData, Variation* var1Data, Variation* var2Data, Variation* var3Data);
  CompositeData(TString prefix, Variation* normalData, Variation* var1Data, Variation* var2Data, Variation* var3Data, Variation* var4Data);
  ~CompositeData();

  struct DataPoint
  {
    Double_t normalValue = -999.0;
    Double_t normalError = -999.0;
    Double_t var1Value = -999.0;
    Double_t var1Error = -999.0;
    Double_t var2Value = -999.0;
    Double_t var2Error = -999.0;
    Double_t var3Value = -999.0;
    Double_t var3Error = -999.0;
    Double_t var4Value = -999.0;
    Double_t var4Error = -999.0;
    Double_t maxValue;
    Double_t maxError;
    Double_t minValue;
    Double_t minError;
    Double_t delta;
    Double_t deltaError;
    Double_t deltaByDeltaError;
    Double_t mean;
    Double_t stdDev;
    Double_t variance;
    Double_t stdDevPercentage;

    void getMax()
    {
      // Get max out of normal value and first 2 variations, 
      //which should always be present when using this function.
      maxValue = normalValue;
      maxError = normalError;
      
      if (var1Value > maxValue)
      {
        maxValue = var1Value;
        maxError = var1Error;
      }
      if (var2Value > maxValue)
      {
        maxValue = var2Value;
        maxError = var2Error;
      }
      ////

      // Add check for 3rd variation if present
      if (var3Value != -999.0 && var3Error != -999.0)
      {
        if (var3Value > maxValue)
        {
          maxValue = var3Value;
          maxError = var3Error;
        }

        // Add check for 4th variation if present
        if (var4Value != -999.0 && var4Error != -999.0)
        {
          if (var4Value > maxValue)
          {
            maxValue = var4Value;
            maxError = var4Error;
          }
        }
      }
    }

    void getMin()
    {
      // Get min out of normal value and first 2 variations, 
      //which should always be present when using this function.
      minValue = normalValue;
      minError = normalError;
      
      if (var1Value < minValue)
      {
        minValue = var1Value;
        minError = var1Error;
      }
      if (var2Value < minValue)
      {
        minValue = var2Value;
        minError = var2Error;
      }
      ////

      // Add check for 3rd variation if present
      if (var3Value != -999.0 && var3Error != -999.0)
      {
        if (var3Value < minValue)
        {
          minValue = var3Value;
          minError = var3Error;
        }

        // Add check for 4th variation if present
        if (var4Value != -999.0 && var4Error != -999.0)
        {
          if (var4Value < minValue)
          {
            minValue = var4Value;
            minError = var4Error;
          }
        }
      }
    }
  }; // End struct DataPoint

//   std::vector<DataPoint> v_vn_pp;
//   std::vector<DataPoint> v_vn_pm;
//   std::vector<DataPoint> v_vn_kp;
//   std::vector<DataPoint> v_vn_km;
//   std::vector<DataPoint> v_vn_pr;
//   std::vector<DataPoint> v_vn_de;
//   std::vector<DataPoint> v_vn_tr;
//   std::vector<DataPoint> v_vn_he3;
//   std::vector<DataPoint> v_vn_he4;
  
//   std::vector<DataPoint> v_vn_yCM_00to10_pr;
  std::vector<DataPoint> v_vn_yCM_10to40_pr;
//   std::vector<DataPoint> v_vn_yCM_40to60_pr;
//   std::vector<DataPoint> v_vn_yCM_00to10_kp;
  std::vector<DataPoint> v_vn_yCM_10to40_kp;
//   std::vector<DataPoint> v_vn_yCM_40to60_kp;
//   std::vector<DataPoint> v_vn_yCM_00to10_km;
  std::vector<DataPoint> v_vn_yCM_10to40_km;
//   std::vector<DataPoint> v_vn_yCM_40to60_km;
//   std::vector<DataPoint> v_vn_yCM_00to10_pp;
  std::vector<DataPoint> v_vn_yCM_10to40_pp;
//   std::vector<DataPoint> v_vn_yCM_40to60_pp;
//   std::vector<DataPoint> v_vn_yCM_00to10_pm;
  std::vector<DataPoint> v_vn_yCM_10to40_pm;
//   std::vector<DataPoint> v_vn_yCM_40to60_pm;
  
//   std::vector<DataPoint> v_vn_yCM_00to10_pr_symm;
//   std::vector<DataPoint> v_vn_yCM_10to40_pr_symm;
//   std::vector<DataPoint> v_vn_yCM_40to60_pr_symm;

//   std::vector<DataPoint> v_vn_yCM_00to10_de;
  std::vector<DataPoint> v_vn_yCM_10to40_de;
//   std::vector<DataPoint> v_vn_yCM_40to60_de;
//   std::vector<DataPoint> v_vn_yCM_00to10_tr;
  std::vector<DataPoint> v_vn_yCM_10to40_tr;
//   std::vector<DataPoint> v_vn_yCM_40to60_tr;
//   std::vector<DataPoint> v_vn_yCM_00to10_he3;
//   std::vector<DataPoint> v_vn_yCM_10to40_he3;
//   std::vector<DataPoint> v_vn_yCM_40to60_he3;
//   std::vector<DataPoint> v_vn_yCM_00to10_he4;
//   std::vector<DataPoint> v_vn_yCM_10to40_he4;
//   std::vector<DataPoint> v_vn_yCM_40to60_he4;

//   std::vector<DataPoint> v_vn_pT_00to10_pr;
//   std::vector<DataPoint> v_vn_pT_10to40_pr;
//   std::vector<DataPoint> v_vn_pT_40to60_pr;
//   std::vector<DataPoint> v_vn_pT_00to10_kp;
//   std::vector<DataPoint> v_vn_pT_10to40_kp;
//   std::vector<DataPoint> v_vn_pT_40to60_kp;
//   std::vector<DataPoint> v_vn_pT_00to10_km;
//   std::vector<DataPoint> v_vn_pT_10to40_km;
//   std::vector<DataPoint> v_vn_pT_40to60_km;
//   std::vector<DataPoint> v_vn_pT_00to10_pp;
//   std::vector<DataPoint> v_vn_pT_10to40_pp;
//   std::vector<DataPoint> v_vn_pT_40to60_pp;
//   std::vector<DataPoint> v_vn_pT_00to10_pm;
//   std::vector<DataPoint> v_vn_pT_10to40_pm;
//   std::vector<DataPoint> v_vn_pT_40to60_pm;
  
  
//   std::vector<DataPoint> v_vn_pT_00to10_pr_yMid;
//   std::vector<DataPoint> v_vn_pT_10to40_pr_yMid;
//   std::vector<DataPoint> v_vn_pT_40to60_pr_yMid;
//   std::vector<DataPoint> v_vn_pT_00to10_pr_yFor;
//   std::vector<DataPoint> v_vn_pT_10to40_pr_yFor;
//   std::vector<DataPoint> v_vn_pT_40to60_pr_yFor;
//   std::vector<DataPoint> v_vn_pT_00to10_pr_yExt;
//   std::vector<DataPoint> v_vn_pT_10to40_pr_yExt;
//   std::vector<DataPoint> v_vn_pT_40to60_pr_yExt;
//   std::vector<DataPoint> v_vn_pT_00to10_pr_yEnd;
//   std::vector<DataPoint> v_vn_pT_10to40_pr_yEnd;
//   std::vector<DataPoint> v_vn_pT_40to60_pr_yEnd;

//   std::vector<DataPoint> v_vn_pT_00to10_de;
//   std::vector<DataPoint> v_vn_pT_10to40_de;
//   std::vector<DataPoint> v_vn_pT_40to60_de;
//   std::vector<DataPoint> v_vn_pT_00to10_de_yMid;
//   std::vector<DataPoint> v_vn_pT_10to40_de_yMid;
//   std::vector<DataPoint> v_vn_pT_40to60_de_yMid;
//   std::vector<DataPoint> v_vn_pT_00to10_de_yFor;
//   std::vector<DataPoint> v_vn_pT_10to40_de_yFor;
//   std::vector<DataPoint> v_vn_pT_40to60_de_yFor;
//   std::vector<DataPoint> v_vn_pT_00to10_de_yExt;
//   std::vector<DataPoint> v_vn_pT_10to40_de_yExt;
//   std::vector<DataPoint> v_vn_pT_40to60_de_yExt;
//   std::vector<DataPoint> v_vn_pT_00to10_de_yEnd;
//   std::vector<DataPoint> v_vn_pT_10to40_de_yEnd;
//   std::vector<DataPoint> v_vn_pT_40to60_de_yEnd;

//   std::vector<DataPoint> v_vn_pT_00to10_tr;
//   std::vector<DataPoint> v_vn_pT_10to40_tr;
//   std::vector<DataPoint> v_vn_pT_40to60_tr;
//   std::vector<DataPoint> v_vn_pT_00to10_tr_yMid;
//   std::vector<DataPoint> v_vn_pT_10to40_tr_yMid;
//   std::vector<DataPoint> v_vn_pT_40to60_tr_yMid;
//   std::vector<DataPoint> v_vn_pT_00to10_tr_yFor;
//   std::vector<DataPoint> v_vn_pT_10to40_tr_yFor;
//   std::vector<DataPoint> v_vn_pT_40to60_tr_yFor;
//   std::vector<DataPoint> v_vn_pT_00to10_tr_yExt;
//   std::vector<DataPoint> v_vn_pT_10to40_tr_yExt;
//   std::vector<DataPoint> v_vn_pT_40to60_tr_yExt;
//   std::vector<DataPoint> v_vn_pT_00to10_tr_yEnd;
//   std::vector<DataPoint> v_vn_pT_10to40_tr_yEnd;
//   std::vector<DataPoint> v_vn_pT_40to60_tr_yEnd;

//   std::vector<DataPoint> v_vn_pT_00to10_he3;
//   std::vector<DataPoint> v_vn_pT_10to40_he3;
//   std::vector<DataPoint> v_vn_pT_40to60_he3;
//   std::vector<DataPoint> v_vn_pT_00to10_he3_yMid;
//   std::vector<DataPoint> v_vn_pT_10to40_he3_yMid;
//   std::vector<DataPoint> v_vn_pT_40to60_he3_yMid;
//   std::vector<DataPoint> v_vn_pT_00to10_he3_yFor;
//   std::vector<DataPoint> v_vn_pT_10to40_he3_yFor;
//   std::vector<DataPoint> v_vn_pT_40to60_he3_yFor;
//   std::vector<DataPoint> v_vn_pT_00to10_he3_yExt;
//   std::vector<DataPoint> v_vn_pT_10to40_he3_yExt;
//   std::vector<DataPoint> v_vn_pT_40to60_he3_yExt;
//   std::vector<DataPoint> v_vn_pT_00to10_he3_yEnd;
//   std::vector<DataPoint> v_vn_pT_10to40_he3_yEnd;
//   std::vector<DataPoint> v_vn_pT_40to60_he3_yEnd;

//   std::vector<DataPoint> v_vn_pT_00to10_he4;
//   std::vector<DataPoint> v_vn_pT_10to40_he4;
//   std::vector<DataPoint> v_vn_pT_40to60_he4;
//   std::vector<DataPoint> v_vn_pT_00to10_he4_yMid;
//   std::vector<DataPoint> v_vn_pT_10to40_he4_yMid;
//   std::vector<DataPoint> v_vn_pT_40to60_he4_yMid;
//   std::vector<DataPoint> v_vn_pT_00to10_he4_yFor;
//   std::vector<DataPoint> v_vn_pT_10to40_he4_yFor;
//   std::vector<DataPoint> v_vn_pT_40to60_he4_yFor;
//   std::vector<DataPoint> v_vn_pT_00to10_he4_yExt;
//   std::vector<DataPoint> v_vn_pT_10to40_he4_yExt;
//   std::vector<DataPoint> v_vn_pT_40to60_he4_yExt;
//   std::vector<DataPoint> v_vn_pT_00to10_he4_yEnd;
//   std::vector<DataPoint> v_vn_pT_10to40_he4_yEnd;
//   std::vector<DataPoint> v_vn_pT_40to60_he4_yEnd;

  // Histograms that hold the values for the Barlow check related to this set of variations
//   TH1D* barlow_vn_pp;
//   TH1D* barlow_vn_pm;
//   TH1D* barlow_vn_kp;
//   TH1D* barlow_vn_km;
//   TH1D* barlow_vn_pr;
//   TH1D* barlow_vn_de;
//   TH1D* barlow_vn_tr;
//   TH1D* barlow_vn_he3;
//   TH1D* barlow_vn_he4;
  
//   TH1D* barlow_vn_yCM_00to10_pr;
  TH1D* barlow_vn_yCM_10to40_pr;
//   TH1D* barlow_vn_yCM_40to60_pr;
//   TH1D* barlow_vn_yCM_00to10_kp;
  TH1D* barlow_vn_yCM_10to40_kp;
//   TH1D* barlow_vn_yCM_40to60_kp;
//   TH1D* barlow_vn_yCM_00to10_km;
  TH1D* barlow_vn_yCM_10to40_km;
//   TH1D* barlow_vn_yCM_40to60_km;
//   TH1D* barlow_vn_yCM_00to10_pp;
  TH1D* barlow_vn_yCM_10to40_pp;
//   TH1D* barlow_vn_yCM_40to60_pp;
//   TH1D* barlow_vn_yCM_00to10_pm;
  TH1D* barlow_vn_yCM_10to40_pm;
//   TH1D* barlow_vn_yCM_40to60_pm;

//   TH1D* barlow_vn_yCM_00to10_pr_symm;
//   TH1D* barlow_vn_yCM_10to40_pr_symm;
//   TH1D* barlow_vn_yCM_40to60_pr_symm;

//   TH1D* barlow_vn_yCM_00to10_de;
  TH1D* barlow_vn_yCM_10to40_de;
//   TH1D* barlow_vn_yCM_40to60_de;
//   TH1D* barlow_vn_yCM_00to10_tr;
  TH1D* barlow_vn_yCM_10to40_tr;
//   TH1D* barlow_vn_yCM_40to60_tr;
//   TH1D* barlow_vn_yCM_00to10_he3;
//   TH1D* barlow_vn_yCM_10to40_he3;
//   TH1D* barlow_vn_yCM_40to60_he3;
//   TH1D* barlow_vn_yCM_00to10_he4;
//   TH1D* barlow_vn_yCM_10to40_he4;
//   TH1D* barlow_vn_yCM_40to60_he4;

//   TH1D* barlow_vn_pT_00to10_pr;
//   TH1D* barlow_vn_pT_10to40_pr;
//   TH1D* barlow_vn_pT_40to60_pr;
//   TH1D* barlow_vn_pT_00to10_pr_yMid;
//   TH1D* barlow_vn_pT_10to40_pr_yMid;
//   TH1D* barlow_vn_pT_40to60_pr_yMid;
//   TH1D* barlow_vn_pT_00to10_pr_yFor;
//   TH1D* barlow_vn_pT_10to40_pr_yFor;
//   TH1D* barlow_vn_pT_40to60_pr_yFor;
//   TH1D* barlow_vn_pT_00to10_pr_yExt;
//   TH1D* barlow_vn_pT_10to40_pr_yExt;
//   TH1D* barlow_vn_pT_40to60_pr_yExt;
//   TH1D* barlow_vn_pT_00to10_pr_yEnd;
//   TH1D* barlow_vn_pT_10to40_pr_yEnd;
//   TH1D* barlow_vn_pT_40to60_pr_yEnd;

//   TH1D* barlow_vn_pT_00to10_de;
//   TH1D* barlow_vn_pT_10to40_de;
//   TH1D* barlow_vn_pT_40to60_de;
//   TH1D* barlow_vn_pT_00to10_de_yMid;
//   TH1D* barlow_vn_pT_10to40_de_yMid;
//   TH1D* barlow_vn_pT_40to60_de_yMid;
//   TH1D* barlow_vn_pT_00to10_de_yFor;
//   TH1D* barlow_vn_pT_10to40_de_yFor;
//   TH1D* barlow_vn_pT_40to60_de_yFor;
//   TH1D* barlow_vn_pT_00to10_de_yExt;
//   TH1D* barlow_vn_pT_10to40_de_yExt;
//   TH1D* barlow_vn_pT_40to60_de_yExt;
//   TH1D* barlow_vn_pT_00to10_de_yEnd;
//   TH1D* barlow_vn_pT_10to40_de_yEnd;
//   TH1D* barlow_vn_pT_40to60_de_yEnd;

//   TH1D* barlow_vn_pT_00to10_tr;
//   TH1D* barlow_vn_pT_10to40_tr;
//   TH1D* barlow_vn_pT_40to60_tr;
//   TH1D* barlow_vn_pT_00to10_tr_yMid;
//   TH1D* barlow_vn_pT_10to40_tr_yMid;
//   TH1D* barlow_vn_pT_40to60_tr_yMid;
//   TH1D* barlow_vn_pT_00to10_tr_yFor;
//   TH1D* barlow_vn_pT_10to40_tr_yFor;
//   TH1D* barlow_vn_pT_40to60_tr_yFor;
//   TH1D* barlow_vn_pT_00to10_tr_yExt;
//   TH1D* barlow_vn_pT_10to40_tr_yExt;
//   TH1D* barlow_vn_pT_40to60_tr_yExt;
//   TH1D* barlow_vn_pT_00to10_tr_yEnd;
//   TH1D* barlow_vn_pT_10to40_tr_yEnd;
//   TH1D* barlow_vn_pT_40to60_tr_yEnd;


//   TH1D* barlow_vn_pT_00to10_he3;
//   TH1D* barlow_vn_pT_10to40_he3;
//   TH1D* barlow_vn_pT_40to60_he3;
//   TH1D* barlow_vn_pT_00to10_he3_yMid;
//   TH1D* barlow_vn_pT_10to40_he3_yMid;
//   TH1D* barlow_vn_pT_40to60_he3_yMid;
//   TH1D* barlow_vn_pT_00to10_he3_yFor;
//   TH1D* barlow_vn_pT_10to40_he3_yFor;
//   TH1D* barlow_vn_pT_40to60_he3_yFor;
//   TH1D* barlow_vn_pT_00to10_he3_yExt;
//   TH1D* barlow_vn_pT_10to40_he3_yExt;
//   TH1D* barlow_vn_pT_40to60_he3_yExt;
//   TH1D* barlow_vn_pT_00to10_he3_yEnd;
//   TH1D* barlow_vn_pT_10to40_he3_yEnd;
//   TH1D* barlow_vn_pT_40to60_he3_yEnd;

//   TH1D* barlow_vn_pT_00to10_he4;
//   TH1D* barlow_vn_pT_10to40_he4;
//   TH1D* barlow_vn_pT_40to60_he4;
//   TH1D* barlow_vn_pT_00to10_he4_yMid;
//   TH1D* barlow_vn_pT_10to40_he4_yMid;
//   TH1D* barlow_vn_pT_40to60_he4_yMid;
//   TH1D* barlow_vn_pT_00to10_he4_yFor;
//   TH1D* barlow_vn_pT_10to40_he4_yFor;
//   TH1D* barlow_vn_pT_40to60_he4_yFor;
//   TH1D* barlow_vn_pT_00to10_he4_yExt;
//   TH1D* barlow_vn_pT_10to40_he4_yExt;
//   TH1D* barlow_vn_pT_40to60_he4_yExt;
//   TH1D* barlow_vn_pT_00to10_he4_yEnd;
//   TH1D* barlow_vn_pT_10to40_he4_yEnd;
//   TH1D* barlow_vn_pT_40to60_he4_yEnd;

  TString ID;
  bool onlyOneVariation;
  int nVariations;
  

 private:
  void initialize();
  void mergePoints(TH1D* normalHisto, TH1D* var1Histo, std::vector<DataPoint>& vectorOfPoints);
  void mergePoints(TH1D* normalHisto, TH1D* var1Histo, TH1D* var2Histo, std::vector<DataPoint>& vectorOfPoints);
  void mergePoints(TH1D* normalHisto, TH1D* var1Histo, TH1D* var2Histo, TH1D* var3Histo, std::vector<DataPoint>& vectorOfPoints);
  void mergePoints(TH1D* normalHisto, TH1D* var1Histo, TH1D* var2Histo, TH1D* var3Histo, TH1D* var4Histo, std::vector<DataPoint>& vectorOfPoints);
  void addRawValuesToFile(TFile* file, TString histogramName, std::vector<DataPoint> vectorOfPoints);
  void addBarlowValuesToFile(TFile* file, TH1D* barlowHistogram, std::vector<DataPoint> vectorOfPoints);
  void saveDetails(Variation* normalData);
  void combine(Variation* normalData, Variation* var1Data);
  void combine(Variation* normalData, Variation* var1Data, Variation* var2Data);
  void combine(Variation* normalData, Variation* var1Data, Variation* var2Data, Variation* var3Data);
  void combine(Variation* normalData, Variation* var1Data, Variation* var2Data, Variation* var3Data, Variation* var4Data);
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"CompositeData", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("CompositeData_rflx",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_CompositeData_rflx_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_CompositeData_rflx_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_CompositeData_rflx() {
  TriggerDictionaryInitialization_CompositeData_rflx_Impl();
}
