/*!
* \file   include/chaboche_PoissonRatio-castem.hxx
* \brief  this file declares the chaboche_PoissonRatio MaterialLaw.
*         File generated by tfel version 3.4.1
 */

#ifndef CHABOCHE_POISSONRATIO_CASTEM_HH
#define CHABOCHE_POISSONRATIO_CASTEM_HH

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif /* NOMINMAX */
#include <windows.h>
#ifdef small
#undef small
#endif /* small */
#ifndef MFRONT_SHAREDOBJ
#ifdef  MFRONT_COMPILING
#define MFRONT_SHAREDOBJ __declspec(dllexport)
#else /* MFRONT_COMPILING */
#define MFRONT_SHAREDOBJ __declspec(dllimport)
#endif /* MFRONT_COMPILING */
#endif /* MFRONT_SHAREDOBJ */
#else
#ifndef MFRONT_SHAREDOBJ
#ifdef __GNUC__
#define MFRONT_SHAREDOBJ __attribute__((visibility("default")))
#else
#define MFRONT_SHAREDOBJ
#endif /* __GNUC__ */
#endif /* MFRONT_SHAREDOBJ */
#endif /* _WIN32 */

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ double
chaboche_PoissonRatio(const double * const);

#ifdef __cplusplus
} // end of extern "C"
#endif /* __cplusplus */

#endif /* CHABOCHE_POISSONRATIO_CASTEM_HH */
