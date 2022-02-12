
/* File generated by gen_cfile.py. Should not be modified. */

#include "TestMaster.h"

/**************************************************************************/
/* Declaration of mapped variables                                        */
/**************************************************************************/
UNS32 pdo_s2m_rx_data = 0x0;		/* Mapped at index 0x2000, subindex 0x00 */
UNS32 pdo_m2s_tx_data = 0x0;		/* Mapped at index 0x2001, subindex 0x00 */
UNS32 sdo_s2m_rx_array[] =		/* Mapped at index 0x2002, subindex 0x01 - 0x0A */
  {
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0	/* 0 */
  };
UNS32 sdo_m2s_tx_array[] =		/* Mapped at index 0x2003, subindex 0x01 - 0x0A */
  {
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0,	/* 0 */
    0x0	/* 0 */
  };

/**************************************************************************/
/* Declaration of value range types                                       */
/**************************************************************************/

#define valueRange_EMC 0x9F /* Type for index 0x1003 subindex 0x00 (only set of value 0 is possible) */
UNS32 TestMaster_valueRangeTest (UNS8 typeValue, void * value)
{
  switch (typeValue) {
    case valueRange_EMC:
      if (*(UNS8*)value != (UNS8)0) return OD_VALUE_RANGE_EXCEEDED;
      break;
  }
  return 0;
}

/**************************************************************************/
/* The node id                                                            */
/**************************************************************************/
/* node_id default value.*/
UNS8 TestMaster_bDeviceNodeId = 0x00;

/**************************************************************************/
/* Array of message processing information */

const UNS8 TestMaster_iam_a_slave = 0;

TIMER_HANDLE TestMaster_heartBeatTimers[1];

/*
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

                               OBJECT DICTIONARY

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
*/

/* index 0x1000 :   Device Type. */
                    UNS32 TestMaster_obj1000 = 0x0;	/* 0 */
                    subindex TestMaster_Index1000[] = 
                     {
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1000 }
                     };

/* index 0x1001 :   Error Register. */
                    UNS8 TestMaster_obj1001 = 0x0;	/* 0 */
                    subindex TestMaster_Index1001[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_obj1001 }
                     };

/* index 0x1003 :   Pre-defined Error Field */
                    UNS8 TestMaster_highestSubIndex_obj1003 = 0; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1003[] = 
                    {
                      0x0	/* 0 */
                    };
                    ODCallback_t TestMaster_Index1003_callbacks[] = 
                     {
                       NULL,
                       NULL,
                     };
                    subindex TestMaster_Index1003[] = 
                     {
                       { RW, valueRange_EMC, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1003 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1003[0] }
                     };

/* index 0x1005 :   SYNC COB ID */
                    UNS32 TestMaster_obj1005 = 0x0;   /* 0 */

/* index 0x1006 :   Communication / Cycle Period */
                    UNS32 TestMaster_obj1006 = 0x0;   /* 0 */

/* index 0x100C :   Guard Time */ 
                    UNS16 TestMaster_obj100C = 0x0;   /* 0 */

/* index 0x100D :   Life Time Factor */ 
                    UNS8 TestMaster_obj100D = 0x0;   /* 0 */

/* index 0x1014 :   Emergency COB ID */
                    UNS32 TestMaster_obj1014 = 0x80 + 0x00;   /* 128 + NodeID */

/* index 0x1016 :   Consumer Heartbeat Time */
                    UNS8 TestMaster_highestSubIndex_obj1016 = 0;
                    UNS32 TestMaster_obj1016[]={0};

/* index 0x1017 :   Producer Heartbeat Time. */
                    UNS16 TestMaster_obj1017 = 0x3E8;	/* 1000 */
                    ODCallback_t TestMaster_Index1017_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestMaster_Index1017[] = 
                     {
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1017 }
                     };

/* index 0x1018 :   Identity. */
                    UNS8 TestMaster_highestSubIndex_obj1018 = 4; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1018_Vendor_ID = 0x0;	/* 0 */
                    UNS32 TestMaster_obj1018_Product_Code = 0x0;	/* 0 */
                    UNS32 TestMaster_obj1018_Revision_Number = 0x0;	/* 0 */
                    UNS32 TestMaster_obj1018_Serial_Number = 0x0;	/* 0 */
                    subindex TestMaster_Index1018[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1018 },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1018_Vendor_ID },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1018_Product_Code },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1018_Revision_Number },
                       { RO, uint32, sizeof (UNS32), (void*)&TestMaster_obj1018_Serial_Number }
                     };

/* index 0x1280 :   Client SDO 1 Parameter. */
                    UNS8 TestMaster_highestSubIndex_obj1280 = 3; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1280_COB_ID_Client_to_Server_Transmit_SDO = 0x601;	/* 1537 */
                    UNS32 TestMaster_obj1280_COB_ID_Server_to_Client_Receive_SDO = 0x581;	/* 1409 */
                    UNS8 TestMaster_obj1280_Node_ID_of_the_SDO_Server = 0x1;	/* 1 */
                    subindex TestMaster_Index1280[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1280 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1280_COB_ID_Client_to_Server_Transmit_SDO },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1280_COB_ID_Server_to_Client_Receive_SDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1280_Node_ID_of_the_SDO_Server }
                     };

/* index 0x1400 :   Receive PDO 1 Parameter. */
                    UNS8 TestMaster_highestSubIndex_obj1400 = 6; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1400_COB_ID_used_by_PDO = 0x201;	/* 513 */
                    UNS8 TestMaster_obj1400_Transmission_Type = 0xFF;	/* 255 */
                    UNS16 TestMaster_obj1400_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 TestMaster_obj1400_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 TestMaster_obj1400_Event_Timer = 0x0;	/* 0 */
                    UNS8 TestMaster_obj1400_SYNC_start_value = 0x0;	/* 0 */
                    subindex TestMaster_Index1400[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1400 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1400_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1400_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1400_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1400_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1400_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1400_SYNC_start_value }
                     };

/* index 0x1600 :   Receive PDO 1 Mapping. */
                    UNS8 TestMaster_highestSubIndex_obj1600 = 1; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1600[] = 
                    {
                      0x20000020	/* 536870944 */
                    };
                    subindex TestMaster_Index1600[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1600 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1600[0] }
                     };

/* index 0x1800 :   Transmit PDO 1 Parameter. */
                    UNS8 TestMaster_highestSubIndex_obj1800 = 6; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1800_COB_ID_used_by_PDO = 0x181;	/* 385 */
                    UNS8 TestMaster_obj1800_Transmission_Type = 0xFF;	/* 255 */
                    UNS16 TestMaster_obj1800_Inhibit_Time = 0x0;	/* 0 */
                    UNS8 TestMaster_obj1800_Compatibility_Entry = 0x0;	/* 0 */
                    UNS16 TestMaster_obj1800_Event_Timer = 0x0;	/* 0 */
                    UNS8 TestMaster_obj1800_SYNC_start_value = 0x0;	/* 0 */
                    ODCallback_t TestMaster_Index1800_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestMaster_Index1800[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1800 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1800_COB_ID_used_by_PDO },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1800_Transmission_Type },
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1800_Inhibit_Time },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1800_Compatibility_Entry },
                       { RW, uint16, sizeof (UNS16), (void*)&TestMaster_obj1800_Event_Timer },
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_obj1800_SYNC_start_value }
                     };

/* index 0x1A00 :   Transmit PDO 1 Mapping. */
                    UNS8 TestMaster_highestSubIndex_obj1A00 = 1; /* number of subindex - 1*/
                    UNS32 TestMaster_obj1A00[] = 
                    {
                      0x20010020	/* 536936480 */
                    };
                    subindex TestMaster_Index1A00[] = 
                     {
                       { RW, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj1A00 },
                       { RW, uint32, sizeof (UNS32), (void*)&TestMaster_obj1A00[0] }
                     };

/* index 0x2000 :   Mapped variable pdo_s2m_rx_data */
                    ODCallback_t pdo_s2m_rx_data_callbacks[] = 
                     {
                       NULL,
                     };
                    subindex TestMaster_Index2000[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo_s2m_rx_data }
                     };

/* index 0x2001 :   Mapped variable pdo_m2s_tx_data */
                    subindex TestMaster_Index2001[] = 
                     {
                       { RW, uint32, sizeof (UNS32), (void*)&pdo_m2s_tx_data }
                     };

/* index 0x2002 :   Mapped variable sdo_s2m_rx_array */
                    UNS8 TestMaster_highestSubIndex_obj2002 = 10; /* number of subindex - 1*/
                    ODCallback_t sdo_s2m_rx_array_callbacks[] = 
                     {
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                       NULL,
                     };
                    subindex TestMaster_Index2002[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj2002 },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[7] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[8] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_s2m_rx_array[9] }
                     };

/* index 0x2003 :   Mapped variable sdo_m2s_tx_array */
                    UNS8 TestMaster_highestSubIndex_obj2003 = 10; /* number of subindex - 1*/
                    subindex TestMaster_Index2003[] = 
                     {
                       { RO, uint8, sizeof (UNS8), (void*)&TestMaster_highestSubIndex_obj2003 },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[0] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[1] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[2] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[3] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[4] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[5] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[6] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[7] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[8] },
                       { RW, uint32, sizeof (UNS32), (void*)&sdo_m2s_tx_array[9] }
                     };

/**************************************************************************/
/* Declaration of pointed variables                                       */
/**************************************************************************/

const indextable TestMaster_objdict[] = 
{
  { (subindex*)TestMaster_Index1000,sizeof(TestMaster_Index1000)/sizeof(TestMaster_Index1000[0]), 0x1000},
  { (subindex*)TestMaster_Index1001,sizeof(TestMaster_Index1001)/sizeof(TestMaster_Index1001[0]), 0x1001},
  { (subindex*)TestMaster_Index1017,sizeof(TestMaster_Index1017)/sizeof(TestMaster_Index1017[0]), 0x1017},
  { (subindex*)TestMaster_Index1018,sizeof(TestMaster_Index1018)/sizeof(TestMaster_Index1018[0]), 0x1018},
  { (subindex*)TestMaster_Index1280,sizeof(TestMaster_Index1280)/sizeof(TestMaster_Index1280[0]), 0x1280},
  { (subindex*)TestMaster_Index1400,sizeof(TestMaster_Index1400)/sizeof(TestMaster_Index1400[0]), 0x1400},
  { (subindex*)TestMaster_Index1600,sizeof(TestMaster_Index1600)/sizeof(TestMaster_Index1600[0]), 0x1600},
  { (subindex*)TestMaster_Index1800,sizeof(TestMaster_Index1800)/sizeof(TestMaster_Index1800[0]), 0x1800},
  { (subindex*)TestMaster_Index1A00,sizeof(TestMaster_Index1A00)/sizeof(TestMaster_Index1A00[0]), 0x1A00},
  { (subindex*)TestMaster_Index2000,sizeof(TestMaster_Index2000)/sizeof(TestMaster_Index2000[0]), 0x2000},
  { (subindex*)TestMaster_Index2001,sizeof(TestMaster_Index2001)/sizeof(TestMaster_Index2001[0]), 0x2001},
  { (subindex*)TestMaster_Index2002,sizeof(TestMaster_Index2002)/sizeof(TestMaster_Index2002[0]), 0x2002},
  { (subindex*)TestMaster_Index2003,sizeof(TestMaster_Index2003)/sizeof(TestMaster_Index2003[0]), 0x2003},
};

const indextable * TestMaster_scanIndexOD (UNS16 wIndex, UNS32 * errorCode, ODCallback_t **callbacks)
{
	int i;
	*callbacks = NULL;
	switch(wIndex){
		case 0x1000: i = 0;break;
		case 0x1001: i = 1;break;
		case 0x1017: i = 2;*callbacks = TestMaster_Index1017_callbacks; break;
		case 0x1018: i = 3;break;
		case 0x1280: i = 4;break;
		case 0x1400: i = 5;break;
		case 0x1600: i = 6;break;
		case 0x1800: i = 7;*callbacks = TestMaster_Index1800_callbacks; break;
		case 0x1A00: i = 8;break;
		case 0x2000: i = 9;*callbacks = pdo_s2m_rx_data_callbacks; break;
		case 0x2001: i = 10;break;
		case 0x2002: i = 11;*callbacks = sdo_s2m_rx_array_callbacks; break;
		case 0x2003: i = 12;break;
		default:
			*errorCode = OD_NO_SUCH_OBJECT;
			return NULL;
	}
	*errorCode = OD_SUCCESSFUL;
	return &TestMaster_objdict[i];
}

/* 
 * To count at which received SYNC a PDO must be sent.
 * Even if no pdoTransmit are defined, at least one entry is computed
 * for compilations issues.
 */
s_PDO_status TestMaster_PDO_status[1] = {s_PDO_status_Initializer};

const quick_index TestMaster_firstIndex = {
  0, /* SDO_SVR */
  4, /* SDO_CLT */
  5, /* PDO_RCV */
  6, /* PDO_RCV_MAP */
  7, /* PDO_TRS */
  8 /* PDO_TRS_MAP */
};

const quick_index TestMaster_lastIndex = {
  0, /* SDO_SVR */
  4, /* SDO_CLT */
  5, /* PDO_RCV */
  6, /* PDO_RCV_MAP */
  7, /* PDO_TRS */
  8 /* PDO_TRS_MAP */
};

const UNS16 TestMaster_ObjdictSize = sizeof(TestMaster_objdict)/sizeof(TestMaster_objdict[0]); 

CO_Data TestMaster_Data = CANOPEN_NODE_DATA_INITIALIZER(TestMaster);
