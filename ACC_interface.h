/*
 * ACC_interface.h
 *
 *  Created on: Oct 25, 2018
 *      Author: Abdulnaser
 */

#ifndef ACC_INTERFACE_H_
#define ACC_INTERFACE_H_

#define acc_slave_address 0X68

void ACC_Init(void);
void ACC_write_data(u8 u8_Reg_Add,u8 u8_data);
s16 ACC_Read_Data(u8 reg_add);
s16 ACC_Read_XData(void);
s16 ACC_Read_YData(void);
s16 ACC_Read_ZData(void);

#endif /* ACC_INTERFACE_H_ */
