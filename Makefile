SHELL=/bin/sh

all:

clean:
	find . -type f -name 'Problem[0-9][0-9][0-9]' -exec rm -f {} \;
