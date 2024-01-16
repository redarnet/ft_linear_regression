NAME = LinearRegression
CC = c++
OBJ_DIR = obj
SRC_DIR = ./src
FLAGS = -Wall -Wextra -Werror -std=c++11

TRAIN_SRC = $(SRC_DIR)/main_train.cpp $(SRC_DIR)/LinearRegressionModel.cpp
PREDICT_SRC = $(SRC_DIR)/main_predict.cpp $(SRC_DIR)/LinearRegressionModel.cpp

TRAIN_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TRAIN_SRC))
PREDICT_OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(PREDICT_SRC))

.PHONY: all
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(TRAIN_OBJ) $(PREDICT_OBJ)
	$(CC) $(TRAIN_OBJ) $(FLAGS) -o train
	$(CC) $(PREDICT_OBJ) $(FLAGS) -o predict

.PHONY: train
train: $(TRAIN_OBJ)
	$(CC) $(TRAIN_OBJ) $(FLAGS) -o train

.PHONY: predict
predict: $(PREDICT_OBJ)
	$(CC) $(PREDICT_OBJ) $(FLAGS) -o predict

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -f train
	rm -f predict

.PHONY: re
re: fclean all