/*!
* \file   TFEL/Material/ekmcBehaviourData.hxx
* \brief  this file implements the ekmcBehaviourData class.
*         File generated by tfel version 3.4.1
 */

#ifndef LIB_TFELMATERIAL_EKMC_BEHAVIOUR_DATA_HXX
#define LIB_TFELMATERIAL_EKMC_BEHAVIOUR_DATA_HXX

#include<limits>
#include<string>
#include<sstream>
#include<iostream>
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
#include"TFEL/Math/stensor.hxx"
#include"TFEL/Math/Stensor/StensorView.hxx"
#include"TFEL/Math/Stensor/StensorConceptIO.hxx"
#include"TFEL/Math/tmatrix.hxx"
#include"TFEL/Math/Matrix/tmatrixIO.hxx"
#include"TFEL/Math/st2tost2.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2ConceptIO.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2View.hxx"
#include"TFEL/Material/ModellingHypothesis.hxx"

#include"MFront/Castem/Castem.hxx"

namespace tfel{

namespace material{

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename,bool>
class ekmcBehaviourData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type,bool use_qt>
class ekmcIntegrationData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
 operator <<(std::ostream&,const ekmcBehaviourData<hypothesis,Type,false>&);

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class ekmcBehaviourData<hypothesis,Type,false>
{

static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;
TFEL_STATIC_ASSERT(N==1||N==2||N==3);
TFEL_STATIC_ASSERT(tfel::typetraits::IsFundamentalNumericType<Type>::cond);
TFEL_STATIC_ASSERT(tfel::typetraits::IsReal<Type>::cond);

friend std::ostream& operator<< <>(std::ostream&,const ekmcBehaviourData&);

/* integration data is declared friend to access   driving variables at the beginning of the time step */
friend class ekmcIntegrationData<hypothesis,Type,false>;

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

protected:

StrainStensor eto;

StressStensor sig;

#line 11 "ekmc.mfront"
strainrate de0;
#line 12 "ekmc.mfront"
real Ea;
#line 13 "ekmc.mfront"
real Va;
#line 14 "ekmc.mfront"
stress P1;
#line 15 "ekmc.mfront"
real P2;
#line 16 "ekmc.mfront"
real omega;
#line 17 "ekmc.mfront"
stress R0;
#line 18 "ekmc.mfront"
stress Q;
#line 19 "ekmc.mfront"
real b;
#line 20 "ekmc.mfront"
stress H;
#line 21 "ekmc.mfront"
real nta;
#line 22 "ekmc.mfront"
real palpha;
#line 23 "ekmc.mfront"
real ta0;
stress young;
real nu;

StrainStensor eel;
#line 25 "ekmc.mfront"
strain p;
#line 28 "ekmc.mfront"
time ta;
temperature T;

public:

/*!
* \brief Default constructor
*/
ekmcBehaviourData()
{}

/*!
* \brief copy constructor
*/
ekmcBehaviourData(const ekmcBehaviourData& src)
: eto(src.eto),
sig(src.sig),
de0(src.de0),
Ea(src.Ea),
Va(src.Va),
P1(src.P1),
P2(src.P2),
omega(src.omega),
R0(src.R0),
Q(src.Q),
b(src.b),
H(src.H),
nta(src.nta),
palpha(src.palpha),
ta0(src.ta0),
young(src.young),
nu(src.nu),
eel(src.eel),
p(src.p),
ta(src.ta),
T(src.T)
{}

/*
 * \brief constructor for the Castem interface
 * \param[in] CASTEMT_: temperature
 * \param[in] CASTEMmat: material properties
 * \param[in] CASTEMint_vars: state variables
 * \param[in] CASTEMext_vars: external std::ate variables
 */
ekmcBehaviourData(const Type* const CASTEMT_,const Type* const CASTEMmat,
const Type* const CASTEMint_vars
,const Type* const)
: de0(CASTEMmat[0]),
Ea(CASTEMmat[1]),
Va(CASTEMmat[2]),
P1(CASTEMmat[3]),
P2(CASTEMmat[4]),
omega(CASTEMmat[5]),
R0(CASTEMmat[6]),
Q(CASTEMmat[7]),
b(CASTEMmat[8]),
H(CASTEMmat[9]),
nta(CASTEMmat[10]),
palpha(CASTEMmat[11]),
ta0(CASTEMmat[12]),
young(CASTEMmat[-6]),
nu(CASTEMmat[-5]),
eel(&CASTEMint_vars[0]),
p(CASTEMint_vars[StensorSize]),
ta(CASTEMint_vars[1+StensorSize]),
T(*CASTEMT_)
{
}

void setCASTEMBehaviourDataGradients(const Type* const CASTEMstran)
{
this->eto.importVoigt(CASTEMstran);
}

void setCASTEMBehaviourDataThermodynamicForces(const Type* const CASTEMstress_)
{
this->sig.importTab(CASTEMstress_);
}


/*
* \brief Assignement operator
*/
ekmcBehaviourData&
operator=(const ekmcBehaviourData& src){
this->eto = src.eto;
this->sig = src.sig;
this->de0 = src.de0;
this->Ea = src.Ea;
this->Va = src.Va;
this->P1 = src.P1;
this->P2 = src.P2;
this->omega = src.omega;
this->R0 = src.R0;
this->Q = src.Q;
this->b = src.b;
this->H = src.H;
this->nta = src.nta;
this->palpha = src.palpha;
this->ta0 = src.ta0;
this->young = src.young;
this->nu = src.nu;
this->eel = src.eel;
this->p = src.p;
this->ta = src.ta;
this->T = src.T;
return *this;
}

void
CASTEMexportStateData(Type * const CASTEMstress_,Type * const CASTEMstatev) const
{
using namespace tfel::math;
this->sig.exportTab(CASTEMstress_);
exportToBaseTypeArray(this->eel,&CASTEMstatev[0]);
CASTEMstatev[StensorSize] = this->p;
CASTEMstatev[1+StensorSize] = this->ta;
} // end of CASTEMexportStateData

}; // end of ekmcBehaviourDataclass

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
operator <<(std::ostream& os,const ekmcBehaviourData<hypothesis,Type,false>& b)
{
os << "εᵗᵒ : " << b.eto << '\n';
os << "σ : " << b.sig << '\n';
os << "de0 : " << b.de0 << '\n';
os << "Ea : " << b.Ea << '\n';
os << "Va : " << b.Va << '\n';
os << "P1 : " << b.P1 << '\n';
os << "P2 : " << b.P2 << '\n';
os << "omega : " << b.omega << '\n';
os << "R0 : " << b.R0 << '\n';
os << "Q : " << b.Q << '\n';
os << "b : " << b.b << '\n';
os << "H : " << b.H << '\n';
os << "nta : " << b.nta << '\n';
os << "palpha : " << b.palpha << '\n';
os << "ta0 : " << b.ta0 << '\n';
os << "young : " << b.young << '\n';
os << "nu : " << b.nu << '\n';
os << "εᵉˡ : " << b.eel << '\n';
os << "p : " << b.p << '\n';
os << "ta : " << b.ta << '\n';
os << "T : " << b.T << '\n';
return os;
}

} // end of namespace material

} // end of namespace tfel

#endif /* LIB_TFELMATERIAL_EKMC_BEHAVIOUR_DATA_HXX */
