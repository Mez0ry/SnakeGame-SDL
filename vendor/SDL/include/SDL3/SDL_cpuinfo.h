/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  \file SDL_cpuinfo.h
 *
 *  CPU feature detection for SDL.
 */

#ifndef SDL_cpuinfo_h_
#define SDL_cpuinfo_h_

#include <SDL3/SDL_stdinc.h>

#include <SDL3/begin_code.h>
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* This is a guess for the cacheline size used for padding.
 * Most x86 processors have a 64 byte cache line.
 * The 64-bit PowerPC processors have a 128 byte cache line.
 * We'll use the larger value to be generally safe.
 */
#define SDL_CACHELINE_SIZE  128

/**
 * Get the number of CPU cores available.
 *
 * \returns the total number of logical CPU cores. On CPUs that include
 *          technologies such as hyperthreading, the number of logical cores
 *          may be more than the number of physical cores.
 *
 * \since This function is available since SDL 3.0.0.
 */
extern DECLSPEC int SDLCALL SDL_GetCPUCount(void);

/**
 * Determine the L1 cache line size of the CPU.
 *
 * This is useful for determining multi-threaded structure padding or SIMD
 * prefetch sizes.
 *
 * \returns the L1 cache line size of the CPU, in bytes.
 *
 * \since This function is available since SDL 3.0.0.
 */
extern DECLSPEC int SDLCALL SDL_GetCPUCacheLineSize(void);

/**
 * Determine whether the CPU has the RDTSC instruction.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has the RDTSC instruction or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasRDTSC(void);

/**
 * Determine whether the CPU has AltiVec features.
 *
 * This always returns false on CPUs that aren't using PowerPC instruction
 * sets.
 *
 * \returns SDL_TRUE if the CPU has AltiVec features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasAltiVec(void);

/**
 * Determine whether the CPU has MMX features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has MMX features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasMMX(void);

/**
 * Determine whether the CPU has 3DNow! features.
 *
 * This always returns false on CPUs that aren't using AMD instruction sets.
 *
 * \returns SDL_TRUE if the CPU has 3DNow! features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_Has3DNow(void);

/**
 * Determine whether the CPU has SSE features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has SSE features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE(void);

/**
 * Determine whether the CPU has SSE2 features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has SSE2 features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE2(void);

/**
 * Determine whether the CPU has SSE3 features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has SSE3 features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE3(void);

/**
 * Determine whether the CPU has SSE4.1 features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has SSE4.1 features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE41(void);

/**
 * Determine whether the CPU has SSE4.2 features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has SSE4.2 features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasSSE42(void);

/**
 * Determine whether the CPU has AVX features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has AVX features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX2
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasAVX(void);

/**
 * Determine whether the CPU has AVX2 features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has AVX2 features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Has3DNow
 * \sa SDL_HasAltiVec
 * \sa SDL_HasAVX
 * \sa SDL_HasMMX
 * \sa SDL_HasRDTSC
 * \sa SDL_HasSSE
 * \sa SDL_HasSSE2
 * \sa SDL_HasSSE3
 * \sa SDL_HasSSE41
 * \sa SDL_HasSSE42
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasAVX2(void);

/**
 * Determine whether the CPU has AVX-512F (foundation) features.
 *
 * This always returns false on CPUs that aren't using Intel instruction sets.
 *
 * \returns SDL_TRUE if the CPU has AVX-512F features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_HasAVX
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasAVX512F(void);

/**
 * Determine whether the CPU has ARM SIMD (ARMv6) features.
 *
 * This is different from ARM NEON, which is a different instruction set.
 *
 * This always returns false on CPUs that aren't using ARM instruction sets.
 *
 * \returns SDL_TRUE if the CPU has ARM SIMD features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_HasNEON
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasARMSIMD(void);

/**
 * Determine whether the CPU has NEON (ARM SIMD) features.
 *
 * This always returns false on CPUs that aren't using ARM instruction sets.
 *
 * \returns SDL_TRUE if the CPU has ARM NEON features or SDL_FALSE if not.
 *
 * \since This function is available since SDL 3.0.0.
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasNEON(void);

/**
 * Determine whether the CPU has LSX (LOONGARCH SIMD) features.
 *
 * This always returns false on CPUs that aren't using LOONGARCH instruction
 * sets.
 *
 * \returns SDL_TRUE if the CPU has LOONGARCH LSX features or SDL_FALSE if
 *          not.
 *
 * \since This function is available since SDL 3.0.0.
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasLSX(void);

/**
 * Determine whether the CPU has LASX (LOONGARCH SIMD) features.
 *
 * This always returns false on CPUs that aren't using LOONGARCH instruction
 * sets.
 *
 * \returns SDL_TRUE if the CPU has LOONGARCH LASX features or SDL_FALSE if
 *          not.
 *
 * \since This function is available since SDL 3.0.0.
 */
extern DECLSPEC SDL_bool SDLCALL SDL_HasLASX(void);

/**
 * Get the amount of RAM configured in the system.
 *
 * \returns the amount of RAM configured in the system in MiB.
 *
 * \since This function is available since SDL 3.0.0.
 */
extern DECLSPEC int SDLCALL SDL_GetSystemRAM(void);

/**
 * Report the alignment this system needs for SIMD allocations.
 *
 * This will return the minimum number of bytes to which a pointer must be
 * aligned to be compatible with SIMD instructions on the current machine. For
 * example, if the machine supports SSE only, it will return 16, but if it
 * supports AVX-512F, it'll return 64 (etc). This only reports values for
 * instruction sets SDL knows about, so if your SDL build doesn't have
 * SDL_HasAVX512F(), then it might return 16 for the SSE support it sees and
 * not 64 for the AVX-512 instructions that exist but SDL doesn't know about.
 * Plan accordingly.
 *
 * \returns the alignment in bytes needed for available, known SIMD
 *          instructions.
 *
 * \since This function is available since SDL 3.0.0.
 */
extern DECLSPEC size_t SDLCALL SDL_SIMDGetAlignment(void);

/**
 * Allocate memory in a SIMD-friendly way.
 *
 * This will allocate a block of memory that is suitable for use with SIMD
 * instructions. Specifically, it will be properly aligned and padded for the
 * system's supported vector instructions.
 *
 * The memory returned will be padded such that it is safe to read or write an
 * incomplete vector at the end of the memory block. This can be useful so you
 * don't have to drop back to a scalar fallback at the end of your SIMD
 * processing loop to deal with the final elements without overflowing the
 * allocated buffer.
 *
 * You must free this memory with SDL_FreeSIMD(), not free() or SDL_free() or
 * delete[], etc.
 *
 * Note that SDL will only deal with SIMD instruction sets it is aware of; for
 * example, SDL 2.0.8 knows that SSE wants 16-byte vectors (SDL_HasSSE()), and
 * AVX2 wants 32 bytes (SDL_HasAVX2()), but doesn't know that AVX-512 wants
 * 64. To be clear: if you can't decide to use an instruction set with an
 * SDL_Has*() function, don't use that instruction set with memory allocated
 * through here.
 *
 * SDL_AllocSIMD(0) will return a non-NULL pointer, assuming the system isn't
 * out of memory, but you are not allowed to dereference it (because you only
 * own zero bytes of that buffer).
 *
 * \param len The length, in bytes, of the block to allocate. The actual
 *            allocated block might be larger due to padding, etc.
 * \returns a pointer to the newly-allocated block, NULL if out of memory.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_SIMDGetAlignment
 * \sa SDL_SIMDRealloc
 * \sa SDL_SIMDFree
 */
extern DECLSPEC void * SDLCALL SDL_SIMDAlloc(const size_t len);

/**
 * Reallocate memory obtained from SDL_SIMDAlloc
 *
 * It is not valid to use this function on a pointer from anything but
 * SDL_SIMDAlloc(). It can't be used on pointers from malloc, realloc,
 * SDL_malloc, memalign, new[], etc.
 *
 * \param mem The pointer obtained from SDL_SIMDAlloc. This function also
 *            accepts NULL, at which point this function is the same as
 *            calling SDL_SIMDAlloc with a NULL pointer.
 * \param len The length, in bytes, of the block to allocated. The actual
 *            allocated block might be larger due to padding, etc. Passing 0
 *            will return a non-NULL pointer, assuming the system isn't out of
 *            memory.
 * \returns a pointer to the newly-reallocated block, NULL if out of memory.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_SIMDGetAlignment
 * \sa SDL_SIMDAlloc
 * \sa SDL_SIMDFree
 */
extern DECLSPEC void * SDLCALL SDL_SIMDRealloc(void *mem, const size_t len);

/**
 * Deallocate memory obtained from SDL_SIMDAlloc
 *
 * It is not valid to use this function on a pointer from anything but
 * SDL_SIMDAlloc() or SDL_SIMDRealloc(). It can't be used on pointers from
 * malloc, realloc, SDL_malloc, memalign, new[], etc.
 *
 * However, SDL_SIMDFree(NULL) is a legal no-op.
 *
 * The memory pointed to by `ptr` is no longer valid for access upon return,
 * and may be returned to the system or reused by a future allocation. The
 * pointer passed to this function is no longer safe to dereference once this
 * function returns, and should be discarded.
 *
 * \param ptr The pointer, returned from SDL_SIMDAlloc or SDL_SIMDRealloc, to
 *            deallocate. NULL is a legal no-op.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_SIMDAlloc
 * \sa SDL_SIMDRealloc
 */
extern DECLSPEC void SDLCALL SDL_SIMDFree(void *ptr);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#include <SDL3/close_code.h>

#endif /* SDL_cpuinfo_h_ */

/* vi: set ts=4 sw=4 expandtab: */
