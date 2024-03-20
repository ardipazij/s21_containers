CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17  
LDFLAGS = -lgtest -pthread
GCFLAGS = -fprofile-arcs -ftest-coverage
VG_FLAGS =	--vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
TEST = test


.PHONY: test

all: clean gcov_report

test: clean
	@echo "+-------------------+"
	@echo "|     UNIT_TEST     |"
	@echo "+-------------------+"
	@$(CC) $(CFLAGS)   ./../unit_test/*.cc ./../unit_test/matrix/*.cc -o $(TEST) $(LDFLAGS) $(GCFLAGS)
	@./$(TEST)
	@mv test ../build/


gcov_report: test
	@echo "+-------------------+"
	@echo "|    GCOV_REPORT    |"
	@echo "+-------------------+"
	@lcov -t "containers_test" -o containers_test.info -c -d . --no-external --ignore-errors mismatch
	@genhtml -o report containers_test.info
	@open report/index.html
	@mkdir lcov_files
	@mv *.gcda *.gcno *.info lcov_files

clean:
	@rm -rf report
	@rm -rf lcov_files
	@rm -f *.o *.a *.out
	@rm -f ../build/test
	@rm -f *.gcda *.gcno *.info
	@rm -rf *.dSYM
	@rm -f .DS_Store */.DS_Store

style:
	@echo "+-------------------+"
	@echo "|       STYLE       |"
	@echo "+-------------------+"
	@clang-format -n -style=Google *.h  */*.h */*.tpp 

docker_setup:
	@echo "+-------------------+"
	@echo "|    DOCKER_SETUP   |"
	@echo "+-------------------+"
	@rm -rf ~/Library/Containers/com.docker.docker
	@mkdir -p ~/goinfre/Docker/Data
	@ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker
	@open ~/../../Applications/Docker.app

docker:
	@echo "+-------------------+"
	@echo "|    DOCKER_RUN     |"
	@echo "+-------------------+"
	@sh ../build/run.sh

valgrind: test
	@echo "+-------------------+"
	@echo "|   VALGRIND_LEAK   |"
	@echo "+-------------------+"
	@CK_FORK=no valgrind  $(VG_FLAGS) ./../build/$(TEST)

leaks: 
	@echo "+-------------------+"
	@echo "|     LEAKS_RUN     |"
	@echo "+-------------------+"
	@leaks -atExit -- ./../build/$(TEST)
