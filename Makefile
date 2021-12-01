all:
	clang++ -o check_flag check_flag.cpp CustomVM.cpp
	strip check_flag
release:
	clang++ -O3 -o check_flag check_flag.cpp CustomVM.cpp
	strip check_flag