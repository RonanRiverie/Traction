/*!
* \file   umatchaboche.hxx
* \brief  This file declares the umat interface for the chaboche behaviour law
* \author 
* \date   
*/

#ifndef LIB_CASTEM_CHABOCHE_HXX
#define LIB_CASTEM_CHABOCHE_HXX

#include"castem.h"
#ifdef umat
#undef umat
#endif /* umat */

#include"TFEL/Config/TFELConfig.hxx"

#include"MFront/Castem/Castem.hxx"

#ifdef __cplusplus
#include"MFront/Castem/CastemTraits.hxx"
#include"TFEL/Material/chaboche.hxx"
#endif /* __cplusplus */

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif /* NOMINMAX */
#include <windows.h>
#ifdef small
#undef small
#endif /* small */
#endif /* _WIN32 */

#ifndef MFRONT_SHAREDOBJ
#define MFRONT_SHAREDOBJ TFEL_VISIBILITY_EXPORT
#endif /* MFRONT_SHAREDOBJ */

#ifdef __cplusplus

namespace castem{

template<tfel::material::ModellingHypothesis::Hypothesis H,typename Type>
struct CastemTraits<tfel::material::chaboche<H,Type,false> >{
using ModellingHypothesis = tfel::material::ModellingHypothesis;
using ModellingHypothesisToSpaceDimension = tfel::material::ModellingHypothesisToSpaceDimension<H>;
static constexpr const CastemBehaviourType btype  = STANDARDSTRAINBASEDBEHAVIOUR;
// space dimension
static constexpr const unsigned short N           = ModellingHypothesisToSpaceDimension::value;
// tiny vector size
static constexpr const unsigned short TVectorSize = N;
// symmetric tensor size
static constexpr const unsigned short StensorSize = tfel::math::StensorDimeToSize<N>::value;
// tensor size
static constexpr const unsigned short TensorSize  = tfel::math::TensorDimeToSize<N>::value;
// size of the driving variable array (STRAN)
static constexpr const unsigned short GradientSize = StensorSize;
// size of the thermodynamic force variable array (STRESS)
static constexpr const unsigned short ThermodynamicForceVariableSize = StensorSize;
static constexpr const bool useTimeSubStepping = false;
static constexpr const bool doSubSteppingOnInvalidResults = true;
static constexpr const unsigned short maximumSubStepping = 0u;
static constexpr const bool requiresStiffnessTensor = false;
static constexpr const bool requiresThermalExpansionCoefficientTensor = false;
static constexpr const unsigned short material_properties_nb = 5;
static constexpr const unsigned short propertiesOffset = CastemIsotropicOffset<castem::STANDARDSTRAINBASEDBEHAVIOUR,H>::value + 2u;
static constexpr const CastemSymmetryType stype = castem::ISOTROPIC;
}; // end of class CastemTraits

} // end of namespace castem

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ int
umatchaboche_setParameter(const char *const,const double);

MFRONT_SHAREDOBJ int
umatchaboche_setUnsignedShortParameter(const char *const,const unsigned short);

MFRONT_SHAREDOBJ void
umatchaboche_setOutOfBoundsPolicy(const int);

MFRONT_SHAREDOBJ void
umatchaboche(castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const char           *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemReal *const,
 const castem::CastemInt  *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
       castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemReal *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
 const castem::CastemInt  *const,
       castem::CastemInt  *const,
const int);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIB_CASTEM_CHABOCHE_HXX */
