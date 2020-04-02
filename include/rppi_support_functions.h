#ifndef RPPI_SUPPORT_FUNCTIONS
#define RPPI_SUPPORT_FUNCTIONS

#include "rpp.h"

#ifdef __cplusplus
extern "C" {
#endif


RppStatus warp_affine_output_size(RppiSize srcSize, RppiSize *dstSizePtr,
                                       float* affine);

RppStatus warp_affine_output_offset(RppiSize srcSize, RppiPoint *offset,
                                       float* affine);

RppStatus rotate_output_size(RppiSize srcSize, RppiSize *dstSizePtr,
                                  Rpp32f angleDeg);

RppStatus rotate_output_offset(RppiSize srcSize, RppiPoint *offset,
                                  Rpp32f angleDeg);

#ifdef __cplusplus
}
#endif

#endif /* RPPI_SUPPORT_FUNCTIONS_H */
