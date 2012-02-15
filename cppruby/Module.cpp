
#include "Module.hpp"

namespace rb
{
    
    Module Module::Define(const char* name)
    {
        return rb_define_module(name);
    }
    
    Module Module::Define(Module under, const char* name)
    {
        return rb_define_module_under(under, name);
    }
    
	Module& Module::include( Module module )
	{
		rb_include_module( value, module );
	}
}
