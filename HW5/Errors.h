#ifndef ERRORS_H
#define ERRORS_H
/*
*		HEXGAME ERRORS CLASS FOR TRY-CATCH-THROW
*		BY SULEYMAN GOLBOL
*		1801042656
*/
#include <stdexcept>
using std::runtime_error;
using std::string;

namespace hexname{

class Errors: public runtime_error{
	public:
        Errors(string which_error): runtime_error(which_error)
        {/*BODY INTENTIONALLY EMPTY*/} 
    private:
        
};


}	//End of namespace.
#endif
