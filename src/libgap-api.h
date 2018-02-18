// LibGAP API - API for using GAP as shared library.
// Most functions defined here are just wrappers of
// internal GAP kernel functions.

// The corresponding kernel functions are written before the functions
// declarations. Please see their documentation for more details.

#ifndef LIBGAP__API__H
#define LIBGAP__API__H

#include <src/gap.h>

/*************************************************************************/
/*** Integer *************************************************************/
/*************************************************************************/

// INTOBJ_INT
Obj GAP_IntObj_Int( Int );

// INT_INTOBJ
Int GAP_Int_IntObj( Obj );

/*************************************************************************/
/*** Strings *************************************************************/
/*************************************************************************/

// CSTR_STRING
char* GAP_CSTR_STRING( Obj );

// MakeString
Obj GAP_MakeString( char * );

/*************************************************************************/
/*** List ****************************************************************/
/*************************************************************************/

// NEW_PLIST( T_PLIST, length )
Obj GAP_NewPList( UInt length );

// SET_LEN_PLIST
void GAP_SetLenPList( Obj, Int );

// AssPlist
void GAP_AssPList( Obj list, Int pos, Obj elem );

// SET_ELM_PLIST
void GAP_SetElmPList( Obj, Int, Obj );

// ELM_PLIST
Obj GAP_ElmPList( Obj, Int );

// LEN_PLIST
Int GAP_LenPList( Obj );

/*************************************************************************/
/*** GVars ***************************************************************/
/*************************************************************************/

// Combines GVarName and ValGVar. For a given string, it returns the value
// of the gvar with name <name>, or NULL if the global variable is not defined.
Obj GAP_ValGVar( char* name );

/*************************************************************************/
/*** Functions ***********************************************************/
/*************************************************************************/

// CallFuncList
Obj GAP_CallFuncList( Obj, Obj );

#endif
