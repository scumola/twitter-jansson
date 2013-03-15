#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>

#define MAXLEN 16*1024

extern FILE *stdout;

int main(int argc, char **argv) {
	struct json_object *new_obj,*txt;
	char mystring[MAXLEN];
	char *newline,*str,*src,*dst;

	json_t *root;
	json_error_t error;
	json_t *user;
	json_t *message_text;
	json_t *message_lang;

	while (!feof(stdin)) {
		if (fgets(mystring,MAXLEN,stdin)) {
			newline = strchr(mystring, '\n');
			if (newline) {
				*newline = '\0';
			}
//			printf ("LINE: %s",mystring);
			root = json_loads(mystring, 0, &error);
			if (!root) {
//				fprintf(stderr, "ERROR: error parsing json string: %s\n",error.text);
				continue;
			}
			user = json_object_get(root, "user");
			if (!user) {
//				fprintf(stderr, "ERROR: error finding user branch\n");
				continue;
			}
			message_text = json_object_get(root, "text");
			if (!json_is_string(message_text)) {
//				fprintf(stderr, "ERROR: error finding text\n");
				continue;
			}
			message_lang = json_object_get(user, "lang");
			if (!json_is_string(message_lang)) {
//				fprintf(stderr, "ERROR: error finding user->lang\n");
				continue;
			}
			if (!strcmp(json_string_value(message_lang),"en")) {
				str = (char *) json_string_value(message_text);
				for (src = dst = str; *src != '\0'; src++) {
					*dst = *src;
					if (*dst != '\n') dst++;
				}
				*dst = '\0';
				// printf("%s\n",str);
				printf("%s\n",json_string_value(message_text));
				fflush(stdout);
			}
			json_decref(root);
		}
	}
}
