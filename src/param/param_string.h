/*
 * param_string.h
 *
 *  Created on: Sep 30, 2016
 *      Author: johan
 */

#ifndef SRC_PARAM_PARAM_STRING_H_
#define SRC_PARAM_PARAM_STRING_H_

#include <param/param.h>

void param_value_str(param_t *param, unsigned int i, char * out, int len);
int param_str_to_value(param_type_e type, char * in, void * out);
void param_type_str(param_type_e type, char * out, int len);
void param_print(param_t * param, int offset, int nodes[], int nodes_count, int verbose);
uint32_t param_maskstr_to_mask(char * str);

#endif /* SRC_PARAM_PARAM_STRING_H_ */
