// LibGAP API - API for using GAP as shared library.

#include <src/libgap-api.h>

#include <src/calls.h>
#include <src/gvars.h>
#include <src/intobj.h>
#include <src/plist.h>
#include <src/stringobj.h>

/*************************************************************************/
/*** Integer *************************************************************/
/*************************************************************************/

Obj GAP_IntObj_Int( Int value )
{
    return INTOBJ_INT( value );
}

Int GAP_Int_IntObj( Obj value )
{
    return INT_INTOBJ( value );
}

/*************************************************************************/
/*** Strings *************************************************************/
/*************************************************************************/

char* GAP_CSTR_STRING( Obj str ){
    return CSTR_STRING( str );
}

Obj GAP_MakeString( char * str )
{
    return MakeString( str );
}

/*************************************************************************/
/*** List ****************************************************************/
/*************************************************************************/

Obj GAP_NewPList( UInt length )
{
    return NEW_PLIST( T_PLIST, length );
}

void GAP_SetLenPList( Obj list, Int len ){
    SET_LEN_PLIST( list, len );
}

void GAP_AssPList( Obj list, Int pos, Obj elem ){
    AssPlist( list, pos, elem );
}

void GAP_SetElmPList( Obj list, Int pos, Obj elem ){
    SET_ELM_PLIST( list, pos, elem );
}

Obj GAP_ElmPList( Obj list, Int pos ){
    return ELM_PLIST( list, pos );
}

Int GAP_LenPList( Obj list ){
    return LEN_PLIST( list );
}

/*************************************************************************/
/*** GVars ***************************************************************/
/*************************************************************************/

Obj GAP_ValGVar( char* name ){
    UInt gvar = GVarName( name );
    if( gvar != 0 ){
        return ValGVar( gvar );
    }else{
        return NULL;
    }
}

/*************************************************************************/
/*** Functions ***********************************************************/
/*************************************************************************/

Obj GAP_CallFuncList( Obj func, Obj arg_list )
{
    return CallFuncList( func, arg_list );
}
