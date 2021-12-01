all:
	clang++ -o check_flag check_flag.cpp CustomVM.cpp
	strip check_flag
release-protected:
	clang++ -O3 -o check_flag check_flag.cpp CustomVM.cpp
	strip check_flag
release-unprotected:
	clang++ -o unprotected_check_flag unprotected_check_flag.cpp