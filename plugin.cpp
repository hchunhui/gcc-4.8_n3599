#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
 
#include "gcc-plugin.h"
#include "tree.h"
#include "langhooks.h"
#include "cpplib.h"
#include "c-family/c-common.h"
#include "diagnostic-core.h"

int plugin_is_GPL_compatible;

void new_c_parse_file (void);
void init_pragma (void);

extern struct cpp_options *cpp_opts;

void start_unit_callback(void *gcc_data, void *user_data)
{
	if (strcmp(lang_hooks.name, "GNU C++") == 0) {
		if (cxx_dialect < cxx1y) {
			verbatim("notice: use \"-std=c++1y\" to turn on n3599");
		}

		if (!cpp_opts->preprocessed) {
			fatal_error("rerun with \"-no-integrated-cpp\"");
		}
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
