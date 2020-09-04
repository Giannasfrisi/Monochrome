#pragma once
#include "bindings_iresponder.h"
#include "bindings_layer.h"

typedef struct _UIViewObject {
	IResponderObject _super;
	Ref<UIView> handle = nullptr;
} UIViewObject;

PyObject* UIViewObject_New(PyTypeObject* type, PyObject* args, PyObject* kwds);
int UIViewObject_Init(UIViewObject* type, PyObject* args, PyObject* kwds);

//============ Methods ============ //
PyObject* UIViewObject_AddSubview(UIViewObject* self, PyObject* args);
PyObject* UIViewObject_RemoveSubview(UIViewObject* self, PyObject* args);

static PyMethodDef UIViewObjectMethods[] = {
	{ "add_subview", (PyCFunction)UIViewObject_AddSubview, METH_VARARGS, "add_subview" },
	{ "remove_subview", (PyCFunction)UIViewObject_RemoveSubview, METH_VARARGS, "remove_subview" },
	{ NULL, NULL, 0, NULL }
};

//============ Getters ============ //
PyObject* UIViewObject_GetVisible(UIViewObject* self, void* closure);
PyObject* UIViewObject_GetLayer(UIViewObject* self, void* closure);
PyObject* UIViewObject_GetZIndex(UIViewObject* self, void* closure);

//============ Setters ============ //
int UIViewObject_SetVisible(UIViewObject* self, PyObject* value, void* closure);
int UIViewObject_SetZIndex(UIViewObject* self, PyObject* value, void* closure);

static PyGetSetDef UIViewObjectGettersSetters[] = {
	{ "visible", (getter)UIViewObject_GetVisible, (setter)UIViewObject_SetVisible, "visible", NULL },
	{ "layer", (getter)UIViewObject_GetLayer, (setter)0, "layer", NULL },
	{ "z_index", (getter)UIViewObject_GetZIndex, (setter)UIViewObject_SetZIndex, "z_index", NULL },
	{ NULL, NULL, 0, NULL }
};

static PyTypeObject UIViewObject_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
	"UIView", /*tp_name*/
	sizeof(UIViewObject), /*tp_basicsize*/
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
	0, 0, 0, 0, 0, 0, 0, 
	UIViewObjectMethods, /*tp_methods*/
	0, /*tp_members*/
	UIViewObjectGettersSetters, /*tp_getset*/
	&IResponderObject_Type, /*tp_base*/
	0, 0, 0, 0, 
	(initproc)UIViewObject_Init, /*tp_init*/
	0, /*tp_alloc*/
	UIViewObject_New, /*tp_new*/
	0, /*tp_free*/
	0, /*tp_is_gc*/
};

PyTypeObject& UIViewObject_GetType();
