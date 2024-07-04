/*!
* \file   umatchaboche.cxx
* \brief  This file implements the umat interface for the chaboche behaviour law
* \author 
* \date   
*/

#include<iostream>
#include<stdexcept>
#include"MFront/Castem/CastemOutOfBoundsPolicy.hxx"
#include"MFront/Castem/CastemInterface.hxx"

#include"MFront/Castem/CastemStressFreeExpansionHandler.hxx"

#include"TFEL/Material/chaboche.hxx"
#include"MFront/Castem/umatchaboche.hxx"

static tfel::material::OutOfBoundsPolicy&
umatchaboche_getOutOfBoundsPolicy(){
using namespace castem;
using namespace tfel::material;
static OutOfBoundsPolicy policy = CastemOutOfBoundsPolicy::getCastemOutOfBoundsPolicy().getOutOfBoundsPolicy();
return policy;
}

extern "C"{

MFRONT_SHAREDOBJ const char* 
umatchaboche_build_id = "";

MFRONT_SHAREDOBJ const char* 
umatchaboche_mfront_ept = "umatchaboche";

MFRONT_SHAREDOBJ const char* 
umatchaboche_tfel_version = "3.4.1";

MFRONT_SHAREDOBJ unsigned short umatchaboche_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
umatchaboche_mfront_interface = "Castem21";

MFRONT_SHAREDOBJ const char *
umatchaboche_src = "chaboche.mfront";

MFRONT_SHAREDOBJ unsigned short umatchaboche_nModellingHypotheses = 5u;

MFRONT_SHAREDOBJ const char * 
umatchaboche_ModellingHypotheses[5u] = {"AxisymmetricalGeneralisedPlaneStrain",
"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short umatchaboche_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * umatchaboche_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short umatchaboche_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short umatchaboche_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short umatchaboche_UsesGenericPlaneStressAlgorithm = 1u;

MFRONT_SHAREDOBJ unsigned short umatchaboche_nElasticMaterialPropertiesEntryPoints = 2u;
MFRONT_SHAREDOBJ const char * umatchaboche_ElasticMaterialPropertiesEntryPoints[2] = {"chaboche_YoungModulus",
"chaboche_PoissonRatio"};
MFRONT_SHAREDOBJ unsigned short umatchaboche_nLinearThermalExpansionCoefficientsEntryPoints = 0u;
MFRONT_SHAREDOBJ const char * const * umatchaboche_LinearThermalExpansionCoefficientsEntryPoints = nullptr;

MFRONT_SHAREDOBJ unsigned short umatchaboche_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short umatchaboche_nMaterialProperties = 5u;

MFRONT_SHAREDOBJ const char *umatchaboche_MaterialProperties[5u] = {"xyoung",
"xnu",
"xR0",
"xQ",
"xb"};

MFRONT_SHAREDOBJ unsigned short umatchaboche_nInternalStateVariables = 2;
MFRONT_SHAREDOBJ const char * umatchaboche_InternalStateVariables[2] = {"ElasticStrain",
"EquivalentPlasticStrain"};
MFRONT_SHAREDOBJ int umatchaboche_InternalStateVariablesTypes [] = {1,0};

MFRONT_SHAREDOBJ unsigned short umatchaboche_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * umatchaboche_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short umatchaboche_nParameters = 7;
MFRONT_SHAREDOBJ const char * umatchaboche_Parameters[7] = {"epsilon",
"theta","RelativeValueForTheEquivalentStressLowerBoundDefinition","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon",
"iterMax"};
MFRONT_SHAREDOBJ int umatchaboche_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double umatchaboche_epsilon_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double umatchaboche_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double umatchaboche_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double umatchaboche_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double umatchaboche_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double umatchaboche_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-13;

MFRONT_SHAREDOBJ unsigned short umatchaboche_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short umatchaboche_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short umatchaboche_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short umatchaboche_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short umatchaboche_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short umatchaboche_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short umatchaboche_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short umatchaboche_Interface = 1u;

MFRONT_SHAREDOBJ unsigned short umatchaboche_nMainVariables = 1u;

MFRONT_SHAREDOBJ unsigned short umatchaboche_nGradients = 1u;
MFRONT_SHAREDOBJ int umatchaboche_GradientsTypes[1u] = {1};
MFRONT_SHAREDOBJ const char* umatchaboche_Gradients[1u] = {"Strain"};

MFRONT_SHAREDOBJ unsigned short umatchaboche_nThermodynamicForces = 1u;
MFRONT_SHAREDOBJ int umatchaboche_ThermodynamicForcesTypes[1u] = {1};
MFRONT_SHAREDOBJ const char* umatchaboche_ThermodynamicForces[1u] = {"Stress"};

MFRONT_SHAREDOBJ int
umatchaboche_setParameter(const char *const key,const double value){
using tfel::material::chabocheParametersInitializer;
auto& i = chabocheParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
umatchaboche_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::chabocheParametersInitializer;
auto& i = chabocheParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ void
umatchaboche_setOutOfBoundsPolicy(const int p){
if(p==0){
umatchaboche_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
umatchaboche_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
umatchaboche_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "umatchaboche_setOutOfBoundsPolicy: invalid argument\n";
}
}

static void 
umatchaboche_base_TRIDIMENSIONAL(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
const castem::CastemReal *const DROT,  castem::CastemReal *const DDSDDE,
const castem::CastemReal *const STRAN, const castem::CastemReal *const DSTRAN,
const castem::CastemReal *const TEMP,  const castem::CastemReal *const DTEMP,
const castem::CastemReal *const PROPS, const castem::CastemInt    *const NPROPS,
const castem::CastemReal *const PREDEF,const castem::CastemReal *const DPRED,
castem::CastemReal *const STATEV,const castem::CastemInt    *const NSTATV,
castem::CastemReal *const STRESS,castem::CastemReal *const PNEWDT,
castem::CastemInt  *const KINC,
const castem::StressFreeExpansionHandler& sfeh)
{
const auto op = umatchaboche_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::TRIDIMENSIONAL,tfel::material::chaboche>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatchaboche_base_AXISYMMETRICAL(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
const castem::CastemReal *const DROT,  castem::CastemReal *const DDSDDE,
const castem::CastemReal *const STRAN, const castem::CastemReal *const DSTRAN,
const castem::CastemReal *const TEMP,  const castem::CastemReal *const DTEMP,
const castem::CastemReal *const PROPS, const castem::CastemInt    *const NPROPS,
const castem::CastemReal *const PREDEF,const castem::CastemReal *const DPRED,
castem::CastemReal *const STATEV,const castem::CastemInt    *const NSTATV,
castem::CastemReal *const STRESS,castem::CastemReal *const PNEWDT,
castem::CastemInt  *const KINC,
const castem::StressFreeExpansionHandler& sfeh)
{
const auto op = umatchaboche_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::AXISYMMETRICAL,tfel::material::chaboche>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatchaboche_base_PLANESTRAIN(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
const castem::CastemReal *const DROT,  castem::CastemReal *const DDSDDE,
const castem::CastemReal *const STRAN, const castem::CastemReal *const DSTRAN,
const castem::CastemReal *const TEMP,  const castem::CastemReal *const DTEMP,
const castem::CastemReal *const PROPS, const castem::CastemInt    *const NPROPS,
const castem::CastemReal *const PREDEF,const castem::CastemReal *const DPRED,
castem::CastemReal *const STATEV,const castem::CastemInt    *const NSTATV,
castem::CastemReal *const STRESS,castem::CastemReal *const PNEWDT,
castem::CastemInt  *const KINC,
const castem::StressFreeExpansionHandler& sfeh)
{
const auto op = umatchaboche_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::PLANESTRAIN,tfel::material::chaboche>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatchaboche_base_PLANESTRESS(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
const castem::CastemReal *const DROT,  castem::CastemReal *const DDSDDE,
const castem::CastemReal *const STRAN, const castem::CastemReal *const DSTRAN,
const castem::CastemReal *const TEMP,  const castem::CastemReal *const DTEMP,
const castem::CastemReal *const PROPS, const castem::CastemInt    *const NPROPS,
const castem::CastemReal *const PREDEF,const castem::CastemReal *const DPRED,
castem::CastemReal *const STATEV,const castem::CastemInt    *const NSTATV,
castem::CastemReal *const STRESS,castem::CastemReal *const PNEWDT,
castem::CastemInt  *const KINC,
const castem::StressFreeExpansionHandler& sfeh)
{
const auto op = umatchaboche_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::PLANESTRESS,tfel::material::chaboche>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatchaboche_base_GENERALISEDPLANESTRAIN(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
const castem::CastemReal *const DROT,  castem::CastemReal *const DDSDDE,
const castem::CastemReal *const STRAN, const castem::CastemReal *const DSTRAN,
const castem::CastemReal *const TEMP,  const castem::CastemReal *const DTEMP,
const castem::CastemReal *const PROPS, const castem::CastemInt    *const NPROPS,
const castem::CastemReal *const PREDEF,const castem::CastemReal *const DPRED,
castem::CastemReal *const STATEV,const castem::CastemInt    *const NSTATV,
castem::CastemReal *const STRESS,castem::CastemReal *const PNEWDT,
castem::CastemInt  *const KINC,
const castem::StressFreeExpansionHandler& sfeh)
{
const auto op = umatchaboche_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::GENERALISEDPLANESTRAIN,tfel::material::chaboche>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatchaboche_base_AXISYMMETRICALGENERALISEDPLANESTRAIN(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
const castem::CastemReal *const DROT,  castem::CastemReal *const DDSDDE,
const castem::CastemReal *const STRAN, const castem::CastemReal *const DSTRAN,
const castem::CastemReal *const TEMP,  const castem::CastemReal *const DTEMP,
const castem::CastemReal *const PROPS, const castem::CastemInt    *const NPROPS,
const castem::CastemReal *const PREDEF,const castem::CastemReal *const DPRED,
castem::CastemReal *const STATEV,const castem::CastemInt    *const NSTATV,
castem::CastemReal *const STRESS,castem::CastemReal *const PNEWDT,
castem::CastemInt  *const KINC,
const castem::StressFreeExpansionHandler& sfeh)
{
const auto op = umatchaboche_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN,tfel::material::chaboche>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatchaboche_base(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
const castem::CastemReal *const DROT,  castem::CastemReal *const DDSDDE,
const castem::CastemReal *const STRAN, const castem::CastemReal *const DSTRAN,
const castem::CastemReal *const TEMP,  const castem::CastemReal *const DTEMP,
const castem::CastemReal *const PROPS, const castem::CastemInt    *const NPROPS,
const castem::CastemReal *const PREDEF,const castem::CastemReal *const DPRED,
castem::CastemReal *const STATEV,const castem::CastemInt    *const NSTATV,
castem::CastemReal *const STRESS,castem::CastemReal *const PNEWDT,
const castem::CastemInt *const NDI,
castem::CastemInt  *const KINC,
const castem::StressFreeExpansionHandler& sfeh)
{
if(*NDI==2){
	umatchaboche_base_TRIDIMENSIONAL(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==0){
	umatchaboche_base_AXISYMMETRICAL(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==-1){
	umatchaboche_base_PLANESTRAIN(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==-2){
	umatchaboche_base_PLANESTRESS(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==-3){
	umatchaboche_base_GENERALISEDPLANESTRAIN(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==14){
	umatchaboche_base_AXISYMMETRICALGENERALISEDPLANESTRAIN(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else {
castem::CastemInterfaceExceptions::displayInvalidModellingHypothesisErrorMessage();
*KINC = -7;
}
}

MFRONT_SHAREDOBJ void
umatchaboche(castem::CastemReal *const STRESS,
 castem::CastemReal *const STATEV,
 castem::CastemReal *const DDSDDE,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 const castem::CastemReal *const STRAN,
 const castem::CastemReal *const DSTRAN,
 const castem::CastemReal *const,
 const castem::CastemReal *const DTIME,
 const castem::CastemReal *const TEMP,
 const castem::CastemReal *const DTEMP,
 const castem::CastemReal *const PREDEF,
 const castem::CastemReal *const DPRED,
 const char           *const,
 const castem::CastemInt  *const NDI,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const NTENS,
 const castem::CastemInt  *const NSTATV,
 const castem::CastemReal *const PROPS,
 const castem::CastemInt  *const NPROPS,
 const castem::CastemReal *const,
 const castem::CastemReal *const DROT,
       castem::CastemReal *const PNEWDT,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
       castem::CastemInt  *const KINC,
const int)
{
umatchaboche_base(NTENS, DTIME,DROT,DDSDDE,STRAN,DSTRAN,TEMP,DTEMP,
PROPS,NPROPS,PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,NDI,KINC,
castem::CastemStandardSmallStrainStressFreeExpansionHandler);
}

} // end of extern "C"
