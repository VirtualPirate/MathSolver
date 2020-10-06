#ifndef Operation_Functions_H
#define Operation_Functions_H

class Constant;
//Constant to Constant arithmetic operators
Constant Constant_Constant_add(const Constant&, const Constant&);
Constant Constant_Constant_sub(const Constant&, const Constant&);
Constant Constant_Constant_mul(const Constant&, const Constant&);
Constant Constant_Constant_div(const Constant&, const Constant&);
Constant Constant_Constant_pow(const Constant&, const Constant&);

#endif