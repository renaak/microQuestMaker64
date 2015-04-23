TARGET=c64

DIRECTIVE1=CBM
DIRECTIVE2=NO_DEBUG
DIRECTIVE3=__RUNTIME__

editor:
		rm -rf *.o
		cl65 --static-locals -D$(DIRECTIVE1) -D$(DIRECTIVE2) -Oi -t $(TARGET) -o mqm64-editor \
		     file.c parser.c movement.c level.c object.c advfuncs.c toolfuncs.c \
		     condition.c menu.c main.c
runtime:
		rm -rf *.o
		cl65 --static-locals -D$(DIRECTIVE3) -D$(DIRECTIVE2) -Oi -t $(TARGET) -o mqm64-runtime \
		     file.c parser.c movement.c level.c object.c advfuncs.c toolfuncs.c  \
		     condition.c runtime.c
mazegen:
		rm -rf *.o
		cl65 --static-locals -D$(DIRECTIVE1) -D$(DIRECTIVE2) -Oi -t $(TARGET) -o mqm64-mazegen \
		     file.c level.c toolfuncs.c mazegen.c
test:
		rm -rf *.o
		cl65 --static-locals -D$(DIRECTIVE1) -D$(DIRECTIVE2) -Oi -t $(TARGET) -o test \
		test.c toolfuncs.c

clean:
		rm -rf *.o
		rm -rf mqm64-editor
		rm -rf mqm64-runtime
		rm -rf mqm64-mazegen
