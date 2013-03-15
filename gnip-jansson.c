#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <jansson.h>

#define MAXLEN 16*1024

extern FILE *stdout;
int max_screen_name_len = 0;

int main(int argc, char **argv) {
	struct json_object *new_obj,*txt;
	char mystring[MAXLEN];
	char *newline;
	int a,screen_name_len;
	char *src, *dst, *str;

	json_t *root;
	json_error_t error;
	json_t *user;
	json_t *original;
	json_t *gnip;
	json_t *gnip_lang;
	json_t *gnip_klout;
	json_t *gnip_lang_value;
	json_t *gnip_lang_confidence;
	json_t *message_id;
	json_t *message_text;
	json_t *message_screen_name;
	json_t *message_lang;

	while (!feof(stdin)) {
		if (fgets(mystring,MAXLEN,stdin)) {
			newline = strchr(mystring, '\n');
			if (newline) {
				*newline = '\0';
			}
			root = json_loads(mystring, 0, &error);
			original = json_object_get(root, "original");
			gnip = json_object_get(root, "metadata");
			gnip_lang = json_object_get(gnip, "language");
			gnip_klout = json_object_get(gnip, "klout_score");
			gnip_lang_value = json_object_get(gnip_lang, "value");
			gnip_lang_confidence = json_object_get(gnip_lang, "confidence");
			user = json_object_get(original, "user");
			message_id = json_object_get(original, "id_str");
			message_text = json_object_get(original, "text");
			message_lang = json_object_get(user, "lang");
			message_screen_name = json_object_get(user, "screen_name");
			if (message_id) {
				screen_name_len = strlen(json_string_value(message_screen_name));
				if (screen_name_len > max_screen_name_len) {
					max_screen_name_len = screen_name_len;
				}
				printf("%s|",json_string_value(message_lang));
				if (gnip_lang_value) {
					printf("%s|%3ld|", json_string_value(gnip_lang_value),
								lround(json_number_value(gnip_lang_confidence)));
				} else {
					printf("--|---|");
				}
				if (gnip_klout) {
					printf("%2ld|", lround(json_number_value(gnip_klout)));
				} else {
					printf("--|");
				}
				printf("%s|@%s",json_string_value(message_id),json_string_value(message_screen_name));
				for (a=0;a<(max_screen_name_len - screen_name_len);a++) {
					printf(" ");
				}
				str = (char *) json_string_value(message_text);
				for (src = dst = str; *src != '\0'; src++) {
					*dst = *src;
					if (*dst != '\n') dst++;
				}
				*dst = '\0';

				printf("|%s\n",json_string_value(message_text));
				fflush(stdout);
			}
			json_decref(root);
		}
	}
}
