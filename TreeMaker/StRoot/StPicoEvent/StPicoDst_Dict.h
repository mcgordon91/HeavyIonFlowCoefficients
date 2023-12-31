/********************************************************************
* StPicoDst_Dict.h
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************************/
#ifdef __CINT__
#error StPicoDst_Dict.h/C is only for compilation. Abort cint.
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define G__ANSIHEADER
#define G__DICTIONARY
#define G__PRIVATE_GVALUE
#include "G__ci.h"
#include "FastAllocString.h"
extern "C" {
extern void G__cpp_setup_tagtableStPicoDst_Dict();
extern void G__cpp_setup_inheritanceStPicoDst_Dict();
extern void G__cpp_setup_typetableStPicoDst_Dict();
extern void G__cpp_setup_memvarStPicoDst_Dict();
extern void G__cpp_setup_globalStPicoDst_Dict();
extern void G__cpp_setup_memfuncStPicoDst_Dict();
extern void G__cpp_setup_funcStPicoDst_Dict();
extern void G__set_cpp_environmentStPicoDst_Dict();
}


#include "TObject.h"
#include "TMemberInspector.h"
#include "PhysicalConstants.h"
#include "StPicoArrays.h"
#include "StPicoBEmcPidTraits.h"
#include "StPicoBEmcSmdEHit.h"
#include "StPicoBEmcSmdPHit.h"
#include "StPicoBTofHit.h"
#include "StPicoBTofPidTraits.h"
#include "StPicoBTowHit.h"
#include "StPicoBbcHit.h"
#include "StPicoCommon.h"
#include "StPicoDst.h"
#include "StPicoDstReader.h"
#include "StPicoETofHit.h"
#include "StPicoETofPidTraits.h"
#include "StPicoEmcTrigger.h"
#include "StPicoEpdHit.h"
#include "StPicoEvent.h"
#include "StPicoFmsHit.h"
#include "StPicoHelix.h"
#include "StPicoMcTrack.h"
#include "StPicoMcVertex.h"
#include "StPicoMessMgr.h"
#include "StPicoMtdHit.h"
#include "StPicoMtdPidTraits.h"
#include "StPicoMtdTrigger.h"
#include "StPicoPhysicalHelix.h"
#include "StPicoTrack.h"
#include "StPicoTrackCovMatrix.h"
#include "SystemOfUnits.h"
#include <algorithm>
namespace std { }
using namespace std;

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__StPicoDst_DictLN_TClass;
extern G__linked_taginfo G__StPicoDst_DictLN_TBuffer;
extern G__linked_taginfo G__StPicoDst_DictLN_TMemberInspector;
extern G__linked_taginfo G__StPicoDst_DictLN_TObject;
extern G__linked_taginfo G__StPicoDst_DictLN_TString;
extern G__linked_taginfo G__StPicoDst_DictLN_vectorlEunsignedsPshortcOallocatorlEunsignedsPshortgRsPgR;
extern G__linked_taginfo G__StPicoDst_DictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR;
extern G__linked_taginfo G__StPicoDst_DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR;
extern G__linked_taginfo G__StPicoDst_DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TClonesArray;
extern G__linked_taginfo G__StPicoDst_DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR;
extern G__linked_taginfo G__StPicoDst_DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoBEmcPidTraits;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoBEmcSmdEHit;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoBEmcSmdPHit;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoBTofHit;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTBaselEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTBaselEdoublegR;
extern G__linked_taginfo G__StPicoDst_DictLN_TVectorTlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TVectorTlEdoublegR;
extern G__linked_taginfo G__StPicoDst_DictLN_TElementActionTlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TElementPosActionTlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTRow_constlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTRowlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTDiag_constlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTColumn_constlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTFlat_constlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTSub_constlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTSparseRow_constlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTSparseDiag_constlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTColumnlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTDiaglEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTFlatlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTSublEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTSparseRowlEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TMatrixTSparseDiaglEfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TVector3;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoBTofPidTraits;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoBTowHit;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoBbcHit;
extern G__linked_taginfo G__StPicoDst_DictLN_setlEStarPicoDstcLcLDetectorSidecOlesslEStarPicoDstcLcLDetectorSidegRcOallocatorlEStarPicoDstcLcLDetectorSidegRsPgR;
extern G__linked_taginfo G__StPicoDst_DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoEvent;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoTrack;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoEmcTrigger;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoMtdTrigger;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoMtdHit;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoEpdHit;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoFmsHit;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoMtdPidTraits;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoTrackCovMatrix;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoETofHit;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoETofPidTraits;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoMcVertex;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoMcTrack;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoDst;
extern G__linked_taginfo G__StPicoDst_DictLN_TTree;
extern G__linked_taginfo G__StPicoDst_DictLN_pairlEdoublecOdoublegR;
extern G__linked_taginfo G__StPicoDst_DictLN_maplEstringcOTObjArraymUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOTObjArraymUgRsPgRsPgR;
extern G__linked_taginfo G__StPicoDst_DictLN_TChain;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoDstReader;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoHelix;
extern G__linked_taginfo G__StPicoDst_DictLN_TLorentzVector;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoPhysicalHelix;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoMcTrackcLcLEHIT;
extern G__linked_taginfo G__StPicoDst_DictLN_pairlEfloatcOfloatgR;
extern G__linked_taginfo G__StPicoDst_DictLN_StPicoTrackcLcLdA;

/* STUB derived class for protected member access */
