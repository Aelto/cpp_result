# ignore this Makefile,
# still learning make.

objs = main.obj
winargs = /EHsc /I include /std:c++17 /O2

win: $(objs)
	cl $(objs) $(winargs)

main.obj: src/main.cpp include/result.h
	cl /c src/main.cpp $(winargs)

clean-win:
	del *.obj