# st version
VERSION = 0.8.4

# --------------------------------------------------------------------
# Theme
# --------------------------------------------------------------------

THEME ?= MATRIX

THEMES := \
	CLASSIC \
	MATRIX \
	DRACULA \
	NORD \
	GRUVBOX \
	SOLARIZED_DARK \
	TOKYO_NIGHT \
	AMBER

ifeq ($(filter $(THEME),$(THEMES)),)
$(error Invalid theme '$(THEME)'. Available themes: $(THEMES))
endif

# --------------------------------------------------------------------
# Installation paths
# --------------------------------------------------------------------

PREFIX    ?= /usr/local
MANPREFIX ?= $(PREFIX)/share/man

# --------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------

PKG_CONFIG ?= PKG_CONFIG_PATH=/usr/lib/x86_64-linux-gnu/pkgconfig pkg-config

# Let pkg-config select one coherent set of system headers/libraries.
# Do not hard-code /usr/X11R6 or /usr/local include/library paths.
PACKAGES := x11 xft xrender fontconfig freetype2 harfbuzz

PKG_CFLAGS := $(shell $(PKG_CONFIG) --cflags $(PACKAGES))
PKG_LIBS   := $(shell $(PKG_CONFIG) --libs $(PACKAGES))

INCS := $(PKG_CFLAGS)
LIBS := \
	-lm \
	-lrt \
	-lutil \
	$(PKG_LIBS)

# --------------------------------------------------------------------
# Compiler and linker
# --------------------------------------------------------------------

CC ?= cc

CPPFLAGS += \
	-DVERSION=\"$(VERSION)\" \
	-D_XOPEN_SOURCE=600

ifneq ($(THEME),CLASSIC)
CPPFLAGS += -D$(THEME)
endif

CFLAGS += \
	-std=c99 \
	-O2 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror=implicit-function-declaration \
	-Werror=int-conversion

STCPPFLAGS := $(CPPFLAGS)
STCFLAGS   := $(INCS) $(STCPPFLAGS) $(CFLAGS)
STLDFLAGS  := $(LDFLAGS) $(LIBS)
