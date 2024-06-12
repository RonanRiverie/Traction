/*!
* \file   umatekmc.cxx
* \brief  This file implements the umat interface for the ekmc behaviour law
* \author 
* \date   
*/

#include<iostream>
#include<stdexcept>
#include"MFront/Castem/CastemOutOfBoundsPolicy.hxx"
#include"MFront/Castem/CastemInterface.hxx"

#include"MFront/Castem/CastemStressFreeExpansionHandler.hxx"

#include"TFEL/Material/ekmc.hxx"
#include"MFront/Castem/umatekmc.hxx"

static tfel::material::OutOfBoundsPolicy&
umatekmc_getOutOfBoundsPolicy(){
using namespace castem;
using namespace tfel::material;
static OutOfBoundsPolicy policy = CastemOutOfBoundsPolicy::getCastemOutOfBoundsPolicy().getOutOfBoundsPolicy();
return policy;
}

extern "C"{

MFRONT_SHAREDOBJ const char* 
umatekmc_build_id = "";

MFRONT_SHAREDOBJ const char* 
umatekmc_mfront_ept = "umatekmc";

MFRONT_SHAREDOBJ const char* 
umatekmc_tfel_version = "3.4.1";

MFRONT_SHAREDOBJ unsigned short umatekmc_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
umatekmc_mfront_interface = "Castem21";

MFRONT_SHAREDOBJ const char *
umatekmc_src = "ekmc.mfront";

MFRONT_SHAREDOBJ unsigned short umatekmc_nModellingHypotheses = 5u;

MFRONT_SHAREDOBJ const char * 
umatekmc_ModellingHypotheses[5u] = {"AxisymmetricalGeneralisedPlaneStrain",
"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short umatekmc_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * umatekmc_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short umatekmc_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short umatekmc_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short umatekmc_UsesGenericPlaneStressAlgorithm = 1u;

MFRONT_SHAREDOBJ unsigned short umatekmc_nElasticMaterialPropertiesEntryPoints = 0u;
MFRONT_SHAREDOBJ const char * const * umatekmc_ElasticMaterialPropertiesEntryPoints = nullptr;

MFRONT_SHAREDOBJ unsigned short umatekmc_nLinearThermalExpansionCoefficientsEntryPoints = 0u;
MFRONT_SHAREDOBJ const char * const * umatekmc_LinearThermalExpansionCoefficientsEntryPoints = nullptr;

MFRONT_SHAREDOBJ unsigned short umatekmc_UsableInPurelyImplicitResolution = 0;

MFRONT_SHAREDOBJ unsigned short umatekmc_nMaterialProperties = 12u;

MFRONT_SHAREDOBJ const char *umatekmc_MaterialProperties[12u] = {"de0",
"Ea",
"Va",
"P1",
"P2",
"omega",
"R0",
"Q",
"b",
"H",
"nta",
"palpha"};

MFRONT_SHAREDOBJ unsigned short umatekmc_nInternalStateVariables = 3;
MFRONT_SHAREDOBJ const char * umatekmc_InternalStateVariables[3] = {"ElasticStrain",
"EquivalentViscoplasticStrain","StrainAgingTime"};
MFRONT_SHAREDOBJ int umatekmc_InternalStateVariablesTypes [] = {1,0,0};

MFRONT_SHAREDOBJ unsigned short umatekmc_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * umatekmc_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short umatekmc_nParameters = 7;
MFRONT_SHAREDOBJ const char * umatekmc_Parameters[7] = {"numerical_jacobian_epsilon",
"epsilon","theta","RelativeValueForTheEquivalentStressLowerBoundDefinition","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor",
"iterMax"};
MFRONT_SHAREDOBJ int umatekmc_ParametersTypes [] = {0,0,0,0,0,0,2};

MFRONT_SHAREDOBJ double umatekmc_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-08;

MFRONT_SHAREDOBJ double umatekmc_epsilon_ParameterDefaultValue = 1e-14;

MFRONT_SHAREDOBJ double umatekmc_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double umatekmc_RelativeValueForTheEquivalentStressLowerBoundDefinition_ParameterDefaultValue = 1e-12;

MFRONT_SHAREDOBJ double umatekmc_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double umatekmc_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ unsigned short umatekmc_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short umatekmc_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short umatekmc_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short umatekmc_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short umatekmc_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ unsigned short umatekmc_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short umatekmc_BehaviourKinematic = 1u;

MFRONT_SHAREDOBJ unsigned short umatekmc_Interface = 1u;

MFRONT_SHAREDOBJ unsigned short umatekmc_nMainVariables = 1u;

MFRONT_SHAREDOBJ unsigned short umatekmc_nGradients = 1u;
MFRONT_SHAREDOBJ int umatekmc_GradientsTypes[1u] = {1};
MFRONT_SHAREDOBJ const char* umatekmc_Gradients[1u] = {"Strain"};

MFRONT_SHAREDOBJ unsigned short umatekmc_nThermodynamicForces = 1u;
MFRONT_SHAREDOBJ int umatekmc_ThermodynamicForcesTypes[1u] = {1};
MFRONT_SHAREDOBJ const char* umatekmc_ThermodynamicForces[1u] = {"Stress"};

MFRONT_SHAREDOBJ int
umatekmc_setParameter(const char *const key,const double value){
using tfel::material::ekmcParametersInitializer;
auto& i = ekmcParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
umatekmc_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::ekmcParametersInitializer;
auto& i = ekmcParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ void
umatekmc_setOutOfBoundsPolicy(const int p){
if(p==0){
umatekmc_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
umatekmc_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
umatekmc_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "umatekmc_setOutOfBoundsPolicy: invalid argument\n";
}
}

static void 
umatekmc_base_TRIDIMENSIONAL(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
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
const auto op = umatekmc_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::TRIDIMENSIONAL,tfel::material::ekmc>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatekmc_base_AXISYMMETRICAL(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
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
const auto op = umatekmc_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::AXISYMMETRICAL,tfel::material::ekmc>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatekmc_base_PLANESTRAIN(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
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
const auto op = umatekmc_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::PLANESTRAIN,tfel::material::ekmc>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatekmc_base_PLANESTRESS(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
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
const auto op = umatekmc_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::PLANESTRESS,tfel::material::ekmc>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatekmc_base_GENERALISEDPLANESTRAIN(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
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
const auto op = umatekmc_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::GENERALISEDPLANESTRAIN,tfel::material::ekmc>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatekmc_base_AXISYMMETRICALGENERALISEDPLANESTRAIN(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
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
const auto op = umatekmc_getOutOfBoundsPolicy();
castem::CastemInterface<tfel::material::ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRAIN,tfel::material::ekmc>::exe(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
TEMP,DTEMP,PROPS,NPROPS,
PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,KINC,op,sfeh);
}

static void 
umatekmc_base(const castem::CastemInt *const NTENS, const castem::CastemReal *const DTIME,
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
	umatekmc_base_TRIDIMENSIONAL(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==0){
	umatekmc_base_AXISYMMETRICAL(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==-1){
	umatekmc_base_PLANESTRAIN(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==-2){
	umatekmc_base_PLANESTRESS(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==-3){
	umatekmc_base_GENERALISEDPLANESTRAIN(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else if(*NDI==14){
	umatekmc_base_AXISYMMETRICALGENERALISEDPLANESTRAIN(NTENS,DTIME,DROT,DDSDDE,STRAN,DSTRAN,
 TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,
 STATEV,NSTATV,STRESS,PNEWDT,KINC,sfeh);
 } else {
castem::CastemInterfaceExceptions::displayInvalidModellingHypothesisErrorMessage();
*KINC = -7;
}
}

MFRONT_SHAREDOBJ void
umatekmc(castem::CastemReal *const STRESS,
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
umatekmc_base(NTENS, DTIME,DROT,DDSDDE,STRAN,DSTRAN,TEMP,DTEMP,
PROPS,NPROPS,PREDEF,DPRED,STATEV,NSTATV,
STRESS,PNEWDT,NDI,KINC,
castem::CastemStandardSmallStrainStressFreeExpansionHandler);
}

} // end of extern "C"
