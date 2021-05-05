#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
 
#include "gcc-plugin.h"
#include "tree.h"
#include "langhooks.h"
int plugin_is_GPL_compatible;

void new_c_parse_file (void);
void init_pragma (void);

void start_unit_callback(void *gcc_data, void *user_data)
{
	if (strcmp(lang_hooks.name, "GNU C++") == 0) {
		fprintf(stderr, "install new C++ parser\n");
		init_pragma();
		lang_hooks.parse_file = new_c_parse_file;
	}
}

extern "C"
int plugin_init(plugin_name_args *info,
		plugin_gcc_version *ver)
{
	register_callback(info->base_name,
			  PLUGIN_START_UNIT,
			  &start_unit_callback,
			  0);
	return 0;
}
