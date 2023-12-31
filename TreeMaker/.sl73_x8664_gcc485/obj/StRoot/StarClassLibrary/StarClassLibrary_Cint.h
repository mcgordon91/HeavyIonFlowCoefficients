/********************************************************************
* .sl73_x8664_gcc485/obj/StRoot/StarClassLibrary/StarClassLibrary_Cint.h
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************************/
#ifdef __CINT__
#error .sl73_x8664_gcc485/obj/StRoot/StarClassLibrary/StarClassLibrary_Cint.h/C is only for compilation. Abort cint.
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
extern void G__cpp_setup_tagtableStarClassLibrary_Cint();
extern void G__cpp_setup_inheritanceStarClassLibrary_Cint();
extern void G__cpp_setup_typetableStarClassLibrary_Cint();
extern void G__cpp_setup_memvarStarClassLibrary_Cint();
extern void G__cpp_setup_globalStarClassLibrary_Cint();
extern void G__cpp_setup_memfuncStarClassLibrary_Cint();
extern void G__cpp_setup_funcStarClassLibrary_Cint();
extern void G__set_cpp_environmentStarClassLibrary_Cint();
}


#include "TObject.h"
#include "TMemberInspector.h"
#include "StThreeVector.hh"
#include "StThreeVectorF.hh"
#include "StThreeVectorD.hh"
#include "StLorentzVector.hh"
#include "StLorentzVectorF.hh"
#include "StLorentzVectorD.hh"
#include "StMatrix.hh"
#include "StMatrixF.hh"
#include "StMatrixD.hh"
#include "StHelix.hh"
#include "StHelixD.hh"
#include "StPhysicalHelix.hh"
#include "StPhysicalHelixD.hh"
#include "BetheBloch.h"
#include "StHelixHelper.h"
#include "StParticleDefinition.hh"
#include "StParticleTable.hh"
#include <algorithm>
namespace std { }
using namespace std;

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__StarClassLibrary_CintLN_TClass;
extern G__linked_taginfo G__StarClassLibrary_CintLN_TBuffer;
extern G__linked_taginfo G__StarClassLibrary_CintLN_TMemberInspector;
extern G__linked_taginfo G__StarClassLibrary_CintLN_TObject;
extern G__linked_taginfo G__StarClassLibrary_CintLN_TRootIOCtor;
extern G__linked_taginfo G__StarClassLibrary_CintLN_basic_istreamlEcharcOchar_traitslEchargRsPgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_basic_ostreamlEcharcOchar_traitslEchargRsPgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_string;
extern G__linked_taginfo G__StarClassLibrary_CintLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StThreeVectorlEdoublegR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StThreeVectorlEfloatgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StLorentzVectorlEfloatgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StLorentzVectorlEdoublegR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StMatrixlEdoublegR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StMatrixlEfloatgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StMatrixlEfloatgRcLcLStMatrixRow;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StMatrixlEfloatgRcLcLStMatrixRowConst;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StMatrixlEdoublegRcLcLStMatrixRow;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StMatrixlEdoublegRcLcLStMatrixRowConst;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StHelix;
extern G__linked_taginfo G__StarClassLibrary_CintLN_pairlEdoublecOdoublegR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StPhysicalHelix;
extern G__linked_taginfo G__StarClassLibrary_CintLN_maplEintcOintcOlesslEintgRcOallocatorlEpairlEconstsPintcOintgRsPgRsPgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_maplEdoublecOdoublecOlesslEdoublegRcOallocatorlEpairlEconstsPdoublecOdoublegRsPgRsPgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_BetheBloch;
extern G__linked_taginfo G__StarClassLibrary_CintLN_THelixTrack;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StHelixHelper;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StHelixHelpercLcLdA;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StParticleTable;
extern G__linked_taginfo G__StarClassLibrary_CintLN_StParticleDefinition;
extern G__linked_taginfo G__StarClassLibrary_CintLN_vectorlEStParticleDefinitionmUcOallocatorlEStParticleDefinitionmUgRsPgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_reverse_iteratorlEvectorlEStParticleDefinitionmUcOallocatorlEStParticleDefinitionmUgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_maplEintcOStParticleDefinitionmUcOlesslEintgRcOallocatorlEpairlEconstsPintcOStParticleDefinitionmUgRsPgRsPgR;
extern G__linked_taginfo G__StarClassLibrary_CintLN_maplEstringcOStParticleDefinitionmUcOlesslEstringgRcOallocatorlEpairlEconstsPstringcOStParticleDefinitionmUgRsPgRsPgR;

/* STUB derived class for protected member access */
typedef StThreeVector<double> G__StThreeVectorlEdoublegR;
typedef StThreeVector<float> G__StThreeVectorlEfloatgR;
typedef StLorentzVector<float> G__StLorentzVectorlEfloatgR;
typedef StLorentzVector<double> G__StLorentzVectorlEdoublegR;
typedef StMatrix<double> G__StMatrixlEdoublegR;
typedef StMatrix<float> G__StMatrixlEfloatgR;
