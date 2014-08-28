/*
*   KONNEX/EIB-Protocol-Stack.
*
*  (C) 2007-2014 by Christoph Schueler <github.com/Christoph2,
*                                       cpu12.gems@googlemail.com>
*
*   All Rights Reserved
*
*  This program is free softwKNXe; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free SoftwKNXe Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WKNXRANTY; without even the implied wKNXranty of
*  MERCHANTABILITY or FITNESS FOR A PKNXTICULKNX PURPOSE.  See the
*  GNU General Public License for more KnxEtails.
*
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free SoftwKNXe Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*/
#if !defined(__KNX_ET_H)
#define __KNX_ET_H

#include "knx_defs.h"
#include "knx_platform.h"

#if defined(__cplusplus)
extern "C"
{
#endif  /* __cplusplus */


#if defined(_WIN32) || defined(_WIN64)
    #define CPU_BREAKPOINT()            __debugbreak()
#else
    #define CPU_BREAKPOINT()
#endif

/*
** Some standard macros.
*/

/* check for C99-Compiler */
#if defined(__STDC_VERSION__)
    #if __STDC_VERSION__ >= 199901L
        #define _C99_COMPILER
    #endif
#endif

/* check for C11-Compiler */
#if defined(__STDC_VERSION__)
    #if __STDC_VERSION__>= 201112L
        #define _C11_COMPILER
    #endif
#endif

#if defined(_C99_COMPILER) || defined(_C1x_COMPILER)
    #define _MODERN_C
#else
    #define _LEGACY_C
#endif

/* Check for Freestanding-Environment */
#if !defined(__STDC_HOSTED__)
    #define _FREESTANDING
#endif

#if defined(_C99_COMPILER)
    #define INLINE      inline
    #define RESTRICT    restrict
#elif defined(_CPP_COMPILER)
    #define INLINE      inline
    #define RESTRICT
#else
    #if !defined(INLINE)
        #define INLINE
    #endif
    #define RESTRICT
#endif

#define VOID_EXPRESSION()           ((void)0)

#if !defined(UNREFERENCED_PARAMETER)
    #define UNREFERENCED_PARAMETER(p)   ((p) = (p))
#endif

#if !defined(MIN)
    #define MIN(a, b)                   (((a) > (b)) ? (b) : (a))
#endif

#if !defined(MAX)
    #define MAX(a, b)                   (((a) > (b)) ? (a) : (b))
#endif

#if !defined(BETWEEN)
    #define BETWEEN(x, min, max)        (((x) >= (min)) && ((x) <= (max)))
#endif

#if !defined(ABS)
    #define ABS(i)                      (((i) < 0) ? ((i) * -1) : ((i)))
#endif

#define SWAP_INPLACE(a, b)  \
    _BEGIN_BLOCK            \
        (a) = (a) ^ (b);    \
        (b) = (a) ^ (b);    \
        (a) = (a) ^ (b);    \
    _END_BLOCK

#if !defined(LOBYTE)
    #define LOBYTE(w)                   ((uint8_t)((uint16_t)((uint16_t)(w) & 0x00ffU)))
#endif

#if !defined(HIBYTE)
    #define HIBYTE(w)                   ((uint8_t)((uint16_t)(((uint16_t)(w ) >> 8) & 0x00ffU)))
#endif

#if !defined(LOWORD)
    #define LOWORD(dw)                  ((uint16_t)((uint32_t)((uint32_t)(dw) & 0xffffU)))
#endif

#if !defined(HIWORD)
    #define HIWORD(dw)                  ((uint16_t)((uint32_t)(((uint32_t)(dw) >> 16) & 0xffffU)))
#endif

#if !defined(MAKEWORD)
    #define MAKEWORD(h, l)              ((((uint16_t)((h) & ((uint8_t)0xff))) <<  (uint16_t)8) | ((uint16_t)((l) & ((uint8_t)0xff))))
#endif

#if !defined(MAKEDWORD)
    #define MAKEDWORD(h, l)             ((((uint32_t)((h) & ((uint16_t)0xffffu))) << (uint32_t)16) | ((uint32_t)((l) & ((uint16_t)0xffffu))))
#endif

#if !defined(INVERT_NIBBLE)
    #define INVERT_NIBBLE(b)            ((uint8_t)(((uint8_t) ~(b)) & ((uint8_t)0x0f)))
#endif

#if !defined(SIZEOF_ARRAY)
    #define SIZEOF_ARRAY(arr)           (sizeof((arr)) / sizeof((arr[0])))
#endif

#if !defined(BEYOND_ARRAY)
    #define BEYOND_ARRAY(arr)           ((arr) + SIZE_OF_ARRAY((arr)))
#endif

#define STATIC  static

#define _BEGIN_BLOCK                    do {
#define _END_BLOCK                      } while (0)

#if !defined(_countof)
    #define _countof(arr)               SIZEOF_ARRAY(arr)
#endif

#define __HEX(n)                        0x ## n ## LU
#define __BIN8(x)                                   \
    (((x)& 0x0000000FLU) ? 1 : 0)                   \
    + (((x)& 0x000000F0LU) ? 2 : 0)                 \
    + (((x)& 0x00000F00LU) ? 4 : 0)                 \
    + (((x)& 0x0000F000LU) ? 8 : 0)                 \
    + (((x)& 0x000F0000LU) ? 16 : 0)                \
    + (((x)& 0x00F00000LU) ? 32 : 0)                \
    + (((x)& 0x0F000000LU) ? 64 : 0)                \
    + (((x)& 0xF0000000LU) ? 128 : 0)

#define BIN8(d)                     ((uint8)__BIN8(__HEX(d)))
#define BIN16(dmsb, dlsb)           (((uint16)BIN8(dmsb) << 8) + BIN8(dlsb))
#define BIN32(dmsb, db2, db3, dlsb)                 \
    (((uint32)BIN8(dmsb) << 24)                     \
    + ((uint32)BIN8(db2) << 16)                     \
    + ((uint32)BIN8(db3) << 8)                      \
    + BIN8(dlsb))

#define FOREVER                         while(TRUE)

#define NOT_ADDRESSABLE                 register

#define WAIT_FOR(cond)                              \
while (!(cond))                                     \
    _BEGIN_BLOCK                                    \
    _END_BLOCK

/* todo: 'Assert.h', 'ASSERT_DBG','ASSERT_RT', Assertion-Handler!!! */                    
#if !defined(NDEBUG)
#define ASSERT(cond)                                \
    _BEGIN_BLOCK                                    \
        if (!(cond)) {                              \
            CPU_BREAKPOINT();                       \
        }                                           \
    _END_BLOCK

#else
#define ASSERT(cond)
#endif  /* NDEBUG */


/* Static  (compile time) Assertion. */
#if defined(_C1x_COMPILER)
#define STATIC_ASSERT(cond, msg) _Static_assert((cond), (msg))
#else
#define STATIC_ASSERT(cond, msg)                    \
struct  GLUE2(__NEVER_USED_BY_ISO_C_, __LINE__) {   \
    uint8 x[(cond) ? 1 : -1];                       \
}
#endif

#define RETURN_VALUE_IF_FALSE(expr, value)          \
    _BEGIN_BLOCK                                    \
        if (!(expr)) {                              \
            return (value);                         \
        }                                           \
    _END_BLOCK


#define _BEGIN_BLOCK    do {
#define _END_BLOCK      } while (0)

typedef void(*VoidFunctionType)(void);

#define TO_STRING_2(s)          # s
#define TO_STRING(s)            TO_STRING_2(s)

#define GLUE2_2(a, b)           a ## b
#define GLUE2(a, b)             GLUE2_2(a, b)

#define GLUE3_2(a, b, c)        a ## b ## c
#define GLUE3(a, b, c)          GLUE3_2(a, b, c)

#define BREF(b, o)              (*(((uint8 *)(b) + (o))))
#define BPTR(b, o)              ((((uint8 *)(b) + (o))))

#define WREF(w, o)              (*((uint16 *)((uint8 *)(w) + (o))))
#define WPTR(w, o)              (((uint16 *)((uint8 *)(w) + (o))))

#define LREF(l, o)              (*((uint32 *)((uint8 *)(l) + (o))))
#define LPTR(l, o)              (((uint32 *)((uint8 *)(l) + (o))))

#define FREF(f, o)              (*((float64 *)((uint8 *)(f) + (o))))
#define FPTR(f, o)              (((float64 *)((uint8 *)(f) + (o))))

#define BYTE_REG(base, offs)    *(volatile uint8 *)BPTR((base), (offs))
#define WORD_REG(base, offs)    *(volatile uint16 *)WPTR((base), (offs))

#define BIT(n, type)            ((type)(1 << (n)))

#define BIT0    ((uint16)0x01)
#define BIT1    ((uint16)0x02)
#define BIT2    ((uint16)0x04)
#define BIT3    ((uint16)0x08)
#define BIT4    ((uint16)0x10)
#define BIT5    ((uint16)0x20)
#define BIT6    ((uint16)0x40)
#define BIT7    ((uint16)0x80)
#define BIT8    ((uint16)0x0100)
#define BIT9    ((uint16)0x0200)
#define BIT10   ((uint16)0x0400)
#define BIT11   ((uint16)0x0800)
#define BIT12   ((uint16)0x1000)
#define BIT13   ((uint16)0x2000)
#define BIT14   ((uint16)0x4000)
#define BIT15   ((uint16)0x8000)

#define TENARY_COMPARE(id1, id2, mask)  (~((id1) ^ (id2)) | (~(mask)))
/*
**
**  Tenary comparision.
**  -------------------
**
**  Params:
**      id1
**      id2     IDs to compare.
**      mask    Compare mask, bit values: 0 ==> don't care; 1 ==> compare.
**
**  Descr.:     XNor (Equivalence) IDs and Impl-B (Implication/Subjuction)
**              with Mask.
**
**  Result:     0xff ==> Match, otherwise no match.
**
**  Use Case:   CAN-Style Soft-Message-Filtering.
**
*/

#define OFFSET_OF(structure, member)    ((SizeType) & (((structure) *) 0)->(member))
#define SIZE_OF(s, m)                   ((SizeType)sizeof(((s *)0)->m))


/*
**  Some specific macros.
*/

#define KNX_DEV_ERROR_DETECT(module) GLUE2(module, _DEV_ERROR_DETECT)

#define KNX_RAISE_DEV_ERROR(module, api, error) \
    Det_ReportError(module ## _MODULE_ID, module ## _INSTANCE_ID, KNX_SERVICE_ ## module ## _ ## api, error)

#define KNX_IMPLEMENT_MODULE_STATE_VKNX(module) \
    static BSW_State module ## _State = BSW_UNINIT   /* todo: 'P2VKNX' !!!    */

#define KNX_GET_MODULE_STATE_VKNX(module) \
    GLUE2(module, _State)

#define KNX_MODULE_INITIALIZE(module) \
    KNX_GET_MODULE_STATE_VKNX(module) = BSW_READY

#define KNX_MODULE_UNINITIALIZE(module) \
    KNX_GET_MODULE_STATE_VKNX(module) = BSW_UNINIT

#define KNX_MODULE_IS_INITIALIZED(module) \
    ((KNX_GET_MODULE_STATE_VKNX(module) == BSW_READY) ? TRUE : FALSE)

#define KNX_ASSERT_MODULE_IS_INITIALIZED(ml, mu, fkt)               \
    _BEGIN_BLOCK                                                    \
    if (!KNX_MODULE_IS_INITIALIZED(ml)) {                           \
    KNX_RAISE_DEV_ERROR(mu, fkt, mu ## _E_UNINIT);                  \
    return;                                                         \
    }                                                               \
    _END_BLOCK

#define KNX_ASSERT_MODULE_IS_INITIALIZED_RETURN(ml, mu, fkt, value) \
    _BEGIN_BLOCK                                                    \
    if (!KNX_MODULE_IS_INITIALIZED(ml)) {                           \
        KNX_RAISE_DEV_ERROR(mu, fkt, mu ## _E_UNINIT);              \
        return value;                                               \
    }                                                               \
    _END_BLOCK

#define KKNX_DEFINE_LOCAL_CONFIG_VKNX(u, l)   P2CONST(l ## _ConfigType, STATIC, u ## _VKNX)  l ## _Config

#define KNX_SAVE_CONFIG_PTR(module)             module ## _Config = ConfigPtr
#define KNX_GET_CONFIG_PTR(module)              module ## _Config

#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif  /* __KNX_ET_H */

