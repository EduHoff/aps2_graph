rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

ifeq ($(OS),Windows_NT)
    TARGET_EXT = .exe
    RM = del /Q /S
    FIXPATH = $(subst /,\,$1)
    MKDIR = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
    RUN_CMD = $(call FIXPATH,$(TARGET))
else
    TARGET_EXT =
    RM = rm -rf
    FIXPATH = $1
    MKDIR = mkdir -p $1
    RUN_CMD = ./$(TARGET)
endif

CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11 -O2 -MMD -MP
INC_DIR  := include

INC_DIRS := $(INC_DIR) $(dir $(call rwildcard,$(INC_DIR),*/))
INCLUDES := $(addprefix -I,$(INC_DIRS))

PROJECT_NAME := aps2_graph
TARGET   := build/$(PROJECT_NAME)$(TARGET_EXT)
SRC_DIR  := src
OBJ_DIR  := build/obj

SRCS := $(call rwildcard,$(SRC_DIR),*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

all: compiledb $(TARGET)

run: compiledb $(TARGET)
	@$(RUN_CMD)

$(TARGET): $(OBJS)
	@$(call MKDIR,$(dir $@))
	$(CC) $(CFLAGS) $^ -o $@
	@echo "Compilation completed successfully: $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(call MKDIR,$(dir $@))
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

compiledb:
ifeq ($(OS),Windows_NT)
	@powershell -Command "$$srcs = '$(SRCS)'.Split(' '); $$objs = @(); foreach ($$s in $$srcs) { if ($$s) { $$objs += @{ directory = '$(CURDIR)'; command = '$(CC) $(CFLAGS) $(INCLUDES) -c ' + $$s; file = $$s } } }; $$objs | ConvertTo-Json | Set-Content compile_commands.json"
	@echo Updated compile_commands.json
else
	@echo "[" > compile_commands.json
	@first=1; \
	for src in $(SRCS); do \
		if [ $$first -eq 1 ]; then first=0; else echo "," >> compile_commands.json; fi; \
		echo "  {" >> compile_commands.json; \
		echo "    \"directory\": \"$(CURDIR)\"," >> compile_commands.json; \
		echo "    \"command\": \"$(CC) $(CFLAGS) $(INCLUDES) -c $$src\"," >> compile_commands.json; \
		echo "    \"file\": \"$$src\"" >> compile_commands.json; \
		echo "  }" >> compile_commands.json; \
	done
	@echo "]" >> compile_commands.json
	@echo "Updated compile_commands.json"
endif

-include $(DEPS)

clean:
	$(RM) $(call FIXPATH,$(OBJ_DIR))
	$(RM) $(call FIXPATH,$(TARGET))
	$(RM) compile_commands.json
	@echo "Cleaning complete."

.PHONY: all run clean compiledb
