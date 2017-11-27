#include <src/include/chains.h>
#include <src/include/chains_common.h>

/* Define the type of sensor to be initialized as part of App_init */
#define EARLY_SRV_SENSOR_TYPE_OV10635


/*Function prototype for list of sensors*/
#ifdef EARLY_SRV_SENSOR_TYPE_OV10635
Void ChainsCommon_EarlyBoot_StartCaptureOV10635(void);
#endif


/*Function definitions for above defined prototypes*/
#ifdef EARLY_SRV_SENSOR_TYPE_OV10635
/*Start OV10635 camera capture. There are a maximum of 6 channels, however for
 TDA2x we use only upto 5 and for TDA2ex we use only 4*/
Void ChainsCommon_EarlyBoot_StartCaptureOV10635(void)
{
  UInt32 portId[6];
  UInt32 noChannel=5;
#ifdef TDA2EX_BUILD
  noChannel=4;
#endif
  ChainsCommon_MultiCam_StartCaptureDevice(CHAINS_CAPTURE_SRC_OV10635,
          portId,
          noChannel);
}
#endif


#ifdef EARLY_SRV_ENABLE
Void ChainsCommon_EarlyBoot_StartCaptureDevice(void)
{
  #ifdef EARLY_SRV_SENSOR_TYPE_OV10635
    ChainsCommon_EarlyBoot_StartCaptureOV10635();
  #endif
}
#endif

