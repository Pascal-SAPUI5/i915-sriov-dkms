#include_next <linux/dma-fence-array.h>
#ifndef __BACKPORT_DMA_FENCE_ARRAY_H__
#define __BACKPORT_DMA_FENCE_ARRAY_H__

/*
 * Linux 7.2: dma_fence_array_create() and dma_fence_array_init() lost their
 * trailing "bool signal_on_any" parameter; the array now always signals only
 * after all sub-fences have signalled, which is what signal_on_any == false
 * did before. All three call sites in the vendored tree
 * (i915_gem_execbuffer.c, xe_sync.c, xe_vm.c) pass false, so dropping the
 * argument is semantically identical here -- variadic-macro shim (same
 * technique as the drm_plane_colorop_*_init() shim) instead of touching the
 * vendored .c files.
 *
 * Lives in a header shim rather than the -include config on purpose: the
 * macro is function-like and would otherwise rewrite the prototypes in the
 * real <linux/dma-fence-array.h>. #include_next pulls those in first.
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(7, 2, 0)
#define dma_fence_array_create(num_fences, fences, context, seqno, ...) \
	dma_fence_array_create(num_fences, fences, context, seqno)
#define dma_fence_array_init(array, num_fences, fences, context, seqno, ...) \
	dma_fence_array_init(array, num_fences, fences, context, seqno)
#endif

#endif /* __BACKPORT_DMA_FENCE_ARRAY_H__ */
