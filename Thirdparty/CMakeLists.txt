

IF(BUILD_NEWMAT)
    SUBDIRS(newmat)
ENDIF(BUILD_NEWMAT)

IF(BUILD_FLTKVW)
    SET(NEED_FLTK 1)
    SUBDIRS(FLTKVW)
ENDIF(BUILD_FLTKVW)

