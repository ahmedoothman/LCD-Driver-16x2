/*
 * Header.h
 *
 * Created: 6/22/2022 11:02:40 AM
 *  Author: Ahmed Othman
 */


#ifndef HEADER_H_
#define HEADER_H_

#define SET_BIT(ADDRESS,BIT) ADDRESS |=(1<<BIT)
#define RESET_BIT(ADDRESS,BIT) ADDRESS &=~(1<<BIT)
#define TOGGLE_BIT(ADDRESS,BIT) ADDRESS ^=(1<<BIT)
#define READ_BIT(ADDRESS,BIT) ((ADDRESS & (1<<BIT))>>BIT)





#endif /* HEADER_H_ */
