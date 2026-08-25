#include_next <drm/drm_exec.h>
#ifndef __BACKPORT_DRM_EXEC_H__
#define __BACKPORT_DRM_EXEC_H__

#if LINUX_VERSION_CODE >= KERNEL_VERSION(7, 2, 0)
/*
 * Linux 7.2: drm_exec_for_each_locked_object() dropped its explicit index
 * parameter and now declares an internal __UNIQUE_ID() counter instead. The
 * vendored xe tree still uses the 7.0 three-argument form and declares the
 * index itself. Rebuilt here on top of drm_exec_obj(), which is unchanged --
 * that keeps the caller's variable live (no shadowing, no unused-variable
 * warning) and reproduces the old iteration order exactly.
 */
#undef drm_exec_for_each_locked_object
#define drm_exec_for_each_locked_object(exec, index, obj)		\
	for ((index) = 0; ((obj) = drm_exec_obj((exec), (index))); ++(index))

/*
 * Linux 7.2: drm_exec_until_all_locked() replaced the computed-goto pointer
 * __drm_exec_retry_ptr with a plain label named drm_exec_retry. Map the old
 * name onto the address of that label so xe_validation.h's
 * "goto *__drm_exec_retry_ptr" keeps working unchanged -- the label is in
 * scope exactly where the macro is used. Bare drm_exec_retry is not expanded
 * by the like-named function-like macro (no following parenthesis).
 */
#define __drm_exec_retry_ptr (&&drm_exec_retry)
#endif

#endif /* __BACKPORT_DRM_EXEC_H__ */
