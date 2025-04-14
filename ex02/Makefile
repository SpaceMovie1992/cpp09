NAME = PmergeMe
CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -g3
INCLUDES = -I ./inc

SRCS = src/PmergeMe.cpp src/main.cpp

OBJDIR = objs
OBJS = $(SRCS:src/%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

.SILENT:

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	echo $(GREEN)"Building $(NAME)"$(DEFAULT);

$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJDIR)
	echo $(RED)"Removing $(NAME)"$(DEFAULT);

re: fclean all
	echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colours
DEFAULT = "\033[39m"
GREEN = "\033[32m"
RED = "\033[31m"