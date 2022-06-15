c++ -Wall -Werror -Wextra -D FT=1 vector_test.cpp
./a.out > ft
c++ -Wall -Werror -Wextra -D STD=1 vector_test.cpp
./a.out > std

diff ft std
