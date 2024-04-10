NAME			:= PmergeMe
CPPFLAGS		:= -g -Wall -Wextra -Werror
STD				:= -std=c++98
SRCDIR			:= src/
SRCS			:= main.cpp
BINDIR			:= bin/
HEADERS			:= include/
OBJS			:= $(addprefix $(BINDIR), $(SRCS:.cpp=.o))
RM				:= rm -f
CC				:= c++

all : $(NAME)

$(BINDIR)%.o : %.cpp
	@$(CC) -c $(CPPFLAGS) $(STD) -o $@ $^

$(NAME) : $(BINDIR) $(OBJS)
	@echo $(NAME): Compiling!
	@$(CC) $(CPPFLAGS) $(STD) -o $(NAME) $(OBJS)

$(BINDIR) :
	@mkdir $(BINDIR)

clean:
	@echo $(NAME): Deleting binaries.
	@rm -rf $(BINDIR)

fclean: clean
	@echo $(NAME): Deleting program.
	@rm -f $(NAME)

re : fclean all