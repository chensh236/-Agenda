CC := g++ -g -std=c++11
INC_DIR := include
SRC_DIR := src
BUILD_DIR := bulid
BIN_DIR := bin
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/main : $(BUILD_DIR)/Date.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/Agenda.o
	@mkdir -p $(BIN_DIR)/
	$(CC) $(INCLUDE) -g -o $@ $(BUILD_DIR)/Date.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/Agenda.o

$(BUILD_DIR)/Agenda.o : $(SRC_DIR)/Agenda.cpp
	@mkdir -p $(BUILD_DIR)/
	$(CC) $(INCLUDE) -c -g -o $@ $(SRC_DIR)/Agenda.cpp

$(BUILD_DIR)/Date.o : $(SRC_DIR)/Date.cpp
	@mkdir -p $(BUILD_DIR)/
	$(CC) $(INCLUDE) -c -g -o $@ $(SRC_DIR)/Date.cpp

$(BUILD_DIR)/User.o : $(SRC_DIR)/User.cpp
	@mkdir -p $(BUILD_DIR)/
	$(CC) $(INCLUDE) -c -g -o $@ $(SRC_DIR)/User.cpp

$(BUILD_DIR)/Meeting.o : $(SRC_DIR)/Meeting.cpp
	@mkdir -p $(BUILD_DIR)/
	$(CC) $(INCLUDE) -c -g -o $@ $(SRC_DIR)/Meeting.cpp

$(BUILD_DIR)/Storage.o : $(SRC_DIR)/Storage.cpp
	@mkdir -p $(BUILD_DIR)/
	$(CC) $(INCLUDE) -c -g -o $@ $(SRC_DIR)/Storage.cpp

$(BUILD_DIR)/AgendaService.o : $(SRC_DIR)/AgendaService.cpp
	@mkdir -p $(BUILD_DIR)/
	$(CC) $(INCLUDE) -c -g -o $@  $(SRC_DIR)/AgendaService.cpp

$(BUILD_DIR)/AgendaUI.o : $(SRC_DIR)/AgendaUI.cpp
	@mkdir -p $(BUILD_DIR)/
	$(CC) $(INCLUDE) -c -g -o $@  $(SRC_DIR)/AgendaUI.cpp

clean :
	@rm -rf $(BUILD_DIR)/
	@rm -rf $(BIN_DIR)/