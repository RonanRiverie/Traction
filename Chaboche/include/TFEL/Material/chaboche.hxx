/*!
* \file   TFEL/Material/chaboche.hxx
* \brief  this file implements the chaboche Behaviour.
*         File generated by tfel version 3.4.1
 */

#ifndef LIB_TFELMATERIAL_CHABOCHE_HXX
#define LIB_TFELMATERIAL_CHABOCHE_HXX

#include<string>
#include<iostream>
#include<limits>
#include<stdexcept>
#include<algorithm>

#include"TFEL/Raise.hxx"
#include"TFEL/PhysicalConstants.hxx"
#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Config/TFELTypes.hxx"
#include"TFEL/Metaprogramming/StaticAssert.hxx"
#include"TFEL/TypeTraits/IsFundamentalNumericType.hxx"
#include"TFEL/TypeTraits/IsReal.hxx"
#include"TFEL/Math/General/IEEE754.hxx"
#include"TFEL/Material/MaterialException.hxx"
#include"TFEL/Material/MechanicalBehaviour.hxx"
#include"TFEL/Material/MechanicalBehaviourTraits.hxx"
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Material/BoundsCheck.hxx"
#include"TFEL/Material/IsotropicPlasticity.hxx"
#include"TFEL/Material/Lame.hxx"
#include"TFEL/Material/Hosford1972YieldCriterion.hxx"
#include"TFEL/Material/chabocheBehaviourData.hxx"
#include"TFEL/Material/chabocheIntegrationData.hxx"

#include"TFEL/Math/st2tost2.hxx"
#include"TFEL/Math/tmatrix.hxx"
#include"TFEL/Math/tvector.hxx"
#include"TFEL/Math/Matrix/tmatrixIO.hxx"
#include"TFEL/Math/Vector/tvectorIO.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2ConceptIO.hxx"
#include"TFEL/Math/Vector/TinyVectorFromTinyVectorView.hxx"
#include"TFEL/Math/Vector/TinyVectorFromTinyVectorViewIO.hxx"
#include"TFEL/Math/Stensor/StensorFromTinyVectorView.hxx"
#include "TFEL/Math/Stensor/StensorFromTinyMatrixRowView.hxx"
#include "TFEL/Math/Stensor/StensorFromTinyMatrixRowView2.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2FromTinyMatrixView.hxx"

#include"TFEL/Math/ST2toST2/ST2toST2FromTinyMatrixView2.hxx"

#include"TFEL/Math/Stensor/StensorFromTinyMatrixColumnView.hxx"
#include"TFEL/Math/Stensor/StensorFromTinyMatrixRowView.hxx"
#include"TFEL/Math/Stensor/StensorFromTinyMatrixColumnView2.hxx"
#include"TFEL/Math/Stensor/StensorFromTinyMatrixRowView2.hxx"
#include"TFEL/Math/Vector/TinyVectorOfStensorFromTinyVectorView.hxx"
#include"TFEL/Math/Vector/TinyVectorOfStensorFromTinyVectorViewIO.hxx"
#include "TFEL/Math/RootFinding/BissectionAlgorithmBase.hxx"
#include "TFEL/Math/AccelerationAlgorithms/AitkenAccelerationAlgorithm.hxx"

#include"MFront/Castem/Castem.hxx"

namespace tfel{

namespace material{

struct chabocheParametersInitializer
{
static chabocheParametersInitializer&
get();

double epsilon;
double theta;
double relative_value_for_the_equivalent_stress_lower_bound;
double minimal_time_step_scaling_factor;
double maximal_time_step_scaling_factor;
double numerical_jacobian_epsilon;
unsigned short iterMax;

void set(const char* const,const double);

void set(const char* const,const unsigned short);

/*!
 * \brief convert a string to double
 * \param[in] p : parameter
 * \param[in] v : value
 */
static double getDouble(const std::string&,const std::string&);
/*!
 * \brief convert a string to unsigned short
 * \param[in] p : parameter
 * \param[in] v : value
 */
static unsigned short getUnsignedShort(const std::string&,const std::string&);
private :

chabocheParametersInitializer();

chabocheParametersInitializer(const chabocheParametersInitializer&);

chabocheParametersInitializer&
operator=(const chabocheParametersInitializer&);
/*!
 * \brief read the parameters from the given file
 * \param[out] pi : parameters initializer
 * \param[in]  fn : file name
 */
static void readParameters(chabocheParametersInitializer&,const char* const);
};

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis,typename Type,bool use_qt>
class chaboche;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
 operator <<(std::ostream&,const chaboche<hypothesis,Type,false>&);

/*!
* \class chaboche
* \brief This class implements the chaboche behaviour.
* \param hypothesis, modelling hypothesis.
* \param Type, numerical type.
*/
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class chaboche<hypothesis,Type,false> final
: public MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>,
public chabocheBehaviourData<hypothesis,Type,false>,
public chabocheIntegrationData<hypothesis,Type,false>
{

static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;

TFEL_STATIC_ASSERT(N==1||N==2||N==3);
TFEL_STATIC_ASSERT(tfel::typetraits::IsFundamentalNumericType<Type>::cond);
TFEL_STATIC_ASSERT(tfel::typetraits::IsReal<Type>::cond);

friend std::ostream& operator<< <>(std::ostream&,const chaboche&);

static constexpr unsigned short TVectorSize = N;
typedef tfel::math::StensorDimeToSize<N> StensorDimeToSize;
static constexpr unsigned short StensorSize = StensorDimeToSize::value;
typedef tfel::math::TensorDimeToSize<N> TensorDimeToSize;
static constexpr unsigned short TensorSize = TensorDimeToSize::value;

using ushort =  unsigned short;
using Types = tfel::config::Types<N,Type,false>;
using real                = typename Types::real;
using time                = typename Types::time;
using length              = typename Types::length;
using frequency           = typename Types::frequency;
using speed               = typename Types::speed;
using stress              = typename Types::stress;
using strain              = typename Types::strain;
using strainrate          = typename Types::strainrate;
using stressrate          = typename Types::stressrate;
using temperature         = typename Types::temperature;
using thermalexpansion    = typename Types::thermalexpansion;
using thermalconductivity = typename Types::thermalconductivity;
using massdensity         = typename Types::massdensity;
using energydensity         = typename Types::energydensity;
using TVector             = typename Types::TVector;
using Stensor             = typename Types::Stensor;
using Stensor4            = typename Types::Stensor4;
using FrequencyStensor    = typename Types::FrequencyStensor;
using ForceTVector        = typename Types::ForceTVector;
using StressStensor       = typename Types::StressStensor;
using StressRateStensor   = typename Types::StressRateStensor;
using DisplacementTVector = typename Types::DisplacementTVector;
using StrainStensor       = typename Types::StrainStensor;
using StrainRateStensor   = typename Types::StrainRateStensor;
using StiffnessTensor     = typename Types::StiffnessTensor;
using Tensor              = typename Types::Tensor;
using FrequencyTensor     = typename Types::FrequencyTensor;
using StressTensor        = typename Types::StressTensor;
using ThermalExpansionCoefficientTensor = typename Types::ThermalExpansionCoefficientTensor;
using DeformationGradientTensor         = typename Types::DeformationGradientTensor;
using DeformationGradientRateTensor     = typename Types::DeformationGradientRateTensor;
using TemperatureGradient = typename Types::TemperatureGradient;
using HeatFlux = typename Types::HeatFlux;
using TangentOperator   = StiffnessTensor;
using PhysicalConstants = tfel::PhysicalConstants<real>;

public :

typedef chabocheBehaviourData<hypothesis,Type,false> BehaviourData;
typedef chabocheIntegrationData<hypothesis,Type,false> IntegrationData;
typedef typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SMFlag SMFlag;
typedef typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SMType SMType;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::ELASTIC;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SECANTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::TANGENTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::CONSISTENTTANGENTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::NOSTIFFNESSREQUESTED;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::STANDARDTANGENTOPERATOR;
using IntegrationResult = typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::IntegrationResult;

using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SUCCESS;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::UNRELIABLE_RESULTS;

using StressFreeExpansionType = StrainStensor;

private :



typename tfel::math::StensorFromTinyVectorView<N,1+StensorSize,0,real>::type deel;
real& dp;

stress ihr_R0_;
stress ihr_Rinf_;
real ihr_b_;
bool bpl;
tfel::math::BissectionAlgorithmBase<real> staggered_scheme_bissection_algorithm;
tfel::math::AitkenAccelerationAlgorithm<real> staggered_scheme_aitken_acceleration_algorithm;
stress young;
real nu;
stress lambda;
stress mu;
stress young_tdt;
real nu_tdt;
stress lambda_tdt;
stress mu_tdt;

real epsilon;
real theta;
real relative_value_for_the_equivalent_stress_lower_bound;
real minimal_time_step_scaling_factor;
real maximal_time_step_scaling_factor;
real numerical_jacobian_epsilon;
ushort iterMax;

//! Tangent operator;
TangentOperator Dt;
//! alias to the tangent operator;
TangentOperator& dsig_ddeto;
// updating material properties, in mandatory
void updateMaterialPropertiesDependantOnStateVariables(){
using namespace std;
using namespace tfel::math;
using std::vector;
}

// Jacobian
tfel::math::tmatrix<1+StensorSize,1+StensorSize,real> jacobian;
// zeros
tfel::math::tvector<1+StensorSize,real> zeros;

// previous zeros
tfel::math::tvector<1+StensorSize,real> zeros_1;

// function
tfel::math::tvector<1+StensorSize,real> fzeros;

// number of iterations
unsigned int iter = 0u;

void computeNumericalJacobian(tfel::math::tmatrix<1+StensorSize,1+StensorSize,real>& njacobian)
{
using namespace std;
using namespace tfel::math;
tvector<1+StensorSize,real> tzeros(this->zeros);
tvector<1+StensorSize,real> tfzeros(this->fzeros);
tmatrix<1+StensorSize,1+StensorSize,real> tjacobian(this->jacobian);
for(unsigned short idx = 0; idx!= 1+StensorSize;++idx){
this->zeros(idx) -= this->numerical_jacobian_epsilon;
this->computeThermodynamicForces();
this->computeFdF(true);
this->zeros = tzeros;
tvector<1+StensorSize,real> tfzeros2(this->fzeros);
this->zeros(idx) += this->numerical_jacobian_epsilon;
this->computeThermodynamicForces();
this->computeFdF(true);
this->fzeros = (this->fzeros-tfzeros2)/(2*(this->numerical_jacobian_epsilon));
for(unsigned short idx2 = 0; idx2!= 1+StensorSize;++idx2){
njacobian(idx2,idx) = this->fzeros(idx2);
}
this->zeros    = tzeros;
this->fzeros   = tfzeros;
}
if(&njacobian!=&(this->jacobian)){
this->jacobian = tjacobian;
}
}

void
computePartialJacobianInvert(const tfel::math::TinyPermutation<1+StensorSize>& jacobian_permutation, tfel::math::derivative_type<StrainStensor, StrainStensor>& partial_jacobian_eel)
{
using namespace tfel::math;
for(unsigned short idx=0;idx!=StensorSize;++idx){
tvector<1+StensorSize,real> vect_e(real(0));
vect_e(idx) = real(1);
TinyMatrixSolve<1+StensorSize,real>::back_substitute(this->jacobian,jacobian_permutation,vect_e);
for(unsigned short idx2=0;idx2!=StensorSize;++idx2){
partial_jacobian_eel(idx2,idx)=vect_e(idx2);
}
}
}

void
computePartialJacobianInvert(const tfel::math::TinyPermutation<1+StensorSize>& jacobian_permutation, tfel::math::derivative_type<StrainStensor, StrainStensor>& partial_jacobian_eel,
tfel::math::derivative_type<strain, StrainStensor>& partial_jacobian_p)
{
using namespace tfel::math;
for(unsigned short idx=0;idx!=StensorSize;++idx){
tvector<1+StensorSize,real> vect_e(real(0));
vect_e(idx) = real(1);
TinyMatrixSolve<1+StensorSize,real>::back_substitute(this->jacobian,jacobian_permutation,vect_e);
for(unsigned short idx2=0;idx2!=StensorSize;++idx2){
partial_jacobian_eel(idx2,idx)=vect_e(idx2);
}
partial_jacobian_p(idx)=vect_e(StensorSize);
}
}

void additionalConvergenceChecks(bool& converged,real& error, const SMType smt){
using namespace std;
using namespace tfel::math;
using std::vector;
if (converged) {
// checking status consistency
if (this->bpl) {
if (this->dp < -2*this->epsilon) {
// desactivating this system
converged = this->bpl = false;
}
} else {
const auto& s = this->sig;
const auto seq = sigmaeq(s);
const auto R = this->ihr_Rinf_+(this->ihr_R0_-this->ihr_Rinf_)*exp(-(this->ihr_b_)*(this->p+(this->theta)*(this->dp)));
if(seq > R) {
converged = false;
this->bpl = true;
}
}
} // end of if(converged)

static_cast<void>(converged);
static_cast<void>(error);
static_cast<void>(smt);
} // end of additionalConvergenceChecks

void computeThermodynamicForces(){
using namespace std;
using namespace tfel::math;
using std::vector;
this->sig=this->lambda*trace(this->eel+(this->theta)*(this->deel))*Stensor::Id()+2*(this->mu)*(this->eel+(this->theta)*(this->deel));

} // end of chaboche::computeThermodynamicForces

void computeFinalThermodynamicForces(){
using namespace std;
using namespace tfel::math;
using std::vector;
this->sig=this->lambda_tdt*trace(this->eel)*Stensor::Id()+2*(this->mu_tdt)*this->eel;

} // end of chaboche::computeFinalThermodynamicForces

/*!
* \brief Update internal variables at end of integration
*/
void updateIntegrationVariables(){
}

/*!
* \brief Update internal variables at end of integration
*/
void updateStateVariables(){
this->eel += this->deel;
this->p += this->dp;
}

/*!
* \brief Update auxiliary state variables at end of integration
*/
void updateAuxiliaryStateVariables()
{}

//! \brief return an elastic prediction of the stresses
StressStensor computeElasticPrediction() const{
return this->lambda*trace(this->eel+(this->theta)*(this->deto))*Stensor::Id()+2*(this->mu)*(this->eel+(this->theta)*(this->deto));
}


//! \brief Default constructor (disabled)
chaboche() =delete ;
//! \brief Copy constructor (disabled)
chaboche(const chaboche&) = delete;
//! \brief Assignement operator (disabled)
chaboche& operator = (const chaboche&) = delete;

public:

/*!
* \brief Constructor
*/
chaboche(const chabocheBehaviourData<hypothesis,Type,false>& src1,
const chabocheIntegrationData<hypothesis,Type,false>& src2)
: chabocheBehaviourData<hypothesis,Type,false>(src1),
chabocheIntegrationData<hypothesis,Type,false>(src2),
deel(this->zeros),
dp(this->zeros(StensorSize)),
dsig_ddeto(Dt),
zeros(real(0)),
fzeros(real(0))
{
using namespace std;
using namespace tfel::math;
using std::vector;
this->epsilon = chabocheParametersInitializer::get().epsilon;
this->theta = chabocheParametersInitializer::get().theta;
this->relative_value_for_the_equivalent_stress_lower_bound = chabocheParametersInitializer::get().relative_value_for_the_equivalent_stress_lower_bound;
this->minimal_time_step_scaling_factor = chabocheParametersInitializer::get().minimal_time_step_scaling_factor;
this->maximal_time_step_scaling_factor = chabocheParametersInitializer::get().maximal_time_step_scaling_factor;
this->numerical_jacobian_epsilon = chabocheParametersInitializer::get().numerical_jacobian_epsilon;
this->iterMax = chabocheParametersInitializer::get().iterMax;
this->young=this->xyoung;
this->nu=this->xnu;
this->lambda=computeLambda(young,nu);
this->mu=computeMu(young,nu);
this->young_tdt  = this->young;
this->nu_tdt     = this->nu;
this->lambda_tdt = this->lambda;
this->mu_tdt     = this->mu;
}

/*
 * \brief constructor for the Castem interface
 * \param[in] CASTEMdt_: time increment
 * \param[in] CASTEMT_: temperature
 * \param[in] CASTEMdT_: temperature increment
 * \param[in] CASTEMmat: material properties
 * \param[in] CASTEMint_vars: state variables
 * \param[in] CASTEMext_vars: external state variables
 * \param[in] CASTEMdext_vars: external state variables increments
 */
chaboche(const Type* const CASTEMdt_,
const Type* const CASTEMT_,
const Type* const CASTEMdT_,
const Type* const CASTEMmat,
const Type* const CASTEMint_vars,
const Type* const CASTEMext_vars,
const Type* const CASTEMdext_vars)
: chabocheBehaviourData<hypothesis,Type,false>(CASTEMT_,CASTEMmat,
CASTEMint_vars,CASTEMext_vars),
chabocheIntegrationData<hypothesis,Type,false>(CASTEMdt_,CASTEMdT_,CASTEMdext_vars),
deel(this->zeros),
dp(this->zeros(StensorSize)),
dsig_ddeto(Dt),
zeros(real(0)),
fzeros(real(0))
{
using namespace std;
using namespace tfel::math;
using std::vector;
this->epsilon = chabocheParametersInitializer::get().epsilon;
this->theta = chabocheParametersInitializer::get().theta;
this->relative_value_for_the_equivalent_stress_lower_bound = chabocheParametersInitializer::get().relative_value_for_the_equivalent_stress_lower_bound;
this->minimal_time_step_scaling_factor = chabocheParametersInitializer::get().minimal_time_step_scaling_factor;
this->maximal_time_step_scaling_factor = chabocheParametersInitializer::get().maximal_time_step_scaling_factor;
this->numerical_jacobian_epsilon = chabocheParametersInitializer::get().numerical_jacobian_epsilon;
this->iterMax = chabocheParametersInitializer::get().iterMax;
this->young=this->xyoung;
this->nu=this->xnu;
this->lambda=computeLambda(young,nu);
this->mu=computeMu(young,nu);
this->young_tdt  = this->young;
this->nu_tdt     = this->nu;
this->lambda_tdt = this->lambda;
this->mu_tdt     = this->mu;
}

/*!
 * \ brief initialize the behaviour with user code
 */
void initialize(){
using namespace std;
using namespace tfel::math;
using std::vector;
this->ihr_R0_ = this->xR0;
this->ihr_Rinf_ = (this->xQ)+(this->xR0);
this->ihr_b_ = this->xb;

const auto sigel = this->computeElasticPrediction();

const auto& sel = sigel;
const auto seqel = sigmaeq(sel);
const auto Rel = this->ihr_Rinf_+(this->ihr_R0_-this->ihr_Rinf_)*exp(-(this->ihr_b_)*(this->p));
this->bpl = seqel > Rel;

}

/*!
* \brief set the policy for "out of bounds" conditions
*/
void
setOutOfBoundsPolicy(const OutOfBoundsPolicy policy_value){
this->policy = policy_value;
} // end of setOutOfBoundsPolicy

/*!
* \return the modelling hypothesis
*/
constexpr ModellingHypothesis::Hypothesis
getModellingHypothesis() const{
return hypothesis;
} // end of getModellingHypothesis

/*!
* \brief check bounds
*/
void checkBounds() const{
} // end of checkBounds

IntegrationResult
computePredictionOperator(const SMFlag smflag,const SMType smt) override{
using namespace std;
using namespace tfel::math;
using std::vector;
tfel::raise_if(smflag!=MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::STANDARDTANGENTOPERATOR,
"invalid prediction operator flag");
if((smt==ELASTIC)||(smt==SECANTOPERATOR)){
  computeAlteredElasticStiffness<hypothesis,Type>::exe(Dt,this->lambda_tdt,this->mu_tdt);
} else {
  return FAILURE;
}return SUCCESS;
}

real getMinimalTimeStepScalingFactor() const override{
  return this->minimal_time_step_scaling_factor;
}

std::pair<bool,real>
computeAPrioriTimeStepScalingFactor(const real current_time_step_scaling_factor) const override{
const auto time_scaling_factor = this->computeAPrioriTimeStepScalingFactorII();
return {time_scaling_factor.first,
        std::min(std::min(std::max(time_scaling_factor.second,
                                   this->minimal_time_step_scaling_factor),
                          this->maximal_time_step_scaling_factor),
                  current_time_step_scaling_factor)};
}

/*!
 * \brief Integrate behaviour law over the time step
 */
IntegrationResult integrate(const SMFlag smflag,const SMType smt) override{
using namespace std;
using namespace tfel::math;
tfel::raise_if(smflag!=MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::STANDARDTANGENTOPERATOR,
"invalid tangent operator flag");
auto error = real{};
bool converged=false;
this->iter=0;
while((converged==false)&&
(this->iter<chaboche::iterMax)){
++(this->iter);
this->computeThermodynamicForces();
const auto computeFdF_ok = this->computeFdF(false);
if(computeFdF_ok){
error=norm(this->fzeros)/(real(1+StensorSize));
}
if((!computeFdF_ok)||(!ieee754::isfinite(error))){
if(this->iter==1){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
} else {
const real integrate_one_half = real(1)/real(2);
this->zeros -= (this->zeros-this->zeros_1)*integrate_one_half;
this->updateMaterialPropertiesDependantOnStateVariables();
}
} else {
this->zeros_1  = this->zeros;
converged = error<this->epsilon;
this->additionalConvergenceChecks(converged, error, smt);
if((!converged)||(smt!=NOSTIFFNESSREQUESTED)){
}
if(!converged){
try{
TinyMatrixSolve<1+StensorSize,real>::exe(this->jacobian,this->fzeros);
}
catch(LUException&){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
}
this->zeros -= this->fzeros;
this->updateMaterialPropertiesDependantOnStateVariables();
}
}
}
if(this->iter==this->iterMax){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
}
this->updateIntegrationVariables();
this->updateStateVariables();
this->computeFinalThermodynamicForces();
this->updateAuxiliaryStateVariables();
if(smt!=NOSTIFFNESSREQUESTED){
if(!this->computeConsistentTangentOperator(smt)){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
}
}
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SUCCESS;
} // end of chaboche::integrate

/*!
* \brief compute fzeros and jacobian
*/
bool computeFdF(const bool perturbatedSystemEvaluation){
using namespace std;
using namespace tfel::math;
using std::vector;
// silent compiler warning
static_cast<void>(perturbatedSystemEvaluation); 
constexpr const auto eel_offset = 0;
static_cast<void>(eel_offset);
typename tfel::math::StensorFromTinyVectorView<N,1+StensorSize,0,real>::type feel(this->fzeros);
constexpr const auto p_offset = StensorSize;
static_cast<void>(p_offset);
real& fp(this->fzeros(StensorSize));
// derivative of variable feel by variable eel
typename tfel::math::ST2toST2FromTinyMatrixView<N,1+StensorSize,1+StensorSize,
0,0,real>::type dfeel_ddeel(this->jacobian);
// derivative of variable feel by variable p
typename tfel::math::StensorFromTinyMatrixColumnView<N,1+StensorSize,1+StensorSize,
0,StensorSize,real>::type dfeel_ddp(this->jacobian);
// derivative of variable fp by variable eel
typename tfel::math::StensorFromTinyMatrixRowView<N,1+StensorSize,1+StensorSize,
StensorSize,0,real>::type dfp_ddeel(this->jacobian);
// derivative of variable fp by variable p
real& dfp_ddp = this->jacobian(StensorSize,StensorSize);
// setting jacobian to identity
std::fill(this->jacobian.begin(),this->jacobian.end(),real(0));
for(unsigned short idx = 0; idx!=1+StensorSize;++idx){
this->jacobian(idx,idx)= real(1);
}
// setting f values to zeros
this->fzeros = this->zeros;
feel -= this->deto;

if(this->bpl){
if(!perturbatedSystemEvaluation){
}
const auto& s = this->sig;
const auto seq = sigmaeq(s);
const auto iseq = 1/max(seq,(this->relative_value_for_the_equivalent_stress_lower_bound) * this->young);
const auto dseq_ds = 3*deviator(s)*(iseq/2);
const auto d2seq_dsds = (Stensor4::M()-(dseq_ds^dseq_ds))*iseq;
const auto& n = dseq_ds;
const auto& dn_ds = d2seq_dsds;
feel += this->dp* n;
dfeel_ddp = n;
dfeel_ddeel += (2 * this->mu)*(this->theta) * ((this->dp) * dn_ds);
const auto R = this->ihr_Rinf_+(this->ihr_R0_-this->ihr_Rinf_)*exp(-(this->ihr_b_)*(this->p+(this->theta)*(this->dp)));
const auto dR_ddp = -(this->theta)*(this->ihr_b_)*(R-(this->ihr_Rinf_));
fp = (seq-R)/(this->young);
dfp_ddeel += (2 * this->mu)*(this->theta) * (dseq_ds/(this->young));
if(seq<(this->relative_value_for_the_equivalent_stress_lower_bound) * this->young){
if(dR_ddp>0){
dfp_ddp = -1*std::max(real(1.e-12),(dR_ddp)/(this->young));
} else {
dfp_ddp = -1*std::min(-real(1.e-12),(dR_ddp)/(this->young));
}
} else {
dfp_ddp = -(dR_ddp)/(this->young);
}
} // end if(this->bpl)

static_cast<void>(dfeel_ddeel); /* suppress potential warnings */
static_cast<void>(dfeel_ddp); /* suppress potential warnings */
static_cast<void>(dfp_ddeel); /* suppress potential warnings */
static_cast<void>(dfp_ddp); /* suppress potential warnings */
return true;
}

std::pair<bool,real>
computeAPosterioriTimeStepScalingFactor(const real current_time_step_scaling_factor) const override{
const auto time_scaling_factor = this->computeAPosterioriTimeStepScalingFactorII();
return {time_scaling_factor.first,
        std::min(std::min(std::max(time_scaling_factor.second,
                                   this->minimal_time_step_scaling_factor),
                          this->maximal_time_step_scaling_factor),
                 current_time_step_scaling_factor)};
}

/*!
* \brief Update the internal energy at end of the time step
* \param[in] Psi_s: internal energy at end of the time step
*/
void computeInternalEnergy(real& Psi_s) const
{
Psi_s=0;
}

/*!
* \brief Update the dissipated energy at end of the time step
* \param[in] Psi_d: dissipated energy at end of the time step
*/
void computeDissipatedEnergy(real& Psi_d) const
{
Psi_d=0;
}

/*!
* \brief compute the sound velocity
* \param[in] rho_m0: mass density in the reference configuration
*/
real computeSpeedOfSound(const massdensity&) const {
return 0;

}

bool computeConsistentTangentOperator(const SMType smt){
using namespace std;
using namespace tfel::math;
using std::vector;
TinyPermutation<1+StensorSize> jacobian_permutation;
TinyMatrixSolve<1+StensorSize,real>::decomp(this->jacobian,jacobian_permutation);
struct TFEL_VISIBILITY_LOCAL GetPartialJacobianInvert{
GetPartialJacobianInvert(chaboche& b,
const tfel::math::TinyPermutation<1+StensorSize>& p)
: behaviour(b),
permutation(p)
{}
void operator()(tfel::math::derivative_type<StrainStensor, StrainStensor>& partial_jacobian_eel){
this->behaviour.computePartialJacobianInvert(this->permutation, partial_jacobian_eel);
}
void operator()(tfel::math::derivative_type<StrainStensor, StrainStensor>& partial_jacobian_eel,
tfel::math::derivative_type<strain, StrainStensor>& partial_jacobian_p){
this->behaviour.computePartialJacobianInvert(this->permutation, partial_jacobian_eel,
partial_jacobian_p);
}
private:
chaboche& behaviour;
const tfel::math::TinyPermutation<1+StensorSize>& permutation;
}; // end of struct GetPartialJacobianInvert
GetPartialJacobianInvert getPartialJacobianInvert(*this, jacobian_permutation);
if((smt==ELASTIC)||(smt==SECANTOPERATOR)){
  computeAlteredElasticStiffness<hypothesis,Type>::exe(Dt,this->lambda_tdt,this->mu_tdt);
} else if (smt==CONSISTENTTANGENTOPERATOR){
  StiffnessTensor Hooke;
  Stensor4 Je;
  computeElasticStiffness<N,Type>::exe(Hooke,this->lambda_tdt,this->mu_tdt);
  getPartialJacobianInvert(Je);
  Dt = Hooke*Je;
} else {
  return false;
}
return true;
}

const TangentOperator& getTangentOperator() const{
return this->Dt;
}

void updateExternalStateVariables(){
this->eto  += this->deto;
this->T += this->dT;
}

//!
~chaboche()
 override = default;

private:

std::pair<bool,real> computeAPrioriTimeStepScalingFactorII() const{
return {true,this->maximal_time_step_scaling_factor};
}

std::pair<bool,real> computeAPosterioriTimeStepScalingFactorII() const{
return {true,this->maximal_time_step_scaling_factor};
}

//! policy for treating out of bounds conditions
OutOfBoundsPolicy policy = None;
}; // end of chaboche class

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
operator <<(std::ostream& os,const chaboche<hypothesis,Type,false>& b)
{
os << "εᵗᵒ : " << b.eto << '\n';
os << "Δεᵗᵒ : " << b.deto << '\n';
os << "σ : " << b.sig << '\n';
os << "Δt : " << b.dt << '\n';
os << "xyoung : " << b.xyoung << '\n';
os << "xnu : " << b.xnu << '\n';
os << "xR0 : " << b.xR0 << '\n';
os << "xQ : " << b.xQ << '\n';
os << "xb : " << b.xb << '\n';
os << "εᵉˡ : " << b.eel << '\n';
os << "Δεᵉˡ : " << b.deel << '\n';
os << "p : " << b.p << '\n';
os << "Δp : " << b.dp << '\n';
os << "T : " << b.T << '\n';
os << "ΔT : " << b.dT << '\n';
os << "staggered_scheme_bissection_algorithm : " << b.staggered_scheme_bissection_algorithm << '\n';
os << "staggered_scheme_aitken_acceleration_algorithm : " << b.staggered_scheme_aitken_acceleration_algorithm << '\n';
os << "ε : " << b.epsilon << '\n';
os << "θ : " << b.theta << '\n';
os << "relative_value_for_the_equivalent_stress_lower_bound : " << b.relative_value_for_the_equivalent_stress_lower_bound << '\n';
os << "minimal_time_step_scaling_factor : " << b.minimal_time_step_scaling_factor << '\n';
os << "maximal_time_step_scaling_factor : " << b.maximal_time_step_scaling_factor << '\n';
os << "numerical_jacobian_epsilon : " << b.numerical_jacobian_epsilon << '\n';
os << "iterMax : " << b.iterMax << '\n';
return os;
}

/*!
* Partial specialisation for chaboche.
*/
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class MechanicalBehaviourTraits<chaboche<hypothesis,Type,false> >
{
static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;
static constexpr unsigned short TVectorSize = N;
typedef tfel::math::StensorDimeToSize<N> StensorDimeToSize;
static constexpr unsigned short StensorSize = StensorDimeToSize::value;
typedef tfel::math::TensorDimeToSize<N> TensorDimeToSize;
static constexpr unsigned short TensorSize = TensorDimeToSize::value;
public:
static constexpr bool is_defined = true;
static constexpr bool use_quantities = false;
static constexpr bool hasStressFreeExpansion = false;
static constexpr bool handlesThermalExpansion = false;
static constexpr unsigned short dimension = N;
typedef Type NumType;
static constexpr unsigned short material_properties_nb = 5;
static constexpr unsigned short internal_variables_nb  = 1+StensorSize;
static constexpr unsigned short external_variables_nb  = 1;
static constexpr unsigned short external_variables_nb2 = 0;
static constexpr bool hasConsistentTangentOperator = true;
static constexpr bool isConsistentTangentOperatorSymmetric = false;
static constexpr bool hasPredictionOperator = true;
static constexpr bool hasAPrioriTimeStepScalingFactor = false;
static constexpr bool hasComputeInternalEnergy = false;
static constexpr bool hasComputeDissipatedEnergy = false;
/*!
* \return the name of the class.
*/
static const char* getName(){
return "chaboche";
}

};

/*!
* Partial specialisation for chaboche.
*/
template<typename Type>
class MechanicalBehaviourTraits<chaboche<ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS,Type,false> >
{
public:
static constexpr bool is_defined = false;
static constexpr bool use_quantities = false;
static constexpr bool hasStressFreeExpansion = false;
static constexpr bool handlesThermalExpansion = false;
static constexpr unsigned short dimension = 0u;
typedef Type NumType;
static constexpr unsigned short material_properties_nb = 0;
static constexpr unsigned short internal_variables_nb  = 0;
static constexpr unsigned short external_variables_nb  = 0;
static constexpr unsigned short external_variables_nb2 = 0;
static constexpr bool hasConsistentTangentOperator = false;
static constexpr bool isConsistentTangentOperatorSymmetric = false;
static constexpr bool hasPredictionOperator = false;
static constexpr bool hasAPrioriTimeStepScalingFactor = false;
static constexpr bool hasComputeInternalEnergy = false;
static constexpr bool hasComputeDissipatedEnergy = false;
/*!
* \return the name of the class.
*/
static const char* getName(){
return "chaboche";
}

};

/*!
* Partial specialisation for chaboche.
*/
template<typename Type>
class MechanicalBehaviourTraits<chaboche<ModellingHypothesis::PLANESTRESS,Type,false> >
{
public:
static constexpr bool is_defined = false;
static constexpr bool use_quantities = false;
static constexpr bool hasStressFreeExpansion = false;
static constexpr bool handlesThermalExpansion = false;
static constexpr unsigned short dimension = 0u;
typedef Type NumType;
static constexpr unsigned short material_properties_nb = 0;
static constexpr unsigned short internal_variables_nb  = 0;
static constexpr unsigned short external_variables_nb  = 0;
static constexpr unsigned short external_variables_nb2 = 0;
static constexpr bool hasConsistentTangentOperator = false;
static constexpr bool isConsistentTangentOperatorSymmetric = false;
static constexpr bool hasPredictionOperator = false;
static constexpr bool hasAPrioriTimeStepScalingFactor = false;
static constexpr bool hasComputeInternalEnergy = false;
static constexpr bool hasComputeDissipatedEnergy = false;
/*!
* \return the name of the class.
*/
static const char* getName(){
return "chaboche";
}

};

} // end of namespace material

} // end of namespace tfel

#endif /* LIB_TFELMATERIAL_CHABOCHE_HXX */
