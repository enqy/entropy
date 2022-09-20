/* ------------------------------ DIRECTIVES -------------------------------- */
/* Disable some warnings that the generated code can trigger. */
#if defined(__clang__) && __clang_major__ >= 3
  #pragma clang diagnostic ignored "-Wtype-limits"
  #pragma clang diagnostic ignored "-Wwrite-strings"
  #pragma clang diagnostic ignored "-Wunused"
  #pragma clang diagnostic ignored "-Wunused-parameter"
  #pragma clang diagnostic ignored "-Wmissing-field-initializers"
  #pragma clang diagnostic ignored "-Wparentheses-equality"
  #pragma clang diagnostic ignored "-Wtautological-compare"
  #ifndef __cplusplus
    #pragma clang diagnostic ignored "-Wmissing-braces"
    #pragma clang diagnostic ignored "-Wincompatible-pointer-types"
    #pragma clang diagnostic error   "-Wimplicit-function-declaration"
    #pragma clang diagnostic error   "-Wimplicit-int"
  #else
    #pragma clang diagnostic ignored "-Wnarrowing"
  #endif
#elif defined(__GNUC__) && __GNUC__ >= 5
  #pragma GCC diagnostic ignored "-Wtype-limits"
  #pragma GCC diagnostic ignored "-Wwrite-strings"
  #pragma GCC diagnostic ignored "-Wunused-parameter"
  #pragma GCC diagnostic ignored "-Wunused-value"
  #pragma GCC diagnostic ignored "-Wunused-variable"
  #pragma GCC diagnostic ignored "-Wunused-function"
  #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
  #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  #ifndef __cplusplus
    #pragma GCC diagnostic ignored "-Wmissing-braces"
    #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
    #pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
    #pragma GCC diagnostic error   "-Wimplicit-function-declaration"
    #pragma GCC diagnostic error   "-Wimplicit-int"
  #else
    #pragma GCC diagnostic ignored "-Wnarrowing"
  #endif
#endif
#if defined(_WIN32) && !defined(_CRT_SECURE_NO_WARNINGS)
  #define _CRT_SECURE_NO_WARNINGS
#endif
/* Macro used to perform compile-time checks. */
#if __STDC_VERSION__ >= 201112L
  #define NELUA_STATIC_ASSERT _Static_assert
#elif __cplusplus >= 201103L
  #define NELUA_STATIC_ASSERT static_assert
#else
  #define NELUA_STATIC_ASSERT(x, y)
#endif
/* Macro used to get alignment of a type. */
#if __STDC_VERSION__ >= 201112L
  #define NELUA_ALIGNOF _Alignof
#elif __cplusplus >= 201103L
  #define NELUA_ALIGNOF alignof
#elif defined(__GNUC__)
  #define NELUA_ALIGNOF __alignof__
#elif defined(_MSC_VER)
  #define NELUA_ALIGNOF __alignof
#else
  #define NELUA_ALIGNOF(x)
#endif
/* Checks if Nelua and C agrees on pointer size. */
NELUA_STATIC_ASSERT(sizeof(void*) == 8 && NELUA_ALIGNOF(void*) == 8, "Nelua and C disagree on pointer size or alignment");
/* Enable 64 bit offsets for stdio APIs. */
#if !defined(_FILE_OFFSET_BITS) && __SIZEOF_LONG__ >= 8
  #define _FILE_OFFSET_BITS 64
#endif
/* Enable POSIX APIs in included headers. */
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && !defined(_GNU_SOURCE) && !defined(_DEFAULT_SOURCE)
  #if defined(__gnu_linux__)
    #define _GNU_SOURCE
  #else
    #define _XOPEN_SOURCE 600
  #endif
#endif
#include <stdbool.h>
#include <stdint.h>
/* Macro used to force inlining a function. */
#ifdef __GNUC__
  #define NELUA_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
  #define NELUA_INLINE __forceinline
#elif __STDC_VERSION__ >= 199901L
  #define NELUA_INLINE inline
#else
  #define NELUA_INLINE
#endif
#include <stdio.h>
#include <stdlib.h>
/* Macro used to import/export extern C functions. */
#ifdef __cplusplus
  #define NELUA_EXTERN extern "C"
#else
  #define NELUA_EXTERN extern
#endif
/* Macro used to generate traceback on aborts when sanitizing. */
#if defined(__clang__) && defined(__has_feature)
  #if __has_feature(undefined_behavior_sanitizer)
    #define NELUA_UBSAN_UNREACHABLE __builtin_unreachable
  #endif
#elif defined(__gnu_linux__) && defined(__GNUC__) && __GNUC__ >= 5
  NELUA_EXTERN void __ubsan_handle_builtin_unreachable(void*) __attribute__((weak));
  #define NELUA_UBSAN_UNREACHABLE() {if(&__ubsan_handle_builtin_unreachable) __builtin_unreachable();}
#endif
#ifndef NELUA_UBSAN_UNREACHABLE
  #define NELUA_UBSAN_UNREACHABLE()
#endif
/* Macro used to specify a function that never returns. */
#if __STDC_VERSION__ >= 201112L
  #define NELUA_NORETURN _Noreturn
#elif defined(__GNUC__)
  #define NELUA_NORETURN __attribute__((noreturn))
#elif defined(_MSC_VER)
  #define NELUA_NORETURN __declspec(noreturn)
#else
  #define NELUA_NORETURN
#endif
#include <string.h>
/* Macro used for branch prediction. */
#if defined(__GNUC__) || defined(__clang__)
  #define NELUA_UNLIKELY(x) __builtin_expect(x, 0)
#else
  #define NELUA_UNLIKELY(x) (x)
#endif
#include <stddef.h>
#define NELUA_NIL (nlniltype){}
/* Macro used for branch prediction. */
#if defined(__GNUC__) || defined(__clang__)
  #define NELUA_LIKELY(x) __builtin_expect(x, 1)
#else
  #define NELUA_LIKELY(x) (x)
#endif
/* Macro used to force not inlining a function. */
#ifdef __GNUC__
  #define NELUA_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
  #define NELUA_NOINLINE __declspec(noinline)
#else
  #define NELUA_NOINLINE
#endif
/* Macro used suppress sanitizer errors when the GC is scanning. */
#if defined(__has_feature)
  #if __has_feature(address_sanitizer)
    #define NELUA_GC_NO_SANITIZE __attribute__((no_sanitize_address))
  #elif __has_feature(memory_sanitizer)
    #define NELUA_GC_NO_SANITIZE __attribute__((no_sanitize_memory))
  #endif
#endif
#ifndef NELUA_GC_NO_SANITIZE
  #if defined(__SANITIZE_ADDRESS__)
    #define NELUA_GC_NO_SANITIZE __attribute__((no_sanitize_address))
  #else
    #define NELUA_GC_NO_SANITIZE
  #endif
#endif
#include <setjmp.h>
/* Macro used sign that a type punning cast may alias (related to strict aliasing). */
#ifdef __GNUC__
  #define NELUA_MAYALIAS __attribute__((may_alias))
#else
  #define NELUA_MAYALIAS
#endif
#include <math.h>
/* Infinite number constant. */
#ifdef HUGE_VALF
  #define NELUA_INFF HUGE_VALF
#else
  #define NELUA_INFF (1.0f/0.0f)
#endif
/* Infinite number constant. */
#ifdef HUGE_VAL
  #define NELUA_INF HUGE_VAL
#else
  #define NELUA_INF (1.0/0.0)
#endif
#include <time.h>
/* Include basic POSIX constants and APIs */
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || \
                        (defined(__APPLE__) && defined(__MACH__)) || \
                        defined(__HAIKU__))
  #include <unistd.h>
#endif
/* Include Windows APIs. */
#ifdef _WIN32
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
  #endif
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x600
  #endif
  #include <windows.h>
#endif
/* Determine supported high resolution time API. */
#if defined(_POSIX_TIMERS) && defined(_POSIX_MONOTONIC_CLOCK)
  #define NELUA_HAVE_POSIX_MONOTONIC_CLOCK
#elif __STDC_VERSION__ >= 201112L && defined(TIME_UTC) && !defined(__ANDROID__) && !defined(__wasm__)
  #define NELUA_HAVE_C11_TIMESPEC_GET
#elif defined(_POSIX_VERSION)
  #include <sys/time.h>
  #define NELUA_HAVE_POSIX_GETTIMEOFDAY
#endif
/* Macro used to take reference of literals. */
#define NELUA_LITERAL_REF(T, x) (&((struct{T v;}){x}.v))
#include <webgpu.h>
#include <wgpu.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>
#include <errno.h>
/* ------------------------------ DECLARATIONS ------------------------------ */
typedef struct nlmulret_nlboolean_nlint64_nlfloat64 {
  bool r1;
  int64_t r2;
  double r3;
} nlmulret_nlboolean_nlint64_nlfloat64;
typedef struct nelua_vector_float64_ nelua_vector_float64_;
typedef nelua_vector_float64_* nelua_vector_float64__ptr;
typedef nlmulret_nlboolean_nlint64_nlfloat64 (*function_5RRHk7NVNoo3zrsdP)(nelua_vector_float64__ptr, int64_t);
typedef struct nelua_span_float64_ nelua_span_float64_;
typedef double* nlfloat64_arr0_ptr;
struct nelua_span_float64_ {
  nlfloat64_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_float64_) == 16 && NELUA_ALIGNOF(nelua_span_float64_) == 8, "Nelua and C disagree on type size or align");
typedef struct nelua_GCAllocator nelua_GCAllocator;
struct nelua_GCAllocator {};
struct nelua_vector_float64_ {
  nelua_span_float64_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_float64_) == 24 && NELUA_ALIGNOF(nelua_vector_float64_) == 8, "Nelua and C disagree on type size or align");
typedef struct nlmulret_function_5RRHk7NVNoo3zrsdP_nelua_vector_float64__ptr_nlint64 {
  function_5RRHk7NVNoo3zrsdP r1;
  nelua_vector_float64__ptr r2;
  int64_t r3;
} nlmulret_function_5RRHk7NVNoo3zrsdP_nelua_vector_float64__ptr_nlint64;
static NELUA_INLINE nlmulret_function_5RRHk7NVNoo3zrsdP_nelua_vector_float64__ptr_nlint64 nelua_ipairs_1(nelua_vector_float64__ptr a);
static NELUA_INLINE nlmulret_nlboolean_nlint64_nlfloat64 nelua_ipairs_next(nelua_vector_float64__ptr a_1, int64_t k);
static NELUA_INLINE void nelua_write_stderr(const char* msg, uintptr_t len, bool flush);
static NELUA_NORETURN void nelua_abort(void);
static NELUA_NORETURN void nelua_panic_cstring(const char* s);
static NELUA_INLINE void* nelua_assert_deref(void* p);
static NELUA_INLINE uintptr_t nelua_assert_narrow_nlint64_nlusize(int64_t x);
typedef struct nelua_GCItem nelua_GCItem;
typedef nelua_GCItem* nelua_GCItem_ptr;
typedef struct nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr {
  bool r1;
  void* r2;
  nelua_GCItem_ptr r3;
} nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr;
typedef struct nelua_hashmap_iteratorT nelua_hashmap_iteratorT;
typedef nelua_hashmap_iteratorT* nelua_hashmap_iteratorT_ptr;
typedef nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr (*function_4xGnvujKcT3F2fJ4Z)(nelua_hashmap_iteratorT_ptr, void*);
typedef struct nelua_hashmap_pointer__GCItem_ nelua_hashmap_pointer__GCItem_;
typedef nelua_hashmap_pointer__GCItem_* nelua_hashmap_pointer__GCItem__ptr;
struct nelua_hashmap_iteratorT {
  nelua_hashmap_pointer__GCItem__ptr container;
  uintptr_t index;
};
NELUA_STATIC_ASSERT(sizeof(nelua_hashmap_iteratorT) == 16 && NELUA_ALIGNOF(nelua_hashmap_iteratorT) == 8, "Nelua and C disagree on type size or align");
typedef struct nelua_span_usize_ nelua_span_usize_;
typedef uintptr_t* nlusize_arr0_ptr;
struct nelua_span_usize_ {
  nlusize_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_usize_) == 16 && NELUA_ALIGNOF(nelua_span_usize_) == 8, "Nelua and C disagree on type size or align");
typedef struct nelua_span_hashmapnode_pointer__GCItem__ nelua_span_hashmapnode_pointer__GCItem__;
typedef struct nelua_hashmapnode_pointer__GCItem_ nelua_hashmapnode_pointer__GCItem_;
typedef nelua_hashmapnode_pointer__GCItem_* nelua_hashmapnode_pointer__GCItem__arr0_ptr;
struct nelua_span_hashmapnode_pointer__GCItem__ {
  nelua_hashmapnode_pointer__GCItem__arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_hashmapnode_pointer__GCItem__) == 16 && NELUA_ALIGNOF(nelua_span_hashmapnode_pointer__GCItem__) == 8, "Nelua and C disagree on type size or align");
typedef struct nelua_GeneralAllocator nelua_GeneralAllocator;
struct nelua_GeneralAllocator {};
struct nelua_hashmap_pointer__GCItem_ {
  nelua_span_usize_ buckets;
  nelua_span_hashmapnode_pointer__GCItem__ nodes;
  uintptr_t size;
  uintptr_t free_index;
  nelua_GeneralAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_hashmap_pointer__GCItem_) == 48 && NELUA_ALIGNOF(nelua_hashmap_pointer__GCItem_) == 8, "Nelua and C disagree on type size or align");
typedef void (*nelua_GCFinalizerCallback)(void*, void*);
struct nelua_GCItem {
  uintptr_t flags;
  uintptr_t size;
  void* ptr;
  nelua_GCFinalizerCallback finalizer;
  void* userdata;
};
NELUA_STATIC_ASSERT(sizeof(nelua_GCItem) == 40 && NELUA_ALIGNOF(nelua_GCItem) == 8, "Nelua and C disagree on type size or align");
struct nelua_hashmapnode_pointer__GCItem_ {
  void* key;
  nelua_GCItem value;
  bool filled;
  uintptr_t next;
};
NELUA_STATIC_ASSERT(sizeof(nelua_hashmapnode_pointer__GCItem_) == 64 && NELUA_ALIGNOF(nelua_hashmapnode_pointer__GCItem_) == 8, "Nelua and C disagree on type size or align");
typedef struct nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer {
  function_4xGnvujKcT3F2fJ4Z r1;
  nelua_hashmap_iteratorT r2;
  void* r3;
} nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer;
static NELUA_INLINE nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer nelua_mpairs_1(nelua_hashmap_pointer__GCItem__ptr a);
typedef struct entropy_scene_mesh_Mesh entropy_scene_mesh_Mesh;
typedef entropy_scene_mesh_Mesh* entropy_scene_mesh_Mesh_ptr;
typedef struct nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr {
  bool r1;
  intptr_t r2;
  entropy_scene_mesh_Mesh_ptr r3;
} nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr;
typedef struct entropy_world_Storage_Mesh_ entropy_world_Storage_Mesh_;
typedef entropy_world_Storage_Mesh_* entropy_world_Storage_Mesh__ptr;
typedef nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr (*function_cn8qNCYTz9afPmWb)(entropy_world_Storage_Mesh__ptr, intptr_t);
typedef struct nelua_vector_Mesh_ nelua_vector_Mesh_;
typedef struct nelua_span_Mesh_ nelua_span_Mesh_;
typedef entropy_scene_mesh_Mesh* entropy_scene_mesh_Mesh_arr0_ptr;
struct nelua_span_Mesh_ {
  entropy_scene_mesh_Mesh_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_Mesh_) == 16 && NELUA_ALIGNOF(nelua_span_Mesh_) == 8, "Nelua and C disagree on type size or align");
struct nelua_vector_Mesh_ {
  nelua_span_Mesh_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_Mesh_) == 24 && NELUA_ALIGNOF(nelua_vector_Mesh_) == 8, "Nelua and C disagree on type size or align");
typedef struct nelua_vector_uint16_ nelua_vector_uint16_;
typedef struct nelua_span_uint16_ nelua_span_uint16_;
typedef uint16_t* nluint16_arr0_ptr;
struct nelua_span_uint16_ {
  nluint16_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_uint16_) == 16 && NELUA_ALIGNOF(nelua_span_uint16_) == 8, "Nelua and C disagree on type size or align");
struct nelua_vector_uint16_ {
  nelua_span_uint16_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_uint16_) == 24 && NELUA_ALIGNOF(nelua_vector_uint16_) == 8, "Nelua and C disagree on type size or align");
typedef struct nelua_vector_usize_ nelua_vector_usize_;
struct nelua_vector_usize_ {
  nelua_span_usize_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_usize_) == 24 && NELUA_ALIGNOF(nelua_vector_usize_) == 8, "Nelua and C disagree on type size or align");
struct entropy_world_Storage_Mesh_ {
  nelua_vector_Mesh_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_Mesh_) == 72 && NELUA_ALIGNOF(entropy_world_Storage_Mesh_) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_math_mat4_Mat4 entropy_math_mat4_Mat4;
typedef struct entropy_math_vec4_Vec4 entropy_math_vec4_Vec4;
struct entropy_math_vec4_Vec4 {
  float x;
  float y;
  float z;
  float w;
};
NELUA_STATIC_ASSERT(sizeof(entropy_math_vec4_Vec4) == 16 && NELUA_ALIGNOF(entropy_math_vec4_Vec4) == 4, "Nelua and C disagree on type size or align");
struct entropy_math_mat4_Mat4 {
  entropy_math_vec4_Vec4 x;
  entropy_math_vec4_Vec4 y;
  entropy_math_vec4_Vec4 z;
  entropy_math_vec4_Vec4 w;
};
NELUA_STATIC_ASSERT(sizeof(entropy_math_mat4_Mat4) == 64 && NELUA_ALIGNOF(entropy_math_mat4_Mat4) == 4, "Nelua and C disagree on type size or align");
typedef struct nelua_vector_Vertex_ nelua_vector_Vertex_;
typedef struct nelua_span_Vertex_ nelua_span_Vertex_;
typedef struct entropy_scene_mesh_Vertex entropy_scene_mesh_Vertex;
typedef entropy_scene_mesh_Vertex* entropy_scene_mesh_Vertex_arr0_ptr;
struct nelua_span_Vertex_ {
  entropy_scene_mesh_Vertex_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_Vertex_) == 16 && NELUA_ALIGNOF(nelua_span_Vertex_) == 8, "Nelua and C disagree on type size or align");
struct nelua_vector_Vertex_ {
  nelua_span_Vertex_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_Vertex_) == 24 && NELUA_ALIGNOF(nelua_vector_Vertex_) == 8, "Nelua and C disagree on type size or align");
typedef struct nelua_vector_uint32_ nelua_vector_uint32_;
typedef struct nelua_span_uint32_ nelua_span_uint32_;
typedef uint32_t* nluint32_arr0_ptr;
struct nelua_span_uint32_ {
  nluint32_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_uint32_) == 16 && NELUA_ALIGNOF(nelua_span_uint32_) == 8, "Nelua and C disagree on type size or align");
struct nelua_vector_uint32_ {
  nelua_span_uint32_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_uint32_) == 24 && NELUA_ALIGNOF(nelua_vector_uint32_) == 8, "Nelua and C disagree on type size or align");
typedef struct WGPUBufferImpl WGPUBufferImpl;
typedef WGPUBufferImpl* WGPUBufferImpl_ptr;
struct entropy_scene_mesh_Mesh {
  entropy_math_mat4_Mat4 transform;
  nelua_vector_Vertex_ vertices;
  nelua_vector_uint32_ indices;
  WGPUBufferImpl_ptr vertex_buffer;
  WGPUBufferImpl_ptr index_buffer;
};
NELUA_STATIC_ASSERT(sizeof(entropy_scene_mesh_Mesh) == 128 && NELUA_ALIGNOF(entropy_scene_mesh_Mesh) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_math_vec3_Vec3 entropy_math_vec3_Vec3;
struct entropy_math_vec3_Vec3 {
  float x;
  float y;
  float z;
};
NELUA_STATIC_ASSERT(sizeof(entropy_math_vec3_Vec3) == 12 && NELUA_ALIGNOF(entropy_math_vec3_Vec3) == 4, "Nelua and C disagree on type size or align");
typedef struct entropy_math_vec2_Vec2 entropy_math_vec2_Vec2;
struct entropy_math_vec2_Vec2 {
  float x;
  float y;
};
NELUA_STATIC_ASSERT(sizeof(entropy_math_vec2_Vec2) == 8 && NELUA_ALIGNOF(entropy_math_vec2_Vec2) == 4, "Nelua and C disagree on type size or align");
struct entropy_scene_mesh_Vertex {
  entropy_math_vec3_Vec3 pos;
  entropy_math_vec4_Vec4 col;
  entropy_math_vec2_Vec2 uv;
};
NELUA_STATIC_ASSERT(sizeof(entropy_scene_mesh_Vertex) == 36 && NELUA_ALIGNOF(entropy_scene_mesh_Vertex) == 4, "Nelua and C disagree on type size or align");
typedef struct nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize {
  function_cn8qNCYTz9afPmWb r1;
  entropy_world_Storage_Mesh__ptr r2;
  intptr_t r3;
} nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize;
static NELUA_INLINE nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize nelua_mpairs_2(entropy_world_Storage_Mesh__ptr a);
typedef struct main_Entity main_Entity;
typedef main_Entity* main_Entity_ptr;
typedef struct nlmulret_nlboolean_nlisize_main_Entity_ptr {
  bool r1;
  intptr_t r2;
  main_Entity_ptr r3;
} nlmulret_nlboolean_nlisize_main_Entity_ptr;
typedef struct entropy_world_Storage_Entity_ entropy_world_Storage_Entity_;
typedef entropy_world_Storage_Entity_* entropy_world_Storage_Entity__ptr;
typedef nlmulret_nlboolean_nlisize_main_Entity_ptr (*function_22cTQHv4wXQKFZ1xf)(entropy_world_Storage_Entity__ptr, intptr_t);
typedef struct nelua_vector_Entity_ nelua_vector_Entity_;
typedef struct nelua_span_Entity_ nelua_span_Entity_;
typedef main_Entity* main_Entity_arr0_ptr;
struct nelua_span_Entity_ {
  main_Entity_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_Entity_) == 16 && NELUA_ALIGNOF(nelua_span_Entity_) == 8, "Nelua and C disagree on type size or align");
struct nelua_vector_Entity_ {
  nelua_span_Entity_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_Entity_) == 24 && NELUA_ALIGNOF(nelua_vector_Entity_) == 8, "Nelua and C disagree on type size or align");
struct entropy_world_Storage_Entity_ {
  nelua_vector_Entity_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_Entity_) == 72 && NELUA_ALIGNOF(entropy_world_Storage_Entity_) == 8, "Nelua and C disagree on type size or align");
struct main_Entity {
  uintptr_t pos;
  uintptr_t vel;
};
NELUA_STATIC_ASSERT(sizeof(main_Entity) == 16 && NELUA_ALIGNOF(main_Entity) == 8, "Nelua and C disagree on type size or align");
typedef struct nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize {
  function_22cTQHv4wXQKFZ1xf r1;
  entropy_world_Storage_Entity__ptr r2;
  intptr_t r3;
} nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize;
static NELUA_INLINE nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize nelua_mpairs_3(entropy_world_Storage_Entity__ptr a);
static NELUA_INLINE void nelua_memory_copy(void* dest, void* src, uintptr_t n);
typedef struct nlstring nlstring;
typedef uint8_t* nluint8_arr0_ptr;
struct nlstring {
  nluint8_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nlstring) == 16 && NELUA_ALIGNOF(nlstring) == 8, "Nelua and C disagree on type size or align");
static void nelua_assert_line_1(bool cond, nlstring msg);
static NELUA_INLINE void nelua_memory_zero(void* dest, uintptr_t n);
static void nelua_assert_line_2(bool cond, nlstring msg);
static NELUA_INLINE int32_t nelua_memory_compare(void* a, void* b, uintptr_t n);
static void nelua_assert_line_3(bool cond, nlstring msg);
static NELUA_INLINE bool nelua_memory_equals(void* a, void* b, uintptr_t n);
static void nelua_assert_line_4(bool cond, nlstring msg);
static NELUA_INLINE void* nelua_memory_scan(void* src, uint8_t x, uintptr_t n);
static void nelua_assert_line_5(bool cond, nlstring msg);
static void* nelua_memory_find(void* haystack, uintptr_t haystacksize, void* needle, uintptr_t needlesize);
static void nelua_assert_line_6(bool cond, nlstring msg);
typedef uint8_t* nluint8_ptr;
typedef struct nelua_span_uint8_ nelua_span_uint8_;
struct nelua_span_uint8_ {
  nluint8_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_uint8_) == 16 && NELUA_ALIGNOF(nelua_span_uint8_) == 8, "Nelua and C disagree on type size or align");
static NELUA_INLINE bool nelua_span_uint8__empty(nelua_span_uint8_ self);
static NELUA_INLINE nluint8_ptr nelua_span_uint8____atindex(nelua_span_uint8_ self, uintptr_t i);
static void nelua_assert_line_7(bool cond, nlstring msg);
typedef void** nlpointer_ptr;
typedef struct nelua_span_pointer_ nelua_span_pointer_;
typedef void** nlpointer_arr0_ptr;
struct nelua_span_pointer_ {
  nlpointer_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_pointer_) == 16 && NELUA_ALIGNOF(nelua_span_pointer_) == 8, "Nelua and C disagree on type size or align");
static NELUA_INLINE nlpointer_ptr nelua_span_pointer____atindex(nelua_span_pointer_ self, uintptr_t i);
static void nelua_assert_line_8(bool cond, nlstring msg);
typedef struct nelua_GCMarkRange nelua_GCMarkRange;
typedef nelua_GCMarkRange* nelua_GCMarkRange_ptr;
struct nelua_GCMarkRange {
  uintptr_t low;
  uintptr_t high;
};
NELUA_STATIC_ASSERT(sizeof(nelua_GCMarkRange) == 16 && NELUA_ALIGNOF(nelua_GCMarkRange) == 8, "Nelua and C disagree on type size or align");
typedef struct nelua_span_GCMarkRange_ nelua_span_GCMarkRange_;
typedef nelua_GCMarkRange* nelua_GCMarkRange_arr0_ptr;
struct nelua_span_GCMarkRange_ {
  nelua_GCMarkRange_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_GCMarkRange_) == 16 && NELUA_ALIGNOF(nelua_span_GCMarkRange_) == 8, "Nelua and C disagree on type size or align");
static NELUA_INLINE nelua_GCMarkRange_ptr nelua_span_GCMarkRange____atindex(nelua_span_GCMarkRange_ self, uintptr_t i);
static void nelua_assert_line_9(bool cond, nlstring msg);
typedef uintptr_t* nlusize_ptr;
static NELUA_INLINE nlusize_ptr nelua_span_usize____atindex(nelua_span_usize_ self, uintptr_t i);
static void nelua_assert_line_10(bool cond, nlstring msg);
typedef nelua_hashmapnode_pointer__GCItem_* nelua_hashmapnode_pointer__GCItem__ptr;
static NELUA_INLINE nelua_hashmapnode_pointer__GCItem__ptr nelua_span_hashmapnode_pointer__GCItem_____atindex(nelua_span_hashmapnode_pointer__GCItem__ self, uintptr_t i);
static void nelua_assert_line_11(bool cond, nlstring msg);
typedef nlstring* nlstring_ptr;
typedef struct nelua_span_string_ nelua_span_string_;
typedef nlstring* nlstring_arr0_ptr;
struct nelua_span_string_ {
  nlstring_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_string_) == 16 && NELUA_ALIGNOF(nelua_span_string_) == 8, "Nelua and C disagree on type size or align");
static NELUA_INLINE nlstring_ptr nelua_span_string____atindex(nelua_span_string_ self, uintptr_t i);
static void nelua_assert_line_12(bool cond, nlstring msg);
typedef double* nlfloat64_ptr;
static NELUA_INLINE nlfloat64_ptr nelua_span_float64____atindex(nelua_span_float64_ self, uintptr_t i);
static void nelua_assert_line_13(bool cond, nlstring msg);
typedef entropy_scene_mesh_Vertex* entropy_scene_mesh_Vertex_ptr;
static NELUA_INLINE entropy_scene_mesh_Vertex_ptr nelua_span_Vertex____atindex(nelua_span_Vertex_ self, uintptr_t i);
static void nelua_assert_line_14(bool cond, nlstring msg);
typedef uint32_t* nluint32_ptr;
static NELUA_INLINE nluint32_ptr nelua_span_uint32____atindex(nelua_span_uint32_ self, uintptr_t i);
static void nelua_assert_line_15(bool cond, nlstring msg);
typedef entropy_math_vec2_Vec2* entropy_math_vec2_Vec2_ptr;
typedef struct nelua_span_Vec2_ nelua_span_Vec2_;
typedef entropy_math_vec2_Vec2* entropy_math_vec2_Vec2_arr0_ptr;
struct nelua_span_Vec2_ {
  entropy_math_vec2_Vec2_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_Vec2_) == 16 && NELUA_ALIGNOF(nelua_span_Vec2_) == 8, "Nelua and C disagree on type size or align");
static NELUA_INLINE entropy_math_vec2_Vec2_ptr nelua_span_Vec2____atindex(nelua_span_Vec2_ self, uintptr_t i);
static void nelua_assert_line_16(bool cond, nlstring msg);
typedef uint16_t* nluint16_ptr;
static NELUA_INLINE nluint16_ptr nelua_span_uint16____atindex(nelua_span_uint16_ self, uintptr_t i);
static void nelua_assert_line_17(bool cond, nlstring msg);
static NELUA_INLINE main_Entity_ptr nelua_span_Entity____atindex(nelua_span_Entity_ self, uintptr_t i);
static void nelua_assert_line_18(bool cond, nlstring msg);
static NELUA_INLINE entropy_scene_mesh_Mesh_ptr nelua_span_Mesh____atindex(nelua_span_Mesh_ self, uintptr_t i);
static void nelua_assert_line_19(bool cond, nlstring msg);
typedef struct entropy_scene_camera_Camera entropy_scene_camera_Camera;
typedef entropy_scene_camera_Camera* entropy_scene_camera_Camera_ptr;
struct entropy_scene_camera_Camera {
  entropy_math_vec3_Vec3 pos;
  entropy_math_vec3_Vec3 rot;
  float fov;
  float z_near;
  float z_far;
};
NELUA_STATIC_ASSERT(sizeof(entropy_scene_camera_Camera) == 36 && NELUA_ALIGNOF(entropy_scene_camera_Camera) == 4, "Nelua and C disagree on type size or align");
typedef struct nelua_span_Camera_ nelua_span_Camera_;
typedef entropy_scene_camera_Camera* entropy_scene_camera_Camera_arr0_ptr;
struct nelua_span_Camera_ {
  entropy_scene_camera_Camera_arr0_ptr data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_span_Camera_) == 16 && NELUA_ALIGNOF(nelua_span_Camera_) == 8, "Nelua and C disagree on type size or align");
static NELUA_INLINE entropy_scene_camera_Camera_ptr nelua_span_Camera____atindex(nelua_span_Camera_ self, uintptr_t i);
static void nelua_assert_line_20(bool cond, nlstring msg);
typedef struct nlniltype {} nlniltype;
typedef struct nlniltype nltype;
static NELUA_INLINE void nelua_memory_spanset_1(nelua_span_usize_ dest, uintptr_t x);
typedef struct nelua_sequence_string_ nelua_sequence_string_;
typedef nelua_sequence_string_* nelua_sequence_string__ptr;
typedef struct nelua_sequenceimpl_string_ nelua_sequenceimpl_string_;
typedef nelua_sequenceimpl_string_* nelua_sequenceimpl_string__ptr;
struct nelua_sequence_string_ {
  nelua_sequenceimpl_string__ptr impl;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_sequence_string_) == 8 && NELUA_ALIGNOF(nelua_sequence_string_) == 8, "Nelua and C disagree on type size or align");
struct nelua_sequenceimpl_string_ {
  nelua_span_string_ data;
  uintptr_t size;
};
NELUA_STATIC_ASSERT(sizeof(nelua_sequenceimpl_string_) == 24 && NELUA_ALIGNOF(nelua_sequenceimpl_string_) == 8, "Nelua and C disagree on type size or align");
static void nelua_sequence_string___init(nelua_sequence_string__ptr self);
static void nelua_sequence_string__reserve(nelua_sequence_string__ptr self, uintptr_t n);
static void nelua_sequence_string__resize(nelua_sequence_string__ptr self, uintptr_t n);
static NELUA_NOINLINE void nelua_sequenceT_grow(nelua_sequence_string__ptr self);
static void nelua_assert_line_21(bool cond, nlstring msg);
static NELUA_INLINE nlstring_ptr nelua_sequence_string____atindex(nelua_sequence_string__ptr self, uintptr_t pos);
static void nelua_assert_line_22(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_sequence_string____len(nelua_sequence_string__ptr self);
static nelua_GeneralAllocator nelua_general_allocator;
typedef nelua_GeneralAllocator* nelua_GeneralAllocator_ptr;
static NELUA_INLINE void* nelua_GeneralAllocator_alloc_1(nelua_GeneralAllocator_ptr self, uintptr_t size, uintptr_t flags);
static NELUA_INLINE void* nelua_GeneralAllocator_alloc_2(nelua_GeneralAllocator_ptr self, uintptr_t size, nlniltype flags);
static NELUA_INLINE void* nelua_GeneralAllocator_alloc0_1(nelua_GeneralAllocator_ptr self, uintptr_t size, nlniltype flags);
static NELUA_INLINE void* nelua_GeneralAllocator_alloc0_2(nelua_GeneralAllocator_ptr self, uintptr_t size, uintptr_t flags);
static NELUA_INLINE void nelua_GeneralAllocator_dealloc(nelua_GeneralAllocator_ptr self, void* p);
static NELUA_INLINE void* nelua_GeneralAllocator_realloc(nelua_GeneralAllocator_ptr self, void* p, uintptr_t newsize, uintptr_t oldsize);
static void* nelua_GeneralAllocator_realloc0(nelua_GeneralAllocator_ptr self, void* p, uintptr_t newsize, uintptr_t oldsize);
static nelua_span_pointer_ nelua_GeneralAllocator_spanalloc_1(nelua_GeneralAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags);
static nelua_span_GCMarkRange_ nelua_GeneralAllocator_spanalloc_2(nelua_GeneralAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags);
static nelua_span_usize_ nelua_GeneralAllocator_spanalloc_3(nelua_GeneralAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags);
static nelua_span_hashmapnode_pointer__GCItem__ nelua_GeneralAllocator_spanalloc0_1(nelua_GeneralAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags);
static void nelua_GeneralAllocator_spandealloc_1(nelua_GeneralAllocator_ptr self, nelua_span_pointer_ s);
static void nelua_GeneralAllocator_spandealloc_2(nelua_GeneralAllocator_ptr self, nelua_span_GCMarkRange_ s);
static void nelua_GeneralAllocator_spandealloc_3(nelua_GeneralAllocator_ptr self, nelua_span_usize_ s);
static void nelua_GeneralAllocator_spandealloc_4(nelua_GeneralAllocator_ptr self, nelua_span_hashmapnode_pointer__GCItem__ s);
static nelua_span_pointer_ nelua_GeneralAllocator_spanrealloc_1(nelua_GeneralAllocator_ptr self, nelua_span_pointer_ s, uintptr_t size);
static nelua_span_GCMarkRange_ nelua_GeneralAllocator_spanrealloc_2(nelua_GeneralAllocator_ptr self, nelua_span_GCMarkRange_ s, uintptr_t size);
static nelua_span_usize_ nelua_GeneralAllocator_spanrealloc_3(nelua_GeneralAllocator_ptr self, nelua_span_usize_ s, uintptr_t size);
static nelua_span_pointer_ nelua_GeneralAllocator_xspanrealloc_1(nelua_GeneralAllocator_ptr self, nelua_span_pointer_ s, uintptr_t size);
static NELUA_NORETURN void nelua_panic_string(nlstring s);
static nelua_span_GCMarkRange_ nelua_GeneralAllocator_xspanrealloc_2(nelua_GeneralAllocator_ptr self, nelua_span_GCMarkRange_ s, uintptr_t size);
static nelua_span_usize_ nelua_GeneralAllocator_xspanrealloc_3(nelua_GeneralAllocator_ptr self, nelua_span_usize_ s, uintptr_t size);
static nelua_span_hashmapnode_pointer__GCItem__ nelua_GeneralAllocator_spanrealloc0_1(nelua_GeneralAllocator_ptr self, nelua_span_hashmapnode_pointer__GCItem__ s, uintptr_t size);
static nelua_span_hashmapnode_pointer__GCItem__ nelua_GeneralAllocator_xspanrealloc0_1(nelua_GeneralAllocator_ptr self, nelua_span_hashmapnode_pointer__GCItem__ s, uintptr_t size);
static uintptr_t nelua_hash_hash_1(void* v);
static NELUA_INLINE uintptr_t nelua_ceilidiv(uintptr_t x, uintptr_t y);
static NELUA_INLINE uintptr_t nelua_hashmod(uintptr_t h, uintptr_t n);
static NELUA_INLINE uintptr_t nelua_roundpow2(uintptr_t n);
static void nelua_hashmap_pointer__GCItem__destroy(nelua_hashmap_pointer__GCItem__ptr self);
typedef struct nlmulret_nlusize_nlusize_nlusize {
  uintptr_t r1;
  uintptr_t r2;
  uintptr_t r3;
} nlmulret_nlusize_nlusize_nlusize;
static NELUA_INLINE nlmulret_nlusize_nlusize_nlusize nelua_hashmap_pointer__GCItem___find(nelua_hashmap_pointer__GCItem__ptr self, void* key);
static NELUA_NOINLINE void nelua_hashmap_pointer__GCItem__rehash(nelua_hashmap_pointer__GCItem__ptr self, uintptr_t bucket_count);
static void nelua_assert_line_23(bool cond);
static uintptr_t nelua_hashmap_pointer__GCItem___at(nelua_hashmap_pointer__GCItem__ptr self, void* key);
static void nelua_assert_line_24(bool cond, nlstring msg);
static nelua_GCItem_ptr nelua_hashmap_pointer__GCItem____atindex(nelua_hashmap_pointer__GCItem__ptr self, void* key);
static nelua_GCItem_ptr nelua_hashmap_pointer__GCItem__peek(nelua_hashmap_pointer__GCItem__ptr self, void* key);
static nelua_GCItem nelua_hashmap_pointer__GCItem__remove(nelua_hashmap_pointer__GCItem__ptr self, void* key);
static uintptr_t nelua_hashmap_pointer__GCItem__bucketcount(nelua_hashmap_pointer__GCItem__ptr self);
static NELUA_INLINE nelua_hashmapnode_pointer__GCItem__ptr nelua_hashmap_iteratorT__next_node(nelua_hashmap_iteratorT_ptr self, void* key);
static NELUA_INLINE nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr nelua_hashmap_iteratorT_mnext(nelua_hashmap_iteratorT_ptr self, void* key);
static NELUA_INLINE nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer nelua_hashmap_pointer__GCItem____mpairs(nelua_hashmap_pointer__GCItem__ptr self);
typedef struct nelua_vector_pointer_ nelua_vector_pointer_;
typedef nelua_vector_pointer_* nelua_vector_pointer__ptr;
struct nelua_vector_pointer_ {
  nelua_span_pointer_ data;
  uintptr_t size;
  nelua_GeneralAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_pointer_) == 24 && NELUA_ALIGNOF(nelua_vector_pointer_) == 8, "Nelua and C disagree on type size or align");
static void nelua_vector_pointer__clear(nelua_vector_pointer__ptr self);
static void nelua_vector_pointer__destroy(nelua_vector_pointer__ptr self);
static NELUA_NOINLINE void nelua_vectorT_grow(nelua_vector_pointer__ptr self);
static void nelua_assert_line_25(bool cond, nlstring msg);
static void nelua_vector_pointer__push(nelua_vector_pointer__ptr self, void* v);
static NELUA_INLINE nlpointer_ptr nelua_vector_pointer____atindex(nelua_vector_pointer__ptr self, uintptr_t pos);
static void nelua_assert_line_26(bool cond, nlstring msg);
typedef struct nelua_vector_GCMarkRange_ nelua_vector_GCMarkRange_;
typedef nelua_vector_GCMarkRange_* nelua_vector_GCMarkRange__ptr;
struct nelua_vector_GCMarkRange_ {
  nelua_span_GCMarkRange_ data;
  uintptr_t size;
  nelua_GeneralAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_GCMarkRange_) == 24 && NELUA_ALIGNOF(nelua_vector_GCMarkRange_) == 8, "Nelua and C disagree on type size or align");
static void nelua_vector_GCMarkRange__destroy(nelua_vector_GCMarkRange__ptr self);
static NELUA_NOINLINE void nelua_vectorT_grow_1(nelua_vector_GCMarkRange__ptr self);
static void nelua_assert_line_27(bool cond, nlstring msg);
static void nelua_vector_GCMarkRange__push(nelua_vector_GCMarkRange__ptr self, nelua_GCMarkRange v);
static nelua_GCMarkRange nelua_vector_GCMarkRange__pop(nelua_vector_GCMarkRange__ptr self);
static void nelua_assert_line_28(bool cond, nlstring msg);
static void nelua_vector_float64__clear(nelua_vector_float64__ptr self);
static NELUA_NOINLINE void nelua_vectorT_grow_2(nelua_vector_float64__ptr self);
static void nelua_assert_line_29(bool cond, nlstring msg);
static void nelua_vector_float64__push(nelua_vector_float64__ptr self, double v);
static NELUA_INLINE nlfloat64_ptr nelua_vector_float64____atindex(nelua_vector_float64__ptr self, uintptr_t pos);
static void nelua_assert_line_30(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_float64____len(nelua_vector_float64__ptr self);
typedef nelua_vector_Vertex_* nelua_vector_Vertex__ptr;
static NELUA_NOINLINE void nelua_vectorT_grow_3(nelua_vector_Vertex__ptr self);
static void nelua_assert_line_31(bool cond, nlstring msg);
static void nelua_vector_Vertex__push(nelua_vector_Vertex__ptr self, entropy_scene_mesh_Vertex v);
static NELUA_INLINE entropy_scene_mesh_Vertex_ptr nelua_vector_Vertex____atindex(nelua_vector_Vertex__ptr self, uintptr_t pos);
static void nelua_assert_line_32(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_Vertex____len(nelua_vector_Vertex__ptr self);
typedef nelua_vector_uint32_* nelua_vector_uint32__ptr;
static NELUA_NOINLINE void nelua_vectorT_grow_4(nelua_vector_uint32__ptr self);
static void nelua_assert_line_33(bool cond, nlstring msg);
static void nelua_vector_uint32__push(nelua_vector_uint32__ptr self, uint32_t v);
static NELUA_INLINE nluint32_ptr nelua_vector_uint32____atindex(nelua_vector_uint32__ptr self, uintptr_t pos);
static void nelua_assert_line_34(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_uint32____len(nelua_vector_uint32__ptr self);
typedef struct nelua_vector_Vec2_ nelua_vector_Vec2_;
typedef nelua_vector_Vec2_* nelua_vector_Vec2__ptr;
struct nelua_vector_Vec2_ {
  nelua_span_Vec2_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_Vec2_) == 24 && NELUA_ALIGNOF(nelua_vector_Vec2_) == 8, "Nelua and C disagree on type size or align");
static void nelua_vector_Vec2__reserve(nelua_vector_Vec2__ptr self, uintptr_t n);
static NELUA_NOINLINE void nelua_vectorT_grow_5(nelua_vector_Vec2__ptr self);
static void nelua_assert_line_35(bool cond, nlstring msg);
static void nelua_vector_Vec2__push(nelua_vector_Vec2__ptr self, entropy_math_vec2_Vec2 v);
static NELUA_INLINE intptr_t nelua_vector_Vec2__capacity(nelua_vector_Vec2__ptr self);
static NELUA_INLINE entropy_math_vec2_Vec2_ptr nelua_vector_Vec2____atindex(nelua_vector_Vec2__ptr self, uintptr_t pos);
static void nelua_assert_line_36(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_Vec2____len(nelua_vector_Vec2__ptr self);
typedef nelua_vector_uint16_* nelua_vector_uint16__ptr;
static void nelua_vector_uint16__reserve(nelua_vector_uint16__ptr self, uintptr_t n);
static NELUA_NOINLINE void nelua_vectorT_grow_6(nelua_vector_uint16__ptr self);
static void nelua_assert_line_37(bool cond, nlstring msg);
static void nelua_vector_uint16__push(nelua_vector_uint16__ptr self, uint16_t v);
static NELUA_INLINE nluint16_ptr nelua_vector_uint16____atindex(nelua_vector_uint16__ptr self, uintptr_t pos);
static void nelua_assert_line_38(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_uint16____len(nelua_vector_uint16__ptr self);
typedef nelua_vector_usize_* nelua_vector_usize__ptr;
static uintptr_t nelua_vector_usize__pop(nelua_vector_usize__ptr self);
static void nelua_assert_line_39(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_usize____len(nelua_vector_usize__ptr self);
typedef nelua_vector_Entity_* nelua_vector_Entity__ptr;
static void nelua_vector_Entity__reserve(nelua_vector_Entity__ptr self, uintptr_t n);
static NELUA_NOINLINE void nelua_vectorT_grow_8(nelua_vector_Entity__ptr self);
static void nelua_assert_line_40(bool cond, nlstring msg);
static void nelua_vector_Entity__push(nelua_vector_Entity__ptr self, main_Entity v);
static NELUA_INLINE intptr_t nelua_vector_Entity__capacity(nelua_vector_Entity__ptr self);
static NELUA_INLINE main_Entity_ptr nelua_vector_Entity____atindex(nelua_vector_Entity__ptr self, uintptr_t pos);
static void nelua_assert_line_41(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_Entity____len(nelua_vector_Entity__ptr self);
typedef nelua_vector_Mesh_* nelua_vector_Mesh__ptr;
static NELUA_NOINLINE void nelua_vectorT_grow_9(nelua_vector_Mesh__ptr self);
static void nelua_assert_line_42(bool cond, nlstring msg);
static void nelua_vector_Mesh__push(nelua_vector_Mesh__ptr self, entropy_scene_mesh_Mesh v);
static NELUA_INLINE entropy_scene_mesh_Mesh_ptr nelua_vector_Mesh____atindex(nelua_vector_Mesh__ptr self, uintptr_t pos);
static void nelua_assert_line_43(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_Mesh____len(nelua_vector_Mesh__ptr self);
typedef struct nelua_vector_Camera_ nelua_vector_Camera_;
typedef nelua_vector_Camera_* nelua_vector_Camera__ptr;
struct nelua_vector_Camera_ {
  nelua_span_Camera_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_vector_Camera_) == 24 && NELUA_ALIGNOF(nelua_vector_Camera_) == 8, "Nelua and C disagree on type size or align");
static NELUA_NOINLINE void nelua_vectorT_grow_10(nelua_vector_Camera__ptr self);
static void nelua_assert_line_44(bool cond, nlstring msg);
static void nelua_vector_Camera__push(nelua_vector_Camera__ptr self, entropy_scene_camera_Camera v);
static NELUA_INLINE entropy_scene_camera_Camera_ptr nelua_vector_Camera____atindex(nelua_vector_Camera__ptr self, uintptr_t pos);
static void nelua_assert_line_45(bool cond, nlstring msg);
static NELUA_INLINE intptr_t nelua_vector_Camera____len(nelua_vector_Camera__ptr self);
static NELUA_INLINE bool nelua_hasflag(uintptr_t flags, uintptr_t flag);
static NELUA_INLINE uintptr_t nelua_align_forward(uintptr_t addr, uintptr_t align);
static NELUA_INLINE bool nelua_GCItem_ismarked(nelua_GCItem_ptr self);
typedef struct nelua_GC nelua_GC;
struct nelua_GC {
  bool running;
  bool collecting;
  uintptr_t pause;
  uintptr_t membytes;
  uintptr_t lastmembytes;
  uintptr_t minaddr;
  uintptr_t maxaddr;
  uintptr_t stacktop;
  uintptr_t stackbottom;
  nelua_vector_pointer_ frees;
  nelua_vector_GCMarkRange_ markranges;
  nelua_hashmap_pointer__GCItem_ items;
};
NELUA_STATIC_ASSERT(sizeof(nelua_GC) == 160 && NELUA_ALIGNOF(nelua_GC) == 8, "Nelua and C disagree on type size or align");
static nelua_GC nelua_gc;
typedef nelua_GC* nelua_GC_ptr;
static void nelua_GC_unregister_1(nelua_GC_ptr self, void* ptr, bool finalize);
static void nelua_assert_line_46(bool cond, nlstring msg);
static NELUA_NOINLINE NELUA_GC_NO_SANITIZE void nelua_GC_markptrs(nelua_GC_ptr self, uintptr_t low, uintptr_t high);
static NELUA_NOINLINE void nelua_GC_markptr(nelua_GC_ptr self, void* ptr);
static NELUA_NOINLINE void nelua_GC_unmarkall(nelua_GC_ptr self);
static NELUA_NOINLINE void nelua_GC_markroot(nelua_GC_ptr self);
static NELUA_NOINLINE void nelua_GC_markstack(nelua_GC_ptr self);
typedef union nelua_RegsBuf nelua_RegsBuf;
union nelua_RegsBuf {
  jmp_buf regs;
  void* firstreg;
};
static void nelua_GC_mark(nelua_GC_ptr self);
typedef void (*function_mysnywycqLNjnvNk)(nelua_GC_ptr);
static NELUA_NOINLINE void nelua_GC_sweep(nelua_GC_ptr self);
static void nelua_assert_line_47(bool cond, nlstring msg);
static void nelua_assert_line_48(bool cond, nlstring msg);
static NELUA_NOINLINE void nelua_GC_collect(nelua_GC_ptr self);
static void nelua_GC_registerroots(nelua_GC_ptr self);
typedef void (*function_3nQBPDMn8AvVWYLJQ)(void*, void*);
static bool nelua_GC_step(nelua_GC_ptr self);
static void nelua_GC_register(nelua_GC_ptr self, void* ptr, uintptr_t size, uintptr_t flags, function_3nQBPDMn8AvVWYLJQ finalizer, void* userdata);
static void nelua_assert_line_49(bool cond, nlstring msg);
static void nelua_GC_reregister(nelua_GC_ptr self, void* oldptr, void* newptr, uintptr_t newsize);
static void nelua_assert_line_50(bool cond, nlstring msg);
static void nelua_assert_line_51(bool cond, nlstring msg);
static void nelua_assert_line_52(bool cond, nlstring msg);
static void nelua_GC_restart(nelua_GC_ptr self);
static NELUA_NOINLINE void nelua_GC_init(nelua_GC_ptr self, void* stack);
static NELUA_NOINLINE void nelua_GC_destroy(nelua_GC_ptr self);
typedef char** nlcstring_ptr;
int main(int argc, nlcstring_ptr argv);
typedef int (*function_3eqvaxExYq7cCkwLH)(int, nlcstring_ptr);
static nelua_GCAllocator nelua_gc_allocator;
typedef nelua_GCAllocator* nelua_GCAllocator_ptr;
static NELUA_NOINLINE void* nelua_GCAllocator_alloc_1(nelua_GCAllocator_ptr self, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static NELUA_NOINLINE void* nelua_GCAllocator_alloc_2(nelua_GCAllocator_ptr self, uintptr_t size, nlniltype flags, nelua_GCFinalizerCallback finalizer, void* userdata);
static NELUA_NOINLINE void* nelua_GCAllocator_alloc_3(nelua_GCAllocator_ptr self, uintptr_t size, uintptr_t flags, nelua_GCFinalizerCallback finalizer, void* userdata);
static NELUA_NOINLINE void* nelua_GCAllocator_alloc0_1(nelua_GCAllocator_ptr self, uintptr_t size, nlniltype flags, nelua_GCFinalizerCallback finalizer, void* userdata);
static NELUA_NOINLINE void* nelua_GCAllocator_alloc0_2(nelua_GCAllocator_ptr self, uintptr_t size, uintptr_t flags, nelua_GCFinalizerCallback finalizer, void* userdata);
static NELUA_NOINLINE void nelua_GCAllocator_dealloc(nelua_GCAllocator_ptr self, void* ptr);
static NELUA_NOINLINE void* nelua_GCAllocator_realloc(nelua_GCAllocator_ptr self, void* ptr, uintptr_t newsize, uintptr_t oldsize);
static nelua_span_string_ nelua_GCAllocator_spanalloc_1(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_float64_ nelua_GCAllocator_spanalloc_2(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_Vertex_ nelua_GCAllocator_spanalloc_3(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_uint32_ nelua_GCAllocator_spanalloc_4(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_uint8_ nelua_GCAllocator_spanalloc_5(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_Vec2_ nelua_GCAllocator_spanalloc_6(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_uint16_ nelua_GCAllocator_spanalloc_7(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_Entity_ nelua_GCAllocator_spanalloc_9(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_Mesh_ nelua_GCAllocator_spanalloc_10(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_Camera_ nelua_GCAllocator_spanalloc_11(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static nelua_span_uint8_ nelua_GCAllocator_spanalloc0_1(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata);
static NELUA_NOINLINE nelua_sequenceimpl_string__ptr nelua_GCAllocator_new_1(nelua_GCAllocator_ptr self, nlniltype what, nlniltype size, nlniltype flags);
static void nelua_assert_line_53(bool cond, nlstring msg);
typedef struct nelua_listnode_Event_ nelua_listnode_Event_;
typedef nelua_listnode_Event_* nelua_listnode_Event__ptr;
typedef nelua_listnode_Event_* nelua_listnodeT_ptr;
typedef struct entropy_defs_event_Event entropy_defs_event_Event;
typedef int64_t entropy_defs_event_Type;
typedef union entropy_defs_event_Data entropy_defs_event_Data;
typedef struct entropy_defs_event_DataKey entropy_defs_event_DataKey;
typedef int64_t entropy_defs_event_DataKeyAction;
struct entropy_defs_event_DataKey {
  entropy_defs_event_DataKeyAction action;
  uint32_t key;
  uint32_t modifiers;
};
NELUA_STATIC_ASSERT(sizeof(entropy_defs_event_DataKey) == 16 && NELUA_ALIGNOF(entropy_defs_event_DataKey) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_defs_event_DataMouseMotion entropy_defs_event_DataMouseMotion;
struct entropy_defs_event_DataMouseMotion {
  int32_t x;
  int32_t y;
};
NELUA_STATIC_ASSERT(sizeof(entropy_defs_event_DataMouseMotion) == 8 && NELUA_ALIGNOF(entropy_defs_event_DataMouseMotion) == 4, "Nelua and C disagree on type size or align");
typedef struct entropy_defs_event_DataMouseButton entropy_defs_event_DataMouseButton;
typedef int64_t entropy_defs_event_DataMouseButtonAction;
struct entropy_defs_event_DataMouseButton {
  entropy_defs_event_DataMouseButtonAction action;
  uint32_t button;
};
NELUA_STATIC_ASSERT(sizeof(entropy_defs_event_DataMouseButton) == 16 && NELUA_ALIGNOF(entropy_defs_event_DataMouseButton) == 8, "Nelua and C disagree on type size or align");
union entropy_defs_event_Data {
  entropy_defs_event_DataKey Key;
  entropy_defs_event_DataMouseMotion MouseMotion;
  entropy_defs_event_DataMouseButton MouseButton;
};
NELUA_STATIC_ASSERT(sizeof(entropy_defs_event_Data) == 16 && NELUA_ALIGNOF(entropy_defs_event_Data) == 8, "Nelua and C disagree on type size or align");
struct entropy_defs_event_Event {
  entropy_defs_event_Type type;
  entropy_defs_event_Data data;
};
NELUA_STATIC_ASSERT(sizeof(entropy_defs_event_Event) == 24 && NELUA_ALIGNOF(entropy_defs_event_Event) == 8, "Nelua and C disagree on type size or align");
struct nelua_listnode_Event_ {
  nelua_listnodeT_ptr prev;
  nelua_listnodeT_ptr next;
  entropy_defs_event_Event value;
};
NELUA_STATIC_ASSERT(sizeof(nelua_listnode_Event_) == 40 && NELUA_ALIGNOF(nelua_listnode_Event_) == 8, "Nelua and C disagree on type size or align");
static NELUA_NOINLINE nelua_listnode_Event__ptr nelua_GCAllocator_new_2(nelua_GCAllocator_ptr self, nlniltype what, nlniltype size, nlniltype flags);
static void nelua_assert_line_54(bool cond, nlstring msg);
typedef struct nelua_FStream nelua_FStream;
typedef nelua_FStream* nelua_FStream_ptr;
typedef FILE* FILE_ptr;
typedef int (*function_4jgCZA213GoJ9669W)(FILE_ptr);
struct nelua_FStream {
  FILE_ptr fp;
  function_4jgCZA213GoJ9669W closef;
};
NELUA_STATIC_ASSERT(sizeof(nelua_FStream) == 16 && NELUA_ALIGNOF(nelua_FStream) == 8, "Nelua and C disagree on type size or align");
static NELUA_NOINLINE nelua_FStream_ptr nelua_GCAllocator_new_3(nelua_GCAllocator_ptr self, nelua_FStream what, nlniltype size, nlniltype flags);
static void nelua_assert_line_55(bool cond, nlstring msg);
typedef WGPUShaderModuleWGSLDescriptor* WGPUShaderModuleWGSLDescriptor_ptr;
static NELUA_NOINLINE WGPUShaderModuleWGSLDescriptor_ptr nelua_GCAllocator_new_4(nelua_GCAllocator_ptr self, nlniltype what, nlniltype size, nlniltype flags);
static void nelua_assert_line_56(bool cond, nlstring msg);
static void* nelua_GCAllocator_xalloc_1(nelua_GCAllocator_ptr self, uintptr_t size, nlniltype flags);
static void* nelua_GCAllocator_realloc0(nelua_GCAllocator_ptr self, void* p, uintptr_t newsize, uintptr_t oldsize);
static void nelua_GCAllocator_spandealloc_1(nelua_GCAllocator_ptr self, nelua_span_uint8_ s);
static nelua_span_uint8_ nelua_GCAllocator_spanrealloc_1(nelua_GCAllocator_ptr self, nelua_span_uint8_ s, uintptr_t size);
static nelua_span_string_ nelua_GCAllocator_spanrealloc_2(nelua_GCAllocator_ptr self, nelua_span_string_ s, uintptr_t size);
static nelua_span_float64_ nelua_GCAllocator_spanrealloc_3(nelua_GCAllocator_ptr self, nelua_span_float64_ s, uintptr_t size);
static nelua_span_Vertex_ nelua_GCAllocator_spanrealloc_4(nelua_GCAllocator_ptr self, nelua_span_Vertex_ s, uintptr_t size);
static nelua_span_uint32_ nelua_GCAllocator_spanrealloc_5(nelua_GCAllocator_ptr self, nelua_span_uint32_ s, uintptr_t size);
static nelua_span_Vec2_ nelua_GCAllocator_spanrealloc_6(nelua_GCAllocator_ptr self, nelua_span_Vec2_ s, uintptr_t size);
static nelua_span_uint16_ nelua_GCAllocator_spanrealloc_7(nelua_GCAllocator_ptr self, nelua_span_uint16_ s, uintptr_t size);
static nelua_span_Entity_ nelua_GCAllocator_spanrealloc_9(nelua_GCAllocator_ptr self, nelua_span_Entity_ s, uintptr_t size);
static nelua_span_Mesh_ nelua_GCAllocator_spanrealloc_10(nelua_GCAllocator_ptr self, nelua_span_Mesh_ s, uintptr_t size);
static nelua_span_Camera_ nelua_GCAllocator_spanrealloc_11(nelua_GCAllocator_ptr self, nelua_span_Camera_ s, uintptr_t size);
static nelua_span_uint8_ nelua_GCAllocator_xspanrealloc_1(nelua_GCAllocator_ptr self, nelua_span_uint8_ s, uintptr_t size);
static nelua_span_string_ nelua_GCAllocator_xspanrealloc_2(nelua_GCAllocator_ptr self, nelua_span_string_ s, uintptr_t size);
static nelua_span_float64_ nelua_GCAllocator_xspanrealloc_3(nelua_GCAllocator_ptr self, nelua_span_float64_ s, uintptr_t size);
static nelua_span_Vertex_ nelua_GCAllocator_xspanrealloc_4(nelua_GCAllocator_ptr self, nelua_span_Vertex_ s, uintptr_t size);
static nelua_span_uint32_ nelua_GCAllocator_xspanrealloc_5(nelua_GCAllocator_ptr self, nelua_span_uint32_ s, uintptr_t size);
static nelua_span_Vec2_ nelua_GCAllocator_xspanrealloc_6(nelua_GCAllocator_ptr self, nelua_span_Vec2_ s, uintptr_t size);
static nelua_span_uint16_ nelua_GCAllocator_xspanrealloc_7(nelua_GCAllocator_ptr self, nelua_span_uint16_ s, uintptr_t size);
static nelua_span_Entity_ nelua_GCAllocator_xspanrealloc_9(nelua_GCAllocator_ptr self, nelua_span_Entity_ s, uintptr_t size);
static nelua_span_Mesh_ nelua_GCAllocator_xspanrealloc_10(nelua_GCAllocator_ptr self, nelua_span_Mesh_ s, uintptr_t size);
static nelua_span_Camera_ nelua_GCAllocator_xspanrealloc_11(nelua_GCAllocator_ptr self, nelua_span_Camera_ s, uintptr_t size);
static nelua_span_uint8_ nelua_GCAllocator_spanrealloc0_1(nelua_GCAllocator_ptr self, nelua_span_uint8_ s, uintptr_t size);
static void nelua_GCAllocator_delete_2(nelua_GCAllocator_ptr self, nelua_listnode_Event__ptr v);
static void nelua_GCAllocator_delete_3(nelua_GCAllocator_ptr self, nelua_FStream_ptr v);
static NELUA_INLINE bool nelua_strchar_1_isalpha(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_islower(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_isupper(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_isdigit(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_isxdigit(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_iscntrl(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_isgraph(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_isspace(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_isalnum(uint8_t c);
static NELUA_INLINE bool nelua_strchar_1_ispunct(uint8_t c);
static NELUA_INLINE uint8_t nelua_strchar_1_getdigit(uint8_t c);
static NELUA_INLINE uint8_t nelua_strchar_1_getbasedigit(uint8_t c);
typedef struct nlmulret_nlboolean_nlint64 {
  bool r1;
  int64_t r2;
} nlmulret_nlboolean_nlint64;
static nlmulret_nlboolean_nlint64 nelua_strconv_1_str2int(nlstring s, uint64_t base);
static void nelua_assert_line_57(bool cond, nlstring msg);
typedef struct NELUA_MAYALIAS nluint8_arr48 {uint8_t v[48];} nluint8_arr48;
typedef union NELUA_MAYALIAS nluint8_arr48_cast {nluint8_arr48 a; uint8_t p[48];} nluint8_arr48_cast;
NELUA_STATIC_ASSERT(sizeof(nluint8_arr48) == 48 && NELUA_ALIGNOF(nluint8_arr48) == 1, "Nelua and C disagree on type size or align");
typedef nluint8_arr48* nluint8_arr48_ptr;
static nlstring nelua_strconv_1_int2str_1(nluint8_arr48_ptr buf, intptr_t x, nlniltype base);
static NELUA_INLINE uintptr_t nelua_assert_bounds_nlusize(uintptr_t index, uintptr_t len);
typedef struct nlmulret_nlboolean_nlfloat64 {
  bool r1;
  double r2;
} nlmulret_nlboolean_nlfloat64;
static nlmulret_nlboolean_nlfloat64 nelua_strconv_1_str2num(nlstring s);
typedef struct NELUA_MAYALIAS nluint8_arr64 {uint8_t v[64];} nluint8_arr64;
typedef union NELUA_MAYALIAS nluint8_arr64_cast {nluint8_arr64 a; uint8_t p[64];} nluint8_arr64_cast;
NELUA_STATIC_ASSERT(sizeof(nluint8_arr64) == 64 && NELUA_ALIGNOF(nluint8_arr64) == 1, "Nelua and C disagree on type size or align");
typedef nluint8_arr64* nluint8_arr64_ptr;
static nlstring nelua_strconv_1_num2str_1(nluint8_arr64_ptr buf, float x);
typedef union nelua_UF2I nelua_UF2I;
union nelua_UF2I {
  float f;
  uint32_t i;
};
NELUA_STATIC_ASSERT(sizeof(nelua_UF2I) == 4 && NELUA_ALIGNOF(nelua_UF2I) == 4, "Nelua and C disagree on type size or align");
typedef struct nelua_stringbuilderT nelua_stringbuilderT;
typedef nelua_stringbuilderT* nelua_stringbuilderT_ptr;
struct nelua_stringbuilderT {
  nelua_span_uint8_ data;
  uintptr_t size;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_stringbuilderT) == 24 && NELUA_ALIGNOF(nelua_stringbuilderT) == 8, "Nelua and C disagree on type size or align");
static void nelua_stringbuilderT_destroy(nelua_stringbuilderT_ptr self);
static bool nelua_stringbuilderT_grow(nelua_stringbuilderT_ptr self, uintptr_t newsize);
static nelua_span_uint8_ nelua_stringbuilderT_prepare(nelua_stringbuilderT_ptr self, uintptr_t n);
static void nelua_stringbuilderT_commit(nelua_stringbuilderT_ptr self, uintptr_t n);
static void nelua_assert_line_58(bool cond, nlstring msg);
static bool nelua_stringbuilderT_writebyte_1(nelua_stringbuilderT_ptr self, uint8_t c, nlniltype n);
static nlstring nelua_stringbuilderT_promote(nelua_stringbuilderT_ptr self);
static nlstring nelua_nlstring_create(uintptr_t size);
static void nelua_assert_line_59(bool cond, nlstring msg);
static void nelua_nlstring_destroy(nlstring_ptr self);
static nlstring nelua_nlstring_copy(nlstring s);
static nlstring nelua_nlstring_subview_1(nlstring s, intptr_t i, intptr_t j);
static NELUA_INLINE intptr_t nelua_nlstring___len(nlstring a);
static nlstring nelua_nlstring___concat_2(float a, nlstring b);
static nlstring nelua_nlstring___concat_6(nlstring a, char* b);
static nlstring nelua_nlstring___concat_7(nlstring a, nlstring b);
static nlstring nelua_nlstring___concat_8(WGPULogLevel a, nlstring b);
static bool nelua_nlstring___eq(nlstring a, nlstring b);
typedef struct nelua_StrPattCapture nelua_StrPattCapture;
typedef nelua_StrPattCapture* nelua_StrPattCapture_ptr;
struct nelua_StrPattCapture {
  intptr_t init;
  intptr_t len;
};
NELUA_STATIC_ASSERT(sizeof(nelua_StrPattCapture) == 16 && NELUA_ALIGNOF(nelua_StrPattCapture) == 8, "Nelua and C disagree on type size or align");
static bool nelua_StrPattCapture_is_unfinished(nelua_StrPattCapture_ptr self);
static bool nelua_StrPattCapture_is_position(nelua_StrPattCapture_ptr self);
static bool nelua_match_has_pattern_specials(nlstring pattern);
static bool nelua_match_has_pattern_anchor(nlstring pattern);
typedef struct nelua_StrPatt_1 nelua_StrPatt_1;
struct nelua_StrPatt_1 {
  nlstring source;
  nlstring pattern;
  intptr_t depth;
  intptr_t numcaptures;
  nelua_StrPattCapture capture[32];
  bool plain;
  bool anchor;
};
NELUA_STATIC_ASSERT(sizeof(nelua_StrPatt_1) == 568 && NELUA_ALIGNOF(nelua_StrPatt_1) == 8, "Nelua and C disagree on type size or align");
static nelua_StrPatt_1 nelua_StrPatt_1_create(nlstring source, nlstring pattern, bool plain);
typedef nelua_StrPatt_1* nelua_StrPatt_1_ptr;
static void nelua_StrPatt_1_reset_captures(nelua_StrPatt_1_ptr self);
static NELUA_INLINE intptr_t nelua_assert_bounds_nlisize(intptr_t index, uintptr_t len);
typedef struct nlmulret_nlboolean_nlstring_nelua_StrPattCapture {
  bool r1;
  nlstring r2;
  nelua_StrPattCapture r3;
} nlmulret_nlboolean_nlstring_nelua_StrPattCapture;
static nlmulret_nlboolean_nlstring_nelua_StrPattCapture nelua_StrPatt_1_get_capture(nelua_StrPatt_1_ptr self, intptr_t i);
static intptr_t nelua_StrPatt_1__match(nelua_StrPatt_1_ptr ms, intptr_t s, intptr_t p);
static bool nelua_match_class(uint8_t c, uint8_t cl);
static intptr_t nelua_match_class_end(nelua_StrPatt_1_ptr ms_1, intptr_t p_1);
static void nelua_assert_line_60(bool cond, nlstring msg);
static void nelua_assert_line_61(bool cond, nlstring msg);
static bool nelua_match_bracket_class(nelua_StrPatt_1_ptr ms_2, uint8_t c, intptr_t p_2, intptr_t ep);
static bool nelua_match_single(nelua_StrPatt_1_ptr ms_3, intptr_t s_1, intptr_t p_3, intptr_t ep);
static intptr_t nelua_match_balance(nelua_StrPatt_1_ptr ms_4, intptr_t s_2, intptr_t p_4);
static void nelua_assert_line_62(bool cond, nlstring msg);
static intptr_t nelua_match_max_expand(nelua_StrPatt_1_ptr ms_5, intptr_t s_3, intptr_t p_5, intptr_t ep);
static intptr_t nelua_match_min_expand(nelua_StrPatt_1_ptr ms_6, intptr_t s_4, intptr_t p_6, intptr_t ep);
static intptr_t nelua_match_start_capture(nelua_StrPatt_1_ptr ms_7, intptr_t s_5, intptr_t p_7, intptr_t what);
static void nelua_assert_line_63(bool cond, nlstring msg);
static intptr_t nelua_match_end_capture(nelua_StrPatt_1_ptr ms_8, intptr_t s_6, intptr_t p_8);
static void nelua_assert_line_64(bool cond, nlstring msg);
static intptr_t nelua_match_capture(nelua_StrPatt_1_ptr ms_9, intptr_t s_7, intptr_t l);
static void nelua_assert_line_65(bool cond, nlstring msg);
static void nelua_assert_line_66(bool cond, nlstring msg);
static void nelua_assert_line_67(bool cond, nlstring msg);
typedef struct nlmulret_nlisize_nlisize {
  intptr_t r1;
  intptr_t r2;
} nlmulret_nlisize_nlisize;
static nlmulret_nlisize_nlisize nelua_StrPatt_1_match(nelua_StrPatt_1_ptr ms, intptr_t s);
typedef struct nlmulret_nlboolean_nelua_sequence_string_ {
  bool r1;
  nelua_sequence_string_ r2;
} nlmulret_nlboolean_nelua_sequence_string_;
static nlmulret_nlboolean_nelua_sequence_string_ nelua_string_match_1(nlstring s, nlstring pattern, nlniltype init);
static void nelua_assert_line_68(bool cond, nlstring msg);
static void nelua_assert_line_69(bool cond, nlstring msg);
static nlmulret_nlboolean_nelua_sequence_string_ nelua_nlstring_match_1(nlstring s, nlstring pattern, nlniltype init);
static NELUA_INLINE uintptr_t nelua_assert_narrow_nlisize_nlusize(intptr_t x);
static nlstring nelua_tostring_1(char* x);
static NELUA_INLINE nlstring nelua_cstring2string(const char* s);
static nlstring nelua_tostring_2(float x);
static nlstring nelua_tostring_6(WGPULogLevel x);
static double nelua_tonumber_1(nlstring x, nlniltype base);
static void nelua_assert_line_70(bool cond, nlstring msg);
static int64_t nelua_tointeger_1(nlstring x, nlniltype base);
static void nelua_assert_line_71(bool cond, nlstring msg);
static double nelua_os_now(void);
static NELUA_INLINE void entropy_world_World_r_1(nlniltype name, nlniltype T);
typedef struct entropy_world_Storage_Vec2_ entropy_world_Storage_Vec2_;
typedef entropy_world_Storage_Vec2_* entropy_world_Storage_Vec2__ptr;
struct entropy_world_Storage_Vec2_ {
  nelua_vector_Vec2_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_Vec2_) == 72 && NELUA_ALIGNOF(entropy_world_Storage_Vec2_) == 8, "Nelua and C disagree on type size or align");
static void entropy_world_Storage_Vec2__reserve(entropy_world_Storage_Vec2__ptr self, uintptr_t n);
static NELUA_INLINE bool nelua_lt_nlisize_nlusize(intptr_t a, uintptr_t b);
static NELUA_INLINE uintptr_t entropy_world_Storage_Vec2__create(entropy_world_Storage_Vec2__ptr self, entropy_math_vec2_Vec2 item);
static void nelua_assert_line_72(bool cond, nlstring msg);
static void nelua_assert_line_73(bool cond, nlstring msg);
static NELUA_INLINE entropy_math_vec2_Vec2_ptr entropy_world_Storage_Vec2____atindex(entropy_world_Storage_Vec2__ptr self, uintptr_t ptr);
static void nelua_assert_line_74(bool cond, nlstring msg);
static NELUA_INLINE bool nelua_lt_nlusize_nlisize(uintptr_t a, intptr_t b);
static void nelua_assert_line_75(bool cond, nlstring msg);
static NELUA_INLINE void entropy_world_World_r_2(nlniltype name, nlniltype T);
typedef struct entropy_world_Storage_Vec2__1 entropy_world_Storage_Vec2__1;
typedef entropy_world_Storage_Vec2__1* entropy_world_Storage_Vec2__1_ptr;
struct entropy_world_Storage_Vec2__1 {
  nelua_vector_Vec2_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_Vec2__1) == 72 && NELUA_ALIGNOF(entropy_world_Storage_Vec2__1) == 8, "Nelua and C disagree on type size or align");
static void entropy_world_Storage_Vec2__1_reserve(entropy_world_Storage_Vec2__1_ptr self, uintptr_t n);
static NELUA_INLINE uintptr_t entropy_world_Storage_Vec2__1_create(entropy_world_Storage_Vec2__1_ptr self, entropy_math_vec2_Vec2 item);
static void nelua_assert_line_76(bool cond, nlstring msg);
static void nelua_assert_line_77(bool cond, nlstring msg);
static NELUA_INLINE entropy_math_vec2_Vec2_ptr entropy_world_Storage_Vec2__1___atindex(entropy_world_Storage_Vec2__1_ptr self, uintptr_t ptr);
static void nelua_assert_line_78(bool cond, nlstring msg);
static void nelua_assert_line_79(bool cond, nlstring msg);
static NELUA_INLINE void entropy_world_World_r_3(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_4(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_5(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_6(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_7(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_8(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_9(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_10(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_11(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_12(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_World_r_13(nlniltype name, nlniltype T);
static void entropy_world_Storage_Entity__reserve(entropy_world_Storage_Entity__ptr self, uintptr_t n);
static NELUA_INLINE uintptr_t entropy_world_Storage_Entity__create(entropy_world_Storage_Entity__ptr self, main_Entity item);
static void nelua_assert_line_80(bool cond, nlstring msg);
static void nelua_assert_line_81(bool cond, nlstring msg);
static NELUA_INLINE nlmulret_nlboolean_nlisize_main_Entity_ptr entropy_world_Storage_Entity____mnext(entropy_world_Storage_Entity__ptr self, intptr_t ctrl_var);
static NELUA_INLINE nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize entropy_world_Storage_Entity____mpairs(entropy_world_Storage_Entity__ptr self);
static NELUA_INLINE void entropy_world_World_r_14(nlniltype name, nlniltype T);
static NELUA_INLINE uintptr_t entropy_world_Storage_Mesh__create(entropy_world_Storage_Mesh__ptr self, entropy_scene_mesh_Mesh item);
static void nelua_assert_line_82(bool cond, nlstring msg);
static void nelua_assert_line_83(bool cond, nlstring msg);
static NELUA_INLINE entropy_scene_mesh_Mesh_ptr entropy_world_Storage_Mesh____atindex(entropy_world_Storage_Mesh__ptr self, uintptr_t ptr);
static void nelua_assert_line_84(bool cond, nlstring msg);
static void nelua_assert_line_85(bool cond, nlstring msg);
static NELUA_INLINE nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr entropy_world_Storage_Mesh____mnext(entropy_world_Storage_Mesh__ptr self, intptr_t ctrl_var);
static NELUA_INLINE nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize entropy_world_Storage_Mesh____mpairs(entropy_world_Storage_Mesh__ptr self);
static NELUA_INLINE void entropy_world_World_r_15(nlniltype name, nlniltype T);
typedef struct entropy_world_Storage_Camera_ entropy_world_Storage_Camera_;
typedef entropy_world_Storage_Camera_* entropy_world_Storage_Camera__ptr;
struct entropy_world_Storage_Camera_ {
  nelua_vector_Camera_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_Camera_) == 72 && NELUA_ALIGNOF(entropy_world_Storage_Camera_) == 8, "Nelua and C disagree on type size or align");
static NELUA_INLINE uintptr_t entropy_world_Storage_Camera__create(entropy_world_Storage_Camera__ptr self, entropy_scene_camera_Camera item);
static void nelua_assert_line_86(bool cond, nlstring msg);
static void nelua_assert_line_87(bool cond, nlstring msg);
static NELUA_INLINE entropy_scene_camera_Camera_ptr entropy_world_Storage_Camera____atindex(entropy_world_Storage_Camera__ptr self, uintptr_t ptr);
static void nelua_assert_line_88(bool cond, nlstring msg);
static void nelua_assert_line_89(bool cond, nlstring msg);
typedef struct entropy_world_World entropy_world_World;
typedef entropy_world_World* entropy_world_World_ptr;
typedef struct entropy_world_Storage_usize_ entropy_world_Storage_usize_;
struct entropy_world_Storage_usize_ {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize_) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize_) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__1 entropy_world_Storage_usize__1;
struct entropy_world_Storage_usize__1 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__1) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__1) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__2 entropy_world_Storage_usize__2;
struct entropy_world_Storage_usize__2 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__2) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__2) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__3 entropy_world_Storage_usize__3;
struct entropy_world_Storage_usize__3 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__3) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__3) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__4 entropy_world_Storage_usize__4;
struct entropy_world_Storage_usize__4 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__4) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__4) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__5 entropy_world_Storage_usize__5;
struct entropy_world_Storage_usize__5 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__5) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__5) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__6 entropy_world_Storage_usize__6;
struct entropy_world_Storage_usize__6 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__6) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__6) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__7 entropy_world_Storage_usize__7;
struct entropy_world_Storage_usize__7 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__7) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__7) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__8 entropy_world_Storage_usize__8;
struct entropy_world_Storage_usize__8 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__8) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__8) == 8, "Nelua and C disagree on type size or align");
typedef struct entropy_world_Storage_usize__9 entropy_world_Storage_usize__9;
struct entropy_world_Storage_usize__9 {
  nelua_vector_usize_ data;
  nelua_vector_uint16_ refs;
  nelua_vector_usize_ free;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_Storage_usize__9) == 72 && NELUA_ALIGNOF(entropy_world_Storage_usize__9) == 8, "Nelua and C disagree on type size or align");
struct entropy_world_World {
  entropy_world_Storage_Vec2_ positions;
  entropy_world_Storage_Vec2__1 velocities;
  entropy_world_Storage_usize_ _1;
  entropy_world_Storage_usize__1 _2;
  entropy_world_Storage_usize__2 _3;
  entropy_world_Storage_usize__3 _4;
  entropy_world_Storage_usize__4 _5;
  entropy_world_Storage_usize__5 _6;
  entropy_world_Storage_usize__6 _7;
  entropy_world_Storage_usize__7 _8;
  entropy_world_Storage_usize__8 _9;
  entropy_world_Storage_usize__9 _10;
  entropy_world_Storage_Entity_ entities;
  entropy_world_Storage_Mesh_ entropy___scene___meshes;
  entropy_world_Storage_Camera_ entropy___scene___cameras;
};
NELUA_STATIC_ASSERT(sizeof(entropy_world_World) == 1080 && NELUA_ALIGNOF(entropy_world_World) == 8, "Nelua and C disagree on type size or align");
static NELUA_INLINE entropy_world_Storage_Vec2__ptr entropy_world_World_s_1(entropy_world_World_ptr self, nlniltype name);
static NELUA_INLINE entropy_world_Storage_Vec2__1_ptr entropy_world_World_s_2(entropy_world_World_ptr self, nlniltype name);
static NELUA_INLINE entropy_world_Storage_Entity__ptr entropy_world_World_s_3(entropy_world_World_ptr self, nlniltype name);
static NELUA_INLINE entropy_world_Storage_Camera__ptr entropy_world_World_s_4(entropy_world_World_ptr self, nlniltype name);
static NELUA_INLINE entropy_world_Storage_Mesh__ptr entropy_world_World_s_5(entropy_world_World_ptr self, nlniltype name);
static NELUA_INLINE void entropy_world_check_storage_1(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_2(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_3(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_4(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_5(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_6(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_7(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_8(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_9(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_10(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_11(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_12(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_13(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_14(nlniltype name, nlniltype T);
static NELUA_INLINE void entropy_world_check_storage_15(nlniltype name, nlniltype T);
static NELUA_INLINE double entropy_world_World_now(entropy_world_World_ptr self);
static nltype nelua_require_entropy_world_pointer(nlniltype modname);
static nltype nelua_require_entropy_world_pointer_cached(nlniltype modname);
static NELUA_INLINE float nelua_math_sqrt_1(float x);
static NELUA_INLINE float nelua_math_cos_1(float x);
static NELUA_INLINE double nelua_math_cos_2(double x);
static NELUA_INLINE float nelua_math_sin_1(float x);
static NELUA_INLINE double nelua_math_sin_2(double x);
static NELUA_INLINE float nelua_math_tan_1(float x);
static NELUA_INLINE float nelua_math_rad_1(float x);
static NELUA_INLINE double nelua_math_rad_2(double x);
static NELUA_INLINE double nelua_math_clamp_1(double x, double min, double max);
static entropy_math_vec2_Vec2 entropy_math_vec2_Vec2___add(entropy_math_vec2_Vec2 a, entropy_math_vec2_Vec2 b);
static nlstring entropy_math_vec2_Vec2___tostring(entropy_math_vec2_Vec2_ptr self);
static entropy_math_vec3_Vec3 entropy_math_vec3_Vec3___add(entropy_math_vec3_Vec3 a, entropy_math_vec3_Vec3 b);
static entropy_math_vec3_Vec3 entropy_math_vec3_Vec3___sub(entropy_math_vec3_Vec3 a, entropy_math_vec3_Vec3 b);
typedef entropy_math_vec3_Vec3* entropy_math_vec3_Vec3_ptr;
static entropy_math_vec3_Vec3 entropy_math_vec3_Vec3_scale(entropy_math_vec3_Vec3_ptr self, float s);
static double entropy_math_vec3_Vec3_dot(entropy_math_vec3_Vec3_ptr self, entropy_math_vec3_Vec3 b);
static entropy_math_vec3_Vec3 entropy_math_vec3_Vec3_cross(entropy_math_vec3_Vec3_ptr self, entropy_math_vec3_Vec3 b);
static double entropy_math_vec3_Vec3___len(entropy_math_vec3_Vec3_ptr self);
static entropy_math_vec3_Vec3 entropy_math_vec3_Vec3_norm(entropy_math_vec3_Vec3_ptr self);
static entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_identity(void);
static entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_from_pos(entropy_math_vec3_Vec3 pos);
static entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_from_rot(float angle, entropy_math_vec3_Vec3 axis);
static entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_from_scl(entropy_math_vec3_Vec3 scale);
typedef entropy_math_mat4_Mat4* entropy_math_mat4_Mat4_ptr;
static entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_transpose(entropy_math_mat4_Mat4_ptr self);
static entropy_math_mat4_Mat4 entropy_math_mat4_Mat4___mul(entropy_math_mat4_Mat4 a, entropy_math_mat4_Mat4 b);
static entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_look_at(entropy_math_vec3_Vec3 eye, entropy_math_vec3_Vec3 target, entropy_math_vec3_Vec3 up);
static entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_perspective(float fov, float aspect, float near, float far);
static entropy_world_World main_world;
static entropy_world_Storage_Vec2__ptr main_positions;
static entropy_world_Storage_Vec2__1_ptr main_velocities;
static entropy_world_Storage_Entity__ptr main_entities;
static void nelua_print_1(nlstring a1);
static void nelua_print_2(intptr_t a1, main_Entity_ptr a2, nlstring a3, nlstring a4);
static double main_now;
static NELUA_INLINE int64_t nelua_assert_imod_nlint64(int64_t a, int64_t b);
static void nelua_print_3(nlstring a1, double a2);
static nelua_vector_float64_ main_times;
static double main_avg = 0.0;
static void main_anonfunc(WGPULogLevel level, char* msg, void* ptr);
typedef struct WGPUAdapterImpl WGPUAdapterImpl;
typedef WGPUAdapterImpl* WGPUAdapterImpl_ptr;
typedef struct WGPUDeviceImpl WGPUDeviceImpl;
typedef WGPUDeviceImpl* WGPUDeviceImpl_ptr;
typedef struct nlmulret_WGPUAdapterImpl_ptr_WGPUDeviceImpl_ptr {
  WGPUAdapterImpl_ptr r1;
  WGPUDeviceImpl_ptr r2;
} nlmulret_WGPUAdapterImpl_ptr_WGPUDeviceImpl_ptr;
typedef struct WGPUSurfaceImpl WGPUSurfaceImpl;
typedef WGPUSurfaceImpl* WGPUSurfaceImpl_ptr;
static nlmulret_WGPUAdapterImpl_ptr_WGPUDeviceImpl_ptr entropy_render_render_request_adapter_device(WGPUSurfaceImpl_ptr surface);
typedef struct WGPUInstanceImpl WGPUInstanceImpl;
typedef WGPUInstanceImpl* WGPUInstanceImpl_ptr;
typedef WGPUChainedStruct* WGPUChainedStruct_ptr;
typedef WGPUAdapterImpl_ptr* WGPUAdapterImpl_ptr_ptr;
static void entropy_render_anonfunc(WGPURequestAdapterStatus status, WGPUAdapterImpl_ptr received, char* message, void* userdata);
typedef WGPUFeatureName* WGPUFeatureName_ptr;
typedef struct NELUA_MAYALIAS WGPUFeatureName_arr1 {WGPUFeatureName v[1];} WGPUFeatureName_arr1;
typedef union NELUA_MAYALIAS WGPUFeatureName_arr1_cast {WGPUFeatureName_arr1 a; WGPUFeatureName p[1];} WGPUFeatureName_arr1_cast;
NELUA_STATIC_ASSERT(sizeof(WGPUFeatureName_arr1) == 4 && NELUA_ALIGNOF(WGPUFeatureName_arr1) == 4, "Nelua and C disagree on type size or align");
typedef WGPUDeviceImpl_ptr* WGPUDeviceImpl_ptr_ptr;
static void entropy_render_anonfunc_1(WGPURequestDeviceStatus status, WGPUDeviceImpl_ptr received, char* message, void* userdata);
typedef struct nelua_list_Event_ nelua_list_Event_;
typedef nelua_list_Event_* nelua_list_Event__ptr;
struct nelua_list_Event_ {
  nelua_listnode_Event__ptr front;
  nelua_listnode_Event__ptr back;
  nelua_GCAllocator allocator;
};
NELUA_STATIC_ASSERT(sizeof(nelua_list_Event_) == 16 && NELUA_ALIGNOF(nelua_list_Event_) == 8, "Nelua and C disagree on type size or align");
static void nelua_list_Event__pushback(nelua_list_Event__ptr self, entropy_defs_event_Event value);
static entropy_defs_event_Event nelua_list_Event__popfront(nelua_list_Event__ptr self);
static void nelua_assert_line_90(bool cond, nlstring msg);
static bool nelua_list_Event__empty(nelua_list_Event__ptr self);
typedef struct entropy_render_glfw_context_GLFWContext entropy_render_glfw_context_GLFWContext;
typedef entropy_render_glfw_context_GLFWContext* entropy_render_glfw_context_GLFWContext_ptr;
typedef void (*function_3mNX19Hui8rMor1PF)(void*, uint32_t, uint32_t);
typedef GLFWwindow* GLFWwindow_ptr;
typedef struct WGPUSwapChainImpl WGPUSwapChainImpl;
typedef WGPUSwapChainImpl* WGPUSwapChainImpl_ptr;
struct entropy_render_glfw_context_GLFWContext {
  uint32_t width;
  uint32_t height;
  bool vsync;
  void* user_pointer;
  function_3mNX19Hui8rMor1PF resize_callback;
  GLFWwindow_ptr window;
  WGPUSurfaceImpl_ptr surface;
  WGPUAdapterImpl_ptr adapter;
  WGPUDeviceImpl_ptr device;
  WGPUTextureFormat format;
  WGPUSwapChainImpl_ptr swapchain;
  nelua_list_Event_ event_queue;
};
NELUA_STATIC_ASSERT(sizeof(entropy_render_glfw_context_GLFWContext) == 96 && NELUA_ALIGNOF(entropy_render_glfw_context_GLFWContext) == 8, "Nelua and C disagree on type size or align");
static void entropy_render_glfw_context_GLFWContext_create_swapchain(entropy_render_glfw_context_GLFWContext_ptr self);
static void entropy_render_glfw_context_GLFWContext_resize(entropy_render_glfw_context_GLFWContext_ptr self, uint32_t width, uint32_t height);
static void entropy_render_glfw_context_GLFWContext_init(entropy_render_glfw_context_GLFWContext_ptr self, nlstring title, uint32_t width, uint32_t height, bool vsync);
static NELUA_INLINE int nelua_assert_narrow_nluint32_nlcint(uint32_t x);
static NELUA_INLINE char* nelua_assert_string2cstring(nlstring s);
typedef GLFWmonitor* GLFWmonitor_ptr;
static void nelua_assert_line_91(bool cond, nlstring msg);
static NELUA_INLINE uint32_t nelua_assert_narrow_nlcint_nluint32(int x);
static void entropy_render_glfw_context_anonfunc(GLFWwindow_ptr window, int width_1, int height_1);
static void entropy_render_glfw_context_anonfunc_1(GLFWwindow_ptr window, int key, int scancode, int action, int mods);
static NELUA_INLINE int32_t nelua_assert_narrow_nlfloat64_nlint32(double x);
static void entropy_render_glfw_context_anonfunc_2(GLFWwindow_ptr window, double x, double y);
static void entropy_render_glfw_context_GLFWContext_cleanup(entropy_render_glfw_context_GLFWContext_ptr self);
typedef struct WGPUTextureViewImpl WGPUTextureViewImpl;
typedef WGPUTextureViewImpl* WGPUTextureViewImpl_ptr;
static NELUA_INLINE WGPUTextureViewImpl_ptr entropy_render_glfw_context_GLFWContext_view(entropy_render_glfw_context_GLFWContext_ptr self);
static NELUA_INLINE void entropy_render_glfw_context_GLFWContext_present(entropy_render_glfw_context_GLFWContext_ptr self);
static NELUA_INLINE bool entropy_render_glfw_context_GLFWContext_should_close(entropy_render_glfw_context_GLFWContext_ptr self);
static NELUA_INLINE void entropy_render_glfw_context_GLFWContext_close(entropy_render_glfw_context_GLFWContext_ptr self);
typedef struct nlmulret_nlboolean_nelua_list_Event__ptr {
  bool r1;
  nelua_list_Event__ptr r2;
} nlmulret_nlboolean_nelua_list_Event__ptr;
static NELUA_INLINE nlmulret_nlboolean_nelua_list_Event__ptr entropy_render_glfw_context_GLFWContext_poll_event(entropy_render_glfw_context_GLFWContext_ptr self);
typedef struct entropy_render_renderer_RendererImplT entropy_render_renderer_RendererImplT;
typedef entropy_render_renderer_RendererImplT* entropy_render_renderer_RendererImplT_ptr;
typedef struct entropy_render_impl_basic_Impl entropy_render_impl_basic_Impl;
typedef struct WGPUBindGroupImpl WGPUBindGroupImpl;
typedef WGPUBindGroupImpl* WGPUBindGroupImpl_ptr;
typedef struct WGPURenderPipelineImpl WGPURenderPipelineImpl;
typedef WGPURenderPipelineImpl* WGPURenderPipelineImpl_ptr;
struct entropy_render_impl_basic_Impl {
  WGPUBufferImpl_ptr globals_buffer;
  WGPUBindGroupImpl_ptr globals_bind_group;
  WGPURenderPipelineImpl_ptr pipeline;
};
NELUA_STATIC_ASSERT(sizeof(entropy_render_impl_basic_Impl) == 24 && NELUA_ALIGNOF(entropy_render_impl_basic_Impl) == 8, "Nelua and C disagree on type size or align");
typedef struct WGPUQueueImpl WGPUQueueImpl;
typedef WGPUQueueImpl* WGPUQueueImpl_ptr;
typedef struct record_3NPFB7dQvgvfT34FH record_3NPFB7dQvgvfT34FH;
struct record_3NPFB7dQvgvfT34FH {
  WGPUTextureFormat format;
  uint32_t width;
  uint32_t height;
};
NELUA_STATIC_ASSERT(sizeof(record_3NPFB7dQvgvfT34FH) == 12 && NELUA_ALIGNOF(record_3NPFB7dQvgvfT34FH) == 4, "Nelua and C disagree on type size or align");
typedef struct WGPUTextureImpl WGPUTextureImpl;
typedef WGPUTextureImpl* WGPUTextureImpl_ptr;
struct entropy_render_renderer_RendererImplT {
  entropy_render_impl_basic_Impl impl;
  WGPUDeviceImpl_ptr device;
  WGPUQueueImpl_ptr queue;
  record_3NPFB7dQvgvfT34FH target_config;
  WGPUTextureImpl_ptr depth_buffer;
};
NELUA_STATIC_ASSERT(sizeof(entropy_render_renderer_RendererImplT) == 64 && NELUA_ALIGNOF(entropy_render_renderer_RendererImplT) == 8, "Nelua and C disagree on type size or align");
static void entropy_render_renderer_RendererImplT_init(entropy_render_renderer_RendererImplT_ptr self, WGPUDeviceImpl_ptr device, WGPUTextureFormat target_format, uint32_t target_width, uint32_t target_height);
static void entropy_render_renderer_RendererImplT_cleanup(entropy_render_renderer_RendererImplT_ptr self);
static void entropy_render_renderer_RendererImplT_resize(entropy_render_renderer_RendererImplT_ptr self, uint32_t width, uint32_t height);
static WGPUTextureViewImpl_ptr entropy_render_renderer_RendererImplT_depth_stencil_view(entropy_render_renderer_RendererImplT_ptr self);
static void entropy_render_renderer_RendererImplT_render(entropy_render_renderer_RendererImplT_ptr self, WGPUTextureViewImpl_ptr target, entropy_world_World_ptr world);
typedef struct WGPUCommandEncoderImpl WGPUCommandEncoderImpl;
typedef WGPUCommandEncoderImpl* WGPUCommandEncoderImpl_ptr;
typedef struct WGPURenderPassEncoderImpl WGPURenderPassEncoderImpl;
typedef WGPURenderPassEncoderImpl* WGPURenderPassEncoderImpl_ptr;
typedef WGPURenderPassColorAttachment* WGPURenderPassColorAttachment_ptr;
typedef struct NELUA_MAYALIAS WGPURenderPassColorAttachment_arr1 {WGPURenderPassColorAttachment v[1];} WGPURenderPassColorAttachment_arr1;
typedef union NELUA_MAYALIAS WGPURenderPassColorAttachment_arr1_cast {WGPURenderPassColorAttachment_arr1 a; WGPURenderPassColorAttachment p[1];} WGPURenderPassColorAttachment_arr1_cast;
NELUA_STATIC_ASSERT(sizeof(WGPURenderPassColorAttachment_arr1) == 56 && NELUA_ALIGNOF(WGPURenderPassColorAttachment_arr1) == 8, "Nelua and C disagree on type size or align");
typedef struct WGPUCommandBufferImpl WGPUCommandBufferImpl;
typedef WGPUCommandBufferImpl* WGPUCommandBufferImpl_ptr;
typedef struct nelua_filestream nelua_filestream;
struct nelua_filestream {
  nelua_FStream_ptr fs;
};
NELUA_STATIC_ASSERT(sizeof(nelua_filestream) == 8 && NELUA_ALIGNOF(nelua_filestream) == 8, "Nelua and C disagree on type size or align");
typedef int (*function_2vA5rraMvZeJQbU9V)(FILE_ptr);
static nelua_filestream nelua_filestream__fromfp(FILE_ptr fp, function_2vA5rraMvZeJQbU9V closef);
typedef nelua_filestream* nelua_filestream_ptr;
static NELUA_INLINE FILE_ptr nelua_filestream__getfp(nelua_filestream_ptr self);
typedef struct nlmulret_nlstring_nlint64 {
  nlstring r1;
  int64_t r2;
} nlmulret_nlstring_nlint64;
static nlmulret_nlstring_nlint64 nelua_geterrno_1(void);
typedef struct nlmulret_nelua_filestream_nlstring_nlint64 {
  nelua_filestream r1;
  nlstring r2;
  int64_t r3;
} nlmulret_nelua_filestream_nlstring_nlint64;
static nlmulret_nelua_filestream_nlstring_nlint64 nelua_filestream_open_1(nlstring filename, nlstring mode);
static bool nelua_checkmode(nlstring mode_1);
static void nelua_assert_line_92(bool cond, nlstring msg);
static nlmulret_nelua_filestream_nlstring_nlint64 nelua_filestream_open_2(nlstring filename, nlniltype mode);
typedef struct nlmulret_nlboolean_nlstring_nlint64 {
  bool r1;
  nlstring r2;
  int64_t r3;
} nlmulret_nlboolean_nlstring_nlint64;
static nlmulret_nlboolean_nlstring_nlint64 nelua_filestream_close(nelua_filestream_ptr self);
static void nelua_filestream_destroy(nelua_filestream_ptr self);
static void nelua_filestream___close(nelua_filestream_ptr self);
typedef struct nlmulret_nlint64_nlstring_nlint64 {
  int64_t r1;
  nlstring r2;
  int64_t r3;
} nlmulret_nlint64_nlstring_nlint64;
static nlmulret_nlint64_nlstring_nlint64 nelua_filestream_seek_1(nelua_filestream_ptr self, nlstring whence, int64_t offset);
typedef struct nlmulret_nlboolean_nlstring {
  bool r1;
  nlstring r2;
} nlmulret_nlboolean_nlstring;
static nlmulret_nlboolean_nlstring nelua_readline(nelua_stringbuilderT_ptr sb, FILE_ptr fp, bool chop);
static NELUA_INLINE bool nelua_eq_nlcint_nluint8(int a, uint8_t b);
static nlmulret_nlboolean_nlstring nelua_readall(nelua_stringbuilderT_ptr sb, FILE_ptr fp);
typedef struct nlmulret_nlstring_nlstring_nlint64 {
  nlstring r1;
  nlstring r2;
  int64_t r3;
} nlmulret_nlstring_nlstring_nlint64;
static nlmulret_nlstring_nlstring_nlint64 nelua_filestream_read_1(nelua_filestream_ptr self, nlstring fmt);
static bool nelua_filestream_isopen(nelua_filestream_ptr self);
typedef struct entropy_render_shader_Shader entropy_render_shader_Shader;
typedef struct WGPUShaderModuleImpl WGPUShaderModuleImpl;
typedef WGPUShaderModuleImpl* WGPUShaderModuleImpl_ptr;
struct entropy_render_shader_Shader {
  WGPUShaderModuleDescriptor descriptor;
  WGPUShaderModuleImpl_ptr module;
};
NELUA_STATIC_ASSERT(sizeof(entropy_render_shader_Shader) == 40 && NELUA_ALIGNOF(entropy_render_shader_Shader) == 8, "Nelua and C disagree on type size or align");
static entropy_render_shader_Shader entropy_render_shader_Shader_load_from_file(nlstring path);
typedef entropy_render_shader_Shader* entropy_render_shader_Shader_ptr;
static void entropy_render_shader_Shader_create(entropy_render_shader_Shader_ptr self, WGPUDeviceImpl_ptr device);
static void entropy_render_shader_Shader_cleanup(entropy_render_shader_Shader_ptr self);
static nlmulret_nelua_filestream_nlstring_nlint64 nelua_io_open_1(nlstring filename, nlniltype mode);
typedef struct nelua_LinesState nelua_LinesState;
struct nelua_LinesState {
  nelua_filestream file;
  nlstring fmt;
};
NELUA_STATIC_ASSERT(sizeof(nelua_LinesState) == 24 && NELUA_ALIGNOF(nelua_LinesState) == 8, "Nelua and C disagree on type size or align");
typedef nlmulret_nlboolean_nlstring (*function_3z5zrzypWbveb3uzk)(nelua_LinesState, nlstring);
typedef struct nlmulret_function_3z5zrzypWbveb3uzk_nelua_LinesState_nlstring_nelua_filestream {
  function_3z5zrzypWbveb3uzk r1;
  nelua_LinesState r2;
  nlstring r3;
  nelua_filestream r4;
} nlmulret_function_3z5zrzypWbveb3uzk_nelua_LinesState_nlstring_nelua_filestream;
static nlmulret_function_3z5zrzypWbveb3uzk_nelua_LinesState_nlstring_nelua_filestream nelua_io_lines_1(nlstring filename, nlniltype fmt);
static void nelua_assert_line_93(bool cond, nlstring msg);
static nlmulret_nlboolean_nlstring nelua_lines_next(nelua_LinesState state, nlstring prevstr);
static entropy_scene_mesh_Mesh entropy_scene_mesh_Mesh_load_from_obj(nlstring path);
static NELUA_INLINE uint32_t nelua_assert_narrow_nlint64_nluint32(int64_t x);
static entropy_scene_mesh_Mesh entropy_scene_mesh_Mesh_clone(entropy_scene_mesh_Mesh_ptr self);
static void entropy_scene_mesh_Mesh_prepare_1(entropy_scene_mesh_Mesh_ptr self, entropy_render_renderer_RendererImplT renderer);
static NELUA_INLINE size_t nelua_assert_narrow_nlisize_nlcsize(intptr_t x);
static nltype nelua_require_entropy_scene_mesh(nlniltype modname);
static nltype nelua_require_entropy_scene_mesh_cached(nlniltype modname);
typedef entropy_render_impl_basic_Impl* entropy_render_impl_basic_Impl_ptr;
static void entropy_render_impl_basic_Impl_init_1(entropy_render_impl_basic_Impl_ptr self, entropy_render_renderer_RendererImplT_ptr renderer);
typedef struct NELUA_MAYALIAS WGPUVertexBufferLayout_arr1 {WGPUVertexBufferLayout v[1];} WGPUVertexBufferLayout_arr1;
typedef union NELUA_MAYALIAS WGPUVertexBufferLayout_arr1_cast {WGPUVertexBufferLayout_arr1 a; WGPUVertexBufferLayout p[1];} WGPUVertexBufferLayout_arr1_cast;
NELUA_STATIC_ASSERT(sizeof(WGPUVertexBufferLayout_arr1) == 24 && NELUA_ALIGNOF(WGPUVertexBufferLayout_arr1) == 8, "Nelua and C disagree on type size or align");
typedef WGPUVertexAttribute* WGPUVertexAttribute_ptr;
typedef struct NELUA_MAYALIAS WGPUVertexAttribute_arr3 {WGPUVertexAttribute v[3];} WGPUVertexAttribute_arr3;
typedef union NELUA_MAYALIAS WGPUVertexAttribute_arr3_cast {WGPUVertexAttribute_arr3 a; WGPUVertexAttribute p[3];} WGPUVertexAttribute_arr3_cast;
NELUA_STATIC_ASSERT(sizeof(WGPUVertexAttribute_arr3) == 72 && NELUA_ALIGNOF(WGPUVertexAttribute_arr3) == 8, "Nelua and C disagree on type size or align");
typedef WGPUVertexBufferLayout* WGPUVertexBufferLayout_ptr;
typedef struct NELUA_MAYALIAS WGPUBindGroupLayoutEntry_arr1 {WGPUBindGroupLayoutEntry v[1];} WGPUBindGroupLayoutEntry_arr1;
typedef union NELUA_MAYALIAS WGPUBindGroupLayoutEntry_arr1_cast {WGPUBindGroupLayoutEntry_arr1 a; WGPUBindGroupLayoutEntry p[1];} WGPUBindGroupLayoutEntry_arr1_cast;
NELUA_STATIC_ASSERT(sizeof(WGPUBindGroupLayoutEntry_arr1) == 104 && NELUA_ALIGNOF(WGPUBindGroupLayoutEntry_arr1) == 8, "Nelua and C disagree on type size or align");
typedef struct WGPUBindGroupLayoutImpl WGPUBindGroupLayoutImpl;
typedef WGPUBindGroupLayoutImpl* WGPUBindGroupLayoutImpl_ptr;
typedef WGPUBindGroupLayoutEntry* WGPUBindGroupLayoutEntry_ptr;
typedef WGPUBindGroupEntry* WGPUBindGroupEntry_ptr;
typedef struct NELUA_MAYALIAS WGPUBindGroupEntry_arr1 {WGPUBindGroupEntry v[1];} WGPUBindGroupEntry_arr1;
typedef union NELUA_MAYALIAS WGPUBindGroupEntry_arr1_cast {WGPUBindGroupEntry_arr1 a; WGPUBindGroupEntry p[1];} WGPUBindGroupEntry_arr1_cast;
NELUA_STATIC_ASSERT(sizeof(WGPUBindGroupEntry_arr1) == 56 && NELUA_ALIGNOF(WGPUBindGroupEntry_arr1) == 8, "Nelua and C disagree on type size or align");
typedef struct WGPUPipelineLayoutImpl WGPUPipelineLayoutImpl;
typedef WGPUPipelineLayoutImpl* WGPUPipelineLayoutImpl_ptr;
typedef WGPUBindGroupLayoutImpl_ptr* WGPUBindGroupLayoutImpl_ptr_ptr;
typedef struct NELUA_MAYALIAS WGPUBindGroupLayoutImpl_ptr_arr1 {WGPUBindGroupLayoutImpl_ptr v[1];} WGPUBindGroupLayoutImpl_ptr_arr1;
typedef union NELUA_MAYALIAS WGPUBindGroupLayoutImpl_ptr_arr1_cast {WGPUBindGroupLayoutImpl_ptr_arr1 a; WGPUBindGroupLayoutImpl_ptr p[1];} WGPUBindGroupLayoutImpl_ptr_arr1_cast;
NELUA_STATIC_ASSERT(sizeof(WGPUBindGroupLayoutImpl_ptr_arr1) == 8 && NELUA_ALIGNOF(WGPUBindGroupLayoutImpl_ptr_arr1) == 8, "Nelua and C disagree on type size or align");
typedef WGPUPushConstantRange* WGPUPushConstantRange_ptr;
typedef struct NELUA_MAYALIAS WGPUPushConstantRange_arr1 {WGPUPushConstantRange v[1];} WGPUPushConstantRange_arr1;
typedef union NELUA_MAYALIAS WGPUPushConstantRange_arr1_cast {WGPUPushConstantRange_arr1 a; WGPUPushConstantRange p[1];} WGPUPushConstantRange_arr1_cast;
NELUA_STATIC_ASSERT(sizeof(WGPUPushConstantRange_arr1) == 12 && NELUA_ALIGNOF(WGPUPushConstantRange_arr1) == 4, "Nelua and C disagree on type size or align");
static void entropy_render_impl_basic_Impl_cleanup_1(entropy_render_impl_basic_Impl_ptr self, entropy_render_renderer_RendererImplT_ptr renderer);
static void entropy_render_impl_basic_Impl_resize_1(entropy_render_impl_basic_Impl_ptr self, entropy_render_renderer_RendererImplT_ptr renderer);
static void entropy_render_impl_basic_Impl_render_1(entropy_render_impl_basic_Impl_ptr self, entropy_render_renderer_RendererImplT_ptr renderer, WGPURenderPassEncoderImpl_ptr pass, WGPUCommandEncoderImpl_ptr encoder, WGPUTextureViewImpl_ptr target, entropy_world_World_ptr world);
typedef struct entropy_render_impl_basic_Globals entropy_render_impl_basic_Globals;
struct entropy_render_impl_basic_Globals {
  entropy_math_mat4_Mat4 mvp;
};
NELUA_STATIC_ASSERT(sizeof(entropy_render_impl_basic_Globals) == 64 && NELUA_ALIGNOF(entropy_render_impl_basic_Globals) == 4, "Nelua and C disagree on type size or align");
static NELUA_INLINE uint32_t nelua_assert_narrow_nlisize_nluint32(intptr_t x);
static nltype nelua_require_entropy_render_impl_basic(nlniltype modname);
static void entropy_scene_camera_Camera_look_at(entropy_scene_camera_Camera_ptr self, entropy_math_vec3_Vec3 target);
static entropy_math_mat4_Mat4 entropy_scene_camera_Camera_view_matrix(entropy_scene_camera_Camera_ptr self);
static entropy_math_mat4_Mat4 entropy_scene_camera_Camera_proj_matrix(entropy_scene_camera_Camera_ptr self, uint32_t width, uint32_t height);
static nltype nelua_require_entropy_scene_camera(nlniltype modname);
static entropy_render_glfw_context_GLFWContext main_context;
static entropy_render_renderer_RendererImplT main_renderer;
static void main_anonfunc_1(void* user, uint32_t width, uint32_t height);
static entropy_world_Storage_Camera__ptr main_cameras;
static uintptr_t main_camera_idx;
static entropy_scene_mesh_Mesh main_teapot_mesh;
static entropy_scene_mesh_Mesh main_cube_mesh;
static entropy_world_Storage_Mesh__ptr main_meshes;
static nelua_vector_float64_ main_fps_list;
static bool main_is_forward_pressed = false;
static bool main_is_backward_pressed = false;
static bool main_is_left_pressed = false;
static bool main_is_right_pressed = false;
static bool main_is_up_pressed = false;
static bool main_is_down_pressed = false;
static double main_camera_yaw = 0.0;
static double main_camera_pitch = 0.0;
static double main_last_mouse_x = 0.0;
static double main_last_mouse_y = 0.0;
static int nelua_main(int argc, char** argv);
/* ------------------------------ DEFINITIONS ------------------------------- */
void nelua_write_stderr(const char* msg, uintptr_t len, bool flush) {
  if(len > 0 && msg) {
    fwrite(msg, 1, len, stderr);
  }
  if(flush) {
    fwrite("\n", 1, 1, stderr);
    fflush(stderr);
  }
}
void nelua_abort(void) {
  NELUA_UBSAN_UNREACHABLE();
  abort();
}
void nelua_panic_cstring(const char* s) {
  if(s) {
    nelua_write_stderr(s, strlen(s), true);
  }
  nelua_abort();
}
void* nelua_assert_deref(void* p) {
  if(NELUA_UNLIKELY(p == NULL)) {
    nelua_panic_cstring("attempt to dereference a null pointer");
  }
  return p;
}
uintptr_t nelua_assert_narrow_nlint64_nlusize(int64_t x) {
  if(NELUA_UNLIKELY(x < 0)) {
    nelua_panic_cstring("narrow casting from int64 to usize failed");
  }
  return (uintptr_t)x;
}
nlmulret_nlboolean_nlint64_nlfloat64 nelua_ipairs_next(nelua_vector_float64__ptr a_1, int64_t k) {
  k = (k + 1);
  if((k >= (nelua_vector_float64____len(a_1) + 0))) {
    return (nlmulret_nlboolean_nlint64_nlfloat64){false, 0, 0.0};
  }
  return (nlmulret_nlboolean_nlint64_nlfloat64){true, k, (*(double*)nelua_assert_deref(nelua_vector_float64____atindex(a_1, nelua_assert_narrow_nlint64_nlusize(k))))};
}
nlmulret_function_5RRHk7NVNoo3zrsdP_nelua_vector_float64__ptr_nlint64 nelua_ipairs_1(nelua_vector_float64__ptr a) {
  return (nlmulret_function_5RRHk7NVNoo3zrsdP_nelua_vector_float64__ptr_nlint64){nelua_ipairs_next, a, -1};
}
nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer nelua_mpairs_1(nelua_hashmap_pointer__GCItem__ptr a) {
  nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer _ret_1 = nelua_hashmap_pointer__GCItem____mpairs(a);
  return (nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer){_ret_1.r1, _ret_1.r2, _ret_1.r3};
}
nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize nelua_mpairs_2(entropy_world_Storage_Mesh__ptr a) {
  nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize _ret_1 = entropy_world_Storage_Mesh____mpairs(a);
  return (nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize){_ret_1.r1, _ret_1.r2, _ret_1.r3};
}
nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize nelua_mpairs_3(entropy_world_Storage_Entity__ptr a) {
  nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize _ret_1 = entropy_world_Storage_Entity____mpairs(a);
  return (nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize){_ret_1.r1, _ret_1.r2, _ret_1.r3};
}
void nelua_assert_line_1(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/memory.nelua:27:14: runtime error: ", 107, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(dest and src, 'invalid pointer')\n             ^~~~~~~\n", 63, true);
    nelua_abort();
  }
}
void nelua_memory_copy(void* dest, void* src, uintptr_t n) {
  if(NELUA_UNLIKELY((n == 0))) {
    return;
  }
  nelua_assert_line_1(((dest != NULL) && (src != NULL)), ((nlstring){(uint8_t*)"invalid pointer", 15}));
  memcpy(dest, src, (size_t)n);
}
void nelua_assert_line_2(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/memory.nelua:60:9: runtime error: ", 106, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(dest, 'invalid pointer')\n        ^~~~\n", 47, true);
    nelua_abort();
  }
}
void nelua_memory_zero(void* dest, uintptr_t n) {
  if(NELUA_UNLIKELY((n == 0))) {
    return;
  }
  nelua_assert_line_2((dest != NULL), ((nlstring){(uint8_t*)"invalid pointer", 15}));
  memset(dest, 0, (size_t)n);
}
void nelua_assert_line_3(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/memory.nelua:76:11: runtime error: ", 107, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(a and b, 'invalid pointer')\n          ^~~~~\n", 53, true);
    nelua_abort();
  }
}
int32_t nelua_memory_compare(void* a, void* b, uintptr_t n) {
  if(NELUA_UNLIKELY((n == 0))) {
    return 0;
  }
  nelua_assert_line_3(((a != NULL) && (b != NULL)), ((nlstring){(uint8_t*)"invalid pointer", 15}));
  return (int32_t)memcmp(a, b, (size_t)n);
}
void nelua_assert_line_4(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/memory.nelua:89:11: runtime error: ", 107, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(a and b, 'invalid pointer')\n          ^~~~~\n", 53, true);
    nelua_abort();
  }
}
bool nelua_memory_equals(void* a, void* b, uintptr_t n) {
  if(NELUA_UNLIKELY((n == 0))) {
    return true;
  }
  nelua_assert_line_4(((a != NULL) && (b != NULL)), ((nlstring){(uint8_t*)"invalid pointer", 15}));
  return (memcmp(a, b, (size_t)n) == 0);
}
void nelua_assert_line_5(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/memory.nelua:102:9: runtime error: ", 107, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(src, 'invalid pointer')\n        ^~~\n", 45, true);
    nelua_abort();
  }
}
void* nelua_memory_scan(void* src, uint8_t x, uintptr_t n) {
  if(NELUA_UNLIKELY((n == 0))) {
    return (void*)NULL;
  }
  nelua_assert_line_5((src != NULL), ((nlstring){(uint8_t*)"invalid pointer", 15}));
  return memchr(src, (int)x, (size_t)n);
}
void nelua_assert_line_6(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/memory.nelua:116:20: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(haystack and needle, 'invalid pointer')\n                   ^~~~~~~~~~\n", 81, true);
    nelua_abort();
  }
}
void* nelua_memory_find(void* haystack, uintptr_t haystacksize, void* needle, uintptr_t needlesize) {
  if(NELUA_UNLIKELY(((needlesize == 0) || (haystack == needle)))) {
    return haystack;
  } else if(NELUA_UNLIKELY((needlesize > haystacksize))) {
    return (void*)NULL;
  } else {
    nelua_assert_line_6(((haystack != NULL) && (needle != NULL)), ((nlstring){(uint8_t*)"invalid pointer", 15}));
    if((needlesize == 1)) {
      return memchr(haystack, (int)(*(uint8_t*)nelua_assert_deref((nluint8_ptr)needle)), (size_t)haystacksize);
    }
    uintptr_t haystackbegin = (uintptr_t)haystack;
    for(uintptr_t i = haystackbegin, _end = (haystackbegin + (haystacksize - needlesize)); i <= _end; i += 1) {
      void* p = (void*)i;
      if((memcmp(p, needle, (size_t)needlesize) == 0)) {
        return p;
      }
    }
    return (void*)NULL;
  }
}
bool nelua_span_uint8__empty(nelua_span_uint8_ self) {
  return (self.size == 0);
}
void nelua_assert_line_7(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nluint8_ptr nelua_span_uint8____atindex(nelua_span_uint8_ self, uintptr_t i) {
  nelua_assert_line_7((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_8(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nlpointer_ptr nelua_span_pointer____atindex(nelua_span_pointer_ self, uintptr_t i) {
  nelua_assert_line_8((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_9(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nelua_GCMarkRange_ptr nelua_span_GCMarkRange____atindex(nelua_span_GCMarkRange_ self, uintptr_t i) {
  nelua_assert_line_9((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_10(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nlusize_ptr nelua_span_usize____atindex(nelua_span_usize_ self, uintptr_t i) {
  nelua_assert_line_10((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_11(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nelua_hashmapnode_pointer__GCItem__ptr nelua_span_hashmapnode_pointer__GCItem_____atindex(nelua_span_hashmapnode_pointer__GCItem__ self, uintptr_t i) {
  nelua_assert_line_11((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_12(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nlstring_ptr nelua_span_string____atindex(nelua_span_string_ self, uintptr_t i) {
  nelua_assert_line_12((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_13(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nlfloat64_ptr nelua_span_float64____atindex(nelua_span_float64_ self, uintptr_t i) {
  nelua_assert_line_13((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_14(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
entropy_scene_mesh_Vertex_ptr nelua_span_Vertex____atindex(nelua_span_Vertex_ self, uintptr_t i) {
  nelua_assert_line_14((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_15(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nluint32_ptr nelua_span_uint32____atindex(nelua_span_uint32_ self, uintptr_t i) {
  nelua_assert_line_15((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_16(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
entropy_math_vec2_Vec2_ptr nelua_span_Vec2____atindex(nelua_span_Vec2_ self, uintptr_t i) {
  nelua_assert_line_16((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_17(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nluint16_ptr nelua_span_uint16____atindex(nelua_span_uint16_ self, uintptr_t i) {
  nelua_assert_line_17((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_18(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
main_Entity_ptr nelua_span_Entity____atindex(nelua_span_Entity_ self, uintptr_t i) {
  nelua_assert_line_18((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_19(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
entropy_scene_mesh_Mesh_ptr nelua_span_Mesh____atindex(nelua_span_Mesh_ self, uintptr_t i) {
  nelua_assert_line_19((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_assert_line_20(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/span.nelua:90:13: runtime error: ", 105, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(i < self.size, 'index out of range')\n            ^~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
entropy_scene_camera_Camera_ptr nelua_span_Camera____atindex(nelua_span_Camera_ self, uintptr_t i) {
  nelua_assert_line_20((i < self.size), ((nlstring){(uint8_t*)"index out of range", 18}));
  return (&self.data[i]);
}
void nelua_memory_spanset_1(nelua_span_usize_ dest, uintptr_t x) {
  for(uintptr_t i = 0U, _end = dest.size; i < _end; i += 1) {
    (*(uintptr_t*)nelua_assert_deref(nelua_span_usize____atindex(dest, i))) = x;
  }
}
void nelua_sequence_string___init(nelua_sequence_string__ptr self) {
  if(NELUA_LIKELY((self->impl != NULL))) {
    return;
  }
  self->impl = nelua_GCAllocator_new_1((&self->allocator), NELUA_NIL, NELUA_NIL, NELUA_NIL);
}
void nelua_sequence_string__reserve(nelua_sequence_string__ptr self, uintptr_t n) {
  nelua_sequence_string___init(self);
  uintptr_t cap = (n + 1);
  uintptr_t curcap = self->impl->data.size;
  if((curcap >= cap)) {
    return;
  }
  self->impl->data = nelua_GCAllocator_xspanrealloc_2((&self->allocator), self->impl->data, cap);
  if(NELUA_UNLIKELY((curcap == 0))) {
    (*(nlstring*)nelua_assert_deref(nelua_span_string____atindex(self->impl->data, 0U))) = (nlstring){0};
  }
}
void nelua_sequence_string__resize(nelua_sequence_string__ptr self, uintptr_t n) {
  nelua_sequence_string__reserve(self, n);
  if((n > self->impl->size)) {
    nelua_memory_zero((void*)(&(*(nlstring*)nelua_assert_deref(nelua_span_string____atindex(self->impl->data, (self->impl->size + 1))))), ((n - self->impl->size) * 16));
  }
  self->impl->size = n;
}
void nelua_assert_line_21(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/sequence.nelua:147:17: runtime error: ", 110, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > curcap, 'capacity overflow')\n                ^~~~~~~~\n", 73, true);
    nelua_abort();
  }
}
void nelua_sequenceT_grow(nelua_sequence_string__ptr self) {
  uintptr_t cap = 2U;
  uintptr_t curcap = self->impl->data.size;
  if(NELUA_LIKELY((curcap != 0))) {
    cap = (curcap * 2);
    nelua_assert_line_21((cap > curcap), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->impl->data = nelua_GCAllocator_xspanrealloc_2((&self->allocator), self->impl->data, cap);
  if(NELUA_UNLIKELY((curcap == 0))) {
    (*(nlstring*)nelua_assert_deref(nelua_span_string____atindex(self->impl->data, 0U))) = (nlstring){0};
  }
}
void nelua_assert_line_22(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/sequence.nelua:255:18: runtime error: ", 110, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      assert(pos == self.impl.size + 1, 'position out of bounds')\n                 ^~~~~~~~~~~~~~~~~~~~~\n", 106, true);
    nelua_abort();
  }
}
nlstring_ptr nelua_sequence_string____atindex(nelua_sequence_string__ptr self, uintptr_t pos) {
  nelua_sequence_string___init(self);
  if(NELUA_UNLIKELY((pos > self->impl->size))) {
    nelua_assert_line_22((pos == (self->impl->size + 1)), ((nlstring){(uint8_t*)"position out of bounds", 22}));
    self->impl->size = (self->impl->size + 1);
    if(NELUA_UNLIKELY(((self->impl->size + 1) > self->impl->data.size))) {
      nelua_sequenceT_grow(self);
    }
    (*(nlstring*)nelua_assert_deref(nelua_span_string____atindex(self->impl->data, pos))) = (nlstring){0};
  } else if(NELUA_UNLIKELY(((self->impl->data.size == 0) && (pos == 0)))) {
    nelua_sequenceT_grow(self);
  }
  return (&(*(nlstring*)nelua_assert_deref(nelua_span_string____atindex(self->impl->data, pos))));
}
intptr_t nelua_sequence_string____len(nelua_sequence_string__ptr self) {
  if(NELUA_UNLIKELY((!(self->impl != NULL)))) {
    return 0;
  }
  return (intptr_t)self->impl->size;
}
void* nelua_GeneralAllocator_alloc_1(nelua_GeneralAllocator_ptr self, uintptr_t size, uintptr_t flags) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  return malloc((size_t)size);
}
void* nelua_GeneralAllocator_alloc_2(nelua_GeneralAllocator_ptr self, uintptr_t size, nlniltype flags) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  return malloc((size_t)size);
}
void* nelua_GeneralAllocator_alloc0_1(nelua_GeneralAllocator_ptr self, uintptr_t size, nlniltype flags) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  return calloc((size_t)size, 1U);
}
void* nelua_GeneralAllocator_alloc0_2(nelua_GeneralAllocator_ptr self, uintptr_t size, uintptr_t flags) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  return calloc((size_t)size, 1U);
}
void nelua_GeneralAllocator_dealloc(nelua_GeneralAllocator_ptr self, void* p) {
  if(NELUA_UNLIKELY((p == (void*)NULL))) {
    return;
  }
  free(p);
}
void* nelua_GeneralAllocator_realloc(nelua_GeneralAllocator_ptr self, void* p, uintptr_t newsize, uintptr_t oldsize) {
  if(NELUA_UNLIKELY((newsize == 0))) {
    if(NELUA_LIKELY((p != (void*)NULL))) {
      free(p);
    }
    return (void*)NULL;
  } else if(NELUA_UNLIKELY((newsize == oldsize))) {
    return p;
  }
  return realloc(p, (size_t)newsize);
}
void* nelua_GeneralAllocator_realloc0(nelua_GeneralAllocator_ptr self, void* p, uintptr_t newsize, uintptr_t oldsize) {
  p = nelua_GeneralAllocator_realloc(self, p, newsize, oldsize);
  if(NELUA_LIKELY(((newsize > oldsize) && (p != (void*)NULL)))) {
    nelua_memory_zero((void*)(&((nluint8_arr0_ptr)p)[oldsize]), (newsize - oldsize));
  }
  return p;
}
nelua_span_pointer_ nelua_GeneralAllocator_spanalloc_1(nelua_GeneralAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags) {
  if(NELUA_LIKELY((size > 0))) {
    nlpointer_arr0_ptr data = ((nlpointer_arr0_ptr)nelua_GeneralAllocator_alloc_2(self, (size * 8), NELUA_NIL));
    if(NELUA_LIKELY((data != ((nlpointer_arr0_ptr)NULL)))) {
      return (nelua_span_pointer_){.data = data, .size = size};
    }
  }
  return (nelua_span_pointer_){0};
}
nelua_span_GCMarkRange_ nelua_GeneralAllocator_spanalloc_2(nelua_GeneralAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags) {
  if(NELUA_LIKELY((size > 0))) {
    uintptr_t flags_1 = 262144U;
    nelua_GCMarkRange_arr0_ptr data = ((nelua_GCMarkRange_arr0_ptr)nelua_GeneralAllocator_alloc_1(self, (size * 16), flags_1));
    if(NELUA_LIKELY((data != ((nelua_GCMarkRange_arr0_ptr)NULL)))) {
      return (nelua_span_GCMarkRange_){.data = data, .size = size};
    }
  }
  return (nelua_span_GCMarkRange_){0};
}
nelua_span_usize_ nelua_GeneralAllocator_spanalloc_3(nelua_GeneralAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags) {
  if(NELUA_LIKELY((size > 0))) {
    uintptr_t flags_2 = 262144U;
    nlusize_arr0_ptr data = ((nlusize_arr0_ptr)nelua_GeneralAllocator_alloc_1(self, (size * 8), flags_2));
    if(NELUA_LIKELY((data != ((nlusize_arr0_ptr)NULL)))) {
      return (nelua_span_usize_){.data = data, .size = size};
    }
  }
  return (nelua_span_usize_){0};
}
nelua_span_hashmapnode_pointer__GCItem__ nelua_GeneralAllocator_spanalloc0_1(nelua_GeneralAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags) {
  if(NELUA_LIKELY((size > 0))) {
    nelua_hashmapnode_pointer__GCItem__arr0_ptr data = ((nelua_hashmapnode_pointer__GCItem__arr0_ptr)nelua_GeneralAllocator_alloc0_1(self, (size * 64), NELUA_NIL));
    if(NELUA_LIKELY((data != ((nelua_hashmapnode_pointer__GCItem__arr0_ptr)NULL)))) {
      return (nelua_span_hashmapnode_pointer__GCItem__){.data = data, .size = size};
    }
  }
  return (nelua_span_hashmapnode_pointer__GCItem__){0};
}
void nelua_GeneralAllocator_spandealloc_1(nelua_GeneralAllocator_ptr self, nelua_span_pointer_ s) {
  if(NELUA_UNLIKELY((s.size == 0))) {
    return;
  }
  nelua_GeneralAllocator_dealloc(self, (void*)s.data);
}
void nelua_GeneralAllocator_spandealloc_2(nelua_GeneralAllocator_ptr self, nelua_span_GCMarkRange_ s) {
  if(NELUA_UNLIKELY((s.size == 0))) {
    return;
  }
  nelua_GeneralAllocator_dealloc(self, (void*)s.data);
}
void nelua_GeneralAllocator_spandealloc_3(nelua_GeneralAllocator_ptr self, nelua_span_usize_ s) {
  if(NELUA_UNLIKELY((s.size == 0))) {
    return;
  }
  nelua_GeneralAllocator_dealloc(self, (void*)s.data);
}
void nelua_GeneralAllocator_spandealloc_4(nelua_GeneralAllocator_ptr self, nelua_span_hashmapnode_pointer__GCItem__ s) {
  if(NELUA_UNLIKELY((s.size == 0))) {
    return;
  }
  nelua_GeneralAllocator_dealloc(self, (void*)s.data);
}
nelua_span_pointer_ nelua_GeneralAllocator_spanrealloc_1(nelua_GeneralAllocator_ptr self, nelua_span_pointer_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GeneralAllocator_spanalloc_1(self, NELUA_NIL, size, NELUA_NIL);
    return s;
  }
  nlpointer_arr0_ptr p = ((nlpointer_arr0_ptr)nelua_GeneralAllocator_realloc(self, (void*)s.data, (size * 8), (s.size * 8)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nlpointer_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_GCMarkRange_ nelua_GeneralAllocator_spanrealloc_2(nelua_GeneralAllocator_ptr self, nelua_span_GCMarkRange_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GeneralAllocator_spanalloc_2(self, NELUA_NIL, size, NELUA_NIL);
    return s;
  }
  nelua_GCMarkRange_arr0_ptr p = ((nelua_GCMarkRange_arr0_ptr)nelua_GeneralAllocator_realloc(self, (void*)s.data, (size * 16), (s.size * 16)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nelua_GCMarkRange_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_usize_ nelua_GeneralAllocator_spanrealloc_3(nelua_GeneralAllocator_ptr self, nelua_span_usize_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GeneralAllocator_spanalloc_3(self, NELUA_NIL, size, NELUA_NIL);
    return s;
  }
  nlusize_arr0_ptr p = ((nlusize_arr0_ptr)nelua_GeneralAllocator_realloc(self, (void*)s.data, (size * 8), (s.size * 8)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nlusize_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
void nelua_panic_string(nlstring s) {
  if(s.size > 0) {
    nelua_write_stderr((const char*)s.data, s.size, true);
  }
  nelua_abort();
}
nelua_span_pointer_ nelua_GeneralAllocator_xspanrealloc_1(nelua_GeneralAllocator_ptr self, nelua_span_pointer_ s, uintptr_t size) {
  s = nelua_GeneralAllocator_spanrealloc_1(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_GCMarkRange_ nelua_GeneralAllocator_xspanrealloc_2(nelua_GeneralAllocator_ptr self, nelua_span_GCMarkRange_ s, uintptr_t size) {
  s = nelua_GeneralAllocator_spanrealloc_2(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_usize_ nelua_GeneralAllocator_xspanrealloc_3(nelua_GeneralAllocator_ptr self, nelua_span_usize_ s, uintptr_t size) {
  s = nelua_GeneralAllocator_spanrealloc_3(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_hashmapnode_pointer__GCItem__ nelua_GeneralAllocator_spanrealloc0_1(nelua_GeneralAllocator_ptr self, nelua_span_hashmapnode_pointer__GCItem__ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GeneralAllocator_spanalloc0_1(self, NELUA_NIL, size, NELUA_NIL);
    return s;
  }
  nelua_hashmapnode_pointer__GCItem__arr0_ptr p = ((nelua_hashmapnode_pointer__GCItem__arr0_ptr)nelua_GeneralAllocator_realloc0(self, (void*)s.data, (size * 64), (s.size * 64)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nelua_hashmapnode_pointer__GCItem__arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_hashmapnode_pointer__GCItem__ nelua_GeneralAllocator_xspanrealloc0_1(nelua_GeneralAllocator_ptr self, nelua_span_hashmapnode_pointer__GCItem__ s, uintptr_t size) {
  s = nelua_GeneralAllocator_spanrealloc0_1(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
uintptr_t nelua_hash_hash_1(void* v) {
  return ((uintptr_t)v >> 3);
}
uintptr_t nelua_ceilidiv(uintptr_t x, uintptr_t y) {
  return (((x + y) - 1) / y);
}
uintptr_t nelua_hashmod(uintptr_t h, uintptr_t n) {
  return (h % ((n - 1) | 1));
}
uintptr_t nelua_roundpow2(uintptr_t n) {
  if(((n & (n - 1)) == 0)) {
    return n;
  }
  n = (n | (n >> 1));
  n = (n | (n >> 2));
  n = (n | (n >> 4));
  n = (n | (n >> 8));
  n = (n | (n >> 16));
  n = (n | (n >> 32));
  n = (n + 1);
  return n;
}
void nelua_hashmap_pointer__GCItem__destroy(nelua_hashmap_pointer__GCItem__ptr self) {
  nelua_GeneralAllocator_spandealloc_3((&self->allocator), self->buckets);
  nelua_GeneralAllocator_spandealloc_4((&self->allocator), self->nodes);
  self->buckets = (nelua_span_usize_){0};
  self->nodes = (nelua_span_hashmapnode_pointer__GCItem__){0};
  self->size = 0U;
  self->free_index = 0U;
}
nlmulret_nlusize_nlusize_nlusize nelua_hashmap_pointer__GCItem___find(nelua_hashmap_pointer__GCItem__ptr self, void* key) {
  uintptr_t h = nelua_hash_hash_1(key);
  uintptr_t bucket_index = nelua_hashmod(h, self->buckets.size);
  uintptr_t prev_node_index = 0xffffffffffffffffULL;
  if(NELUA_UNLIKELY((self->buckets.size == 0))) {
    return (nlmulret_nlusize_nlusize_nlusize){0xffffffffffffffffULL, prev_node_index, bucket_index};
  }
  uintptr_t node_index = (*(uintptr_t*)nelua_assert_deref(nelua_span_usize____atindex(self->buckets, bucket_index)));
  while((node_index != 0xffffffffffffffffULL)) {
    nelua_hashmapnode_pointer__GCItem__ptr node = (&(*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, node_index))));
    bool eq = (key == node->key);
    if(eq) {
      return (nlmulret_nlusize_nlusize_nlusize){node_index, prev_node_index, bucket_index};
    }
    prev_node_index = node_index;
    node_index = node->next;
  }
  return (nlmulret_nlusize_nlusize_nlusize){node_index, prev_node_index, bucket_index};
}
void nelua_assert_line_23(bool cond) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/hashmap.nelua:212:15: runtime error: assertion failed!\n      check(j == self.size)\n              ^~~~~~~~~~~~\n",  182, true);
    nelua_abort();
  }
}
void nelua_hashmap_pointer__GCItem__rehash(nelua_hashmap_pointer__GCItem__ptr self, uintptr_t bucket_count) {
  uintptr_t min_buckets_count = nelua_ceilidiv((self->size * 100), 75U);
  if((bucket_count < min_buckets_count)) {
    bucket_count = min_buckets_count;
  }
  bucket_count = nelua_roundpow2(bucket_count);
  uintptr_t node_count = nelua_ceilidiv((bucket_count * 75U), 100U);
  if(((bucket_count > 0) && (node_count <= self->size))) {
    node_count = (self->size + 1);
  }
  if((((node_count < self->nodes.size) && (self->nodes.size > 0)) && (node_count > 0))) {
    uintptr_t j = 0U;
    while(((j < self->nodes.size) && (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, j))).filled)) {
      j = (j + 1);
    }
    for(uintptr_t i = j, _end = self->nodes.size; i < _end; i += 1) {
      if((*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, i))).filled) {
        (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, j))) = (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, i)));
        j = (j + 1);
      }
    }
    for(uintptr_t i = j, _end = self->nodes.size; i < _end; i += 1) {
      (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, i))) = (nelua_hashmapnode_pointer__GCItem_){0};
    }
    nelua_assert_line_23((j == self->size));
  }
  self->nodes = nelua_GeneralAllocator_xspanrealloc0_1((&self->allocator), self->nodes, node_count);
  self->buckets = nelua_GeneralAllocator_xspanrealloc_3((&self->allocator), self->buckets, bucket_count);
  nelua_memory_spanset_1(self->buckets, 0xffffffffffffffffULL);
  uintptr_t free_index = 0xffffffffffffffffULL;
  for(intptr_t i = (intptr_t)(self->nodes.size - 1); i >= 0; i += -1) {
    nelua_hashmapnode_pointer__GCItem__ptr node = (&(*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, (uintptr_t)i))));
    if(node->filled) {
      node->next = 0xffffffffffffffffULL;
    } else {
      node->next = free_index;
      free_index = (uintptr_t)i;
    }
  }
  self->free_index = free_index;
  for(uintptr_t i = 0U, _end = self->nodes.size; i < _end; i += 1) {
    if((*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, i))).filled) {
      nlmulret_nlusize_nlusize_nlusize _asgnret_1 = nelua_hashmap_pointer__GCItem___find(self, (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, i))).key);
      uintptr_t node_index = _asgnret_1.r1;
      uintptr_t prev_node_index = _asgnret_1.r2;
      uintptr_t bucket_index = _asgnret_1.r3;
      if(NELUA_LIKELY((prev_node_index == 0xffffffffffffffffULL))) {
        (*(uintptr_t*)nelua_assert_deref(nelua_span_usize____atindex(self->buckets, bucket_index))) = i;
      } else {
        (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, prev_node_index))).next = i;
      }
      (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, i))).next = node_index;
    }
  }
}
void nelua_assert_line_24(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/hashmap.nelua:268:24: runtime error: ", 109, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(node_index < self.nodes.size, 'not enough space to add a node')\n                       ^~~~~~~~~~~~~~~~~\n", 118, true);
    nelua_abort();
  }
}
uintptr_t nelua_hashmap_pointer__GCItem___at(nelua_hashmap_pointer__GCItem__ptr self, void* key) {
  if(NELUA_UNLIKELY((self->buckets.size == 0))) {
    nelua_hashmap_pointer__GCItem__rehash(self, 8U);
  }
  nlmulret_nlusize_nlusize_nlusize _asgnret_1 = nelua_hashmap_pointer__GCItem___find(self, key);
  uintptr_t node_index = _asgnret_1.r1;
  uintptr_t prev_node_index = _asgnret_1.r2;
  uintptr_t bucket_index = _asgnret_1.r3;
  if((node_index != 0xffffffffffffffffULL)) {
    return node_index;
  } else {
    uintptr_t node_index_1 = self->free_index;
    nelua_assert_line_24((node_index_1 < self->nodes.size), ((nlstring){(uint8_t*)"not enough space to add a node", 30}));
    nelua_hashmapnode_pointer__GCItem__ptr node = (&(*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, node_index_1))));
    self->free_index = node->next;
    (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(node)) = (nelua_hashmapnode_pointer__GCItem_){.key = key, .filled = true, .next = 0xffffffffffffffffULL};
    if(NELUA_LIKELY((prev_node_index == 0xffffffffffffffffULL))) {
      (*(uintptr_t*)nelua_assert_deref(nelua_span_usize____atindex(self->buckets, bucket_index))) = node_index_1;
    } else {
      (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, prev_node_index))).next = node_index_1;
    }
    self->size = (self->size + 1);
    if(NELUA_UNLIKELY(((self->size * 100) >= (self->buckets.size * 75U)))) {
      nelua_hashmap_pointer__GCItem__rehash(self, nelua_ceilidiv((self->size * 200U), 75U));
    }
    return node_index_1;
  }
}
nelua_GCItem_ptr nelua_hashmap_pointer__GCItem____atindex(nelua_hashmap_pointer__GCItem__ptr self, void* key) {
  return (&(*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, nelua_hashmap_pointer__GCItem___at(self, key)))).value);
}
nelua_GCItem_ptr nelua_hashmap_pointer__GCItem__peek(nelua_hashmap_pointer__GCItem__ptr self, void* key) {
  uintptr_t node_index = nelua_hashmap_pointer__GCItem___find(self, key).r1;
  if((node_index != 0xffffffffffffffffULL)) {
    return (&(*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, node_index))).value);
  }
  return ((nelua_GCItem_ptr)NULL);
}
nelua_GCItem nelua_hashmap_pointer__GCItem__remove(nelua_hashmap_pointer__GCItem__ptr self, void* key) {
  nlmulret_nlusize_nlusize_nlusize _asgnret_1 = nelua_hashmap_pointer__GCItem___find(self, key);
  uintptr_t node_index = _asgnret_1.r1;
  uintptr_t prev_node_index = _asgnret_1.r2;
  uintptr_t bucket_index = _asgnret_1.r3;
  if(NELUA_UNLIKELY((node_index == 0xffffffffffffffffULL))) {
    return (nelua_GCItem){0};
  }
  nelua_hashmapnode_pointer__GCItem__ptr node = (&(*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, node_index))));
  nelua_GCItem value = node->value;
  if(NELUA_LIKELY((prev_node_index == 0xffffffffffffffffULL))) {
    (*(uintptr_t*)nelua_assert_deref(nelua_span_usize____atindex(self->buckets, bucket_index))) = node->next;
  } else {
    (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->nodes, prev_node_index))).next = node->next;
  }
  self->size = (self->size - 1);
  (*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(node)) = (nelua_hashmapnode_pointer__GCItem_){.next = self->free_index};
  self->free_index = node_index;
  return value;
}
uintptr_t nelua_hashmap_pointer__GCItem__bucketcount(nelua_hashmap_pointer__GCItem__ptr self) {
  return self->buckets.size;
}
nelua_hashmapnode_pointer__GCItem__ptr nelua_hashmap_iteratorT__next_node(nelua_hashmap_iteratorT_ptr self, void* key) {
  if(NELUA_UNLIKELY((self->index == 0xffffffffffffffffULL))) {
    self->index = 0U;
  } else {
    self->index = (self->index + 1);
  }
  while((self->index < self->container->nodes.size)) {
    nelua_hashmapnode_pointer__GCItem__ptr node = (&(*(nelua_hashmapnode_pointer__GCItem_*)nelua_assert_deref(nelua_span_hashmapnode_pointer__GCItem_____atindex(self->container->nodes, self->index))));
    if(node->filled) {
      return node;
    }
    self->index = (self->index + 1);
  }
  return ((nelua_hashmapnode_pointer__GCItem__ptr)NULL);
}
nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr nelua_hashmap_iteratorT_mnext(nelua_hashmap_iteratorT_ptr self, void* key) {
  nelua_hashmapnode_pointer__GCItem__ptr node = nelua_hashmap_iteratorT__next_node(self, key);
  if((!(node != NULL))) {
    return (nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr){false, NULL, ((nelua_GCItem_ptr)NULL)};
  }
  return (nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr){true, node->key, (&node->value)};
}
nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer nelua_hashmap_pointer__GCItem____mpairs(nelua_hashmap_pointer__GCItem__ptr self) {
  return (nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer){nelua_hashmap_iteratorT_mnext, (nelua_hashmap_iteratorT){.container = self, .index = 0xffffffffffffffffULL}, NULL};
}
void nelua_vector_pointer__clear(nelua_vector_pointer__ptr self) {
  self->size = 0U;
}
void nelua_vector_pointer__destroy(nelua_vector_pointer__ptr self) {
  nelua_GeneralAllocator_spandealloc_1((&self->allocator), self->data);
  self->data = (nelua_span_pointer_){0};
  self->size = 0U;
}
void nelua_assert_line_25(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow(nelua_vector_pointer__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_25((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GeneralAllocator_xspanrealloc_1((&self->allocator), self->data, cap);
}
void nelua_vector_pointer__push(nelua_vector_pointer__ptr self, void* v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow(self);
  }
  (*(void**)nelua_assert_deref(nelua_span_pointer____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
void nelua_assert_line_26(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
nlpointer_ptr nelua_vector_pointer____atindex(nelua_vector_pointer__ptr self, uintptr_t pos) {
  nelua_assert_line_26((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(void**)nelua_assert_deref(nelua_span_pointer____atindex(self->data, pos))));
}
void nelua_vector_GCMarkRange__destroy(nelua_vector_GCMarkRange__ptr self) {
  nelua_GeneralAllocator_spandealloc_2((&self->allocator), self->data);
  self->data = (nelua_span_GCMarkRange_){0};
  self->size = 0U;
}
void nelua_assert_line_27(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_1(nelua_vector_GCMarkRange__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_27((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GeneralAllocator_xspanrealloc_2((&self->allocator), self->data, cap);
}
void nelua_vector_GCMarkRange__push(nelua_vector_GCMarkRange__ptr self, nelua_GCMarkRange v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_1(self);
  }
  (*(nelua_GCMarkRange*)nelua_assert_deref(nelua_span_GCMarkRange____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
void nelua_assert_line_28(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:140:21: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(self.size > 0, 'attempt to pop an empty vector')\n                    ^~~\n", 84, true);
    nelua_abort();
  }
}
nelua_GCMarkRange nelua_vector_GCMarkRange__pop(nelua_vector_GCMarkRange__ptr self) {
  nelua_assert_line_28((self->size > 0), ((nlstring){(uint8_t*)"attempt to pop an empty vector", 30}));
  self->size = (self->size - 1);
  return (*(nelua_GCMarkRange*)nelua_assert_deref(nelua_span_GCMarkRange____atindex(self->data, self->size)));
}
void nelua_vector_float64__clear(nelua_vector_float64__ptr self) {
  self->size = 0U;
}
void nelua_assert_line_29(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_2(nelua_vector_float64__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_29((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GCAllocator_xspanrealloc_3((&self->allocator), self->data, cap);
}
void nelua_vector_float64__push(nelua_vector_float64__ptr self, double v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_2(self);
  }
  (*(double*)nelua_assert_deref(nelua_span_float64____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
void nelua_assert_line_30(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
nlfloat64_ptr nelua_vector_float64____atindex(nelua_vector_float64__ptr self, uintptr_t pos) {
  nelua_assert_line_30((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(double*)nelua_assert_deref(nelua_span_float64____atindex(self->data, pos))));
}
intptr_t nelua_vector_float64____len(nelua_vector_float64__ptr self) {
  return (intptr_t)self->size;
}
void nelua_assert_line_31(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_3(nelua_vector_Vertex__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_31((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GCAllocator_xspanrealloc_4((&self->allocator), self->data, cap);
}
void nelua_vector_Vertex__push(nelua_vector_Vertex__ptr self, entropy_scene_mesh_Vertex v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_3(self);
  }
  (*(entropy_scene_mesh_Vertex*)nelua_assert_deref(nelua_span_Vertex____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
void nelua_assert_line_32(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
entropy_scene_mesh_Vertex_ptr nelua_vector_Vertex____atindex(nelua_vector_Vertex__ptr self, uintptr_t pos) {
  nelua_assert_line_32((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(entropy_scene_mesh_Vertex*)nelua_assert_deref(nelua_span_Vertex____atindex(self->data, pos))));
}
intptr_t nelua_vector_Vertex____len(nelua_vector_Vertex__ptr self) {
  return (intptr_t)self->size;
}
void nelua_assert_line_33(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_4(nelua_vector_uint32__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_33((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GCAllocator_xspanrealloc_5((&self->allocator), self->data, cap);
}
void nelua_vector_uint32__push(nelua_vector_uint32__ptr self, uint32_t v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_4(self);
  }
  (*(uint32_t*)nelua_assert_deref(nelua_span_uint32____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
void nelua_assert_line_34(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
nluint32_ptr nelua_vector_uint32____atindex(nelua_vector_uint32__ptr self, uintptr_t pos) {
  nelua_assert_line_34((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(uint32_t*)nelua_assert_deref(nelua_span_uint32____atindex(self->data, pos))));
}
intptr_t nelua_vector_uint32____len(nelua_vector_uint32__ptr self) {
  return (intptr_t)self->size;
}
void nelua_vector_Vec2__reserve(nelua_vector_Vec2__ptr self, uintptr_t n) {
  if(NELUA_LIKELY((self->data.size >= n))) {
    return;
  }
  self->data = nelua_GCAllocator_xspanrealloc_6((&self->allocator), self->data, n);
}
void nelua_assert_line_35(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_5(nelua_vector_Vec2__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_35((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GCAllocator_xspanrealloc_6((&self->allocator), self->data, cap);
}
void nelua_vector_Vec2__push(nelua_vector_Vec2__ptr self, entropy_math_vec2_Vec2 v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_5(self);
  }
  (*(entropy_math_vec2_Vec2*)nelua_assert_deref(nelua_span_Vec2____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
intptr_t nelua_vector_Vec2__capacity(nelua_vector_Vec2__ptr self) {
  return (intptr_t)self->data.size;
}
void nelua_assert_line_36(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
entropy_math_vec2_Vec2_ptr nelua_vector_Vec2____atindex(nelua_vector_Vec2__ptr self, uintptr_t pos) {
  nelua_assert_line_36((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(entropy_math_vec2_Vec2*)nelua_assert_deref(nelua_span_Vec2____atindex(self->data, pos))));
}
intptr_t nelua_vector_Vec2____len(nelua_vector_Vec2__ptr self) {
  return (intptr_t)self->size;
}
void nelua_vector_uint16__reserve(nelua_vector_uint16__ptr self, uintptr_t n) {
  if(NELUA_LIKELY((self->data.size >= n))) {
    return;
  }
  self->data = nelua_GCAllocator_xspanrealloc_7((&self->allocator), self->data, n);
}
void nelua_assert_line_37(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_6(nelua_vector_uint16__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_37((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GCAllocator_xspanrealloc_7((&self->allocator), self->data, cap);
}
void nelua_vector_uint16__push(nelua_vector_uint16__ptr self, uint16_t v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_6(self);
  }
  (*(uint16_t*)nelua_assert_deref(nelua_span_uint16____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
void nelua_assert_line_38(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
nluint16_ptr nelua_vector_uint16____atindex(nelua_vector_uint16__ptr self, uintptr_t pos) {
  nelua_assert_line_38((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(uint16_t*)nelua_assert_deref(nelua_span_uint16____atindex(self->data, pos))));
}
intptr_t nelua_vector_uint16____len(nelua_vector_uint16__ptr self) {
  return (intptr_t)self->size;
}
void nelua_assert_line_39(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:140:21: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(self.size > 0, 'attempt to pop an empty vector')\n                    ^~~\n", 84, true);
    nelua_abort();
  }
}
uintptr_t nelua_vector_usize__pop(nelua_vector_usize__ptr self) {
  nelua_assert_line_39((self->size > 0), ((nlstring){(uint8_t*)"attempt to pop an empty vector", 30}));
  self->size = (self->size - 1);
  return (*(uintptr_t*)nelua_assert_deref(nelua_span_usize____atindex(self->data, self->size)));
}
intptr_t nelua_vector_usize____len(nelua_vector_usize__ptr self) {
  return (intptr_t)self->size;
}
void nelua_vector_Entity__reserve(nelua_vector_Entity__ptr self, uintptr_t n) {
  if(NELUA_LIKELY((self->data.size >= n))) {
    return;
  }
  self->data = nelua_GCAllocator_xspanrealloc_9((&self->allocator), self->data, n);
}
void nelua_assert_line_40(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_8(nelua_vector_Entity__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_40((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GCAllocator_xspanrealloc_9((&self->allocator), self->data, cap);
}
void nelua_vector_Entity__push(nelua_vector_Entity__ptr self, main_Entity v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_8(self);
  }
  (*(main_Entity*)nelua_assert_deref(nelua_span_Entity____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
intptr_t nelua_vector_Entity__capacity(nelua_vector_Entity__ptr self) {
  return (intptr_t)self->data.size;
}
void nelua_assert_line_41(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
main_Entity_ptr nelua_vector_Entity____atindex(nelua_vector_Entity__ptr self, uintptr_t pos) {
  nelua_assert_line_41((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(main_Entity*)nelua_assert_deref(nelua_span_Entity____atindex(self->data, pos))));
}
intptr_t nelua_vector_Entity____len(nelua_vector_Entity__ptr self) {
  return (intptr_t)self->size;
}
void nelua_assert_line_42(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_9(nelua_vector_Mesh__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_42((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GCAllocator_xspanrealloc_10((&self->allocator), self->data, cap);
}
void nelua_vector_Mesh__push(nelua_vector_Mesh__ptr self, entropy_scene_mesh_Mesh v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_9(self);
  }
  (*(entropy_scene_mesh_Mesh*)nelua_assert_deref(nelua_span_Mesh____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
void nelua_assert_line_43(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
entropy_scene_mesh_Mesh_ptr nelua_vector_Mesh____atindex(nelua_vector_Mesh__ptr self, uintptr_t pos) {
  nelua_assert_line_43((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(entropy_scene_mesh_Mesh*)nelua_assert_deref(nelua_span_Mesh____atindex(self->data, pos))));
}
intptr_t nelua_vector_Mesh____len(nelua_vector_Mesh__ptr self) {
  return (intptr_t)self->size;
}
void nelua_assert_line_44(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:120:17: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(cap > self.data.size, 'capacity overflow')\n                ^~~~~~~~~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_vectorT_grow_10(nelua_vector_Camera__ptr self) {
  uintptr_t cap = 1U;
  if(NELUA_LIKELY((self->data.size != 0))) {
    cap = (self->data.size * 2);
    nelua_assert_line_44((cap > self->data.size), ((nlstring){(uint8_t*)"capacity overflow", 17}));
  }
  self->data = nelua_GCAllocator_xspanrealloc_11((&self->allocator), self->data, cap);
}
void nelua_vector_Camera__push(nelua_vector_Camera__ptr self, entropy_scene_camera_Camera v) {
  uintptr_t newsize = (self->size + 1);
  if(NELUA_UNLIKELY((newsize > self->data.size))) {
    nelua_vectorT_grow_10(self);
  }
  (*(entropy_scene_camera_Camera*)nelua_assert_deref(nelua_span_Camera____atindex(self->data, self->size))) = v;
  self->size = newsize;
}
void nelua_assert_line_45(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/vector.nelua:219:15: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(pos < self.size, 'position out of bounds')\n              ^~~~~~~~~~~\n", 80, true);
    nelua_abort();
  }
}
entropy_scene_camera_Camera_ptr nelua_vector_Camera____atindex(nelua_vector_Camera__ptr self, uintptr_t pos) {
  nelua_assert_line_45((pos < self->size), ((nlstring){(uint8_t*)"position out of bounds", 22}));
  return (&(*(entropy_scene_camera_Camera*)nelua_assert_deref(nelua_span_Camera____atindex(self->data, pos))));
}
intptr_t nelua_vector_Camera____len(nelua_vector_Camera__ptr self) {
  return (intptr_t)self->size;
}
bool nelua_hasflag(uintptr_t flags, uintptr_t flag) {
  return ((flags & flag) != 0);
}
uintptr_t nelua_align_forward(uintptr_t addr, uintptr_t align) {
  return ((addr + (align - 1)) & (~(align - 1)));
}
bool nelua_GCItem_ismarked(nelua_GCItem_ptr self) {
  return nelua_hasflag(self->flags, 196608U);
}
void nelua_assert_line_46(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:127:19: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  assert(item.ptr == ptr, 'invalid unregister pointer')\n                  ^~~~~~\n", 82, true);
    nelua_abort();
  }
}
void nelua_GC_unregister_1(nelua_GC_ptr self, void* ptr, bool finalize) {
  if(NELUA_UNLIKELY((!(ptr != NULL)))) {
    return;
  }
  nelua_GCItem item = nelua_hashmap_pointer__GCItem__remove((&self->items), ptr);
  nelua_assert_line_46((item.ptr == ptr), ((nlstring){(uint8_t*)"invalid unregister pointer", 26}));
  if((!nelua_hasflag(item.flags, 131072U))) {
    self->membytes = (self->membytes - item.size);
    for(uintptr_t i = 0U, _end = self->frees.size; i < _end; i += 1) {
      if(((*(void**)nelua_assert_deref(nelua_vector_pointer____atindex((&self->frees), i))) == ptr)) {
        (*(void**)nelua_assert_deref(nelua_vector_pointer____atindex((&self->frees), i))) = (void*)NULL;
        break;
      }
    }
  }
  if((finalize && (item.finalizer != NULL))) {
    item.finalizer(ptr, item.userdata);
  }
}
void nelua_GC_markptrs(nelua_GC_ptr self, uintptr_t low, uintptr_t high) {
  uintptr_t minaddr = self->minaddr;
  uintptr_t maxaddr = self->maxaddr;
  nelua_hashmap_pointer__GCItem__ptr items = (&self->items);
  nelua_vector_GCMarkRange__push((&self->markranges), (nelua_GCMarkRange){low, high});
  while((self->markranges.size > 0)) {
    nelua_GCMarkRange range = nelua_vector_GCMarkRange__pop((&self->markranges));
    for(uintptr_t memaddr = range.low, _end = range.high; memaddr < _end; memaddr += 8) {
      uintptr_t addr = (*(uintptr_t*)nelua_assert_deref((nlusize_ptr)memaddr));
      if(((addr >= minaddr) && (addr <= maxaddr))) {
        nelua_GCItem_ptr item = nelua_hashmap_pointer__GCItem__peek(items, (void*)addr);
        if(((item != NULL) && (!nelua_GCItem_ismarked(item)))) {
          item->flags = (item->flags | 65536U);
          if((!nelua_hasflag(item->flags, 262144U))) {
            nelua_vector_GCMarkRange__push((&self->markranges), (nelua_GCMarkRange){addr, (addr + item->size)});
          }
        }
      }
    }
  }
}
void nelua_GC_markptr(nelua_GC_ptr self, void* ptr) {
  nelua_GCItem_ptr item = nelua_hashmap_pointer__GCItem__peek((&self->items), ptr);
  if(((item != NULL) && (!nelua_GCItem_ismarked(item)))) {
    item->flags = (item->flags | 65536U);
    if((!nelua_hasflag(item->flags, 262144U))) {
      uintptr_t addr = (uintptr_t)ptr;
      nelua_GC_markptrs(self, addr, (addr + item->size));
    }
  }
}
void nelua_GC_unmarkall(nelua_GC_ptr self) {
  {
    nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer _asgnret_1 = nelua_mpairs_1((&self->items));
    function_4xGnvujKcT3F2fJ4Z __fornext = _asgnret_1.r1;
    nelua_hashmap_iteratorT __forstate = _asgnret_1.r2;
    void* __fornextit = _asgnret_1.r3;
    while(true) {
      nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr _asgnret_2 = __fornext((&__forstate), __fornextit);
      bool __forcont = _asgnret_2.r1;
      void* ptr = _asgnret_2.r2;
      nelua_GCItem_ptr item = _asgnret_2.r3;
      if((!__forcont)) {
        break;
      }
      __fornextit = ptr;
      {
        item->flags = (item->flags & 18446744073709486079ULL);
      }
    }
  }
}
void nelua_GC_markroot(nelua_GC_ptr self) {
  {
    nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer _asgnret_1 = nelua_mpairs_1((&self->items));
    function_4xGnvujKcT3F2fJ4Z __fornext = _asgnret_1.r1;
    nelua_hashmap_iteratorT __forstate = _asgnret_1.r2;
    void* __fornextit = _asgnret_1.r3;
    while(true) {
      nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr _asgnret_2 = __fornext((&__forstate), __fornextit);
      bool __forcont = _asgnret_2.r1;
      void* ptr = _asgnret_2.r2;
      nelua_GCItem_ptr item = _asgnret_2.r3;
      if((!__forcont)) {
        break;
      }
      __fornextit = ptr;
      {
        if(nelua_hasflag(item->flags, 131072U)) {
          uintptr_t addr = (uintptr_t)ptr;
          nelua_GC_markptrs(self, addr, (addr + item->size));
        }
      }
    }
  }
}
void nelua_GC_markstack(nelua_GC_ptr self) {
  nelua_RegsBuf regsbuf;
  setjmp(regsbuf.regs);
#if defined(__GNUC__) || defined(__clang__)
  void* sp = __builtin_frame_address(0);
#endif
  uintptr_t low = ((self->stacktop == 0) ? (uintptr_t)(&regsbuf) : self->stacktop);
  uintptr_t high = self->stackbottom;
  if((high < low)) {
    uintptr_t _asgntmp_1 = high;
    uintptr_t _asgntmp_2 = low;
    low = _asgntmp_1;
    high = _asgntmp_2;
  }
  low = nelua_align_forward(low, 8U);
  nelua_GC_markptrs(self, low, high);
  nelua_GC_markptrs(self, (uintptr_t)(&regsbuf), ((uintptr_t)(&regsbuf) + (uintptr_t)sizeof(nelua_RegsBuf)));
#if defined(__GNUC__) || defined(__clang__)
  nelua_GC_markptr(self, sp);
#endif
}
void nelua_GC_mark(nelua_GC_ptr self) {
  nelua_GC_unmarkall(self);
  nelua_GC_markroot(self);
  if((self->stackbottom != 0)) {
    volatile function_mysnywycqLNjnvNk markstack = nelua_GC_markstack;
    markstack(self);
  }
}
void nelua_assert_line_47(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:261:20: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n        check(item ~= nilptr, 'gc item not found to finalize')\n                   ^~~~~~~~~\n", 93, true);
    nelua_abort();
  }
}
void nelua_assert_line_48(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:277:22: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(item.ptr == ptr, 'gc item not found to deallocate')\n                     ^~~~~~\n", 93, true);
    nelua_abort();
  }
}
void nelua_GC_sweep(nelua_GC_ptr self) {
  bool finalize = false;
  {
    nlmulret_function_4xGnvujKcT3F2fJ4Z_nelua_hashmap_iteratorT_nlpointer _asgnret_1 = nelua_mpairs_1((&self->items));
    function_4xGnvujKcT3F2fJ4Z __fornext = _asgnret_1.r1;
    nelua_hashmap_iteratorT __forstate = _asgnret_1.r2;
    void* __fornextit = _asgnret_1.r3;
    while(true) {
      nlmulret_nlboolean_nlpointer_nelua_GCItem_ptr _asgnret_2 = __fornext((&__forstate), __fornextit);
      bool __forcont = _asgnret_2.r1;
      void* ptr = _asgnret_2.r2;
      nelua_GCItem_ptr item = _asgnret_2.r3;
      if((!__forcont)) {
        break;
      }
      __fornextit = ptr;
      {
        if((!nelua_GCItem_ismarked(item))) {
          nelua_vector_pointer__push((&self->frees), ptr);
          if(((!finalize) && (item->finalizer != NULL))) {
            finalize = true;
          }
        }
      }
    }
  }
  if(finalize) {
    uintptr_t i = 0U;
    while((i < self->frees.size)) {
      void* ptr = (*(void**)nelua_assert_deref(nelua_vector_pointer____atindex((&self->frees), i)));
      if((ptr != NULL)) {
        nelua_GCItem_ptr item = nelua_hashmap_pointer__GCItem__peek((&self->items), ptr);
        nelua_assert_line_47((item != ((nelua_GCItem_ptr)NULL)), ((nlstring){(uint8_t*)"gc item not found to finalize", 29}));
        if(((item != NULL) && (item->finalizer != NULL))) {
          nelua_GCFinalizerCallback finalizer = item->finalizer;
          item->finalizer = (nelua_GCFinalizerCallback)NULL;
          finalizer(ptr, item->userdata);
        }
      }
      i = (i + 1);
    }
  }
  uintptr_t i = 0U;
  while((i < self->frees.size)) {
    void* ptr = (*(void**)nelua_assert_deref(nelua_vector_pointer____atindex((&self->frees), i)));
    if((ptr != NULL)) {
      nelua_GCItem item = nelua_hashmap_pointer__GCItem__remove((&self->items), ptr);
      nelua_assert_line_48((item.ptr == ptr), ((nlstring){(uint8_t*)"gc item not found to deallocate", 31}));
      if((item.ptr != NULL)) {
        self->membytes = (self->membytes - item.size);
        if((!nelua_hasflag(item.flags, 1048576U))) {
          nelua_GeneralAllocator_dealloc((&nelua_general_allocator), ptr);
        }
      }
    }
    i = (i + 1);
  }
  nelua_vector_pointer__clear((&self->frees));
}
void nelua_GC_collect(nelua_GC_ptr self) {
  if((self->collecting || (self->membytes == 0))) {
    return;
  }
  self->collecting = true;
  nelua_GC_mark(self);
  nelua_GC_sweep(self);
  self->lastmembytes = self->membytes;
  if(((self->items.size * 4) < nelua_hashmap_pointer__GCItem__bucketcount((&self->items)))) {
    nelua_hashmap_pointer__GCItem__rehash((&self->items), 0U);
  }
  self->collecting = false;
}
void nelua_GC_registerroots(nelua_GC_ptr self) {
  nelua_GC_register((&nelua_gc), (void*)(&main_world), 1080U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_positions), 8U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_velocities), 8U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_entities), 8U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_times), 24U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_context), 96U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_renderer), 64U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_cameras), 8U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_teapot_mesh), 128U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_cube_mesh), 128U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_meshes), 8U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
  nelua_GC_register((&nelua_gc), (void*)(&main_fps_list), 24U, 131072U, (function_3nQBPDMn8AvVWYLJQ)NULL, (void*)NULL);
}
bool nelua_GC_step(nelua_GC_ptr self) {
  if(((!self->collecting) && ((self->membytes * 100) >= (self->lastmembytes * self->pause)))) {
    nelua_GC_collect(self);
    return true;
  }
  return false;
}
void nelua_assert_line_49(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:382:18: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(item.ptr == nilptr, 'cannot register pointer twice')\n                 ^~~~~~~~~\n", 89, true);
    nelua_abort();
  }
}
void nelua_GC_register(nelua_GC_ptr self, void* ptr, uintptr_t size, uintptr_t flags, function_3nQBPDMn8AvVWYLJQ finalizer, void* userdata) {
  if(NELUA_UNLIKELY((!(ptr != NULL)))) {
    return;
  }
  if(NELUA_UNLIKELY((size < 8))) {
    flags = (flags | 262144U);
  }
  nelua_GCItem_ptr item = (&(*(nelua_GCItem*)nelua_assert_deref(nelua_hashmap_pointer__GCItem____atindex((&self->items), ptr))));
  nelua_assert_line_49((item->ptr == (void*)NULL), ((nlstring){(uint8_t*)"cannot register pointer twice", 29}));
  (*(nelua_GCItem*)nelua_assert_deref(item)) = (nelua_GCItem){.flags = flags, .size = size, .ptr = ptr, .finalizer = finalizer, .userdata = userdata};
  if(NELUA_LIKELY((!nelua_hasflag(flags, 131072U)))) {
    uintptr_t addr = (uintptr_t)ptr;
    uintptr_t addrhigh = (addr + size);
    if((addrhigh > self->maxaddr)) {
      self->maxaddr = addrhigh;
    }
    if((addr < self->minaddr)) {
      self->minaddr = addr;
    }
    self->membytes = (self->membytes + size);
    if(self->running) {
      nelua_GC_step(self);
    }
  }
}
void nelua_assert_line_50(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:409:47: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(oldptr ~= nilptr and newptr ~= nilptr and newsize > 0, 'invalid reregister arguments')\n                                              ^~~~~~~~~~~~~~~\n", 158, true);
    nelua_abort();
  }
}
void nelua_assert_line_51(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:413:17: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(item ~= nilptr, 'invalid reregister pointer')\n                ^~~~~~~~~\n", 84, true);
    nelua_abort();
  }
}
void nelua_assert_line_52(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:428:21: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(item.ptr ~= nilptr, 'invalid reregister pointer')\n                    ^~~~~~~~~\n", 92, true);
    nelua_abort();
  }
}
void nelua_GC_reregister(nelua_GC_ptr self, void* oldptr, void* newptr, uintptr_t newsize) {
  nelua_assert_line_50((((oldptr != (void*)NULL) && (newptr != (void*)NULL)) && (newsize > 0)), ((nlstring){(uint8_t*)"invalid reregister arguments", 28}));
  uintptr_t oldsize = 0U;
  if((newptr == oldptr)) {
    nelua_GCItem_ptr item = nelua_hashmap_pointer__GCItem__peek((&self->items), oldptr);
    nelua_assert_line_51((item != ((nelua_GCItem_ptr)NULL)), ((nlstring){(uint8_t*)"invalid reregister pointer", 26}));
    oldsize = item->size;
    item->size = newsize;
    if(NELUA_LIKELY((!nelua_hasflag(item->flags, 131072U)))) {
      if((newsize > oldsize)) {
        self->membytes = (self->membytes + (newsize - oldsize));
        if(self->running) {
          nelua_GC_step(self);
        }
      } else if((newsize < oldsize)) {
        self->membytes = (self->membytes - (oldsize - newsize));
      }
    }
  } else {
    nelua_GCItem item = nelua_hashmap_pointer__GCItem__remove((&self->items), oldptr);
    nelua_assert_line_52((item.ptr != (void*)NULL), ((nlstring){(uint8_t*)"invalid reregister pointer", 26}));
    oldsize = item.size;
    if(NELUA_LIKELY((!nelua_hasflag(item.flags, 131072U)))) {
      self->membytes = (self->membytes - oldsize);
      for(uintptr_t i = 0U, _end = self->frees.size; i < _end; i += 1) {
        if(((*(void**)nelua_assert_deref(nelua_vector_pointer____atindex((&self->frees), i))) == oldptr)) {
          (*(void**)nelua_assert_deref(nelua_vector_pointer____atindex((&self->frees), i))) = newptr;
          break;
        }
      }
    }
    nelua_GC_register(self, newptr, newsize, item.flags, item.finalizer, item.userdata);
  }
}
void nelua_GC_restart(nelua_GC_ptr self) {
  self->running = true;
}
void nelua_GC_init(nelua_GC_ptr self, void* stack) {
  self->stackbottom = (uintptr_t)stack;
  self->minaddr = 0xffffffffffffffffULL;
  self->pause = 200U;
  nelua_GC_registerroots(self);
  nelua_GC_restart(self);
}
void nelua_GC_destroy(nelua_GC_ptr self) {
  nelua_GC_unmarkall(self);
  nelua_GC_sweep(self);
  nelua_hashmap_pointer__GCItem__destroy((&self->items));
  nelua_vector_pointer__destroy((&self->frees));
  nelua_vector_GCMarkRange__destroy((&self->markranges));
  (*(nelua_GC*)nelua_assert_deref(self)) = (nelua_GC){0};
}
int main(int argc, nlcstring_ptr argv) {
  nelua_GC_init((&nelua_gc), (void*)(&argc));
  volatile function_3eqvaxExYq7cCkwLH inner_main = nelua_main;
  int ret = inner_main(argc, argv);
  nelua_GC_destroy((&nelua_gc));
  return ret;
}
void* nelua_GCAllocator_alloc_1(nelua_GCAllocator_ptr self, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  uintptr_t flags_3 = 0U;
  nelua_GCFinalizerCallback finalizer_1 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_1 = (void*)NULL;
  void* ptr = nelua_GeneralAllocator_alloc_1((&nelua_general_allocator), size, flags_3);
  nelua_GC_register((&nelua_gc), ptr, size, flags_3, finalizer_1, userdata_1);
  return ptr;
}
void* nelua_GCAllocator_alloc_2(nelua_GCAllocator_ptr self, uintptr_t size, nlniltype flags, nelua_GCFinalizerCallback finalizer, void* userdata) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  uintptr_t flags_4 = 0U;
  void* ptr = nelua_GeneralAllocator_alloc_1((&nelua_general_allocator), size, flags_4);
  nelua_GC_register((&nelua_gc), ptr, size, flags_4, finalizer, userdata);
  return ptr;
}
void* nelua_GCAllocator_alloc_3(nelua_GCAllocator_ptr self, uintptr_t size, uintptr_t flags, nelua_GCFinalizerCallback finalizer, void* userdata) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  void* ptr = nelua_GeneralAllocator_alloc_1((&nelua_general_allocator), size, flags);
  nelua_GC_register((&nelua_gc), ptr, size, flags, finalizer, userdata);
  return ptr;
}
void* nelua_GCAllocator_alloc0_1(nelua_GCAllocator_ptr self, uintptr_t size, nlniltype flags, nelua_GCFinalizerCallback finalizer, void* userdata) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  uintptr_t flags_5 = 0U;
  void* ptr = nelua_GeneralAllocator_alloc0_2((&nelua_general_allocator), size, flags_5);
  nelua_GC_register((&nelua_gc), ptr, size, flags_5, finalizer, userdata);
  return ptr;
}
void* nelua_GCAllocator_alloc0_2(nelua_GCAllocator_ptr self, uintptr_t size, uintptr_t flags, nelua_GCFinalizerCallback finalizer, void* userdata) {
  if(NELUA_UNLIKELY((size == 0))) {
    return (void*)NULL;
  }
  void* ptr = nelua_GeneralAllocator_alloc0_2((&nelua_general_allocator), size, flags);
  nelua_GC_register((&nelua_gc), ptr, size, flags, finalizer, userdata);
  return ptr;
}
void nelua_GCAllocator_dealloc(nelua_GCAllocator_ptr self, void* ptr) {
  nelua_GC_unregister_1((&nelua_gc), ptr, true);
  nelua_GeneralAllocator_dealloc((&nelua_general_allocator), ptr);
}
void* nelua_GCAllocator_realloc(nelua_GCAllocator_ptr self, void* ptr, uintptr_t newsize, uintptr_t oldsize) {
  if(NELUA_UNLIKELY((ptr == (void*)NULL))) {
    return nelua_GCAllocator_alloc_1(self, newsize, NELUA_NIL, NELUA_NIL, NELUA_NIL);
  } else if(NELUA_UNLIKELY((newsize == 0))) {
    nelua_GCAllocator_dealloc(self, ptr);
    return (void*)NULL;
  } else if(NELUA_UNLIKELY((newsize == oldsize))) {
    return ptr;
  } else {
    void* newptr = nelua_GeneralAllocator_realloc((&nelua_general_allocator), ptr, newsize, oldsize);
    if((newptr != NULL)) {
      nelua_GC_reregister((&nelua_gc), ptr, newptr, newsize);
    }
    return newptr;
  }
}
nelua_span_string_ nelua_GCAllocator_spanalloc_1(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  nelua_GCFinalizerCallback finalizer_2 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_2 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    nlstring_arr0_ptr data = ((nlstring_arr0_ptr)nelua_GCAllocator_alloc_2(self, (size * 16), NELUA_NIL, finalizer_2, userdata_2));
    if(NELUA_LIKELY((data != ((nlstring_arr0_ptr)NULL)))) {
      return (nelua_span_string_){.data = data, .size = size};
    }
  }
  return (nelua_span_string_){0};
}
nelua_span_float64_ nelua_GCAllocator_spanalloc_2(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_6 = 262144U;
  nelua_GCFinalizerCallback finalizer_3 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_3 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    nlfloat64_arr0_ptr data = ((nlfloat64_arr0_ptr)nelua_GCAllocator_alloc_3(self, (size * 8), flags_6, finalizer_3, userdata_3));
    if(NELUA_LIKELY((data != ((nlfloat64_arr0_ptr)NULL)))) {
      return (nelua_span_float64_){.data = data, .size = size};
    }
  }
  return (nelua_span_float64_){0};
}
nelua_span_Vertex_ nelua_GCAllocator_spanalloc_3(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_7 = 262144U;
  nelua_GCFinalizerCallback finalizer_4 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_4 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    entropy_scene_mesh_Vertex_arr0_ptr data = ((entropy_scene_mesh_Vertex_arr0_ptr)nelua_GCAllocator_alloc_3(self, (size * 36), flags_7, finalizer_4, userdata_4));
    if(NELUA_LIKELY((data != ((entropy_scene_mesh_Vertex_arr0_ptr)NULL)))) {
      return (nelua_span_Vertex_){.data = data, .size = size};
    }
  }
  return (nelua_span_Vertex_){0};
}
nelua_span_uint32_ nelua_GCAllocator_spanalloc_4(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_8 = 262144U;
  nelua_GCFinalizerCallback finalizer_5 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_5 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    nluint32_arr0_ptr data = ((nluint32_arr0_ptr)nelua_GCAllocator_alloc_3(self, (size * 4), flags_8, finalizer_5, userdata_5));
    if(NELUA_LIKELY((data != ((nluint32_arr0_ptr)NULL)))) {
      return (nelua_span_uint32_){.data = data, .size = size};
    }
  }
  return (nelua_span_uint32_){0};
}
nelua_span_uint8_ nelua_GCAllocator_spanalloc_5(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_9 = 262144U;
  nelua_GCFinalizerCallback finalizer_6 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_6 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    nluint8_arr0_ptr data = ((nluint8_arr0_ptr)nelua_GCAllocator_alloc_3(self, (size * 1), flags_9, finalizer_6, userdata_6));
    if(NELUA_LIKELY((data != ((nluint8_arr0_ptr)NULL)))) {
      return (nelua_span_uint8_){.data = data, .size = size};
    }
  }
  return (nelua_span_uint8_){0};
}
nelua_span_Vec2_ nelua_GCAllocator_spanalloc_6(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_10 = 262144U;
  nelua_GCFinalizerCallback finalizer_7 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_7 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    entropy_math_vec2_Vec2_arr0_ptr data = ((entropy_math_vec2_Vec2_arr0_ptr)nelua_GCAllocator_alloc_3(self, (size * 8), flags_10, finalizer_7, userdata_7));
    if(NELUA_LIKELY((data != ((entropy_math_vec2_Vec2_arr0_ptr)NULL)))) {
      return (nelua_span_Vec2_){.data = data, .size = size};
    }
  }
  return (nelua_span_Vec2_){0};
}
nelua_span_uint16_ nelua_GCAllocator_spanalloc_7(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_11 = 262144U;
  nelua_GCFinalizerCallback finalizer_8 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_8 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    nluint16_arr0_ptr data = ((nluint16_arr0_ptr)nelua_GCAllocator_alloc_3(self, (size * 2), flags_11, finalizer_8, userdata_8));
    if(NELUA_LIKELY((data != ((nluint16_arr0_ptr)NULL)))) {
      return (nelua_span_uint16_){.data = data, .size = size};
    }
  }
  return (nelua_span_uint16_){0};
}
nelua_span_Entity_ nelua_GCAllocator_spanalloc_9(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_12 = 262144U;
  nelua_GCFinalizerCallback finalizer_9 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_9 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    main_Entity_arr0_ptr data = ((main_Entity_arr0_ptr)nelua_GCAllocator_alloc_3(self, (size * 16), flags_12, finalizer_9, userdata_9));
    if(NELUA_LIKELY((data != ((main_Entity_arr0_ptr)NULL)))) {
      return (nelua_span_Entity_){.data = data, .size = size};
    }
  }
  return (nelua_span_Entity_){0};
}
nelua_span_Mesh_ nelua_GCAllocator_spanalloc_10(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  nelua_GCFinalizerCallback finalizer_10 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_10 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    entropy_scene_mesh_Mesh_arr0_ptr data = ((entropy_scene_mesh_Mesh_arr0_ptr)nelua_GCAllocator_alloc_2(self, (size * 128), NELUA_NIL, finalizer_10, userdata_10));
    if(NELUA_LIKELY((data != ((entropy_scene_mesh_Mesh_arr0_ptr)NULL)))) {
      return (nelua_span_Mesh_){.data = data, .size = size};
    }
  }
  return (nelua_span_Mesh_){0};
}
nelua_span_Camera_ nelua_GCAllocator_spanalloc_11(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_13 = 262144U;
  nelua_GCFinalizerCallback finalizer_11 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_11 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    entropy_scene_camera_Camera_arr0_ptr data = ((entropy_scene_camera_Camera_arr0_ptr)nelua_GCAllocator_alloc_3(self, (size * 36), flags_13, finalizer_11, userdata_11));
    if(NELUA_LIKELY((data != ((entropy_scene_camera_Camera_arr0_ptr)NULL)))) {
      return (nelua_span_Camera_){.data = data, .size = size};
    }
  }
  return (nelua_span_Camera_){0};
}
nelua_span_uint8_ nelua_GCAllocator_spanalloc0_1(nelua_GCAllocator_ptr self, nlniltype T, uintptr_t size, nlniltype flags, nlniltype finalizer, nlniltype userdata) {
  uintptr_t flags_14 = 262144U;
  nelua_GCFinalizerCallback finalizer_12 = (nelua_GCFinalizerCallback)NULL;
  void* userdata_12 = (void*)NULL;
  if(NELUA_LIKELY((size > 0))) {
    nluint8_arr0_ptr data = ((nluint8_arr0_ptr)nelua_GCAllocator_alloc0_2(self, (size * 1), flags_14, finalizer_12, userdata_12));
    if(NELUA_LIKELY((data != ((nluint8_arr0_ptr)NULL)))) {
      return (nelua_span_uint8_){.data = data, .size = size};
    }
  }
  return (nelua_span_uint8_){0};
}
void nelua_assert_line_53(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:759:16: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(ptr ~= nilptr, 'out of memory')\n               ^~~~~~~~~\n", 69, true);
    nelua_abort();
  }
}
nelua_sequenceimpl_string__ptr nelua_GCAllocator_new_1(nelua_GCAllocator_ptr self, nlniltype what, nlniltype size, nlniltype flags) {
  nelua_GCFinalizerCallback finalizer = (nelua_GCFinalizerCallback)NULL;
  nelua_sequenceimpl_string__ptr ptr;
  ptr = ((nelua_sequenceimpl_string__ptr)nelua_GCAllocator_alloc0_1((&nelua_gc_allocator), 24U, NELUA_NIL, finalizer, (void*)NULL));
  nelua_assert_line_53((ptr != ((nelua_sequenceimpl_string__ptr)NULL)), ((nlstring){(uint8_t*)"out of memory", 13}));
  return ptr;
}
void nelua_assert_line_54(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:759:16: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(ptr ~= nilptr, 'out of memory')\n               ^~~~~~~~~\n", 69, true);
    nelua_abort();
  }
}
nelua_listnode_Event__ptr nelua_GCAllocator_new_2(nelua_GCAllocator_ptr self, nlniltype what, nlniltype size, nlniltype flags) {
  nelua_GCFinalizerCallback finalizer = (nelua_GCFinalizerCallback)NULL;
  nelua_listnode_Event__ptr ptr;
  ptr = ((nelua_listnode_Event__ptr)nelua_GCAllocator_alloc0_1((&nelua_gc_allocator), 40U, NELUA_NIL, finalizer, (void*)NULL));
  nelua_assert_line_54((ptr != ((nelua_listnode_Event__ptr)NULL)), ((nlstring){(uint8_t*)"out of memory", 13}));
  return ptr;
}
void nelua_assert_line_55(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:762:16: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(ptr ~= nilptr, 'out of memory')\n               ^~~~~~~~~\n", 69, true);
    nelua_abort();
  }
}
nelua_FStream_ptr nelua_GCAllocator_new_3(nelua_GCAllocator_ptr self, nelua_FStream what, nlniltype size, nlniltype flags) {
  nelua_GCFinalizerCallback finalizer = (nelua_GCFinalizerCallback)NULL;
  nelua_FStream_ptr ptr;
  ptr = ((nelua_FStream_ptr)nelua_GCAllocator_alloc_2((&nelua_gc_allocator), 16U, NELUA_NIL, finalizer, (void*)NULL));
  nelua_assert_line_55((ptr != ((nelua_FStream_ptr)NULL)), ((nlstring){(uint8_t*)"out of memory", 13}));
  nelua_memory_copy((void*)ptr, (void*)(&what), 16U);
  return ptr;
}
void nelua_assert_line_56(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/allocators/gc.nelua:759:16: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(ptr ~= nilptr, 'out of memory')\n               ^~~~~~~~~\n", 69, true);
    nelua_abort();
  }
}
WGPUShaderModuleWGSLDescriptor_ptr nelua_GCAllocator_new_4(nelua_GCAllocator_ptr self, nlniltype what, nlniltype size, nlniltype flags) {
  nelua_GCFinalizerCallback finalizer = (nelua_GCFinalizerCallback)NULL;
  WGPUShaderModuleWGSLDescriptor_ptr ptr;
  ptr = ((WGPUShaderModuleWGSLDescriptor_ptr)nelua_GCAllocator_alloc0_1((&nelua_gc_allocator), 24U, NELUA_NIL, finalizer, (void*)NULL));
  nelua_assert_line_56((ptr != ((WGPUShaderModuleWGSLDescriptor_ptr)NULL)), ((nlstring){(uint8_t*)"out of memory", 13}));
  return ptr;
}
void* nelua_GCAllocator_xalloc_1(nelua_GCAllocator_ptr self, uintptr_t size, nlniltype flags) {
  void* p = nelua_GCAllocator_alloc_1(self, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
  if(NELUA_UNLIKELY(((p == (void*)NULL) && (size > 0)))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return p;
}
void* nelua_GCAllocator_realloc0(nelua_GCAllocator_ptr self, void* p, uintptr_t newsize, uintptr_t oldsize) {
  p = nelua_GCAllocator_realloc(self, p, newsize, oldsize);
  if(NELUA_LIKELY(((newsize > oldsize) && (p != (void*)NULL)))) {
    nelua_memory_zero((void*)(&((nluint8_arr0_ptr)p)[oldsize]), (newsize - oldsize));
  }
  return p;
}
void nelua_GCAllocator_spandealloc_1(nelua_GCAllocator_ptr self, nelua_span_uint8_ s) {
  if(NELUA_UNLIKELY((s.size == 0))) {
    return;
  }
  nelua_GCAllocator_dealloc(self, (void*)s.data);
}
nelua_span_uint8_ nelua_GCAllocator_spanrealloc_1(nelua_GCAllocator_ptr self, nelua_span_uint8_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_5(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  nluint8_arr0_ptr p = ((nluint8_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 1), (s.size * 1)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nluint8_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_string_ nelua_GCAllocator_spanrealloc_2(nelua_GCAllocator_ptr self, nelua_span_string_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_1(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  nlstring_arr0_ptr p = ((nlstring_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 16), (s.size * 16)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nlstring_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_float64_ nelua_GCAllocator_spanrealloc_3(nelua_GCAllocator_ptr self, nelua_span_float64_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_2(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  nlfloat64_arr0_ptr p = ((nlfloat64_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 8), (s.size * 8)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nlfloat64_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_Vertex_ nelua_GCAllocator_spanrealloc_4(nelua_GCAllocator_ptr self, nelua_span_Vertex_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_3(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  entropy_scene_mesh_Vertex_arr0_ptr p = ((entropy_scene_mesh_Vertex_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 36), (s.size * 36)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((entropy_scene_mesh_Vertex_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_uint32_ nelua_GCAllocator_spanrealloc_5(nelua_GCAllocator_ptr self, nelua_span_uint32_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_4(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  nluint32_arr0_ptr p = ((nluint32_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 4), (s.size * 4)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nluint32_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_Vec2_ nelua_GCAllocator_spanrealloc_6(nelua_GCAllocator_ptr self, nelua_span_Vec2_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_6(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  entropy_math_vec2_Vec2_arr0_ptr p = ((entropy_math_vec2_Vec2_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 8), (s.size * 8)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((entropy_math_vec2_Vec2_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_uint16_ nelua_GCAllocator_spanrealloc_7(nelua_GCAllocator_ptr self, nelua_span_uint16_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_7(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  nluint16_arr0_ptr p = ((nluint16_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 2), (s.size * 2)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nluint16_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_Entity_ nelua_GCAllocator_spanrealloc_9(nelua_GCAllocator_ptr self, nelua_span_Entity_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_9(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  main_Entity_arr0_ptr p = ((main_Entity_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 16), (s.size * 16)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((main_Entity_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_Mesh_ nelua_GCAllocator_spanrealloc_10(nelua_GCAllocator_ptr self, nelua_span_Mesh_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_10(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  entropy_scene_mesh_Mesh_arr0_ptr p = ((entropy_scene_mesh_Mesh_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 128), (s.size * 128)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((entropy_scene_mesh_Mesh_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_Camera_ nelua_GCAllocator_spanrealloc_11(nelua_GCAllocator_ptr self, nelua_span_Camera_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc_11(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  entropy_scene_camera_Camera_arr0_ptr p = ((entropy_scene_camera_Camera_arr0_ptr)nelua_GCAllocator_realloc(self, (void*)s.data, (size * 36), (s.size * 36)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((entropy_scene_camera_Camera_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
nelua_span_uint8_ nelua_GCAllocator_xspanrealloc_1(nelua_GCAllocator_ptr self, nelua_span_uint8_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_1(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_string_ nelua_GCAllocator_xspanrealloc_2(nelua_GCAllocator_ptr self, nelua_span_string_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_2(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_float64_ nelua_GCAllocator_xspanrealloc_3(nelua_GCAllocator_ptr self, nelua_span_float64_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_3(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_Vertex_ nelua_GCAllocator_xspanrealloc_4(nelua_GCAllocator_ptr self, nelua_span_Vertex_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_4(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_uint32_ nelua_GCAllocator_xspanrealloc_5(nelua_GCAllocator_ptr self, nelua_span_uint32_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_5(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_Vec2_ nelua_GCAllocator_xspanrealloc_6(nelua_GCAllocator_ptr self, nelua_span_Vec2_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_6(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_uint16_ nelua_GCAllocator_xspanrealloc_7(nelua_GCAllocator_ptr self, nelua_span_uint16_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_7(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_Entity_ nelua_GCAllocator_xspanrealloc_9(nelua_GCAllocator_ptr self, nelua_span_Entity_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_9(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_Mesh_ nelua_GCAllocator_xspanrealloc_10(nelua_GCAllocator_ptr self, nelua_span_Mesh_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_10(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_Camera_ nelua_GCAllocator_xspanrealloc_11(nelua_GCAllocator_ptr self, nelua_span_Camera_ s, uintptr_t size) {
  s = nelua_GCAllocator_spanrealloc_11(self, s, size);
  if(NELUA_UNLIKELY((s.size != size))) {
    nelua_panic_string(((nlstring){(uint8_t*)"out of memory", 13}));
  }
  return s;
}
nelua_span_uint8_ nelua_GCAllocator_spanrealloc0_1(nelua_GCAllocator_ptr self, nelua_span_uint8_ s, uintptr_t size) {
  if(NELUA_UNLIKELY(((s.size == 0) && (size > 0)))) {
    s = nelua_GCAllocator_spanalloc0_1(self, NELUA_NIL, size, NELUA_NIL, NELUA_NIL, NELUA_NIL);
    return s;
  }
  nluint8_arr0_ptr p = ((nluint8_arr0_ptr)nelua_GCAllocator_realloc0(self, (void*)s.data, (size * 1), (s.size * 1)));
  if(NELUA_UNLIKELY(((size > 0) && (p == ((nluint8_arr0_ptr)NULL))))) {
    return s;
  }
  s.data = p;
  s.size = size;
  return s;
}
void nelua_GCAllocator_delete_2(nelua_GCAllocator_ptr self, nelua_listnode_Event__ptr v) {
  nelua_GCAllocator_dealloc(self, (void*)v);
}
void nelua_GCAllocator_delete_3(nelua_GCAllocator_ptr self, nelua_FStream_ptr v) {
  nelua_GCAllocator_dealloc(self, (void*)v);
}
bool nelua_strchar_1_isalpha(uint8_t c) {
  return ((((uint32_t)c | 32) - 97U) < 26);
}
bool nelua_strchar_1_islower(uint8_t c) {
  return (((uint32_t)c - 97U) < 26);
}
bool nelua_strchar_1_isupper(uint8_t c) {
  return (((uint32_t)c - 65U) < 26);
}
bool nelua_strchar_1_isdigit(uint8_t c) {
  return (((uint32_t)c - 48U) < 10);
}
bool nelua_strchar_1_isxdigit(uint8_t c) {
  return (nelua_strchar_1_isdigit(c) || ((((uint32_t)c | 32) - 97U) < 6));
}
bool nelua_strchar_1_iscntrl(uint8_t c) {
  return (((uint32_t)c < 0x20) || (c == 0x7f));
}
bool nelua_strchar_1_isgraph(uint8_t c) {
  return (((uint32_t)c - 0x21) < 0x5e);
}
bool nelua_strchar_1_isspace(uint8_t c) {
  return ((c == 32U) || (((uint32_t)c - 9U) < 5));
}
bool nelua_strchar_1_isalnum(uint8_t c) {
  return (nelua_strchar_1_isalpha(c) || nelua_strchar_1_isdigit(c));
}
bool nelua_strchar_1_ispunct(uint8_t c) {
  return (nelua_strchar_1_isgraph(c) && (!nelua_strchar_1_isalnum(c)));
}
uint8_t nelua_strchar_1_getdigit(uint8_t c) {
  return (c - 48U);
}
uint8_t nelua_strchar_1_getbasedigit(uint8_t c) {
  uint8_t d = (c - 48U);
  if((d < 10)) {
    return d;
  }
  d = (c - 97U);
  if((d < 26)) {
    return (d + 10);
  }
  d = (c - 65U);
  if((d < 26)) {
    return (d + 10);
  }
  return 255U;
}
void nelua_assert_line_57(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strconv.nelua:38:20: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  assert(base >= 2 and base <= 36, \"base out of range\")\n                   ^~~~~~~~~~~~~~\n", 91, true);
    nelua_abort();
  }
}
nlmulret_nlboolean_nlint64 nelua_strconv_1_str2int(nlstring s, uint64_t base) {
  if((s.size == 0)) {
    return (nlmulret_nlboolean_nlint64){false, 0};
  }
  uintptr_t pos = 0U;
  while(((pos < s.size) && nelua_strchar_1_isspace(s.data[pos]))) {
    pos = (pos + 1);
  }
  if((pos >= s.size)) {
    return (nlmulret_nlboolean_nlint64){false, 0};
  }
  bool neg = false;
  if((s.data[pos] == 45U)) {
    pos = (pos + 1);
    neg = true;
  } else if((s.data[pos] == 43U)) {
    pos = (pos + 1);
  }
  if((base == 0)) {
    base = 10U;
    if(((s.data[pos] == 48U) && ((pos + 1) < s.size))) {
      uint8_t bc = s.data[(pos + 1)];
      if(((bc == 98U) || (bc == 66U))) {
        base = 2U;
        pos = (pos + 2);
      } else if(((bc == 120U) || (bc == 88U))) {
        base = 16U;
        pos = (pos + 2);
      }
    }
  }
  nelua_assert_line_57(((base >= 2) && (base <= 36)), ((nlstring){(uint8_t*)"base out of range", 17}));
  uint64_t n = 0U;
  while((pos < s.size)) {
    uint64_t x = (uint64_t)nelua_strchar_1_getbasedigit(s.data[pos]);
    if((x >= base)) {
      break;
    }
    n = ((n * base) + x);
    pos = (pos + 1);
  }
  while(((pos < s.size) && nelua_strchar_1_isspace(s.data[pos]))) {
    pos = (pos + 1);
  }
  if((pos != s.size)) {
    return (nlmulret_nlboolean_nlint64){false, 0};
  }
  if(neg) {
    n = (-n);
  }
  return (nlmulret_nlboolean_nlint64){true, (int64_t)n};
}
uintptr_t nelua_assert_bounds_nlusize(uintptr_t index, uintptr_t len) {
  if(NELUA_UNLIKELY((uintptr_t)index >= len)) {
    nelua_panic_cstring("array index: position out of bounds");
  }
  return index;
}
nlstring nelua_strconv_1_int2str_1(nluint8_arr48_ptr buf, intptr_t x, nlniltype base) {
  uintptr_t pos = 47U;
  buf->v[nelua_assert_bounds_nlusize(pos, 48)] = 0U;
  pos = (pos - 1);
  bool neg = (x < 0);
  if((x == 0)) {
    buf->v[nelua_assert_bounds_nlusize(pos, 48)] = 48U;
    pos = (pos - 1);
  } else {
    while((x != 0)) {
      intptr_t quot = (x / 10);
      intptr_t rema = (x - (quot * 10));
      if((rema < 0)) {
        rema = (-rema);
      }
      x = quot;
      buf->v[nelua_assert_bounds_nlusize(pos, 48)] = (uint8_t)(rema + 48);
      pos = (pos - 1);
    }
  }
  if(neg) {
    buf->v[nelua_assert_bounds_nlusize(pos, 48)] = 45U;
    pos = (pos - 1);
  }
  return (nlstring){.data = ((nluint8_arr0_ptr)(&buf->v[nelua_assert_bounds_nlusize((pos + 1), 48)])), .size = ((48 - pos) - 2)};
}
nlmulret_nlboolean_nlfloat64 nelua_strconv_1_str2num(nlstring s) {
  long double num = 0.0l;
  long double basenum = 10.0l;
  int32_t base = 10;
  int32_t exp = 0;
  uintptr_t pos = 0U;
  uintptr_t len = s.size;
  while(((pos < len) && nelua_strchar_1_isspace(s.data[pos]))) {
    pos = (pos + 1);
  }
  if((pos >= len)) {
    return (nlmulret_nlboolean_nlfloat64){false, 0.0};
  }
  uint8_t c = s.data[pos];
  bool neg = (c == 45U);
  bool gotdigit = false;
  bool gotfrac = false;
  if((neg || (c == 43U))) {
    pos = (pos + 1);
  }
  if((((pos + 1) < len) && (s.data[pos] == 48U))) {
    c = s.data[(pos + 1)];
    if(((c == 120U) || (c == 88U))) {
      pos = (pos + 2);
      base = 16;
      basenum = 16.0l;
    } else if(((c == 98U) || (c == 66U))) {
      pos = (pos + 2);
      base = 2;
      basenum = 2.0l;
    }
  }
  while((pos < len)) {
    c = s.data[pos];
    if((c != 48U)) {
      break;
    }
    pos = (pos + 1);
    gotdigit = true;
  }
  while((pos < len)) {
    c = s.data[pos];
    int32_t d = (int32_t)nelua_strchar_1_getbasedigit(c);
    if((d < base)) {
      num = ((num * basenum) + (long double)d);
      gotdigit = true;
      pos = (pos + 1);
      if(gotfrac) {
        exp = (exp - ((base == 16) ? 4 : 1));
      }
    } else if((c == 46U)) {
      if(gotfrac) {
        return (nlmulret_nlboolean_nlfloat64){false, 0.0};
      }
      gotfrac = true;
      pos = (pos + 1);
    } else {
      break;
    }
  }
  if((!gotdigit)) {
    return (nlmulret_nlboolean_nlfloat64){false, 0.0};
  }
  if((((pos < len) && ((base == 10) && ((c == 101U) || (c == 69U)))) || ((base != 10) && ((c == 112U) || (c == 80U))))) {
    pos = (pos + 1);
    if((pos >= len)) {
      return (nlmulret_nlboolean_nlfloat64){false, 0.0};
    }
    c = s.data[pos];
    bool negexp = (c == 45U);
    if((negexp || (c == 43U))) {
      pos = (pos + 1);
    }
    if(((pos >= len) || (nelua_strchar_1_getdigit(s.data[pos]) >= 10))) {
      return (nlmulret_nlboolean_nlfloat64){false, 0.0};
    }
    int32_t e = 0;
    while((pos < len)) {
      int32_t d = (int32_t)nelua_strchar_1_getdigit(s.data[pos]);
      if((d >= 10)) {
        break;
      }
      pos = (pos + 1);
      e = ((e * 10) + d);
      if(((e > 16500) && (base == 2))) {
        e = 16500;
      } else if(((e > 5000) && (base == 10))) {
        e = 5000;
      }
    }
    if(negexp) {
      e = (-e);
    }
    exp = (exp + e);
  }
  while(((pos < len) && nelua_strchar_1_isspace(s.data[pos]))) {
    pos = (pos + 1);
  }
  if((pos != len)) {
    return (nlmulret_nlboolean_nlfloat64){false, 0.0};
  }
  if((exp != 0)) {
    bool invscale = (exp < 0);
    long double scale = 1.0l;
    if(invscale) {
      exp = (-exp);
    }
    if((base == 10)) {
      while((exp >= 256)) {
        scale = (scale * 1e+256l);
        exp = (exp - 256);
      }
      if((exp >= 128)) {
        scale = (scale * 1e+128l);
        exp = (exp - 128);
      }
      if((exp >= 64)) {
        scale = (scale * 1e+64l);
        exp = (exp - 64);
      }
      if((exp >= 32)) {
        scale = (scale * 1e+32l);
        exp = (exp - 32);
      }
      if((exp >= 16)) {
        scale = (scale * 10000000000000000.0l);
        exp = (exp - 16);
      }
      if((exp >= 8)) {
        scale = (scale * 100000000.0l);
        exp = (exp - 8);
      }
      if((exp >= 4)) {
        scale = (scale * 10000.0l);
        exp = (exp - 4);
      }
      if((exp >= 2)) {
        scale = (scale * 100.0l);
        exp = (exp - 2);
      }
      if((exp >= 1)) {
        scale = (scale * 10.0l);
        exp = (exp - 1);
      }
    } else {
      long double te = 2.0l;
      while(true) {
        if(((exp & 1) == 1)) {
          scale = (scale * te);
        }
        exp = (exp >> 1);
        if((exp == 0)) {
          break;
        }
        te = (te * te);
      }
    }
    if(invscale) {
      scale = (1 / scale);
    }
    num = (num * scale);
  }
  if(neg) {
    num = (-num);
  }
  return (nlmulret_nlboolean_nlfloat64){true, (double)num};
}
nlstring nelua_strconv_1_num2str_1(nluint8_arr64_ptr buf, float x) {
  volatile double n = (double)x;
  {
    nelua_UF2I pinf = (nelua_UF2I){.f = NELUA_INFF};
    nelua_UF2I ninf = (nelua_UF2I){.f = -NELUA_INFF};
    volatile double huge = NELUA_INF;
    nelua_UF2I ux = (nelua_UF2I){.f = (float)n};
    if((((ux.i & ninf.i) == ninf.i) && (ux.i != ninf.i))) {
      return ((nlstring){(uint8_t*)"-nan", 4});
    } else if(((((ux.i & pinf.i) == pinf.i) && (ux.i != pinf.i)) && (ux.i != ninf.i))) {
      return ((nlstring){(uint8_t*)"nan", 3});
    } else if((n == 0)) {
      return ((ux.i != 0) ? ((nlstring){(uint8_t*)"-0.0", 4}) : ((nlstring){(uint8_t*)"0.0", 3}));
    } else if((n == huge)) {
      return ((nlstring){(uint8_t*)"inf", 3});
    } else if((n == (-huge))) {
      return ((nlstring){(uint8_t*)"-inf", 4});
    }
  }
  uintptr_t pos = 63U;
  buf->v[nelua_assert_bounds_nlusize(pos, 64)] = 0U;
  pos = (pos - 1);
  bool gotdigit = false;
  bool gotexpo = false;
  bool neg = (n < 0);
  if(neg) {
    n = (-n);
  }
  int32_t expo = 6;
  while((n <= 1e-249)) {
    n = (n * 1e+256);
    expo = (expo - 256);
  }
  if((n <= 1e-121)) {
    n = (n * 1e+128);
    expo = (expo - 128);
  }
  if((n <= 1e-57)) {
    n = (n * 1e+64);
    expo = (expo - 64);
  }
  if((n <= 1e-25)) {
    n = (n * 1e+32);
    expo = (expo - 32);
  }
  if((n <= 1e-9)) {
    n = (n * 10000000000000000.0);
    expo = (expo - 16);
  }
  if((n <= 0.1)) {
    n = (n * 100000000.0);
    expo = (expo - 8);
  }
  if((n <= 1000.0)) {
    n = (n * 10000.0);
    expo = (expo - 4);
  }
  if((n <= 100000.0)) {
    n = (n * 100.0);
    expo = (expo - 2);
  }
  if((n <= 1000000.0)) {
    n = (n * 10.0);
    expo = (expo - 1);
  }
  while((n >= 1e+263)) {
    n = (n * 1e-256);
    expo = (expo + 256);
  }
  if((n >= 1e+135)) {
    n = (n * 1e-128);
    expo = (expo + 128);
  }
  if((n >= 1e+71)) {
    n = (n * 1e-64);
    expo = (expo + 64);
  }
  if((n >= 1e+39)) {
    n = (n * 1e-32);
    expo = (expo + 32);
  }
  if((n >= 1e+23)) {
    n = (n * 1e-16);
    expo = (expo + 16);
  }
  if((n >= 1000000000000000.0)) {
    n = (n * 1e-8);
    expo = (expo + 8);
  }
  if((n >= 100000000000.0)) {
    n = (n * 0.0001);
    expo = (expo + 4);
  }
  if((n >= 1000000000.0)) {
    n = (n * 0.01);
    expo = (expo + 2);
  }
  if((n >= 100000000.0)) {
    n = (n * 0.1);
    expo = (expo + 1);
  }
  if((n >= 10000000.0)) {
    n = (n * 0.1);
    expo = (expo + 1);
  }
  n = (n + 0.5);
  uint32_t frac = (uint32_t)n;
  uint32_t fracmax = 1U;
  for(int32_t i = 0; i < 7; i += 1) {
    fracmax = (fracmax * 10);
  }
  while((frac >= fracmax)) {
    frac = (frac / 10);
    expo = (expo + 1);
  }
  if(((expo < -4) || (expo >= 7))) {
    bool negexpo = (expo < 0);
    if(negexpo) {
      expo = (-expo);
    }
    bool expozero = (expo < 10);
    while((expo != 0)) {
      buf->v[nelua_assert_bounds_nlusize(pos, 64)] = ((uint8_t)(expo % 10) + 48U);
      expo = (expo / 10);
      pos = (pos - 1);
    }
    if(expozero) {
      buf->v[nelua_assert_bounds_nlusize(pos, 64)] = 48U;
      pos = (pos - 1);
    }
    buf->v[nelua_assert_bounds_nlusize(pos, 64)] = (negexpo ? 45U : 43U);
    buf->v[nelua_assert_bounds_nlusize((pos - 1), 64)] = 101U;
    pos = (pos - 2);
    gotexpo = true;
  }
  for(int32_t i = 6, _end = ((expo <= 0) ? expo : 0); i >= _end; i += -1) {
    if(((i == expo) && (!(gotexpo && (!gotdigit))))) {
      if((!gotdigit)) {
        buf->v[nelua_assert_bounds_nlusize(pos, 64)] = 48U;
        pos = (pos - 1);
        gotdigit = true;
      }
      buf->v[nelua_assert_bounds_nlusize(pos, 64)] = 46U;
      pos = (pos - 1);
    }
    uint32_t rema = (frac % 10);
    frac = (frac / 10);
    if((gotdigit || (rema != 0))) {
      buf->v[nelua_assert_bounds_nlusize(pos, 64)] = ((uint8_t)rema + 48U);
      pos = (pos - 1);
      gotdigit = true;
    }
  }
  while((((pos < 62) && (buf->v[nelua_assert_bounds_nlusize((pos + 1), 64)] == 48U)) && (buf->v[nelua_assert_bounds_nlusize((pos + 2), 64)] != 46U))) {
    pos = (pos + 1);
  }
  if(neg) {
    buf->v[nelua_assert_bounds_nlusize(pos, 64)] = 45U;
    pos = (pos - 1);
  }
  return (nlstring){.data = ((nluint8_arr0_ptr)(&buf->v[nelua_assert_bounds_nlusize((pos + 1), 64)])), .size = ((64 - pos) - 2)};
}
void nelua_stringbuilderT_destroy(nelua_stringbuilderT_ptr self) {
  nelua_GCAllocator_spandealloc_1((&self->allocator), self->data);
  self->data = (nelua_span_uint8_){0};
  self->size = 0U;
}
bool nelua_stringbuilderT_grow(nelua_stringbuilderT_ptr self, uintptr_t newsize) {
  uintptr_t needed = (newsize + 1);
  uintptr_t cap = self->data.size;
  if((needed <= cap)) {
    return true;
  }
  if((cap == 0)) {
    cap = 16U;
  }
  while((cap < needed)) {
    cap = (cap * 2);
    if((cap <= 16U)) {
      return false;
    }
  }
  self->data = nelua_GCAllocator_spanrealloc0_1((&self->allocator), self->data, cap);
  if((self->data.size != cap)) {
    self->data = nelua_GCAllocator_spanrealloc0_1((&self->allocator), self->data, needed);
  }
  return (needed <= self->data.size);
}
nelua_span_uint8_ nelua_stringbuilderT_prepare(nelua_stringbuilderT_ptr self, uintptr_t n) {
  if((!nelua_stringbuilderT_grow(self, (self->size + n)))) {
    return (nelua_span_uint8_){0};
  }
  return (nelua_span_uint8_){.data = ((nluint8_arr0_ptr)(&(*(uint8_t*)nelua_assert_deref(nelua_span_uint8____atindex(self->data, self->size))))), .size = ((self->data.size - self->size) - 1)};
}
void nelua_assert_line_58(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/stringbuilder.nelua:150:19: runtime error: ", 115, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(newsize <= self.data.size, 'not enough space in string buffer')\n                  ^~~~~~~~~~~~~~~~~\n", 111, true);
    nelua_abort();
  }
}
void nelua_stringbuilderT_commit(nelua_stringbuilderT_ptr self, uintptr_t n) {
  uintptr_t newsize = (self->size + n);
  nelua_assert_line_58((newsize <= self->data.size), ((nlstring){(uint8_t*)"not enough space in string buffer", 33}));
  self->size = newsize;
}
bool nelua_stringbuilderT_writebyte_1(nelua_stringbuilderT_ptr self, uint8_t c, nlniltype n) {
  nelua_span_uint8_ p = nelua_stringbuilderT_prepare(self, 1U);
  if(NELUA_UNLIKELY(nelua_span_uint8__empty(p))) {
    return false;
  }
  p.data[0] = c;
  self->size = (self->size + 1);
  return true;
}
nlstring nelua_stringbuilderT_promote(nelua_stringbuilderT_ptr self) {
  if(NELUA_UNLIKELY((self->size == 0))) {
    nelua_stringbuilderT_destroy(self);
    return (nlstring){0};
  }
  uintptr_t size = self->size;
  nelua_span_uint8_ data = nelua_GCAllocator_xspanrealloc_1((&self->allocator), self->data, (size + 1));
  (*(uint8_t*)nelua_assert_deref(nelua_span_uint8____atindex(data, size))) = 0U;
  self->data = (nelua_span_uint8_){0};
  self->size = 0U;
  return (nlstring){.data = data.data, .size = size};
}
void nelua_assert_line_59(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/string.nelua:35:14: runtime error: ", 107, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  check(size > 0, 'attempt to create an empty string')\n             ^~~\n", 73, true);
    nelua_abort();
  }
}
nlstring nelua_nlstring_create(uintptr_t size) {
  nelua_assert_line_59((size > 0), ((nlstring){(uint8_t*)"attempt to create an empty string", 33}));
  nlstring s = (nlstring){.data = ((nluint8_arr0_ptr)nelua_GCAllocator_xalloc_1((&nelua_gc_allocator), (size + 1), NELUA_NIL)), .size = size};
  s.data[size] = 0U;
  return s;
}
void nelua_nlstring_destroy(nlstring_ptr self) {
  if(NELUA_UNLIKELY((self->size == 0))) {
    return;
  }
  nelua_GCAllocator_dealloc((&nelua_gc_allocator), (void*)self->data);
  self->data = ((nluint8_arr0_ptr)NULL);
  self->size = 0U;
}
nlstring nelua_nlstring_copy(nlstring s) {
  nlstring clone = (nlstring){0};
  if(NELUA_UNLIKELY((s.size == 0))) {
    return clone;
  }
  clone.data = ((nluint8_arr0_ptr)nelua_GCAllocator_xalloc_1((&nelua_gc_allocator), (s.size + 1), NELUA_NIL));
  nelua_memory_copy((void*)clone.data, (void*)s.data, s.size);
  clone.data[s.size] = 0U;
  clone.size = s.size;
  return clone;
}
nlstring nelua_nlstring_subview_1(nlstring s, intptr_t i, intptr_t j) {
  intptr_t size = (intptr_t)s.size;
  if(NELUA_UNLIKELY((size == 0))) {
    return (nlstring){0};
  }
  if(NELUA_UNLIKELY((i < 0))) {
    i = ((size + i) + 1);
  }
  if(NELUA_UNLIKELY((i <= 0))) {
    i = 1;
  }
  if(NELUA_UNLIKELY((j < 0))) {
    j = ((size + j) + 1);
  }
  if(NELUA_UNLIKELY((j > size))) {
    j = size;
  }
  if(NELUA_UNLIKELY(((i == 1) && (j == size)))) {
    return s;
  }
  if(NELUA_UNLIKELY((i > j))) {
    return (nlstring){0};
  }
  uintptr_t subsize = (uintptr_t)((j - i) + 1);
  if(NELUA_UNLIKELY((subsize == 0))) {
    return (nlstring){0};
  }
  return (nlstring){.data = ((nluint8_arr0_ptr)(&s.data[(i - 1)])), .size = subsize};
}
intptr_t nelua_nlstring___len(nlstring a) {
  return (intptr_t)a.size;
}
nlstring nelua_nlstring___concat_2(float a, nlstring b) {
  nlstring a_2 = nelua_tostring_2(a);
  if((a_2.size == 0)) {
    nlstring _ret_1 = nelua_nlstring_copy(b);
    { /* defer */
      nelua_nlstring_destroy((&a_2));
    }
    return _ret_1;
  } else if((b.size == 0)) {
    nlstring _ret_2 = nelua_nlstring_copy(a_2);
    { /* defer */
      nelua_nlstring_destroy((&a_2));
    }
    return _ret_2;
  }
  nlstring s = nelua_nlstring_create((a_2.size + b.size));
  nelua_memory_copy((void*)s.data, (void*)a_2.data, a_2.size);
  nelua_memory_copy((void*)(&s.data[a_2.size]), (void*)b.data, b.size);
  { /* defer */
    nelua_nlstring_destroy((&a_2));
  }
  return s;
}
nlstring nelua_nlstring___concat_6(nlstring a, char* b) {
  nlstring b_1 = nelua_tostring_1(b);
  if((a.size == 0)) {
    nlstring _ret_1 = nelua_nlstring_copy(b_1);
    { /* defer */
      nelua_nlstring_destroy((&b_1));
    }
    return _ret_1;
  } else if((b_1.size == 0)) {
    nlstring _ret_2 = nelua_nlstring_copy(a);
    { /* defer */
      nelua_nlstring_destroy((&b_1));
    }
    return _ret_2;
  }
  nlstring s = nelua_nlstring_create((a.size + b_1.size));
  nelua_memory_copy((void*)s.data, (void*)a.data, a.size);
  nelua_memory_copy((void*)(&s.data[a.size]), (void*)b_1.data, b_1.size);
  { /* defer */
    nelua_nlstring_destroy((&b_1));
  }
  return s;
}
nlstring nelua_nlstring___concat_7(nlstring a, nlstring b) {
  if((a.size == 0)) {
    return nelua_nlstring_copy(b);
  } else if((b.size == 0)) {
    return nelua_nlstring_copy(a);
  }
  nlstring s = nelua_nlstring_create((a.size + b.size));
  nelua_memory_copy((void*)s.data, (void*)a.data, a.size);
  nelua_memory_copy((void*)(&s.data[a.size]), (void*)b.data, b.size);
  return s;
}
nlstring nelua_nlstring___concat_8(WGPULogLevel a, nlstring b) {
  nlstring a_3 = nelua_tostring_6(a);
  if((a_3.size == 0)) {
    nlstring _ret_1 = nelua_nlstring_copy(b);
    { /* defer */
      nelua_nlstring_destroy((&a_3));
    }
    return _ret_1;
  } else if((b.size == 0)) {
    nlstring _ret_2 = nelua_nlstring_copy(a_3);
    { /* defer */
      nelua_nlstring_destroy((&a_3));
    }
    return _ret_2;
  }
  nlstring s = nelua_nlstring_create((a_3.size + b.size));
  nelua_memory_copy((void*)s.data, (void*)a_3.data, a_3.size);
  nelua_memory_copy((void*)(&s.data[a_3.size]), (void*)b.data, b.size);
  { /* defer */
    nelua_nlstring_destroy((&a_3));
  }
  return s;
}
bool nelua_nlstring___eq(nlstring a, nlstring b) {
  return ((a.size == b.size) && (((a.data == b.data) || (a.size == 0)) || nelua_memory_equals((void*)a.data, (void*)b.data, a.size)));
}
bool nelua_StrPattCapture_is_unfinished(nelua_StrPattCapture_ptr self) {
  return (self->len == -1);
}
bool nelua_StrPattCapture_is_position(nelua_StrPattCapture_ptr self) {
  return (self->len == -2);
}
bool nelua_match_has_pattern_specials(nlstring pattern) {
  for(uintptr_t i = 0U, _end = pattern.size; i < _end; i += 1) {
    switch(pattern.data[i]) {
      case 94U:
      case 36U:
      case 42U:
      case 43U:
      case 63U:
      case 46U:
      case 40U:
      case 91U:
      case 37U:
      case 45U: {
        return true;
      }
    }
  }
  return false;
}
bool nelua_match_has_pattern_anchor(nlstring pattern) {
  return ((pattern.size > 0) && (pattern.data[0] == 94U));
}
nelua_StrPatt_1 nelua_StrPatt_1_create(nlstring source, nlstring pattern, bool plain) {
  if((!nelua_match_has_pattern_specials(pattern))) {
    plain = false;
  }
  bool anchor = ((!plain) && nelua_match_has_pattern_anchor(pattern));
  return (nelua_StrPatt_1){.source = source, .pattern = pattern, .plain = plain, .anchor = anchor, .depth = 32};
}
intptr_t nelua_assert_bounds_nlisize(intptr_t index, uintptr_t len) {
  if(NELUA_UNLIKELY((uintptr_t)index >= len || index < 0)) {
    nelua_panic_cstring("array index: position out of bounds");
  }
  return index;
}
void nelua_StrPatt_1_reset_captures(nelua_StrPatt_1_ptr self) {
  for(intptr_t i = 0, _end = self->numcaptures; i < _end; i += 1) {
    self->capture[nelua_assert_bounds_nlisize(i, 32)] = (nelua_StrPattCapture){0};
  }
  self->numcaptures = 0;
}
nlmulret_nlboolean_nlstring_nelua_StrPattCapture nelua_StrPatt_1_get_capture(nelua_StrPatt_1_ptr self, intptr_t i) {
  if(NELUA_UNLIKELY(((i < 0) || (i >= self->numcaptures)))) {
    return (nlmulret_nlboolean_nlstring_nelua_StrPattCapture){false, ((nlstring){(uint8_t*)"invalid capture index", 21}), (nelua_StrPattCapture){0}};
  }
  if(NELUA_UNLIKELY(nelua_StrPattCapture_is_unfinished((&self->capture[nelua_assert_bounds_nlisize(i, 32)])))) {
    return (nlmulret_nlboolean_nlstring_nelua_StrPattCapture){false, ((nlstring){(uint8_t*)"unfinished capture", 18}), (nelua_StrPattCapture){0}};
  }
  nelua_StrPattCapture capture = self->capture[nelua_assert_bounds_nlisize(i, 32)];
  if((!nelua_StrPattCapture_is_position((&self->capture[nelua_assert_bounds_nlisize(i, 32)])))) {
    nlstring capstr = (nlstring){.data = ((nluint8_arr0_ptr)(&self->source.data[self->capture[nelua_assert_bounds_nlisize(i, 32)].init])), .size = (uintptr_t)self->capture[nelua_assert_bounds_nlisize(i, 32)].len};
    return (nlmulret_nlboolean_nlstring_nelua_StrPattCapture){true, capstr, capture};
  } else {
    return (nlmulret_nlboolean_nlstring_nelua_StrPattCapture){true, ((nlstring){(uint8_t*)"", 0}), capture};
  }
}
bool nelua_match_class(uint8_t c, uint8_t cl) {
  bool res = false;
  switch(cl) {
    case 97U: {
      res = nelua_strchar_1_isalpha(c);
      break;
    }
    case 65U: {
      res = (!nelua_strchar_1_isalpha(c));
      break;
    }
    case 99U: {
      res = nelua_strchar_1_iscntrl(c);
      break;
    }
    case 67U: {
      res = (!nelua_strchar_1_iscntrl(c));
      break;
    }
    case 100U: {
      res = nelua_strchar_1_isdigit(c);
      break;
    }
    case 68U: {
      res = (!nelua_strchar_1_isdigit(c));
      break;
    }
    case 103U: {
      res = nelua_strchar_1_isgraph(c);
      break;
    }
    case 71U: {
      res = (!nelua_strchar_1_isgraph(c));
      break;
    }
    case 108U: {
      res = nelua_strchar_1_islower(c);
      break;
    }
    case 76U: {
      res = (!nelua_strchar_1_islower(c));
      break;
    }
    case 112U: {
      res = nelua_strchar_1_ispunct(c);
      break;
    }
    case 80U: {
      res = (!nelua_strchar_1_ispunct(c));
      break;
    }
    case 115U: {
      res = nelua_strchar_1_isspace(c);
      break;
    }
    case 83U: {
      res = (!nelua_strchar_1_isspace(c));
      break;
    }
    case 117U: {
      res = nelua_strchar_1_isupper(c);
      break;
    }
    case 85U: {
      res = (!nelua_strchar_1_isupper(c));
      break;
    }
    case 119U: {
      res = nelua_strchar_1_isalnum(c);
      break;
    }
    case 87U: {
      res = (!nelua_strchar_1_isalnum(c));
      break;
    }
    case 120U: {
      res = nelua_strchar_1_isxdigit(c);
      break;
    }
    case 88U: {
      res = (!nelua_strchar_1_isxdigit(c));
      break;
    }
    case 122U: {
      res = (c == 0);
      break;
    }
    case 90U: {
      res = (c != 0);
      break;
    }
    default: {
      return (cl == c);
    }
  }
  return res;
}
void nelua_assert_line_60(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strpatt.nelua:135:16: runtime error: ", 116, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      assert(p ~= #ms.pattern, \"malformed pattern (ends with '%')\")\n               ^~~~~~~~~~~~~~\n", 99, true);
    nelua_abort();
  }
}
void nelua_assert_line_61(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strpatt.nelua:142:18: runtime error: ", 116, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n        assert(p ~= #ms.pattern, \"malformed pattern (missing ']')\")\n                 ^~~~~~~~~~~~~~\n", 101, true);
    nelua_abort();
  }
}
intptr_t nelua_match_class_end(nelua_StrPatt_1_ptr ms_1, intptr_t p_1) {
  uint8_t c = ms_1->pattern.data[p_1];
  p_1 = (p_1 + 1);
  switch(c) {
    case 37U: {
      nelua_assert_line_60((p_1 != nelua_nlstring___len(ms_1->pattern)), ((nlstring){(uint8_t*)"malformed pattern (ends with '%')", 33}));
      p_1 = (p_1 + 1);
      break;
    }
    case 91U: {
      if((ms_1->pattern.data[p_1] == 94U)) {
        p_1 = (p_1 + 1);
      }
      {
        bool _repeat_stop;
        do {
          nelua_assert_line_61((p_1 != nelua_nlstring___len(ms_1->pattern)), ((nlstring){(uint8_t*)"malformed pattern (missing ']')", 31}));
          c = ms_1->pattern.data[p_1];
          p_1 = (p_1 + 1);
          if(((c == 37U) && (p_1 < nelua_nlstring___len(ms_1->pattern)))) {
            p_1 = (p_1 + 1);
          }
          _repeat_stop = (ms_1->pattern.data[p_1] == 93U);
        } while(!_repeat_stop);
      }
      p_1 = (p_1 + 1);
      break;
    }
  }
  return p_1;
}
bool nelua_match_bracket_class(nelua_StrPatt_1_ptr ms_2, uint8_t c, intptr_t p_2, intptr_t ep) {
  bool sig = true;
  if((ms_2->pattern.data[(p_2 + 1)] == 94U)) {
    sig = false;
    p_2 = (p_2 + 1);
  }
  p_2 = (p_2 + 1);
  while((p_2 < ep)) {
    if((ms_2->pattern.data[p_2] == 37U)) {
      p_2 = (p_2 + 1);
      if(nelua_match_class(c, ms_2->pattern.data[p_2])) {
        return sig;
      }
    } else if(((ms_2->pattern.data[(p_2 + 1)] == 45U) && ((p_2 + 2) < ep))) {
      p_2 = (p_2 + 2);
      if(((ms_2->pattern.data[(p_2 - 2)] <= c) && (c <= ms_2->pattern.data[p_2]))) {
        return sig;
      }
    } else if((ms_2->pattern.data[p_2] == c)) {
      return sig;
    }
    p_2 = (p_2 + 1);
  }
  return (!sig);
}
bool nelua_match_single(nelua_StrPatt_1_ptr ms_3, intptr_t s_1, intptr_t p_3, intptr_t ep) {
  if((s_1 >= nelua_nlstring___len(ms_3->source))) {
    return false;
  } else {
    uint8_t c = ms_3->source.data[s_1];
    uint8_t pc = ms_3->pattern.data[p_3];
    switch(pc) {
      case 46U: {
        return true;
      }
      case 37U: {
        return nelua_match_class(c, ms_3->pattern.data[(p_3 + 1)]);
      }
      case 91U: {
        return nelua_match_bracket_class(ms_3, c, p_3, (ep - 1));
      }
      default: {
        return (pc == c);
      }
    }
  }
}
void nelua_assert_line_62(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strpatt.nelua:196:14: runtime error: ", 116, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(p < #ms.pattern - 1, \"malformed pattern (missing arguments to '%b')\")\n             ^~~~~~~~~~~~~~~~~\n", 113, true);
    nelua_abort();
  }
}
intptr_t nelua_match_balance(nelua_StrPatt_1_ptr ms_4, intptr_t s_2, intptr_t p_4) {
  nelua_assert_line_62((p_4 < (nelua_nlstring___len(ms_4->pattern) - 1)), ((nlstring){(uint8_t*)"malformed pattern (missing arguments to '%b')", 45}));
  if(((s_2 >= nelua_nlstring___len(ms_4->source)) || (ms_4->source.data[s_2] != ms_4->pattern.data[p_4]))) {
    return -1;
  } else {
    uint8_t b = ms_4->pattern.data[p_4];
    uint8_t e = ms_4->pattern.data[(p_4 + 1)];
    intptr_t cont = 1;
    s_2 = (s_2 + 1);
    while((s_2 < nelua_nlstring___len(ms_4->source))) {
      if((ms_4->source.data[s_2] == e)) {
        cont = (cont - 1);
        if((cont == 0)) {
          return (s_2 + 1);
        }
      } else if((ms_4->source.data[s_2] == b)) {
        cont = (cont + 1);
      }
      s_2 = (s_2 + 1);
    }
  }
  return -1;
}
intptr_t nelua_match_max_expand(nelua_StrPatt_1_ptr ms_5, intptr_t s_3, intptr_t p_5, intptr_t ep) {
  intptr_t i = 0;
  while(nelua_match_single(ms_5, (s_3 + i), p_5, ep)) {
    i = (i + 1);
  }
  while((i >= 0)) {
    intptr_t res = nelua_StrPatt_1__match(ms_5, (s_3 + i), (ep + 1));
    if((res != -1)) {
      return res;
    } else {
      i = (i - 1);
    }
  }
  return -1;
}
intptr_t nelua_match_min_expand(nelua_StrPatt_1_ptr ms_6, intptr_t s_4, intptr_t p_6, intptr_t ep) {
  while(true) {
    intptr_t res = nelua_StrPatt_1__match(ms_6, s_4, (ep + 1));
    if((res != -1)) {
      return res;
    } else if(nelua_match_single(ms_6, s_4, p_6, ep)) {
      s_4 = (s_4 + 1);
    } else {
      break;
    }
  }
  return -1;
}
void nelua_assert_line_63(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strpatt.nelua:251:24: runtime error: ", 116, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(numcaptures < #ms.capture, \"too many captures\")\n                       ^~~~~~~~~~~~~\n", 97, true);
    nelua_abort();
  }
}
intptr_t nelua_match_start_capture(nelua_StrPatt_1_ptr ms_7, intptr_t s_5, intptr_t p_7, intptr_t what) {
  intptr_t numcaptures = ms_7->numcaptures;
  nelua_assert_line_63((numcaptures < 32), ((nlstring){(uint8_t*)"too many captures", 17}));
  ms_7->capture[nelua_assert_bounds_nlisize(numcaptures, 32)].init = s_5;
  ms_7->capture[nelua_assert_bounds_nlisize(numcaptures, 32)].len = what;
  ms_7->numcaptures = (numcaptures + 1);
  intptr_t res = nelua_StrPatt_1__match(ms_7, s_5, p_7);
  if((res == -1)) {
    ms_7->capture[nelua_assert_bounds_nlisize(numcaptures, 32)] = (nelua_StrPattCapture){0};
    ms_7->numcaptures = (ms_7->numcaptures - 1);
  }
  return res;
}
void nelua_assert_line_64(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strpatt.nelua:271:14: runtime error: ", 116, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(l ~= -1, \"invalid pattern capture\")\n             ^~~~~\n", 67, true);
    nelua_abort();
  }
}
intptr_t nelua_match_end_capture(nelua_StrPatt_1_ptr ms_8, intptr_t s_6, intptr_t p_8) {
  intptr_t l = -1;
  for(intptr_t numcaptures = (ms_8->numcaptures - 1); numcaptures >= 0; numcaptures += -1) {
    if((ms_8->capture[nelua_assert_bounds_nlisize(numcaptures, 32)].len == -1)) {
      l = numcaptures;
      break;
    }
  }
  nelua_assert_line_64((l != -1), ((nlstring){(uint8_t*)"invalid pattern capture", 23}));
  ms_8->capture[nelua_assert_bounds_nlisize(l, 32)].len = (s_6 - ms_8->capture[nelua_assert_bounds_nlisize(l, 32)].init);
  intptr_t res = nelua_StrPatt_1__match(ms_8, s_6, p_8);
  if((res == -1)) {
    ms_8->capture[nelua_assert_bounds_nlisize(l, 32)].len = -1;
  }
  return res;
}
void nelua_assert_line_65(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strpatt.nelua:282:42: runtime error: ", 116, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(l >= 0 and l < ms.numcaptures and ms.capture[l].len ~= CAP_UNFINISHED, \"invalid capture index\")\n                                         ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", 189, true);
    nelua_abort();
  }
}
intptr_t nelua_match_capture(nelua_StrPatt_1_ptr ms_9, intptr_t s_7, intptr_t l) {
  l = (intptr_t)(l - 49U);
  nelua_assert_line_65((((l >= 0) && (l < ms_9->numcaptures)) && (ms_9->capture[nelua_assert_bounds_nlisize(l, 32)].len != -1)), ((nlstring){(uint8_t*)"invalid capture index", 21}));
  uintptr_t len = (uintptr_t)ms_9->capture[nelua_assert_bounds_nlisize(l, 32)].len;
  if((((uintptr_t)(nelua_nlstring___len(ms_9->source) - s_7) >= len) && (nelua_memory_compare((void*)(&ms_9->source.data[ms_9->capture[nelua_assert_bounds_nlisize(l, 32)].init]), (void*)(&ms_9->source.data[s_7]), len) == 0))) {
    return (intptr_t)(int64_t)(s_7 + len);
  }
  return -1;
}
void nelua_assert_line_66(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strpatt.nelua:292:19: runtime error: ", 116, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  assert(ms.depth > 0, 'pattern too complex')\n                  ^~~\n", 69, true);
    nelua_abort();
  }
}
void nelua_assert_line_67(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/detail/strpatt.nelua:324:35: runtime error: ", 116, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n        assert(ms.pattern.data[p] == '['_b, \"missing '[' after '%f' in pattern\")\n                                  ^~~~~~~~\n", 125, true);
    nelua_abort();
  }
}
intptr_t nelua_StrPatt_1__match(nelua_StrPatt_1_ptr ms, intptr_t s, intptr_t p) {
  ms->depth = (ms->depth - 1);
  nelua_assert_line_66((ms->depth > 0), ((nlstring){(uint8_t*)"pattern too complex", 19}));
  while((p < nelua_nlstring___len(ms->pattern))) {
    switch(ms->pattern.data[p]) {
      case 40U: {
        if((ms->pattern.data[(p + 1)] == 41U)) {
          s = nelua_match_start_capture(ms, s, (p + 2), -2);
        } else {
          s = nelua_match_start_capture(ms, s, (p + 1), -1);
        }
        goto _breaklabel_1;
      }
      case 41U: {
        s = nelua_match_end_capture(ms, s, (p + 1));
        goto _breaklabel_1;
      }
      case 36U: {
        if(((p + 1) == nelua_nlstring___len(ms->pattern))) {
          if((s != nelua_nlstring___len(ms->source))) {
            s = -1;
          }
          goto _breaklabel_1;
        }
        break;
      }
      case 37U: {
        switch(ms->pattern.data[(p + 1)]) {
          case 98U: {
            s = nelua_match_balance(ms, s, (p + 2));
            if((s != -1)) {
              p = (p + 4);
              continue;
            }
            goto _breaklabel_1;
          }
          case 102U: {
            p = (p + 2);
            nelua_assert_line_67((ms->pattern.data[p] == 91U), ((nlstring){(uint8_t*)"missing '[' after '%f' in pattern", 33}));
            intptr_t ep = nelua_match_class_end(ms, p);
            uint8_t previous = (((s == 0) && (s < nelua_nlstring___len(ms->source))) ? 0x0U : ms->source.data[(s - 1)]);
            uint8_t next_1 = ((s == nelua_nlstring___len(ms->source)) ? 0x0U : ms->source.data[s]);
            if(((!nelua_match_bracket_class(ms, previous, p, (ep - 1))) && nelua_match_bracket_class(ms, next_1, p, (ep - 1)))) {
              p = ep;
              continue;
            }
            s = -1;
            goto _breaklabel_1;
          }
          case 48U:
          case 49U:
          case 50U:
          case 51U:
          case 52U:
          case 53U:
          case 54U:
          case 55U:
          case 56U:
          case 57U: {
            s = nelua_match_capture(ms, s, (intptr_t)ms->pattern.data[(p + 1)]);
            if((s != -1)) {
              p = (p + 2);
              continue;
            }
            goto _breaklabel_1;
          }
        }
        break;
      }
    }
    {
      intptr_t ep = nelua_match_class_end(ms, p);
      uint8_t epc = ms->pattern.data[ep];
      if((!nelua_match_single(ms, s, p, ep))) {
        if((((epc == 42U) || (epc == 63U)) || (epc == 45U))) {
          p = (ep + 1);
          continue;
        } else {
          s = -1;
        }
      } else {
        switch(epc) {
          case 63U: {
            intptr_t res = nelua_StrPatt_1__match(ms, (s + 1), (ep + 1));
            if((res != -1)) {
              s = res;
            } else {
              p = (ep + 1);
              continue;
            }
            break;
          }
          case 43U: {
            s = (s + 1);
            s = nelua_match_max_expand(ms, s, p, ep);
            break;
          }
          case 42U: {
            s = nelua_match_max_expand(ms, s, p, ep);
            break;
          }
          case 45U: {
            s = nelua_match_min_expand(ms, s, p, ep);
            break;
          }
          default: {
            s = (s + 1);
            p = ep;
            continue;
          }
        }
      }
      break;
    }
  }
  _breaklabel_1:;
  ms->depth = (ms->depth + 1);
  return s;
}
nlmulret_nlisize_nlisize nelua_StrPatt_1_match(nelua_StrPatt_1_ptr ms, intptr_t s) {
  if(((uintptr_t)s > ms->source.size)) {
    return (nlmulret_nlisize_nlisize){s, -1};
  } else if((ms->pattern.size == 0)) {
    return (nlmulret_nlisize_nlisize){s, s};
  } else if(ms->plain) {
    void* found = nelua_memory_find((void*)(&ms->source.data[s]), (ms->source.size - (uintptr_t)s), (void*)(&ms->pattern.data[0]), ms->pattern.size);
    if((!(found != NULL))) {
      return (nlmulret_nlisize_nlisize){s, -1};
    } else {
      s = (intptr_t)((uintptr_t)found - (uintptr_t)(&ms->source.data[0]));
      return (nlmulret_nlisize_nlisize){s, (intptr_t)(int64_t)(s + ms->pattern.size)};
    }
  } else {
    intptr_t p = 0;
    if(ms->anchor) {
      p = 1;
    }
    {
      bool _repeat_stop;
      do {
        nelua_StrPatt_1_reset_captures(ms);
        intptr_t e = nelua_StrPatt_1__match(ms, s, p);
        if((e != -1)) {
          return (nlmulret_nlisize_nlisize){s, e};
        }
        s = (s + 1);
        _repeat_stop = ((s > nelua_nlstring___len(ms->source)) || ms->anchor);
      } while(!_repeat_stop);
    }
    return (nlmulret_nlisize_nlisize){s, -1};
  }
}
void nelua_assert_line_68(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/string.nelua:814:16: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n        assert(ok, capstr)\n               ^~\n", 46, true);
    nelua_abort();
  }
}
void nelua_assert_line_69(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/string.nelua:815:16: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n        assert(not capture:is_position(), 'position capture not supported yet')\n               ^~~~~~~~~~~~~~~~~~~~~~~~~\n", 122, true);
    nelua_abort();
  }
}
nlmulret_nlboolean_nelua_sequence_string_ nelua_string_match_1(nlstring s, nlstring pattern, nlniltype init) {
  intptr_t init_1 = 1;
  nelua_StrPatt_1 ms = nelua_StrPatt_1_create(s, pattern, false);
  nlmulret_nlisize_nlisize _asgnret_1 = nelua_StrPatt_1_match((&ms), (init_1 - 1));
  intptr_t startpos = _asgnret_1.r1;
  intptr_t endpos = _asgnret_1.r2;
  nelua_sequence_string_ captures = (nelua_sequence_string_){0};
  if((endpos != -1)) {
    if((ms.numcaptures > 0)) {
      nelua_sequence_string__resize((&captures), (uintptr_t)ms.numcaptures);
      for(intptr_t i = 0, _end = ms.numcaptures; i < _end; i += 1) {
        nlmulret_nlboolean_nlstring_nelua_StrPattCapture _asgnret_2 = nelua_StrPatt_1_get_capture((&ms), i);
        bool ok = _asgnret_2.r1;
        nlstring capstr = _asgnret_2.r2;
        nelua_StrPattCapture capture = _asgnret_2.r3;
        nelua_assert_line_68(ok, capstr);
        nelua_assert_line_69((!nelua_StrPattCapture_is_position((&capture))), ((nlstring){(uint8_t*)"position capture not supported yet", 34}));
        (*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&captures), (uintptr_t)(i + 1)))) = capstr;
      }
      return (nlmulret_nlboolean_nelua_sequence_string_){true, captures};
    } else {
      (*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&captures), 1U))) = nelua_nlstring_subview_1(ms.source, (startpos + 1), endpos);
      return (nlmulret_nlboolean_nelua_sequence_string_){true, captures};
    }
  } else {
    return (nlmulret_nlboolean_nelua_sequence_string_){false, captures};
  }
}
uintptr_t nelua_assert_narrow_nlisize_nlusize(intptr_t x) {
  if(NELUA_UNLIKELY(x < 0)) {
    nelua_panic_cstring("narrow casting from isize to usize failed");
  }
  return (uintptr_t)x;
}
nlmulret_nlboolean_nelua_sequence_string_ nelua_nlstring_match_1(nlstring s, nlstring pattern, nlniltype init) {
  nlmulret_nlboolean_nelua_sequence_string_ _asgnret_1 = nelua_string_match_1(s, pattern, NELUA_NIL);
  bool ok = _asgnret_1.r1;
  nelua_sequence_string_ seq = _asgnret_1.r2;
  for(intptr_t i = 1, _end = nelua_sequence_string____len((&seq)); i <= _end; i += 1) {
    (*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&seq), nelua_assert_narrow_nlisize_nlusize(i)))) = nelua_nlstring_copy((*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&seq), nelua_assert_narrow_nlisize_nlusize(i)))));
  }
  return (nlmulret_nlboolean_nelua_sequence_string_){ok, seq};
}
nlstring nelua_cstring2string(const char* s) {
  if(s == NULL) {
    return (nlstring){0};
  }
  uintptr_t size = strlen(s);
  if(size == 0) {
    return (nlstring){0};
  }
  return (nlstring){(uint8_t*)s, size};
}
nlstring nelua_tostring_1(char* x) {
  return nelua_nlstring_copy(nelua_cstring2string(x));
}
nlstring nelua_tostring_2(float x) {
  nluint8_arr64 buf;
  return nelua_nlstring_copy(nelua_strconv_1_num2str_1((&buf), x));
}
nlstring nelua_tostring_6(WGPULogLevel x) {
  nluint8_arr48 buf;
  nlstring s = nelua_strconv_1_int2str_1((&buf), (intptr_t)x, NELUA_NIL);
  return nelua_nlstring_copy(s);
}
void nelua_assert_line_70(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/string.nelua:986:12: runtime error: ", 108, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(ok, 'malformed number')\n           ^~\n", 50, true);
    nelua_abort();
  }
}
double nelua_tonumber_1(nlstring x, nlniltype base) {
  nlmulret_nlboolean_nlfloat64 _asgnret_1 = nelua_strconv_1_str2num(x);
  bool ok = _asgnret_1.r1;
  double n = _asgnret_1.r2;
  nelua_assert_line_70(ok, ((nlstring){(uint8_t*)"malformed number", 16}));
  return n;
}
void nelua_assert_line_71(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/string.nelua:1002:12: runtime error: ", 109, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(ok, 'malformed integer')\n           ^~\n", 51, true);
    nelua_abort();
  }
}
int64_t nelua_tointeger_1(nlstring x, nlniltype base) {
  nlmulret_nlboolean_nlint64 _asgnret_1 = nelua_strconv_1_str2int(x, 0U);
  bool ok = _asgnret_1.r1;
  int64_t i = _asgnret_1.r2;
  nelua_assert_line_71(ok, ((nlstring){(uint8_t*)"malformed integer", 17}));
  return i;
}
double nelua_os_now(void) {
  bool ok = false;
  int64_t ns = 0;
#if defined(_WIN32)
  static bool initialized = false;
  static LARGE_INTEGER freq;
  static LARGE_INTEGER start;
  if(!initialized) {
    initialized = true;
    ok = (QueryPerformanceFrequency(&freq) != 0) && (QueryPerformanceCounter(&start) != 0);
  } else {
    LARGE_INTEGER qpc;
    ok = QueryPerformanceCounter(&qpc) != 0;
    int64_t ticks = qpc.QuadPart - start.QuadPart;
    int64_t q = ticks / freq.QuadPart;
    int64_t r = ticks % freq.QuadPart;
    ns = (q * 1000000000) + ((r * 1000000000) / freq.QuadPart);
  }
#elif defined(NELUA_HAVE_POSIX_MONOTONIC_CLOCK)
  static bool initialized = false;
  static struct timespec start = {0};
  if(!initialized) {
    initialized = true;
    ok = clock_gettime(CLOCK_MONOTONIC, &start) == 0;
  } else {
    struct timespec ts = {0};
    ok = clock_gettime(CLOCK_MONOTONIC, &ts) == 0;
    ns = (int64_t)(ts.tv_sec - start.tv_sec)*1000000000 + (int64_t)(ts.tv_nsec - start.tv_nsec);
  }
#elif defined(NELUA_HAVE_C11_TIMESPEC_GET)
  static bool initialized = false;
  static struct timespec start = {0};
  if(!initialized) {
    initialized = true;
    ok = timespec_get(&start, TIME_UTC) == TIME_UTC;
  } else {
    struct timespec ts = {0};
    ok = timespec_get(&ts, TIME_UTC) == TIME_UTC;
    ns = (int64_t)(ts.tv_sec - start.tv_sec)*1000000000 + (int64_t)(ts.tv_nsec - start.tv_nsec);
  }
#elif defined(NELUA_HAVE_POSIX_GETTIMEOFDAY)
  static bool initialized = false;
  static struct timeval start = {0};
  if(!initialized) {
    initialized = true;
    ok = gettimeofday(&start, NULL) == 0;
  } else {
    struct timeval ts;
    ok = gettimeofday(&ts, NULL) == 0;
    ns = (int64_t)(ts.tv_sec - start.tv_sec)*1000000000 + (int64_t)(ts.tv_usec - start.tv_usec)*1000;
  }
#endif
  if((!ok)) {
    return -1.0;
  }
  return (ns / 1000000000.0);
}
bool nelua_lt_nlisize_nlusize(intptr_t a, uintptr_t b) {
  return a < 0 || (uint64_t)a < b;
}
void entropy_world_Storage_Vec2__reserve(entropy_world_Storage_Vec2__ptr self, uintptr_t n) {
  if(nelua_lt_nlisize_nlusize(nelua_vector_Vec2__capacity((&self->data)), n)) {
    nelua_vector_Vec2__reserve((&self->data), n);
    nelua_vector_uint16__reserve((&self->refs), n);
  }
}
void nelua_assert_line_72(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:29:27: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(self.refs[id] == 0, \"supposedly free id still has references!\")\n                          ^~~~\n", 108, true);
    nelua_abort();
  }
}
void nelua_assert_line_73(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:41:16: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(id == #self.refs - 1, \"ids between refcount and data don't match up!\")\n               ^~~~~~~~~~~~~~~~~\n", 117, true);
    nelua_abort();
  }
}
uintptr_t entropy_world_Storage_Vec2__create(entropy_world_Storage_Vec2__ptr self, entropy_math_vec2_Vec2 item) {
  if((nelua_vector_usize____len((&self->free)) > 0)) {
    uintptr_t id = nelua_vector_usize__pop((&self->free));
    nelua_assert_line_72(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) == 0), ((nlstring){(uint8_t*)"supposedly free id still has references!", 40}));
    (*(entropy_math_vec2_Vec2*)nelua_assert_deref(nelua_vector_Vec2____atindex((&self->data), id))) = item;
    (*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) = 1U;
    return id;
  } else {
    nelua_vector_Vec2__push((&self->data), item);
    intptr_t id = (nelua_vector_Vec2____len((&self->data)) - 1);
    nelua_vector_uint16__push((&self->refs), 1U);
    nelua_assert_line_73((id == (nelua_vector_uint16____len((&self->refs)) - 1)), ((nlstring){(uint8_t*)"ids between refcount and data don't match up!", 45}));
    return (uintptr_t)id;
  }
}
void nelua_assert_line_74(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:66:15: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(ptr < #self.data, \"invalid ptr!\")\n              ^~~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
bool nelua_lt_nlusize_nlisize(uintptr_t a, intptr_t b) {
  return b > 0 && a < (uint64_t)b;
}
void nelua_assert_line_75(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:67:26: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(self.refs[ptr] > 0, \"dead ptr!\")\n                         ^~~\n", 73, true);
    nelua_abort();
  }
}
entropy_math_vec2_Vec2_ptr entropy_world_Storage_Vec2____atindex(entropy_world_Storage_Vec2__ptr self, uintptr_t ptr) {
  nelua_assert_line_74(nelua_lt_nlusize_nlisize(ptr, nelua_vector_Vec2____len((&self->data))), ((nlstring){(uint8_t*)"invalid ptr!", 12}));
  nelua_assert_line_75(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), ptr))) > 0), ((nlstring){(uint8_t*)"dead ptr!", 9}));
  return (&(*(entropy_math_vec2_Vec2*)nelua_assert_deref(nelua_vector_Vec2____atindex((&self->data), ptr))));
}
void entropy_world_World_r_1(nlniltype name, nlniltype T) {
}
void entropy_world_Storage_Vec2__1_reserve(entropy_world_Storage_Vec2__1_ptr self, uintptr_t n) {
  if(nelua_lt_nlisize_nlusize(nelua_vector_Vec2__capacity((&self->data)), n)) {
    nelua_vector_Vec2__reserve((&self->data), n);
    nelua_vector_uint16__reserve((&self->refs), n);
  }
}
void nelua_assert_line_76(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:29:27: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(self.refs[id] == 0, \"supposedly free id still has references!\")\n                          ^~~~\n", 108, true);
    nelua_abort();
  }
}
void nelua_assert_line_77(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:41:16: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(id == #self.refs - 1, \"ids between refcount and data don't match up!\")\n               ^~~~~~~~~~~~~~~~~\n", 117, true);
    nelua_abort();
  }
}
uintptr_t entropy_world_Storage_Vec2__1_create(entropy_world_Storage_Vec2__1_ptr self, entropy_math_vec2_Vec2 item) {
  if((nelua_vector_usize____len((&self->free)) > 0)) {
    uintptr_t id = nelua_vector_usize__pop((&self->free));
    nelua_assert_line_76(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) == 0), ((nlstring){(uint8_t*)"supposedly free id still has references!", 40}));
    (*(entropy_math_vec2_Vec2*)nelua_assert_deref(nelua_vector_Vec2____atindex((&self->data), id))) = item;
    (*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) = 1U;
    return id;
  } else {
    nelua_vector_Vec2__push((&self->data), item);
    intptr_t id = (nelua_vector_Vec2____len((&self->data)) - 1);
    nelua_vector_uint16__push((&self->refs), 1U);
    nelua_assert_line_77((id == (nelua_vector_uint16____len((&self->refs)) - 1)), ((nlstring){(uint8_t*)"ids between refcount and data don't match up!", 45}));
    return (uintptr_t)id;
  }
}
void nelua_assert_line_78(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:66:15: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(ptr < #self.data, \"invalid ptr!\")\n              ^~~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
void nelua_assert_line_79(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:67:26: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(self.refs[ptr] > 0, \"dead ptr!\")\n                         ^~~\n", 73, true);
    nelua_abort();
  }
}
entropy_math_vec2_Vec2_ptr entropy_world_Storage_Vec2__1___atindex(entropy_world_Storage_Vec2__1_ptr self, uintptr_t ptr) {
  nelua_assert_line_78(nelua_lt_nlusize_nlisize(ptr, nelua_vector_Vec2____len((&self->data))), ((nlstring){(uint8_t*)"invalid ptr!", 12}));
  nelua_assert_line_79(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), ptr))) > 0), ((nlstring){(uint8_t*)"dead ptr!", 9}));
  return (&(*(entropy_math_vec2_Vec2*)nelua_assert_deref(nelua_vector_Vec2____atindex((&self->data), ptr))));
}
void entropy_world_World_r_2(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_3(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_4(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_5(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_6(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_7(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_8(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_9(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_10(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_11(nlniltype name, nlniltype T) {
}
void entropy_world_World_r_12(nlniltype name, nlniltype T) {
}
void entropy_world_Storage_Entity__reserve(entropy_world_Storage_Entity__ptr self, uintptr_t n) {
  if(nelua_lt_nlisize_nlusize(nelua_vector_Entity__capacity((&self->data)), n)) {
    nelua_vector_Entity__reserve((&self->data), n);
    nelua_vector_uint16__reserve((&self->refs), n);
  }
}
void nelua_assert_line_80(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:29:27: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(self.refs[id] == 0, \"supposedly free id still has references!\")\n                          ^~~~\n", 108, true);
    nelua_abort();
  }
}
void nelua_assert_line_81(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:41:16: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(id == #self.refs - 1, \"ids between refcount and data don't match up!\")\n               ^~~~~~~~~~~~~~~~~\n", 117, true);
    nelua_abort();
  }
}
uintptr_t entropy_world_Storage_Entity__create(entropy_world_Storage_Entity__ptr self, main_Entity item) {
  if((nelua_vector_usize____len((&self->free)) > 0)) {
    uintptr_t id = nelua_vector_usize__pop((&self->free));
    nelua_assert_line_80(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) == 0), ((nlstring){(uint8_t*)"supposedly free id still has references!", 40}));
    (*(main_Entity*)nelua_assert_deref(nelua_vector_Entity____atindex((&self->data), id))) = item;
    (*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) = 1U;
    return id;
  } else {
    nelua_vector_Entity__push((&self->data), item);
    intptr_t id = (nelua_vector_Entity____len((&self->data)) - 1);
    nelua_vector_uint16__push((&self->refs), 1U);
    nelua_assert_line_81((id == (nelua_vector_uint16____len((&self->refs)) - 1)), ((nlstring){(uint8_t*)"ids between refcount and data don't match up!", 45}));
    return (uintptr_t)id;
  }
}
nlmulret_nlboolean_nlisize_main_Entity_ptr entropy_world_Storage_Entity____mnext(entropy_world_Storage_Entity__ptr self, intptr_t ctrl_var) {
  ctrl_var = (ctrl_var + 1);
  while((ctrl_var < nelua_vector_Entity____len((&self->data)))) {
    if(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), nelua_assert_narrow_nlisize_nlusize(ctrl_var)))) > 0)) {
      return (nlmulret_nlboolean_nlisize_main_Entity_ptr){true, ctrl_var, (&(*(main_Entity*)nelua_assert_deref(nelua_vector_Entity____atindex((&self->data), nelua_assert_narrow_nlisize_nlusize(ctrl_var)))))};
    } else {
      ctrl_var = (ctrl_var + 1);
    }
  }
  return (nlmulret_nlboolean_nlisize_main_Entity_ptr){false, -1, ((main_Entity_ptr)NULL)};
}
nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize entropy_world_Storage_Entity____mpairs(entropy_world_Storage_Entity__ptr self) {
  return (nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize){entropy_world_Storage_Entity____mnext, self, -1};
}
void entropy_world_World_r_13(nlniltype name, nlniltype T) {
}
void nelua_assert_line_82(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:29:27: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(self.refs[id] == 0, \"supposedly free id still has references!\")\n                          ^~~~\n", 108, true);
    nelua_abort();
  }
}
void nelua_assert_line_83(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:41:16: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(id == #self.refs - 1, \"ids between refcount and data don't match up!\")\n               ^~~~~~~~~~~~~~~~~\n", 117, true);
    nelua_abort();
  }
}
uintptr_t entropy_world_Storage_Mesh__create(entropy_world_Storage_Mesh__ptr self, entropy_scene_mesh_Mesh item) {
  if((nelua_vector_usize____len((&self->free)) > 0)) {
    uintptr_t id = nelua_vector_usize__pop((&self->free));
    nelua_assert_line_82(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) == 0), ((nlstring){(uint8_t*)"supposedly free id still has references!", 40}));
    (*(entropy_scene_mesh_Mesh*)nelua_assert_deref(nelua_vector_Mesh____atindex((&self->data), id))) = item;
    (*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) = 1U;
    return id;
  } else {
    nelua_vector_Mesh__push((&self->data), item);
    intptr_t id = (nelua_vector_Mesh____len((&self->data)) - 1);
    nelua_vector_uint16__push((&self->refs), 1U);
    nelua_assert_line_83((id == (nelua_vector_uint16____len((&self->refs)) - 1)), ((nlstring){(uint8_t*)"ids between refcount and data don't match up!", 45}));
    return (uintptr_t)id;
  }
}
void nelua_assert_line_84(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:66:15: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(ptr < #self.data, \"invalid ptr!\")\n              ^~~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
void nelua_assert_line_85(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:67:26: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(self.refs[ptr] > 0, \"dead ptr!\")\n                         ^~~\n", 73, true);
    nelua_abort();
  }
}
entropy_scene_mesh_Mesh_ptr entropy_world_Storage_Mesh____atindex(entropy_world_Storage_Mesh__ptr self, uintptr_t ptr) {
  nelua_assert_line_84(nelua_lt_nlusize_nlisize(ptr, nelua_vector_Mesh____len((&self->data))), ((nlstring){(uint8_t*)"invalid ptr!", 12}));
  nelua_assert_line_85(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), ptr))) > 0), ((nlstring){(uint8_t*)"dead ptr!", 9}));
  return (&(*(entropy_scene_mesh_Mesh*)nelua_assert_deref(nelua_vector_Mesh____atindex((&self->data), ptr))));
}
nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr entropy_world_Storage_Mesh____mnext(entropy_world_Storage_Mesh__ptr self, intptr_t ctrl_var) {
  ctrl_var = (ctrl_var + 1);
  while((ctrl_var < nelua_vector_Mesh____len((&self->data)))) {
    if(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), nelua_assert_narrow_nlisize_nlusize(ctrl_var)))) > 0)) {
      return (nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr){true, ctrl_var, (&(*(entropy_scene_mesh_Mesh*)nelua_assert_deref(nelua_vector_Mesh____atindex((&self->data), nelua_assert_narrow_nlisize_nlusize(ctrl_var)))))};
    } else {
      ctrl_var = (ctrl_var + 1);
    }
  }
  return (nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr){false, -1, ((entropy_scene_mesh_Mesh_ptr)NULL)};
}
nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize entropy_world_Storage_Mesh____mpairs(entropy_world_Storage_Mesh__ptr self) {
  return (nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize){entropy_world_Storage_Mesh____mnext, self, -1};
}
void entropy_world_World_r_14(nlniltype name, nlniltype T) {
}
void nelua_assert_line_86(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:29:27: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(self.refs[id] == 0, \"supposedly free id still has references!\")\n                          ^~~~\n", 108, true);
    nelua_abort();
  }
}
void nelua_assert_line_87(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:41:16: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n      check(id == #self.refs - 1, \"ids between refcount and data don't match up!\")\n               ^~~~~~~~~~~~~~~~~\n", 117, true);
    nelua_abort();
  }
}
uintptr_t entropy_world_Storage_Camera__create(entropy_world_Storage_Camera__ptr self, entropy_scene_camera_Camera item) {
  if((nelua_vector_usize____len((&self->free)) > 0)) {
    uintptr_t id = nelua_vector_usize__pop((&self->free));
    nelua_assert_line_86(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) == 0), ((nlstring){(uint8_t*)"supposedly free id still has references!", 40}));
    (*(entropy_scene_camera_Camera*)nelua_assert_deref(nelua_vector_Camera____atindex((&self->data), id))) = item;
    (*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), id))) = 1U;
    return id;
  } else {
    nelua_vector_Camera__push((&self->data), item);
    intptr_t id = (nelua_vector_Camera____len((&self->data)) - 1);
    nelua_vector_uint16__push((&self->refs), 1U);
    nelua_assert_line_87((id == (nelua_vector_uint16____len((&self->refs)) - 1)), ((nlstring){(uint8_t*)"ids between refcount and data don't match up!", 45}));
    return (uintptr_t)id;
  }
}
void nelua_assert_line_88(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:66:15: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(ptr < #self.data, \"invalid ptr!\")\n              ^~~~~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
void nelua_assert_line_89(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/world/storage.nelua:67:26: runtime error: ", 83, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(self.refs[ptr] > 0, \"dead ptr!\")\n                         ^~~\n", 73, true);
    nelua_abort();
  }
}
entropy_scene_camera_Camera_ptr entropy_world_Storage_Camera____atindex(entropy_world_Storage_Camera__ptr self, uintptr_t ptr) {
  nelua_assert_line_88(nelua_lt_nlusize_nlisize(ptr, nelua_vector_Camera____len((&self->data))), ((nlstring){(uint8_t*)"invalid ptr!", 12}));
  nelua_assert_line_89(((*(uint16_t*)nelua_assert_deref(nelua_vector_uint16____atindex((&self->refs), ptr))) > 0), ((nlstring){(uint8_t*)"dead ptr!", 9}));
  return (&(*(entropy_scene_camera_Camera*)nelua_assert_deref(nelua_vector_Camera____atindex((&self->data), ptr))));
}
void entropy_world_World_r_15(nlniltype name, nlniltype T) {
}
entropy_world_Storage_Vec2__ptr entropy_world_World_s_1(entropy_world_World_ptr self, nlniltype name) {
  return (&self->positions);
}
entropy_world_Storage_Vec2__1_ptr entropy_world_World_s_2(entropy_world_World_ptr self, nlniltype name) {
  return (&self->velocities);
}
entropy_world_Storage_Entity__ptr entropy_world_World_s_3(entropy_world_World_ptr self, nlniltype name) {
  return (&self->entities);
}
entropy_world_Storage_Camera__ptr entropy_world_World_s_4(entropy_world_World_ptr self, nlniltype name) {
  return (&self->entropy___scene___cameras);
}
entropy_world_Storage_Mesh__ptr entropy_world_World_s_5(entropy_world_World_ptr self, nlniltype name) {
  return (&self->entropy___scene___meshes);
}
void entropy_world_check_storage_1(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_2(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_3(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_4(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_5(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_6(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_7(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_8(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_9(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_10(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_11(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_12(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_13(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_14(nlniltype name, nlniltype T) {
}
void entropy_world_check_storage_15(nlniltype name, nlniltype T) {
}
double entropy_world_World_now(entropy_world_World_ptr self) {
  return nelua_os_now();
}
nltype nelua_require_entropy_world_pointer(nlniltype modname) {
  entropy_world_check_storage_1(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_2(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_3(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_4(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_5(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_6(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_7(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_8(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_9(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_10(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_11(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_12(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_13(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_14(NELUA_NIL, NELUA_NIL);
  entropy_world_check_storage_15(NELUA_NIL, NELUA_NIL);
  return NELUA_NIL;
}
nltype nelua_require_entropy_world_pointer_cached(nlniltype modname) {
  static bool loaded = false;
  static nltype cache;
  if(!loaded) {
    cache = nelua_require_entropy_world_pointer(NELUA_NIL);
    loaded = true;
  }
  return cache;
}
float nelua_math_sqrt_1(float x) {
  return sqrtf(x);
}
float nelua_math_cos_1(float x) {
  return cosf(x);
}
double nelua_math_cos_2(double x) {
  return cos(x);
}
float nelua_math_sin_1(float x) {
  return sinf(x);
}
double nelua_math_sin_2(double x) {
  return sin(x);
}
float nelua_math_tan_1(float x) {
  return tanf(x);
}
float nelua_math_rad_1(float x) {
  return (x * 0.0174532925f);
}
double nelua_math_rad_2(double x) {
  return (x * 0.017453292519943295);
}
double nelua_math_clamp_1(double x, double min, double max) {
  x = ((x < min) ? min : x);
  x = ((x > max) ? max : x);
  return x;
}
entropy_math_vec2_Vec2 entropy_math_vec2_Vec2___add(entropy_math_vec2_Vec2 a, entropy_math_vec2_Vec2 b) {
  return (entropy_math_vec2_Vec2){.x = (a.x + b.x), .y = (a.y + b.y)};
}
nlstring entropy_math_vec2_Vec2___tostring(entropy_math_vec2_Vec2_ptr self) {
  return nelua_nlstring___concat_7(((nlstring){(uint8_t*)"Vec2", 4}), nelua_nlstring___concat_7(((nlstring){(uint8_t*)"(", 1}), nelua_nlstring___concat_2(self->x, nelua_nlstring___concat_7(((nlstring){(uint8_t*)", ", 2}), nelua_nlstring___concat_2(self->y, ((nlstring){(uint8_t*)")", 1}))))));
}
entropy_math_vec3_Vec3 entropy_math_vec3_Vec3___add(entropy_math_vec3_Vec3 a, entropy_math_vec3_Vec3 b) {
  return (entropy_math_vec3_Vec3){.x = (a.x + b.x), .y = (a.y + b.y), .z = (a.z + b.z)};
}
entropy_math_vec3_Vec3 entropy_math_vec3_Vec3___sub(entropy_math_vec3_Vec3 a, entropy_math_vec3_Vec3 b) {
  return (entropy_math_vec3_Vec3){.x = (a.x - b.x), .y = (a.y - b.y), .z = (a.z - b.z)};
}
entropy_math_vec3_Vec3 entropy_math_vec3_Vec3_scale(entropy_math_vec3_Vec3_ptr self, float s) {
  return (entropy_math_vec3_Vec3){.x = (self->x * s), .y = (self->y * s), .z = (self->z * s)};
}
double entropy_math_vec3_Vec3_dot(entropy_math_vec3_Vec3_ptr self, entropy_math_vec3_Vec3 b) {
  return (double)(((self->x * b.x) + (self->y * b.y)) + (self->z * b.z));
}
entropy_math_vec3_Vec3 entropy_math_vec3_Vec3_cross(entropy_math_vec3_Vec3_ptr self, entropy_math_vec3_Vec3 b) {
  return (entropy_math_vec3_Vec3){.x = ((self->y * b.z) - (self->z * b.y)), .y = ((self->z * b.x) - (self->x * b.z)), .z = ((self->x * b.y) - (self->y * b.x))};
}
double entropy_math_vec3_Vec3___len(entropy_math_vec3_Vec3_ptr self) {
  return (double)nelua_math_sqrt_1((((self->x * self->x) + (self->y * self->y)) + (self->z * self->z)));
}
entropy_math_vec3_Vec3 entropy_math_vec3_Vec3_norm(entropy_math_vec3_Vec3_ptr self) {
  double len = entropy_math_vec3_Vec3___len(self);
  return (entropy_math_vec3_Vec3){.x = (float)(self->x / len), .y = (float)(self->y / len), .z = (float)(self->z / len)};
}
entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_identity(void) {
  return (entropy_math_mat4_Mat4){.x = {1.0f, 0.0f, 0.0f, 0.0f}, .y = {0.0f, 1.0f, 0.0f, 0.0f}, .z = {0.0f, 0.0f, 1.0f, 0.0f}, .w = {0.0f, 0.0f, 0.0f, 1.0f}};
}
entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_from_pos(entropy_math_vec3_Vec3 pos) {
  return (entropy_math_mat4_Mat4){.x = {1.0f, 0.0f, 0.0f, 0.0f}, .y = {0.0f, 1.0f, 0.0f, 0.0f}, .z = {0.0f, 0.0f, 1.0f, 0.0f}, .w = {pos.x, pos.y, pos.z, 1.0f}};
}
entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_from_rot(float angle, entropy_math_vec3_Vec3 axis) {
  float c = nelua_math_cos_1(angle);
  float s = nelua_math_sin_1(angle);
  float t = (1 - c);
  float x = axis.x;
  float y = axis.y;
  float z = axis.z;
  float tx = (t * x);
  float ty = (t * y);
  float tz = (t * z);
  float sx = (s * x);
  float sy = (s * y);
  float sz = (s * z);
  return (entropy_math_mat4_Mat4){.x = {((tx * x) + c), ((tx * y) + sz), ((tx * z) - sy), 0.0f}, .y = {((tx * y) - sz), ((ty * y) + c), ((ty * z) + sx), 0.0f}, .z = {((tx * z) + sy), ((ty * z) - sx), ((tz * z) + c), 0.0f}, .w = {0.0f, 0.0f, 0.0f, 1.0f}};
}
entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_from_scl(entropy_math_vec3_Vec3 scale) {
  return (entropy_math_mat4_Mat4){.x = {scale.x, 0.0f, 0.0f, 0.0f}, .y = {0.0f, scale.y, 0.0f, 0.0f}, .z = {0.0f, 0.0f, scale.z, 0.0f}, .w = {0.0f, 0.0f, 0.0f, 1.0f}};
}
entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_transpose(entropy_math_mat4_Mat4_ptr self) {
  return (entropy_math_mat4_Mat4){.x = {self->x.x, self->y.x, self->z.x, self->w.x}, .y = {self->x.y, self->y.y, self->z.y, self->w.y}, .z = {self->x.z, self->y.z, self->z.z, self->w.z}, .w = {self->x.w, self->y.w, self->z.w, self->w.w}};
}
entropy_math_mat4_Mat4 entropy_math_mat4_Mat4___mul(entropy_math_mat4_Mat4 a, entropy_math_mat4_Mat4 b) {
  entropy_math_mat4_Mat4 result = entropy_math_mat4_Mat4_identity();
  result.x.x = ((((a.x.x * b.x.x) + (a.y.x * b.x.y)) + (a.z.x * b.x.z)) + (a.w.x * b.x.w));
  result.x.y = ((((a.x.y * b.x.x) + (a.y.y * b.x.y)) + (a.z.y * b.x.z)) + (a.w.y * b.x.w));
  result.x.z = ((((a.x.z * b.x.x) + (a.y.z * b.x.y)) + (a.z.z * b.x.z)) + (a.w.z * b.x.w));
  result.x.w = ((((a.x.w * b.x.x) + (a.y.w * b.x.y)) + (a.z.w * b.x.z)) + (a.w.w * b.x.w));
  result.y.x = ((((a.x.x * b.y.x) + (a.y.x * b.y.y)) + (a.z.x * b.y.z)) + (a.w.x * b.y.w));
  result.y.y = ((((a.x.y * b.y.x) + (a.y.y * b.y.y)) + (a.z.y * b.y.z)) + (a.w.y * b.y.w));
  result.y.z = ((((a.x.z * b.y.x) + (a.y.z * b.y.y)) + (a.z.z * b.y.z)) + (a.w.z * b.y.w));
  result.y.w = ((((a.x.w * b.y.x) + (a.y.w * b.y.y)) + (a.z.w * b.y.z)) + (a.w.w * b.y.w));
  result.z.x = ((((a.x.x * b.z.x) + (a.y.x * b.z.y)) + (a.z.x * b.z.z)) + (a.w.x * b.z.w));
  result.z.y = ((((a.x.y * b.z.x) + (a.y.y * b.z.y)) + (a.z.y * b.z.z)) + (a.w.y * b.z.w));
  result.z.z = ((((a.x.z * b.z.x) + (a.y.z * b.z.y)) + (a.z.z * b.z.z)) + (a.w.z * b.z.w));
  result.z.w = ((((a.x.w * b.z.x) + (a.y.w * b.z.y)) + (a.z.w * b.z.z)) + (a.w.w * b.z.w));
  result.w.x = ((((a.x.x * b.w.x) + (a.y.x * b.w.y)) + (a.z.x * b.w.z)) + (a.w.x * b.w.w));
  result.w.y = ((((a.x.y * b.w.x) + (a.y.y * b.w.y)) + (a.z.y * b.w.z)) + (a.w.y * b.w.w));
  result.w.z = ((((a.x.z * b.w.x) + (a.y.z * b.w.y)) + (a.z.z * b.w.z)) + (a.w.z * b.w.w));
  result.w.w = ((((a.x.w * b.w.x) + (a.y.w * b.w.y)) + (a.z.w * b.w.z)) + (a.w.w * b.w.w));
  return result;
}
entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_look_at(entropy_math_vec3_Vec3 eye, entropy_math_vec3_Vec3 target, entropy_math_vec3_Vec3 up) {
  entropy_math_vec3_Vec3 f = entropy_math_vec3_Vec3_norm(NELUA_LITERAL_REF(entropy_math_vec3_Vec3, (entropy_math_vec3_Vec3___sub(target, eye))));
  entropy_math_vec3_Vec3 s = entropy_math_vec3_Vec3_norm(NELUA_LITERAL_REF(entropy_math_vec3_Vec3, (entropy_math_vec3_Vec3_cross((&f), up))));
  entropy_math_vec3_Vec3 u = entropy_math_vec3_Vec3_cross((&s), f);
  return (entropy_math_mat4_Mat4){.x = {s.x, u.x, (-f.x), 0.0f}, .y = {s.y, u.y, (-f.y), 0.0f}, .z = {s.z, u.z, (-f.z), 0.0f}, .w = {(float)(-entropy_math_vec3_Vec3_dot((&s), eye)), (float)(-entropy_math_vec3_Vec3_dot((&u), eye)), (float)entropy_math_vec3_Vec3_dot((&f), eye), 1.0f}};
}
entropy_math_mat4_Mat4 entropy_math_mat4_Mat4_perspective(float fov, float aspect, float near, float far) {
  entropy_math_mat4_Mat4 result = entropy_math_mat4_Mat4_identity();
  float f = (1 / nelua_math_tan_1((nelua_math_rad_1(fov) / 2)));
  float nf = (1 / (near - far));
  result.x.x = (f / aspect);
  result.y.y = f;
  result.z.z = ((far + near) * nf);
  result.z.w = -1.0f;
  result.w.z = (((2 * far) * near) * nf);
  result.w.w = 0.0f;
  return result;
}
void nelua_print_1(nlstring a1) {
  if(a1.size > 0) {
    fwrite(a1.data, 1, a1.size, stdout);
  }
  fputs("\n", stdout);
  fflush(stdout);
}
void nelua_print_2(intptr_t a1, main_Entity_ptr a2, nlstring a3, nlstring a4) {
  fprintf(stdout, "%lli", (long long)a1);
  fputs("	", stdout);
  if(a2 != NULL) {
    fprintf(stdout, "0x%llx", (unsigned long long)(uintptr_t)a2);
  } else {
    fputs("(null)", stdout);
  }
  fputs("	", stdout);
  if(a3.size > 0) {
    fwrite(a3.data, 1, a3.size, stdout);
  }
  fputs("	", stdout);
  if(a4.size > 0) {
    fwrite(a4.data, 1, a4.size, stdout);
  }
  fputs("\n", stdout);
  fflush(stdout);
}
int64_t nelua_assert_imod_nlint64(int64_t a, int64_t b) {
  if(NELUA_UNLIKELY(b == -1)) return 0;
  if(NELUA_UNLIKELY(b == 0)) nelua_panic_cstring("division by zero");
  int64_t r = a % b;
  return (r != 0 && (a ^ b) < 0) ? r + b : r;
}
void nelua_print_3(nlstring a1, double a2) {
  int len;
  bool fractnum;
  char buff[48];
  buff[sizeof(buff)-1] = 0;
  if(a1.size > 0) {
    fwrite(a1.data, 1, a1.size, stdout);
  }
  fputs("	", stdout);
  len = snprintf(buff, sizeof(buff)-1, "%.14g", a2);
  fractnum = false;
  for(int i=0;i<len && buff[i] != 0;++i) {
    if(!((buff[i] >= '0' && buff[i] <= '9') || buff[i] == '-')) {
      fractnum = true;
      break;
    }
  }
  if(!fractnum && len > 0 && len + 2 < (int)sizeof(buff)) {
    buff[len] = '.';
    buff[len+1] = '0';
    len = len + 2;
  }
  fwrite(buff, 1, len, stdout);
  fputs("\n", stdout);
  fflush(stdout);
}
void main_anonfunc(WGPULogLevel level, char* msg, void* ptr) {
  nelua_print_1(nelua_nlstring___concat_7(((nlstring){(uint8_t*)"WGPU", 4}), nelua_nlstring___concat_8(level, nelua_nlstring___concat_6(((nlstring){(uint8_t*)": ", 2}), msg))));
}
void entropy_render_anonfunc(WGPURequestAdapterStatus status, WGPUAdapterImpl_ptr received, char* message, void* userdata) {
  (*(WGPUAdapterImpl_ptr*)nelua_assert_deref((WGPUAdapterImpl_ptr_ptr)userdata)) = received;
}
void entropy_render_anonfunc_1(WGPURequestDeviceStatus status, WGPUDeviceImpl_ptr received, char* message, void* userdata) {
  (*(WGPUDeviceImpl_ptr*)nelua_assert_deref((WGPUDeviceImpl_ptr_ptr)userdata)) = received;
}
nlmulret_WGPUAdapterImpl_ptr_WGPUDeviceImpl_ptr entropy_render_render_request_adapter_device(WGPUSurfaceImpl_ptr surface) {
  WGPUAdapterImpl_ptr adapter = NULL;
  wgpuInstanceRequestAdapter(((WGPUInstanceImpl_ptr)NULL), NELUA_LITERAL_REF(WGPURequestAdapterOptions, ((WGPURequestAdapterOptions){.nextInChain = ((WGPUChainedStruct_ptr)NELUA_LITERAL_REF(WGPUAdapterExtras, ((WGPUAdapterExtras){.chain = {.sType = 1610612738}, .backend = 5}))), .powerPreference = 2, .compatibleSurface = surface, .forceFallbackAdapter = false})), entropy_render_anonfunc, (void*)(&adapter));
  while((!(adapter != NULL))) {
  }
  WGPUDeviceImpl_ptr device = NULL;
  wgpuAdapterRequestDevice(adapter, NELUA_LITERAL_REF(WGPUDeviceDescriptor, ((WGPUDeviceDescriptor){.nextInChain = ((WGPUChainedStruct_ptr)NELUA_LITERAL_REF(WGPUDeviceExtras, ((WGPUDeviceExtras){.chain = {.sType = 1610612737}}))), .requiredLimits = NELUA_LITERAL_REF(WGPURequiredLimits, ((WGPURequiredLimits){.limits = {.maxBindGroups = 8U}, .nextInChain = ((WGPUChainedStruct_ptr)NELUA_LITERAL_REF(WGPURequiredLimitsExtras, ((WGPURequiredLimitsExtras){.chain = {.sType = 1610612739}, .maxPushConstantSize = 128U})))})), .requiredFeaturesCount = 1U, .requiredFeatures = (WGPUFeatureName_ptr)NELUA_LITERAL_REF(WGPUFeatureName_arr1, ((WGPUFeatureName_arr1){{1610612737}}))})), entropy_render_anonfunc_1, (void*)(&device));
  while((!(device != NULL))) {
  }
  return (nlmulret_WGPUAdapterImpl_ptr_WGPUDeviceImpl_ptr){adapter, device};
}
void nelua_list_Event__pushback(nelua_list_Event__ptr self, entropy_defs_event_Event value) {
  nelua_listnode_Event__ptr node = nelua_GCAllocator_new_2((&self->allocator), NELUA_NIL, NELUA_NIL, NELUA_NIL);
  node->prev = self->back;
  node->next = ((nelua_listnodeT_ptr)NULL);
  node->value = value;
  if(NELUA_LIKELY((self->back != NULL))) {
    self->back->next = node;
  }
  if(NELUA_UNLIKELY((!(self->front != NULL)))) {
    self->front = node;
  }
  self->back = node;
}
void nelua_assert_line_90(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/list.nelua:163:22: runtime error: ", 106, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    check(self.front ~= nilptr, 'list is empty')\n                     ^~~~~~~~~\n", 81, true);
    nelua_abort();
  }
}
entropy_defs_event_Event nelua_list_Event__popfront(nelua_list_Event__ptr self) {
  nelua_assert_line_90((self->front != ((nelua_listnode_Event__ptr)NULL)), ((nlstring){(uint8_t*)"list is empty", 13}));
  nelua_listnode_Event__ptr node = self->front;
  entropy_defs_event_Event ret = node->value;
  self->front = node->next;
  if(NELUA_LIKELY((self->front != NULL))) {
    self->front->prev = ((nelua_listnodeT_ptr)NULL);
  }
  if(NELUA_UNLIKELY((self->back == node))) {
    self->back = ((nelua_listnode_Event__ptr)NULL);
  }
  nelua_GCAllocator_delete_2((&self->allocator), node);
  return ret;
}
bool nelua_list_Event__empty(nelua_list_Event__ptr self) {
  return (self->front == ((nelua_listnode_Event__ptr)NULL));
}
void entropy_render_glfw_context_GLFWContext_create_swapchain(entropy_render_glfw_context_GLFWContext_ptr self) {
  WGPUPresentMode present_mode = 0;
  if(self->vsync) {
    present_mode = 2;
  } else {
    present_mode = 0;
  }
  self->swapchain = wgpuDeviceCreateSwapChain(self->device, self->surface, NELUA_LITERAL_REF(WGPUSwapChainDescriptor, ((WGPUSwapChainDescriptor){.usage = 16U, .format = self->format, .width = self->width, .height = self->height, .presentMode = present_mode})));
}
void entropy_render_glfw_context_GLFWContext_resize(entropy_render_glfw_context_GLFWContext_ptr self, uint32_t width, uint32_t height) {
  self->width = width;
  self->height = height;
  entropy_render_glfw_context_GLFWContext_create_swapchain(self);
}
int nelua_assert_narrow_nluint32_nlcint(uint32_t x) {
  if(NELUA_UNLIKELY(x > 0x7fffffffU)) {
    nelua_panic_cstring("narrow casting from uint32 to cint failed");
  }
  return (int)x;
}
char* nelua_assert_string2cstring(nlstring s) {
  if(s.size == 0) {
    return (char*)"";
  }
  if(NELUA_UNLIKELY(s.data[s.size]) != 0) {
    nelua_panic_cstring("attempt to convert a non null terminated string to cstring");
  }
  return (char*)s.data;
}
void nelua_assert_line_91(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/home/woze/projects/enqy/entropy/entropy/render/glfw_context.nelua:66:14: runtime error: ", 89, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  assert(self.window, \"failed to create window!\")\n             ^~~~~~~\n", 72, true);
    nelua_abort();
  }
}
uint32_t nelua_assert_narrow_nlcint_nluint32(int x) {
  if(NELUA_UNLIKELY(x < 0)) {
    nelua_panic_cstring("narrow casting from cint to uint32 failed");
  }
  return (uint32_t)x;
}
void entropy_render_glfw_context_anonfunc(GLFWwindow_ptr window, int width_1, int height_1) {
  entropy_render_glfw_context_GLFWContext_ptr cself = ((entropy_render_glfw_context_GLFWContext_ptr)glfwGetWindowUserPointer(window));
  entropy_render_glfw_context_GLFWContext_resize(cself, nelua_assert_narrow_nlcint_nluint32(width_1), nelua_assert_narrow_nlcint_nluint32(height_1));
  if((cself->resize_callback != NULL)) {
    cself->resize_callback(cself->user_pointer, nelua_assert_narrow_nlcint_nluint32(width_1), nelua_assert_narrow_nlcint_nluint32(height_1));
  }
}
void entropy_render_glfw_context_anonfunc_1(GLFWwindow_ptr window, int key, int scancode, int action, int mods) {
  entropy_render_glfw_context_GLFWContext_ptr cself = ((entropy_render_glfw_context_GLFWContext_ptr)glfwGetWindowUserPointer(window));
  entropy_defs_event_Event event = (entropy_defs_event_Event){0};
  event.type = 0;
  event.data.Key.action = (entropy_defs_event_DataKeyAction)action;
  event.data.Key.key = nelua_assert_narrow_nlcint_nluint32(key);
  event.data.Key.modifiers = nelua_assert_narrow_nlcint_nluint32(mods);
  nelua_list_Event__pushback((&cself->event_queue), event);
}
int32_t nelua_assert_narrow_nlfloat64_nlint32(double x) {
  if(NELUA_UNLIKELY((int32_t)(x) != x)) {
    nelua_panic_cstring("narrow casting from float64 to int32 failed");
  }
  return (int32_t)x;
}
void entropy_render_glfw_context_anonfunc_2(GLFWwindow_ptr window, double x, double y) {
  entropy_render_glfw_context_GLFWContext_ptr cself = ((entropy_render_glfw_context_GLFWContext_ptr)glfwGetWindowUserPointer(window));
  entropy_defs_event_Event event = (entropy_defs_event_Event){0};
  event.type = 1;
  event.data.MouseMotion.x = nelua_assert_narrow_nlfloat64_nlint32(x);
  event.data.MouseMotion.y = nelua_assert_narrow_nlfloat64_nlint32(y);
  nelua_list_Event__pushback((&cself->event_queue), event);
}
void entropy_render_glfw_context_GLFWContext_init(entropy_render_glfw_context_GLFWContext_ptr self, nlstring title, uint32_t width, uint32_t height, bool vsync) {
  glfwInit();
  glfwWindowHint(139265, 0);
  self->window = glfwCreateWindow(nelua_assert_narrow_nluint32_nlcint(width), nelua_assert_narrow_nluint32_nlcint(height), nelua_assert_string2cstring(title), ((GLFWmonitor_ptr)NULL), ((GLFWwindow_ptr)NULL));
  nelua_assert_line_91((self->window != NULL), ((nlstring){(uint8_t*)"failed to create window!", 24}));
  self->width = width;
  self->height = height;
  glfwSetWindowUserPointer(self->window, (void*)self);
  glfwSetWindowSizeCallback(self->window, entropy_render_glfw_context_anonfunc);
  glfwSetKeyCallback(self->window, entropy_render_glfw_context_anonfunc_1);
  glfwSetCursorPosCallback(self->window, entropy_render_glfw_context_anonfunc_2);
  glfwSetInputMode(self->window, 208897, 212995);
  if((glfwRawMouseMotionSupported() != 0)) {
    glfwSetInputMode(self->window, 208901, 1);
  }
  self->surface = wgpuInstanceCreateSurface(((WGPUInstanceImpl_ptr)NULL), NELUA_LITERAL_REF(WGPUSurfaceDescriptor, ((WGPUSurfaceDescriptor){.nextInChain = ((WGPUChainedStruct_ptr)NELUA_LITERAL_REF(WGPUSurfaceDescriptorFromXlibWindow, ((WGPUSurfaceDescriptorFromXlibWindow){.chain = {.sType = 3}, .display = (void*)glfwGetX11Display(), .window = (uint32_t)glfwGetX11Window(self->window)})))})));
  nlmulret_WGPUAdapterImpl_ptr_WGPUDeviceImpl_ptr _asgnret_1 = entropy_render_render_request_adapter_device(self->surface);
  self->adapter = _asgnret_1.r1;
  self->device = _asgnret_1.r2;
  self->format = wgpuSurfaceGetPreferredFormat(self->surface, self->adapter);
  self->vsync = vsync;
  entropy_render_glfw_context_GLFWContext_create_swapchain(self);
}
void entropy_render_glfw_context_GLFWContext_cleanup(entropy_render_glfw_context_GLFWContext_ptr self) {
  wgpuDeviceDrop(self->device);
  wgpuAdapterDrop(self->adapter);
  glfwTerminate();
}
WGPUTextureViewImpl_ptr entropy_render_glfw_context_GLFWContext_view(entropy_render_glfw_context_GLFWContext_ptr self) {
  return wgpuSwapChainGetCurrentTextureView(self->swapchain);
}
void entropy_render_glfw_context_GLFWContext_present(entropy_render_glfw_context_GLFWContext_ptr self) {
  wgpuSwapChainPresent(self->swapchain);
}
bool entropy_render_glfw_context_GLFWContext_should_close(entropy_render_glfw_context_GLFWContext_ptr self) {
  return (glfwWindowShouldClose(self->window) != 0);
}
void entropy_render_glfw_context_GLFWContext_close(entropy_render_glfw_context_GLFWContext_ptr self) {
  glfwSetWindowShouldClose(self->window, 1);
}
nlmulret_nlboolean_nelua_list_Event__ptr entropy_render_glfw_context_GLFWContext_poll_event(entropy_render_glfw_context_GLFWContext_ptr self) {
  glfwPollEvents();
  if(nelua_list_Event__empty((&self->event_queue))) {
    return (nlmulret_nlboolean_nelua_list_Event__ptr){false, (&self->event_queue)};
  } else {
    return (nlmulret_nlboolean_nelua_list_Event__ptr){true, (&self->event_queue)};
  }
}
void entropy_render_renderer_RendererImplT_init(entropy_render_renderer_RendererImplT_ptr self, WGPUDeviceImpl_ptr device, WGPUTextureFormat target_format, uint32_t target_width, uint32_t target_height) {
  self->device = device;
  self->queue = wgpuDeviceGetQueue(device);
  self->target_config = (record_3NPFB7dQvgvfT34FH){.format = target_format, .width = target_width, .height = target_height};
  self->depth_buffer = wgpuDeviceCreateTexture(self->device, NELUA_LITERAL_REF(WGPUTextureDescriptor, ((WGPUTextureDescriptor){.size = {.width = self->target_config.width, .height = self->target_config.height, .depthOrArrayLayers = 1U}, .mipLevelCount = 1U, .sampleCount = 1U, .dimension = 1, .usage = 20U, .format = 40})));
  entropy_render_impl_basic_Impl_init_1((&self->impl), self);
}
void entropy_render_renderer_RendererImplT_cleanup(entropy_render_renderer_RendererImplT_ptr self) {
  wgpuTextureDestroy(self->depth_buffer);
  entropy_render_impl_basic_Impl_cleanup_1((&self->impl), self);
  wgpuDeviceDestroy(self->device);
}
void entropy_render_renderer_RendererImplT_resize(entropy_render_renderer_RendererImplT_ptr self, uint32_t width, uint32_t height) {
  self->target_config.width = width;
  self->target_config.height = height;
  wgpuTextureDestroy(self->depth_buffer);
  self->depth_buffer = wgpuDeviceCreateTexture(self->device, NELUA_LITERAL_REF(WGPUTextureDescriptor, ((WGPUTextureDescriptor){.size = {.width = self->target_config.width, .height = self->target_config.height, .depthOrArrayLayers = 1U}, .mipLevelCount = 1U, .sampleCount = 1U, .dimension = 1, .usage = 20U, .format = 40})));
  entropy_render_impl_basic_Impl_resize_1((&self->impl), self);
}
WGPUTextureViewImpl_ptr entropy_render_renderer_RendererImplT_depth_stencil_view(entropy_render_renderer_RendererImplT_ptr self) {
  return wgpuTextureCreateView(self->depth_buffer, NELUA_LITERAL_REF(WGPUTextureViewDescriptor, ((WGPUTextureViewDescriptor){.format = 40, .dimension = 2, .aspect = 0, .baseMipLevel = 0U, .mipLevelCount = 1U, .baseArrayLayer = 0U, .arrayLayerCount = 1U})));
}
void entropy_render_renderer_RendererImplT_render(entropy_render_renderer_RendererImplT_ptr self, WGPUTextureViewImpl_ptr target, entropy_world_World_ptr world) {
  WGPUCommandEncoderImpl_ptr encoder = wgpuDeviceCreateCommandEncoder(self->device, NELUA_LITERAL_REF(WGPUCommandEncoderDescriptor, ((WGPUCommandEncoderDescriptor){.label = (char*)NULL})));
  WGPURenderPassEncoderImpl_ptr pass = wgpuCommandEncoderBeginRenderPass(encoder, NELUA_LITERAL_REF(WGPURenderPassDescriptor, ((WGPURenderPassDescriptor){.colorAttachmentCount = 1U, .colorAttachments = ((WGPURenderPassColorAttachment_ptr)NELUA_LITERAL_REF(WGPURenderPassColorAttachment_arr1, ((WGPURenderPassColorAttachment_arr1){{{.view = target, .loadOp = 1, .storeOp = 1, .clearValue = {.r = 0.0, .g = 0.0, .b = 0.0, .a = 1.0}}}}))), .depthStencilAttachment = NELUA_LITERAL_REF(WGPURenderPassDepthStencilAttachment, ((WGPURenderPassDepthStencilAttachment){.view = entropy_render_renderer_RendererImplT_depth_stencil_view(self), .depthLoadOp = 1, .depthStoreOp = 1, .depthClearValue = 1.0f, .depthReadOnly = false, .stencilLoadOp = 1, .stencilStoreOp = 1, .stencilClearValue = 0U, .stencilReadOnly = false}))})));
  entropy_render_impl_basic_Impl_render_1((&self->impl), self, pass, encoder, target, world);
  wgpuRenderPassEncoderEnd(pass);
  WGPUCommandBufferImpl_ptr cmd_buffer = wgpuCommandEncoderFinish(encoder, NELUA_LITERAL_REF(WGPUCommandBufferDescriptor, ((WGPUCommandBufferDescriptor){.label = (char*)NULL})));
  wgpuQueueSubmit(self->queue, 1U, (&cmd_buffer));
}
nelua_filestream nelua_filestream__fromfp(FILE_ptr fp, function_2vA5rraMvZeJQbU9V closef) {
  return (nelua_filestream){.fs = nelua_GCAllocator_new_3((&nelua_gc_allocator), (nelua_FStream){.fp = fp, .closef = closef}, NELUA_NIL, NELUA_NIL)};
}
FILE_ptr nelua_filestream__getfp(nelua_filestream_ptr self) {
  if((!(self->fs != NULL))) {
    return ((FILE_ptr)NULL);
  }
  return self->fs->fp;
}
nlmulret_nlstring_nlint64 nelua_geterrno_1(void) {
  return (nlmulret_nlstring_nlint64){nelua_cstring2string(strerror(errno)), (int64_t)errno};
}
bool nelua_checkmode(nlstring mode_1) {
  if((nelua_nlstring___len(mode_1) == 0)) {
    return false;
  }
  if((nelua_memory_scan((void*)(char*)"rwa", mode_1.data[0], 3U) == (void*)NULL)) {
    return false;
  }
  uintptr_t pos = 1U;
  if((mode_1.data[pos] == 43U)) {
    pos = (pos + 1);
  }
  if((mode_1.data[pos] == 98U)) {
    pos = (pos + 1);
  }
  return (mode_1.data[pos] == 0);
}
void nelua_assert_line_92(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/filestream.nelua:93:19: runtime error: ", 111, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n  assert(checkmode(mode), 'invalid mode')\n                  ^~~~~~\n", 68, true);
    nelua_abort();
  }
}
nlmulret_nelua_filestream_nlstring_nlint64 nelua_filestream_open_1(nlstring filename, nlstring mode) {
  nelua_assert_line_92(nelua_checkmode(mode), ((nlstring){(uint8_t*)"invalid mode", 12}));
  FILE_ptr fp = fopen(nelua_assert_string2cstring(filename), nelua_assert_string2cstring(mode));
  if((!(fp != NULL))) {
    nlmulret_nlstring_nlint64 _ret_1 = nelua_geterrno_1();
    return (nlmulret_nelua_filestream_nlstring_nlint64){(nelua_filestream){0}, _ret_1.r1, _ret_1.r2};
  }
  return (nlmulret_nelua_filestream_nlstring_nlint64){nelua_filestream__fromfp(fp, fclose), ((nlstring){(uint8_t*)"", 0}), 0};
}
nlmulret_nelua_filestream_nlstring_nlint64 nelua_filestream_open_2(nlstring filename, nlniltype mode) {
  nlstring mode_2 = ((nlstring){(uint8_t*)"r", 1});
  FILE_ptr fp = fopen(nelua_assert_string2cstring(filename), nelua_assert_string2cstring(mode_2));
  if((!(fp != NULL))) {
    nlmulret_nlstring_nlint64 _ret_1 = nelua_geterrno_1();
    return (nlmulret_nelua_filestream_nlstring_nlint64){(nelua_filestream){0}, _ret_1.r1, _ret_1.r2};
  }
  nlmulret_nelua_filestream_nlstring_nlint64 _mulret_1;
  _mulret_1.r1 = nelua_filestream__fromfp(fp, fclose);
  _mulret_1.r2 = ((nlstring){(uint8_t*)"", 0});
  _mulret_1.r3 = 0;
  return _mulret_1;
}
nlmulret_nlboolean_nlstring_nlint64 nelua_filestream_close(nelua_filestream_ptr self) {
  nelua_FStream_ptr fs = self->fs;
  if(((!(fs != NULL)) || (!(fs->fp != NULL)))) {
    return (nlmulret_nlboolean_nlstring_nlint64){false, ((nlstring){(uint8_t*)"attempt to use a closed file", 28}), -1};
  }
  if((((fs->fp == stdout) || (fs->fp == stderr)) || (fs->fp == stdin))) {
    return (nlmulret_nlboolean_nlstring_nlint64){false, ((nlstring){(uint8_t*)"cannot close standard file", 26}), -1};
  }
  int res = 0;
  if((fs->closef != NULL)) {
    res = fs->closef(fs->fp);
  }
  self->fs->fp = ((FILE_ptr)NULL);
  self->fs->closef = (function_4jgCZA213GoJ9669W)NULL;
  if((res != 0)) {
    nlmulret_nlstring_nlint64 _ret_1 = nelua_geterrno_1();
    return (nlmulret_nlboolean_nlstring_nlint64){false, _ret_1.r1, _ret_1.r2};
  }
  return (nlmulret_nlboolean_nlstring_nlint64){true, (nlstring){0}, 0};
}
void nelua_filestream_destroy(nelua_filestream_ptr self) {
  nelua_FStream_ptr fs = self->fs;
  if((fs != NULL)) {
    if(((fs->fp != NULL) && (fs->closef != NULL))) {
      nelua_filestream_close(self);
    }
    nelua_GCAllocator_delete_3((&nelua_gc_allocator), self->fs);
  }
  self->fs = ((nelua_FStream_ptr)NULL);
}
void nelua_filestream___close(nelua_filestream_ptr self) {
  nelua_filestream_destroy(self);
}
nlmulret_nlint64_nlstring_nlint64 nelua_filestream_seek_1(nelua_filestream_ptr self, nlstring whence, int64_t offset) {
  FILE_ptr fp = nelua_filestream__getfp(self);
  if((!(fp != NULL))) {
    return (nlmulret_nlint64_nlstring_nlint64){-1, ((nlstring){(uint8_t*)"attempt to use a closed file", 28}), -1};
  }
  int op = 0;
  if(nelua_nlstring___eq(whence, ((nlstring){(uint8_t*)"set", 3}))) {
    op = SEEK_SET;
  } else if(nelua_nlstring___eq(whence, ((nlstring){(uint8_t*)"end", 3}))) {
    op = SEEK_END;
  } else if(nelua_nlstring___eq(whence, ((nlstring){(uint8_t*)"cur", 3}))) {
    op = SEEK_CUR;
  } else {
    return (nlmulret_nlint64_nlstring_nlint64){-1, ((nlstring){(uint8_t*)"invalid whence", 14}), -1};
  }
  int64_t len = 0;
  nlstring errmsg = (nlstring){0};
  int64_t status = 0;
  if((fseek(fp, (long)offset, op) == 0)) {
    len = (int64_t)ftell(fp);
  } else {
    len = -1;
    nlmulret_nlstring_nlint64 _asgnret_1 = nelua_geterrno_1();
    errmsg = _asgnret_1.r1;
    status = _asgnret_1.r2;
  }
  return (nlmulret_nlint64_nlstring_nlint64){len, errmsg, status};
}
bool nelua_eq_nlcint_nluint8(int a, uint8_t b) {
  return (uint32_t)a == (uint32_t)b && a >= 0;
}
nlmulret_nlboolean_nlstring nelua_readline(nelua_stringbuilderT_ptr sb, FILE_ptr fp, bool chop) {
  int c = 0;
  {
    bool _repeat_stop;
    do {
      uint32_t nr = 0U;
      nelua_span_uint8_ buff = nelua_stringbuilderT_prepare(sb, 1024U);
      if(nelua_span_uint8__empty(buff)) {
        return (nlmulret_nlboolean_nlstring){false, ((nlstring){(uint8_t*)"out of buffer memory", 20})};
      }
      while((nr < 1024U)) {
        c = fgetc(fp);
        if(((c == EOF) || nelua_eq_nlcint_nluint8(c, 10U))) {
          break;
        }
        (*(uint8_t*)nelua_assert_deref(nelua_span_uint8____atindex(buff, (uintptr_t)nr))) = (uint8_t)c;
        nr = (nr + 1);
      }
      nelua_stringbuilderT_commit(sb, (uintptr_t)nr);
      _repeat_stop = ((c == EOF) || nelua_eq_nlcint_nluint8(c, 10U));
    } while(!_repeat_stop);
  }
  if(((!chop) && nelua_eq_nlcint_nluint8(c, 10U))) {
    if((!nelua_stringbuilderT_writebyte_1(sb, (uint8_t)c, NELUA_NIL))) {
      return (nlmulret_nlboolean_nlstring){false, ((nlstring){(uint8_t*)"out of buffer memory", 20})};
    }
  }
  return (nlmulret_nlboolean_nlstring){(nelua_eq_nlcint_nluint8(c, 10U) || (sb->size > 0)), (nlstring){0}};
}
nlmulret_nlboolean_nlstring nelua_readall(nelua_stringbuilderT_ptr sb, FILE_ptr fp) {
  {
    bool _repeat_stop;
    do {
      nelua_span_uint8_ p = nelua_stringbuilderT_prepare(sb, 1024U);
      if(nelua_span_uint8__empty(p)) {
        return (nlmulret_nlboolean_nlstring){false, ((nlstring){(uint8_t*)"out of buffer memory", 20})};
      }
      size_t nr = fread((void*)p.data, 1U, 1024U, fp);
      nelua_stringbuilderT_commit(sb, (uintptr_t)nr);
      _repeat_stop = (nr < 1024U);
    } while(!_repeat_stop);
  }
  return (nlmulret_nlboolean_nlstring){true, (nlstring){0}};
}
nlmulret_nlstring_nlstring_nlint64 nelua_filestream_read_1(nelua_filestream_ptr self, nlstring fmt) {
  FILE_ptr fp = nelua_filestream__getfp(self);
  if((!(fp != NULL))) {
    return (nlmulret_nlstring_nlstring_nlint64){(nlstring){0}, ((nlstring){(uint8_t*)"attempt to use a closed file", 28}), -1};
  }
  nelua_stringbuilderT sb = (nelua_stringbuilderT){0};
  bool success = false;
  nlstring errmsg = (nlstring){0};
  clearerr(fp);
  uint8_t c = fmt.data[0];
  if((c == 42U)) {
    c = fmt.data[1];
  }
  if((c == 108U)) {
    nlmulret_nlboolean_nlstring _asgnret_1 = nelua_readline((&sb), fp, true);
    success = _asgnret_1.r1;
    errmsg = _asgnret_1.r2;
  } else if((c == 76U)) {
    nlmulret_nlboolean_nlstring _asgnret_2 = nelua_readline((&sb), fp, false);
    success = _asgnret_2.r1;
    errmsg = _asgnret_2.r2;
  } else if((c == 97U)) {
    nlmulret_nlboolean_nlstring _asgnret_3 = nelua_readall((&sb), fp);
    success = _asgnret_3.r1;
    errmsg = _asgnret_3.r2;
  } else {
    nelua_panic_string(((nlstring){(uint8_t*)"invalid format", 14}));
  }
  int64_t status = 0;
  if((ferror(fp) != 0)) {
    success = false;
    nlmulret_nlstring_nlint64 _asgnret_4 = nelua_geterrno_1();
    errmsg = _asgnret_4.r1;
    status = _asgnret_4.r2;
  }
  nlstring s = (nlstring){0};
  if(success) {
    s = nelua_stringbuilderT_promote((&sb));
  } else {
    if((nelua_nlstring___len(errmsg) == 0)) {
      errmsg = ((nlstring){(uint8_t*)"eof", 3});
      status = (int64_t)EOF;
    } else if((status == 0)) {
      status = -1;
    }
    nelua_stringbuilderT_destroy((&sb));
  }
  return (nlmulret_nlstring_nlstring_nlint64){s, errmsg, status};
}
bool nelua_filestream_isopen(nelua_filestream_ptr self) {
  return ((self->fs != ((nelua_FStream_ptr)NULL)) && (self->fs->fp != ((FILE_ptr)NULL)));
}
entropy_render_shader_Shader entropy_render_shader_Shader_load_from_file(nlstring path) {
  nelua_filestream file = nelua_filestream_open_1(path, ((nlstring){(uint8_t*)"rb", 2})).r1;
  nelua_filestream_seek_1((&file), ((nlstring){(uint8_t*)"set", 3}), 0);
  WGPUShaderModuleWGSLDescriptor_ptr wgsl_descriptor = nelua_GCAllocator_new_4((&nelua_gc_allocator), NELUA_NIL, NELUA_NIL, NELUA_NIL);
  (*(WGPUShaderModuleWGSLDescriptor*)nelua_assert_deref(wgsl_descriptor)) = (WGPUShaderModuleWGSLDescriptor){.chain = {.sType = 6}, .code = nelua_assert_string2cstring(nelua_filestream_read_1((&file), ((nlstring){(uint8_t*)"*a", 2})).r1)};
  nelua_filestream_close((&file));
  return (entropy_render_shader_Shader){.descriptor = {.nextInChain = ((WGPUChainedStruct_ptr)wgsl_descriptor)}};
}
void entropy_render_shader_Shader_create(entropy_render_shader_Shader_ptr self, WGPUDeviceImpl_ptr device) {
  self->module = wgpuDeviceCreateShaderModule(device, (&self->descriptor));
}
void entropy_render_shader_Shader_cleanup(entropy_render_shader_Shader_ptr self) {
  wgpuShaderModuleDrop(self->module);
}
nlmulret_nelua_filestream_nlstring_nlint64 nelua_io_open_1(nlstring filename, nlniltype mode) {
  nlmulret_nelua_filestream_nlstring_nlint64 _mulret_1;
  nlmulret_nelua_filestream_nlstring_nlint64 _ret_1 = nelua_filestream_open_2(filename, NELUA_NIL);
  _mulret_1.r1 = _ret_1.r1;
  _mulret_1.r2 = _ret_1.r2;
  _mulret_1.r3 = _ret_1.r3;
  return _mulret_1;
}
void nelua_assert_line_93(bool cond, nlstring msg) {
  if(NELUA_UNLIKELY(!cond)) {
    nelua_write_stderr("/nix/store/w4nkds3jq9r5ni6w5fd8287i9ikzcc1p-nelua-9de66a3/lib/nelua/lib/io.nelua:274:16: runtime error: ", 104, false);
    nelua_write_stderr((const char*)msg.data, msg.size, false);
    nelua_write_stderr("\n    assert(file:isopen(), 'cannot open file')\n               ^~~~~~~~~\n", 72, true);
    nelua_abort();
  }
}
nlmulret_nlboolean_nlstring nelua_lines_next(nelua_LinesState state, nlstring prevstr) {
  nlmulret_nlstring_nlstring_nlint64 _asgnret_1 = nelua_filestream_read_1((&state.file), state.fmt);
  nlstring str = _asgnret_1.r1;
  int64_t status = _asgnret_1.r3;
  return (nlmulret_nlboolean_nlstring){(status == 0), str};
}
nlmulret_function_3z5zrzypWbveb3uzk_nelua_LinesState_nlstring_nelua_filestream nelua_io_lines_1(nlstring filename, nlniltype fmt) {
  nelua_filestream file = nelua_io_open_1(filename, NELUA_NIL).r1;
  nelua_assert_line_93(nelua_filestream_isopen((&file)), ((nlstring){(uint8_t*)"cannot open file", 16}));
  nlstring fmt_1 = ((nlstring){(uint8_t*)"l", 1});
  return (nlmulret_function_3z5zrzypWbveb3uzk_nelua_LinesState_nlstring_nelua_filestream){nelua_lines_next, (nelua_LinesState){.file = file, .fmt = fmt_1}, (nlstring){0}, file};
}
uint32_t nelua_assert_narrow_nlint64_nluint32(int64_t x) {
  if(NELUA_UNLIKELY(x < 0 || x > 0xffffffffLL)) {
    nelua_panic_cstring("narrow casting from int64 to uint32 failed");
  }
  return (uint32_t)x;
}
entropy_scene_mesh_Mesh entropy_scene_mesh_Mesh_load_from_obj(nlstring path) {
  entropy_scene_mesh_Mesh result = (entropy_scene_mesh_Mesh){0};
  nelua_vector_Vertex_ vertices = (nelua_vector_Vertex_){0};
  nelua_vector_uint32_ indices = (nelua_vector_uint32_){0};
  {
    nlmulret_function_3z5zrzypWbveb3uzk_nelua_LinesState_nlstring_nelua_filestream _asgnret_1 = nelua_io_lines_1(path, NELUA_NIL);
    function_3z5zrzypWbveb3uzk __fornext = _asgnret_1.r1;
    nelua_LinesState __forstate = _asgnret_1.r2;
    nlstring __fornextit = _asgnret_1.r3;
    nelua_filestream __forclose = _asgnret_1.r4;
    while(true) {
      nlmulret_nlboolean_nlstring _asgnret_2 = __fornext(__forstate, __fornextit);
      bool __forcont = _asgnret_2.r1;
      nlstring line = _asgnret_2.r2;
      if((!__forcont)) {
        break;
      }
      __fornextit = line;
      {
        nlmulret_nlboolean_nelua_sequence_string_ _asgnret_3 = nelua_nlstring_match_1(line, ((nlstring){(uint8_t*)"v (%S+) (%S+) (%S+)", 19}), NELUA_NIL);
        bool matched = _asgnret_3.r1;
        nelua_sequence_string_ captures = _asgnret_3.r2;
        if(matched) {
          nelua_vector_Vertex__push((&vertices), ({
            entropy_scene_mesh_Vertex _tmp = {0};
            _tmp.pos = ({
              entropy_math_vec3_Vec3 _tmp = {0};
              _tmp.x = (float)nelua_tonumber_1((*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&captures), 1U))), NELUA_NIL);
              _tmp.y = (float)nelua_tonumber_1((*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&captures), 2U))), NELUA_NIL);
              _tmp.z = (float)nelua_tonumber_1((*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&captures), 3U))), NELUA_NIL);
              _tmp;
            });
            _tmp.col = (entropy_math_vec4_Vec4){1.0f, 1.0f, 1.0f, 1.0f};
            _tmp.uv = (entropy_math_vec2_Vec2){0.0f, 0.0f};
            _tmp;
          }));
        }
      }
    }
    { /* defer */
      nelua_filestream___close((&__forclose));
    }
  }
  {
    nlmulret_function_3z5zrzypWbveb3uzk_nelua_LinesState_nlstring_nelua_filestream _asgnret_4 = nelua_io_lines_1(path, NELUA_NIL);
    function_3z5zrzypWbveb3uzk __fornext = _asgnret_4.r1;
    nelua_LinesState __forstate = _asgnret_4.r2;
    nlstring __fornextit = _asgnret_4.r3;
    nelua_filestream __forclose = _asgnret_4.r4;
    while(true) {
      nlmulret_nlboolean_nlstring _asgnret_5 = __fornext(__forstate, __fornextit);
      bool __forcont = _asgnret_5.r1;
      nlstring line = _asgnret_5.r2;
      if((!__forcont)) {
        break;
      }
      __fornextit = line;
      {
        nlmulret_nlboolean_nelua_sequence_string_ _asgnret_6 = nelua_nlstring_match_1(line, ((nlstring){(uint8_t*)"f (%S+) (%S+) (%S+)", 19}), NELUA_NIL);
        bool matched = _asgnret_6.r1;
        nelua_sequence_string_ captures = _asgnret_6.r2;
        if(matched) {
          nelua_vector_uint32__push((&indices), nelua_assert_narrow_nlint64_nluint32((nelua_tointeger_1((*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&captures), 1U))), NELUA_NIL) - 1)));
          nelua_vector_uint32__push((&indices), nelua_assert_narrow_nlint64_nluint32((nelua_tointeger_1((*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&captures), 2U))), NELUA_NIL) - 1)));
          nelua_vector_uint32__push((&indices), nelua_assert_narrow_nlint64_nluint32((nelua_tointeger_1((*(nlstring*)nelua_assert_deref(nelua_sequence_string____atindex((&captures), 3U))), NELUA_NIL) - 1)));
        }
      }
    }
    { /* defer */
      nelua_filestream___close((&__forclose));
    }
  }
  result.vertices = vertices;
  result.indices = indices;
  return result;
}
entropy_scene_mesh_Mesh entropy_scene_mesh_Mesh_clone(entropy_scene_mesh_Mesh_ptr self) {
  entropy_scene_mesh_Mesh result = (entropy_scene_mesh_Mesh){0};
  result.vertices = self->vertices;
  result.indices = self->indices;
  return result;
}
size_t nelua_assert_narrow_nlisize_nlcsize(intptr_t x) {
  if(NELUA_UNLIKELY(x < 0)) {
    nelua_panic_cstring("narrow casting from isize to csize failed");
  }
  return (size_t)x;
}
void entropy_scene_mesh_Mesh_prepare_1(entropy_scene_mesh_Mesh_ptr self, entropy_render_renderer_RendererImplT renderer) {
  self->vertex_buffer = wgpuDeviceCreateBuffer(renderer.device, NELUA_LITERAL_REF(WGPUBufferDescriptor, ((WGPUBufferDescriptor){.label = (char*)"mesh vertex buffer", .usage = 32U, .size = (uint64_t)(36 * nelua_vector_Vertex____len((&self->vertices))), .mappedAtCreation = true})));
  entropy_scene_mesh_Vertex_arr0_ptr vertex_buffer_mapped = ((entropy_scene_mesh_Vertex_arr0_ptr)wgpuBufferGetMappedRange(self->vertex_buffer, 0U, nelua_assert_narrow_nlisize_nlcsize((36 * nelua_vector_Vertex____len((&self->vertices))))));
  for(intptr_t i = 0, _end = (nelua_vector_Vertex____len((&self->vertices)) - 1); i <= _end; i += 1) {
    vertex_buffer_mapped[i] = (*(entropy_scene_mesh_Vertex*)nelua_assert_deref(nelua_vector_Vertex____atindex((&self->vertices), nelua_assert_narrow_nlisize_nlusize(i))));
  }
  wgpuBufferUnmap(self->vertex_buffer);
  self->index_buffer = wgpuDeviceCreateBuffer(renderer.device, NELUA_LITERAL_REF(WGPUBufferDescriptor, ((WGPUBufferDescriptor){.label = (char*)"mesh index buffer", .usage = 16U, .size = (uint64_t)(4 * nelua_vector_uint32____len((&self->indices))), .mappedAtCreation = true})));
  nluint32_arr0_ptr index_buffer_mapped = ((nluint32_arr0_ptr)wgpuBufferGetMappedRange(self->index_buffer, 0U, nelua_assert_narrow_nlisize_nlcsize((4 * nelua_vector_uint32____len((&self->indices))))));
  for(intptr_t i = 0, _end = (nelua_vector_uint32____len((&self->indices)) - 1); i <= _end; i += 1) {
    index_buffer_mapped[i] = (*(uint32_t*)nelua_assert_deref(nelua_vector_uint32____atindex((&self->indices), nelua_assert_narrow_nlisize_nlusize(i))));
  }
  wgpuBufferUnmap(self->index_buffer);
}
nltype nelua_require_entropy_scene_mesh(nlniltype modname) {
  entropy_world_World_r_14(NELUA_NIL, NELUA_NIL);
  return NELUA_NIL;
}
nltype nelua_require_entropy_scene_mesh_cached(nlniltype modname) {
  static bool loaded = false;
  static nltype cache;
  if(!loaded) {
    cache = nelua_require_entropy_scene_mesh(NELUA_NIL);
    loaded = true;
  }
  return cache;
}
void entropy_render_impl_basic_Impl_init_1(entropy_render_impl_basic_Impl_ptr self, entropy_render_renderer_RendererImplT_ptr renderer) {
  entropy_render_shader_Shader vs_shader = entropy_render_shader_Shader_load_from_file(((nlstring){(uint8_t*)"entropy/render/impl/basic/vert.wgsl", 35}));
  entropy_render_shader_Shader_create((&vs_shader), renderer->device);
  WGPUVertexBufferLayout_arr1 vertex_buffer_layouts = (WGPUVertexBufferLayout_arr1){{{.arrayStride = 36U, .stepMode = 0, .attributeCount = 3U, .attributes = ((WGPUVertexAttribute_ptr)NELUA_LITERAL_REF(WGPUVertexAttribute_arr3, ((WGPUVertexAttribute_arr3){{{.shaderLocation = 0U, .offset = 0U, .format = 21}, {.shaderLocation = 1U, .offset = 12U, .format = 22}, {.shaderLocation = 2U, .offset = 28U, .format = 20}}})))}}};
  WGPUVertexState vertex = (WGPUVertexState){.module = vs_shader.module, .entryPoint = (char*)"main", .bufferCount = 1U, .buffers = ((WGPUVertexBufferLayout_ptr)(&vertex_buffer_layouts))};
  entropy_render_shader_Shader fs_shader = entropy_render_shader_Shader_load_from_file(((nlstring){(uint8_t*)"entropy/render/impl/basic/frag.wgsl", 35}));
  entropy_render_shader_Shader_create((&fs_shader), renderer->device);
  WGPUBlendState blend = (WGPUBlendState){.color = {.srcFactor = 1, .dstFactor = 5, .operation = 0}, .alpha = {.srcFactor = 1, .dstFactor = 5, .operation = 0}};
  WGPUColorTargetState color_target = (WGPUColorTargetState){.format = renderer->target_config.format, .blend = (&blend), .writeMask = 15U};
  WGPUFragmentState fragment = (WGPUFragmentState){.module = fs_shader.module, .entryPoint = (char*)"main", .targetCount = 1U, .targets = (&color_target)};
  WGPUBindGroupLayoutEntry_arr1 globals_bind_group_layout_entries = (WGPUBindGroupLayoutEntry_arr1){{{.binding = 0U, .visibility = 1U, .buffer = {.type = 1, .hasDynamicOffset = false, .minBindingSize = 64U}}}};
  WGPUBindGroupLayoutImpl_ptr globals_bind_group_layout = wgpuDeviceCreateBindGroupLayout(renderer->device, NELUA_LITERAL_REF(WGPUBindGroupLayoutDescriptor, ((WGPUBindGroupLayoutDescriptor){.entryCount = 1U, .entries = ((WGPUBindGroupLayoutEntry_ptr)(&globals_bind_group_layout_entries))})));
  self->globals_buffer = wgpuDeviceCreateBuffer(renderer->device, NELUA_LITERAL_REF(WGPUBufferDescriptor, ((WGPUBufferDescriptor){.label = (char*)"basic globals buffer", .usage = 72U, .size = 64U, .mappedAtCreation = false})));
  self->globals_bind_group = wgpuDeviceCreateBindGroup(renderer->device, NELUA_LITERAL_REF(WGPUBindGroupDescriptor, ((WGPUBindGroupDescriptor){.label = (char*)"basic globals bind group", .layout = globals_bind_group_layout, .entryCount = 1U, .entries = ((WGPUBindGroupEntry_ptr)NELUA_LITERAL_REF(WGPUBindGroupEntry_arr1, ((WGPUBindGroupEntry_arr1){{{.binding = 0U, .buffer = self->globals_buffer, .size = 64U}}})))})));
  WGPUPipelineLayoutImpl_ptr pipeline_layout = wgpuDeviceCreatePipelineLayout(renderer->device, NELUA_LITERAL_REF(WGPUPipelineLayoutDescriptor, ((WGPUPipelineLayoutDescriptor){.bindGroupLayoutCount = 1U, .bindGroupLayouts = (WGPUBindGroupLayoutImpl_ptr_ptr)NELUA_LITERAL_REF(WGPUBindGroupLayoutImpl_ptr_arr1, ((WGPUBindGroupLayoutImpl_ptr_arr1){{globals_bind_group_layout}})), .nextInChain = ((WGPUChainedStruct_ptr)NELUA_LITERAL_REF(WGPUPipelineLayoutExtras, ((WGPUPipelineLayoutExtras){.chain = {.sType = 1610612740}, .pushConstantRangeCount = 1U, .pushConstantRanges = ((WGPUPushConstantRange_ptr)NELUA_LITERAL_REF(WGPUPushConstantRange_arr1, ((WGPUPushConstantRange_arr1){{{.stages = 1U, .start = 0U, .end = 64U}}})))})))})));
  WGPURenderPipelineDescriptor pipeline_descriptor = (WGPURenderPipelineDescriptor){.label = (char*)"basic render pipeline", .layout = pipeline_layout, .vertex = vertex, .fragment = (&fragment), .primitive = {.cullMode = 2, .topology = 3, .stripIndexFormat = 0, .frontFace = 0}, .multisample = {.count = 1U, .mask = 0xffffffffULL, .alphaToCoverageEnabled = false}, .depthStencil = NELUA_LITERAL_REF(WGPUDepthStencilState, ((WGPUDepthStencilState){.format = 40, .depthWriteEnabled = true, .depthCompare = 2, .stencilFront = {.compare = 8, .failOp = 0, .depthFailOp = 0, .passOp = 0}, .stencilBack = {.compare = 8, .failOp = 0, .depthFailOp = 0, .passOp = 0}, .stencilReadMask = 0xffffffffULL, .stencilWriteMask = 0xffffffffULL}))};
  self->pipeline = wgpuDeviceCreateRenderPipeline(renderer->device, (&pipeline_descriptor));
  entropy_render_shader_Shader_cleanup((&vs_shader));
  entropy_render_shader_Shader_cleanup((&fs_shader));
  wgpuPipelineLayoutDrop(pipeline_layout);
  wgpuBindGroupLayoutDrop(globals_bind_group_layout);
}
void entropy_render_impl_basic_Impl_cleanup_1(entropy_render_impl_basic_Impl_ptr self, entropy_render_renderer_RendererImplT_ptr renderer) {
  wgpuRenderPipelineDrop(self->pipeline);
  wgpuBufferDrop(self->globals_buffer);
  wgpuBindGroupDrop(self->globals_bind_group);
}
void entropy_render_impl_basic_Impl_resize_1(entropy_render_impl_basic_Impl_ptr self, entropy_render_renderer_RendererImplT_ptr renderer) {
}
uint32_t nelua_assert_narrow_nlisize_nluint32(intptr_t x) {
  if(NELUA_UNLIKELY(x < 0 || x > 0xffffffffLL)) {
    nelua_panic_cstring("narrow casting from isize to uint32 failed");
  }
  return (uint32_t)x;
}
void entropy_render_impl_basic_Impl_render_1(entropy_render_impl_basic_Impl_ptr self, entropy_render_renderer_RendererImplT_ptr renderer, WGPURenderPassEncoderImpl_ptr pass, WGPUCommandEncoderImpl_ptr encoder, WGPUTextureViewImpl_ptr target, entropy_world_World_ptr world) {
  entropy_scene_camera_Camera camera = (*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(entropy_world_World_s_4(world, NELUA_NIL), 0U)));
  entropy_math_mat4_Mat4 view = entropy_scene_camera_Camera_view_matrix((&camera));
  entropy_math_mat4_Mat4 proj = entropy_scene_camera_Camera_proj_matrix((&camera), renderer->target_config.width, renderer->target_config.height);
  wgpuQueueWriteBuffer(renderer->queue, self->globals_buffer, 0U, (void*)NELUA_LITERAL_REF(entropy_render_impl_basic_Globals, ((entropy_render_impl_basic_Globals){.mvp = entropy_math_mat4_Mat4_transpose(NELUA_LITERAL_REF(entropy_math_mat4_Mat4, (entropy_math_mat4_Mat4___mul(proj, view))))})), 64U);
  wgpuRenderPassEncoderSetPipeline(pass, self->pipeline);
  wgpuRenderPassEncoderSetBindGroup(pass, 0U, self->globals_bind_group, 0U, (nluint32_ptr)NULL);
  entropy_world_Storage_Mesh__ptr meshes = entropy_world_World_s_5(world, NELUA_NIL);
  {
    nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize _asgnret_1 = nelua_mpairs_2(meshes);
    function_cn8qNCYTz9afPmWb __fornext = _asgnret_1.r1;
    entropy_world_Storage_Mesh__ptr __forstate = _asgnret_1.r2;
    intptr_t __fornextit = _asgnret_1.r3;
    while(true) {
      nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr _asgnret_2 = __fornext(__forstate, __fornextit);
      bool __forcont = _asgnret_2.r1;
      intptr_t id = _asgnret_2.r2;
      entropy_scene_mesh_Mesh_ptr mesh = _asgnret_2.r3;
      if((!__forcont)) {
        break;
      }
      __fornextit = id;
      {
        wgpuRenderPassEncoderSetVertexBuffer(pass, 0U, mesh->vertex_buffer, 0U, 0U);
        wgpuRenderPassEncoderSetIndexBuffer(pass, mesh->index_buffer, 2, 0U, 0U);
        entropy_math_mat4_Mat4 model = entropy_math_mat4_Mat4_transpose((&mesh->transform));
        wgpuRenderPassEncoderSetPushConstants(pass, 1U, 0U, 64U, (void*)(&model));
        wgpuRenderPassEncoderDrawIndexed(pass, nelua_assert_narrow_nlisize_nluint32(nelua_vector_uint32____len((&mesh->indices))), 1U, 0U, 0, 0U);
      }
    }
  }
}
nltype nelua_require_entropy_render_impl_basic(nlniltype modname) {
  nelua_require_entropy_scene_mesh_cached(NELUA_NIL);  return NELUA_NIL;
}
void entropy_scene_camera_Camera_look_at(entropy_scene_camera_Camera_ptr self, entropy_math_vec3_Vec3 target) {
  entropy_math_vec3_Vec3 dir = entropy_math_vec3_Vec3___sub(target, self->pos);
  self->rot = entropy_math_vec3_Vec3_norm((&dir));
}
entropy_math_mat4_Mat4 entropy_scene_camera_Camera_view_matrix(entropy_scene_camera_Camera_ptr self) {
  return entropy_math_mat4_Mat4_look_at(self->pos, entropy_math_vec3_Vec3___add(self->pos, self->rot), (entropy_math_vec3_Vec3){0.0f, 1.0f, 0.0f});
}
entropy_math_mat4_Mat4 entropy_scene_camera_Camera_proj_matrix(entropy_scene_camera_Camera_ptr self, uint32_t width, uint32_t height) {
  return entropy_math_mat4_Mat4_perspective(self->fov, (float)(width / (double)height), self->z_near, self->z_far);
}
nltype nelua_require_entropy_scene_camera(nlniltype modname) {
  entropy_world_World_r_15(NELUA_NIL, NELUA_NIL);
  return NELUA_NIL;
}
void main_anonfunc_1(void* user, uint32_t width, uint32_t height) {
  entropy_render_renderer_RendererImplT_ptr crenderer = ((entropy_render_renderer_RendererImplT_ptr)user);
  entropy_render_renderer_RendererImplT_resize(crenderer, width, height);
}
int nelua_main(int argc, char** argv) {
  nelua_require_entropy_world_pointer_cached(NELUA_NIL);  entropy_world_World_r_1(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_2(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_3(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_4(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_5(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_6(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_7(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_8(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_9(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_10(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_11(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_12(NELUA_NIL, NELUA_NIL);
  entropy_world_World_r_13(NELUA_NIL, NELUA_NIL);
  main_positions = entropy_world_World_s_1((&main_world), NELUA_NIL);
  entropy_world_Storage_Vec2__reserve(main_positions, 10010U);
  main_velocities = entropy_world_World_s_2((&main_world), NELUA_NIL);
  entropy_world_Storage_Vec2__1_reserve(main_velocities, 10010U);
  main_entities = entropy_world_World_s_3((&main_world), NELUA_NIL);
  entropy_world_Storage_Entity__reserve(main_entities, 10010U);
  for(int64_t i = 0; i < 10; i += 1) {
    uintptr_t pos = entropy_world_Storage_Vec2__create(main_positions, (entropy_math_vec2_Vec2){.x = (float)i, .y = (float)i});
    uintptr_t vel = entropy_world_Storage_Vec2__1_create(main_velocities, (entropy_math_vec2_Vec2){.x = (float)i, .y = (float)i});
    entropy_world_Storage_Entity__create(main_entities, (main_Entity){.pos = pos, .vel = vel});
  }
  nelua_print_1(((nlstring){(uint8_t*)"===== Initial State =====", 25}));
  {
    nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize _asgnret_1 = nelua_mpairs_3(main_entities);
    function_22cTQHv4wXQKFZ1xf __fornext = _asgnret_1.r1;
    entropy_world_Storage_Entity__ptr __forstate = _asgnret_1.r2;
    intptr_t __fornextit = _asgnret_1.r3;
    while(true) {
      nlmulret_nlboolean_nlisize_main_Entity_ptr _asgnret_2 = __fornext(__forstate, __fornextit);
      bool __forcont = _asgnret_2.r1;
      intptr_t id = _asgnret_2.r2;
      main_Entity_ptr e = _asgnret_2.r3;
      if((!__forcont)) {
        break;
      }
      __fornextit = id;
      {
        {
          nlstring _tmp1 = entropy_math_vec2_Vec2___tostring((&(*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2____atindex(main_positions, e->pos)))));
          nlstring _tmp2 = entropy_math_vec2_Vec2___tostring((&(*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2__1___atindex(main_velocities, e->vel)))));
          nelua_print_2(id, e, _tmp1, _tmp2);
        }
      }
    }
  }
  {
    nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize _asgnret_3 = nelua_mpairs_3(main_entities);
    function_22cTQHv4wXQKFZ1xf __fornext = _asgnret_3.r1;
    entropy_world_Storage_Entity__ptr __forstate = _asgnret_3.r2;
    intptr_t __fornextit = _asgnret_3.r3;
    while(true) {
      nlmulret_nlboolean_nlisize_main_Entity_ptr _asgnret_4 = __fornext(__forstate, __fornextit);
      bool __forcont = _asgnret_4.r1;
      intptr_t _ = _asgnret_4.r2;
      main_Entity_ptr e = _asgnret_4.r3;
      if((!__forcont)) {
        break;
      }
      __fornextit = _;
      {
        (*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2____atindex(main_positions, e->pos))) = ({
          entropy_math_vec2_Vec2 _tmp1 = (*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2____atindex(main_positions, e->pos)));
          entropy_math_vec2_Vec2 _tmp2 = (*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2__1___atindex(main_velocities, e->vel)));
          entropy_math_vec2_Vec2___add(_tmp1, _tmp2);
        });
      }
    }
  }
  nelua_print_1(((nlstring){(uint8_t*)"===== Final State =====", 23}));
  {
    nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize _asgnret_5 = nelua_mpairs_3(main_entities);
    function_22cTQHv4wXQKFZ1xf __fornext = _asgnret_5.r1;
    entropy_world_Storage_Entity__ptr __forstate = _asgnret_5.r2;
    intptr_t __fornextit = _asgnret_5.r3;
    while(true) {
      nlmulret_nlboolean_nlisize_main_Entity_ptr _asgnret_6 = __fornext(__forstate, __fornextit);
      bool __forcont = _asgnret_6.r1;
      intptr_t id = _asgnret_6.r2;
      main_Entity_ptr e = _asgnret_6.r3;
      if((!__forcont)) {
        break;
      }
      __fornextit = id;
      {
        {
          nlstring _tmp1 = entropy_math_vec2_Vec2___tostring((&(*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2____atindex(main_positions, e->pos)))));
          nlstring _tmp2 = entropy_math_vec2_Vec2___tostring((&(*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2__1___atindex(main_velocities, e->vel)))));
          nelua_print_2(id, e, _tmp1, _tmp2);
        }
      }
    }
  }
  nelua_print_1(((nlstring){(uint8_t*)"===== Benching with 10,000 Entities =====", 41}));
  main_now = nelua_os_now();
  for(int64_t i = 0; i < 10000; i += 1) {
    if((nelua_assert_imod_nlint64(i, 10) == 0)) {
      entropy_world_Storage_Entity__create(main_entities, ({
        main_Entity _tmp = {0};
        _tmp.pos = entropy_world_Storage_Vec2__create(main_positions, (entropy_math_vec2_Vec2){.x = (float)i, .y = (float)i});
        _tmp.vel = entropy_world_Storage_Vec2__1_create(main_velocities, (entropy_math_vec2_Vec2){.x = (float)i, .y = (float)i});
        _tmp;
      }));
    } else {
      entropy_world_Storage_Entity__create(main_entities, (main_Entity){.pos = entropy_world_Storage_Vec2__create(main_positions, (entropy_math_vec2_Vec2){.x = (float)i, .y = (float)i})});
    }
  }
  nelua_print_3(((nlstring){(uint8_t*)"Creation: ", 10}), ((nelua_os_now() - main_now) * 1000000));
  for(int64_t i = 0; i < 1000; i += 1) {
    main_now = nelua_os_now();
    {
      nlmulret_function_22cTQHv4wXQKFZ1xf_entropy_world_Storage_Entity__ptr_nlisize _asgnret_7 = nelua_mpairs_3(main_entities);
      function_22cTQHv4wXQKFZ1xf __fornext = _asgnret_7.r1;
      entropy_world_Storage_Entity__ptr __forstate = _asgnret_7.r2;
      intptr_t __fornextit = _asgnret_7.r3;
      while(true) {
        nlmulret_nlboolean_nlisize_main_Entity_ptr _asgnret_8 = __fornext(__forstate, __fornextit);
        bool __forcont = _asgnret_8.r1;
        intptr_t id = _asgnret_8.r2;
        main_Entity_ptr e = _asgnret_8.r3;
        if((!__forcont)) {
          break;
        }
        __fornextit = id;
        {
          (*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2____atindex(main_positions, e->pos))) = ({
            entropy_math_vec2_Vec2 _tmp1 = (*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2____atindex(main_positions, e->pos)));
            entropy_math_vec2_Vec2 _tmp2 = (*(entropy_math_vec2_Vec2*)nelua_assert_deref(entropy_world_Storage_Vec2__1___atindex(main_velocities, e->vel)));
            entropy_math_vec2_Vec2___add(_tmp1, _tmp2);
          });
        }
      }
    }
    double time = (nelua_os_now() - main_now);
    nelua_vector_float64__push((&main_times), time);
  }
  {
    nlmulret_function_5RRHk7NVNoo3zrsdP_nelua_vector_float64__ptr_nlint64 _asgnret_9 = nelua_ipairs_1((&main_times));
    function_5RRHk7NVNoo3zrsdP __fornext = _asgnret_9.r1;
    nelua_vector_float64__ptr __forstate = _asgnret_9.r2;
    int64_t __fornextit = _asgnret_9.r3;
    while(true) {
      nlmulret_nlboolean_nlint64_nlfloat64 _asgnret_10 = __fornext(__forstate, __fornextit);
      bool __forcont = _asgnret_10.r1;
      int64_t _ = _asgnret_10.r2;
      double time = _asgnret_10.r3;
      if((!__forcont)) {
        break;
      }
      __fornextit = _;
      {
        main_avg = (main_avg + time);
      }
    }
  }
  main_avg = (main_avg / nelua_vector_float64____len((&main_times)));
  nelua_print_3(((nlstring){(uint8_t*)"Avg Iteration: ", 15}), (main_avg * 1000000));
  wgpuSetLogCallback(main_anonfunc, NULL);
  wgpuSetLogLevel(3);
  nelua_require_entropy_render_impl_basic(NELUA_NIL);  nelua_require_entropy_scene_camera(NELUA_NIL);  nelua_require_entropy_scene_mesh_cached(NELUA_NIL);  entropy_render_glfw_context_GLFWContext_init((&main_context), ((nlstring){(uint8_t*)"testing", 7}), 512U, 512U, true);
  entropy_render_renderer_RendererImplT_init((&main_renderer), main_context.device, main_context.format, main_context.width, main_context.height);
  main_context.user_pointer = (void*)(&main_renderer);
  main_context.resize_callback = main_anonfunc_1;
  main_cameras = entropy_world_World_s_4((&main_world), NELUA_NIL);
  main_camera_idx = entropy_world_Storage_Camera__create(main_cameras, (entropy_scene_camera_Camera){.pos = {10.0f, 10.0f, 10.0f}, .rot = {0.0f, 0.0f, 0.0f}, .fov = 90.0f, .z_near = 0.1f, .z_far = 100.0f});
  entropy_scene_camera_Camera_look_at((&(*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx)))), (entropy_math_vec3_Vec3){0.0f, 0.0f, 0.0f});
  main_teapot_mesh = entropy_scene_mesh_Mesh_load_from_obj(((nlstring){(uint8_t*)"./teapot.obj", 12}));
  main_cube_mesh = entropy_scene_mesh_Mesh_load_from_obj(((nlstring){(uint8_t*)"./cube.obj", 10}));
  main_meshes = entropy_world_World_s_5((&main_world), NELUA_NIL);
  for(int64_t y = -3; y <= 3; y += 1) {
    for(int64_t x = -3; x <= 3; x += 1) {
      for(int64_t z = -3; z <= 3; z += 1) {
        uintptr_t mesh_idx = 0U;
        if((((nelua_assert_imod_nlint64(y, 2) == 0) && (nelua_assert_imod_nlint64(x, 2) == 0)) && (nelua_assert_imod_nlint64(z, 2) == 0))) {
          mesh_idx = entropy_world_Storage_Mesh__create(main_meshes, entropy_scene_mesh_Mesh_clone((&main_teapot_mesh)));
        } else {
          mesh_idx = entropy_world_Storage_Mesh__create(main_meshes, entropy_scene_mesh_Mesh_clone((&main_cube_mesh)));
        }
        entropy_scene_mesh_Mesh_prepare_1((&(*(entropy_scene_mesh_Mesh*)nelua_assert_deref(entropy_world_Storage_Mesh____atindex(main_meshes, mesh_idx)))), main_renderer);
        (*(entropy_scene_mesh_Mesh*)nelua_assert_deref(entropy_world_Storage_Mesh____atindex(main_meshes, mesh_idx))).transform = entropy_math_mat4_Mat4___mul(entropy_math_mat4_Mat4_from_pos((entropy_math_vec3_Vec3){(float)(x * 5), (float)(z * 5), (float)(y * 5)}), entropy_math_mat4_Mat4_from_scl((entropy_math_vec3_Vec3){(float)x, (float)y, (float)z}));
      }
    }
  }
  while((!entropy_render_glfw_context_GLFWContext_should_close((&main_context)))) {
    double now_1 = entropy_world_World_now((&main_world));
    nlmulret_nlboolean_nelua_list_Event__ptr _asgnret_11 = entropy_render_glfw_context_GLFWContext_poll_event((&main_context));
    bool has_event = _asgnret_11.r1;
    nelua_list_Event__ptr event_queue = _asgnret_11.r2;
    if(has_event) {
      while((!nelua_list_Event__empty(event_queue))) {
        entropy_defs_event_Event event = nelua_list_Event__popfront(event_queue);
        if((event.type == 0)) {
          if((event.data.Key.action == 1)) {
            if((event.data.Key.key == 256)) {
              entropy_render_glfw_context_GLFWContext_close((&main_context));
            }
          }
          bool state = false;
          if(((event.data.Key.action == 1) || (event.data.Key.action == 2))) {
            state = true;
          } else if((event.data.Key.action == 0)) {
            state = false;
          }
          if((event.data.Key.key == 87)) {
            main_is_forward_pressed = state;
          } else if((event.data.Key.key == 83)) {
            main_is_backward_pressed = state;
          } else if((event.data.Key.key == 65)) {
            main_is_left_pressed = state;
          } else if((event.data.Key.key == 68)) {
            main_is_right_pressed = state;
          } else if((event.data.Key.key == 32)) {
            main_is_up_pressed = state;
          } else if((event.data.Key.key == 340)) {
            main_is_down_pressed = state;
          }
        } else if((event.type == 1)) {
          double mouse_dx = (event.data.MouseMotion.x - main_last_mouse_x);
          double mouse_dy = (event.data.MouseMotion.y - main_last_mouse_y);
          main_camera_yaw = (main_camera_yaw + (nelua_math_rad_2(mouse_dx) * 0.2));
          main_camera_pitch = nelua_math_clamp_1((main_camera_pitch + (nelua_math_rad_2(mouse_dy) * 0.2)), -1.5706963267948966, 1.5706963267948966);
          entropy_scene_camera_Camera_ptr camera = (&(*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))));
          camera->rot = entropy_math_vec3_Vec3_norm(NELUA_LITERAL_REF(entropy_math_vec3_Vec3, ((entropy_math_vec3_Vec3){(float)(nelua_math_cos_2(main_camera_yaw) * nelua_math_cos_2(main_camera_pitch)), (float)(-nelua_math_sin_2(main_camera_pitch)), (float)(nelua_math_sin_2(main_camera_yaw) * nelua_math_cos_2(main_camera_pitch))})));
          main_last_mouse_x = (double)event.data.MouseMotion.x;
          main_last_mouse_y = (double)event.data.MouseMotion.y;
        }
      }
    }
    if(main_is_forward_pressed) {
      (*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos = entropy_math_vec3_Vec3___add((*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos, entropy_math_vec3_Vec3_scale((&(*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).rot), 1.0f));
    }
    if(main_is_backward_pressed) {
      (*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos = entropy_math_vec3_Vec3___sub((*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos, entropy_math_vec3_Vec3_scale((&(*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).rot), 1.0f));
    }
    if(main_is_left_pressed) {
      (*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos = entropy_math_vec3_Vec3___sub((*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos, entropy_math_vec3_Vec3_scale(NELUA_LITERAL_REF(entropy_math_vec3_Vec3, (entropy_math_vec3_Vec3_norm(NELUA_LITERAL_REF(entropy_math_vec3_Vec3, (entropy_math_vec3_Vec3_cross((&(*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).rot), (entropy_math_vec3_Vec3){0.0f, 1.0f, 0.0f})))))), 1.0f));
    }
    if(main_is_right_pressed) {
      (*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos = entropy_math_vec3_Vec3___add((*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos, entropy_math_vec3_Vec3_scale(NELUA_LITERAL_REF(entropy_math_vec3_Vec3, (entropy_math_vec3_Vec3_norm(NELUA_LITERAL_REF(entropy_math_vec3_Vec3, (entropy_math_vec3_Vec3_cross((&(*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).rot), (entropy_math_vec3_Vec3){0.0f, 1.0f, 0.0f})))))), 1.0f));
    }
    if(main_is_up_pressed) {
      (*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos = entropy_math_vec3_Vec3___add((*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos, (entropy_math_vec3_Vec3){0.0f, 1.0f, 0.0f});
    }
    if(main_is_down_pressed) {
      (*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos = entropy_math_vec3_Vec3___sub((*(entropy_scene_camera_Camera*)nelua_assert_deref(entropy_world_Storage_Camera____atindex(main_cameras, main_camera_idx))).pos, (entropy_math_vec3_Vec3){0.0f, 1.0f, 0.0f});
    }
    {
      nlmulret_function_cn8qNCYTz9afPmWb_entropy_world_Storage_Mesh__ptr_nlisize _asgnret_12 = nelua_mpairs_2(main_meshes);
      function_cn8qNCYTz9afPmWb __fornext = _asgnret_12.r1;
      entropy_world_Storage_Mesh__ptr __forstate = _asgnret_12.r2;
      intptr_t __fornextit = _asgnret_12.r3;
      while(true) {
        nlmulret_nlboolean_nlisize_entropy_scene_mesh_Mesh_ptr _asgnret_13 = __fornext(__forstate, __fornextit);
        bool __forcont = _asgnret_13.r1;
        intptr_t _ = _asgnret_13.r2;
        entropy_scene_mesh_Mesh_ptr mesh = _asgnret_13.r3;
        if((!__forcont)) {
          break;
        }
        __fornextit = _;
        {
          mesh->transform = entropy_math_mat4_Mat4___mul(entropy_math_mat4_Mat4___mul(mesh->transform, entropy_math_mat4_Mat4_from_rot(0.01f, (entropy_math_vec3_Vec3){0.0f, 0.0f, 1.0f})), entropy_math_mat4_Mat4_from_rot(0.01f, (entropy_math_vec3_Vec3){1.0f, 0.0f, 0.0f}));
        }
      }
    }
    WGPUTextureViewImpl_ptr view = entropy_render_glfw_context_GLFWContext_view((&main_context));
    entropy_render_renderer_RendererImplT_render((&main_renderer), view, (&main_world));
    entropy_render_glfw_context_GLFWContext_present((&main_context));
    nelua_vector_float64__push((&main_fps_list), (1 / (entropy_world_World_now((&main_world)) - now_1)));
    if((nelua_vector_float64____len((&main_fps_list)) > 30)) {
      double avg_1 = 0.0;
      {
        nlmulret_function_5RRHk7NVNoo3zrsdP_nelua_vector_float64__ptr_nlint64 _asgnret_14 = nelua_ipairs_1((&main_fps_list));
        function_5RRHk7NVNoo3zrsdP __fornext = _asgnret_14.r1;
        nelua_vector_float64__ptr __forstate = _asgnret_14.r2;
        int64_t __fornextit = _asgnret_14.r3;
        while(true) {
          nlmulret_nlboolean_nlint64_nlfloat64 _asgnret_15 = __fornext(__forstate, __fornextit);
          bool __forcont = _asgnret_15.r1;
          int64_t _ = _asgnret_15.r2;
          double time = _asgnret_15.r3;
          if((!__forcont)) {
            break;
          }
          __fornextit = _;
          {
            avg_1 = (avg_1 + time);
          }
        }
      }
      avg_1 = (avg_1 / nelua_vector_float64____len((&main_fps_list)));
      nelua_print_3(((nlstring){(uint8_t*)"FPS: ", 5}), avg_1);
      nelua_vector_float64__clear((&main_fps_list));
    }
  }
  entropy_render_renderer_RendererImplT_cleanup((&main_renderer));
  entropy_render_glfw_context_GLFWContext_cleanup((&main_context));
  return 0;
}

