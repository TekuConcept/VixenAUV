%module "Power"
%{
	#include "PowerInterface.h"
%}
%include "PowerInterface.h"

// This requires a SWIG version that supports native functions...
// You can clone the git repo that does here: https://github.com/TekuConcept/swig
%wrapper %{
static SwigV8ReturnValue _wrap_Power_waitStart(const SwigV8Arguments &args)
{
	SWIGV8_HANDLESCOPE();

	v8::Handle<v8::Value> jsresult;
	Power *arg1 = (Power *) 0 ;
	void *argp1 = 0 ;
	int res1 = 0 ;
	
	if(args.Length() != 1) SWIG_exception_fail(SWIG_ERROR, "Illegal number of arguments for _wrap_Power_waitStart.");

	res1 = SWIG_ConvertPtr(args.Holder(), &argp1,SWIGTYPE_p_Power, 0 |  0 );
    if (!SWIG_IsOK(res1)) {
        SWIG_exception_fail(SWIG_ArgError(res1), "in method '" "Power_waitStart" "', argument " "1"" of type '" "Power *""'"); 
    }
    arg1 = (Power *)(argp1);
    (arg1)->waitStart(args);
    jsresult = SWIGV8_UNDEFINED();

    SWIGV8_RETURN(jsresult);
    
    goto fail;
fail:
    SWIGV8_RETURN(SWIGV8_UNDEFINED());
}
%}

%native(waitForStartSignal) void _wrap_Power_waitStart();