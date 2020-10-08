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

//Constant to Term arithmetic operators
Term Constant_Term_add(const Constant&, const Term&);
Term Constant_Term_sub(const Constant&, const Term&);
Term Constant_Term_mul(const Constant&, const Term&);
Term Constant_Term_div(const Constant&, const Term&);
Term Constant_Term_pow(const Constant&, const Term&);




//Variable to Constant arithmetic operators
Term Variable_Constant_add(const Variable&, const Constant&);
Term Variable_Constant_sub(const Variable&, const Constant&);
Term Variable_Constant_mul(const Variable&, const Constant&);
Term Variable_Constant_div(const Variable&, const Constant&);
Term Variable_Constant_pow(const Variable&, const Constant&);

//Variable to Variable arithmetic operators
Term Variable_Variable_add(const Variable&, const Variable&);
Term Variable_Variable_sub(const Variable&, const Variable&);
Term Variable_Variable_mul(const Variable&, const Variable&);
Term Variable_Variable_div(const Variable&, const Variable&);
Term Variable_Variable_pow(const Variable&, const Variable&);

//Variable to Term arithmetic operators
Term Variable_Term_add(const Variable&, const Variable&);
Term Variable_Term_sub(const Variable&, const Variable&);
Term Variable_Term_mul(const Variable&, const Variable&);
Term Variable_Term_div(const Variable&, const Variable&);
Term Variable_Term_pow(const Variable&, const Variable&);


//Term to Constant arithmetic operators
Term Term_Constant_add(const Term&, const Constant&);
Term Term_Constant_sub(const Term&, const Constant&);
Term Term_Constant_mul(const Term&, const Constant&);
Term Term_Constant_div(const Term&, const Constant&);
Term Term_Constant_pow(const Term&, const Constant&);

//Term to Variable arithmetic operators
Term Term_Variable_add(const Term&, const Variable&);
Term Term_Variable_sub(const Term&, const Variable&);
Term Term_Variable_mul(const Term&, const Variable&);
Term Term_Variable_div(const Term&, const Variable&);
Term Term_Variable_pow(const Term&, const Variable&);

//Term to Term arithmetic operators
Term Term_Term_add(const Term&, const Term&);
Term Term_Term_sub(const Term&, const Term&);
Term Term_Term_mul(const Term&, const Term&);
Term Term_Term_div(const Term&, const Term&);
Term Term_Term_pow(const Term&, const Term&);




#endif