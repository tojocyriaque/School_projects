#include "husers.h"

void print_head(){
	printf("Content-Type:text/html \n\n");
	printf("<html>\n");
	printf("<head>\n");
	printf("<meta charset=UTF-8>");
	printf("<title>Users Page</title>");
	printf("</head>\n\n");
}

void print_styles(){
	printf("<style>");
	printf("h3{color: skyblue; font-family: sans-serif}");
	printf("tr{font-family: Helvetica}");
	printf("body{display: flex; flex-direction: row; justify-content: center;}");
	printf(".login{color: red}");
	printf(".id{color: #458845}");
	printf(".home{color: gray}");
	printf(".shell{color: gray}");
	printf("</style>");
}

void print_body(){
	printf("<body>\n");
	print_styles();
	print_HTML_husers_table();
	printf("</body>\n");
}

void print_foot(){
	printf("</html>");
}

void print_HTML_structured(){
	print_head();
	print_body();
	print_foot();
}
