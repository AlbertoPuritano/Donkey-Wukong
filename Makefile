CXX ?= g++
PKG_CONFIG ?= pkg-config

BUILD_DIR := build
TARGET := $(BUILD_DIR)/donkey-wukong

SOURCES := \
	Source/main.cpp \
	Source/Game.cpp \
	Source/Graphics.cpp \
	Source/Entities.cpp \
	Source/Sounds.cpp

ALLEGRO_MODULES := \
	allegro_main-5 \
	allegro-5 \
	allegro_font-5 \
	allegro_ttf-5 \
	allegro_image-5 \
	allegro_audio-5 \
	allegro_acodec-5

CPPFLAGS += -IHeaders $(shell $(PKG_CONFIG) --cflags $(ALLEGRO_MODULES))
CXXFLAGS += -std=c++11 -Wall -Wextra
LDLIBS += $(shell $(PKG_CONFIG) --libs $(ALLEGRO_MODULES))

.PHONY: all run clean check-deps

all: check-deps $(TARGET)

check-deps:
	@command -v $(PKG_CONFIG) >/dev/null 2>&1 || { echo "pkg-config is required but was not found."; exit 1; }
	@$(PKG_CONFIG) --exists $(ALLEGRO_MODULES) || { \
		echo "Missing Allegro pkg-config modules:"; \
		echo "  $(ALLEGRO_MODULES)"; \
		echo "Install Allegro 5 development files, then try again."; \
		exit 1; \
	}

$(TARGET): $(SOURCES) | $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD_DIR):
	mkdir -p $@

run: all
	cd $(BUILD_DIR) && ./$(notdir $(TARGET))

clean:
	rm -rf $(BUILD_DIR)

