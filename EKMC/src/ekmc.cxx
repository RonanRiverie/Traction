/*!
* \file   ekmc.cxx
* \brief  this file implements the ekmc Behaviour.
*         File generated by tfel version 3.4.1
 */

#include<string>
#include<cstring>
#include<sstream>
#include<fstream>
#include<stdexcept>

#include"TFEL/Raise.hxx"
#include"TFEL/Material/ekmcBehaviourData.hxx"
#include"TFEL/Material/ekmcIntegrationData.hxx"
#include"TFEL/Material/ekmc.hxx"

namespace tfel{

namespace material{

ekmcParametersInitializer&
ekmcParametersInitializer::get()
{
static ekmcParametersInitializer i;
return i;
}

ekmcParametersInitializer::ekmcParametersInitializer()
{
this->numerical_jacobian_epsilon = 1e-08;
this->epsilon = 1e-14;
this->theta = 1;
this->relative_value_for_the_equivalent_stress_lower_bound = 1e-12;
this->minimal_time_step_scaling_factor = 0.1;
this->maximal_time_step_scaling_factor = 1.7976931348623e+308;
this->iterMax = 100;
// Reading parameters from a file
ekmcParametersInitializer::readParameters(*this,"ekmc-parameters.txt");
}

void
ekmcParametersInitializer::set(const char* const key,
const double v){
using namespace std;
if(::strcmp("numerical_jacobian_epsilon",key)==0){
this->numerical_jacobian_epsilon = v;
} else if(::strcmp("epsilon",key)==0){
this->epsilon = v;
} else if(::strcmp("theta",key)==0){
this->theta = v;
} else if(::strcmp("RelativeValueForTheEquivalentStressLowerBoundDefinition",key)==0){
this->relative_value_for_the_equivalent_stress_lower_bound = v;
} else if(::strcmp("minimal_time_step_scaling_factor",key)==0){
this->minimal_time_step_scaling_factor = v;
} else if(::strcmp("maximal_time_step_scaling_factor",key)==0){
this->maximal_time_step_scaling_factor = v;
} else {
tfel::raise("ekmcParametersInitializer::set: "
" no parameter named '"+std::string(key)+"'");
}
}

void
ekmcParametersInitializer::set(const char* const key,
const unsigned short v){
using namespace std;
if(::strcmp("iterMax",key)==0){
this->iterMax = v;
} else {
tfel::raise("ekmcParametersInitializer::set: "
"no parameter named '"+std::string(key)+"'");
}
}

double
ekmcParametersInitializer::getDouble(const std::string& n,
const std::string& v)
{
double value;
std::istringstream converter(v);
converter >> value;
tfel::raise_if(!converter||(!converter.eof()),
"ekmcParametersInitializer::getDouble: "
"can't convert '"+v+"' to double for parameter '"+ n+"'");
return value;
}

unsigned short
ekmcParametersInitializer::getUnsignedShort(const std::string& n,
const std::string& v)
{
unsigned short value;
std::istringstream converter(v);
converter >> value;
tfel::raise_if(!converter||(!converter.eof()),
"ekmcParametersInitializer::getUnsignedShort: "
"can't convert '"+v+"' to unsigned short for parameter '"+ n+"'");
return value;
}

void
ekmcParametersInitializer::readParameters(ekmcParametersInitializer& pi,const char* const fn){
auto tokenize = [](const std::string& line){
std::istringstream tokenizer(line);
std::vector<std::string> tokens;
std::copy(std::istream_iterator<std::string>(tokenizer),
std::istream_iterator<std::string>(),
std::back_inserter(tokens));
return tokens;
};
std::ifstream f(fn);
if(!f){
return;
}
size_t ln = 1u;
while(!f.eof()){
auto line = std::string{};
std::getline(f,line);
auto tokens = tokenize(line);
auto throw_if = [ln,line,fn](const bool c,const std::string& m){
tfel::raise_if(c,"ekmcParametersInitializer::readParameters: "
"error at line '"+std::to_string(ln)+"' "
"while reading parameter file '"+std::string(fn)+"'"
"("+m+")");
};
if(tokens.empty()){
continue;
}
if(tokens[0][0]=='#'){
continue;
}
throw_if(tokens.size()!=2u,"invalid number of tokens");
if("numerical_jacobian_epsilon"==tokens[0]){
pi.numerical_jacobian_epsilon = ekmcParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("epsilon"==tokens[0]){
pi.epsilon = ekmcParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("theta"==tokens[0]){
pi.theta = ekmcParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("RelativeValueForTheEquivalentStressLowerBoundDefinition"==tokens[0]){
pi.relative_value_for_the_equivalent_stress_lower_bound = ekmcParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("minimal_time_step_scaling_factor"==tokens[0]){
pi.minimal_time_step_scaling_factor = ekmcParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("maximal_time_step_scaling_factor"==tokens[0]){
pi.maximal_time_step_scaling_factor = ekmcParametersInitializer::getDouble(tokens[0],tokens[1]);
} else if("iterMax"==tokens[0]){
pi.iterMax = ekmcParametersInitializer::getUnsignedShort(tokens[0],tokens[1]);
} else {
throw_if(true,"invalid parameter '"+tokens[0]+"'");
}
}
}

} // end of namespace material

} // end of namespace tfel

