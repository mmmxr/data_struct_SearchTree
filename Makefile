search:search.c 
	gcc -g -o $@ $^

.PHONY:clean

clean:
	rm -f search
