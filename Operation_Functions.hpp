#ifndef Operation_Functions_H
#define Operation_Functions_H

class Constant;
class Variable;
class Term;
//Constant to Constant arithmetic operators
Constant Constant_Constant_add(const Constant&, const Constant&);
Constant Constant_Constant_sub(const Constant&, const Constant&);
Constant Constant_Constant_mul(const Constant&, const Constant&);
Constant Constant_Constant_div(const Constant&, const Constant&);
Constant Constant_Constant_pow(const Constant&, const Constant&);

//Constant to Variable arithmetic operators
Term Constant_Variable_add(const Constant&, const Variable&);
Term Constant_Variable_sub(const Constant&, const Variable&);
Term Constant_Variable_mul(const Constant&, const Variable&);
Term Constant_Variable_div(const Constant&, const Variable&);
Term Constant_Variable_pow(const Constant&, const Variable&);


#endif