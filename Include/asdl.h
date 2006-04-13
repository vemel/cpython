#ifndef Py_ASDL_H
#define Py_ASDL_H

typedef PyObject * identifier;
typedef PyObject * string;
typedef PyObject * object;

#ifndef __cplusplus
typedef enum {false, true} bool;
#endif

/* It would be nice if the code generated by asdl_c.py was completely
   independent of Python, but it is a goal the requires too much work
   at this stage.  So, for example, I'll represent identifiers as
   interned Python strings.
*/

/* XXX A sequence should be typed so that its use can be typechecked. */

typedef struct {
    int size;
    union {
        void *elements[1];
	unsigned int enum_type[1];
    } elt;
} asdl_seq;

asdl_seq *asdl_seq_new(int size, PyArena *arena);

#define asdl_seq_GET(S, I) (S)->elt.elements[(I)]
#define asdl_seq_GET_ENUM(S, I) (S)->elt.enum_type[(I)]
#define asdl_seq_LEN(S) ((S) == NULL ? 0 : (S)->size)
#ifdef Py_DEBUG
#define asdl_seq_SET(S, I, V) { \
        int _asdl_i = (I); \
        assert((S) && _asdl_i < (S)->size); \
        (S)->elt.elements[_asdl_i] = (V); \
}
#else
#define asdl_seq_SET(S, I, V) (S)->elements[I] = (V)
#endif

#endif /* !Py_ASDL_H */
