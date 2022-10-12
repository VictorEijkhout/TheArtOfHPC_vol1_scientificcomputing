# -*- makefile -*-
################################################################
################################################################
####
#### Makefile for:
####     Introduction to High-Performance Scientific Computing
#### by Victor Eijkhout
#### copyright 2010-2021
####
#### top level makefile
####
################################################################
################################################################

info ::

info ::
	@echo "Do: make clean"
clean ::
	@rm -f *~
	@for d in booksources code slides ; do \
	    echo "cleaning $$d" \
	     && ( cd $$d && make clean ) \
	    ; \
	done

