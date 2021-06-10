#include "Substitutor.hpp"
#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"
#include "Parser.hpp"
#include "Tests.hpp"

namespace test{
    void show_sizes(){
        using namespace std;
        cout << "sizeof Constant is -> " << sizeof(Constant) << endl;
        cout << "sizeof Variable is -> " << sizeof(Variable) << endl;
        cout << "sizeof OperandList is -> " << sizeof(OperandList) << endl;
        cout << "sizeof Term is -> " << sizeof(Term) << endl;
        cout << "sizeof Expression is -> " << sizeof(Expression) << endl;
        cout << "sizeof Operand is -> " << sizeof(Operand) << endl;
    }
}

