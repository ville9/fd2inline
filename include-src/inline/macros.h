#ifndef __INLINE_MACROS_H
#define __INLINE_MACROS_H

/*
   General macros for Amiga function calls. Not all the possibilities have
   been created - only the ones which exist in OS 3.2. Third party libraries
   and future versions of AmigaOS will maybe need some new ones...

   LPX - functions that take X arguments.

   Modifiers (variations are possible):
   NR - no return (void),
   A4, A5 - "a4" or "a5" is used as one of the arguments,
   UB - base will be given explicitly by user (see cia.resource).
   FP - one of the parameters has type "pointer to function".

   "bt" arguments are not used - they are provided for backward compatibility
   only.
*/

#ifndef __INLINE_STUB_H
#include <inline/stubs.h>
#endif /* !__INLINE_STUB_H */

#ifndef __PPC__

/* provide a syscall macro */
#ifndef __AMIGAOS_SYSCALL
#define __AMIGAOS_SYSCALL(FUNC) "jsr %/a6@(-"#FUNC":w)"
#endif /* !__AMIGAOS_SYSCALL */

#define LP0(offs, rt, name, bt, bn)				\
({								\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn)					\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP0NR(offs, name, bt, bn)				\
({								\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn)					\
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

#define LP1(offs, rt, name, t1, v1, r1, bt, bn)			\
({								\
   t1 _##name##_v1 = (v1);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1)				\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP1NR(offs, name, t1, v1, r1, bt, bn)			\
({								\
   t1 _##name##_v1 = (v1);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1)				\
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only hdwrench.library/LowlevelFormat() and hdwrench.library/VerifyDrive() */
#define LP1FP(offs, rt, name, t1, v1, r1, bt, bn, fpt)		\
({								\
   typedef fpt;							\
   t1 _##name##_v1 = (v1);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1)				\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* Only graphics.library/AttemptLockLayerRom() */
#define LP1A5(offs, rt, name, t1, v1, r1, bt, bn)		\
({								\
   t1 _##name##_v1 = (v1);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      __asm volatile ("exg %/d7,%/a5\n\t" __AMIGAOS_SYSCALL(offs) "\n\texg %/d7,%/a5" \
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1)				\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* Only graphics.library/LockLayerRom() and graphics.library/UnlockLayerRom() */
#define LP1NRA5(offs, name, t1, v1, r1, bt, bn)			\
({								\
   t1 _##name##_v1 = (v1);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      __asm volatile ("exg %/d7,%/a5\n\t" __AMIGAOS_SYSCALL(offs) "\n\texg %/d7,%/a5" \
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1)				\
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only exec.library/Supervisor() */
#define LP1A5FP(offs, rt, name, t1, v1, r1, bt, bn, fpt)	\
({								\
   typedef fpt;							\
   t1 _##name##_v1 = (v1);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      __asm volatile ("exg %/d7,%/a5\n\t" __AMIGAOS_SYSCALL(offs) "\n\texg %/d7,%/a5" \
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1)				\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP2(offs, rt, name, t1, v1, r1, t2, v2, r2, bt, bn)	\
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2)		\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP2NR(offs, name, t1, v1, r1, t2, v2, r2, bt, bn)	\
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2)		\
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only cia.resource/AbleICR() and cia.resource/SetICR() */
#define LP2UB(offs, rt, name, t1, v1, r1, t2, v2, r2)		\
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r"(_n1), "rf"(_n2)					\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* Only dos.library/InternalUnLoadSeg() */
#define LP2FP(offs, rt, name, t1, v1, r1, t2, v2, r2, bt, bn, fpt) \
({								\
   typedef fpt;							\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2)		\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP2A5(offs, rt, name, t1, v1, r1, t2, v2, r2, bt, bn)	\
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      __asm volatile ("exg %/d7,%/a5\n\t" __AMIGAOS_SYSCALL(offs) "\n\texg %/d7,%/a5" \
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2)		\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP3(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3)	\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP3NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3)	\
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only cia.resource/AddICRVector() */
#define LP3UB(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r"(_n1), "rf"(_n2), "rf"(_n3)				\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* Only cia.resource/RemICRVector() */
#define LP3NRUB(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3)	\
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r"(_n1), "rf"(_n2), "rf"(_n3)				\
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only exec.library/SetFunction() */
#define LP3FP(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn, fpt) \
({								\
   typedef fpt;							\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3)	\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* Only graphics.library/SetCollision() */
#define LP3NRFP(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn, fpt) \
({								\
   typedef fpt;							\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3)	\
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

#define LP3A5(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      __asm volatile ("exg %/d7,%/a5\n\t" __AMIGAOS_SYSCALL(offs) "\n\texg %/d7,%/a5" \
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3)	\
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP4(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP4NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4) \
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only exec.library/RawDoFmt() */
#define LP4FP(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn, fpt) \
({								\
   typedef fpt;							\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP5(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP5NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5) \
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only exec.library/MakeLibrary() */
#define LP5FP(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn, fpt) \
({								\
   typedef fpt;							\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn);	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP6(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP6NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6) \
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only hdwrench.library/QueryFindValid() */
#define LP6NRFP(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn, fpt) \
({								\
   typedef fpt;							\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6) \
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only cgx3drave.library/QADrawContextNew() */
#define LP6A4(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      __asm volatile ("exg %/d7,%/a4\n\t" __AMIGAOS_SYSCALL(offs) "\n\texg %/d7,%/a4" \
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP7(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#define LP7NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7) \
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only workbench.library/AddAppIconA() */
#define LP7A4(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      __asm volatile ("exg %/d7,%/a4\n\t" __AMIGAOS_SYSCALL(offs) "\n\texg %/d7,%/a4" \
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* Would you believe that there really are beasts that need more than 7
   arguments? :-) */

/* For example intuition.library/AutoRequest() */
#define LP8(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   t8 _##name##_v8 = (v8);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      register t8 _n8 __asm(#r8) = _##name##_v8;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7), "rf"(_n8) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* For example intuition.library/ModifyProp() */
#define LP8NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   t8 _##name##_v8 = (v8);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      register t8 _n8 __asm(#r8) = _##name##_v8;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7), "rf"(_n8) \
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* For example layers.library/CreateUpfrontHookLayer() */
#define LP9(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   t8 _##name##_v8 = (v8);					\
   t9 _##name##_v9 = (v9);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      register t8 _n8 __asm(#r8) = _##name##_v8;		\
      register t9 _n9 __asm(#r9) = _##name##_v9;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7), "rf"(_n8), "rf"(_n9) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* For example intuition.library/NewModifyProp() */
#define LP9NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   t8 _##name##_v8 = (v8);					\
   t9 _##name##_v9 = (v9);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      register t8 _n8 __asm(#r8) = _##name##_v8;		\
      register t9 _n9 __asm(#r9) = _##name##_v9;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7), "rf"(_n8), "rf"(_n9) \
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Kriton Kyrimis <kyrimis@cti.gr> says CyberGraphics needs the following */
#define LP10(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   t8 _##name##_v8 = (v8);					\
   t9 _##name##_v9 = (v9);					\
   t10 _##name##_v10 = (v10);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      register t8 _n8 __asm(#r8) = _##name##_v8;		\
      register t9 _n9 __asm(#r9) = _##name##_v9;		\
      register t10 _n10 __asm(#r10) = _##name##_v10;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7), "rf"(_n8), "rf"(_n9), "rf"(_n10) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

/* Only graphics.library/BltMaskBitMapRastPort() */
#define LP10NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   t8 _##name##_v8 = (v8);					\
   t9 _##name##_v9 = (v9);					\
   t10 _##name##_v10 = (v10);					\
   {								\
      register int _d0 __asm("d0");				\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      register t8 _n8 __asm(#r8) = _##name##_v8;		\
      register t9 _n9 __asm(#r9) = _##name##_v9;		\
      register t10 _n10 __asm(#r10) = _##name##_v10;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_d0), "=r" (_d1), "=r" (_a0), "=r" (_a1)		\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7), "rf"(_n8), "rf"(_n9), "rf"(_n10) \
      : "fp0", "fp1", "cc", "memory");				\
   }								\
})

/* Only graphics.library/BltBitMap() */
#define LP11(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, t11, v11, r11, bt, bn) \
({								\
   t1 _##name##_v1 = (v1);					\
   t2 _##name##_v2 = (v2);					\
   t3 _##name##_v3 = (v3);					\
   t4 _##name##_v4 = (v4);					\
   t5 _##name##_v5 = (v5);					\
   t6 _##name##_v6 = (v6);					\
   t7 _##name##_v7 = (v7);					\
   t8 _##name##_v8 = (v8);					\
   t9 _##name##_v9 = (v9);					\
   t10 _##name##_v10 = (v10);					\
   t11 _##name##_v11 = (v11);					\
   ({								\
      register int _d1 __asm("d1");				\
      register int _a0 __asm("a0");				\
      register int _a1 __asm("a1");				\
      register rt _##name##_re __asm("d0");			\
      register void *const _##name##_bn __asm("a6") = (bn); 	\
      register t1 _n1 __asm(#r1) = _##name##_v1;		\
      register t2 _n2 __asm(#r2) = _##name##_v2;		\
      register t3 _n3 __asm(#r3) = _##name##_v3;		\
      register t4 _n4 __asm(#r4) = _##name##_v4;		\
      register t5 _n5 __asm(#r5) = _##name##_v5;		\
      register t6 _n6 __asm(#r6) = _##name##_v6;		\
      register t7 _n7 __asm(#r7) = _##name##_v7;		\
      register t8 _n8 __asm(#r8) = _##name##_v8;		\
      register t9 _n9 __asm(#r9) = _##name##_v9;		\
      register t10 _n10 __asm(#r10) = _##name##_v10;		\
      register t11 _n11 __asm(#r11) = _##name##_v11;		\
      __asm volatile (__AMIGAOS_SYSCALL(offs)			\
      : "=r" (_##name##_re), "=r" (_d1), "=r" (_a0), "=r" (_a1)	\
      : "r" (_##name##_bn), "rf"(_n1), "rf"(_n2), "rf"(_n3), "rf"(_n4), "rf"(_n5), "rf"(_n6), "rf"(_n7), "rf"(_n8), "rf"(_n9), "rf"(_n10), "rf"(_n11) \
      : "fp0", "fp1", "cc", "memory");				\
      _##name##_re;						\
   });								\
})

#else /* __PPC__ */

#if defined(WARPUP) || !defined(_CALL_SYSV)

#ifndef POWERPC_POWERPC_H
#include <powerpc/powerpc.h>
#endif /* !POWERPC_POWERPC_H */

#ifndef WARPUP_GCCLIB_PROTOS_H
#include <powerpc/powerpc_protos.h>
#endif /* !WARPUP_GCCLIB_PROTOS_H */

#define PPREG_d0 PPREG_D0
#define PPREG_d1 PPREG_D1
#define PPREG_d2 PPREG_D2
#define PPREG_d3 PPREG_D3
#define PPREG_d4 PPREG_D4
#define PPREG_d5 PPREG_D5
#define PPREG_d6 PPREG_D6
#define PPREG_d7 PPREG_D7

#define PPREG_a0 PPREG_A0
#define PPREG_a1 PPREG_A1
#define PPREG_a2 PPREG_A2
#define PPREG_a3 PPREG_A3
#define PPREG_a4 PPREG_A4
#define PPREG_a5 PPREG_A5
#define PPREG_a6 PPREG_A6

#define PPREG_EXG_d0(r) PPREG_D0
#define PPREG_EXG_d1(r) PPREG_D1
#define PPREG_EXG_d2(r) PPREG_D2
#define PPREG_EXG_d3(r) PPREG_D3
#define PPREG_EXG_d4(r) PPREG_D4
#define PPREG_EXG_d5(r) PPREG_D5
#define PPREG_EXG_d6(r) PPREG_D6
#define PPREG_EXG_d7(r) PPREG_##r

#define PPREG_EXG_a0(r) PPREG_A0
#define PPREG_EXG_a1(r) PPREG_A1
#define PPREG_EXG_a2(r) PPREG_A2
#define PPREG_EXG_a3(r) PPREG_A3

#define LP0(offs, rt, name, bt, bn)				\
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

#define LP1(offs, rt, name, t1, v1, r1, bt, bn)			\
({                             					\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

#define LP2(offs, rt, name, t1, v1, r1, t2, v2, r2, bt, bn)	\
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

/* Only cia.resource/AbleICR() and cia.resource/SetICR() */
#define LP2UB(offs, rt, name, t1, v1, r1, t2, v2, r2)		\
({								\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

#define LP3(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn) \
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

/* Only cia.resource/AddICRVector() */
#define LP3UB(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3) \
({								\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

#define LP4(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn) \
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_##r4] = (ULONG)(v4);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

#define LP5(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn) \
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_##r4] = (ULONG)(v4);		\
   _##name##_st.PP_Regs[PPREG_##r5] = (ULONG)(v5);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

#define LP6(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn) \
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_##r4] = (ULONG)(v4);		\
   _##name##_st.PP_Regs[PPREG_##r5] = (ULONG)(v5);		\
   _##name##_st.PP_Regs[PPREG_##r6] = (ULONG)(v6);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

#define LP7(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, bt, bn) \
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_##r4] = (ULONG)(v4);		\
   _##name##_st.PP_Regs[PPREG_##r5] = (ULONG)(v5);		\
   _##name##_st.PP_Regs[PPREG_##r6] = (ULONG)(v6);		\
   _##name##_st.PP_Regs[PPREG_##r7] = (ULONG)(v7);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

/* Would you believe that there really are beasts that need more than 7
   arguments? :-) */

/* For example intuition.library/AutoRequest() */
#define LP8(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, bt, bn) \
({								\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_##r4] = (ULONG)(v4);		\
   _##name##_st.PP_Regs[PPREG_##r5] = (ULONG)(v5);		\
   _##name##_st.PP_Regs[PPREG_##r6] = (ULONG)(v6);		\
   _##name##_st.PP_Regs[PPREG_##r7] = (ULONG)(v7);		\
   _##name##_st.PP_Regs[PPREG_##r8] = (ULONG)(v8);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

/* For example layers.library/CreateUpfrontHookLayer() */
#define LP9(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, bt, bn) \
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_##r4] = (ULONG)(v4);		\
   _##name##_st.PP_Regs[PPREG_##r5] = (ULONG)(v5);		\
   _##name##_st.PP_Regs[PPREG_##r6] = (ULONG)(v6);		\
   _##name##_st.PP_Regs[PPREG_##r7] = (ULONG)(v7);		\
   _##name##_st.PP_Regs[PPREG_##r8] = (ULONG)(v8);		\
   _##name##_st.PP_Regs[PPREG_##r9] = (ULONG)(v9);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

/* Kriton Kyrimis <kyrimis@cti.gr> says CyberGraphics needs the following */
#define LP10(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, bt, bn) \
({                              				\
   struct PPCArgs _##name##_st;                 		\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_##r4] = (ULONG)(v4);		\
   _##name##_st.PP_Regs[PPREG_##r5] = (ULONG)(v5);		\
   _##name##_st.PP_Regs[PPREG_##r6] = (ULONG)(v6);		\
   _##name##_st.PP_Regs[PPREG_##r7] = (ULONG)(v7);		\
   _##name##_st.PP_Regs[PPREG_##r8] = (ULONG)(v8);		\
   _##name##_st.PP_Regs[PPREG_##r9] = (ULONG)(v9);		\
   _##name##_st.PP_Regs[PPREG_##r10] = (ULONG)(v10);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

/* Only graphics.library/BltBitMap() */
#define LP11(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, t11, v11, r11, bt, bn) \
({                              				\
   struct PPCArgs _##name##_st;					\
   _##name##_st.PP_Regs[PPREG_##r1] = (ULONG)(v1);		\
   _##name##_st.PP_Regs[PPREG_##r2] = (ULONG)(v2);		\
   _##name##_st.PP_Regs[PPREG_##r3] = (ULONG)(v3);		\
   _##name##_st.PP_Regs[PPREG_##r4] = (ULONG)(v4);		\
   _##name##_st.PP_Regs[PPREG_##r5] = (ULONG)(v5);		\
   _##name##_st.PP_Regs[PPREG_##r6] = (ULONG)(v6);		\
   _##name##_st.PP_Regs[PPREG_##r7] = (ULONG)(v7);		\
   _##name##_st.PP_Regs[PPREG_##r8] = (ULONG)(v8);		\
   _##name##_st.PP_Regs[PPREG_##r9] = (ULONG)(v9);		\
   _##name##_st.PP_Regs[PPREG_##r10] = (ULONG)(v10);		\
   _##name##_st.PP_Regs[PPREG_##r11] = (ULONG)(v11);		\
   _##name##_st.PP_Regs[PPREG_A6] = (ULONG)(bn);		\
   _##name##_st.PP_Code = (APTR)_##name##_st.PP_Regs[PPREG_A6];	\
   _##name##_st.PP_Offset = -(offs);				\
   _##name##_st.PP_Flags = 0;					\
   _##name##_st.PP_Stack = 0;					\
   _##name##_st.PP_StackSize = 0;				\
   Run68K(&_##name##_st);					\
   (rt)_##name##_st.PP_Regs[PPREG_D0];				\
})

#else /* !WARPUP && _CALL_SYSV */

#ifndef POWERUP_GCCLIB_PROTOS_H
#include <powerup/gcclib/powerup_protos.h>
#endif /* !POWERUP_GCCLIB_PROTOS_H */

#define EXG_d0(r) d0
#define EXG_d1(r) d1
#define EXG_d2(r) d2
#define EXG_d3(r) d3
#define EXG_d4(r) d4
#define EXG_d5(r) d5
#define EXG_d6(r) d6
#define EXG_d7(r) r

#define EXG_a0(r) a0
#define EXG_a1(r) a1
#define EXG_a2(r) a2
#define EXG_a3(r) a3

#define LP0(offs, rt, name, bt, bn)				\
({								\
   struct Caos _##name##_st;					\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

#define LP1(offs, rt, name, t1, v1, r1, bt, bn)			\
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

#define LP2(offs, rt, name, t1, v1, r1, t2, v2, r2, bt, bn)	\
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

/* Only cia.resource/AbleICR() and cia.resource/SetICR() */
#define LP2UB(offs, rt, name, t1, v1, r1, t2, v2, r2)		\
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

#define LP3(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn)	\
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

/* Only cia.resource/AddICRVector() */
#define LP3UB(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3) \
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

#define LP4(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn) \
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.r4 = (ULONG)(v4);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

#define LP5(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn)	\
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.r4 = (ULONG)(v4);				\
   _##name##_st.r5 = (ULONG)(v5);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

#define LP6(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn) \
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.r4 = (ULONG)(v4);				\
   _##name##_st.r5 = (ULONG)(v5);				\
   _##name##_st.r6 = (ULONG)(v6);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

#define LP7(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, bt, bn)	\
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.r4 = (ULONG)(v4);				\
   _##name##_st.r5 = (ULONG)(v5);				\
   _##name##_st.r6 = (ULONG)(v6);				\
   _##name##_st.r7 = (ULONG)(v7);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

/* Would you believe that there really are beasts that need more than 7
   arguments? :-) */

/* For example intuition.library/AutoRequest() */
#define LP8(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, bt, bn) \
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.r4 = (ULONG)(v4);				\
   _##name##_st.r5 = (ULONG)(v5);				\
   _##name##_st.r6 = (ULONG)(v6);				\
   _##name##_st.r7 = (ULONG)(v7);				\
   _##name##_st.r8 = (ULONG)(v8);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

/* For example layers.library/CreateUpfrontHookLayer() */
#define LP9(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, bt, bn) \
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.r4 = (ULONG)(v4);				\
   _##name##_st.r5 = (ULONG)(v5);				\
   _##name##_st.r6 = (ULONG)(v6);				\
   _##name##_st.r7 = (ULONG)(v7);				\
   _##name##_st.r8 = (ULONG)(v8);				\
   _##name##_st.r9 = (ULONG)(v9);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

/* Kriton Kyrimis <kyrimis@cti.gr> says CyberGraphics needs the following */
#define LP10(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, bt, bn)	 \
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.r4 = (ULONG)(v4);				\
   _##name##_st.r5 = (ULONG)(v5);				\
   _##name##_st.r6 = (ULONG)(v6);				\
   _##name##_st.r7 = (ULONG)(v7);				\
   _##name##_st.r8 = (ULONG)(v8);				\
   _##name##_st.r9 = (ULONG)(v9);				\
   _##name##_st.r10 = (ULONG)(v10);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

/* Only graphics.library/BltBitMap() */
#define LP11(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, t11, v11, r11, bt, bn) \
({								\
   struct Caos _##name##_st;					\
   _##name##_st.r1 = (ULONG)(v1);				\
   _##name##_st.r2 = (ULONG)(v2);				\
   _##name##_st.r3 = (ULONG)(v3);				\
   _##name##_st.r4 = (ULONG)(v4);				\
   _##name##_st.r5 = (ULONG)(v5);				\
   _##name##_st.r6 = (ULONG)(v6);				\
   _##name##_st.r7 = (ULONG)(v7);				\
   _##name##_st.r8 = (ULONG)(v8);				\
   _##name##_st.r9 = (ULONG)(v9);				\
   _##name##_st.r10 = (ULONG)(v10);				\
   _##name##_st.r11 = (ULONG)(v11);				\
   _##name##_st.a6 = (ULONG)(bn);				\
   _##name##_st.caos_Un.Offset = -(offs);			\
   _##name##_st.M68kCacheMode = IF_CACHEFLUSHALL;		\
   _##name##_st.PPCCacheMode = IF_CACHEFLUSHALL;		\
   (rt)PPCCallOS(&_##name##_st);				\
})

#endif /* !WARPUP && _CALL_SYSV */

#define LP0NR(offs, name, bt, bn)				\
   LP0(offs, VOID, name, bt, bn)

#define LP1NR(offs, name, t1, v1, r1, bt, bn)			\
   LP1(offs, VOID, name, t1, v1, r1, bt, bn)

/* Only hdwrench.library/LowlevelFormat() and hdwrench.library/VerifyDrive() */
#define LP1FP(offs, rt, name, t1, v1, r1, bt, bn, fpt)		\
   LP1(offs, rt, name, t1, v1, r1, bt, bn)

/* Only graphics.library/AttemptLockLayerRom() */
#define LP1A5(offs, rt, name, t1, v1, r1, bt, bn)		\
   LP1(offs, rt, name, t1, v1, EXG_##r1(a5), bt, bn)

/* Only graphics.library/LockLayerRom() and graphics.library/UnlockLayerRom() */
#define LP1NRA5(offs, name, t1, v1, r1, bt, bn)			\
   LP1(offs, VOID, name, t1, v1, EXG_##r1(a5), bt, bn)

/* Only exec.library/Supervisor() */
#define LP1A5FP(offs, rt, name, t1, v1, r1, bt, bn, fpt)	\
   LP1(offs, rt, name, t1, v1, EXG_##r1(a5), bt, bn)

#define LP2NR(offs, name, t1, v1, r1, t2, v2, r2, bt, bn)	\
   LP2(offs, VOID, name, t1, v1, r1, t2, v2, r2, bt, bn)

/* Only dos.library/InternalUnLoadSeg() */
#define LP2FP(offs, rt, name, t1, v1, r1, t2, v2, r2, bt, bn, fpt) \
   LP2(offs, rt, name, t1, v1, r1, t2, v2, r2, bt, bn)

#define LP2A5(offs, rt, name, t1, v1, r1, t2, v2, r2, bt, bn)	\
   LP2(offs, rt, name, t1, v1, EXG_##r1(a5), t2, v2, EXG_##r2(a5), bt, bn)

#define LP3NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn) \
   LP3(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn)

/* Only cia.resource/RemICRVector() */
#define LP3NRUB(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3)	\
   LP3UB(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3)

/* Only exec.library/SetFunction() */
#define LP3FP(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn, fpt) \
   LP3(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn)

/* Only graphics.library/SetCollision() */
#define LP3NRFP(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn, fpt) \
   LP3(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn)

#define LP3A5(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, bt, bn) \
   LP3(offs, rt, name, t1, v1, EXG_##r1(a5), t2, v2, EXG_##r2(a5), t3, v3, EXG_##r3(a5), bt, bn)

#define LP4NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn) \
   LP4(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn)

/* Only exec.library/RawDoFmt() */
#define LP4FP(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn, fpt) \
   LP4(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, bt, bn)

#define LP5NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn) \
   LP5(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn)

/* Only exec.library/MakeLibrary() */
#define LP5FP(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn, fpt) \
   LP5(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, bt, bn)

#define LP6NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn) \
   LP6(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn)

/* Only hdwrench.library/QueryFindValid() */
#define LP6NRFP(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn, fpt) \
   LP6(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn)

/* Only cgx3drave.library/QADrawContextNew() */
#define LP6A4(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, bt, bn) \
   LP6(offs, rt, name, t1, v1, EXG_##r1(a4), t2, v2, EXG_##r2(a4), t3, v3, EXG_##r3(a4), t4, v4, EXG_##r4(a4), t5, v5, EXG_##r5(a4), t6, v6, EXG_##r6(a4), bt, bn)

#define LP7NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, bt, bn) \
   LP7(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, bt, bn)

/* Only workbench.library/AddAppIconA() */
#define LP7A4(offs, rt, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, bt, bn) \
   LP7(offs, rt, name, t1, v1, EXG_##r1(a4), t2, v2, EXG_##r2(a4), t3, v3, EXG_##r3(a4), t4, v4, EXG_##r4(a4), t5, v5, EXG_##r5(a4), t6, v6, EXG_##r6(a4), t7, v7, EXG_##r7(a4), bt, bn)

/* For example intuition.library/ModifyProp() */
#define LP8NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, bt, bn) \
   LP8(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, bt, bn)

/* For example intuition.library/NewModifyProp() */
#define LP9NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, bt, bn) \
   LP9(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, bt, bn)

/* Only graphics.library/BltMaskBitMapRastPort() */
#define LP10NR(offs, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, bt, bn) \
   LP10(offs, VOID, name, t1, v1, r1, t2, v2, r2, t3, v3, r3, t4, v4, r4, t5, v5, r5, t6, v6, r6, t7, v7, r7, t8, v8, r8, t9, v9, r9, t10, v10, r10, bt, bn)

#endif /* __PPC__ */

#endif /* !__INLINE_MACROS_H */
