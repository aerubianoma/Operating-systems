all: menu search

menu: menu.c
	gcc -o menu menu.c

search: search.c
	gcc -o search search.c

run: run-menu run-search

run-menu: menu
	./menu

run-search: search
	./search	
