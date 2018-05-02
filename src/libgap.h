/* LibGAP - a shared library version of the GAP kernel
 * Copyright (C) 2013 Volker Braun <vbraun.name@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. 
 */

#ifndef LIBGAP__H
#define LIBGAP__H


/*************************************************************************/
/*** Initialize / Finalize ***********************************************/
/*************************************************************************/

/* To setup libGAP, you must call GAP_initialize() to
 * set argv and env
 *
 * Two mandatory component of argv is "-K", "memory_pool_size" to set the
 * libgap memory pool size. For example,
 *
 * argc = 5
 * argv = "libgap", "-l", "/path/to/gap-library", "-K", "64M", NULL
 * env = NULL
 */
void GAP_initialize(int argc, char** argv, char** env);


/* Currently, this does nothing. One day, it should correctly
 * finalize libgap so that it can be reinitialized with a different
 * memory pool...
 */
void GAP_finalize(void);


/*************************************************************************/
/*** Local (per-function) Initialization  ********************************/
/*************************************************************************/

/* You must call GAP_mark_stack_bottom() in every function that
 * calls into the libGAP C functions. The reason is that the GAP
 * memory manager will automatically keep objects alive that are
 * referenced in local (stack-allocated) variables. While convenient,
 * this requires to look through the stack to find anything that looks
 * like an address to a memory bag.
 *
 * I suggest you use GAP_enter / GAP_exit (see below) instead of
 * calling GAP_mark_stack_bottom manually.
 */

extern void* StackBottomBags;

/* This is implemented as a macro to run in the same stack frame as
 * the calling function */
#ifdef __GNUC__
#define GAP_mark_stack_bottom()              \
  StackBottomBags = __builtin_frame_address(0);
#else  /* try x86 asm */ 
#define GAP_mark_stack_bottom()                 \
  register void* ebp asm("ebp");                   \
  StackBottomBags = ebp;
#endif


/* Its important to mark the stack bottom before every call into
 * libGAP. But this requires vigilance against the following pattern:
 * 
 * void f() {
 *   GAP_mark_stack_bottom();
 *   call_libGAP_function();
 * }
 *
 * void g() {
 *   GAP_mark_stack_bottom();
 *   f();                     // f() changed the stack bottom marker 
 *   call_libGAP_function();  //  boom 
 * }
 * 
 * The solution is to re-order g() to first call f(). In order to
 * catch this error, it is recommended that you wrap calls into libGAP
 * in GAP_enter/GAP_exit blocks and not call GAP_mark_stack_bottom
 * manually.
 */

extern int GAP_in_enter_exit_block;

#define GAP_enter()						 \
  if (GAP_in_enter_exit_block) {				 \
    GAP_set_error("Entered a critical block twice");		 \
    GAP_call_error_handler();				 \
  }								 \
  GAP_in_enter_exit_block = 1;				 \
  GAP_mark_stack_bottom();

#define GAP_exit()							\
  if (!GAP_in_enter_exit_block) {					\
    GAP_set_error("Called GAP_exit without previous GAP_enter"); \
    GAP_call_error_handler();					\
  }									\
  GAP_in_enter_exit_block = 0;



/*************************************************************************/
/*** Garbage collector callback ******************************************/
/*************************************************************************/

/* This will be called before garbage collection by GAP's memory
 * manager GASMAN. You can use the MARK_BAG(bag) GAP function to mark
 * GAP memory bags that you want to survive the following garbage
 * collection.
 */

typedef void(*GAP_gasman_callback_ptr)(void);
void GAP_set_gasman_callback(GAP_gasman_callback_ptr callback);

/*************************************************************************/
/*** Input/Output interaction ********************************************/
/*************************************************************************/

/* Set a function that will be called if an error occurs. If set, this
 * will be called instead of a longjmp() back to the GAP main loop.
 */

typedef void(*GAP_error_func_ptr)(char* msg);
void GAP_set_error_handler(GAP_error_func_ptr callback);


/* GAP uses this function to call the error handler, and you can too */
void GAP_call_error_handler(void);


/* libGAP is supposed to be used as follows from your code:
 *
 * 1. call GAP_start_interaction(char* inputline). The inputline
 *    buffer is not copied, it is your responsibility to keep it alive
 *    until you call GAP_finish_interaction()
 *
 * 2. Make GAP perform some computation, for example by calling
 *    ReadEvalCommand()
 *
 * 3. The output is accumulated in the buffer returned by
 *    GAP_get_output(). The buffer is owned by libgap, you must not
 *    free it.
 *
 * 4. call GAP_finish_interaction() when you are finished with the
 *    GAP commands. The GAP parser is reset and the output buffer is
 *    freed.
 */
void GAP_start_interaction(char* inputline);
void GAP_set_input(char* line);
char* GAP_get_output(void);
void GAP_finish_interaction(void);



#endif /* LIBGAP__H */
