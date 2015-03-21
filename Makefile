CC = gcc
TARGET = RayTracing.exe
SRCS := $(shell ls | grep c$$)
DEPEND_FILE = depend_file
CCLIB = -lm -msse2 -mfpmath=sse

ifeq ($(MAKECMDGOALS), release)
DEFINE = 	
OBJS_DIR = gcc_release
else
DEFINE = -DDEBUG
OBJS_DIR = gcc_debug
endif

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

.SUFFIXES: .c .o
.PHONY: all release debug clean test oneshot

all:
	@echo "=========================="
	@echo "usage: make release"
	@echo "       make debug"
	@echo "       make clean"
	@echo "       make test [filename=filename.obj]"
	@echo "=========================="

$(OBJS_DIR)/%.o : %.c
	$(CC) $(DEFINE) -c $< -o $@ $(CCLIB)

release: chkdir depend $(OBJS)
	$(CC) $(DEFINE) $(OBJS) -o $(TARGET) $(CCLIB)

debug: chkdir depend $(OBJS)
	$(CC) $(DEFINE) $(OBJS) -o $(TARGET) $(CCLIB)

clean:
	@rm -rf $(DEPEND_FILE) gcc_debug gcc_release $(TARGET) *.bmp

test:
	$(TARGET) $(filename)

chkdir:
	@`[ -d $(OBJS_DIR) ] || mkdir $(OBJS_DIR)`

depend: chkdir
	@rm -f $(DEPEND_FILE)
	@for FILE in $(SRCS:%.c=%); do \
		$(CC) -MM -MT $(OBJS_DIR)/$$FILE.o $$FILE.c >> $(DEPEND_FILE); \
	done

-include $(DEPEND_FILE)
