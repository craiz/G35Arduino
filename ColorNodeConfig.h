#ifndef _COLOR_NODE_CONFIG_H_
#define _COLOR_NODE_CONFIG_H_

#include <G35.h>

void ShowNodeConfiguration(byte nodeType, byte rfNodeId, byte rfGroupId, byte rfControllerId, byte frequency);

void ShowStringConfiguration(byte stringId, byte* pStringGroups, byte stringType, byte physicalLightCount, byte logicalLightCount, byte enumerationDirection, uint16_t enumerationDelay);


#endif //_COLOR_NODE_CONFIG_H_

