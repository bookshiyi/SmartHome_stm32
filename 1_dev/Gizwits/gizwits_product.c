/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related       hardware initialization
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#include <stdio.h>
#include <string.h>
#include "hal_key.h"
#include "gizwits_product.h"
#include "common.h"
#include "hal_led.h" 
#include "OLED.h" 
#include "delay.h" 
#include "hal_buzz.h" 
#include "hal_relay.h" 
#include "hal_temp_hum.h" 
#include "hal_infrared.h" 

//模式状态标志位
bool Flag_mode_auto_manu;
bool Flag_mode_winter_summer;
bool Flag_mode_safe;
//数据存储
uint8_t temp_upper;
uint8_t temp_lower;


static uint32_t timerMsCount;
uint8_t aRxBuffer;

/** User area the current device state structure*/
dataPoint_t currentDataPoint;
extern keysTypedef_t keys;

extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
    uint8_t i = 0;
    dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
    moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
    protocolTime_t *ptime = (protocolTime_t *)gizdata;

#if MODULE_TYPE
    gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
    moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

    if((NULL == info) || (NULL == gizdata))
    {
        return -1;
    }

    for(i=0; i<info->num; i++)
    {
        switch(info->event[i])
        {
        case EVENT_relay_4:
            currentDataPoint.valuerelay_4 = dataPointPtr->valuerelay_4;
            GIZWITS_LOG("Evt: EVENT_relay_4 %d \n", currentDataPoint.valuerelay_4);
            if(0x01 == currentDataPoint.valuerelay_4)
            {
                RelayWrite(4,1);
                LedWrite(1,1);
                LedWrite(2,1);
                LedWrite(3,1);
            }
            else
            {
                RelayWrite(4,0);
                LedWrite(1,0);
                LedWrite(2,0);
                LedWrite(3,0);
            }
            break;
        case EVENT_relay_1:
            currentDataPoint.valuerelay_1 = dataPointPtr->valuerelay_1;
            GIZWITS_LOG("Evt: EVENT_relay_1 %d \n", currentDataPoint.valuerelay_1);
            if(0x01 == currentDataPoint.valuerelay_1)
            {
                RelayWrite(1,1);
            }
            else
            {
                RelayWrite(1,0);
            }
            break;
        case EVENT_relay_2:
            currentDataPoint.valuerelay_2 = dataPointPtr->valuerelay_2;
            GIZWITS_LOG("Evt: EVENT_relay_2 %d \n", currentDataPoint.valuerelay_2);
            if(0x01 == currentDataPoint.valuerelay_2)
            {
                RelayWrite(2,1);
            }
            else
            {
                RelayWrite(2,0);
            }
            break;
        case EVENT_buzz:
            currentDataPoint.valuebuzz = dataPointPtr->valuebuzz;
            GIZWITS_LOG("Evt: EVENT_buzz %d \n", currentDataPoint.valuebuzz);
            if(0x01 == currentDataPoint.valuebuzz)
            {
                BuzzWrite(1000);
            }
            else
            {
            }
            break;
        case EVENT_relay_3:
            currentDataPoint.valuerelay_3 = dataPointPtr->valuerelay_3;
            GIZWITS_LOG("Evt: EVENT_relay_3 %d \n", currentDataPoint.valuerelay_3);
            if(0x01 == currentDataPoint.valuerelay_3)
            {
                RelayWrite(3,1);
            }
            else
            {
                RelayWrite(3,0);
            }
            break;

        case EVENT_mode_auto_manu:
            currentDataPoint.valuemode_auto_manu = dataPointPtr->valuemode_auto_manu;
            GIZWITS_LOG("Evt: EVENT_mode_auto_manu %d \n", currentDataPoint.valuemode_auto_manu);
            if(0x01 == currentDataPoint.valuemode_auto_manu)//设置自动模式
            {

            }
            else
            {

            }
            break;
        case EVENT_mode_winter_summer:
            currentDataPoint.valuemode_winter_summer = dataPointPtr->valuemode_winter_summer;
            GIZWITS_LOG("Evt: EVENT_mode_winter_summer %d \n", currentDataPoint.valuemode_winter_summer);
            if(0x01 == currentDataPoint.valuemode_winter_summer)
            {
            }
            else
            {
            }
            break;
        case EVENT_mode_safe:
            currentDataPoint.valuemode_safe = dataPointPtr->valuemode_safe;
            GIZWITS_LOG("Evt: EVENT_mode_safe %d \n", currentDataPoint.valuemode_safe);
            if(0x01 == currentDataPoint.valuemode_safe)
            {
            }
            break;

        case EVENT_temp_upper:
            currentDataPoint.valuetemp_upper = dataPointPtr->valuetemp_upper;
            GIZWITS_LOG("Evt: EVENT_temp_upper %d \n", currentDataPoint.valuetemp_upper);
            if(0x00 != currentDataPoint.valuetemp_upper)//用户尝试改变温度上下限
            {


            }
            break;

        case EVENT_temp_lower:
            currentDataPoint.valuetemp_lower = dataPointPtr->valuetemp_lower;
            GIZWITS_LOG("Evt: EVENT_temp_lower %d \n", currentDataPoint.valuetemp_lower);
            if(0x00 != currentDataPoint.valuetemp_lower)//用户尝试改变温度上下限
            {
            }

            break;
        case EVENT_humi_threshold:
            currentDataPoint.valuehumi_threshold = dataPointPtr->valuehumi_threshold;
            GIZWITS_LOG("Evt: EVENT_humi_threshold %d \n", currentDataPoint.valuehumi_threshold);
            if(0x00 != currentDataPoint.valuehumi_threshold)//用户尝试改变湿度阈值
            {
            }
            break;
        case EVENT_heater_hour:
            currentDataPoint.valueheater_hour = dataPointPtr->valueheater_hour;
            GIZWITS_LOG("Evt: EVENT_heater_hour %d \n", currentDataPoint.valueheater_hour);
            if(0x00 != currentDataPoint.valueheater_hour)//用户尝试改变定时 小时
            {
            }
            break;
        case EVENT_heater_min:
            currentDataPoint.valueheater_min = dataPointPtr->valueheater_min;
            GIZWITS_LOG("Evt: EVENT_heater_min %d \n", currentDataPoint.valueheater_min);
            if(0x00 != currentDataPoint.valueheater_min)//用户尝试改变定时 分钟
            {
            }
            break;



        case WIFI_SOFTAP:
            break;
        case WIFI_AIRLINK:
            break;
        case WIFI_STATION:
            break;
        case WIFI_CON_ROUTER:

            break;
        case WIFI_DISCON_ROUTER:

            break;
        case WIFI_CON_M2M:

            break;
        case WIFI_DISCON_M2M:
            break;
        case WIFI_RSSI:
            GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
            break;
        case TRANSPARENT_DATA:
            GIZWITS_LOG("TRANSPARENT_DATA \n");
            //user handle , Fetch data from [data] , size is [len]
            break;
        case WIFI_NTP:
            GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
            break;
        case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
#if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
#else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
#endif
            break;
        default:
            break;
        }
    }

    return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
    Delay_ms(100);

    my_temp_handler(); //温度处理函数
    my_humi_handler();//湿度处理函数
    my_heater_handler();
    my_ir_handler();//人体红外数据处理函数

    currentDataPoint.valuebuzz = 0;//关闭蜂鸣器状态


}
void my_oled_hadler()
{
    OLED_DispStr(0, 17, "temp:    C", &tFont12);//温度
    OLED_DisDigital(50, 17, currentDataPoint.valuetemp, &tFont12);
    OLED_DispStr(0, 32, "humi:    %", &tFont12);//湿度
    OLED_DisDigital(50, 32, currentDataPoint.valuerh, &tFont12);

    OLED_DispStr(0, 50, "    -  -  -  : ", &tFont12);//符号
    OLED_DisDigital(0, 52, gizwitsProtocol.TimeNTP.year, &tFont12);
    OLED_DisDigital(36, 52, gizwitsProtocol.TimeNTP.month, &tFont12);
    OLED_DisDigital(54, 52, gizwitsProtocol.TimeNTP.day, &tFont12);
    OLED_DisDigital(78, 52, gizwitsProtocol.TimeNTP.hour, &tFont12);
    OLED_DisDigital(96, 52, gizwitsProtocol.TimeNTP.minute, &tFont12);
}
void my_ir_handler()
{
    currentDataPoint.valueir =  irRead();//读取人体红外数据

    if(currentDataPoint.valuemode_auto_manu)//如果是自动模式
    {
        if(currentDataPoint.valuemode_safe)//如果是安全模式
        {
            if(irRead())//如果有检测到人体
            {
                BuzzWrite(500);
                LedWrite(1,1);
                LedWrite(2,1);
                LedWrite(3,1);
                RelayWrite(4,1);
                currentDataPoint.valuerelay_4=1;
            }
            else//如果没人
            {
                RelayWrite(4,0);
                LedWrite(1,0);
                LedWrite(2,0);
                LedWrite(3,0);
                currentDataPoint.valuerelay_4=0;
            }
        }
        else//不是安全模式
        {
            if(irRead())//如果有检测到人体
            {
                LedWrite(1,1);
                LedWrite(2,1);
                LedWrite(3,1);
                RelayWrite(4,1);
                currentDataPoint.valuerelay_4=1;
            }
            else//如果没人
            {
                RelayWrite(4,0);
                LedWrite(1,0);
                LedWrite(2,0);
                LedWrite(3,0);
                currentDataPoint.valuerelay_4=0;
            }
        }
    }

    else//如果是手动模式
    {
        if(currentDataPoint.valuemode_safe)//如果是安全模式
        {
            if(irRead())//如果有检测到人体
            {
                BuzzWrite(500);
                LedWrite(1,1);
                LedWrite(2,1);
                LedWrite(3,1);
                RelayWrite(4,1);
                currentDataPoint.valuerelay_4=1;
            }
            else//如果没人
            {
                RelayWrite(4,0);
                LedWrite(1,0);
                LedWrite(2,0);
                LedWrite(3,0);
                currentDataPoint.valuerelay_4=0;
            }
        }
        else//不是安全模式
        {
            //不动作
        }
    }
}



void my_temp_handler()
{
    uint8_t temperature,humidity;
    //读取温度并放置在数据点
    if(!dht11Read(&temperature,&humidity))
    {
        //GIZWITS_LOG("temperature= %d \n humidity= %d\n",temperature,humidity);
        currentDataPoint.valuetemp =temperature;//Add Sensor Data Collection
        currentDataPoint.valuerh =humidity;//Add Sensor Data Collection
    }
    if(currentDataPoint.valuemode_auto_manu)//如果是自动模式
    {
        //温度控制
        if(currentDataPoint.valuetemp_upper>currentDataPoint.valuetemp_lower)//只有当温度上限 大于 温度下限，才能够进行设置
        {
            if(currentDataPoint.valuetemp >= currentDataPoint.valuetemp_upper)//当前温度 大于 温度上限，
            {
                if(currentDataPoint.valuemode_winter_summer) //如果是夏季模式
                {
                    RelayWrite(1,1);//打开空调（制冷由用户自行设定）
                    currentDataPoint.valuerelay_1=1;
                }
                else//冬季模式
                {
                    RelayWrite(1,0);//关闭空调（制冷由用户自行设定）
                    currentDataPoint.valuerelay_1=0;
                }
            }
            if(currentDataPoint.valuetemp <= currentDataPoint.valuetemp_lower)//当前温度 小于 温度下限，打开空调
            {
                if(currentDataPoint.valuemode_winter_summer) //如果是夏季模式
                {
                    RelayWrite(1,0);//关闭空调（制冷由用户自行设定）
                    currentDataPoint.valuerelay_1=0;
                }
                else//冬季模式
                {
                    RelayWrite(1,1);//打开空调（制冷由用户自行设定）
                    currentDataPoint.valuerelay_1=1;
                }
            }
            if((currentDataPoint.valuetemp > currentDataPoint.valuetemp_lower)
                    &&(currentDataPoint.valuetemp < currentDataPoint.valuetemp_upper))//温度在上限和下限之间
            {
                RelayWrite(1,0);//关闭空调
                currentDataPoint.valuerelay_1=0;
            }
        }
        else//温度上限 小于 温度下限，驳回操作
        {
            currentDataPoint.valuetemp_upper=0;
            currentDataPoint.valuetemp_lower=0;
            currentDataPoint.valuerelay_1=0;
        }





    }
    else//如果是手动模式，则不可调整温度上下限,不可调整湿度下限，不可设置冬夏模式，驳回操作
    {
        //GIZWITS_LOG("manu_mode can't change temp_upper and temp_lower\n");
        currentDataPoint.valuetemp_upper=0;
        currentDataPoint.valuetemp_lower=0;
        currentDataPoint.valuehumi_threshold=10;
        currentDataPoint.valuemode_winter_summer=0;
        currentDataPoint.valueheater_hour=0;
        currentDataPoint.valueheater_min=0;
    }


}

void my_humi_handler()
{
    uint8_t temperature,humidity;
    //读取温度并放置在数据点
    if(!dht11Read(&temperature,&humidity))
    {
        //GIZWITS_LOG("temperature= %d \n humidity= %d\n",temperature,humidity);
        currentDataPoint.valuetemp =temperature;//Add Sensor Data Collection
        currentDataPoint.valuerh =humidity;//Add Sensor Data Collection
    }
    if(currentDataPoint.valuemode_auto_manu)//如果是自动模式
    {
        //湿度控制
        if(currentDataPoint.valuerh<currentDataPoint.valuehumi_threshold-5)//如果湿度小于设定湿度阈值 5%以上
        {
            RelayWrite(2,1);//打开加湿器
            currentDataPoint.valuerelay_2=1;
        }
        if(currentDataPoint.valuerh>currentDataPoint.valuehumi_threshold+5)//如果湿度大于设定湿度阈值 5%以上
        {
            RelayWrite(2,0);//关闭加湿器
            currentDataPoint.valuerelay_2=0;
        }
    }
    else//如果是手动模式，则不可调整温度上下限,不可调整湿度下限，不可设置冬夏模式，驳回操作
    {
        //GIZWITS_LOG("manu_mode can't change temp_upper and temp_lower\n");
        currentDataPoint.valuetemp_upper=0;
        currentDataPoint.valuetemp_lower=0;
        currentDataPoint.valuehumi_threshold=10;
        currentDataPoint.valuemode_winter_summer=0;
        currentDataPoint.valueheater_hour=0;
        currentDataPoint.valueheater_min=0;
    }
}
void my_heater_handler()
{   if(currentDataPoint.valuemode_auto_manu)//如果是自动模式
    {
        //热水器控制
        if(gizwitsProtocol.TimeNTP.hour == currentDataPoint.valueheater_hour) //如果当前时间和所设定时间相等
        {
            if(gizwitsProtocol.TimeNTP.minute >= currentDataPoint.valueheater_min)//如果当前时间和所设定分钟相等或大于所设定分钟
            {
                RelayWrite(3,1);//打开热水器
                currentDataPoint.valuerelay_3=1;
            }
            else//不在定时范围内
            {
                RelayWrite(3,0);//关闭热水器
                currentDataPoint.valuerelay_3=0;
            }
        }
        if (gizwitsProtocol.TimeNTP.hour == currentDataPoint.valueheater_hour+1)//如果当前时间和所设定时间一小时以内
        {
            if(gizwitsProtocol.TimeNTP.minute <= currentDataPoint.valueheater_min)//当前时间小于所设定的分钟
            {
                RelayWrite(3,1);//打开热水器
                currentDataPoint.valuerelay_3=1;
            }
            else//不在定时范围内
            {
                RelayWrite(3,0);//关闭热水器
                currentDataPoint.valuerelay_3=0;
            }
        }
    }
    else//如果是手动模式，则不可调整温度上下限,不可调整湿度下限，不可设置冬夏模式，驳回操作
    {
        //GIZWITS_LOG("manu_mode can't change temp_upper and temp_lower\n");
        currentDataPoint.valuetemp_upper=0;
        currentDataPoint.valuetemp_lower=0;
        currentDataPoint.valuehumi_threshold=10;
        currentDataPoint.valuemode_winter_summer=0;
        currentDataPoint.valueheater_hour=0;
        currentDataPoint.valueheater_min=0;
    }
}
/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    OLED_Init();
    OLED_DispStr(0, 0, "-- Smart Home --", &tFont16);
    irInit();
    LedInit();
    RelayInit();
    BuzzInit();
    irInit();
    GIZWITS_LOG("IR Init\n");
    if(!dht11Init())
        GIZWITS_LOG("dht11 Init Success \n");

    BuzzWrite(1000);


    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/

    currentDataPoint.valuerelay_1 = 0;
    currentDataPoint.valuerelay_2 = 0;
    currentDataPoint.valuerelay_3 = 0;
    currentDataPoint.valuerelay_4 = 0;
    currentDataPoint.valuebuzz = 0;
    currentDataPoint.valueir = 0;
    currentDataPoint.valuetemp = 0;
    currentDataPoint.valuerh = 0;
    currentDataPoint.valuemode_auto_manu = 0;
    currentDataPoint.valuemode_winter_summer = 0;
    currentDataPoint.valuemode_safe = 0;
    currentDataPoint.valuetemp_upper = 0;
    currentDataPoint.valuetemp_lower = 0;
    currentDataPoint.valuehumi_threshold = 0;
    currentDataPoint.valueheater_hour = 0;
    currentDataPoint.valueheater_min = 0;

}


/**
* @brief Millisecond timing maintenance function, milliseconds increment, overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief Read millisecond count

* @param none
* @return millisecond count
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief MCU reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
    __set_FAULTMASK(1);
    HAL_NVIC_SystemReset();
}

/**@} */

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART1 and Loop until the end of transmission */
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

    return ch;
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==&htim2)
    {
        keyHandle((keysTypedef_t *)&keys);
        gizTimerMs();
    }
}

/**
* @brief Timer TIM3 init function

* @param none
* @return none
*/
void timerInit(void)
{
    HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief  This function handles USART IDLE interrupt.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle)
{
    if(UartHandle->Instance == USART2)
    {
        gizPutData((uint8_t *)&aRxBuffer, 1);

        HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);//开启下一次接收中断
    }
}

/**
* @brief USART init function

* Serial communication between WiFi modules and device MCU
* @param none
* @return none
*/
void uartInit(void)
{
    HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);//开启下一次接收中断
}

/**
* @brief Serial port write operation, send data to WiFi module
*
* @param buf      : buf address
* @param len      : buf length
*
* @return : Return effective data length;-1，return failure
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint8_t crc[1] = {0x55};
    uint32_t i = 0;

    if(NULL == buf)
    {
        return -1;
    }

    for(i=0; i<len; i++)
    {
        HAL_UART_Transmit_IT(&huart2, (uint8_t *)&buf[i], 1);
        while (huart2.gState != HAL_UART_STATE_READY);//Loop until the end of transmission

        if(i >=2 && buf[i] == 0xFF)
        {
            HAL_UART_Transmit_IT(&huart2, (uint8_t *)&crc, 1);
            while (huart2.gState != HAL_UART_STATE_READY);//Loop until the end of transmission
        }
    }

#ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);

        if(i >=2 && buf[i] == 0xFF)
        {
            GIZWITS_LOG("%02x ", 0x55);
        }
    }
    GIZWITS_LOG("\n");
#endif

    return len;
}
