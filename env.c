/* This file is part of jsh.
 * 
 * jsh (jo-shell): A proof-of-concept shell implementation
 * Copyright (C) 2014 Jo Van Bulck <jo.vanbulck@student.kuleuven.be>
 *
 * jsh is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * jsh is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with jsh.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "env.h"
#include <ctype.h>

char *resolveenvvars(char *s) {
	printdebug("test", *s);
	char *p = s;
    for (p; p != NULL;p++) {
    	printdebug("%s", *p);
    	if(*p == '$') {
    		replaceenvvar(s,p);
    	}
    }

    printdebug("New command: %s",s);
	return ret;
}

int replaceenvvar(char *head, char *s) {
	char* begin = s;
	char* end;
	char *envvalue;
	char tmpChar;

	// Loop until end of string or until character that cannot be part of envvar name
	for(end = ++begin;end!=NULL && (isalnum(*end) || *end == '_');end++) {}

	printdebug("p points to end");

	// Save character after envvar name and set this character to NULL
	tmpChar = *end;
	*end = '\0';

	printdebug("Character p was saved");

	// Check if this envvar exists
	envvalue = getenv(begin);
	if(envvalue == NULL) {
		return EXIT_FAILURE;
	}

	printdebug("this envar exists.");

	// Allocate new memory, copy the complete string, set pointers to new string and free string.
	char *tmp = malloc(sizeof (char) * strlen(s) + sizeof (char) * strlen(envvalue));
	memcpy(tmp,head,strlen(head));
	begin = tmp+(begin-head);
	end = tmp+(end-head);
	free(head);
	head = tmp;


	// Replace envvar in string
	memmove(end+1,begin+strlen(envvalue),strlen(end+1));
	memcpy(begin,envvalue,strlen(envvalue));
	free(envvalue);

	// replace the character
	*end = tmpChar;
	return EXIT_SUCCESS;
}




