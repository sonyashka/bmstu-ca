#include <stdio.h>
#include "in_out.h"

#ifndef _POLYNOM_FUNC_H_
#define _POLYNOM_FUNC_H_

void sort_data(struct polynom *data);
void find_config(struct polynom *data);
void divided_difference_newton(struct polynom *data);
void divided_difference_armit(struct polynom *data);
void find_polynom_newton(struct polynom *data);
void find_polynom_armit(struct polynom *data);
int check_monotony(struct polynom data);
void swap_columns(struct polynom *data);

#endif
