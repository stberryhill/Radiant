#Compiler to use
CC=gcc -std=c89 -Wall -Wno-deprecated

#Include Directory(External Libraries, EX: OpenGL, GLEW)
PLATFORM = unix
PLATFORM2 = osx
BACKEND = opengl
SOURCEDIR = ./
OBJDIR = build
INCLUDE = ../
LIBRARIES = -lglfw.3.3 -framework opengl -lFreeImage

#Grab sources & headers
PISOURCES = $(wildcard $(SOURCEDIR)/*.c) #platform independent sources
PDSOURCES = $(wildcard $(SOURCEDIR)/$(PLATFORM)/*.c) #platform dependent sources
PDSOURCES2 = $(wildcard $(SOURCEDIR)/$(PLATFORM2)/*.c) #more platform dependent sources
BACKENDSOURCES = $(wildcard $(SOURCEDIR)/$(BACKEND)/*.c) #graphics backend-specific sources

HEADERS = $(wildcard $(SOURCEDIR)/*.h)

#Use addprefix function to add ./obj/ to each individual obj file name (EX: ./obj/ + Camera.o = ./obj/Camera.o)
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(PISOURCES:.c=.o)))
OBJECTS += $(addprefix $(OBJDIR)/$(PLATFORM)/, $(notdir $(PDSOURCES:.c=.o)))
OBJECTS += $(addprefix $(OBJDIR)/$(PLATFORM2)/, $(notdir $(PDSOURCES2:.c=.o)))
OBJECTS += $(addprefix $(OBJDIR)/$(BACKEND)/, $(notdir $(BACKENDSOURCES:.c=.o)))


#Compiler flags
CFLAGS= -Wall -g -I $(INCLUDE) -I ./

#Set executable name
STATICLIB=build/lib.a

all: $(STATICLIB) $(OBJECTS)

$(OBJDIR)/%.o: $(SOURCEDIR)/%.c 
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/$(PLATFORM)/%.o: $(SOURCEDIR)/$(PLATFORM)/%.c 
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJDIR)/$(PLATFORM2)/%.o: $(SOURCEDIR)/$(PLATFORM2)/%.c 
	$(CC) -c $< $(CFLAGS) -o $@


#Objects depend on object directory
$(OBJECTS): | $(OBJDIR)

#Create new object directory if one doesnt exist already
$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/$(PLATFORM)
	mkdir $(OBJDIR)/$(PLATFORM2)

.PHONY : clean
clean:
	rm $(EXECUTABLE) $(OBJECTS)

$(STATICLIB): $(OBJECTS)
	ar rcs $@ $^
