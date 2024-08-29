#!/bin/bash

if [ $1 = "re" ]; then 
	make re
else 
	make
fi
cd ./minishell_tester
if [ $2 = "builtins" ]; then 
	./tester builtins
elif [ $1 = "builtins" ]; then
	./tester builtins
else
	./tester
fi

