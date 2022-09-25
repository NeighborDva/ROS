/*
 * Motor_control_pwm.h
 *
 *  Created on: 2022. 8. 4.
 *      Author: user
 */

#ifndef MOTOR_CONTROL_PWM_H_
#define MOTOR_CONTROL_PWM_H_



void L298_Pin_init(void);
void motor_control(int pwm);


//CC6_PWM_Capture
void init_CCU6_ICU(void);                       /* Function to configure the CCU6                                   */
void init_PWM_signal_generation(void);          /* Function to configure the port pin for PWM generation            */
int generate_PWM_signal(void);                 /* Function to generate a simple PWM signal by toggling a port pin  */
int generate_PWM_signal2(int);

#endif /* MOTOR_CONTROL_PWM_H_ */
