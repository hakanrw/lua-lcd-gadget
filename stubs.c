#include <reent.h>
#include <errno.h>

int _link_r(struct _reent *r, const char *oldpath, const char *newpath) {
    // This is a stub, so we just set errno to ENOSYS (Function not implemented)
    r->_errno = ENOSYS;
    return -1;
}

int _unlink_r(struct _reent *r, const char *pathname) {
    // This is a stub, so we just set errno to ENOSYS (Function not implemented)
    r->_errno = ENOSYS;
    return -1;
}
