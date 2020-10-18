#include <z3++.h>
#include <iostream>
#include <vector>


void example_that_works(){

	// problem definition (context)
	z3::context c;

	// add three variables to the context
	z3::expr x = c.bool_const("x");
	z3::expr y = c.bool_const("y");
	z3::expr z = c.bool_const("z");

	// new solver passing the context as parameter
	z3::solver s (c);

	// creates a new conjecture (x or y or z)
	z3::expr conjecture = (x || y || z);
	s.add(conjecture); //adds conjecture to the solver
	
	//find all solutions
	while(s.check() != z3::unsat){

		//get current solution from solver 
		z3::model model = s.get_model();
		//std::cout << "model >> " << model << std::endl;

		//print the values of the model
		std::cout << "x: " << model.eval(x) << std::endl;
		std::cout << "y: " << model.eval(y) << std::endl;
		std::cout << "z: " << model.eval(z) << std::endl;

		//add the negation of the model to the solver to make
		//current solution unavailable
        s.add(!(
        	x == model.eval(x) &&
	       	y == model.eval(y) &&
        	z == model.eval(z)
        ));
        
	    std::cout << "solver >> " << s << std::endl;
    }
}

void orca_example(){
	
	// problem definition (context)
	z3::context c;

	// add variables to the context
	z3::expr RV32I = c.bool_const("RV32I");
	z3::expr RV32IM = c.bool_const("RV32IM");
	z3::expr SEPF = c.bool_const("sepf");
	z3::expr hf_fplib = c.bool_const("hf-fplib");
	z3::expr dfloat = c.bool_const("-Dfloat");
	
	// new solver passing the context as parameter
	z3::solver s (c);

	// creates new conjectures
	z3::expr conjectureA = 
		(RV32I && !RV32IM) || (!RV32I && RV32IM);
	z3::expr conjectureB = 
		(SEPF && hf_fplib && dfloat) ||
		(!SEPF && !hf_fplib && !dfloat);
	s.add(conjectureA); //adds conjecture
	s.add(conjectureB);
	
	//find all solutions
	while(s.check() != z3::unsat){

		//get current solution from solver 
		z3::model model = s.get_model();

		//add the negation of the model to the solver to make
		//current solution unavailable
        s.add(!(
        	RV32I == model.eval(RV32I) &&
			RV32IM == model.eval(RV32IM) &&
        	SEPF == model.eval(SEPF) &&
        	hf_fplib == model.eval(hf_fplib) &&
	       	dfloat == model.eval(dfloat)
        ));
        
	    std::cout << s << std::endl;
    }
	
}

int main(int argc, char** argv){

	example_that_works();
	orca_example();
	return 0;
}
